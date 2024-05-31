#ifndef _INPUT_BUFFER_H
#define _INPUT_BUFFER_H

#include "Input_system.h"

#define InputEvent_BUFFER_SIZE 10 //���λ������Ĵ�С


//���λ�������������¼�
typedef struct
{
	InputEvent buffer[InputEvent_BUFFER_SIZE];/*�������ռ�*/
	volatile unsigned int pW;//д��ַ
	volatile unsigned int pR;//����ַ
} InputEventBuffer;

int GetInputEvent(PInputEvent ptInputEvent);//ҵ��ϵͳ��������ȡ����

int PutInputEvent(PInputEvent ptInputEvent);//�������������������



#endif 
