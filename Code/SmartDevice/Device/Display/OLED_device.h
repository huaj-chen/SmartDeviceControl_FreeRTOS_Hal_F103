#ifndef _OLED_DEVICE_H
#define _OLED_DEVICE_H

typedef struct DisplayDevice{
	char* name;
	void* FBBase;
	int iXres;//x方向大小
	int iYres;//y方向大小
	int iBpp;//每个像素的位大小
	int (*InitDevice)(struct DisplayDevice* ptDisplayDevice);
	void (*Flush)(struct DisplayDevice* ptDisplayDevice);

}DisplayDevice,*pDisplayDevice;



pDisplayDevice GetDisplayDevice(int which);

void AddDisplayDeviceOLED(void);


#endif

