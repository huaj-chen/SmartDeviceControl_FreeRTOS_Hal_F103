#include <CAL_Time.h>
#include "KAL_Time.h"

TIME_T     KAL_GetTime(void)
{
	return CAL_GetTime();
}

/****************************************************************************
*函数名称：KAL_Delay
*功能描述：延时
*输入参数：DelayMS-延时时间，单位：ms
*输出参数：无
*返回值：     	无
*修改日期			版本号			修改人			修改内容
2024/04//26		V1.0		huaj		创建
***************************************************************************/
void KAL_Delay(unsigned int DelayMS)
{
	CAL_Delay (DelayMS);
}


