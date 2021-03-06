#define MAIN_C
#include "system.h"
#include "uart.h"
#include "misc.h"
#include "sys/alt_irq.h"
#include "nRF2401.h"
#include <altera_avalon_pio_regs.h>
#include <io.h>
#include "flash.h"
#include "main.h"
#include "config.h"
#include "timer.h"
#include "nRF2401.h"
#include "Pca9557.h"




unsigned volatile char g_byte_to_byte_period = 0;
unsigned volatile char g_flash_rx_buf[FLASH_BUF_LEN] = {0};
unsigned volatile long g_uart_get_packet_num = 0;
unsigned volatile long g_uart_send_packet_num = 0;
unsigned volatile long g_2401_get_packet_num = 0;
unsigned volatile long g_2401_send_packet_num = 0;
unsigned volatile long g_uart_get_byte_num = 0;
unsigned volatile long g_uart_send_byte_num = 0;

unsigned char g_send_num;
unsigned char g_send_frq_b;
unsigned char g_send_frq_e;

unsigned char g_count_num[10];
unsigned char g_count_num_len;
unsigned char g_count_num2[10];
unsigned char g_count_num_len2;


extern char g_is_get_send_num;
extern unsigned char g_2401_frq_TBC;
extern char g_frq_cheak_send_flag;
extern char timer_50ms_flag;
extern int pca9557_frq;
extern char pca9557_frq_set_flag;



