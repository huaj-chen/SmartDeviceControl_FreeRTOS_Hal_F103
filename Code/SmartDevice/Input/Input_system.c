#include "Input_system.h"


/**
 * @brief ����һ�������豸�ṹ��ָ�룬��ָ����Ϊ����ͷ
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
	ptInputdevice->pNext = g_ptInputDevices;//���豸����һ��ָ������ͷ��
	g_ptInputDevices = ptInputdevice;//����ͷ��ָ���µ��豸

}

/**
 * @brief ע�� �����豸
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-20
*/
void AddInputDevice()
{
	AddInputDeviceGPIOKey();//ע�ᰴ��Ϊ�����豸
	AddInputDeviceNet();//���������Ϊ�����豸

}


/**
 * @brief ����������豸���ó�����ʼ��
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

