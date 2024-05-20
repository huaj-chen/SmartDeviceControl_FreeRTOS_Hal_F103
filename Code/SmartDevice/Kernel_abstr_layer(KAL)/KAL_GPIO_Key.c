#include "KAL_GPIO_Key.h"
#include <CAL_GPIO_Key.h>

void KAL_GPIOKeyInit(void)
{
	/*对于裸机：注册中断*/
	CAL_GPIOKeyInit();


	
	/*对于RTOS,创建任务*/

}
