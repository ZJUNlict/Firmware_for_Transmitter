#define TIMER_C
#include "timer.h"
#include "config.h"
#include "system.h"
#include "main.h"
#include "uart.h"
#include "nRF2401.h"

unsigned int g_sys_time = 0;
unsigned char g_is_b2b_counter_start = 0;
volatile char g_2401_send_finish = 0;
char g_frq_cheak_send_flag = 0;
char timer_50ms_flag = 0;
void init_timer()
{
	unsigned long temp;

	temp = CLKFREQ / TICKFREQ; // calculate  the period

	IOWR( TIMER_0_BASE, 1, 0x8); // stop the timer
	IOWR( TIMER_0_BASE, 0, 0); //clear the irq flag

	IOWR( TIMER_WATCHDOG_BASE, 1, 0x8); // stop the timer
	IOWR( TIMER_WATCHDOG_BASE, 0, 0); //clear the irq flag
	
	//set the period reg
	IOWR( TIMER_0_BASE, 2, ( temp & 0xffff ) ); 
	IOWR( TIMER_0_BASE, 3, ( temp >> 16 ) );

	// register the interrupt handler
	alt_irq_register( TIMER_0_IRQ, ( void * )0, do_timer ); 

	// start the timer, continuously running.
	IOWR( TIMER_0_BASE, 1, 0x7 ); 
	//IOWR( TIMER_WATCHDOG_BASE, 1, 0x7 ); 
}

void do_timer( void * context, alt_u32 id )
{
	static unsigned int timer_counter = 0;
	static unsigned char g_2401_send_period = 0;
	static unsigned int frq_cheak_counter = 0;
	static unsigned int counterfor50ms = 0;
	IOWR(TIMER_0_BASE,0,0); 
	timer_counter++;
	if(timer_counter == 1000)
	{
		g_sys_time++;
		timer_counter = 0;
	}
	if(frq_cheak_counter == 16)
	{
		frq_cheak_counter = 0;
		g_frq_cheak_send_flag = 1;
	}
	else frq_cheak_counter++;
	if(timer_50ms_flag)
	{
		if(counterfor50ms== 5000)
		{
			counterfor50ms = 0;
			timer_50ms_flag = 0;
		}
		else counterfor50ms++;
	}
	if(g_is_b2b_counter_start)
	{
		g_byte_to_byte_period++;
	}
	if(g_byte_to_byte_period > UART_B2B_PERIOD)
	{
		g_is_b2b_counter_start = 0;
		g_byte_to_byte_period = 0;
		g_uart_usb1_read_buf_pos = 0;
		note_err(UART_B2B_PERIOD_OVERFLOW);
	}
	if(g_is_2401_send_period)
	{
		g_2401_send_period++;
	}
	if(g_2401_send_period > NRF2401_SEND_PERIOD)
	{
		g_2401_send_period = 0;
		g_2401_send_finish = 1;
		g_is_2401_send_period = 0;
	}
}
