/*********************************************
  * file name: [ file ]
  * last update: [ date ]
  * description: [ desc ]
  * note: [ note ]
  * author: [ author ]
  * copyright: [ copyright ]
  * revision history:
  * [ history ]
  *
*********************************************/
#ifndef _CRC_H_
#define _CRC_H_


int is_crc_good( const unsigned char *pData, int nLength );
int get_crc( const unsigned char *pData, int nLength );

#endif
