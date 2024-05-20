#ifndef _DISPLAY_DEVICE_H
#define _DISPLAY_DEVICE_H
/*为所有显示设备抽象出的一层，以管理所有显示设备*/

typedef struct DisplayDevice{
	char* name;
	void* FBBase;
	int iXres;//x方向大小
	int iYres;//y方向大小
	int iBpp;//每个像素的位大小
	int (*InitDevice)(struct DisplayDevice* ptDisplayDevice);//硬件初始化
	void (*Flush)(struct DisplayDevice* ptDisplayDevice);//将数据刷入到硬件的显存
	struct DisplayDevice* pNext;//显示设备的指针
}DisplayDevice,*pDisplayDevice;


pDisplayDevice __GetDisplayDevice(char *name);//根据名字获得显示设备结构体指针



#endif

