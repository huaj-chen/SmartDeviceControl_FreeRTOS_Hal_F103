#include "driver_I2C.h"
#include <stm32f1xx_hal.h>

void I2C_GPIO_ReInit()
{
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	I2C_SCL_GPIO_CLK_ENABLE();
	I2C_SDA_GPIO_CLK_ENABLE();

	GPIO_InitStruct.Pin = SCL_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init (SCL_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = SDA_PIN;
	HAL_GPIO_Init (SDA_PORT, &GPIO_InitStruct);
}

void I2C_delay(uint8_t i)
{
	volatile uint8_t tmp = i;
	while(tmp--);
}

void I2C_Start()
{
	SDA_H;
	SCL_H;
	I2C_delay(200);
	SDA_L;
	I2C_delay(200);
}


void I2C_Stop()
{
	SDA_L;
	SCL_H;
	I2C_delay(200);
	SDA_H;
	I2C_delay(200);
}




int I2C_GetAck()
{
    int i = 0; 
	SDA_H;//往SDA写高，此时SDA状态由外部决定
	SCL_L;
	I2C_delay(200);
	SCL_H;
	while(SDA_IN != 0)//等待SDA拉低，则收到从机应答信号	
	{
		i++;
		if(i == 1000)
		{
			SCL_L;
			return -1;
		}
	}
	SCL_L;//将SCL拉低，留给从机时间
	return 0;
}

//主机产生一个应答信号  ，应答信号是：SDA拉低 
void I2C_ACK()
{

	SDA_L;
	SCL_L;//SCL为低，SDA数据无效，为SDA电平转换时间
	I2C_delay(200);
	SCL_H;
	I2C_delay(200);
}

//主机产生一个非应答信号
void I2C_NACK()
{

	SDA_H;//输出浮空，由外部上拉为高
	SCL_L;//SCL为低，SDA数据无效，为SDA电平转换时间
	I2C_delay(200);
	SCL_H;
	I2C_delay(200);
}

void I2C_WriteByte(uint8_t data)
{
	uint8_t i = 0;
	for(i = 0;i < 8; i++)
	{
		SCL_L;
		I2C_delay(200);
		if(data & 0x80)//获得最高位，并判断是1或0
		{
			SDA_H;
		}
		else
		{
			SDA_L;
		}
		data << 1;
		SDA_H;//时钟线拉高，使数据有效
		I2C_delay(200);
	}
	I2C_GetAck ();

}


uint8_t I2C_ReadByte(uint8_t ack)
{

	uint8_t i = 0;
	uint8_t data = 0;

	SDA_H;
	for(i = 0; i < 8; i++)
	{
		SCL_L;
		I2C_delay(200);
		SCL_H;//SCL拉高使数据位有效
		I2C_delay(200);
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

