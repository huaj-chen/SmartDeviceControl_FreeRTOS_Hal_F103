#include <UART_dev.h>
#include "Net_Device.h"

#define ATINTERFACE_TIMEOUT 10

static pATInterfaceDevice g_ptATIntfDev;//定义了一个AT命令发送设备的结构体指针

//==================================================================
//函    数：	isReturnOK
//功   	能：	判断字符串里面有没有：“OK\r\n”
//输入参数：	字符串；长度
//返 回 值：
//日    期：	2024/05/02
//版    本：
//==================================================================
static int isReturnOK(char* buf, int len)
{
	//判断字符串里面有没有：“OK\r\n”
	buf[len] = '\0';//在后面加上\0结束符
	return strstr(buf, "OK\r\n");
}

static int isReturnERROR(char* buf, int len)
{
	//判断字符串里面有没有：“ERROR\r\n”
	buf[len] = '\0';
	return strstr(buf, "ERROR\r\n");
}


/****************************************************************************
*函数名称：ATInterfaceInit
*功能描述：AT命令设备发送结构体初始化
*输入参数：无
*输出参数：无
*返回值：     	无
*修改日期			版本号			修改人			修改内容
2024/05/02		V1.0		huaj		创建
***************************************************************************/
int ATInterfaceInit(void)
{
	g_ptATIntfDev = GetATInterfaceDevice();
	g_ptATIntfDev->Init(g_ptATIntfDev);
}



ATInterfaceSelect("uart")
{
	g
}



/****************************************************************************
*函数名称：ATCommandSend
*功能描述：调用AT命令设备发送结构体
*输入参数：cmd - 命令
*输入参数：iTimeoutMS - 超时时间
*输出参数：无
*返回值：     	无
*修改日期			版本号			修改人			修改内容
2024/05/02		V1.0		huaj		创建
***************************************************************************/
int ATCommandSend(char* cmd, int iTimeoutMS)
{
	char buf[50];
	int i = 0;
	int pre;
	int now;
	
	g_ptATIntfDev->InvalidRecvBuf(g_ptATIntfDev);//清除环形缓冲区
	g_ptATIntfDev->Write(g_ptATIntfDev, cmd, strlen(cmd));
	g_ptATIntfDev->Write(g_ptATIntfDev, "\r\n", 2);


	//ReadByte返回的条件：
	//读到了一个字节
	//没有数据也立刻返回
	pre = KAL_GetTime(); 
	while(iTimeoutMS)
	{
		if(g_ptATIntfDev ->ReadByte(g_ptATIntfDev, &buf[i]) == 0)
		{
			//有没有碰到回车换行\r\n
			if(  (i != 0) && (buf[i-1] == '\r') && (buf[i] == '\n'))
			{
				if(isReturnOK(buf,i+1))
					return 0;
				else if(isReturnERROR(buf,i+1))
					return -1;
				else
				{
					i = 0;
				}
			}
			i++;
		}
		now = KAL_GetTime();//获取现在时间
		if(now > pre)//现在的时间大于上一次时间
		{
			iTimeoutMS--;
			pre = now;//同步上一次时间
		}
	}
	return -2;//超时退出
}


/****************************************************************************
*函数名称：USART3_SendBytes
*功能描述：通过UART3发出多个数据
*输入参数：buf - 数据缓冲区
*输入参数：1en - 数据长度
*输出参数：无
*返回值：     	无
*修改日期			版本号			修改人			修改内容
2024/05/02		V1.0		huaj		创建
***************************************************************************/
int ATCommandSendAndRecv(char *cmd, char *pcRecvbuf, int iTimeoutMS)
{
	char *buf = pcRecvbuf;
	int i = 0;
	int pre;
	int now;
	
	g_ptATIntfDev->InvalidRecvBuf(g_ptATIntfDev);//清除环形缓冲区
	g_ptATIntfDev->Write(g_ptATIntfDev, cmd, strlen(cmd));
	g_ptATIntfDev->Write(g_ptATIntfDev, "\r\n", 2);


	//ReadByte返回的条件：
	//读到了一个字节
	//没有数据也立刻返回
	pre = KAL_GetTime(); 
	while(iTimeoutMS)
	{
		if(g_ptATIntfDev ->ReadByte(g_ptATIntfDev, &buf[i]) == 0)
		{
			//有没有碰到回车换行\r\n
			if(  (i != 0) && (buf[i-1] == '\r') && (buf[i] == '\n'))
			{
				if(isReturnOK(buf,i+1))
					return 0;
				else if(isReturnERROR(buf,i+1))
					return -1;
				else
				{
					i = 0;
				}
			}
			i++;
		}
		now = KAL_GetTime();//获取现在时间
		if(now > pre)//现在的时间大于上一次时间
		{
			iTimeoutMS--;
			pre = now;//同步上一次时间
		}
	}
	return -2;//超时退出
}



/****************************************************************************
*函数名称：USART3_SendBytes
*功能描述：通过UART3发出多个数据
*输入参数：buf - 数据缓冲区
*输入参数：1en - 数据长度
*输出参数：无
*返回值：     	无
*修改日期			版本号			修改人			修改内容
2024/05/02		V1.0		huaj		创建
***************************************************************************/
static int ATDataRecv(unsigned char* Data,int * piLen,int iTimeoutMS)
{
	//数据格式：+IPD,2:ab
	enum AT_STATUS{
		INIT_STATUS,
		LEN_STATUS,
		DATA_STATUS
	};
		
	AT_STATUS status = INIT_STATUS;
	
	char buf[50];//接收的缓冲区
	int i = 0;//接收数组的下标
	int len = 0;//数据的长度
	int pre;//上一次时间
	int now;//现在的时间


	//ReadByte返回的条件：
	//读到了一个字节
	//没有数据也立刻返回
	pre = KAL_GetTime(); 
	while(iTimeoutMS)
	{
		if(g_ptATIntfDev ->ReadByte(g_ptATIntfDev, buf) == 0)
		{
			switch(status)
			{
				case INIT_STATUS:
				{
					buf[i+1] = '\0';//读取了8个字节，在末尾加上'\0'
					if(strstr(buf, "+IPD,"))//判断是否含有
					{
						status = LEN_STATUS;
					}
					break;
				}
				case LEN_STATUS:
				{
					if(buf[i] = ':')
					{
						//计算长度
						for(m = 0; m < i; m++)//读取':'之前的 
						{
							len = len* 10 + buf[m] - '0';//
						}
						status = DATA_STATUS;
						i = 0；
							
					}
					else
					{
						i++;
					}
					break;
				}
				case DATA_STATUS:
				{
					Data[i] = buf[i];
					i++;
					if(i == len)
					{
						if(piLen)
						{
							*piLen = len;
						}
						return 0;
					}
					break;
				}
			}
		}
		now = KAL_GetTime();//获取现在时间
		if(now > pre)//现在的时间大于上一次时间
		{
			iTimeoutMS--;
			pre = now;//同步上一次时间
		}
	}
	return -2;//超时退出
}


