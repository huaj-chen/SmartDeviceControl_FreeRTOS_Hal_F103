#include <Net_system.h>



void Net_test()
{
	pNETDevice pNetDev;
	char ip[20];
	int port = 1234;
	char data[200];
	int LEN;
	AddNetDevices ();

	pNetDev = GetDisplayDevice ("esp8266");

	pNetDev->Init(pNetDev);
	if (pNetDev->Connect(pNetDev, "huaj", "15876864921") == 0 )
		printf("Connect WIFI success\r\n");
	else
		printf("Connect WIFI error\r\n");
		return;

	if(pNetDev ->GetInfo(pNetDev, ip) == 0)
	{
		printf("Board IP = %s, port = %d\r\n", ip, port);
	}
	else 
		
		printf("GetInfo error\r\n");
		return ;
	if(pNetDev ->CreatTransfer(pNetDev, "UDP", port) == 0)
	{
		printf("CreatTransfer OK\r\n");
	}
	else 
		printf("CreatTransfer error\r\n");
		return ;

	while(1)
	{
		if(0 = pNetDev ->Recv(pNetDev, data, &LEN, 100))
		{
			data[LEN] = '\0';
			printf("GET NetData:%s\r\n",data);
		}	
	}
}

