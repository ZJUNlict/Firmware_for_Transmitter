#ifndef MAIN_H_
#define MAIN_H_

void initialize(int flag);
void init_config_data();
void set_config_data();
int frq_check(unsigned char frq);
void cf_reset_robot();
int num_change_to_char(int num,unsigned char * num_char);
void char_ary_reverse(int num_len,unsigned char * num_char);
int calculate_packet_loss_rate(unsigned char * mes,unsigned char * num_char,int num_len,int send_num);
void do_comm_test(unsigned char *packet, int len);
int check_comm_test(unsigned char *packet, int len);



#ifndef MAIN_C
extern volatile unsigned char g_byte_to_byte_period;
extern volatile unsigned char g_flash_rx_buf[FLASH_BUF_LEN];
extern volatile unsigned long g_uart_get_packet_num;
extern volatile unsigned long g_uart_send_packet_num;
extern volatile unsigned long g_2401_get_packet_num;
extern volatile unsigned long g_2401_send_packet_num;
extern volatile unsigned long g_uart_get_byte_num;
extern volatile unsigned long g_uart_send_byte_num;
#endif

#endif /*MAIN_H_*/
