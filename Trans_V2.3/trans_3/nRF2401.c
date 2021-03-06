#define NRF2401_C
#include "nRF2401.h"
#include <io.h>
#include "system.h"
#include "sys/alt_irq.h"
#include "unistd.h"
#include "misc.h"
#include "config.h"
#include "main.h"
//#include "alt_syscall.h"

volatile nRF2401_t g_nRF2401_dev1p, g_nRF2401_dev2p, g_nRF2401_tem;
volatile unsigned char g_comm_data_len = 0;
volatile unsigned char g_2401_frq = 0;
volatile unsigned char g_2401_addr_len = 0;
volatile unsigned char g_2401_rxtx = 0;		//0:发射，1:接收
volatile unsigned char g_2401_2_frq = 0;
volatile unsigned char g_2401_2_addr_len = 0;
volatile unsigned char g_2401_2_rxtx = 1;		//0:发射，1:接收

volatile unsigned char g_2401_addr[MAX_2401_ADDR_LEN] = {0};
volatile unsigned char g_2401_2_addr[MAX_2401_ADDR_LEN] = {0};
volatile unsigned char g_2401_send_addr[MAX_2401_ADDR_LEN] = {0};

volatile unsigned char g_is_2401_send_period = 0;
nRF2401_t *g_send_2401_dev_p = &g_nRF2401_dev1p;

extern unsigned char g_count_num[10];
extern char g_count_num_len;
extern unsigned char g_count_num2[10];
extern char g_count_num_len2;
extern unsigned char g_send_num;
volatile unsigned char g_2401_frq_TBC = 0;

void set_nrf2401_base()
{
	g_nRF2401_dev1p.ce_base = PIO_C1_CE_BASE;
	g_nRF2401_dev1p.cs_base = PIO_C1_CS_BASE;
	g_nRF2401_dev1p.clk_base = PIO_C1_CLK_BASE;
	g_nRF2401_dev1p.data_base = PIO_C1_DATA_BASE;
	g_nRF2401_dev1p.dr_base = PIO_C1_DR_BASE;
	g_nRF2401_dev1p.dr_irq= PIO_C1_DR_IRQ;
	g_nRF2401_dev1p.pac_get = 0;	

	g_nRF2401_dev2p.ce_base = PIO_C2_CE_BASE;
	g_nRF2401_dev2p.cs_base = PIO_C2_CS_BASE;
	g_nRF2401_dev2p.clk_base = PIO_C2_CLK_BASE;
	g_nRF2401_dev2p.data_base = PIO_C2_DATA_BASE;
	g_nRF2401_dev2p.dr_base = PIO_C2_DR_BASE;
	g_nRF2401_dev2p.dr_irq= PIO_C2_DR_IRQ;
	g_nRF2401_dev2p.pac_get = 0;	
}

void set_config_mode(nRF2401_t *dev)
{
	SetCE( 0, dev);
	SetCS( 1, dev);
	usleep(10);
}

void end_config_mode(nRF2401_t *dev)
{
	SetCS(0, dev);
	SetCE(1, dev);
	usleep(300);			//加了这里的延时与第一版一致，有用吗
}

void set_a_bit_to(char txrx, nRF2401_t *dev)  //耗时
{
	SetDATADir(1, dev);
	set_config_mode(dev);
	SetCLK( 0, dev );
	Set_DATA( txrx, dev);
	SetCLK( 1, dev);
	SetCLK( 0, dev);
	end_config_mode(dev);
}

/**********************************************************************************
函数名：void Tra_Rf_Write( unsigned char b )
输入：发送数据
输出：无
功能描述：向射频单元写数据//写一个字节
**********************************************************************************/
void Tra_Rf_Write( unsigned char b ,nRF2401_t *dev)
{
	unsigned char i;
	SetDATADir(1, dev);
	for( i = 0; i < 8; i++ )
	{
        	SetCLK( 0, dev);
		if( ( b & 0x80 ) == 0x00 )
			Set_DATA( 0, dev);
		else
			Set_DATA( 1, dev);
		b <<= 1;
		SetCLK( 1, dev);
	}
	SetCLK( 0, dev);
}

