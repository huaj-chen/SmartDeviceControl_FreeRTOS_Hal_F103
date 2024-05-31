#include "Display_device.h"

static pDisplayDevice g_ptDisplayDevices;//����һ������

/**
 * @brief ע��һ����ʾ�豸
 * @param ptDisplaydevice 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
void DisplayDeviceRegister(pDisplayDevice ptDisplaydevice)
{
	ptDisplaydevice->pNext = g_ptDisplayDevices;//���豸����һ��ָ������ͷ��
	g_ptDisplayDevices = ptDisplaydevice;//����ͷ��ָ���µ��豸

}



/**
 * @brief ����������豸���ó�����ʼ��
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
 * @brief �������ֻ����ʾ�ṹ��ָ�루��ֱ�ӵ��ã��ɱ�ĺ������ã�
 * @param name 
 * @return {pDisplayDevice} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-04-29
*/
pDisplayDevice __GetDisplayDevice(char *name)//�������ֻ����ʾ�豸�ṹ��ָ��
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


