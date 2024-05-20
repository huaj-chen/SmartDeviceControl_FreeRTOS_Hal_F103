#include "Input_system.h"
#include <GPIO_Key.h>
static PInputDevice g_ptInputDevices;//定义一个链表

//==================================================================
//函 数 InputDeviceRegister
//功    能：注册输入设备
//输入参数：输入设备的结构体指针
//返 回 值：无
//日    期：2024/04/29
//版    本：
//==================================================================
void InputDeviceRegister(PInputDevice ptInputdevice)
{
	ptInputdevice->pNext = g_ptInputDevices;//新设备的下一个指向链表头部
	g_ptInputDevices = 	         ptInputdevice;//链表头部指向新的设备

}

//==================================================================
//函 数 AddInputDevice
//功    能：注册多个输入设备
//输入参数：
//返 回 值：
//日    期：
//版    本：
//==================================================================
void AddInputDevice()
{
	AddInputDeviceGPIOKey();
}



void InitInputDevice()//把链表里的设备都拿出来初始化
{
	PInputDevice pDev = g_ptInputDevices;
	while(pDev)
	{
		pDev ->DeviceInit();
		pDev = pDev ->pNext; 
	}
}

