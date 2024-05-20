#include <config.h>

/*为OLED构建一个displayDevice 结构体*/

static int KAL_OLEDDeviceInit(struct DisplayDevice* ptDisplayDevice)
{
	/*初始化OLED*/
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
	/*把g_OLEDFramebuffer的数据搬到OLED自带的显存里面*/
#if defined (CONFIG_NOOS)
	CAL_OLEDDeviceFlush(ptDisplayDevice);
#elif defined (CONFIG_FREERTOS)
	FREERTOS_OLEDDeviceFlush(ptDisplayDevice);
#elif defined (CONFIG_RTTHREAD)
	return RTTHREAD_OLEDDeviceFlush(ptDisplayDevice);
#endif
}




