


#define ESP8266_DEFAULT_TIMEOUT 10 //ms
static NETDevice g_tESP8266NetDevice = {
	"ESP8266",
	"0.0.0.0",
	{0.0.0.0.0.0},
	NULL,
	ESP8266Init,
	ESP8266Connect,
	ESP8266GetInfo,
	ESP8266CreatTransfer,
	ESP8266DisConnect,
	ESP8266Send,
	ESP8266Recv
};



static int ESP8266GetInfo(struct NETDevice *ptDev, char* ip_buf)
{
	//����AT���AT+CIFSR �ӵõ��������������IP
	/*
	+CIFSR:APIP,"192.168.4.1"
	+CIFSR:APMAC,"1a:fe:34:a5:8d:c6"
	+CIFSR:STAIP,"192.168.3.133"
	+CIFSR:STAMAC,"18:fe:34:a5:8d:c6"
	OK
	*/
	char buf[200];
	int ret;
	char *ip;//ip��λ��
	int i;

	ret = ATCommandSendAndRecv("AT+CIFSR", ESP8266_DEFAULT_TIMEOUT);
	if(!ret)
	{
		//������IP
		ip = strstr(buf, "+CIFSR:STAIP,\"");//ip ��ָ���ַ����Ŀ�ʼ����λ��
		if(ip)
		{
			ip += strlen("+CIFSR:STAIP,\"");//�����⴮�ַ��ĳ��ȣ�ָ��IP��ʼ����
			for(i = 0; ip[i] != '\"'; i++)//��IP��ַ��ʼ��������˫����Ϊֹ
			{
				ptDev->IP[i] = ip[i];//��������ַ��뵽�豸�ṹ���е�IP
			}
			ptDev->IP[i] = '\0';//����һ��������
			strcpy(ip_buf, ptDev ->IP);//��IP���Ƶ�ip_buf
			return 0;
		}
	}
	return -1;
}


static int ESP8266Init(struct NETDevice *ptDev)
{
	/*ѡ��AT�����Ӳ���ӿ�*/
	ATInterfaceSelect("uart");
	/*��ʼ��Ӳ���ӿ�*/
	ATInterfaceInit();
	ATCommandSend("AT+CWMODE=3", ESP8266_DEFAULT_TIMEOUT);
	ATCommandSend("AT+CIPMUX=0", ESP8266_DEFAULT_TIMEOUT);
 
}

static	int ESP8266CreatTransfer(struct NETDevice* ptDev, char* type, int iLocalPort)
{
	char cmd[100];
	//ֻ֧��UDP, AT+CIPSTART="UDP","192.168.101.118",8888,1112,2*/
	
	sprintf(cmd, "AT+CIPSTART=\"UDP\",\"192.168.101.118\",8888,%d,2", iLocalPort);
	return ATCommandSend(cmd, ESP8266_DEFAULT_TIMEOUT);
}



/****************************************************************************
*�������ƣ�ESP8266Connect
*��������������ATָ���WIFI�������뵽ESP8266����������
*���������ptDev - �����豸�ṹ��
*���������SSID - WIFI��
*���������password - ����
*�����������
*����ֵ��     	��
*�޸�����			�汾��			�޸���			�޸�����
2024/05/02		V1.0		huaj		����
***************************************************************************/
static	int ESP8266Connect(struct NETDevice *ptDev, char* SSID, char* password)
{
	char cmd[100];
	sprintf(cmd, "AT+CWJAP=\"%s\", \"%s\"", SSID, password);
	return ATCommandSend(cmd, ESP8266_DEFAULT_TIMEOUT);
	
}
static	void ESP8266DisConnect(struct NETDevice* ptDev)
{
	return ATCommandSend("AT+CIPCLOSE", ESP8266_DEFAULT_TIMEOUT);
}

static	int ESP8266Send(struct NETDevice *ptDev,char* type, char* pDestIP, int iDestPort, unsighed char* Data, int iLen)
{
	return 0;
}
static	int ESP8266Recv(struct NETDevice *ptDev, unsigned char* Data, int *piLen, int iTimeoutMS){
	return ATDataRecv(ptDev, Data, piLen, iTimeoutMS);
}


//==================================================================
//�� �� ����AddNetDeviceESP8266
//��    �ܣ�ע��ESP8266�����豸
//�����������
//�� �� ֵ��pDisplayDevice
//��    �ڣ�2024/05/01
//��    ����
//==================================================================
void AddNetDeviceESP8266(void)
{
	NetDeviceRegister(&g_tESP8266NetDevice);
}




