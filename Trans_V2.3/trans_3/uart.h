#ifndef __UART_H__
#define __UART_H__
#include "sys/alt_irq.h"
#include "config.h"
int read_uart_usb1_data( unsigned char *data );
int read_uart_usb2_data( unsigned char *data );
void send_uart_usb1_data(unsigned char *data, int len);
void send_uart_usb2_data(unsigned char *data, int len);
int init_uart();
void decode_start_packet();
void decode_uart_packet();
void decode_uart_packet_cf(unsigned char Mode);
int decode_nrf2401_packet_frq();
void uart_usb1_handle(void *context, alt_u32 interrupt);
void uart_usb2_handle(void *context, alt_u32 interrupt);
void send_eeprom_data();
void decode_config_packet();

#ifndef UART_C
extern volatile unsigned int g_uart_usb1_baudrate;
extern volatile unsigned int g_uart_usb1_control ;
extern volatile unsigned char g_uart_usb1_read_buf[UART_READ_BUF_LEN] ;
extern volatile unsigned char g_uart_usb1_read_buf_pos;
extern volatile unsigned char g_uart_usb1_send_buf[UART_SEND_BUF_LEN] ;
extern volatile unsigned char g_uart_usb1_send_buf_pos ;
extern volatile unsigned char g_uart_usb1_send_len ;
extern volatile char g_is_uart_get_a_packet ; 
extern volatile char g_transfer_start;
extern volatile char g_transfer_config;
extern volatile char g_transfer_config_frq;

#endif

#endif