/**********************************************************************************
函数名：unsigned char Tra_Rf_Read(void)
输入：无
输出：接收数据
功能描述：从射频端口读数据，//读一个字节在IO中断里读，所以不用禁止中断。
**********************************************************************************/
unsigned char Tra_Rf_Read(nRF2401_t *dev)
{
	unsigned char b;
	unsigned char i;
	unsigned temp;

	SetDATADir(0, dev);
	b = 0;
	
	for( i = 0; i < 8; i++ )
	{	
    		b <<= 1;
		SetCLK(0, dev);
		SetCLK(1, dev);
		temp = GetDATA(dev);
		if( temp == 1 )
		b += 0x01;
    
	}
	SetCLK(0, dev);
	return b;
}

void delay_400ns()
{
	int i = 0;
	for(i=0; i<5; i++)
	{
		asm("nop");
	}
}

void SetCE(unsigned char val, nRF2401_t *dev)
{
  	IOWR(dev->ce_base, 0, val);
	delay_400ns();
}

void SetCS(unsigned char val, nRF2401_t *dev)
{
  	IOWR(dev->cs_base, 0, val);
	delay_400ns();
}

void SetCLK(unsigned char val, nRF2401_t *dev)
{	
	IOWR(dev->clk_base, 0, val);
	delay_400ns();
}

void SetDATADir(unsigned char val, nRF2401_t *dev)  // 0 for input , 1 for output
{
	IOWR(dev->data_base, 1, val);	
}

void Set_DATA(unsigned char val, nRF2401_t *dev)
{
	IOWR(dev->data_base, 0, val);
	delay_400ns();
}

unsigned char GetDATA(nRF2401_t *dev)
{
  unsigned char temp = 0;
  temp = IORD(dev->data_base, 0);
  temp = temp & 0x1;
  if ( temp == 0 ) return 0;
  else return 1; 
}

unsigned char GetDR(nRF2401_t *dev)
{
  unsigned int temp = 0;
  temp = IORD(dev->dr_base,0);
  temp = temp & 0x1;
  if ( temp == 0 ) return 0;
  else return 1; 
}

void send_nrf2401_config_data(nRF2401_t *dev)
{
	int i = 0;
	alt_irq_context context;
	context =  alt_irq_disable_all ();
	set_config_mode(dev);
	for(i=0; i<NRF2401_CONFIG_DATA_LEN; i++)
	{
		Tra_Rf_Write(dev->RFconf[i], dev);
	}
	end_config_mode(dev);
	alt_irq_enable_all(context);
}

void init_nrf2401_dr(nRF2401_t *dev)
{
	IOWR(dev->dr_base, 2, 0x1);
    	IOWR(dev->dr_base, 3, 0x00);
	alt_irq_register(dev->dr_irq, dev, (alt_isr_func)get_nRF2401_packet);
}

void init_nrf2401()
{
	set_nrf2401_base();
	//*****************************************************************************************careful!!****************************************************************/
	//g_2401_frq = DEFAULT_FREQ;
	set_nrf2401_config_data(&g_nRF2401_dev1p, g_2401_addr_len * 8, g_comm_data_len * 8,
			g_2401_addr, g_2401_rxtx, g_2401_frq);	
	//*****************************************************************************************careful!!***************************************************************/
	//g_2401_2_frq = DEFAULT_FREQ;
	set_nrf2401_config_data(&g_nRF2401_dev2p, g_2401_2_addr_len * 8, g_comm_data_len * 8,
			g_2401_2_addr, g_2401_2_rxtx, g_2401_2_frq);	
	
	init_nrf2401_dr(&g_nRF2401_dev2p);
}

