#ifndef __NET_DEVICE_H
#define __NET_DEVICE_H
#include <string.h>

#ifndef NULL
#define NULL (void*)0
#endif


/**
 * @brief 网卡设备结构体
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
typedef struct NETDevice{
	char *name; //网卡名称
	char IP[20];//IP地址
	char mac[6];
	struct NETDevice* pNext;//下一个网卡设备指针
	int (*Init)(struct NETDevice *ptDev);//初始化
	int (*Connect)(struct NETDevice *ptDev, char* SSID, char* password);//连接函数
	int (*GetInfo)(struct NETDevice *ptDev, char* ip);
	int (*CreatTransfer)(struct NETDevice* ptDev, char* type, int iLocalPort);//创建传输
	void (*CloseTransfer)(struct NETDevice* ptDev);//关闭传输
	/*source, dest, data*/
	int (*Send)(struct NETDevice *ptDev,char* type, char* pDestIP, int iDestPort, unsigned char* Data, int iLen);
	int (*Recv)(struct NETDevice *ptDev, unsigned char* Data, int *piLen, int iTimeoutMS);
}NETDevice,*pNETDevice;


pNETDevice __GetNetDevice(char* name);

void NetDeviceRegister(pNETDevice ptNetDevice);


#endif// __NET_DEVICE_H

