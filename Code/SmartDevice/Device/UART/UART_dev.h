#ifndef __UART_DEV_H
#define __UART_DEV_H
#include "KAL_UART_dev.h"
#include <Ring_buffer.h>

#define ATInterfaceDevice UARTDevice
#define pATInterfaceDevice pUARTDevice


/**
 * @brief �����豸�ṹ��
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
typedef struct UARTDevice{
	char *name;
	int (*Init)(struct UARTDevice *ptDev);
	void (*InvalidRecvBuf)(struct UARTDevice *ptDev);
	int (*Write)(struct UARTDevice *ptDev, char* Data, int iLen);
	int (*ReadByte)(struct UARTDevice* ptDev, char* Data);//��һ���ֽ�	
}UARTDevice, *pUARTDevice;

pATInterfaceDevice GetATInterfaceDevice(char *name);

ring_buffer* GetUART3RingBuffer(void);

#endif //__UART_DEV_H

