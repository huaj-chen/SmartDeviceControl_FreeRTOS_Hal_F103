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
 * @brief �����¼��ṹ��
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-20
*/
typedef struct InputEvent{
	TIME_T time; //ʱ��
	INPUT_EVENT_TYPE itype;//���������
	int ix;
	int iy;
	int ikey;//����
	int ipressure;//��ѹ
	char str[INPUT_BUF_LEN];//������ַ���
}InputEvent,*PInputEvent;


/**
 * @brief �����豸�ṹ��
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
typedef struct InputDevice{
	char *name;//�����豸����
	int (*GetInputEvent)(PInputEvent ptInputEvent);//���ĳ�������豸�ṹ��
	int (*DeviceInit)(void);//��ʼ��
	int (*DeviceExit)(void);//�˳�
	struct InputDevice *pNext;//��һ�������豸�ṹ�������
}InputDevice,*PInputDevice;



void InputDeviceRegister(PInputDevice ptInputdevice);

void AddInputDevice(void);

void InitInputDevice(void);


#endif

