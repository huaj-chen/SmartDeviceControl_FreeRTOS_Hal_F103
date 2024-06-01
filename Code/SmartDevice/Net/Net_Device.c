#include "Net_Device.h"


pNETDevice g_ptNetDevices;//�����ṹ������

/**
 * @brief ����������ע�ᣬ��ӵ�����
 * @param ptNetDevice - �����豸�Ľṹ��ָ��
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
 * @brief �������ֻ�������豸�ṹ�壬��net_system����
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


