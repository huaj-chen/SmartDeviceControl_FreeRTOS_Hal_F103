#include "OLED_device.h"



/*显示设备结构体下的一层，构建结构体里相关OLED的函数*/
//这里的OLED 是 128*64
/*128*64 bits , 1024 bytes*/
static unsigned char g_OLEDFramebuffer[1024];

 
/**
 * @brief OLED初始化
 * @param ptDisplayDevice 
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
static int OLEDDeviceInit(struct DisplayDevice* ptDisplayDevice)
{
	/*初始化OLED*/
	return KAL_OLEDDeviceInit(ptDisplayDevice);
}


/**
 * @brief 刷新OLED图像
 * @param ptDisplayDevice 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
static void OLEDDeviceFlush(struct DisplayDevice* ptDisplayDevice)
{
	/*把g_OLEDFramebuffer的数据搬到OLED自带的显存里面*/
	KAL_OLEDDeviceFlush(ptDisplayDevice);
}




/*为OLED构建一个displayDevice 结构体*/
static DisplayDevice g_tOLEDDevice = {
	"OLED",
	g_OLEDFramebuffer,
	128,
	64,
	1,
	128*64*1/8,
	OLEDDeviceInit,
	OLEDDeviceFlush
};


/**
 * @brief 注册OLED为显示设备
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
void AddDisplayDeviceOLED(void)
{

	DisplayDeviceRegister(&g_tOLEDDevice);
}


