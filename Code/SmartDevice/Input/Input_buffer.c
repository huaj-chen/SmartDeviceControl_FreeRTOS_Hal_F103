#include "Input_buffer.h"

static InputEventBuffer g_tInputBuffer;

int PutInputEvent(PInputEvent ptInputEvent)//�������������������
{
	int i = (g_tInputBuffer.pW + 1) % BUFFER_SIZE;//��д��ַ�����ڴ�С֮�ڣ��ҵ�����С
	/*�����Ա��,��ֹ������ָ��*/
	if(!ptInputEvent)
	{
		return -1;
	}

	if(i != g_tInputBuffer.pR)//д��ַ�����ڶ�ȡ��ַ�����λ�����û��д��
	{
		g_tInputBuffer. buffer[g_tInputBuffer.pW] = *ptInputEvent;//�����ݷ��뻷�λ�����
		g_tInputBuffer.pW = i;//��д��ַ���µ��ṹ����
		return 0;
	}
	return -1;
}


int GetInputEvent(PInputEvent ptInputEvent)//ҵ��ϵͳ��������ȡ����
{

	/*�����Ա��,��ֹ������ָ��*/
	if(!ptInputEvent)
	{
		return -1;
	}
	
	if(g_tInputBuffer.pR == g_tInputBuffer.pW)
	{
		return -1;
	}
	else
	{
		*ptInputEvent = g_tInputBuffer.buffer[g_tInputBuffer.pR];//�����λ�������λ�õ����ݸ�
		g_tInputBuffer.pR = (g_tInputBuffer.pR + 1) % BUFFER_SIZE;//���ƶ���ַ�Ĵ�С����������
		return 0;
	}
}











