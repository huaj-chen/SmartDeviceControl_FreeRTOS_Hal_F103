#ifndef _DISPLAY_DEVICE_H
#define _DISPLAY_DEVICE_H
/*Ϊ������ʾ�豸�������һ�㣬�Թ���������ʾ�豸*/

typedef struct DisplayDevice{
	char* name;
	void* FBBase;
	int iXres;//x�����С
	int iYres;//y�����С
	int iBpp;//ÿ�����ص�λ��С
	int (*InitDevice)(struct DisplayDevice* ptDisplayDevice);//Ӳ����ʼ��
	void (*Flush)(struct DisplayDevice* ptDisplayDevice);//������ˢ�뵽Ӳ�����Դ�
	struct DisplayDevice* pNext;//��ʾ�豸��ָ��
}DisplayDevice,*pDisplayDevice;


pDisplayDevice __GetDisplayDevice(char *name);//�������ֻ����ʾ�豸�ṹ��ָ��



#endif

