#include "driver_USART.h"

//������Ϣ���ͳ���
void DebugPrint(const char *str)
{
	uint16_t len = strlen(str);
	HAL_UART_Transmit(&huart1, (uint8_t*)str, len, 300);
}

//��ȡ������Ϣ�ŵ�str
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
//  * @brief ʹ��debug ���ڷ����ж� �� �����ж�
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
 * @brief ʹ��UART3�����жϣ���Ϊ�����������ݵĴ���
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
//  * @brief ����1�жϴ������������ݷ��뻷�λ�����
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

static NetInputProcessCallback g_fNetInputProcessCallback;//����һ������ָ�����

/**
 * @brief ������������ص�����
 * @param func - NetInputProcessCallback����һ��ָ������
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-31
*/
void SetNetInputProcessCallback(NetInputProcessCallback func)
{
	g_fNetInputProcessCallback = func;
}

/**
 * @brief USART3 �����жϣ����������豸��������Ϣ�����뻷�λ�����
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

	if((USART3->SR &(1<<5)) != 0)//״̬�Ĵ������ж�
	{
		c = USART3->DR;//�����ݼĴ��������ݸ�C
		ring_buffer_write(c, UART3_ringbuffer);//�����ݷŵ����λ�����
		if(g_fNetInputProcessCallback)//�����������������ص���������ִ�иú�������������д���
			g_fNetInputProcessCallback(c);
	}
	HAL_UART_IRQHandler(&huart3);
}




/**
 * @brief ͨ��UART3����������ݣ�ʹ�ò�ѯ��ʽ
 * @param buf - ���ݻ�����
 * @param len - ���ݳ���
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
void USART3_SendBytes(char *buf, int len)
{
	int i;
	for (i = 0;i < len; i++)
	{
		while((USART3->SR & (1 << 7)) == 0);//��ⷢ�ͼĴ���Ϊ 1 - ��ʾ���У����Խ�����һ������
		USART3->DR = buf[i];
	}
}

