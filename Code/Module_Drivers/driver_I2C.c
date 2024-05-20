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
	SDA_H;//��SDAд�ߣ���ʱSDA״̬���ⲿ����
	SCL_L;
	I2C_delay(200);
	SCL_H;
	while(SDA_IN != 0)//�ȴ�SDA���ͣ����յ��ӻ�Ӧ���ź�	
	{
		i++;
		if(i == 1000)
		{
			SCL_L;
			return -1;
		}
	}
	SCL_L;//��SCL���ͣ������ӻ�ʱ��
	return 0;
}

//��������һ��Ӧ���ź�  ��Ӧ���ź��ǣ�SDA���� 
void I2C_ACK()
{

	SDA_L;
	SCL_L;//SCLΪ�ͣ�SDA������Ч��ΪSDA��ƽת��ʱ��
	I2C_delay(200);
	SCL_H;
	I2C_delay(200);
}

//��������һ����Ӧ���ź�
void I2C_NACK()
{

	SDA_H;//������գ����ⲿ����Ϊ��
	SCL_L;//SCLΪ�ͣ�SDA������Ч��ΪSDA��ƽת��ʱ��
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
		if(data & 0x80)//������λ�����ж���1��0
		{
			SDA_H;
		}
		else
		{
			SDA_L;
		}
		data << 1;
		SDA_H;//ʱ�������ߣ�ʹ������Ч
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
		SCL_H;//SCL����ʹ����λ��Ч
		I2C_delay(200);
		data <<= 1;//����������һλ��ʹ�յ�����������
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

