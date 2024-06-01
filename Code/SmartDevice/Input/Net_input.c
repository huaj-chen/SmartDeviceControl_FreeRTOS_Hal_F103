#include "Net_input.h"


//作为解析数据的枚举
enum AT_STATUS{
		INIT_STATUS,
		LEN_STATUS,
		DATA_STATUS
};
static enum AT_STATUS g_status = INIT_STATUS;//初始为初始化状态


//接收中断时，数据存放的buf
static char g_ESP8266DataBuffer[INPUT_BUF_LEN];
static int g_DataBuffIndex = 0;//用作解析数据的索引
static int g_DataLen = 0;//接收到的数据长度





/**
 * @brief 对接收到的数据进行解析，然后上报为输入事件
 * @param c - 传入的解析的单个字节
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-31
*/
static void ESP8266DataProcessCallback(char c)
{
	
	//1.保存数据
	InputEvent event;//定义一个输入事件
	char *buf = g_ESP8266DataBuffer;
	int i = g_DataBuffIndex;
	int m;//计算长度的索引
	buf[i] = c;//将数据放到buf中
	g_DataBuffIndex++;//索引加1，读取下一个字节
	
	//2.解析+IPD,n:XXXXXXxxxx

	switch(g_status)//根据状态来解析数据
	{
		case INIT_STATUS:
		{
			if(buf[0] != '+')//如果读取到的非‘+’开头，直接丢弃
			{
				g_DataBuffIndex = 0;
			}
			if(i == 4)//读取5个字节数据，i为4
			{
				if(strncmp(buf, "+IPD,", 5) == 0)//找到这个前缀
				{
					g_status = LEN_STATUS;//进入解析数据长度状态
				}
				g_DataBuffIndex = 0;//读取了5个字节，便将index置0，重新读取
			}
			break;
		}
		case LEN_STATUS:
		{
			if(buf[i] == ':')
			{
				//计算长度
				for(m = 0; m < i; m++)//读取':'之前的 
				{
					g_DataLen = g_DataLen* 10 + buf[m] - '0';//接收到的数据的长度
				}
				g_status = DATA_STATUS;//进入解析数据状态
				g_DataBuffIndex = 0;//读取了数字，便将index置0，重新读取
					
			}
			break;
		}
		case DATA_STATUS:
		{
			if(g_DataBuffIndex == g_DataLen)//表示接收的数据，与数据长度相符，接收完成
			{
				//构造InputEvent并上报
				event.time = KAL_GetTime();//输入事件的时间
				event.itype = INPUT_EVENT_TYPE_NET;//输入事件的类型
				strncpy(event.str, buf, g_DataLen);//将buf中的数据放到输入事件中去
				event.str[g_DataLen] = '\0';//给数据的末尾加上结束符
				PutInputEvent(&event);//将事件放到环形缓冲区
				
				g_status = INIT_STATUS;//恢复状态为初始
				g_DataBuffIndex = 0;
				g_DataLen = 0;
			}
			break;
		}
	}

}

/**
 * @brief 为UART中断函数设置一个输入回调函数，在这个回调函数 去解析数据
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-31
*/
static int ESP8266NetInputInit()
{
	//给UART中断函数提供一个回调函数
	SetNetInputProcessCallback(ESP8266DataProcessCallback);
	return 0;
}


/*为esp8266网课设备构建一个InputDevice*/
static InputDevice g_tNetInputDevice = {
	"ESP8266",
	NULL,
	ESP8266NetInputInit,
	NULL,
};





void AddInputDeviceNet()
{
	InputDeviceRegister(&g_tNetInputDevice);
}

