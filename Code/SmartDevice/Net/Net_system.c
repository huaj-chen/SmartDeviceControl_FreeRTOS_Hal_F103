#include "Net_system.h"



/**
 * @brief ע���������豸��������뵽������
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
void AddNetDevices()
{
	AddNetDeviceESP8266();
}


/**
 * @brief Get the Net Device object
 * @param name 
 * @return {pNETDevice} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
pNETDevice GetNetDevice(char *name)
{
	return __GetNetDevice(name);
}


