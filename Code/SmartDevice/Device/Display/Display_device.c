#include "Display_device.h"

static pDisplayDevice g_ptDisplayDevices;//定义一个链表

/**
 * @brief 注册一个显示设备
 * @param ptDisplaydevice 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
void DisplayDeviceRegister(pDisplayDevice ptDisplaydevice)
{
	ptDisplaydevice->pNext = g_ptDisplayDevices;//新设备的下一个指向链表头部
	g_ptDisplayDevices = ptDisplaydevice;//链表头部指向新的设备

}



/**
 * @brief 把链表里的设备都拿出来初始化
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
void InitDisplayDevice()
{
	pDisplayDevice pDev = g_ptDisplayDevices;
	while(pDev)
	{
		pDev->InitDevice(pDev);
		pDev = pDev ->pNext; 
	}

}


/**
 * @brief 根据名字获得显示结构体指针（不直接调用，由别的函数调用）
 * @param name 
 * @return {pDisplayDevice} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-04-29
*/
pDisplayDevice __GetDisplayDevice(char *name)//根据名字获得显示设备结构体指针
{
	pDisplayDevice pTmp = g_ptDisplayDevices;
	while(pTmp)
	{
		if(strcmp(pTmp->name, name) == 0)
		{
			return pTmp;
		}
		else
		{
			pTmp = pTmp ->pNext;
		}
	}
	return NULL;
}


