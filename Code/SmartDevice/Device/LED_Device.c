#include "LED_Device.h"
#include "KAL_LED_Device.h"



//==================================================================
//函    数：	LEDDeviceInit
//功   	能：	调用KAL层进行LED初始化
//输入参数：	LED设备的结构体指针；
//返 回 值：
//日    期：	2024/04/29
//版    本：
//==================================================================
static int LEDDeviceInit(struct LEDDevice* ptLEDDevice)
{	
	return KAL_LEDDeviceInit(ptLEDDevice);
}


//==================================================================
//函 数：LEDDeviceControl
//功    能：调用KAL层进行LED控制
//输入参数：LED设备的结构体指针；控制的状态
//返 回 值：
//日    期：2024/04/29
//版    本：
//==================================================================
static    int  LEDDeviceControl(struct LEDDevice* ptLEDDevice, int iStatus)
{
	return KAL_LEDDeviceControl(ptLEDDevice, iStatus);
}



//本来便已经构建好各个LED的结构体，等待被获取而使用
static LEDDevice g_tLEDDevice[] = {
	{LED_WHITE, LEDDeviceInit, LEDDeviceControl},
	{LED_BLUE, LEDDeviceInit, LEDDeviceControl},
	{LED_GREEN, LEDDeviceInit, LEDDeviceControl}
};



/**
 * @brief 调用此函数以获得具体LED的设备结构体
 * @param which 
 * @return {pLEDDevice} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-20
*/
pLEDDevice GetLEDDevice(int which)
{
	if(which >= LED_WHITE && which <= LED_GREEN)
	{
		return &g_tLEDDevice[which];
	}
	else 
		return NULL;
}


