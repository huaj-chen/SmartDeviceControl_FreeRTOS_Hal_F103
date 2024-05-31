#include "KAL_OLED_device.h"
#include <config.h>

/*为OLED构建一个displayDevice 结构体*/

/**
 * @brief OLED初始化
 * @param ptDisplayDevice 
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
int KAL_OLEDDeviceInit(struct DisplayDevice* ptDisplayDevice)
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


/**
 * @brief OLED刷新函数
 * @param ptDisplayDevice 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
void KAL_OLEDDeviceFlush(struct DisplayDevice* ptDisplayDevice)
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




