#include "ESP8266.h"

//Ĭ�ϳ�ʱʱ��
#define ESP8266_DEFAULT_TIMEOUT 100000 //ms

/**
 * @brief ����AT���AT+CIFSR �ӵõ��������������IP
 * @param ptDev - ESP8266�����豸�ṹ��ָ��
 * @param ip_buf - ���IP�ĵ�ַ
 * @return {int} 0 - �����ɹ��� -1 - ����ʧ��
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
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
	int ret;//��ȡ�Ƿ�ɹ��ı��λ
	char *ip;//ip��λ��
	int i;

	ret = ATCommandSendAndRecv("AT+CIFSR", buf, ESP8266_DEFAULT_TIMEOUT);
	if(!ret)//�ɹ���ȡ���ص���Ϣ
	{
		//������Ӧ�ַ���
		ip = strstr(buf, "+CIFSR:STAIP,\"");//ip ��ָ���ַ����Ŀ�ʼ����λ��
		printf("get the IP start:%c\r\n",*ip);
		if(ip)//���ڸ��ַ���
		{
			ip += strlen("+CIFSR:STAIP,\"");//�����⴮�ַ��ĳ��ȣ�ָ��IP��ʼ����
			for(i = 0; ip[i] != '\"'; i++)//��IP��ַ��ʼ��������˫����Ϊֹ
			{
				ptDev->IP[i] = ip[i];//��������ַ��뵽�豸�ṹ���е�IP
			}
			ptDev->IP[i] = '\0';//����һ��������
			strcpy(ip_buf, ptDev ->IP);//��IP���Ƶ�ip_buf
			return 0;//�����ɹ�
		}
	}
	return -1;//����ʧ��
}


/**
 * @brief ESP8266�����豸��ʼ��
 * @param ptDev - �����豸�ṹ��
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static int ESP8266Init(struct NETDevice *ptDev)
{
	// /*ѡ��AT�����Ӳ���ӿ�*/
	// ATInterfaceSelect("uart");
	/*��ʼ��Ӳ���ӿ�*/
	ATInterfaceInit();
	ATCommandSend("AT+CWMODE=3", ESP8266_DEFAULT_TIMEOUT);
	ATCommandSend("AT+CIPMUX=0", ESP8266_DEFAULT_TIMEOUT);
	return 0;
}

/**
 * @brief ESP8266�����豸��������
 * @param ptDev - ESP8266�����豸
 * @param type  - UDP �� TCP
 * @param iLocalPort 
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static	int ESP8266CreatTransfer(struct NETDevice* ptDev, char* type, int iLocalPort)
{
	char cmd[100];//ָ��
	//ֻ֧��UDP, AT+CIPSTART="UDP","192.168.101.118",8888,1112,2*/
	
	sprintf(cmd, "AT+CIPSTART=\"UDP\",\"192.168.1.244\",8081,%d,2", iLocalPort);
	return ATCommandSend(cmd, ESP8266_DEFAULT_TIMEOUT);
}




/**
 * @brief ����ATָ���WIFI�������뵽ESP8266����������
 * @param ptDev - �����豸�ṹ��
 * @param SSID - WIFI��
 * @param password - ����
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static int ESP8266Connect(struct NETDevice *ptDev, char* SSID, char* password)
{
	char cmd[100];
	sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"", SSID, password);
	return ATCommandSend(cmd, ESP8266_DEFAULT_TIMEOUT);
}


/**
 * @brief ESP8266�رմ���
 * @param ptDev 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static void ESP8266CloseTransfer(struct NETDevice* ptDev)
{
	ATCommandSend("AT+CIPCLOSE", ESP8266_DEFAULT_TIMEOUT);
}

static	int ESP8266Send(struct NETDevice *ptDev,char* type, char* pDestIP, int iDestPort, unsigned char* Data, int iLen)
{
	return 0;
}


/**
 * @brief �������ݣ�������������
 * @param ptDev 
 * @param Data - �������ݴ�ŵĵط�
 * @param piLen - ���յ����ݳ���
 * @param iTimeoutMS - ��ʱʱ��
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static	int ESP8266Recv(struct NETDevice *ptDev, unsigned char* Data, int *piLen, int iTimeoutMS){
	return ATDataRecv( Data, piLen, iTimeoutMS);
}


/**
 * @brief ESP8266�����豸�ṹ��
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static NETDevice g_tESP8266NetDevice = {
	"ESP8266",
	"0.0.0.0",
	"0.0.0",
	NULL,
	ESP8266Init,
	ESP8266Connect,
	ESP8266GetInfo,
	ESP8266CreatTransfer,
	ESP8266CloseTransfer,
	ESP8266Send,
	ESP8266Recv
};

/**
 * @brief ע��ESP8266�����豸
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
void AddNetDeviceESP8266(void)
{
	NetDeviceRegister(&g_tESP8266NetDevice);
}