//unsigned volatile long start_normal = 0;

  
int main()
{
	alt_irq_context context;
	//context =  alt_irq_disable_all ();

	init_config_data();

	initialize(1);
	//alt_irq_enable_all(context);


	while(!g_transfer_start)		//等待上位机的开始信号
	{
	    led_in_turn();
		IOWR(TIMER_WATCHDOG_BASE, 2, 0);
		if(g_is_uart_get_a_packet)
		{
			decode_start_packet();
			g_is_uart_get_a_packet = 0;
		}
	}
	
	context =  alt_irq_disable_all ();
	init_eeprom();
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	flash_get(0, g_flash_rx_buf, FLASH_BUF_LEN);
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	alt_irq_enable_all(context);
	if(g_transfer_start == 1) send_eeprom_data();
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	
	if(g_transfer_start == 1){
		
		while(!g_transfer_config)
		{
			led_flash();
			IOWR(TIMER_WATCHDOG_BASE, 2, 0);
			if(g_is_uart_get_a_packet)
			{
				decode_config_packet();
				g_is_uart_get_a_packet = 0;
			}		
		}

		//if(g_transfer_config == 1)
		{
			set_config_data();
			alt_irq_context context;
			context =  alt_irq_disable_all ();
			initialize(2);
			alt_irq_enable_all(context);
			IOWR(TIMER_WATCHDOG_BASE, 2, 0);
			usleep(1000);
	        
		}
		
		while(1)
		{
			if(g_is_uart_get_a_packet)
			{
				decode_uart_packet();
				g_is_uart_get_a_packet = 0;
			}
            IOWR(TIMER_WATCHDOG_BASE, 2, 0);
            
			if(g_nRF2401_dev2p.pac_get)
			{	
				send_uart_usb1_data(g_nRF2401_dev2p.buf.get_buf, g_comm_data_len);
				g_nRF2401_dev2p.pac_get = 0;
			}
            IOWR(TIMER_WATCHDOG_BASE, 2, 0);
            
			if(1)//(g_2401_send_finish)
			{
				SetCE(1, g_send_2401_dev_p);
				//alt_irq_enable(PIO_C2_DR_IRQ);
				g_2401_send_finish = 0;
			}
            IOWR(TIMER_WATCHDOG_BASE, 2, 0);
            
			if(g_sys_time & 0x1)
			{
				led_on(1);
			}
			else
			{
				led_off(1);
			}

			if(g_uart_get_packet_num & 0x40)
			{
				led_on(2);
			}
			else
			{
				led_off(2);
			}

			if(g_2401_get_packet_num & 0x40)
			{
				led_on(3);
			}
			else
			{
				led_off(3);
			}
			
			IOWR(TIMER_WATCHDOG_BASE, 2, 0);
		}
	}
	else if(g_transfer_start == 2){
		
		while(1)
		{
			alt_irq_context context;
			unsigned char mes1[]="\nPlease input the number to send(plus 100) <5> & the range of frq <6/7> \n";
			unsigned char mes2[]="\n--------------- E N D ------------\n";
			unsigned char i;
				
			led_flash();
			IOWR(TIMER_WATCHDOG_BASE, 2, 0);
			led_flash();
			IOWR(TIMER_WATCHDOG_BASE, 2, 0);
			
			g_2401_frq = CF_DEFAULT_FRQ;
			g_2401_2_frq = CF_DEFAULT_FRQ;

			context =  alt_irq_disable_all ();
			initialize(2);
			alt_irq_enable_all(context);
			IOWR(TIMER_WATCHDOG_BASE, 2, 0);
			usleep(1000);

			send_uart_usb1_data(mes1,sizeof(mes1));

			g_is_get_send_num=0;
			
			while(!g_is_get_send_num)
			{
				IOWR(TIMER_WATCHDOG_BASE, 2, 0);
				if(g_is_uart_get_a_packet)
				{
					decode_uart_packet_cf(GET_PARAMETER);
					g_is_uart_get_a_packet = 0;
				}		
			}


			//g_send_frq = 6;
			for(i=g_send_frq_b;i<=g_send_frq_e;i++)
				if(frq_check(i)) frq_check(i);
				
			cf_reset_robot();

			send_uart_usb1_data(mes2,sizeof(mes2));
		}

	}
	else if(g_transfer_start == 3){
		
		while(!g_transfer_config)
		{
			led_flash();
			IOWR(TIMER_WATCHDOG_BASE, 2, 0);
			if(g_is_uart_get_a_packet)
			{
				decode_config_packet();
				g_is_uart_get_a_packet = 0;
			}		
		}

		//if(g_transfer_config == 1)
		{
			set_config_data();
			alt_irq_context context;
			context =  alt_irq_disable_all ();
			initialize(2);
			alt_irq_enable_all(context);
			IOWR(TIMER_WATCHDOG_BASE, 2, 0);
			usleep(1000);
			     
		}
		
		while(1)
		{
			/*if(g_is_uart_get_a_packet)
			{
				decode_uart_packet();
				g_is_uart_get_a_packet = 0;
			}
            IOWR(TIMER_WATCHDOG_BASE, 2, 0);*/
            
			if(g_nRF2401_dev2p.pac_get)
			{	
				send_uart_usb1_data(g_nRF2401_dev2p.buf.get_buf, g_comm_data_len);
                if(check_comm_test(g_nRF2401_dev2p.buf.get_buf, g_comm_data_len))
					do_comm_test(g_nRF2401_dev2p.buf.get_buf, g_comm_data_len);
					
				g_nRF2401_dev2p.pac_get = 0;
			}
            IOWR(TIMER_WATCHDOG_BASE, 2, 0);
            
			if(1)//(g_2401_send_finish)
			{
				SetCE(1, g_send_2401_dev_p);
				//alt_irq_enable(PIO_C2_DR_IRQ);
				g_2401_send_finish = 0;
			}
            IOWR(TIMER_WATCHDOG_BASE, 2, 0);
            
			if(g_sys_time & 0x1)
			{
				led_on(1);
			}
			else
			{
				led_off(1);
			}

			/*if(g_uart_get_packet_num & 0x40)
			{
				led_on(2);
			}
			else
			{
				led_off(2);
			}*/

			if(g_2401_get_packet_num & 0x40)
			{
				led_on(3);
			}
			else
			{
				led_off(3);
			}
			
			IOWR(TIMER_WATCHDOG_BASE, 2, 0);
		}
	}
  return 0;
}

