#define UART_C
#include "uart.h"
#include "system.h"
#include "misc.h"
#include "nRF2401.h"
#include "altera_avalon_uart_regs.h"
#include "config.h"
#include "main.h"
#include "crc.h"
#include "timer.h"
#include "flash.h"
#include <string.h>



volatile unsigned int g_uart_usb1_baudrate = 0;
volatile unsigned int g_uart_usb1_control = 0;
volatile unsigned char g_uart_usb1_read_buf[UART_READ_BUF_LEN] = {0};
volatile unsigned char g_uart_usb1_read_buf_pos = 0;
volatile unsigned char g_uart_usb1_send_buf[UART_SEND_BUF_LEN] = {0};
volatile unsigned char g_uart_usb1_send_buf_pos = 0;
volatile unsigned char g_uart_usb1_send_len = 0;
volatile char g_is_uart_get_a_packet = 0; 
volatile char g_offline_comm_car_process_it = 0;
volatile char g_transfer_start = 0;
volatile char g_transfer_config = 0;
volatile char g_transfer_config_frq = DEFAULT_FREQ | 0x10;

//extern unsigned volatile long start_normal;

volatile char g_is_get_send_num = 0;
extern unsigned char g_send_num;
extern unsigned char g_send_frq_b;
extern unsigned char g_send_frq_e;

int read_uart_usb1_data( unsigned char *data )
{
	unsigned int status = 0;
	if(!data)
	{
		return -1;
	}

	status = IORD_ALTERA_AVALON_UART_STATUS(UART_USB_BASE);

	if (status & ALTERA_AVALON_UART_STATUS_RRDY_MSK)  //检查RRDY
	{
		*data = IORD_ALTERA_AVALON_UART_RXDATA(UART_USB_BASE);  //读数
		return 0;
	}
	return -1;
}

void send_uart_usb1_data(unsigned char *data, int len)
{
	int i = 0;
	g_uart_usb1_send_len = len;
	g_uart_usb1_send_buf_pos = 0;

	alt_irq_disable(PIO_C2_DR_IRQ);
	for(i=0; i<g_uart_usb1_send_len; i++)
	{
		g_uart_usb1_send_buf[i] = data[i];
	}	
	alt_irq_enable(PIO_C2_DR_IRQ);
	
	g_uart_usb1_control  |= ALTERA_AVALON_UART_CONTROL_TRDY_MSK;
	g_uart_usb1_control  |= ALTERA_AVALON_UART_STATUS_RRDY_MSK;
	IOWR_ALTERA_AVALON_UART_CONTROL(UART_USB_BASE, g_uart_usb1_control);
}

void send_eeprom_data()
{
	int i = 0;
	unsigned char usb_send[UART_SEND_BUF_LEN] = {0};
	memset(usb_send, 0, sizeof(usb_send));
	
	usb_send[0] = 0xff;
	usb_send[1] = 0xb0;

	for(i=0; i<FLASH_BUF_LEN; i++)
	{
		usb_send[i+2] = g_flash_rx_buf[i];
	}

	usb_send[g_comm_data_len-1] = get_crc(usb_send, g_comm_data_len-1);
	send_uart_usb1_data(usb_send, g_comm_data_len);
}

int init_uart()
{
	//TODO:: Add initial uart device code here
	IOWR(UART_USB_BASE, 4, (int)( CLKFREQ / g_uart_usb1_baudrate + 0.5));	//波特率设置
	g_uart_usb1_control |= ALTERA_AVALON_UART_CONTROL_RRDY_MSK |
	             				ALTERA_AVALON_UART_CONTROL_E_MSK;		//准备好读串口和出现错误时产生中断
	IOWR_ALTERA_AVALON_UART_CONTROL(UART_USB_BASE, g_uart_usb1_control );  
	alt_irq_register(UART_USB_IRQ, 0, uart_usb1_handle);
	return 0;
}

