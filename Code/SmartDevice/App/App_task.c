#include "App_task.h"

extern osMessageQueueId_t InputEventQueueHandle;

void TaskPrintfInfo(void *argument)
{
    uint8_t pcWriteBuffer[500];

    while (1)
    {
        // printf("=================================================\r\n");
        // printf("任务名      任务状态 优先级   剩余栈 任务序号\r\n");
        // vTaskList((char *)&pcWriteBuffer);
        // printf("%s\r\n", pcWriteBuffer);
                    
        // printf("\r\n任务名       运行计数         使用率\r\n");
        // vTaskGetRunTimeStats((char *)&pcWriteBuffer);
        // printf("%s\r\n", pcWriteBuffer);

        // vTaskDelay(500);
    }
    
    

}



/**
 * @brief RTOS任务函数，读队列并作控制
 * @param argument 
 * @version 1.0
 * @Author huaj 
 * @date 2024-06-05
*/
void App_control(void *argument)
{
    char strjson[100];
    InputEvent EVENT;//定义一个输入事件结构体，从队列中去获取数列
    osStatus_t Status;
    while(1)
    {
        //1.读队列
        Status = osMessageQueueGet(InputEventQueueHandle, &EVENT, NULL, portMAX_DELAY);
        if(osOK == Status)
        {
            printf("已读到队列,key = %d\r\n", EVENT.ikey);
            //2.转换为json格式并控制
            
            if(0 == ConvertInputEventToJson(&EVENT, strjson))
            {
                //控制设备
                SmartDeviceControl(strjson);
            }
        }
    }
}

