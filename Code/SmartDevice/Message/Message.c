#include "Message.h"



/**
 * @brief 将输入事件转换为json消息  {"dev":"lamp1","status":"0"}
 * @param ptEvent - 输入事件
 * @param pcJson - 字符串
 * @return {int} 0 - 解析成功 ，-1 - 解析失败
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-31
*/
int ConvertInputEventToJson(PInputEvent ptEvent, char* pcJson)
{
    if(ptEvent->itype == INPUT_EVENT_TYPE_NET)
    {
        strcpy(pcJson, ptEvent->str);
        return 0;
    }
    else if (ptEvent->itype == INPUT_EVENT_TYPE_KEY) //输入事件类型为按键输入
    {
        if(ptEvent->ipressure)//判断压力是否为1，为1表示按下
        {
            return -1;
        }
        if(ptEvent->ikey == K1_CODE)
            strcpy(pcJson, "{\"dev\":\"lamp1\",\"status\":\"2\"}");//状态2 为反转灯
        else if(ptEvent->ikey == K2_CODE)
            strcpy(pcJson, "{\"dev\":\"lamp2\",\"status\":\"2\"}");//状态2 为反转灯
        else
            return -1;
    }
    return 0;

}
