#include "AT_Command.h"


#define ATINTERFACE_TIMEOUT 1000

static pATInterfaceDevice g_ptATIntfDev;//定义了一个AT命令发送设备的结构体指针

/**
 * @brief 判断字符串里面有没有：“OK\r\n”
 * @param buf - 字符串
 * @param len - 长度
 * @return {int} 1 - 有OK, 0 - 没有OK
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static int isReturnOK(char* buf, int len)
{

	// 检查输入参数是否有效
    if (buf == NULL || len <= 0) {
        return 0;  // 如果输入无效，返回0
    }

	buf[len] = '\0';//在后面加上\0结束符

    // 使用strstr查找子字符串"OK"
    char* pos = strstr(buf, "OK\r\n");
    if (pos != NULL) {
        // 检查"OK"是否在buf的长度范围内
        if ((pos - buf + 4) <= len) {  // "OK"的长度为4
            return 1;  // 如果在范围内，返回1表示找到
        }
    }

    return 0;  // 如果没有找到，返回0
}


/**
 * @brief 判断字符串里面有没有：“error\r\n”
 * @param buf - 字符串
 * @param len - 长度
 * @return {int} 1 - 有OK, 0 - 没有OK
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static int isReturnERROR(char* buf, int len)
{
	// 检查输入参数是否有效
    if (buf == NULL || len <= 0) {
        return 0;  // 如果输入无效，返回0
    }

	buf[len] = '\0';//在后面加上\0结束符

    // 使用strstr查找子字符串"OK"
    char* pos = strstr(buf, "ERROR\r\n");
    if (pos != NULL) {
        // 检查"OK"是否在buf的长度范围内
        if ((pos - buf + 7) <= len) {  // "error"的长度为7
            return 1;  // 如果在范围内，返回1表示找到
        }
    }

    return 0;  // 如果没有找到，返回0
}



/**
 * @brief AT命令设备发送结构体初始化
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
int ATInterfaceInit(void)
{
	g_ptATIntfDev = GetATInterfaceDevice("uart3");
	return g_ptATIntfDev->Init(g_ptATIntfDev);
}



// ATInterfaceSelect("uart")
// {
// 	g
// }


/**
 * @brief 发送AT命令- 并且判断是否命令发送正确
 * @param cmd - 命令
 * @param iTimeoutMS - 超时时间
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
int ATCommandSend(char* cmd, int iTimeoutMS)
{
	char buf[50];//存放读取的数据
	int i = 0;
	int pre;//过去的时间 		
	int now;//现在的时间
	
	g_ptATIntfDev->InvalidRecvBuf(g_ptATIntfDev);//清除环形缓冲区
	g_ptATIntfDev->Write(g_ptATIntfDev, cmd, strlen(cmd));
	g_ptATIntfDev->Write(g_ptATIntfDev, "\r\n", 2);//在命令末尾加上\r\n
	printf("Send command:%s\r\n",cmd);

	//ReadByte返回的条件：
	//读到了一个字节
	//没有数据也立刻返回
	pre = KAL_GetTime(); 
	while(iTimeoutMS)//仅需要判断字符串中是否有OK\r\n
	{
		if(g_ptATIntfDev ->ReadByte(g_ptATIntfDev, &buf[i]) == 0)
		{
			printf("%c",buf[i]);		//将接收到的信息进行打印
			//有没有碰到回车换行\r\n
			if(  (i != 0) && (buf[i-1] == '\r') && (buf[i] == '\n'))
			{
				if(isReturnOK(buf,i+1))//发送指令正确
					return 0;
				else if(isReturnERROR(buf,i+1))
					return -1;
				else
				{
					i = 0;//未接收到反馈信息，将i清0，重新读取消息
				}
			}
			i++;//读取下一个字节
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


/**
 * @brief 发生AT命令 并 接收返回的信息
 * @param cmd - 命令
 * @param pcRecvbuf - 接收返回信息的位置
 * @param iTimeoutMS - 超时时间
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
int ATCommandSendAndRecv(char *cmd, char *pcRecvbuf, int iTimeoutMS)
{
	char *buf = pcRecvbuf;
	int i = 0;
	int pre;
	int now;
	
	g_ptATIntfDev->InvalidRecvBuf(g_ptATIntfDev);//清除环形缓冲区
	g_ptATIntfDev->Write(g_ptATIntfDev, cmd, strlen(cmd));//发送命令
	g_ptATIntfDev->Write(g_ptATIntfDev, "\r\n", 2);
	printf("Send command:%s\r\n",cmd);

	//ReadByte返回的条件：
	//读到了一个字节
	//没有数据也立刻返回
	pre = KAL_GetTime(); 
	while(iTimeoutMS)
	{
		if(g_ptATIntfDev ->ReadByte(g_ptATIntfDev, &buf[i]) == 0)//读取一个字节
		{
			printf("%c",buf[i]);		//将接收到的信息进行打印
			//有没有碰到回车换行\r\n
			if(  (i != 0) && (buf[i-1] == '\r') && (buf[i] == '\n'))
			{
				if(isReturnOK(buf,i+1))
				{
					buf[i+1] = '\0';//返回之前，为字符串加上一个空白符
					return 0;
				}
				else if(isReturnERROR(buf,i+1))
					return -1;
			}
			i++;//读取下一个字节
		}
		now = KAL_GetTime();//获取现在时间
		if(now > pre)//现在的时间大于 上一次获取的时间
		{
			iTimeoutMS--;
			pre = now;//同步现在的时间为上一次的时间
		}
	}
	return -2;//超时退出
}




/**
 * @brief 对接收的数据进行解析
 * @param Data - 接收的数据
 * @param piLen - 接收的数据长度
 * @param iTimeoutMS - 超时时间
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
int ATDataRecv(unsigned char* Data,int * piLen,int iTimeoutMS)
{
	
	//数据格式：+IPD,2:ab
	enum AT_STATUS {
    INIT_STATUS,
    LEN_STATUS,
    DATA_STATUS
	};
	enum AT_STATUS status = INIT_STATUS;//初始化状态
	
	char buf[50];//接收的缓冲区
	int i = 0;//接收数组的下标
	int len = 0;//数据的长度
	int pre;//上一次时间
	int now;//现在的时间
	int m = 0;

	//ReadByte返回的条件：
	//读到了一个字节
	//没有数据也立刻返回
	pre = KAL_GetTime(); 
	while(iTimeoutMS)
	{
		if(g_ptATIntfDev ->ReadByte(g_ptATIntfDev, &buf[i]) == 0)
		{
			// printf("%s",buf);
			switch(status)
			{
				case INIT_STATUS://初始状态
				{
					buf[i+1] = '\0';//读取了8个字节，在末尾加上'\0'
					if(strstr(buf, "+IPD,"))//判断是否含有
					{
						status = LEN_STATUS;//进入长度判断状态
						i = 0;//i清0，重新读取
					}
					else
					{
						i++;//读取下一个字节
					}
					break;
				}
				case LEN_STATUS:
				{
					if(buf[i] == ':')//这个时候 i-1表示有多少位数字
					{
						//计算长度
						for(m = 0; m < i; m++)//读取':'之前的数字 
						{
							len = len* 10 + buf[m] - '0';//获得数字
						}
						status = DATA_STATUS;//计算完长度，进入数据处理
						i = 0;//清0
					}
					else
					{
						i++;//继续读取
					}
					break;
				}
				case DATA_STATUS:
				{
					Data[i] = buf[i];//将+IPD,2:ab 后的数据放到传入的数组里
					i++;
					if(i == len)//校验是否和收到的数字一致
					{
						if(piLen)//传入的接收数据长度的存储不为空
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


