#ifndef __CAL_Time_H
#define __CAL_Time_H

#include <Input_system.h>
#include "stm32f1xx_hal.h"

TIME_T     CAL_GetTime(void);
void CAL_Delay(unsigned int DelayMS);


#endif    // __CAL_Time_H

