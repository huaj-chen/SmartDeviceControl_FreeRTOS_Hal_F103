#include "driver_I2C.h"
#include <stm32f1xx_hal.h>




void I2C_delay(uint8_t i)
{
	volatile uint8_t tmp = i;
	while(tmp--);
}

/**
 * @brief ��ʼ�ź�-ʱ����Ϊ�ߣ������ߴӸߵ����л�
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
 * @brief �����ź�-ʱ����Ϊ�ߣ��������ɵ͵���
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
 * @brief ��ȡӦ���ź�-SDAΪ�͵�ƽ����ʾӦ��
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
int I2C_GetAck()
{
    int i = 0; 
	SDA_H;            //��SDAд�ߣ��ͷ�SDA����Ȩ
	SCL_L;
	I2C_delay(200);
	SCL_H;			  //��������SCL�ߣ�����ӻ���SCLΪ��ʱ��SDA�߽��в�����
	while(SDA_IN != 0)//�ȴ�SDA���ͣ����յ��ӻ�Ӧ���ź�	
	{
		i++;
		if(i == 1000)
		{
			SCL_L;
			return -1;
		}
	}
	SCL_L;//��������SCL�ߣ�׼����һ�����ݴ���
	return 0;
}


/**
 * @brief ��������һ��Ӧ���źţ�Ӧ���ź��ǣ�SDA���� 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
void I2C_ACK()
{

	SDA_L;
	SCL_L;//SCLΪ�ͣ�SDA������Ч��ΪSDA��ƽת��ʱ��
	SCL_H;

}


/** 
 * @brief ��������һ����Ӧ���ź� 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
void I2C_NACK()
{

	SDA_H;//������գ����ⲿ����Ϊ��
	SCL_L;//SCLΪ�ͣ�SDA������Ч��ΪSDA��ƽת��ʱ��
	SCL_H;
}


/**
 * @brief дһ���ֽ�
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
		if(data & 0x80)//������λ�����ж���1��0
		{
			SDA_H;
		}
		else
		{
			SDA_L;
		}
		data <<= 1;
		SCL_H;//ʱ�������ߣ�ʹ������Ч
		SCL_L;
	}

}


/**
 * @brief ��һ���ֽ�
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

	SDA_H;//SDA ���ⲿ�ӹ�
	for(i = 0; i < 8; i++)
	{
		SCL_L;
		SCL_H;//SCL����ʹ����λ��Ч
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

