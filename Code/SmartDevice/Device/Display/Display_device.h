#ifndef _DISPLAY_DEVICE_H
#define _DISPLAY_DEVICE_H
/*Ϊ������ʾ�豸�������һ�㣬�Թ���������ʾ�豸*/
#include <string.h>



/**
 * @brief ��ʾ�豸�ṹ��
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
typedef struct DisplayDevice{
	char* name;//�豸����
	void* FBBase;//�Դ�ռ�
	int iXres;//x�����С
	int iYres;//y�����С
	int iBpp;//ÿ�����ص�λ��С
	int iSize;//�Դ�ռ��С
	int (*InitDevice)(struct DisplayDevice* ptDisplayDevice);//Ӳ����ʼ��
	void (*Flush)(struct DisplayDevice* ptDisplayDevice);//������ˢ�뵽Ӳ�����Դ� 
	struct DisplayDevice* pNext;//��ʾ�豸��ָ��
}DisplayDevice,*pDisplayDevice;


pDisplayDevice __GetDisplayDevice(char *name);//�������ֻ����ʾ�豸�ṹ��ָ��

void DisplayDeviceRegister(pDisplayDevice ptDisplaydevice);

void InitDisplayDevice(void);




#endif

