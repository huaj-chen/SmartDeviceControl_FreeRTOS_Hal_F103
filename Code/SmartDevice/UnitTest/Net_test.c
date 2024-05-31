#include "Net_test.h"



void Net_test()
{
	pNETDevice pNetDev;
	char ip[20];
	int port = 1234;
	unsigned char data[200];
	int LEN;

	//等待启动完毕
	KAL_Delay(2000);
	printf("Connecting\r\n");
	//注册网卡
	AddNetDevices ();

	pNetDev = GetNetDevice("ESP8266");

	//初始化
	if (pNetDev->Init(pNetDev) == 0)
		printf("init successful\r\n");

	while(1)//多次进行连接
	{


		if (pNetDev->Connect(pNetDev, "huaj", "15876864921") == 0 )//连接WiFi
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
	
	if(pNetDev ->GetInfo(pNetDev, ip) == 0)//获取IP
	{
		printf("Board IP = %s, port = %d\r\n", ip, port);
	}
	else 
	{
		printf("GetInfo error\r\n");
		return ;
	}

	//创建传输之前，先进行关闭传输
	pNetDev->CloseTransfer(pNetDev);
	//创建传输
	if(pNetDev ->CreatTransfer(pNetDev, "UDP", port) == 0)
	{
		printf("CreatTransfer OK\r\n");
	}
	else 
	{
		printf("CreatTransfer error\r\n");
		return ;

	}
		
	while(1)
	{
		if(0 == pNetDev ->Recv(pNetDev, data, &LEN, 1000))
		{
			data[LEN] = '\0';
			printf("GET NetData:%s\r\n",data);
		}	
	}
}