int frq_check(unsigned char frq)
{
	unsigned char mes1[]="\nStart testing for frq - 0 \n";
	unsigned char mes2[]="\n    Finish initialization! Wait for testing!\n";
	unsigned char mes3[]="\n    The result is as follow:\n\n    Send: ";
	unsigned char mes4[]="000    \n    send_A: ";
	unsigned char mes4_2[]="    Robot_Get_A: ";
	unsigned char mes4_3[]="\n    send_B: ";
	unsigned char mes4_4[]="    Robot_Get_B: ";
	unsigned char mes5[]="    Transfer_Get: ";

	unsigned char mes6[]="\n    Recieve_Lose_A(every 100 packet):";
	unsigned char mes7[]="<1\n00";
	unsigned char mes8[]="\n    Recieve_Lose_B(every 100 packet):";
	unsigned char mes9[]="<1\n00";
	unsigned char mes8_2[]="    Return_Lose(every 100 packet):";
	unsigned char mes9_2[]="<1\n00";
    unsigned char meserr1[]="Error: No recieved packet1!\n";
	unsigned char meserr2[]="Error: No recieved packet2! Try again!\n";
	unsigned char meserr3[]="Error: Change frq failed or No robot respond!\n";
	unsigned char meserr4[]="Error: No result recieved!\n";
	unsigned char ch0= '0';
	int i;
	int n;
	int tempn;
	int result_len=0;
	int result_len2=0;
	int result_len3=0;
	int send_count=0;
	int deadtime = 0;
	int trytime = 0;
	unsigned char packet[UART_READ_BUF_LEN] = {0};
	unsigned char frq_counter_num[10];
	unsigned char frq_counter_num2[10];
	unsigned char send_num1[10];
	unsigned char send_num2[10];
	int recieve_frq_counter1 = 0;
	int recieve_frq_counter2 = 0;
	int send_num_counter1 = 0;
	int send_num_counter2 = 0;
	int p;
	int p2;
	g_2401_frq_TBC = frq;

	if(frq < 10)
		mes1[25] = mes1[25] + frq;
	else
		mes1[25] = mes1[25] + 'A' - '0' + frq - 10;

	send_uart_usb1_data(mes1,sizeof(mes1));

	IOWR(TIMER_WATCHDOG_BASE, 2, 0);

	deadtime = 50;
	do{
        deadtime--;
        usleep(14000);
        IOWR(TIMER_WATCHDOG_BASE, 2, 0);
		send_nrf2401_packet_cf(START_TESTING);
	}while(!decode_nrf2401_packet_cf(START_TESTING) && deadtime > 0);

    if(deadtime == 0){send_uart_usb1_data(meserr1,sizeof(meserr1));usleep(20000);}//return 1;}

	g_2401_frq = g_2401_frq_TBC;
	g_2401_2_frq = g_2401_frq_TBC;

	trytime = 5;
	do{
		initialize(2);
		usleep(1000);
		
		IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	    
		deadtime = 20;
		do{
	        deadtime--;
	        usleep(14000);
			IOWR(TIMER_WATCHDOG_BASE, 2, 0);
			send_nrf2401_packet_cf(START_TESTING);
		}while(!decode_nrf2401_packet_cf(START_TESTING) && deadtime > 0);

		trytime--;
		
		if(deadtime == 0){send_uart_usb1_data(meserr2,sizeof(meserr2));usleep(20000);}//return 1;}
		else trytime = -1;
	}while(trytime > 0);

    if(trytime == 0){send_uart_usb1_data(meserr3,sizeof(meserr3));usleep(20000);return 1;}
	
	send_uart_usb1_data(mes2,sizeof(mes2));
	send_count=0;
	i=0;
	recieve_frq_counter1 = 0;
	p2=0;
	send_num_counter1 = 0;
	send_num_counter2 = 0;
	while(1)
	{
		if(g_frq_cheak_send_flag)
		{	
			if(i>=100*g_send_num) break;
			else i++;
			if(p2 == 0)		
			{
				p2 = i % FRQ_CHECK_ABRATE;
				if(p2 != 0)		
				{
					send_nrf2401_packet_cf(TESTING1);
					send_num_counter1++;
					p2 = 0;
				}
				else	
				{
					send_nrf2401_packet_cf(TESTING2);
					p2 = 4;
					send_num_counter2++;
				}
			}
			else 
			{
				send_nrf2401_packet_cf(TESTING2);
				p2--;
				send_num_counter2++;
			}
			
			SetCE(1, g_send_2401_dev_p);  
			IOWR(TIMER_WATCHDOG_BASE, 2, 0);
			g_frq_cheak_send_flag = 0;
			
			
			
			send_count++;
			if(send_count<15) led_on(2);
			else if(send_count<30) led_off(2);
			else send_count=0;
		}
		if(g_nRF2401_dev2p.pac_get)
		{	
			p = decode_nrf2401_packet_frq();
			if(p == 1)		recieve_frq_counter1++;

			g_nRF2401_dev2p.pac_get = 0;
		}
		IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	}
	timer_50ms_flag = 1;
	while(timer_50ms_flag)
	{
		if(g_nRF2401_dev2p.pac_get)
		{
			p = decode_nrf2401_packet_frq();
			if(p == 1)		recieve_frq_counter1++;

			g_nRF2401_dev2p.pac_get = 0;
		}
		IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	}	
	deadtime = 100;
	
	do{
		deadtime--;
		usleep(14000);
		IOWR(TIMER_WATCHDOG_BASE, 2, 0);
		send_nrf2401_packet_cf(GET_TEST_RESULT);
		

	}while(!decode_nrf2401_packet_cf(GET_TEST_RESULT) && deadtime > 0);

    if(deadtime == 0){send_uart_usb1_data(meserr4,sizeof(meserr4));usleep(20000);
        return 1;}

	send_nrf2401_packet_cf(ENDING);
	SetCE(1, g_send_2401_dev_p);  

	int num_frq = 0;
	int num_frq2 = 0;
	int num_send1 = 0;
	int num_send2 = 0;
	unsigned temfrq = '0';
	unsigned temfrq2 = '0';
	
	memset(frq_counter_num,0,sizeof(frq_counter_num));
	memset(frq_counter_num2,0,sizeof(frq_counter_num2));
	memset(send_num1,0,sizeof(send_num1));
	memset(send_num2,0,sizeof(send_num2));
	num_frq = num_change_to_char(recieve_frq_counter1,frq_counter_num);
	num_send1 = num_change_to_char(send_num_counter1,send_num1);
	num_send2 = num_change_to_char(send_num_counter2,send_num2);
	
	char_ary_reverse(num_frq,frq_counter_num);
	char_ary_reverse(num_send1,send_num1);
	char_ary_reverse(num_send2,send_num2);
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	
{	
	char_ary_reverse(g_count_num_len,g_count_num);
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	char_ary_reverse(g_count_num_len2,g_count_num2);
	
}
	//g_count_num[0]=g_count_num[1]=g_count_num[2]=9;
	//g_count_num[3]='\0';
	//g_count_num_len=3;
	//g_send_num=1;
	
	if(g_send_num < 10)
		mes4[0] = ch0+g_send_num;
	else{
		mes4[0] = ch0+g_send_num/10;
		mes4[1] = ch0+g_send_num%10;
		mes4[3] = ch0;
	}
	n = 0;
	for(i=0;i<g_count_num_len2;i++)		n = n*10+g_count_num2[i];
	for(i=0;i<num_frq;i++)		frq_counter_num[i]=frq_counter_num[i]-ch0;
	result_len = calculate_packet_loss_rate(mes7,g_count_num,g_count_num_len,send_num_counter1);
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	result_len2 = calculate_packet_loss_rate(mes9,g_count_num2,g_count_num_len2,send_num_counter2);
	result_len3 = calculate_packet_loss_rate(mes9_2,frq_counter_num,num_frq,n);
	/*n = 0;
	for(i=0;i<g_count_num_len2;i++){
		n = n*10+g_count_num2[i];
		g_count_num2[i]=g_count_num2[i]+ch0;
	}
	n =(send_num_counter2-n)/send_num_counter2*100;

	if(n > 0)
	{
		tempn=n;
		i=0;
		while(tempn!=0)
		{
			tempn=tempn/10;
			i++;
		}

		mes9[i]='\n';
		mes9[i+1]='\0';
		result_len2=i+2;
		while(i!=0)
		{
			mes9[i-1]=n%10+ch0;
			n=n/10;
			i--;
		}
	}
	else
	{
		result_len2 = 4;
		mes9[3]='\0';
	}
	*/
	
	send_uart_usb1_data(mes3,sizeof(mes3));
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(300000);
	send_uart_usb1_data(mes4,sizeof(mes4));
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(100000);
	send_uart_usb1_data(send_num1,sizeof(send_num1));
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(100000);
	send_uart_usb1_data(mes4_2,sizeof(mes4_2));
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(100000);
	send_uart_usb1_data(g_count_num,sizeof(g_count_num));
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(100000);
	send_uart_usb1_data(mes6,sizeof(mes6));
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(300000);	
	send_uart_usb1_data(mes7,result_len);
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(100000);
	
	send_uart_usb1_data(mes4_3,sizeof(mes4_3));
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(100000);
	send_uart_usb1_data(send_num2,sizeof(send_num2));
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(100000);
	send_uart_usb1_data(mes4_4,sizeof(mes4_4));
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(100000);
	send_uart_usb1_data(g_count_num2,sizeof(g_count_num2));
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(100000);
	send_uart_usb1_data(mes5,sizeof(mes5));
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(300000);
	send_uart_usb1_data(frq_counter_num,num_frq);
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(100000);
	send_uart_usb1_data(mes8,sizeof(mes8));
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(300000);	
	send_uart_usb1_data(mes9,result_len2);
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(100000);
	send_uart_usb1_data(mes8_2,sizeof(mes8_2));
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(300000);	
	send_uart_usb1_data(mes9_2,result_len3);
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(100000);
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);

	return 0;
}

