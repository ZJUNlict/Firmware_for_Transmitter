/*********************************************
  * file name: [ file ]
  * last update: [ date ]
  * description: [ desc ]
  * note: [ note ]
  * author: Dong Lin, Chen Shouxian
  * copyright: 
  * revision history:
  * [ history ]
  *
*********************************************/
#ifndef _FLASH_H_
#define _FLASH_H_

/* flash related */
void init_eeprom();
int flash_setb( unsigned short addr, unsigned char byte );
unsigned char  flash_getb( unsigned short addr );
int flash_set( unsigned short addr, unsigned char *data, int len );
int flash_get( unsigned short addr, unsigned char *data, int len );

void	I2C_SDA_WR(unsigned char v);
int		I2C_SDA_RD(void);
void	I2C_SCK_WR(unsigned char v);
void 	I2C_DIR(unsigned char v);	//0 : input, 1:output

/***************************************
 End of IIC pin configuration
***************************************/
int   I2C_Start(void);
void  I2C_Stop(void);
void  I2C_Ack(void);
void  I2C_Nack(void);
int   I2C_Send_Byte( unsigned char);
unsigned char I2C_Receive_Byte(void);
void  AT24C64_R(void *mcu_address,unsigned int AT24C64_address,unsigned int count);
void  AT24C64_W(void *mcu_address,unsigned int AT24C64_address,unsigned int count);

#endif

