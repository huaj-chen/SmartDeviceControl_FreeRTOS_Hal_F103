#ifndef __DRIVER_USART_H
#define __DRIVER_USART_H

#include "main.h"
#include "usart.h"
#include "Ring_buffer.h"
#include "UART_dev.h"
#include <string.h>
#include <stdio.h>

typedef void (*NetInputProcessCallback)(char c);//定义一个网络输入处理回调 函数类型

void SetNetInputProcessCallback(NetInputProcessCallback func);

void DebugPrint(const char *str);
void DebugGet(char* str, uint16_t len);
void USART3_SendBytes(char *buf, int len);
void EnableDebugIRQ(void);
void EnableUART3IRQ(void);



#endif //__DRIVER_USART_H


