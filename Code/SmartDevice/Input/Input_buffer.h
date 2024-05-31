#ifndef _INPUT_BUFFER_H
#define _INPUT_BUFFER_H

#include "Input_system.h"

#define InputEvent_BUFFER_SIZE 10 //环形缓冲区的大小


//环形缓冲区存放输入事件
typedef struct
{
	InputEvent buffer[InputEvent_BUFFER_SIZE];/*缓冲区空间*/
	volatile unsigned int pW;//写地址
	volatile unsigned int pR;//读地址
} InputEventBuffer;

int GetInputEvent(PInputEvent ptInputEvent);//业务系统调用来获取数据

int PutInputEvent(PInputEvent ptInputEvent);//各输入调用来放入数据



#endif 
