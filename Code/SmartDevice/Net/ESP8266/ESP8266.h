#ifndef _ESP_8266_H
#define _ESP_8266_H
#include "Net_Device.h"
#include "AT_Command.h"

void AddDisplayDevices(void);

pNETDevice GetNetDevice(char *name);

#endif

