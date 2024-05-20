#ifndef __UART_DEV_H
#define __UART_DEV_H

#define ATInterfaceDevice UARTDevice
#define pATInterfaceDevice pUARTDevice

typedef struct UARTDevice{
	char *name;
	int (*Init)(struct UARTDevice *p tDev);
	void (*InvalidRecvBuf)(struct UARTDevice *p tDev);
	int (*Write)(struct UARTDevice *ptDev, char* Data, int iLen);
	int (*ReadByte)(struct UARTDevice* ptDev, char* Data);//¶ÁÒ»¸ö×Ö½Ú
	
}UARTDevice, *pUARTDevice;

ATInterfaceDevice GetATInterfaceDevice(void);


#endif __UART_DEV_H

