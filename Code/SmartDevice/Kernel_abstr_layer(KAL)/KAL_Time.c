#include <CAL_Time.h>
#include "KAL_Time.h"

TIME_T     KAL_GetTime(void)
{
	return CAL_GetTime();
}

/****************************************************************************
*�������ƣ�KAL_Delay
*������������ʱ
*���������DelayMS-��ʱʱ�䣬��λ��ms
*�����������
*����ֵ��     	��
*�޸�����			�汾��			�޸���			�޸�����
2024/04//26		V1.0		huaj		����
***************************************************************************/
void KAL_Delay(unsigned int DelayMS)
{
	CAL_Delay (DelayMS);
}


