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

#include "flash.h"
#include "system.h"
#include <io.h>
#include "config.h"

/***************************************
 IIC pin configuration
 
 Change these functions if pin configuration is changed.
***************************************/

void	I2C_SDA_WR(unsigned char v)
{
  	IOWR(PIO_DATA_24_BASE, 1, 1);  
	if( v )
  	{
   	  IOWR(PIO_DATA_24_BASE,0,1);
  	}
	else
  	{
   	  IOWR(PIO_DATA_24_BASE,0,0); 
  	}
}

int I2C_SDA_RD(void)
{
 	 unsigned int temp;  
  	IOWR(PIO_DATA_24_BASE,1,0x0);
	temp = IORD(PIO_DATA_24_BASE,0);
	if( temp & 0x1 )
		return 1;
	else
		return 0;
}

void	I2C_SCK_WR(unsigned char v)
{
	  if( v )
	  {
	     IOWR(PIO_CLK_24_BASE,0,1);
	  }
	  else
	  {
	     IOWR(PIO_CLK_24_BASE,0,0); 
	  }
}

void I2C_DIR(unsigned char v)	//0 : input, 1:output
{
	if( v )
		IOWR(PIO_DATA_24_BASE, 1, 1);
	else
		IOWR(PIO_DATA_24_BASE, 1, 0);
}


int I2C_Start(void)
{
 IOWR(PIO_CLK_24_BASE,0,0);
 IOWR(PIO_DATA_24_BASE,0,0);
 I2C_DIR(1);
 usleep(10);
 I2C_SDA_WR(1);
 usleep(10);
 I2C_SCK_WR(1);
 usleep(10);
 I2C_SDA_WR(0);
 usleep(10);
 I2C_SCK_WR(0);
 usleep(10);
 return 1;
}


void  I2C_Stop(void)
{
 usleep(10);
 I2C_SDA_WR(0);
 usleep(10);
 I2C_SCK_WR(1);
 usleep(10);
 I2C_SDA_WR(1);
 usleep(10);
}

void I2C_Ack(void)
{
 usleep(10);
 I2C_SDA_WR(0);
 usleep(10);
 I2C_SCK_WR(1);
 usleep(10);
 I2C_SCK_WR(0);
 usleep(10);
}

void I2C_Nack(void)
{
 usleep(10);
 I2C_SDA_WR(1);
 usleep(10);
 I2C_SCK_WR(1);
 usleep(10);
 I2C_SCK_WR(0);
 usleep(10);
}

int I2C_Send_Byte( unsigned char d)
{
 unsigned char i = 8;
 int bit_ack;
 while( i-- )
 {
 usleep(10);
  if ( d &0x80 )   I2C_SDA_WR(1);
  else             I2C_SDA_WR(0);
 usleep(10);
  I2C_SCK_WR(1);
 usleep(10);
  I2C_SCK_WR(0);
  d = d << 1;
 }
 usleep(10);
 I2C_SDA_WR(1);
 I2C_DIR(0);
 usleep(10);
 I2C_SCK_WR(1);
 usleep(10);
 bit_ack = I2C_SDA_RD();
 I2C_SCK_WR(0);
 usleep(10);
 I2C_DIR(1);
 return bit_ack;
}

unsigned char I2C_Receive_Byte(void)
{
 unsigned char i = 8, d=0;
 usleep(10);
 I2C_SDA_WR(1);
 I2C_DIR(0);
 I2C_SCK_WR(0);
 while ( i--)
 {
  d = d << 1;
 usleep(10);
  I2C_SCK_WR(1);
  if ( I2C_SDA_RD() ) d++;
 usleep(10);
  I2C_SCK_WR(0);
 }
 return d;
}

void AT24C64_W(void *mcu_address,unsigned int AT24C64_address,unsigned int count)
{

 while(count--)
 {
  I2C_Start();
  I2C_Send_Byte( 0xa0 + AT24C64_address / 256 *2);  /* 24C08  USE */
  I2C_Send_Byte( AT24C64_address %256 );
  I2C_Send_Byte( *(unsigned char*)mcu_address );
  I2C_Stop();
  usleep(10000);        //10ms
  ((unsigned char*)mcu_address)++;
  AT24C64_address++;
 }
}


void AT24C64_R(void *mcu_address,unsigned int AT24C64_address,unsigned int count)
{
 while(count--)
 {
  I2C_Start();
  I2C_Send_Byte( 0xa0 + AT24C64_address / 256 *2 );  /* 24C08 USE */
  I2C_Send_Byte( AT24C64_address % 256 );
  I2C_Start();
  I2C_Send_Byte( 0xa1 + AT24C64_address /256 *2 );
  *(unsigned char*)mcu_address = I2C_Receive_Byte();
  I2C_Nack();
  I2C_Stop();
  usleep(10000);
  ((unsigned char*)mcu_address)++;
  AT24C64_address++;
 }
}



/* interface */
int flash_setb( unsigned short addr, unsigned char byte )
{
	AT24C64_W( &byte, addr, 1 );	
	return 0;
}

unsigned char  flash_getb( unsigned short addr )
{
	unsigned char value = 0;	
	AT24C64_R( &value, addr, 1 );	
	return value;
}

int flash_set( unsigned short addr, unsigned char *data, int len )
{
	int i = 0;	
	if( data == 0 )
		return -1;	
	for( i = 0; i < len; i++ )
	{
		flash_setb( addr + i, *( data + i ) );
	}	
	return 0;
}

int flash_get( unsigned short addr, unsigned char *data, int len )
{
	int i = 0;	
	if( data == 0 )
		return -1;	
	for( i = 0; i < len; i++ )
	{
		*( data + i ) = flash_getb( addr + i );
	}
	
	return 0;	
}

void init_eeprom()
{
    unsigned char eeprom_data[FLASH_BUF_LEN];
    flash_get(0, eeprom_data, FLASH_BUF_LEN);
//    if(eeprom_data[0] != 0x21)      //默认为2.1版本，数据包长25字节，波特率115200，                              
    {                           ////1号2401发射，5字节地址,接收方地址为10，71， 45， 98， 00
        eeprom_data[0] = 0x21;  //2号2401接收，5字节地址，为10，71， 45， 98， 00
        eeprom_data[1] = 0xcf;
        eeprom_data[2] = 0x56;
        eeprom_data[3] = 0xd6;
        eeprom_data[4] = 0x10+0x11;
        eeprom_data[5] = 0x71+0x11;
        eeprom_data[6] = 0x45+0x11;
        eeprom_data[7] = 0x98+0x11;
        eeprom_data[8] = 0x00+0x11;
        eeprom_data[9] = 0x10;
        eeprom_data[10] = 0x71;
        eeprom_data[11] = 0x45;
        eeprom_data[12] = 0x98;
        eeprom_data[13] = 0x00;
        flash_set(0, eeprom_data, FLASH_BUF_LEN);
    }
}

