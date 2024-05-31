#include "OLED_device.h"



/*��ʾ�豸�ṹ���µ�һ�㣬�����ṹ�������OLED�ĺ���*/
//�����OLED �� 128*64
/*128*64 bits , 1024 bytes*/
static unsigned char g_OLEDFramebuffer[1024];

 
/**
 * @brief OLED��ʼ��
 * @param ptDisplayDevice 
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
static int OLEDDeviceInit(struct DisplayDevice* ptDisplayDevice)
{
	/*��ʼ��OLED*/
	return KAL_OLEDDeviceInit(ptDisplayDevice);
}


/**
 * @brief ˢ��OLEDͼ��
 * @param ptDisplayDevice 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
static void OLEDDeviceFlush(struct DisplayDevice* ptDisplayDevice)
{
	/*��g_OLEDFramebuffer�����ݰᵽOLED�Դ����Դ�����*/
	KAL_OLEDDeviceFlush(ptDisplayDevice);
}




/*ΪOLED����һ��displayDevice �ṹ��*/
static DisplayDevice g_tOLEDDevice = {
	"OLED",
	g_OLEDFramebuffer,
	128,
	64,
	1,
	128*64*1/8,
	OLEDDeviceInit,
	OLEDDeviceFlush
};


/**
 * @brief ע��OLEDΪ��ʾ�豸
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-22
*/
void AddDisplayDeviceOLED(void)
{

	DisplayDeviceRegister(&g_tOLEDDevice);
}