int set_nrf2401_config_data(nRF2401_t *dev, unsigned char addr_len, unsigned char data_len, unsigned char *addr, unsigned char rxtx, unsigned char freq)
{
	//TODO :: Add initial nRF2401 device code here
	#ifdef SELF_CHECK
	if(((rxtx>1) || (freq>15))
	{
		note_err(NRF2401_CONFIG_DATA_OVERFLOW);
	}
	#endif
	
	dev->RFconf[0] = 0;		//通道2数据长度
	dev->RFconf[1] = data_len;		//通道1数据长度0-208(bit)
	dev->RFconf[2] = 0;
	dev->RFconf[3] = 0;
	dev->RFconf[4] = 0;
	dev->RFconf[5] = 0;
	dev->RFconf[6] = 0;

	dev->RFconf[7] = *addr;
	dev->RFconf[8] = *(addr + 1);
	dev->RFconf[9] = *(addr + 2);
	dev->RFconf[10] = *(addr + 3);
	dev->RFconf[11] = *(addr + 4);
				
	dev->RFconf[12] = (addr_len << 2) + (CRC_16<<1) + CRC_ENABLE;
	dev->RFconf[13] = (RX2_DISABLE<<7) + (SHOCKBURST_MODE<<6)+(RF_DATA_RATE_250K<<5) + (XO_F_16<<2) + (RF_PWR_0);
	//dev->RFconf[14] = (freq<<3) +rxtx;
/*	if(freq<=7)//change this,if freg>=8,add some data on it.
		freq= (freq<<2);
	else
		freq=(freq<<2)+58;*/

	////////////////////ENABLE_9557_SET///////////////////////
	#ifdef ENABLE_9557_SET
	switch(freq){
		case 0:
			freq = 116;
			break;
		case 1:
			freq = 30;
			break;
		case 2:
			freq = 81;
			break;
		case 3:
			freq = 89;
			break;
		case 4:
			freq = 99;
			break;
		case 5:
			freq = 101;
			break;
		case 6:
			freq = 109;
			break;
		case 7:
			freq = 77;
			break;
		case 8:
			freq = 117;
			break;
		case 9:
			freq = 121;
			break;
		case 10:
			freq = 85;
			break;
		case 11:
			freq = 35;
			break;
		case 12:
			freq = 76;
			break;
		case 13:
			freq = 97;
			break;
		case 14:
			freq = 106;
			break;
		case 15:
			freq = 135;
			break;
		default:
			freq = 85;
			break;
       }
		#endif
	///////////////////////////////////////////////////	

	dev->RFconf[14] = (freq<<1) +rxtx;//change this,if freg>=8,add some data on it.
	
  	 send_nrf2401_config_data(dev);

	return 0;
}

int get_nRF2401_packet(nRF2401_t *dev, alt_u32 interrupt)
{
	//TODO :: Add get a packet from nRF2401 device code here 
	IOWR(dev->dr_base, 3, 0x00);
	dev->buf.get_buf_pos=0;
	while ( GetDR(dev) )
	{ 
		dev->buf.get_buf[dev->buf.get_buf_pos] = Tra_Rf_Read(dev);
		dev->buf.get_buf_pos++;
		if (dev->buf.get_buf_pos > NRF2401_BUF_DATA_LEN)  //Though buffer is full, we MUST read the rest data 
		{
			dev->packet_error++;
			while ( GetDR(dev))
			{
				Tra_Rf_Read(dev);
			}
			return -1;
		}
	}
	if(dev->buf.get_buf_pos>0) 
	{
		g_2401_get_packet_num++;
		dev->pac_get = 1;
		return 1;
	}
	else  
	{
		note_err(NRF2401_GET_NO_DATA_ERROR);
		return 0;
	}
}

int send_nRF2401_packet(nRF2401_t *dev)
{
	//TODO :: Add send a packet to nRF2401 device code here
	unsigned char k;
	//alt_irq_disable(PIO_C2_DR_IRQ);
	//set_a_bit_to(NRF2401_TX, dev);
	for(k=0; k<g_2401_addr_len; k++)
	{
		Tra_Rf_Write(*(g_2401_send_addr + k), dev);
	}
	
	for( k = 0; k < g_comm_data_len; k++ )
	{
		Tra_Rf_Write( dev->buf.send_buf[k], dev);
	}
	SetCE(0, dev);
	g_2401_send_packet_num++;
	usleep(2000);			//延时2000us，等待2401发送。等太久了，改成置标志位，定时器去处理。
	g_is_2401_send_period = 1;
	g_send_2401_dev_p = dev;

	//set_a_bit_to(NRF2401_RX, dev);
	
	return k;
}

void send_nrf2401_packet_cf(unsigned char Mode)
{

	g_nRF2401_dev1p.buf.send_buf[0]=0xFF;
	g_nRF2401_dev1p.buf.send_buf[1]=0xCF;	
	
	switch(Mode){
		
		case START_TESTING:

			g_nRF2401_dev1p.buf.send_buf[2]=0x0A;
			g_nRF2401_dev1p.buf.send_buf[3]=0x0B;
			g_nRF2401_dev1p.buf.send_buf[4]=0x0C;
			g_nRF2401_dev1p.buf.send_buf[5]=g_2401_frq_TBC;
			break;
			
		case TESTING1:
		
			g_nRF2401_dev1p.buf.send_buf[2]=0xBB;
			g_nRF2401_dev1p.buf.send_buf[3]=0xBB;
			g_nRF2401_dev1p.buf.send_buf[4]=0xBB;
			g_nRF2401_dev1p.buf.send_buf[5]=g_send_num;
			break;

		case TESTING2:

			g_nRF2401_dev1p.buf.send_buf[2]=0xAA;
			g_nRF2401_dev1p.buf.send_buf[3]=0xAA;
			g_nRF2401_dev1p.buf.send_buf[4]=0xAA;
			g_nRF2401_dev1p.buf.send_buf[5]=g_send_num;
			break;
			
		case GET_TEST_RESULT:
		
			g_nRF2401_dev1p.buf.send_buf[2]=0x0D;
			g_nRF2401_dev1p.buf.send_buf[3]=0x0E;
			g_nRF2401_dev1p.buf.send_buf[4]=0x0F;
			g_nRF2401_dev1p.buf.send_buf[5]=0x00;
			break;
			
		case ENDING:
		
			g_nRF2401_dev1p.buf.send_buf[2]=0xFF;
			g_nRF2401_dev1p.buf.send_buf[3]=0xFF;
			g_nRF2401_dev1p.buf.send_buf[4]=0xFF;
			g_nRF2401_dev1p.buf.send_buf[5]=0x00;
			break;

		case CF_RESET:

			g_nRF2401_dev1p.buf.send_buf[2]=0x0A;
			g_nRF2401_dev1p.buf.send_buf[3]=0x0B;
			g_nRF2401_dev1p.buf.send_buf[4]=0x0C;
			g_nRF2401_dev1p.buf.send_buf[5]=CF_DEFAULT_FRQ;
			break;
			
	}
	
	memset(&g_nRF2401_dev1p.buf.send_buf[6], 0, sizeof(unsigned char) * (NRF2401_BUF_DATA_LEN - 6));
	send_nRF2401_packet(&g_nRF2401_dev1p);	
}
unsigned char decode_nrf2401_packet_cf(unsigned char Mode)
{
	unsigned char packet[UART_READ_BUF_LEN] = {0};
	int i;
	unsigned char retflg=0;
	g_count_num_len = 0;
	g_count_num_len2 = 0;
	if(g_nRF2401_dev2p.pac_get)
	{
		memcpy(packet, g_nRF2401_dev2p.buf.get_buf, g_comm_data_len);
		g_nRF2401_dev2p.pac_get = 0;

		if(packet[0] == 0xFF && packet[1] == 0xCF)
		{
			switch(Mode){
				case START_TESTING:
				case CF_RESET:
					if(packet[2] == 0xAA && packet[3] == 0xAA && packet[3] == 0xAA)
						retflg = 1;
					break;
				case GET_TEST_RESULT:
					i = 2;
					memset(g_count_num, 0, sizeof(g_count_num));
					memset(g_count_num2,0, sizeof(g_count_num2));
					while(packet[i] != 0xDD && packet[i] != 0xa)
					{
						g_count_num[i-2]=packet[i];
						i++;
					}
					g_count_num_len = i-2;
					i = 3 + g_count_num_len;
					while(packet[i] != 0xEE && packet[i] !=0xa)
					{
						g_count_num2[i-3-g_count_num_len] = packet[i];
						i++;
					}
					g_count_num_len2 = i - 3 - g_count_num_len;
                    if(packet[i] == 0xEE) retflg = 1;
					break;
			}
		}				
	}
	SetCE(1, g_send_2401_dev_p);  
	if(retflg == 1)return 1;
	return 0;
}

