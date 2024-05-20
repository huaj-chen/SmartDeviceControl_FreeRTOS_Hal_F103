#include <stm32f1xx_hal.h>

#include <stdio.h>
#include "led_test.h"
#include "LED_Device.h"


void LED_test(void)
{
	
	pLEDDevice p1 = GetLEDDevice(LED_WHITE);
	pLEDDevice p2 = GetLEDDevice(LED_BLUE);
	pLEDDevice p3 = GetLEDDevice(LED_GREEN);

	p1 ->LEDinit(p1);
	p2 ->LEDinit(p2);
	p3 ->LEDinit(p3);

	while(1)
	{	
		p1->LEDcontrol(p1,1);
		p2->LEDcontrol(p2,1);
//		p1->LEDcontrol(p1,1);
		HAL_Delay (500);
		p1->LEDcontrol(p1,0);
		p2->LEDcontrol(p2,0);
//		p1->LEDcontrol(p1,0);
		HAL_Delay (500);
	}
}
