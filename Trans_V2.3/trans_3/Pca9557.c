#include "Pca9557.h"

/*-----------------------------------------------------------------
 *
 *  IO :   0  |  1   |  2   |  3   |  4   |  5   |  6   |  7
 *  7号:      |      | frq3 | frq2 | frq1 | frq0 |      |  
 *  不接的引脚设为输出。
 *
 -----------------------------------------------------------------*/
 
int pca9557_frq;
char pca9557_frq_set_flag = 0;

/*-----------------------------------------------------------------
 *  function name: init_pca9557
 *  description: 初始化9557，一共有5次重试机会，每次配置完后重新读取
 *				 以检验是否配置成功。无论哪个步骤出错即重置复位标志
 *				 重新配置。9557的地址为7，由硬件连接决定
 *  author:lyc
 *  last update: 2014-12-27
 -----------------------------------------------------------------*/ 
int init_pca9557()
{
	int blood = 6;           //重试标志，给五次重试的机会
	int is_to_reset = 1;     //复位标志
    int temp=0;
	reset_9557();
	while(is_to_reset)
	{
		blood--;		
		if(blood)
		{
			reset_9557();
			
			if(write_byte_9557(7, CMD_WRITE_CONFIG9557, 0x3c) >= 0)
			{
				if(read_byte_9557(7, CMD_WRITE_CONFIG9557) == 0x3c)
				{
					is_to_reset = 0;
				}
				else
				{
					is_to_reset = 1;
					continue;
				}
			}
			else
			{
				is_to_reset = 1;
				continue;
			}
			
			if(write_byte_9557(7, CMD_WRITE_POLARITY9557, 0x0) >= 0)
			{
				if(read_byte_9557(7, CMD_WRITE_POLARITY9557) == 0x0)
				{
					is_to_reset = 0;
				}
				else
				{
					is_to_reset = 1;
					continue;
				}
			}
			else
			{
				is_to_reset = 1;
				continue;
			}

					
  			#ifdef _Config_frq_
				pca9557_frq  = _Config_frq_;
			#else
            pca9557_frq = (read_byte_9557(7, 0));

			
			if(pca9557_frq > 0)
			{
				pca9557_frq = ~pca9557_frq ;
				
				temp=((pca9557_frq & 0x20) >> 5) + ((pca9557_frq & 0x10) >> 3) + ((pca9557_frq & 0x08) >> 1) + ((pca9557_frq & 0x0) << 1);
				
                pca9557_frq = temp;
                /*之后发送数据时再处理
                if(temp <= 7)					
                {
                    pca9557_frq = temp<<2;
 
                }
				else
				{
                    pca9557_frq = (temp<<2) + 58;
 
                }*/
				is_to_reset = 0;
			}
			else
			{
				is_to_reset = 1;
				continue;
			}
			#endif
		}
		else    //若没有成功从pca9557中得到要设置的频点，则设置为0
		{
            pca9557_frq  = 0;
			led_off(0);
			led_off(1);
			return -1;
		}
	}

	if (pca9557_frq != 0)
		pca9557_frq_set_flag = 1;   //若频点为0表示频点数据不从pca9557中获得

	
	return 0;
} 

/*-----------------------------------------------------------------
 *  function name: reset_9557
 *  description:  9557低电平拉低一段时间可完成reset，完成reset后需
 *                重新拉高
 *  author: 未知
 *  last update: 2011-11-26
 -----------------------------------------------------------------*/ 

void reset_9557()
{
	IOWR(PIO_RESET_9557_BASE, 0, 0);
	delay(130);
	IOWR(PIO_RESET_9557_BASE, 0, 1);
	delay(100);
}

/*-----------------------------------------------------------------
 *  function name: set_data_9557
 *  description:  由于IIC总线默认由上拉电阻拉高，故输出高时需先
 *                将IO口置为输入，由上拉电阻输出高。具体高低变化
 *                规则参见IIC通讯协议
 *  author: 未知
 *  last update: 2011-11-26
 -----------------------------------------------------------------*/ 

void set_data_9557()
{
	IOWR(PIO_SDA_9557_BASE, 1, 0);
	//IOWR(PIO_SDA_9557_BASE, 0, 1);
	delay(100);
}

/*-----------------------------------------------------------------
 *  function name: set_clk_9557
 *  description:  将时钟信号拉高
 *  author: 未知
 *  last update: 2011-11-26
 -----------------------------------------------------------------*/ 

void set_clk_9557()
{
	IOWR(PIO_SCL_9557_BASE, 0, 1);
	delay(100);
}

/*-----------------------------------------------------------------
 *  function name: clr_data_9557
 *  description:  将数据信号拉低
 *  author: 未知
 *  last update: 2011-11-26
 -----------------------------------------------------------------*/ 

void clr_data_9557()
{
	IOWR(PIO_SDA_9557_BASE, 1, 1);
	IOWR(PIO_SDA_9557_BASE, 0, 0);
	delay(100);
}

/*-----------------------------------------------------------------
 *  function name: clr_clk_9557
 *  description:  将时钟信号拉低
 *  author: 未知
 *  last update: 2011-11-26
 -----------------------------------------------------------------*/ 

void clr_clk_9557()
{
	IOWR(PIO_SCL_9557_BASE, 0, 0);
	delay(100);
}

/*-----------------------------------------------------------------
 *  function name: get_data_9557
 *  description:  从数据口读取一个位的数据并返回0或1
 *  author: 未知
 *  last update: 2011-11-26
 -----------------------------------------------------------------*/ 
 
