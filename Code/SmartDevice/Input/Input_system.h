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

/**
 * @brief 输入事件结构体
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-20
*/
typedef struct InputEvent{
	TIME_T time; //时间
	INPUT_EVENT_TYPE itype;//输入的类型
	int ix;
	int iy;
	int ikey;//按键
	int ipressure;//按压
	char str[INPUT_BUF_LEN];//输入的字符串
}InputEvent,*PInputEvent;


/**
 * @brief 输入设备结构体
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
typedef struct InputDevice{
	char *name;//输入设备名称
	int (*GetInputEvent)(PInputEvent ptInputEvent);//获得某个输入设备结构体
	int (*DeviceInit)(void);//初始化
	int (*DeviceExit)(void);//退出
	struct InputDevice *pNext;//下一个输入设备结构体的名字
}InputDevice,*PInputDevice;



void InputDeviceRegister(PInputDevice ptInputdevice);

void AddInputDevice(void);

void InitInputDevice(void);


#endif