void decode_start_packet()
{
	int i = 0;
	unsigned char packet[UART_READ_BUF_LEN] = {0};
	
	alt_irq_context context;
	context =  alt_irq_disable_all ();
	for(i=0; i<g_comm_data_len; i++)
	{
		packet[i] = g_uart_usb1_read_buf[i];
	}
	alt_irq_enable_all(context);

	if((packet[0] == 0xff) && (packet[1] == 0xb0))
	{ 
		if(is_crc_good(packet, g_comm_data_len))
		{
			if((packet[2] == 0x1)&&(packet[3] == 0x2)&&(packet[4] == 0x3))
			{
				g_transfer_start = 1;
			}
			else if((packet[2] == 0x11)&&(packet[3] == 0x22)&&(packet[4] == 0x33))
			{
				g_transfer_start = 2;
			}
			else if((packet[2] == 0x10)&&(packet[3] == 0x20)&&(packet[4] == 0x30))
			{
				g_transfer_start = 3;
			}	
		}
	}
}

void decode_config_packet()
{
	int i = 0;
	unsigned char packet[UART_READ_BUF_LEN] = {0};
	
	alt_irq_context context;
	context =  alt_irq_disable_all ();
	for(i=0; i<g_comm_data_len; i++)
	{
		packet[i] = g_uart_usb1_read_buf[i];
	}
	alt_irq_enable_all(context);

	if((packet[0] == 0xff) && (packet[1] == 0xb0))
	{ 
		if(is_crc_good(packet, g_comm_data_len))
		{
			if((packet[2] == 0x4)&&(packet[3] == 0x5)&&(packet[4] == 0x6))
			{
				g_transfer_config = 1;
				g_transfer_config_frq = packet[5];
			}
			else if((packet[2] == 0x3)&&(packet[3] == 0x4)&&(packet[4] == 0x5))
			{
				g_transfer_config = 1;
				g_transfer_config_frq = 0x16;
			}
		}
	}
}


void decode_uart_packet_cf(unsigned char Mode)
{
	switch(Mode){
		case GET_PARAMETER:
		{
			unsigned char packet[UART_READ_BUF_LEN] = {0};
			int i;
			
			alt_irq_disable(UART_USB_IRQ);

			for(i=0; i<g_comm_data_len; i++)
			{
				packet[i] = g_uart_usb1_read_buf[i];
			}
			
			alt_irq_enable(UART_USB_IRQ);
			g_send_num = packet[5];
			g_send_frq_b= packet[6];
			g_send_frq_e= packet[7];
			g_is_get_send_num = 1;
		}break;
	}
}

void decode_uart_packet()
{
	volatile int i = 0;
	unsigned char packet[UART_READ_BUF_LEN] = {0};

	/**********************************************************************careful!!!***************************************************************************/
  	g_comm_data_len = 25;
	
	alt_irq_disable(UART_USB_IRQ);
	for(i=0; i<g_comm_data_len; i++)
	{
		packet[i] = g_uart_usb1_read_buf[i];
	}
	alt_irq_enable(UART_USB_IRQ);

	if((packet[0] == 0xff) && (packet[1] == 0xb0) )
	{ 
		if(packet[2] >= 0x20)
		{
			if(is_crc_good(packet, g_comm_data_len))
			{			
				for(i=1; i<FLASH_BUF_LEN; i++)
				{
					if(packet[i+2] != g_flash_rx_buf[i])
					{
						flash_set(0, packet + 2, FLASH_BUF_LEN);
						while(1)
						{
							led_on(1);		
							led_off(2);
							led_off(3);
							usleep(30000);
							led_off(1);		
							led_on(2);
							led_off(3);
							usleep(30000);
							led_off(1);		
							led_off(2);
							led_on(3);
							usleep(30000);
						}
					}
				}
			}
			else
			{
				note_err(CONFIG_DATA_CRC_ERROR);
			}
		}
		else
		{
			note_err(CONFIG_DATA_VERSION_ERROR);
		}
	}
	else
	{
        i = 0;
		for(i=0; i<g_comm_data_len; i++)
		{
			g_nRF2401_dev1p.buf.send_buf[i] = packet[i];
		}
		send_nRF2401_packet(&g_nRF2401_dev1p);
	}
}

