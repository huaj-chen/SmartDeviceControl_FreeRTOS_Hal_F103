#include <stm32f1xx_hal.h>
#include "LED_Device.h"
#include "driver_LED.h"



//==================================================================
//��    ����	HAL_LEDDeviceControl
//��   	�ܣ�	��HAL�⣬����LED��ʼ��
//���������	LED�豸�Ľṹ��ָ�룻LED��״̬
//�� �� ֵ��-1������ 0�����
//��    �ڣ�	2024/04/29
//��    ����
//==================================================================
int HAL_LEDDeviceControl(struct LEDDevice* ptLEDDevice, int iStatus )
{
	
	if(!ptLEDDevice)
	{

		return -1;
	}
	GPIO_PinState Pin_State;//���������PinState�����
	Pin_State = iStatus ? GPIO_PIN_RESET : GPIO_PIN_SET;

	
	switch (ptLEDDevice->which)
	{
		case LED_WHITE:
			HAL_GPIO_WritePin (WHITE_GPIO_Port, WHITE_Pin, Pin_State);
			break;
		case LED_BLUE:
			HAL_GPIO_WritePin (BLUE_GPIO_Port, BLUE_Pin, Pin_State);
			break;
		case LED_GREEN:
			HAL_GPIO_WritePin (GREEN_GPIO_Port, GREEN_Pin, Pin_State);
			break;
		default:
			return -1;
	}
	return 0;
	
}
