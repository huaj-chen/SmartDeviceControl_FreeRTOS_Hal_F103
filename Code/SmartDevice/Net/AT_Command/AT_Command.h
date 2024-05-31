#ifndef __AT_COMMAND_H
#define __AT_COMMAND_H
#include <string.h>
#include "Net_system.h"
#include "UART_dev.h"
#include "KAL_Time.h"

int ATInterfaceInit(void);

int ATCommandSendAndRecv(char *cmd, char *pcRecvbuf, int iTimeoutMS);

int ATCommandSend(char* cmd, int iTimeoutMS);

int ATDataRecv(unsigned char* Data,int * piLen,int iTimeoutMS);


#endif// __AT_COMMAND_H

