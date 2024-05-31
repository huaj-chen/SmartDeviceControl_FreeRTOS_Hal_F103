#include "Display_system.h"






/**
 * @brief 注册多个显示设备，将其加入到链表中
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-23
*/
void AddDisplayDevices()
{
	AddDisplayDeviceOLED();//注册OLED
}



/**
 * @brief Get the Display Device object
 * @param name 
 * @return {pDisplayDevice} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-23
*/
pDisplayDevice GetDisplayDevice(char *name)
{
	return __GetDisplayDevice(name);
}


