#ifndef _PCA9557_H_
#define _PCA9557_H_

#include <altera_avalon_pio_regs.h>
#include "system.h"
#include "Config.h"
#include "Misc.h"



#define CMD_WRITE_PORT9557 1
#define CMD_WRITE_POLARITY9557 2
#define CMD_WRITE_CONFIG9557 3

void reset_9557();
void set_data_9557();
void set_clk_9557();
void clr_data_9557();
void clr_clk_9557();
char get_data_9557();
void start_bit9557();
void send_byte(unsigned char data);
int get_acknowledge();
unsigned char get_8bit9557();
void stop_bit9557();
int read_byte_9557(unsigned char addr, char command);
int write_byte_9557(unsigned char addr, unsigned char command, unsigned char data);
int	init_pca9557();
void delay(int us);


#endif

