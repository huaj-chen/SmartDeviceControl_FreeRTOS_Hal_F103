#ifndef __NET_DEVICE_H
#define __NET_DEVICE_H


#ifndef NULL
#define NULL (void*)0
#endif

typedef struct NETDevice{
	char *name;
	char IP[20];
	char mac[6];
	struct NETDevice* pNext;
	int (*Init)(struct NETDevice *ptDev);
	int (*Connect)(struct NETDevice *ptDev, char* SSID, char* password);
	int (*GetInfo)(struct NETDevice *ptDev, char* ip);
	int (*CreatTransfer)(struct NETDevice* ptDev, char* type, int iLocalPort);
	void (*DisConnect)(struct NETDevice* ptDev);
	/*source, dest, data*/
	int (*Send)(struct NETDevice *ptDev,char* type, char* pDestIP, int iDestPort, unsighed char* Data, int iLen);
	int (*Recv)(struct NETDevice *ptDev, unsigned char* Data, int *piLen, int iTimeoutMS);
}NETDevice,*pNETDevice;


pNETDevice __GetNetDevice(char* name);



#endif// __NET_DEVICE_H

