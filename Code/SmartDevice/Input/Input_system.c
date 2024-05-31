#include "Input_system.h"


/**
 * @brief 定义一个输入设备结构体指针，此指针作为链表头
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-20
*/
static PInputDevice g_ptInputDevices;


/**
 * @brief 
 * @param ptInputdevice 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-20
*/
void InputDeviceRegister(PInputDevice ptInputdevice)
{
	ptInputdevice->pNext = g_ptInputDevices;//新设备的下一个指向链表头部
	g_ptInputDevices = ptInputdevice;//链表头部指向新的设备

}

/**
 * @brief 注册 输入设备
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-20
*/
void AddInputDevice()
{
	AddInputDeviceGPIOKey();//注册按键为输入设备
	AddInputDeviceNet();//将网卡添加为输入设备

}


/**
 * @brief 把链表里的设备都拿出来初始化
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-20
*/
void InitInputDevice()
{
	PInputDevice pDev = g_ptInputDevices;
	while(pDev)
	{
		pDev ->DeviceInit();
		pDev = pDev ->pNext; 
	}
}

