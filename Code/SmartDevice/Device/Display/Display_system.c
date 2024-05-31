#include "Display_system.h"






/**
 * @brief ע������ʾ�豸��������뵽������
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-23
*/
void AddDisplayDevices()
{
	AddDisplayDeviceOLED();//ע��OLED
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


