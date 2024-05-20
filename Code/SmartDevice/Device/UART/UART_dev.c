#include <kal_uart_dev.h>
#include <Ring_buffer.h>
#include "UART_dev.h"


static ring_buffer g_UARTRingBuffer;//���λ������ṹ��



static int UART3ReadByte(struct UARTDevice *ptDev, char *Data)
{
    return ring_buffer_read((unsigned char*)Data, &g_UARTRingBuffer);
}


static int UART3Init(struct UARTDevice *ptDev)
{
    //��main.c���Ѿ���ʼ��UART3Ӳ��

	ring_buffer_init (&g_UARTRingBuffer);
	return 0;
}

static void UART3InvalidRecvBuf(struct UARTDevice *ptDev)
{
	g_UARTRingBuffer.pR = g_UARTRingBuffer.pW = 0;
}


/****************************************************************************
*�������ƣ�UART3Write
*��������������KAL�㣬ͨ��UART3д������
*���������ptDev - UART�ṹ��
*���������data - Ҫд�������
*���������1en - ���ݳ���
*�����������
*����ֵ��     	��
*�޸�����			�汾��			�޸���			�޸�����
2024/05/02		V1.0		huaj		����
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











