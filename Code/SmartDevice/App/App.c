#include "App.h"



/**
 * @brief LED��ʼ��
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
 * @brief ��ʾ�豸��ʼ��
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
    //1.��ʼ���豸
    ptDevice->InitDevice(ptDevice);
    //2.�����Ļ
    memset(ptDevice->FBBase, 0, ptDevice->iSize);
    //3.��ʾ
    // OLED_ShowChar(0,0,'a', 12);
    //4.flush
	OLED_Refresh();
}

/**
 * @brief ����ϵͳ��ʼ��
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
 * @brief �����ʼ��
 * @version 1.0
 * @Author huaj 
 * @date 2024-06-01
*/
static void NetSystem_Init()
{
	pNETDevice pNetDev;

	//�ȴ��������
	KAL_Delay(2000);

	//ע������
	AddNetDevices ();

	pNetDev = GetNetDevice("ESP8266");

	//��ʼ��
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
	
	//��������֮ǰ���Ƚ��йرմ���
	pNetDev->CloseTransfer(pNetDev);
	//��������
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
    char str[30];//����OLED��ʾ
    pNETDevice pNetDev;
 	pNetDev = GetNetDevice("ESP8266");
    if(pNetDev ->GetInfo(pNetDev, ip) == 0)//��ȡIP
	{
		printf("Board IP = %s, port = %d\r\n", ip, port);
	}
	else 
	{
		printf("GetInfo error\r\n");
		return ;
	}
    //��OLED����ʾ����
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
    char dev[10];//��¼�����豸
    int i = 0;
    int status;//��¼״̬
    char *pTmp;//���Լ�¼λ��

    //������dev��ֵ
    pTmp = strstr(strJson, "\"dev\":\"");//Ѱ�����ǰ׺��λ��
    if(!pTmp)
        return;
    pTmp += strlen("\"dev\":\"");//��������ַ����Ĵ�С���������ݵ�λ��
    for(i = 0; pTmp[i] != '\"'; i++)
    {
        dev[i] = pTmp[i];//���豸���ͷŵ�dev       
    }
    dev[i] = '\0';
    printf("dev:%s\r\n",dev);


    //������status��ֵ
    pTmp = strstr(strJson, "\"status\":\"");//Ѱ�����ǰ׺��λ��
    if(!pTmp)
        return;
    pTmp += strlen("\"status\":\"");//��������ַ����Ĵ�С���������ݵ�λ��
    status = (pTmp[0] == '-') ? (0 - (pTmp[1] - '0')) : (pTmp[0] - '0');//�ж�����

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
//     //1.��ʼ�������豸
//     HardwareInit();

//     //2.����WIFI
//     WIFIConnect();

//     //3.��OLED��ʾIP,�˿�
//     DisplayNetInfo();

//     while (1)
//     {
//         //4.��ȡInputEvent
//         if(0 == GetInputEvent(&Event))
//         {
//             //5.ת��ΪJson
//             if(0 == ConvertInputEventToJson(&Event, strjson))
//                 //6.�����豸
//                 SmartDeviceControl(strjson);
//         }

        
//     }
// }



/**
 * @brief ��RTOS��ʼ������
 * @version 1.0
 * @Author huaj 
 * @date 2024-06-04
*/
void Init_Connect_Display()
{
    //1.��ʼ�������豸
    HardwareInit();

    //2.����WIFI
    WIFIConnect();

    //3.��OLED��ʾIP,�˿�
    DisplayNetInfo();
}
