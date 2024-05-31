#include "ESP8266.h"

//默认超时时间
#define ESP8266_DEFAULT_TIMEOUT 100000 //ms

/**
 * @brief 发出AT命令：AT+CIFSR 从得到的数据里解析出IP
 * @param ptDev - ESP8266网卡设备结构体指针
 * @param ip_buf - 存放IP的地址
 * @return {int} 0 - 解析成功， -1 - 解析失败
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static int ESP8266GetInfo(struct NETDevice *ptDev, char* ip_buf)
{
	//发出AT命令：AT+CIFSR 从得到的数据里解析出IP
	/*
	+CIFSR:APIP,"192.168.4.1"
	+CIFSR:APMAC,"1a:fe:34:a5:8d:c6"
	+CIFSR:STAIP,"192.168.3.133"
	+CIFSR:STAMAC,"18:fe:34:a5:8d:c6"
	OK
	*/
	char buf[200];
	int ret;//读取是否成功的标记位
	char *ip;//ip的位置
	int i;

	ret = ATCommandSendAndRecv("AT+CIFSR", buf, ESP8266_DEFAULT_TIMEOUT);
	if(!ret)//成功获取返回的信息
	{
		//查找相应字符串
		ip = strstr(buf, "+CIFSR:STAIP,\"");//ip 将指向字符串的开始处的位置
		printf("get the IP start:%c\r\n",*ip);
		if(ip)//存在该字符串
		{
			ip += strlen("+CIFSR:STAIP,\"");//加上这串字符的长度，指向IP开始那里
			for(i = 0; ip[i] != '\"'; i++)//从IP地址开始，遍历到双引号为止
			{
				ptDev->IP[i] = ip[i];//将这段数字放入到设备结构体中的IP
			}
			ptDev->IP[i] = '\0';//加上一个结束符
			strcpy(ip_buf, ptDev ->IP);//将IP复制到ip_buf
			return 0;//解析成功
		}
	}
	return -1;//解析失败
}


/**
 * @brief ESP8266网卡设备初始化
 * @param ptDev - 网卡设备结构体
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static int ESP8266Init(struct NETDevice *ptDev)
{
	// /*选择AT命令的硬件接口*/
	// ATInterfaceSelect("uart");
	/*初始化硬件接口*/
	ATInterfaceInit();
	ATCommandSend("AT+CWMODE=3", ESP8266_DEFAULT_TIMEOUT);
	ATCommandSend("AT+CIPMUX=0", ESP8266_DEFAULT_TIMEOUT);
	return 0;
}

/**
 * @brief ESP8266网卡设备创建传输
 * @param ptDev - ESP8266网卡设备
 * @param type  - UDP 或 TCP
 * @param iLocalPort 
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static	int ESP8266CreatTransfer(struct NETDevice* ptDev, char* type, int iLocalPort)
{
	char cmd[100];//指令
	//只支持UDP, AT+CIPSTART="UDP","192.168.101.118",8888,1112,2*/
	
	sprintf(cmd, "AT+CIPSTART=\"UDP\",\"192.168.1.244\",8081,%d,2", iLocalPort);
	return ATCommandSend(cmd, ESP8266_DEFAULT_TIMEOUT);
}




/**
 * @brief 调用AT指令发送WIFI名和密码到ESP8266，建立连接
 * @param ptDev - 网卡设备结构体
 * @param SSID - WIFI名
 * @param password - 密码
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
 * @brief ESP8266关闭传输
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
 * @brief 接收数据，并解析出数据
 * @param ptDev 
 * @param Data - 接收数据存放的地方
 * @param piLen - 接收的数据长度
 * @param iTimeoutMS - 超时时间
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static	int ESP8266Recv(struct NETDevice *ptDev, unsigned char* Data, int *piLen, int iTimeoutMS){
	return ATDataRecv( Data, piLen, iTimeoutMS);
}


/**
 * @brief ESP8266网卡设备结构体
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
 * @brief 注册ESP8266网卡设备
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
void AddNetDeviceESP8266(void)
{
	NetDeviceRegister(&g_tESP8266NetDevice);
}



