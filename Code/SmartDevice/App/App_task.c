#include "App_task.h"

extern osMessageQueueId_t InputEventQueueHandle;

void TaskPrintfInfo(void *argument)
{
    uint8_t pcWriteBuffer[500];

    while (1)
    {
        // printf("=================================================\r\n");
        // printf("������      ����״̬ ���ȼ�   ʣ��ջ �������\r\n");
        // vTaskList((char *)&pcWriteBuffer);
        // printf("%s\r\n", pcWriteBuffer);
                    
        // printf("\r\n������       ���м���         ʹ����\r\n");
        // vTaskGetRunTimeStats((char *)&pcWriteBuffer);
        // printf("%s\r\n", pcWriteBuffer);

        // vTaskDelay(500);
    }
    
    

}



/**
 * @brief RTOS�������������в�������
 * @param argument 
 * @version 1.0
 * @Author huaj 
 * @date 2024-06-05
*/
void App_control(void *argument)
{
    char strjson[100];
    InputEvent EVENT;//����һ�������¼��ṹ�壬�Ӷ�����ȥ��ȡ����
    osStatus_t Status;
    while(1)
    {
        //1.������
        Status = osMessageQueueGet(InputEventQueueHandle, &EVENT, NULL, portMAX_DELAY);
        if(osOK == Status)
        {
            printf("�Ѷ�������,key = %d\r\n", EVENT.ikey);
            //2.ת��Ϊjson��ʽ������
            
            if(0 == ConvertInputEventToJson(&EVENT, strjson))
            {
                //�����豸
                SmartDeviceControl(strjson);
            }
        }
    }
}

