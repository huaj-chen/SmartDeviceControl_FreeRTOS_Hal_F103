#ifndef __APP_TASK_H_
#define __APP_TASK_H_
#include <stdint.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os2.h" 
#include "Input_system.h"
#include "App.h"

void TaskPrintfInfo(void *argument);
void App_control(void *argument);
#endif


