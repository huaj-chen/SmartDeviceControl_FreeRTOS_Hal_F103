#include "CAL_LED_Device.h"
#include "driver_LED.h"

int CAL_LEDDeviceInit(struct LEDDevice* ptLEDDevice)
{	
	/*对于HAL*/
	/*cubeMX已经初始化了*/
	return 0;
}

//==================================================================
//函    数：	CAL_LEDDeviceControl
//功   	能：	调用具体芯片具体库，进行LED初始化
//输入参数：	LED设备的结构体指针；LED的状态
//返 回 值：
//日    期：	2024/04/29
//版    本：
//==================================================================
int   CAL_LEDDeviceControl(struct LEDDevice* ptLEDDevice, int iStatus)
{
	/*对于HAL*/
	return HAL_LEDDeviceControl(ptLEDDevice, iStatus);
}