void cf_reset_robot()
{
    int deadtime = 0;
    
	unsigned char meswarn[]="\nWarning: The robot's frq may not be reset!\n";

	deadtime = 50;
	do{
        deadtime--;
        usleep(14000);
        IOWR(TIMER_WATCHDOG_BASE, 2, 0);
		send_nrf2401_packet_cf(CF_RESET);
	}while(!decode_nrf2401_packet_cf(CF_RESET) && deadtime > 0);

    if(deadtime == 0){send_uart_usb1_data(meswarn,sizeof(meswarn));usleep(20000);}
    
    send_nrf2401_packet_cf(ENDING);
	SetCE(1, g_send_2401_dev_p); 
}


void initialize(int flag)
{
	if(flag == 1)
	{
		init_uart();
		init_timer();	
		init_led();
		init_pca9557();
	}
	else
	{
		init_nrf2401();
	}
}

//默认数据包长25字节，波特率115200，								
//1号2401发射，5字节地址,接收方地址为10，71， 45， 98， 00
//2号2401接收，5字节地址，为10，71， 45， 98， 00
void init_config_data()
{
	int i = 0;
	
	g_uart_usb1_baudrate = 115200;
	g_comm_data_len = 25;
	g_2401_frq = DEFAULT_FREQ;
	g_2401_addr_len = 5;	
	g_2401_rxtx = 0;

	g_2401_2_frq = DEFAULT_FREQ;
	g_2401_2_addr_len = 5;	
	g_2401_2_rxtx = 1;	

	for(i=0; i<MAX_2401_ADDR_LEN; i++)	//1号2401的地址位0x0-0x4，因为一直设定为发射，所以用不到。
	{
		g_2401_addr[i] = i;
	}


	g_2401_2_addr[0] = 0x10+0x11;
	g_2401_2_addr[1] = 0x71+0x11;
	g_2401_2_addr[2] = 0x45+0x11;
	g_2401_2_addr[3] = 0x98+0x11;
	g_2401_2_addr[4] = 0x00+0x11;


	g_2401_send_addr[0] = 0x10;//0x10;
	g_2401_send_addr[1] = 0x71;
	g_2401_send_addr[2] = 0x45;
	g_2401_send_addr[3] = 0x98;
	g_2401_send_addr[4] = 0x00;//0x00;
	
	
}

