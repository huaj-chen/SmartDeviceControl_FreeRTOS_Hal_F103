#ifndef __LED_DEVICE_H
#define __LED_DEVICE_H


enum LED{
	LED_WHITE = 0,
	LED_BLUE,
	LED_GREEN
};

#ifndef NULL
#define NULL (void*)0
#endif

typedef struct LEDDevice{

	int which;
	int (*LEDinit)(struct LEDDevice* ptLEDDevice);
	int (*LEDcontrol)(struct LEDDevice* ptLEDDevice, int iStatus);
	void (*SetColor)(struct LEDDevice* ptLEDDevice, int iColor);
	void (*SetBrightness)(struct LEDDevice* ptLEDDevice, int iBrightness);
}LEDDevice,*pLEDDevice;


pLEDDevice GetLEDDevice(int which);



#endif// __LED_DEVICE_H

