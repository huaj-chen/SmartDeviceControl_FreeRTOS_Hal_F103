#include "driver_I2C.h"
#include <stm32f1xx_hal.h>




void I2C_delay(uint8_t i)
{
	volatile uint8_t tmp = i;
	while(tmp--);
}

/**
 * @brief 起始信号-时钟线为高，数据线从高到低切换
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
void I2C_Start()
{
	SDA_H;
	SCL_H;
	SDA_L;
	SCL_L;

}


/**
 * @brief 结束信号-时钟线为高，数据线由低到高
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
void I2C_Stop()
{
	SCL_H;
	SDA_L;
	SDA_H;
}


/**
 * @brief 获取应答信号-SDA为低电平，表示应答
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
int I2C_GetAck()
{
    int i = 0; 
	SDA_H;            //往SDA写高，释放SDA控制权
	SCL_L;
	I2C_delay(200);
	SCL_H;			  //主机拉高SCL线，允许从机在SCL为高时对SDA线进行操作。
	while(SDA_IN != 0)//等待SDA拉低，则收到从机应答信号	
	{
		i++;
		if(i == 1000)
		{
			SCL_L;
			return -1;
		}
	}
	SCL_L;//主机拉低SCL线，准备下一次数据传输
	return 0;
}


/**
 * @brief 主机产生一个应答信号，应答信号是：SDA拉低 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
void I2C_ACK()
{

	SDA_L;
	SCL_L;//SCL为低，SDA数据无效，为SDA电平转换时间
	SCL_H;

}


/** 
 * @brief 主机产生一个非应答信号 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
void I2C_NACK()
{

	SDA_H;//输出浮空，由外部上拉为高
	SCL_L;//SCL为低，SDA数据无效，为SDA电平转换时间
	SCL_H;
}


/**
 * @brief 写一个字节
 * @param data 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
void I2C_WriteByte(uint8_t data)
{
	uint8_t i = 0;
	for(i = 0;i < 8; i++)
	{
		SCL_L;
		if(data & 0x80)//获得最高位，并判断是1或0
		{
			SDA_H;
		}
		else
		{
			SDA_L;
		}
		data <<= 1;
		SCL_H;//时钟线拉高，使数据有效
		SCL_L;
	}

}


/**
 * @brief 读一个字节
 * @param ack 
 * @return {uint8_t} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
uint8_t I2C_ReadByte(uint8_t ack)
{

	uint8_t i = 0;
	uint8_t data = 0;

	SDA_H;//SDA 由外部接管
	for(i = 0; i < 8; i++)
	{
		SCL_L;
		SCL_H;//SCL拉高使数据位有效
		data <<= 1;//将数据左移一位，使收到的数据正常
		if(SDA_IN == 1)
		{
			data++;
		}
		else
		{
			data = data;
		}
	}

	if(ack == 0)
	{
		 I2C_ACK ();
	}
	else
	{
		I2C_NACK ();
	}
	return data;
}

