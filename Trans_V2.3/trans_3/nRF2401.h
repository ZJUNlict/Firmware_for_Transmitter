#ifndef __NRF2401_H__
#define __NRF2401_H__
#include "sys/alt_irq.h"
#include "config.h"

#define DEFAULT_FREQ 6

typedef struct _nRF2401_buf
{
	int len;
	int get_buf_pos;
	int send_buf_pos;
	unsigned char get_buf[NRF2401_BUF_DATA_LEN];
	unsigned char send_buf[NRF2401_BUF_DATA_LEN];
} nRF2401_buf;

//≈‰÷√◊÷
typedef struct _RFConfig
{
	unsigned char n;
	unsigned char buf[NRF2401_CONFIG_DATA_LEN];
} RFConfig;

typedef struct _nRF2401
{
	nRF2401_buf buf;
	unsigned char RFconf[NRF2401_CONFIG_DATA_LEN];
	unsigned int packet_error;
	unsigned int ce_base;
	unsigned int clk_base;
	unsigned int cs_base;
	unsigned int data_base;
	unsigned int dr_base;
	unsigned int dr_irq;
	unsigned char pac_get;
}nRF2401_t;

void set_nrf2401_base();
void delay_400ns();
void set_config_mode(nRF2401_t *dev);
void end_config_mode(nRF2401_t *dev);
void set_a_bit_to(char txrx, nRF2401_t *dev); 
void Tra_Rf_Write( unsigned char b ,nRF2401_t *dev);
unsigned char Tra_Rf_Read(nRF2401_t *dev);
void SetCE(unsigned char val, nRF2401_t *dev);
void SetCS(unsigned char val, nRF2401_t *dev);
void SetCLK(unsigned char val, nRF2401_t *dev);
void SetDATADir(unsigned char val, nRF2401_t *dev) ;
void Set_DATA(unsigned char val, nRF2401_t *dev);
unsigned char GetDATA(nRF2401_t *dev);
unsigned char GetDR(nRF2401_t *dev);
void init_nrf2401_dr(nRF2401_t *dev);
void send_nrf2401_config_data(nRF2401_t *dev);
int set_nrf2401_config_data(nRF2401_t *dev, unsigned char addr_len, unsigned char data_len, unsigned char *addr, unsigned char rxtx, unsigned char freq);
int get_nRF2401_packet(nRF2401_t *dev, alt_u32 interrupt);
int send_nRF2401_packet(nRF2401_t *dev);
void init_nrf2401();
void send_nrf2401_packet_cf(unsigned char Mode);
unsigned char decode_nrf2401_packet_cf(unsigned char Mode);


#ifndef NRF2401_C
extern volatile nRF2401_t g_nRF2401_dev1p;
extern volatile nRF2401_t g_nRF2401_dev2p;
extern volatile unsigned char g_comm_data_len;
extern volatile unsigned char g_2401_frq ;
extern volatile unsigned char g_2401_addr_len;
extern volatile unsigned char g_2401_rxtx;
extern volatile unsigned char g_2401_addr[MAX_2401_ADDR_LEN];
extern volatile unsigned char g_2401_2_frq ;
extern volatile unsigned char g_2401_2_addr_len;
extern volatile unsigned char g_2401_2_rxtx;
extern volatile unsigned char g_2401_2_addr[MAX_2401_ADDR_LEN];
extern volatile unsigned char g_2401_send_addr[MAX_2401_ADDR_LEN];
extern volatile unsigned char g_is_2401_send_period;
extern nRF2401_t *g_send_2401_dev_p;
#endif

#endif


