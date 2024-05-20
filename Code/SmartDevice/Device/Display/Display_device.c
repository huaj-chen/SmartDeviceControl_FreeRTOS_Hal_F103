#include "Display_device.h"
#include <GPIO_Key.h>
static pDisplayDevice g_ptDisplayDevices;//����һ������

//==================================================================
//�� �� ����DisplayDeviceRegister
//��    �ܣ�ע��һ����ʾ�豸
//�����������ʾ�豸�Ľṹ��ָ��
//�� �� ֵ��
//��    �ڣ�
//��    ����
//==================================================================
void DisplayDeviceRegister(pDisplayDevice ptDisplaydevice)
{
	ptDisplaydevice->pNext = g_ptDisplayDevices;//���豸����һ��ָ������ͷ��
	g_ptDisplayDevices = 	         ptDisplaydevice;//����ͷ��ָ���µ��豸

}


void InitDisplayDevice()//����������豸���ó�����ʼ��
{
	pDisplayDevice pDev = g_ptDisplayDevices;
	while(pDev)
	{
		pDev->InitDevice;
		pDev = pDev ->pNext; 
	}

}

//==================================================================
//�� �� ����__GetDisplayDevice����ֱ�ӵ��ã��ɱ�ĺ������ã�
//��    �ܣ��������ֻ����ʾ�ṹ��ָ��
//�������������
//�� �� ֵ��pDisplayDevice
//��    �ڣ�2024/04/29
//��    ����
//==================================================================
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


