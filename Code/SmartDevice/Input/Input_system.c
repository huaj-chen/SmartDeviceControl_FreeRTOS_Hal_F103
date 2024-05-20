#include "Input_system.h"
#include <GPIO_Key.h>
static PInputDevice g_ptInputDevices;//����һ������

//==================================================================
//�� �� InputDeviceRegister
//��    �ܣ�ע�������豸
//��������������豸�Ľṹ��ָ��
//�� �� ֵ����
//��    �ڣ�2024/04/29
//��    ����
//==================================================================
void InputDeviceRegister(PInputDevice ptInputdevice)
{
	ptInputdevice->pNext = g_ptInputDevices;//���豸����һ��ָ������ͷ��
	g_ptInputDevices = 	         ptInputdevice;//����ͷ��ָ���µ��豸

}

//==================================================================
//�� �� AddInputDevice
//��    �ܣ�ע���������豸
//���������
//�� �� ֵ��
//��    �ڣ�
//��    ����
//==================================================================
void AddInputDevice()
{
	AddInputDeviceGPIOKey();
}



void InitInputDevice()//����������豸���ó�����ʼ��
{
	PInputDevice pDev = g_ptInputDevices;
	while(pDev)
	{
		pDev ->DeviceInit();
		pDev = pDev ->pNext; 
	}
}

