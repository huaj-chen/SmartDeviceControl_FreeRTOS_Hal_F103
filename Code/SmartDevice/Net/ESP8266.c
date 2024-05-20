


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
	//发出AT命令：AT+CIFSR 从得到的数据里解析出IP
	/*
	+CIFSR:APIP,"192.168.4.1"
	+CIFSR:APMAC,"1a:fe:34:a5:8d:c6"
	+CIFSR:STAIP,"192.168.3.133"
	+CIFSR:STAMAC,"18:fe:34:a5:8d:c6"
	OK
	*/
	char buf[200];
	int ret;
	char *ip;//ip的位置
	int i;

	ret = ATCommandSendAndRecv("AT+CIFSR", ESP8266_DEFAULT_TIMEOUT);
	if(!ret)
	{
		//解析出IP
		ip = strstr(buf, "+CIFSR:STAIP,\"");//ip 将指向字符串的开始处的位置
		if(ip)
		{
			ip += strlen("+CIFSR:STAIP,\"");//加上这串字符的长度，指向IP开始那里
			for(i = 0; ip[i] != '\"'; i++)//从IP地址开始，遍历到双引号为止
			{
				ptDev->IP[i] = ip[i];//将这段数字放入到设备结构体中的IP
			}
			ptDev->IP[i] = '\0';//加上一个结束符
			strcpy(ip_buf, ptDev ->IP);//将IP复制到ip_buf
			return 0;
		}
	}
	return -1;
}


static int ESP8266Init(struct NETDevice *ptDev)
{
	/*选择AT命令的硬件接口*/
	ATInterfaceSelect("uart");
	/*初始化硬件接口*/
	ATInterfaceInit();
	ATCommandSend("AT+CWMODE=3", ESP8266_DEFAULT_TIMEOUT);
	ATCommandSend("AT+CIPMUX=0", ESP8266_DEFAULT_TIMEOUT);
 
}

static	int ESP8266CreatTransfer(struct NETDevice* ptDev, char* type, int iLocalPort)
{
	char cmd[100];
	//只支持UDP, AT+CIPSTART="UDP","192.168.101.118",8888,1112,2*/
	
	sprintf(cmd, "AT+CIPSTART=\"UDP\",\"192.168.101.118\",8888,%d,2", iLocalPort);
	return ATCommandSend(cmd, ESP8266_DEFAULT_TIMEOUT);
}



/****************************************************************************
*函数名称：ESP8266Connect
*功能描述：调用AT指令发送WIFI名和密码到ESP8266，建立连接
*输入参数：ptDev - 网卡设备结构体
*输入参数：SSID - WIFI名
*输入参数：password - 密码
*输出参数：无
*返回值：     	无
*修改日期			版本号			修改人			修改内容
2024/05/02		V1.0		huaj		创建
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
//函 数 名：AddNetDeviceESP8266
//功    能：注册ESP8266网卡设备
//输入参数：无
//返 回 值：pDisplayDevice
//日    期：2024/05/01
//版    本：
//==================================================================
void AddNetDeviceESP8266(void)
{
	NetDeviceRegister(&g_tESP8266NetDevice);
}




