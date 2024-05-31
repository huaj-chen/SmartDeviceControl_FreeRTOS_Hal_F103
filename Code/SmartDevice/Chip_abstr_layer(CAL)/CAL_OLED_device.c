#include "CAL_OLED_device.h"


/*ΪOLED����һ��displayDevice �ṹ��*/

/**
 * @brief ����HAL����г�ʼ��
 * @param ptDisplayDevice 
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
int CAL_OLEDDeviceInit(struct DisplayDevice* ptDisplayDevice)
{
	/*��ʼ��OLED*/
#if defined (CONFIG_SUPPORT_HAL)
	//1.���³�ʼ��I2C����
	//2.��ʼ��OLED
	OLED_Init();
	return 0;
#elif 
	return FREERTOS_OLEDDeviceInit(ptDisplayDevice);
#endif

}


/**
 * @brief ����ˢ��ͼ��
 * @param ptDisplayDevice 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
void CAL_OLEDDeviceFlush(struct DisplayDevice* ptDisplayDevice)
{
	/*��g_OLEDFramebuffer�����ݰᵽOLED�Դ����Դ�����*/
#if defined (CONFIG_SUPPORT_HAL)
	OLED_Refresh();
#elif 
	FREERTOS_OLEDDeviceInit(ptDisplayDevice);
#endif

}




