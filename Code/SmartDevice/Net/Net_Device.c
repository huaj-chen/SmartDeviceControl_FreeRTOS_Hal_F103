#include "Net_Device.h"


pNETDevice g_ptNetDevices;//网卡结构体链表

/**
 * @brief 对网卡进行注册，添加到链表
 * @param ptNetDevice - 网卡设备的结构体指针
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
void NetDeviceRegister(pNETDevice ptNetDevice)
{
	ptNetDevice->pNext = g_ptNetDevices;
	g_ptNetDevices = ptNetDevice;
}



/**
 * @brief 根据名字获得网卡设备结构体，供net_system调用
 * @param name 
 * @return {pNETDevice} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-06-01
*/
pNETDevice __GetNetDevice(char* name)
{
	pNETDevice pTmp = g_ptNetDevices;
	while(pTmp)
	{
		if(strcmp(pTmp->name, name) == 0)
		{
			return pTmp;	
		}
			
	}
}


