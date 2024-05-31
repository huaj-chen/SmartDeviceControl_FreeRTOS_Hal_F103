#include "Display_Test.h"


void Display_test(void)
{
	pDisplayDevice ptDevice;
    char *name = "OLED";

    AddDisplayDevices();
    ptDevice = GetDisplayDevice(name);
    //1.初始化设备
    ptDevice->InitDevice(ptDevice);
    //2.清除屏幕
    memset(ptDevice->FBBase, 0, ptDevice->iSize);
    //3.显示
    OLED_ShowChar(0,0,'a', 12);

    //4.flush
	OLED_Refresh();
}
