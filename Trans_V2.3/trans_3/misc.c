#define MISC_C
#include "misc.h"
#include "system.h"
#include "timer.h"
#include "main.h"
#include <altera_avalon_pio_regs.h>

error_tt g_error[MAX_ERR_NUM] = {{0, 0, 0}};
int g_err_num = 0;

void led_on(char num)
{
    switch(num)
    {
        case 1:IOWR(PIO_LED1_BASE, 0, 0); break;
        case 2:IOWR(PIO_LED2_BASE, 0, 0); break;
        case 3:IOWR(PIO_LED3_BASE, 0, 0); break;
        default:    break;
    }
}

void led_off(char num)
{
    switch(num)
    {
        case 1:IOWR(PIO_LED1_BASE, 0, 1); break;
        case 2:IOWR(PIO_LED2_BASE, 0, 1); break;
        case 3:IOWR(PIO_LED3_BASE, 0, 1); break;
        default:    break;
    }
}

void led_in_turn()
{
	led_on(1);		
	led_off(2);
	led_off(3);
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);		
	usleep(300000);
	led_off(1);		
	led_on(2);
	led_off(3);
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(300000);
	led_off(1);		
	led_off(2);
	led_on(3);
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(300000);
	led_off(1);		
	led_on(2);
	led_off(3);
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(300000);
}

void led_flash()
{
	led_on(1);		
	led_on(2);
	led_on(3);
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);		
	usleep(300000);
	led_off(1);		
	led_off(2);
	led_off(3);
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	usleep(300000);
}

void init_led()
{
	int i = 0;
	led_off(1);
	led_off(2);
	led_off(3);
	usleep(250000);
	IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	
	for(i=0; i<(g_flash_rx_buf[1] & 0x07); i++)
	{
		led_on(1);
		led_on(2);
		led_on(3);
		usleep(250000);
		IOWR(TIMER_WATCHDOG_BASE, 2, 0);
		
		led_off(1);
		led_off(2);
		led_off(3);
		usleep(250000);
		IOWR(TIMER_WATCHDOG_BASE, 2, 0);
	}
	
	led_off(1);
	led_off(2);
	led_off(3);
}

void note_err(unsigned int err_kind)
{
	if(g_err_num < MAX_ERR_NUM)
	{
		g_err_num++;
	}
	else
	{
		g_err_num = 0;
	}
	g_error[g_err_num].err_num = g_err_num;
	g_error[g_err_num].err_kinds = err_kind;
	g_error[g_err_num].err_time = g_sys_time;
}
