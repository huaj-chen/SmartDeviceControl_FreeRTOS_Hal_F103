#include <kal_uart_dev.h>
#include <Ring_buffer.h>
#include "UART_dev.h"


static ring_buffer g_UARTRingBuffer;//环形缓冲区结构体



static int UART3ReadByte(struct UARTDevice *ptDev, char *Data)
{
    return ring_buffer_read((unsigned char*)Data, &g_UARTRingBuffer);
}


static int UART3Init(struct UARTDevice *ptDev)
{
    //在main.c中已经初始化UART3硬件

	ring_buffer_init (&g_UARTRingBuffer);
	return 0;
}

static void UART3InvalidRecvBuf(struct UARTDevice *ptDev)
{
	g_UARTRingBuffer.pR = g_UARTRingBuffer.pW = 0;
}


/****************************************************************************
*函数名称：UART3Write
*功能描述：调用KAL层，通过UART3写入数据
*输入参数：ptDev - UART结构体
*输入参数：data - 要写入的数据
*输入参数：1en - 数据长度
*输出参数：无
*返回值：     	无
*修改日期			版本号			修改人			修改内容
2024/05/02		V1.0		huaj		创建
***************************************************************************/
static void UART3Write(struct UARTDevice *ptDev, char* Data, int iLen)
{
	return KAL_UART3Write(Data, iLen);  
}


static UARTDevice g_tUART3Device = {
    "uart3",
    UART3Init,
    UART3InvalidRecvBuf,
    UART3Write,
    UART3ReadByte
};











