#ifndef _OLED_DEVICE_H
#define _OLED_DEVICE_H

typedef struct DisplayDevice{
	char* name;
	void* FBBase;
	int iXres;//x�����С
	int iYres;//y�����С
	int iBpp;//ÿ�����ص�λ��С
	int (*InitDevice)(struct DisplayDevice* ptDisplayDevice);
	void (*Flush)(struct DisplayDevice* ptDisplayDevice);

}DisplayDevice,*pDisplayDevice;



pDisplayDevice GetDisplayDevice(int which);

void AddDisplayDeviceOLED(void);


#endif

