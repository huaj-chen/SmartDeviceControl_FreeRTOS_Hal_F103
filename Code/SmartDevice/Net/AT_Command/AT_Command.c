#include <UART_dev.h>
#include "Net_Device.h"

#define ATINTERFACE_TIMEOUT 10

static pATInterfaceDevice g_ptATIntfDev;//������һ��AT������豸�Ľṹ��ָ��

//==================================================================
//��    ����	isReturnOK
//��   	�ܣ�	�ж��ַ���������û�У���OK\r\n��
//���������	�ַ���������
//�� �� ֵ��
//��    �ڣ�	2024/05/02
//��    ����
//==================================================================
static int isReturnOK(char* buf, int len)
{
	//�ж��ַ���������û�У���OK\r\n��
	buf[len] = '\0';//�ں������\0������
	return strstr(buf, "OK\r\n");
}

static int isReturnERROR(char* buf, int len)
{
	//�ж��ַ���������û�У���ERROR\r\n��
	buf[len] = '\0';
	return strstr(buf, "ERROR\r\n");
}


/****************************************************************************
*�������ƣ�ATInterfaceInit
*����������AT�����豸���ͽṹ���ʼ��
*�����������
*�����������
*����ֵ��     	��
*�޸�����			�汾��			�޸���			�޸�����
2024/05/02		V1.0		huaj		����
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
*�������ƣ�ATCommandSend
*��������������AT�����豸���ͽṹ��
*���������cmd - ����
*���������iTimeoutMS - ��ʱʱ��
*�����������
*����ֵ��     	��
*�޸�����			�汾��			�޸���			�޸�����
2024/05/02		V1.0		huaj		����
***************************************************************************/
int ATCommandSend(char* cmd, int iTimeoutMS)
{
	char buf[50];
	int i = 0;
	int pre;
	int now;
	
	g_ptATIntfDev->InvalidRecvBuf(g_ptATIntfDev);//������λ�����
	g_ptATIntfDev->Write(g_ptATIntfDev, cmd, strlen(cmd));
	g_ptATIntfDev->Write(g_ptATIntfDev, "\r\n", 2);


	//ReadByte���ص�������
	//������һ���ֽ�
	//û������Ҳ���̷���
	pre = KAL_GetTime(); 
	while(iTimeoutMS)
	{
		if(g_ptATIntfDev ->ReadByte(g_ptATIntfDev, &buf[i]) == 0)
		{
			//��û�������س�����\r\n
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
		now = KAL_GetTime();//��ȡ����ʱ��
		if(now > pre)//���ڵ�ʱ�������һ��ʱ��
		{
			iTimeoutMS--;
			pre = now;//ͬ����һ��ʱ��
		}
	}
	return -2;//��ʱ�˳�
}


/****************************************************************************
*�������ƣ�USART3_SendBytes
*����������ͨ��UART3�����������
*���������buf - ���ݻ�����
*���������1en - ���ݳ���
*�����������
*����ֵ��     	��
*�޸�����			�汾��			�޸���			�޸�����
2024/05/02		V1.0		huaj		����
***************************************************************************/
int ATCommandSendAndRecv(char *cmd, char *pcRecvbuf, int iTimeoutMS)
{
	char *buf = pcRecvbuf;
	int i = 0;
	int pre;
	int now;
	
	g_ptATIntfDev->InvalidRecvBuf(g_ptATIntfDev);//������λ�����
	g_ptATIntfDev->Write(g_ptATIntfDev, cmd, strlen(cmd));
	g_ptATIntfDev->Write(g_ptATIntfDev, "\r\n", 2);


	//ReadByte���ص�������
	//������һ���ֽ�
	//û������Ҳ���̷���
	pre = KAL_GetTime(); 
	while(iTimeoutMS)
	{
		if(g_ptATIntfDev ->ReadByte(g_ptATIntfDev, &buf[i]) == 0)
		{
			//��û�������س�����\r\n
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
		now = KAL_GetTime();//��ȡ����ʱ��
		if(now > pre)//���ڵ�ʱ�������һ��ʱ��
		{
			iTimeoutMS--;
			pre = now;//ͬ����һ��ʱ��
		}
	}
	return -2;//��ʱ�˳�
}



/****************************************************************************
*�������ƣ�USART3_SendBytes
*����������ͨ��UART3�����������
*���������buf - ���ݻ�����
*���������1en - ���ݳ���
*�����������
*����ֵ��     	��
*�޸�����			�汾��			�޸���			�޸�����
2024/05/02		V1.0		huaj		����
***************************************************************************/
static int ATDataRecv(unsigned char* Data,int * piLen,int iTimeoutMS)
{
	//���ݸ�ʽ��+IPD,2:ab
	enum AT_STATUS{
		INIT_STATUS,
		LEN_STATUS,
		DATA_STATUS
	};
		
	AT_STATUS status = INIT_STATUS;
	
	char buf[50];//���յĻ�����
	int i = 0;//����������±�
	int len = 0;//���ݵĳ���
	int pre;//��һ��ʱ��
	int now;//���ڵ�ʱ��


	//ReadByte���ص�������
	//������һ���ֽ�
	//û������Ҳ���̷���
	pre = KAL_GetTime(); 
	while(iTimeoutMS)
	{
		if(g_ptATIntfDev ->ReadByte(g_ptATIntfDev, buf) == 0)
		{
			switch(status)
			{
				case INIT_STATUS:
				{
					buf[i+1] = '\0';//��ȡ��8���ֽڣ���ĩβ����'\0'
					if(strstr(buf, "+IPD,"))//�ж��Ƿ���
					{
						status = LEN_STATUS;
					}
					break;
				}
				case LEN_STATUS:
				{
					if(buf[i] = ':')
					{
						//���㳤��
						for(m = 0; m < i; m++)//��ȡ':'֮ǰ�� 
						{
							len = len* 10 + buf[m] - '0';//
						}
						status = DATA_STATUS;
						i = 0��
							
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
		now = KAL_GetTime();//��ȡ����ʱ��
		if(now > pre)//���ڵ�ʱ�������һ��ʱ��
		{
			iTimeoutMS--;
			pre = now;//ͬ����һ��ʱ��
		}
	}
	return -2;//��ʱ�˳�
}


