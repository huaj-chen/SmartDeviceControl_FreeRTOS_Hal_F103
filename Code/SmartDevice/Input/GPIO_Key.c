#include "GPIO_Key.h"


static int GPIO_KeyInit(void)
{
	KAL_GPIOKeyInit();
	return 0;
}

/*为GPIO构建一个InputDevice*/
static InputDevice g_tKeyDevice = {
	"GPIO_Key",
	NULL,
	GPIO_KeyInit,
	NULL,
};


/**
 * @brief 将 GPIOKey 注册为输入设备
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-20
*/
void AddInputDeviceGPIOKey(void)
{
	InputDeviceRegister(&g_tKeyDevice);
}

