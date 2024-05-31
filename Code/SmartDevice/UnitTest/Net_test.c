#include "Net_test.h"



void Net_test()
{
	pNETDevice pNetDev;
	char ip[20];
	int port = 1234;
	// unsigned char data[200];
	// int LEN;
	InputEvent event;//����һ�������¼�

	//�ȴ��������
	KAL_Delay(2000);
	printf("Connecting\r\n");
	//ע������
	AddNetDevices ();

	pNetDev = GetNetDevice("ESP8266");

	//��ʼ��
	if (pNetDev->Init(pNetDev) == 0)
		printf("init successful\r\n");

	while(1)//��ν�������
	{


		if (pNetDev->Connect(pNetDev, "huaj", "15876864921") == 0 )//����WiFi
		{
			printf("Connect WIFI success\r\n");
			break;
		}
		else
		{
			printf("Connect WIFI error\r\n");
			KAL_Delay(1000);
		}

	}
	
	if(pNetDev ->GetInfo(pNetDev, ip) == 0)//��ȡIP
	{
		printf("Board IP = %s, port = %d\r\n", ip, port);
	}
	else 
	{
		printf("GetInfo error\r\n");
		return ;
	}

	//��������֮ǰ���Ƚ��йرմ���
	pNetDev->CloseTransfer(pNetDev);
	//��������
	if(pNetDev ->CreatTransfer(pNetDev, "UDP", port) == 0)
	{
		printf("CreatTransfer OK\r\n");
	}
	else 
	{
		printf("CreatTransfer error\r\n");
		return ;

	}
	AddInputDevice();
	InitInputDevice();	
	// while(1)
	// {
	// 	if(0 == pNetDev ->Recv(pNetDev, data, &LEN, 1000))
	// 	{
	// 		data[LEN] = '\0';
	// 		printf("GET NetData:%s\r\n",data);
	// 	}	
	// }
	while(1)
	{
		if(GetInputEvent (&event) == 0)
		{
			printf("get input event:\r\n");
			printf("type:%d\r\n",event.itype);
			printf("time:%d\r\n",event.time);
			printf("str:%s",event.str);
		}

	}
}

