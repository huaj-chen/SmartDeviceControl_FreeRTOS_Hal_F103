#include "driver_USART.h"

//将该信息发送出来
void DebugPrint(const char *str)
{
	uint16_t len = strlen(str);
	HAL_UART_Transmit(&huart1, (uint8_t*)str, len, 300);
}

//获取串口信息放到str
void DebugGet(char* str, uint16_t len)
{
	while(HAL_UART_Receive(&huart1, (uint8_t*)str, len, 300) != HAL_OK);
}

int fputc(int ch, FILE *f)
{
	while(HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 3000) != HAL_OK);
	return 0;
}

int fgetc(FILE *f)
{
	volatile char c = 0;
	while(HAL_UART_Receive(&huart1, (uint8_t*)&c, 1, 3000) != HAL_OK);
	return c;
}


// /**
//  * @brief 使能debug 串口发送中断 和 接收中断
//  * @version 1.0
//  * @Author huaj 
//  * @date 2024-05-30
// */
// void EnableDebugIRQ()
// {
// 	HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
// 	HAL_NVIC_EnableIRQ(USART1_IRQn);

// 	__HAL_UART_ENABLE_IT(&huart1, UART_IT_TC|UART_IT_RXNE);
// }


/**
 * @brief 使能UART3接收中断，作为接收网卡数据的串口
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
void EnableUART3IRQ()
{
	HAL_NVIC_SetPriority(USART3_IRQn, 6, 0);
	HAL_NVIC_EnableIRQ(USART3_IRQn);

	__HAL_UART_ENABLE_IT(&huart3,UART_IT_RXNE);
}

// /**
//  * @brief 串口1中断处理函数，将数据放入环形缓冲区
//  * @version 1.0
//  * @Author huaj 
//  * @date 2024-05-20
// */
// void USART1_IRQHandler (void)
// {
// 	unsigned char c = 0;

// 	if((USART1->SR &(1<<5)) != 0)
// 	{
// 		c = USART1->DR;
// 		ring_buffer_write(c, uart1_ringbuffer);
// 	}
// 	HAL_UART_IRQHandler (&huart1);
// }

static NetInputProcessCallback g_fNetInputProcessCallback;//定义一个函数指针变量

/**
 * @brief 设置网络输入回调函数
 * @param func - NetInputProcessCallback传入一个指针类型
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-31
*/
void SetNetInputProcessCallback(NetInputProcessCallback func)
{
	g_fNetInputProcessCallback = func;
}

/**
 * @brief USART3 接收中断，接收网卡设备反馈的信息，放入环形缓冲区
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
void USART3_IRQHandler (void)
{
	static ring_buffer* UART3_ringbuffer;
	static int count = 0;
	if(count == 0)
	{
		UART3_ringbuffer = GetUART3RingBuffer();
		count++;
	}
	unsigned char c = 0;

	if((USART3->SR &(1<<5)) != 0)//状态寄存器做判断
	{
		c = USART3->DR;//将数据寄存器的数据给C
		ring_buffer_write(c, UART3_ringbuffer);//将数据放到环形缓冲区
		if(g_fNetInputProcessCallback)//如果设置了网络输入回调函数，则执行该函数，对输入进行处理
			g_fNetInputProcessCallback(c);
	}
	HAL_UART_IRQHandler(&huart3);
}




/**
 * @brief 通过UART3发出多个数据，使用查询方式
 * @param buf - 数据缓冲区
 * @param len - 数据长度
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
void USART3_SendBytes(char *buf, int len)
{
	int i;
	for (i = 0;i < len; i++)
	{
		while((USART3->SR & (1 << 7)) == 0);//检测发送寄存器为 1 - 表示空闲，可以进行下一个发送
		USART3->DR = buf[i];
	}
}