void set_config_data()
{
	int i = 0;
	
	//flash_get(0, g_flash_rx_buf, FLASH_BUF_LEN);
	
	switch(g_flash_rx_buf[1] & 0x07)
    {
		case 0:  g_uart_usb1_baudrate = 1200;	break;
		case 1:	g_uart_usb1_baudrate = 2400;	break;
		case 2:	g_uart_usb1_baudrate = 4800;	break;
		case 3:	g_uart_usb1_baudrate = 9600;	break;
		case 4:	g_uart_usb1_baudrate = 19200;	break;
		case 5:	g_uart_usb1_baudrate = 38400;	break;
		case 6:	g_uart_usb1_baudrate = 57600;	break;
		case 7:	g_uart_usb1_baudrate = 115200;	break;
		default: g_uart_usb1_baudrate = 115200;	break;
	}

	g_comm_data_len = (g_flash_rx_buf[1]  >> 3) & 0x1f;
	
	if(g_transfer_config_frq <= 0x1F && g_transfer_config_frq >= 0x10)
		g_2401_frq = g_transfer_config_frq & 0x0f;
	else
		g_2401_frq = g_flash_rx_buf[2] & 0x0f;
	
	g_2401_addr_len = (g_flash_rx_buf[2] >> 4) & 0x7;	
	g_2401_rxtx = (g_flash_rx_buf[2] >> 7) & 0x1;

	if(g_transfer_config_frq <= 0x1F && g_transfer_config_frq >= 0x10)
		g_2401_2_frq = g_transfer_config_frq & 0x0f;
	else
		g_2401_2_frq = g_flash_rx_buf[3] & 0x0f;

	g_2401_2_addr_len = (g_flash_rx_buf[3] >> 4) & 0x7;	
	g_2401_2_rxtx = (g_flash_rx_buf[3] >> 7) & 0x1;

	if (pca9557_frq_set_flag == 1)
	{
		g_2401_frq = pca9557_frq;
		g_2401_2_frq = pca9557_frq;
	}

	for(i=0; i<MAX_2401_ADDR_LEN; i++)	//1号2401的地址位0x0-0x4，因为一直设定为发射，所以用不到。
	{
		g_2401_addr[i] = i;
	}
	
	for(i=0; i<MAX_2401_ADDR_LEN; i++)
	{
		g_2401_2_addr[i] = g_flash_rx_buf[4+i];
	}
	
	for(i=0; i<g_2401_addr_len; i++)
	{
		g_2401_send_addr[i] = g_flash_rx_buf[9 + MAX_2401_ADDR_LEN - g_2401_addr_len + i];
	}
}

