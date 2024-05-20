#ifndef __KAL_LED_DEVICE_H
#define __KAL_LED_DEVICE_H
#include <LED_Device.h>
int KAL_LEDDeviceInit(struct LEDDevice* ptLEDDevice);

int   KAL_LEDDeviceControl(struct LEDDevice* ptLEDDevice, int iStatus);


#endif// __KAL_LED_DEVICE_H

