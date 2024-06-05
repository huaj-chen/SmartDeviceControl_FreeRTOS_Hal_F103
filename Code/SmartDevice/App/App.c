#include "App.h"



/**
 * @brief LED初始化
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-31
*/
static void LED_Init()
{
    //LED
    pLEDDevice p1 = GetLEDDevice(LED_1);
	pLEDDevice p2 = GetLEDDevice(LED_2);
	p1 ->LEDinit(p1);
	p2 ->LEDinit(p2);
}

/**
 * @brief 显示设备初始化
 * @version 1.0
 * @Author huaj 
 * @date 2024-06-01
*/
static void Display_Init()
{
    pDisplayDevice ptDevice;
    char *name = "OLED";

    AddDisplayDevices();
    ptDevice = GetDisplayDevice(name);
    //1.初始化设备
    ptDevice->InitDevice(ptDevice);
    //2.清除屏幕
    memset(ptDevice->FBBase, 0, ptDevice->iSize);
    //3.显示
    // OLED_ShowChar(0,0,'a', 12);
    //4.flush
	OLED_Refresh();
}

/**
 * @brief 输入系统初始化
 * @version 1.0
 * @Author huaj 
 * @date 2024-06-01
*/
static void InputSystem_Init()
{
    AddInputDevice();
	InitInputDevice();
}


/**
 * @brief 网络初始化
 * @version 1.0
 * @Author huaj 
 * @date 2024-06-01
*/
static void NetSystem_Init()
{
	pNETDevice pNetDev;

	//等待启动完毕
	KAL_Delay(2000);

	//注册网卡
	AddNetDevices ();

	pNetDev = GetNetDevice("ESP8266");

	//初始化
	if (pNetDev->Init(pNetDev) == 0)
		printf("init successful\r\n");

}

static void HardwareInit()
{
    LED_Init();
    Display_Init();
    InputSystem_Init();
    NetSystem_Init();
}


static int WIFIConnect()
{
    int port = 1234;
    pNETDevice pNetDev;
 	pNetDev = GetNetDevice("ESP8266");
    printf("Connecting\r\n");   
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
	
	//创建传输之前，先进行关闭传输
	pNetDev->CloseTransfer(pNetDev);
	//创建传输
	if(pNetDev ->CreatTransfer(pNetDev, "UDP", port) == 0)
	{
		printf("CreatTransfer OK\r\n");
        return 0;
	}
	else 
	{
		printf("CreatTransfer error\r\n");
		return -1;

	}	


}



/**
 * @brief 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-31
*/
static void DisplayNetInfo()
{
    int port = 1234;
    char ip[20];
    char str[30];//用于OLED显示
    pNETDevice pNetDev;
 	pNetDev = GetNetDevice("ESP8266");
    if(pNetDev ->GetInfo(pNetDev, ip) == 0)//获取IP
	{
		printf("Board IP = %s, port = %d\r\n", ip, port);
	}
	else 
	{
		printf("GetInfo error\r\n");
		return ;
	}
    //在OLED上显示出来
    sprintf(str, "IP:%s",ip);
    OLED_ShowString(2,12,(unsigned char*)str,12);

    sprintf(str, "Port:%d",port);
    OLED_ShowString(2,24,(unsigned char*)str,12);
    OLED_Refresh();
}


/**
 * @brief 
 * @param strJson 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-31
*/
void SmartDeviceControl(char *strJson)
{
    pLEDDevice ptLED;
    int which;
    char dev[10];//记录具体设备
    int i = 0;
    int status;//记录状态
    char *pTmp;//用以记录位置

    //解析出dev的值
    pTmp = strstr(strJson, "\"dev\":\"");//寻找这个前缀的位置
    if(!pTmp)
        return;
    pTmp += strlen("\"dev\":\"");//加上这个字符串的大小，到达数据的位置
    for(i = 0; pTmp[i] != '\"'; i++)
    {
        dev[i] = pTmp[i];//将设备类型放到dev       
    }
    dev[i] = '\0';
    printf("dev:%s\r\n",dev);


    //解析出status的值
    pTmp = strstr(strJson, "\"status\":\"");//寻找这个前缀的位置
    if(!pTmp)
        return;
    pTmp += strlen("\"status\":\"");//加上这个字符串的大小，到达数据的位置
    status = (pTmp[0] == '-') ? (0 - (pTmp[1] - '0')) : (pTmp[0] - '0');//判断正负

    printf("status:%d\r\n", status);
    if(strncmp(dev, "lamp", 4) == 0)
    {
        printf("got the lamp\r\n");
        which = dev[4] - '0';
        ptLED = GetLEDDevice(which);
        ptLED->LEDcontrol(ptLED, status);
    }

}


// void App()
// {
//     char strjson[100];
//     InputEvent Event;
//     //1.初始化各类设备
//     HardwareInit();

//     //2.连接WIFI
//     WIFIConnect();

//     //3.在OLED显示IP,端口
//     DisplayNetInfo();

//     while (1)
//     {
//         //4.读取InputEvent
//         if(0 == GetInputEvent(&Event))
//         {
//             //5.转换为Json
//             if(0 == ConvertInputEventToJson(&Event, strjson))
//                 //6.控制设备
//                 SmartDeviceControl(strjson);
//         }

        
//     }
// }



/**
 * @brief 供RTOS初始化调用
 * @version 1.0
 * @Author huaj 
 * @date 2024-06-04
*/
void Init_Connect_Display()
{
    //1.初始化各类设备
    HardwareInit();

    //2.连接WIFI
    WIFIConnect();

    //3.在OLED显示IP,端口
    DisplayNetInfo();
}
