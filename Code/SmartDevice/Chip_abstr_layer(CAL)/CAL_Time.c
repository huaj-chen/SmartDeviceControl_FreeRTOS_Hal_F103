#include "CAL_Time.h"

TIME_T     CAL_GetTime(void)
{
	//tick中断里面，count++
	return HAL_GetTick();
}


/****************************************************************************
*函数名称：CAL_Delay
*功能描述：延时
*输入参数：DelayMS-延时时间，单位：ms
*输出参数：无
*返回值：     	无
*修改日期			版本号			修改人			修改内容
2024/04//26		V1.0		huaj		创建
***************************************************************************/
void CAL_Delay(unsigned int DelayMS)
{
	HAL_Delay (DelayMS);
}

