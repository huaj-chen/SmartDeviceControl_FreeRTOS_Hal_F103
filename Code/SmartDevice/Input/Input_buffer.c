#include "Input_buffer.h"

static InputEventBuffer g_tInputBuffer;

int PutInputEvent(PInputEvent ptInputEvent)//各输入调用来放入数据
{
	int i = (g_tInputBuffer.pW + 1) % BUFFER_SIZE;//将写地址控制在大小之内，且调整大小
	/*防御性编程,防止遇到空指针*/
	if(!ptInputEvent)
	{
		return -1;
	}

	if(i != g_tInputBuffer.pR)//写地址不等于读取地址，环形缓冲区没有写满
	{
		g_tInputBuffer. buffer[g_tInputBuffer.pW] = *ptInputEvent;//将数据放入环形缓冲区
		g_tInputBuffer.pW = i;//将写地址更新到结构体里
		return 0;
	}
	return -1;
}


int GetInputEvent(PInputEvent ptInputEvent)//业务系统调用来获取数据
{

	/*防御性编程,防止遇到空指针*/
	if(!ptInputEvent)
	{
		return -1;
	}
	
	if(g_tInputBuffer.pR == g_tInputBuffer.pW)
	{
		return -1;
	}
	else
	{
		*ptInputEvent = g_tInputBuffer.buffer[g_tInputBuffer.pR];//将环形缓冲区读位置的数据给
		g_tInputBuffer.pR = (g_tInputBuffer.pR + 1) % BUFFER_SIZE;//控制读地址的大小，让其增加
		return 0;
	}
}











