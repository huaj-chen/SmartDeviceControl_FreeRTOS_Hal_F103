#ifndef __CAL_LED_DEVICE_H
#define __CAL_LED_DEVICE_H
#include <LED_Device.h>
int CAL_LEDDeviceInit(struct LEDDevice* ptLEDDevice);

int   CAL_LEDDeviceControl(struct LEDDevice* ptLEDDevice, int iStatus);


#endif// __CAL_LED_DEVICE_H