int num_change_to_char(int num,unsigned char * num_char)
{
	
	int num_len;
	num_len = 0;
	while(num != 0)
	{
		num_char[num_len] = num % 10 + 48;
		num = num / 10;
		num_len++;
	}
	return num_len;
}

void char_ary_reverse(int num_len,unsigned char * num_char)
{
	unsigned tempfrq = '0';
	int i = 0 ;
	for(i = 0;i<(num_len)/2;i++)
	{
		tempfrq = num_char[i];
		num_char[i] = num_char[num_len-i-1];
		num_char[num_len-i-1] = tempfrq;
	}
}
int calculate_packet_loss_rate(unsigned char * mes,unsigned char * num_char,int num_len,int send_num)
{
	int i = 0;
	int n;
	int tempn;
	int result_len;
	unsigned char ch0 = '0';
	n = 0;
	for(i=0;i<num_len;i++){
		n = n*10+num_char[i];
		num_char[i]=num_char[i]+ch0;
	}
	n =(send_num-n)*100/send_num;
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);

	if(n > 0)
	{
		tempn=n;
		i=0;
		while(tempn!=0)
		{
			tempn=tempn/10;
			i++;
		}

		mes[i]='\n';
		mes[i+1]='\0';
		result_len=i+2;
		while(i!=0)
		{
			mes[i-1]=n%10+ch0;
			n=n/10;
			i--;
		}
	}
	else
	{
		result_len = 4;
		mes[3]='\0';
	}
	return result_len;
}


