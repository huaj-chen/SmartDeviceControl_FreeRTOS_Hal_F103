#ifndef __NET_DEVICE_H
#define __NET_DEVICE_H
#include <string.h>

#ifndef NULL
#define NULL (void*)0
#endif


/**
 * @brief �����豸�ṹ��
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
typedef struct NETDevice{
	char *name; //��������
	char IP[20];//IP��ַ
	char mac[6];
	struct NETDevice* pNext;//��һ�������豸ָ��
	int (*Init)(struct NETDevice *ptDev);//��ʼ��
	int (*Connect)(struct NETDevice *ptDev, char* SSID, char* password);//���Ӻ���
	int (*GetInfo)(struct NETDevice *ptDev, char* ip);
	int (*CreatTransfer)(struct NETDevice* ptDev, char* type, int iLocalPort);//��������
	void (*CloseTransfer)(struct NETDevice* ptDev);//�رմ���
	/*source, dest, data*/
	int (*Send)(struct NETDevice *ptDev,char* type, char* pDestIP, int iDestPort, unsigned char* Data, int iLen);
	int (*Recv)(struct NETDevice *ptDev, unsigned char* Data, int *piLen, int iTimeoutMS);
}NETDevice,*pNETDevice;


pNETDevice __GetNetDevice(char* name);

void NetDeviceRegister(pNETDevice ptNetDevice);


#endif// __NET_DEVICE_H

