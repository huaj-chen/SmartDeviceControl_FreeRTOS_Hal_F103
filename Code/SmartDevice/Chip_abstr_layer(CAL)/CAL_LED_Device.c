#include "CAL_LED_Device.h"
#include "driver_LED.h"

int CAL_LEDDeviceInit(struct LEDDevice* ptLEDDevice)
{	
	/*����HAL*/
	/*cubeMX�Ѿ���ʼ����*/
	return 0;
}

//==================================================================
//��    ����	CAL_LEDDeviceControl
//��   	�ܣ�	���þ���оƬ����⣬����LED��ʼ��
//���������	LED�豸�Ľṹ��ָ�룻LED��״̬
//�� �� ֵ��
//��    �ڣ�	2024/04/29
//��    ����
//==================================================================
int   CAL_LEDDeviceControl(struct LEDDevice* ptLEDDevice, int iStatus)
{
	/*����HAL*/
	return HAL_LEDDeviceControl(ptLEDDevice, iStatus);
}
