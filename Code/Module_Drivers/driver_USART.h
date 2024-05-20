#ifndef __DRIVER_USART_H
#define __DRIVER_USART_H


#include <stm32f1xx_hal.h>

void DebugPrint(const char *str);
void DebugGet(char* str, uint16_t len);



#endif //__DRIVER_USART_H


