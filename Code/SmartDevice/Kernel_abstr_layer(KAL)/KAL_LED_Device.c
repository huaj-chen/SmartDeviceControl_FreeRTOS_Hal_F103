#include "KAL_LED_Device.h"
#include "CAL_LED_Device.h"

int KAL_LEDDeviceInit(struct LEDDevice* ptLEDDevice)
{	
	/*����FreeRTOS/���*/

	return CAL_LEDDeviceInit(ptLEDDevice);
	/*����Linux*/


	/*����RT-Thread*/

	
}

//==================================================================
//��    ����	KAL_LEDDeviceControl
//��   	�ܣ�	���ݲ�ͬ�궨�壬����LED��ʼ��
//���������	LED�豸�Ľṹ��ָ�룻LED��״̬
//�� �� ֵ��
//��    �ڣ�	2024/04/29
//��    ����
//==================================================================
int   KAL_LEDDeviceControl(struct LEDDevice* ptLEDDevice, int iStatus)
{
	/*����FreeRTOS/���*/

	return CAL_LEDDeviceControl(ptLEDDevice, iStatus);


	/*����Linux*/
	
	
	/*����RT-Thread*/
}