int decode_nrf2401_packet_frq()
{
	unsigned char packet[UART_READ_BUF_LEN] = {0};
	int k = 0;
	if(g_nRF2401_dev2p.pac_get)
	{
		memcpy(packet, g_nRF2401_dev2p.buf.get_buf, g_comm_data_len);
		g_nRF2401_dev2p.pac_get = 0;

		if(packet[0] == 0xFF && packet[1] == 0xA7)
		{
			if((packet[2] == 0x99) && (packet[3] == 0x88) && (packet[4] == 0x77)) k = 1;
			else if((packet[2] == 0x66) && (packet[3] == 0x55) && (packet[4] == 0x44)) k = 2;
			else k = 0;
		}				
	}
	SetCE(1, g_send_2401_dev_p);  
	return k;
	
}


void uart_usb1_handle(void *context, alt_u32 interrupt)
{
  int status = 0;
  unsigned char data = 0;
  
  status = IORD_ALTERA_AVALON_UART_STATUS(UART_USB_BASE);

  /**********************************************************************careful!!!***************************************************************************/
  g_comm_data_len = 25;

  if((status & ALTERA_AVALON_UART_STATUS_E_MSK)
  	&&(g_uart_usb1_control & ALTERA_AVALON_UART_CONTROL_E_MSK))
  {
  	IOWR_ALTERA_AVALON_UART_STATUS(UART_USB_BASE, status & ~ALTERA_AVALON_UART_STATUS_E_MSK);	//清除标识
	note_err(UART_COMM_ERROR);//报错
	return;
  }
  
  if((status & ALTERA_AVALON_UART_STATUS_RRDY_MSK)
  	&&(g_uart_usb1_control  & ALTERA_AVALON_UART_CONTROL_RRDY_MSK))
  {
	if( read_uart_usb1_data( &data ) >= 0 )
	{    
		g_is_b2b_counter_start = 1;
		g_byte_to_byte_period = 0;
		g_uart_get_byte_num++;
		g_uart_usb1_read_buf[g_uart_usb1_read_buf_pos] = data;
		g_uart_usb1_read_buf_pos++;
		
		if(g_uart_usb1_read_buf_pos == g_comm_data_len)
		{
			g_is_uart_get_a_packet = 1;
			g_uart_get_packet_num++;
			g_is_b2b_counter_start = 0;
			g_uart_usb1_read_buf_pos = 0;
		}
		
		if(g_uart_usb1_read_buf_pos > g_comm_data_len)
		{
			g_uart_usb1_read_buf_pos = 0;
			g_is_b2b_counter_start = 0;
			note_err(USB_RECEIVE_PACKET_OVERFLOW);
		}
  	}
	IOWR_ALTERA_AVALON_UART_STATUS(UART_USB_BASE, status & ~ALTERA_AVALON_UART_STATUS_RRDY_MSK);
  }
  
  if((status & ALTERA_AVALON_UART_STATUS_TRDY_MSK)
  	&&(g_uart_usb1_control  & ALTERA_AVALON_UART_CONTROL_TRDY_MSK))
  {
    if(g_uart_usb1_send_buf_pos < g_uart_usb1_send_len ) 
    //if(g_uart_usb1_send_buf_pos < 6 ) 
    {
     		IOWR(UART_USB_BASE, 1, g_uart_usb1_send_buf[g_uart_usb1_send_buf_pos]);
		g_uart_usb1_send_buf_pos++;
		g_uart_send_byte_num++;
    }
    else  
    {
		g_uart_usb1_send_buf_pos = 0;
		g_uart_send_packet_num++;
		g_uart_usb1_control &= ~ALTERA_AVALON_UART_CONTROL_TRDY_MSK;
		g_uart_usb1_control |= ALTERA_AVALON_UART_STATUS_RRDY_MSK;
		IOWR_ALTERA_AVALON_UART_CONTROL(UART_USB_BASE, g_uart_usb1_control );
     }		

     IOWR_ALTERA_AVALON_UART_STATUS(UART_USB_BASE, status & ~ALTERA_AVALON_UART_STATUS_TRDY_MSK);
  }	
 /* if(g_is_uart_get_a_packet && start_normal)
        {
            decode_uart_packet();
            g_is_uart_get_a_packet = 0;
        }
  */
}


