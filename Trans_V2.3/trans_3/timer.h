#ifndef TIMER_H_
#define TIMER_H_
#include <io.h>

void init_timer();
void do_timer( void * context, alt_u32 id );
#ifndef TIMER_C
extern unsigned int g_sys_time;
extern unsigned char g_is_b2b_counter_start;
extern volatile char g_2401_send_finish;
#endif
#endif /*TIMER_H_*/
