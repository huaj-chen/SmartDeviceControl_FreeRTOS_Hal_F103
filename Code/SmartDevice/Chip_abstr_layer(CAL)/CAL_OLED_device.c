#include "CAL_OLED_device.h"


/*为OLED构建一个displayDevice 结构体*/

/**
 * @brief 调用HAL库进行初始化
 * @param ptDisplayDevice 
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
int CAL_OLEDDeviceInit(struct DisplayDevice* ptDisplayDevice)
{
	/*初始化OLED*/
#if defined (CONFIG_SUPPORT_HAL)
	//1.重新初始化I2C引脚
	//2.初始化OLED
	OLED_Init();
	return 0;
#elif 
	return FREERTOS_OLEDDeviceInit(ptDisplayDevice);
#endif

}


/**
 * @brief 调用刷新图像
 * @param ptDisplayDevice 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
void CAL_OLEDDeviceFlush(struct DisplayDevice* ptDisplayDevice)
{
	/*把g_OLEDFramebuffer的数据搬到OLED自带的显存里面*/
#if defined (CONFIG_SUPPORT_HAL)
	OLED_Refresh();
#elif 
	FREERTOS_OLEDDeviceInit(ptDisplayDevice);
#endif

}




