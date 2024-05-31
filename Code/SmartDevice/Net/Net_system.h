#ifndef _Net_SYSTEM_H
#define _Net_SYSTEM_H
/*网卡设备管理系统*/

#include "Net_device.h"


/**
 * @brief 注册网卡设备
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
void AddNetDevices(void);


/**
 * @brief Get the Net Device object
 * @param name 
 * @return {pNETDevice} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
pNETDevice GetNetDevice(char *name);

#endif

