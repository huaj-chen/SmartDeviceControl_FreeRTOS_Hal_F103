#include <stm32f1xx_hal.h>
#include "LED_Device.h"
#include "driver_LED.h"



//==================================================================
//函    数：	HAL_LEDDeviceControl
//功   	能：	用HAL库，进行LED初始化
//输入参数：	LED设备的结构体指针；LED的状态
//返 回 值：-1：错误 0：完成
//日    期：	2024/04/29
//版    本：
//==================================================================
int HAL_LEDDeviceControl(struct LEDDevice* ptLEDDevice, int iStatus )
{
	
	if(!ptLEDDevice)
	{

		return -1;
	}
	static GPIO_PinState Pin_State;//这里必须用PinState定义的
	if( iStatus == 2)//如果为状态2，则进行反转
	{
		Pin_State = !Pin_State;
	}
	else 
		Pin_State = iStatus ? GPIO_PIN_RESET : GPIO_PIN_SET;

	
	switch (ptLEDDevice->which)
	{
		case LED_1:
			HAL_GPIO_WritePin (WHITE_GPIO_Port, WHITE_Pin, Pin_State);
			break;
		case LED_2:
			HAL_GPIO_WritePin (BLUE_GPIO_Port, BLUE_Pin, Pin_State);
			break;
		default:
			return -1;
	}
	return 0;
	
}
