#include "Net_Device.h"


pNetDevice g_ptNetDevices;

//==================================================================
//��    ����	NetDeviceRegister
//��   	�ܣ�	����������ע�ᣬ��ӵ�����
//���������	�����豸�Ľṹ��ָ�룻
//�� �� ֵ��
//��    �ڣ�	2024/05/01
//��    ����
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


