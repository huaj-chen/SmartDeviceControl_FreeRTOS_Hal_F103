#include "Net_Device.h"


pNetDevice g_ptNetDevices;

//==================================================================
//函    数：	NetDeviceRegister
//功   	能：	对网卡进行注册，添加到链表
//输入参数：	网卡设备的结构体指针；
//返 回 值：
//日    期：	2024/05/01
//版    本：
//==================================================================
void NetDeviceRegister(pNETDevice ptNetDevice)
{
	ptNetDevice->pNext = g_ptNetDevices;
	g_ptNetDevices = ptNetDevice;
}





pNetDevice __GetNetDevice(char* name)
{
	pNetDevice pTmp = g_ptNetDevices;
	while(ptmp)
	{
		if(strcmp(pTmp->name, name) == 0)
		{
			return pTmp;	
		}
		else
			
	}
}


