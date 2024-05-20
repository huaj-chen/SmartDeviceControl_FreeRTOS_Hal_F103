#include <config.h>
#if defined (CONFIG_SUPPORT_HAL)
	#include "deiver_OLED.h"
	#include "deiver_I2C.h"
#endif

/*ΪOLED����һ��displayDevice �ṹ��*/

static int CAL_OLEDDeviceInit(struct DisplayDevice* ptDisplayDevice)
{
	/*��ʼ��OLED*/
#if defined (CONFIG_SUPPORT_HAL)
	//1.���³�ʼ��I2C����
	I2C_GPIO_ReInit();
	//2.��ʼ��OLED
	OLED_Init();
	return 0;
#elif 
	return FREERTOS_OLEDDeviceInit(ptDisplayDevice);
#endif

}


static void CAL_OLEDDeviceFlush(struct DisplayDevice* ptDisplayDevice)
{
	/*��g_OLEDFramebuffer�����ݰᵽOLED�Դ����Դ�����*/
#if defined (CONFIG_SUPPORT_HAL)
	CAL_OLEDDeviceInit(ptDisplayDevice);
#elif 
	FREERTOS_OLEDDeviceInit(ptDisplayDevice);
#endif

}




