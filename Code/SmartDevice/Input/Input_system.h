#ifndef __INPUT_SYSTEM_H
#define __INPUT_SYSTEM_H

#ifndef NULL
#define NULL (void*)0
#endif

#define TIME_T int
#define INPUT_BUF_LEN 10

typedef enum
{
	INPUT_EVENT_TYPE_KEY,
	INPUT_EVENT_TYPE_TOUCH,
	INPUT_EVENT_TYPE_NET,
	INPUT_EVENT_TYPE_STDIO,
}INPUT_EVENT_TYPE;
	
typedef struct InputEvent{
	TIME_T time; /* count++*/
	INPUT_EVENT_TYPE itype;//输入的类型
	int ix;
	int iy;
	int ikey;//按键
	int ipressure;//按压
	char str[INPUT_BUF_LEN];

}InputEvent,*PInputEvent;

typedef struct InputDevice{
	char *name;
	int (*GetInputEvent)(PInputEvent ptInputEvent);
	int (*DeviceInit)(void);
	int (*DeviceExit)(void);
	struct InputDevice *pNext;
}InputDevice,*PInputDevice;

void InputDeviceRegister(PInputDevice ptInputdevice);

void AddInputDevice(void);

void InitInputDevice(void);


#endif

