#ifndef CONFIG_H_
#define CONFIG_H_

//timer:
#define CLKFREQ 50000000
#define TICKFREQ 1000

//uart:
#define UART_READ_BUF_LEN 		256
#define UART_SEND_BUF_LEN		256
#define UART_B2B_PERIOD 5

//flash:
#define FLASH_BUF_LEN		14

//nrf2401:
#define CRC_16				1
#define CRC_8				0
#define CRC_ENABLE			1
#define CRC_DISABLE			0
#define RX2_EN				1
#define RX2_DISABLE			0
#define SHOCKBURST_MODE	1
#define DIRECT_MODE			0
#define RF_DATA_RATE_1M	1
#define RF_DATA_RATE_250K	0
#define XO_F_4				0
#define XO_F_8				1
#define XO_F_12				2
#define XO_F_16				3
#define XO_F_20				4
#define RF_PWR_20			0
#define RF_PWR_10			1
#define RF_PWR_5			2
#define RF_PWR_0			3
#define NRF2401_CONFIG_DATA_LEN		15
#define NRF2401_BUF_DATA_LEN			100
#define NRF2401_RX          1
#define NRF2401_TX          0
#define MAX_2401_ADDR_LEN 5
#define NRF2401_SEND_PERIOD 0

//misc:
#define MAX_ERR_NUM 1000
#define USB_RECEIVE_PACKET_OVERFLOW 1
#define NRF2401_CONFIG_DATA_OVERFLOW 2
#define NRF2401_GET_NO_DATA_ERROR 3
#define USB_READ_OVER_2401_SEND_ERROR 4
#define CONFIG_DATA_CRC_ERROR 5
#define UART_B2B_PERIOD_OVERFLOW 6
#define UART_COMM_ERROR 7
#define CONFIG_DATA_VERSION_ERROR 8
#endif /*CONFIG_H_*/

//check frq
#define GET_PARAMETER 0
#define START_TESTING 1
#define TESTING1 2
#define TESTING2 7
#define GET_TEST_RESULT 3
#define ENDING 4
#define CF_RESET 5

#define CF_DEFAULT_FRQ 6

#define FRQ_CHECK_ABRATE 20

#define ENABLE_9557_SET//�̶�Ƶ������


#include <unistd.h>
