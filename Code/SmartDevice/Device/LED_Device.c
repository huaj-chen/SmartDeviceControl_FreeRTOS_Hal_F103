#include "LED_Device.h"
#include "KAL_LED_Device.h"



//==================================================================
//��    ����	LEDDeviceInit
//��   	�ܣ�	����KAL�����LED��ʼ��
//���������	LED�豸�Ľṹ��ָ�룻
//�� �� ֵ��
//��    �ڣ�	2024/04/29
//��    ����
//==================================================================
static int LEDDeviceInit(struct LEDDevice* ptLEDDevice)
{	
	return KAL_LEDDeviceInit(ptLEDDevice);
}


//==================================================================
//�� ����LEDDeviceControl
//��    �ܣ�����KAL�����LED����
//���������LED�豸�Ľṹ��ָ�룻���Ƶ�״̬
//�� �� ֵ��
//��    �ڣ�2024/04/29
//��    ����
//==================================================================
static    int  LEDDeviceControl(struct LEDDevice* ptLEDDevice, int iStatus)
{
	return KAL_LEDDeviceControl(ptLEDDevice, iStatus);
}



//�������Ѿ������ø���LED�Ľṹ�壬�ȴ�����ȡ��ʹ��
static LEDDevice g_tLEDDevice[] = {
	{LED_WHITE, LEDDeviceInit, LEDDeviceControl},
	{LED_BLUE, LEDDeviceInit, LEDDeviceControl},
	{LED_GREEN, LEDDeviceInit, LEDDeviceControl}
};



/**
 * @brief ���ô˺����Ի�þ���LED���豸�ṹ��
 * @param which 
 * @return {pLEDDevice} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-20
*/
pLEDDevice GetLEDDevice(int which)
{
	if(which >= LED_WHITE && which <= LED_GREEN)
	{
		return &g_tLEDDevice[which];
	}
	else 
		return NULL;
}


