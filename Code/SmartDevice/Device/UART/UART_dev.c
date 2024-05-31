#include "UART_dev.h"


static ring_buffer g_UART3_RingBuffer;//���λ������ṹ��


/**
 * @brief �ӻ��λ�������ȡһ���ֽڵ�����
 * @param ptDev 
 * @param Data - ��Ŷ�ȡ������
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
 * @brief UART3��ʼ��,��main.c���Ѿ���ʼ��UART3Ӳ��,�������ʼ�����λ�����
 * @param ptDev 
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static int UART3Init(struct UARTDevice *ptDev)
{
    //��main.c���Ѿ���ʼ��UART3Ӳ��

	ring_buffer_init (&g_UART3_RingBuffer);
	return 0;
}

/**
 * @brief ��ս��ջ���
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
 * @brief ����KAL�㣬ͨ��UART3д������
 * @param ptDev - UART�ṹ��
 * @param Data - Ҫд�������
 * @param iLen - ���ݳ���
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static int UART3Write(struct UARTDevice *ptDev, char* Data, int iLen)
{
	return KAL_UART3Write(Data, iLen);  
}


/**
 * @brief ����UART3�ṹ��
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




