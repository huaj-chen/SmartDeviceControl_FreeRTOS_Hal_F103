#include "Display_device.h"

/*显示设备结构体下的一层，构建结构体里相关OLED的函数*/
//这里的OLED 是 128*64

static int OLEDDeviceInit(struct DisplayDevice* ptDisplayDevice)
{
	/*初始化OLED*/
	return KAL_OLEDDeviceInit(ptDisplayDevice);
}


static void OLEDDeviceFlush(struct DisplayDevice* ptDisplayDevice)
{
	/*把g_OLEDFramebuffer的数据搬到OLED自带的显存里面*/
	return KAL_OLEDDeviceFlush(ptDisplayDevice);
}

/*128*64 bits , 1024 bytes*/
static unsigned char g_OLEDFramebuffer[1024];


/*为OLED构建一个displayDevice 结构体*/
static DisplayDevice g_tOLEDDevice = {
	"OLED",
	g_OLEDFramebuffer,
	128,
	64,
	1,
	OLEDDeviceInit,
	OLEDDeviceFlush
};


//==================================================================
//函 数 AddDisplayDeviceOLED
//功    能：将OLED注册到显示设备系统当中去
//输入参数：无
//返 回 值：无
//日    期：
//版    本：
//==================================================================
void AddDisplayDeviceOLED(void)
{

	DisplayDeviceRegister(&g_tOLEDDevice);
}


