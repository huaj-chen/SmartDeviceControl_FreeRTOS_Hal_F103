#include "driver_USART.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>
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
}

int fgetc(FILE *f)
{
	volatile char c = 0;
	while(HAL_UART_Receive(&huart1, (uint8_t*)&c, 1, 3000) != HAL_OK);
	return c;
}

void EnableDebugIRQ()
{
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(USART1_IRQn);

	__HAL_UART_ENABLE_IT(&huart1, UART_IT_TC|UART_IT_RXNE);
}


void EnableUART3IRQ()
{
	HAL_NVIC_SetPriority(USART3_IRQn, 0, 1);
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

// typedef void (*NetInputProcessCallback)(char c);//定义一个网络输入处理回调函数类型
// static NetInputProcessCallback g_fNetInputProcessCallback;//定义一个函数

// void SetNetInputProcessCallback(NetInputProcessCallback func)
// {
// 	g_fNetInputProcessCallback = func;
// }


// void USART3_IRQHandler (void)
// {
// 	static ring_buffer *UART3_ringbuffer = GetUART3RingBuffer();
// 	unsigned char c = 0;

// 	if((USART3->SR &(1<<5)) != 0)//状态寄存器做判断
// 	{
// 		c = USART3->DR;//将数据寄存器的数据给C
// 		ring_buffer_write (c, uart3_ringbuffer);
// 		if(g_fNetInputProcessCallback)
// 			g_fNetInputProcessCallback(c);
// 	}
// 	HAL_UART_IRQHandler (&huart3);
// }



// /****************************************************************************
// *函数名称：USART3_SendBytes
// *功能描述：通过UART3发出多个数据
// *输入参数：buf - 数据缓冲区
// *输入参数：1en - 数据长度
// *输出参数：无
// *返回值：     	无
// *修改日期			版本号			修改人			修改内容
// 2024/05/02		V1.0		huaj		创建
// ***************************************************************************/
// void USART3_SendBytes(char *buf, int len)
// {
// 	int i;
// 	for (i = 0;i < len; i++)
// 	{
// 		while((USART3->SR & (1 << 7)) = 8);
// 		USART3->DR = buf[i];
// 	}
// }

