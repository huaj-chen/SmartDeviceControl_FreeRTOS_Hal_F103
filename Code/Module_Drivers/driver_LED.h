#ifndef __DRIVER_LED_H
#define __DRIVER_LED_H
#include <LED_Device.h>

#define WHITE_GPIO_Port GPIOG
#define BLUE_GPIO_Port GPIOG
#define GREEN_GPIO_Port GPIOG

#define WHITE_Pin GPIO_PIN_6
#define BLUE_Pin GPIO_PIN_7
#define GREEN_Pin GPIO_PIN_8

int HAL_LEDDeviceControl(struct LEDDevice* ptLEDDevice, int iStatus );


#endif// __DRIVER_LED_H

