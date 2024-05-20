#include "CAL_GPIO_Key.h"
#include "driver_Key.h"
void CAL_GPIOKeyInit(void)
{
	/*调用芯片相关的代码，注册中断*/
	/*对于ST芯片，调用代码*/
	KEY_GPIO_ReInit ();
	
}
