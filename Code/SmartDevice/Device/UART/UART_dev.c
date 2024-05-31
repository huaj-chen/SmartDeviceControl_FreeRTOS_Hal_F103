#include "UART_dev.h"


static ring_buffer g_UART3_RingBuffer;//环形缓冲区结构体


/**
 * @brief 从环形缓冲区读取一个字节的数据
 * @param ptDev 
 * @param Data - 存放读取的数据
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static int UART3ReadByte(struct UARTDevice *ptDev, char *Data)
{
    return ring_buffer_read((unsigned char*)Data, &g_UART3_RingBuffer);
}


/**
 * @brief UART3初始化,在main.c中已经初始化UART3硬件,在这里初始化环形缓冲区
 * @param ptDev 
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static int UART3Init(struct UARTDevice *ptDev)
{
    //在main.c中已经初始化UART3硬件

	ring_buffer_init (&g_UART3_RingBuffer);
	return 0;
}

/**
 * @brief 清空接收缓存
 * @param ptDev 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static void UART3InvalidRecvBuf(struct UARTDevice *ptDev)
{
	g_UART3_RingBuffer.pR = g_UART3_RingBuffer.pW = 0;
}



/**
 * @brief 调用KAL层，通过UART3写入数据
 * @param ptDev - UART结构体
 * @param Data - 要写入的数据
 * @param iLen - 数据长度
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static int UART3Write(struct UARTDevice *ptDev, char* Data, int iLen)
{
	return KAL_UART3Write(Data, iLen);  
}


/**
 * @brief 构建UART3结构体
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static UARTDevice g_tUART3Device = {
    "uart3",
    UART3Init,
    UART3InvalidRecvBuf,
    UART3Write,
    UART3ReadByte
};



pATInterfaceDevice GetATInterfaceDevice(char *name)
{
    return &g_tUART3Device;
}


ring_buffer* GetUART3RingBuffer(void)
{
    return &g_UART3_RingBuffer;
}




