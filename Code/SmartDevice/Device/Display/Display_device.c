#include "Display_device.h"
#include <GPIO_Key.h>
static pDisplayDevice g_ptDisplayDevices;//定义一个链表

//==================================================================
//函 数 名：DisplayDeviceRegister
//功    能：注册一个显示设备
//输入参数：显示设备的结构体指针
//返 回 值：
//日    期：
//版    本：
//==================================================================
void DisplayDeviceRegister(pDisplayDevice ptDisplaydevice)
{
	ptDisplaydevice->pNext = g_ptDisplayDevices;//新设备的下一个指向链表头部
	g_ptDisplayDevices = 	         ptDisplaydevice;//链表头部指向新的设备

}


void InitDisplayDevice()//把链表里的设备都拿出来初始化
{
	pDisplayDevice pDev = g_ptDisplayDevices;
	while(pDev)
	{
		pDev->InitDevice;
		pDev = pDev ->pNext; 
	}

}

//==================================================================
//函 数 名：__GetDisplayDevice（不直接调用，由别的函数调用）
//功    能：根据名字获得显示结构体指针
//输入参数：名字
//返 回 值：pDisplayDevice
//日    期：2024/04/29
//版    本：
//==================================================================
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


