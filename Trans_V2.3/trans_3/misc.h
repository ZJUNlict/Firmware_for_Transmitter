#ifndef MISC_H_
#define MISC_H_
#include "config.h"
typedef struct _error_
{
	unsigned int err_num;
	unsigned int err_time;/* s */
	unsigned int err_kinds;
} error_tt;

void led_on(char num);
void led_off(char num);
void init_led();
void led_in_turn();
void led_flash();
void note_err(unsigned int err_kind);

#ifndef MISC_C
extern error_tt g_error[MAX_ERR_NUM];
extern int g_err_num;
#endif
#endif /*MISC_H_*/
