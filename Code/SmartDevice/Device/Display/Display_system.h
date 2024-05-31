#ifndef _DISPLAY_SYSTEM_H
#define _DISPLAY_SYSTEM_H
/*显示设备管理系统*/

#include "Display_device.h"
#include "OLED_device.h"
void AddDisplayDevices(void);

pDisplayDevice GetDisplayDevice(char *name);//根据名字获得显示设备结构体指针

#endif

