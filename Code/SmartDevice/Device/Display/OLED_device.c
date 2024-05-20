#include "Display_device.h"

/*��ʾ�豸�ṹ���µ�һ�㣬�����ṹ�������OLED�ĺ���*/
//�����OLED �� 128*64

static int OLEDDeviceInit(struct DisplayDevice* ptDisplayDevice)
{
	/*��ʼ��OLED*/
	return KAL_OLEDDeviceInit(ptDisplayDevice);
}


static void OLEDDeviceFlush(struct DisplayDevice* ptDisplayDevice)
{
	/*��g_OLEDFramebuffer�����ݰᵽOLED�Դ����Դ�����*/
	return KAL_OLEDDeviceFlush(ptDisplayDevice);
}

/*128*64 bits , 1024 bytes*/
static unsigned char g_OLEDFramebuffer[1024];


/*ΪOLED����һ��displayDevice �ṹ��*/
static DisplayDevice g_tOLEDDevice = {
	"OLED",
	g_OLEDFramebuffer,
	128,
	64,
	1,
	OLEDDeviceInit,
	OLEDDeviceFlush
};


//==================================================================
//�� �� AddDisplayDeviceOLED
//��    �ܣ���OLEDע�ᵽ��ʾ�豸ϵͳ����ȥ
//�����������
//�� �� ֵ����
//��    �ڣ�
//��    ����
//==================================================================
void AddDisplayDeviceOLED(void)
{

	DisplayDeviceRegister(&g_tOLEDDevice);
}


