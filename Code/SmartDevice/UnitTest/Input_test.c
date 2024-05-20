#include "Input_system.h"
#include "Input_buffer.h"
#include <stdio.h>



void Input_test(void)
{
	InputEvent event;
	AddInputDevice();
	InitInputDevice();
	while(1)
	{
		if(GetInputEvent (&event) == 0)
		{
			printf("get input event:\r\n");
			printf("type:%d\r\n",event.itype);
			printf("time:%d\r\n",event.time);
			printf("Key:%d\r\n",event.ikey);
			printf("pressure:%d\r\n",event.ipressure);
		}

	}
}
