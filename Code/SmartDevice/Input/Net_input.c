#include "Net_input.h"
#include "Input_system.h"
#include "Input_buffer.h"

enum AT_STATUS{
		INIT_STATUS,
		LEN_STATUS,
		DATA_STATUS
};

static char g_ESP8266DataBuffer[INPUT_BUF_LEN];

static enum AT_STATUS g_status = INIT_STATUS;
static int g_DataBuffIndex = 0;//����
static int g_DataLen = 0;//����


static int ESP8266NetInputInit()
{
	//��UART�жϺ����ṩһ���ص�����
	
	SetNetInputProcessCallback(ESP8266DataProcessCallback);
	return 0;
}


static void ESP8266DataProcessCallback(char c)
{
	//��������
	InputEvent event;
	char *buf = g_ESP8266DataBuffer;
	int i = g_DataBuffIndex;
	int m;//���㳤�ȵ�����
	buf[i] = c;
	g_DataBuffIndex++;
	
	//����+IPD,n:XXXXXXxxxx

	switch(g_status)
	{
		case INIT_STATUS:
		{
			if(i == 4)//��ȡ4/5������
			{
				if(strncmp(buf, "+IPD," 5) == 0)
				{
					g_status = LEN_STATUS;
				}

					g_DataBuffIndex = 0;
			}
			break;
		}
		case LEN_STATUS:
		{
			if(buf[i] = ':')
			{
				//���㳤��
				for(m = 0; m < i; m++)//��ȡ':'֮ǰ�� 
				{
					g_DataLen = g_DataLen* 10 + buf[m] - '0';//
				}
				g_status = DATA_STATUS;
				g_DataBuffIndex = 0;
					
			}
			break;
		}
		case DATA_STATUS:
		{
			if(g_DataBuffIndex == g_DataLen)
			{
				//����������

				event.time = KAL_GetTime();//Kal
				event.itype = INPUT_EVENT_TYPE_NET;
				strncpy(event.str, buf, g_DataLen);
				event.str[g_DataLen] = '\0';
				PutInputEvent (&event);
				//����InputEvent���ϱ�

				//�ָ�״̬
				g_status = INIT_STATUS;
				g_DataBuffIndex = 0;
				g_DataLen = 0;
			}
			break;

	return 0;
}

/*ΪGPIO����һ��InputDevice*/
static InputDevice g_tNetInputDevice = {
	"ESP8266",
	NULL,
	ESP8266NetInputInit,
	NULL,
};

void AddInputDeviceNet(void)
{

	InputDeviceRegister(&g_tNetInputDevice);
}

