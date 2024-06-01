#include "Net_input.h"


//��Ϊ�������ݵ�ö��
enum AT_STATUS{
		INIT_STATUS,
		LEN_STATUS,
		DATA_STATUS
};
static enum AT_STATUS g_status = INIT_STATUS;//��ʼΪ��ʼ��״̬


//�����ж�ʱ�����ݴ�ŵ�buf
static char g_ESP8266DataBuffer[INPUT_BUF_LEN];
static int g_DataBuffIndex = 0;//�����������ݵ�����
static int g_DataLen = 0;//���յ������ݳ���





/**
 * @brief �Խ��յ������ݽ��н�����Ȼ���ϱ�Ϊ�����¼�
 * @param c - ����Ľ����ĵ����ֽ�
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-31
*/
static void ESP8266DataProcessCallback(char c)
{
	
	//1.��������
	InputEvent event;//����һ�������¼�
	char *buf = g_ESP8266DataBuffer;
	int i = g_DataBuffIndex;
	int m;//���㳤�ȵ�����
	buf[i] = c;//�����ݷŵ�buf��
	g_DataBuffIndex++;//������1����ȡ��һ���ֽ�
	
	//2.����+IPD,n:XXXXXXxxxx

	switch(g_status)//����״̬����������
	{
		case INIT_STATUS:
		{
			if(buf[0] != '+')//�����ȡ���ķǡ�+����ͷ��ֱ�Ӷ���
			{
				g_DataBuffIndex = 0;
			}
			if(i == 4)//��ȡ5���ֽ����ݣ�iΪ4
			{
				if(strncmp(buf, "+IPD,", 5) == 0)//�ҵ����ǰ׺
				{
					g_status = LEN_STATUS;//����������ݳ���״̬
				}
				g_DataBuffIndex = 0;//��ȡ��5���ֽڣ��㽫index��0�����¶�ȡ
			}
			break;
		}
		case LEN_STATUS:
		{
			if(buf[i] == ':')
			{
				//���㳤��
				for(m = 0; m < i; m++)//��ȡ':'֮ǰ�� 
				{
					g_DataLen = g_DataLen* 10 + buf[m] - '0';//���յ������ݵĳ���
				}
				g_status = DATA_STATUS;//�����������״̬
				g_DataBuffIndex = 0;//��ȡ�����֣��㽫index��0�����¶�ȡ
					
			}
			break;
		}
		case DATA_STATUS:
		{
			if(g_DataBuffIndex == g_DataLen)//��ʾ���յ����ݣ������ݳ���������������
			{
				//����InputEvent���ϱ�
				event.time = KAL_GetTime();//�����¼���ʱ��
				event.itype = INPUT_EVENT_TYPE_NET;//�����¼�������
				strncpy(event.str, buf, g_DataLen);//��buf�е����ݷŵ������¼���ȥ
				event.str[g_DataLen] = '\0';//�����ݵ�ĩβ���Ͻ�����
				PutInputEvent(&event);//���¼��ŵ����λ�����
				
				g_status = INIT_STATUS;//�ָ�״̬Ϊ��ʼ
				g_DataBuffIndex = 0;
				g_DataLen = 0;
			}
			break;
		}
	}

}

/**
 * @brief ΪUART�жϺ�������һ������ص�������������ص����� ȥ��������
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-31
*/
static int ESP8266NetInputInit()
{
	//��UART�жϺ����ṩһ���ص�����
	SetNetInputProcessCallback(ESP8266DataProcessCallback);
	return 0;
}


/*Ϊesp8266�����豸����һ��InputDevice*/
static InputDevice g_tNetInputDevice = {
	"ESP8266",
	NULL,
	ESP8266NetInputInit,
	NULL,
};





void AddInputDeviceNet()
{
	InputDeviceRegister(&g_tNetInputDevice);
}

