#ifndef _Net_SYSTEM_H
#define _Net_SYSTEM_H
/*�����豸����ϵͳ*/

#include "Net_device.h"


/**
 * @brief ע�������豸
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

