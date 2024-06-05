#include "Message.h"



/**
 * @brief �������¼�ת��Ϊjson��Ϣ  {"dev":"lamp1","status":"0"}
 * @param ptEvent - �����¼�
 * @param pcJson - �ַ���
 * @return {int} 0 - �����ɹ� ��-1 - ����ʧ��
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
    else if (ptEvent->itype == INPUT_EVENT_TYPE_KEY) //�����¼�����Ϊ��������
    {
        if(ptEvent->ipressure)//�ж�ѹ���Ƿ�Ϊ1��Ϊ1��ʾ����
        {
            return -1;
        }
        if(ptEvent->ikey == K1_CODE)
            strcpy(pcJson, "{\"dev\":\"lamp1\",\"status\":\"2\"}");//״̬2 Ϊ��ת��
        else if(ptEvent->ikey == K2_CODE)
            strcpy(pcJson, "{\"dev\":\"lamp2\",\"status\":\"2\"}");//״̬2 Ϊ��ת��
        else
            return -1;
    }
    return 0;

}