char get_data_9557()
{
	IOWR(PIO_SDA_9557_BASE, 1, 0);
	delay(100);
	if(IORD(PIO_SDA_9557_BASE, 0) & 0x1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*-----------------------------------------------------------------
 *  function name: start_bit9557
 *  description:  IIC通讯开始信号，具体规则详见IIC通讯规则，开始信号
 *				  完成后将数据信号拉高为默认高阻态
 *  author: 未知
 *  last update: 2011-11-26
 -----------------------------------------------------------------*/ 

void start_bit9557()
{
	set_data_9557();
	set_clk_9557();
	clr_data_9557();
	clr_clk_9557();
	set_data_9557();
}

/*-----------------------------------------------------------------
 *  function name: send_byte
 *  description:  发送data中的一个字节的数据，逐位发送，具体电平变化
 *				  规则详见IIC通讯协议。通讯完成后设置为高阻态，默认
 *				  为输入
 *  author: 未知
 *  last update: 2011-11-26
 -----------------------------------------------------------------*/ 

void send_byte(unsigned char data)
{
	char i = 0;
	
	 
	for(i=0;i<8;i++)
	{
		if( (data >> (7-i)) & 0x1)
		{
			set_data_9557();
		}
		else
		{
			clr_data_9557();
		}
		set_clk_9557();
		clr_clk_9557();
	}	
	set_data_9557();
}

/*-----------------------------------------------------------------
 *  function name: get_acknowledge
 *  description:  根据数据信号是否为低(默认状态为高)断从芯片对主机
 *				  是否成功应答，成功应答则返回1，否则为0
 *  author: 未知
 *  last update: 2011-11-26
 -----------------------------------------------------------------*/ 

int get_acknowledge()
{
	set_clk_9557();
   	 
	if(get_data_9557())
	{
		clr_clk_9557();	
 		return 0;
	}
	else
	{
		clr_clk_9557();
 		return 1;
	}
	
}

/*-----------------------------------------------------------------
 *  function name: get_8bit9557
 *  description:  从数据信号接收一个自己的数据并返回。逐位接收。
 *  author: 未知
 *  last update: 2011-11-26
 -----------------------------------------------------------------*/ 

unsigned char get_8bit9557()
{
	char i = 0;
	unsigned char data = 0;
	for(i=7;i>=0;i--)
	{
		set_clk_9557();
		data += (get_data_9557()) << i;
		clr_clk_9557();
	}
	return data;
}

/*-----------------------------------------------------------------
 *  function name: stop_bit9557
 *  description:  IIC通讯结束信号，具体规则详见IIC通讯规则
 *  author: 未知
 *  last update: 2011-11-26
 -----------------------------------------------------------------*/ 

void stop_bit9557()
{
	clr_data_9557();
	set_clk_9557();
	set_data_9557();
	clr_clk_9557();
}

/*-----------------------------------------------------------------
 *  function name: read_byte_9557
 *  description:  IIC通讯读取数据全过程，具体规则详见IIC通讯协议，
 *				  其参数addr为从芯片地址，command为读取的命令
 *  author: 未知
 *  last update: 2011-11-26
 -----------------------------------------------------------------*/ 

int read_byte_9557(unsigned char addr, char command)
{
	unsigned char data_from_slave = 0;
	start_bit9557();
	send_byte(0x30+(addr<<1));
	if(get_acknowledge())
	{
		send_byte(command);
		if(get_acknowledge())
		{
			start_bit9557();
			send_byte(0x31+(addr<<1));
			if(get_acknowledge())
			{
				data_from_slave = get_8bit9557();
				stop_bit9557();
				return data_from_slave;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}
	else	
	{
		return -1;
	}
}

/*-----------------------------------------------------------------
 *  function name: read_byte_9557
 *  description:  IIC通讯写数据全过程，具体规则详见IIC通讯协议，
 *				  其参数addr为从芯片地址，command为写数据的模式
 *				  data为待写数据。
 *  author: 未知
 *  last update: 2011-11-26
 -----------------------------------------------------------------*/ 


int write_byte_9557(unsigned char addr, unsigned char command, unsigned char data)
{
	start_bit9557();
	send_byte(0x30+(addr<<1));
	if(get_acknowledge())
	{
		send_byte(command);
		if(get_acknowledge())
		{
			send_byte(data);
			if(get_acknowledge())
			{
				stop_bit9557();
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
	return 0;
}


/*-----------------------------------------------------------------
 *	函数名称： delay
 *	函数描述： 写了一个延时函数，因为不同的编译配置下延时的长短不同，所以用OP_NONE来区分一下优化级别
 *		       这里的优化参数指工程里两个文件夹的属性→build里的配置。需要设置成一致的。
 *			   另外在库属性的system library里需要只选择clean exit /reduced device drivers/small C library. 否则延时会有差别。
 *			   参数表示需要延时的时间，单位是us。最短延时为1us。
 *			   据不完全测试，误差在1us或者10%以下。
 *			   在不优化的情况下，短时间的延时不容易实现，大约有10us的误差。
 *			   需要精确计时最好用定时器。
 *	
 *
 *
 *	作者：	   不详
 *	修改日期： 2011-9-15
 -----------------------------------------------------------------*/ 

void delay(int us)
{
	unsigned int i = 0;
	#ifdef OP_NONE 
		usleep(us);
	#else
		if(us == 0)
		{

		}
		else if(us == 1)
		{
			for(i=0;i<5;i++)
                		asm("nop");
		}
		else if(us < 5)
		{
			usleep(us-2);
		}
		else if(us < 11)
		{
			usleep(us-1);
		}
		else
		{
			usleep(us);
		}
	#endif 
}


