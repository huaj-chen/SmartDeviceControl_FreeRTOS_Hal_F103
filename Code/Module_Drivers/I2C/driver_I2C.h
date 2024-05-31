#ifndef __DRIVER_I2C_H
#define __DRIVER_I2C_H
#include "main.h"


#define 		SCL_PORT  		GPIOB
#define 		SDA_PORT 		GPIOB
#define			I2C_SCL_GPIO_CLK_ENABLE()					__HAL_RCC_GPIOB_CLK_ENABLE()
#define			I2C_SDA_GPIO_CLK_ENABLE()					__HAL_RCC_GPIOB_CLK_ENABLE()


#define 		SCL_PIN			GPIO_PIN_5
#define 		SDA_PIN			GPIO_PIN_6

/*IO��д�ߣ��������գ���ƽ���ⲿ������I2C�ⲿ����Ϊ��*/
/*IO��д�ͣ����Žӵأ���ƽΪ��*/
#define			SCL_H			HAL_GPIO_WritePin (SCL_PORT, SCL_PIN, GPIO_PIN_SET)
#define			SCL_L			HAL_GPIO_WritePin (SCL_PORT, SCL_PIN, GPIO_PIN_RESET)


#define			SDA_H			HAL_GPIO_WritePin (SDA_PORT, SDA_PIN, GPIO_PIN_SET)
#define			SDA_L			HAL_GPIO_WritePin (SDA_PORT, SDA_PIN, GPIO_PIN_RESET)
#define			SDA_IN			HAL_GPIO_ReadPin(SDA_PORT, SDA_PIN)


uint8_t I2C_ReadByte(uint8_t ack);
void I2C_WriteByte(uint8_t data);
void I2C_NACK(void);
void I2C_ACK(void);
int I2C_GetAck(void);//���Ӧ���ź�
void I2C_Stop(void);//ֹͣ�ź�
void I2C_Start(void);//��ʼ�ź�



#endif //__DRIVER_I2C_H


