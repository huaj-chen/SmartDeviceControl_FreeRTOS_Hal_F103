#include <config.h>

/*ΪOLED����һ��displayDevice �ṹ��*/

static int KAL_OLEDDeviceInit(struct DisplayDevice* ptDisplayDevice)
{
	/*��ʼ��OLED*/
#if defined (CONFIG_NOOS)
	return CAL_OLEDDeviceInit(ptDisplayDevice);
#elif defined (CONFIG_FREERTOS)
	return FREERTOS_OLEDDeviceInit(ptDisplayDevice);
#elif defined (CONFIG_RTTHREAD)
	return RTTHREAD_OLEDDeviceInit(ptDisplayDevice);
#endif

}


static void KAL_OLEDDeviceFlush(struct DisplayDevice* ptDisplayDevice)
{
	/*��g_OLEDFramebuffer�����ݰᵽOLED�Դ����Դ�����*/
#if defined (CONFIG_NOOS)
	CAL_OLEDDeviceFlush(ptDisplayDevice);
#elif defined (CONFIG_FREERTOS)
	FREERTOS_OLEDDeviceFlush(ptDisplayDevice);
#elif defined (CONFIG_RTTHREAD)
	return RTTHREAD_OLEDDeviceFlush(ptDisplayDevice);
#endif
}




