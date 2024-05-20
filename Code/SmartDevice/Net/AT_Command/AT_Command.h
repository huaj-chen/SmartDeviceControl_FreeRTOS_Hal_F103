#ifndef __AT_COMMAND_H
#define __AT_COMMAND_H


int ATInterfaceInit(void)

int ATCommandSendAndRecv(char *cmd, char *pcRecvbuf, int iTimeoutMS);

int ATCommandSend(char* cmd, int iTimeoutMS);

static int ATDataRecv(unsigned char* Data,int * piLen,int iTimeoutMS);


#endif// __AT_COMMAND_H