int check_comm_test(unsigned char *packet, int len){
	if(packet[0] == 0xFF && packet[1] == 0x04 && len == 25)
		return 1;
	else 
		return 0;
}

void do_comm_test(unsigned char *packet, int len){
	unsigned char num;
	num = packet[2];
    usleep(30000);
	g_nRF2401_dev1p.buf.send_buf[0] = 0xFF;
	
	if(num<=8){
		g_nRF2401_dev1p.buf.send_buf[1] = 0x40;
		g_nRF2401_dev1p.buf.send_buf[2] = 1<<(num-1);
		}
	else{
		g_nRF2401_dev1p.buf.send_buf[1] = 0x40 | (1<<(num-9));
		g_nRF2401_dev1p.buf.send_buf[2] = 0;
		}
	
	switch(packet[3]){
		case 0x80:			//run
			g_nRF2401_dev1p.buf.send_buf[3] = 0;
			g_nRF2401_dev1p.buf.send_buf[4] = 0x10;
			g_nRF2401_dev1p.buf.send_buf[5] = 0;
			g_nRF2401_dev1p.buf.send_buf[6] = 0;
			memset(&g_nRF2401_dev1p.buf.send_buf[7], 0,sizeof(unsigned char)*(NRF2401_BUF_DATA_LEN - 7));
			break;
		case 0x40:			//drib
			g_nRF2401_dev1p.buf.send_buf[3] = 0x10;
			g_nRF2401_dev1p.buf.send_buf[4] = 0;
			g_nRF2401_dev1p.buf.send_buf[5] = 0;
			g_nRF2401_dev1p.buf.send_buf[6] = 0;
			memset(&g_nRF2401_dev1p.buf.send_buf[7], 0,sizeof(unsigned char)*(NRF2401_BUF_DATA_LEN - 7));
			break;
		case 0x20:			//chip
			memset(&g_nRF2401_dev1p.buf.send_buf[3], 0,sizeof(unsigned char)*(NRF2401_BUF_DATA_LEN - 3));
			g_nRF2401_dev1p.buf.send_buf[3] = 0x40;
			g_nRF2401_dev1p.buf.send_buf[18] = 0x10;
			break;
		case 0x10:			//shoot
			memset(&g_nRF2401_dev1p.buf.send_buf[3], 0,sizeof(unsigned char)*(NRF2401_BUF_DATA_LEN - 3));
			g_nRF2401_dev1p.buf.send_buf[18] = 0x10;
			break;
        case 0x00:
            memset(&g_nRF2401_dev1p.buf.send_buf[3], 0,sizeof(unsigned char)*(NRF2401_BUF_DATA_LEN - 3));
            break;
		default:
			g_nRF2401_dev1p.buf.send_buf[3] = 0;
            g_nRF2401_dev1p.buf.send_buf[4] = 0x40;
            g_nRF2401_dev1p.buf.send_buf[5] = 0;
            g_nRF2401_dev1p.buf.send_buf[6] = 0;
            memset(&g_nRF2401_dev1p.buf.send_buf[7], 0,sizeof(unsigned char)*(NRF2401_BUF_DATA_LEN - 7));
            break;
	}

	send_nRF2401_packet(&g_nRF2401_dev1p);
}

