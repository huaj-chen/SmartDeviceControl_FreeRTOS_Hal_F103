#include "GPIO_Key.h"


static int GPIO_KeyInit(void)
{
	KAL_GPIOKeyInit();
	return 0;
}

/*ΪGPIO����һ��InputDevice*/
static InputDevice g_tKeyDevice = {
	"GPIO_Key",
	NULL,
	GPIO_KeyInit,
	NULL,
};


/**
 * @brief �� GPIOKey ע��Ϊ�����豸
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-20
*/
void AddInputDeviceGPIOKey(void)
{
	InputDeviceRegister(&g_tKeyDevice);
}

