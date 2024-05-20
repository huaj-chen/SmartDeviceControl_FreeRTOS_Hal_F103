#include <config.h>
#if defined (CONFIG_SUPPORT_HAL)
	#include "deiver_OLED.h"
	#include "deiver_I2C.h"
#endif

/*为OLED构建一个displayDevice 结构体*/

static int CAL_OLEDDeviceInit(struct DisplayDevice* ptDisplayDevice)
{
	/*初始化OLED*/
#if defined (CONFIG_SUPPORT_HAL)
	//1.重新初始化I2C引脚
	I2C_GPIO_ReInit();
	//2.初始化OLED
	OLED_Init();
	return 0;
#elif 
	return FREERTOS_OLEDDeviceInit(ptDisplayDevice);
#endif

}


static void CAL_OLEDDeviceFlush(struct DisplayDevice* ptDisplayDevice)
{
	/*把g_OLEDFramebuffer的数据搬到OLED自带的显存里面*/
#if defined (CONFIG_SUPPORT_HAL)
	CAL_OLEDDeviceInit(ptDisplayDevice);
#elif 
	FREERTOS_OLEDDeviceInit(ptDisplayDevice);
#endif

}




