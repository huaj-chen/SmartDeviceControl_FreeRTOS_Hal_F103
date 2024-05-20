#include "KAL_LED_Device.h"
#include "CAL_LED_Device.h"

int KAL_LEDDeviceInit(struct LEDDevice* ptLEDDevice)
{	
	/*对于FreeRTOS/裸机*/

	return CAL_LEDDeviceInit(ptLEDDevice);
	/*对于Linux*/


	/*对于RT-Thread*/

	
}

//==================================================================
//函    数：	KAL_LEDDeviceControl
//功   	能：	根据不同宏定义，进行LED初始化
//输入参数：	LED设备的结构体指针；LED的状态
//返 回 值：
//日    期：	2024/04/29
//版    本：
//==================================================================
int   KAL_LEDDeviceControl(struct LEDDevice* ptLEDDevice, int iStatus)
{
	/*对于FreeRTOS/裸机*/

	return CAL_LEDDeviceControl(ptLEDDevice, iStatus);


	/*对于Linux*/
	
	
	/*对于RT-Thread*/
}
