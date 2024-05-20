#include "GPIO_Key.h"
#include "Input_system.h"
#include "Input_buffer.h"
#include <KAL_GPIO_Key.h>

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

void AddInputDeviceGPIOKey(void)
{
	InputDeviceRegister(&g_tKeyDevice);
}

