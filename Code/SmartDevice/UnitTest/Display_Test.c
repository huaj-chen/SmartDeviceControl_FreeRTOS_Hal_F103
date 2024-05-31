#include "Display_Test.h"


void Display_test(void)
{
	pDisplayDevice ptDevice;
    char *name = "OLED";

    AddDisplayDevices();
    ptDevice = GetDisplayDevice(name);
    //1.��ʼ���豸
    ptDevice->InitDevice(ptDevice);
    //2.�����Ļ
    memset(ptDevice->FBBase, 0, ptDevice->iSize);
    //3.��ʾ
    OLED_ShowChar(0,0,'a', 12);

    //4.flush
	OLED_Refresh();
}
