#ifndef _CAL_OLED_DEVICE_H
#define _CAL_OLED_DEVICE_H
#include "Display_device.h"
#include <config.h>
#if defined (CONFIG_SUPPORT_HAL)
	#include "driver_OLED.h"
	#include "driver_I2C.h"
#endif

int CAL_OLEDDeviceInit(struct DisplayDevice* ptDisplayDevice);


void CAL_OLEDDeviceFlush(struct DisplayDevice* ptDisplayDevice);





#endif//_CAL_OLED_DEVICE_H

