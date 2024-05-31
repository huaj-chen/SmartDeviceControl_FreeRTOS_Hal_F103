#include "AT_Command.h"


#define ATINTERFACE_TIMEOUT 1000

static pATInterfaceDevice g_ptATIntfDev;//������һ��AT������豸�Ľṹ��ָ��

/**
 * @brief �ж��ַ���������û�У���OK\r\n��
 * @param buf - �ַ���
 * @param len - ����
 * @return {int} 1 - ��OK, 0 - û��OK
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static int isReturnOK(char* buf, int len)
{

	// �����������Ƿ���Ч
    if (buf == NULL || len <= 0) {
        return 0;  // ���������Ч������0
    }

	buf[len] = '\0';//�ں������\0������

    // ʹ��strstr�������ַ���"OK"
    char* pos = strstr(buf, "OK\r\n");
    if (pos != NULL) {
        // ���"OK"�Ƿ���buf�ĳ��ȷ�Χ��
        if ((pos - buf + 4) <= len) {  // "OK"�ĳ���Ϊ4
            return 1;  // ����ڷ�Χ�ڣ�����1��ʾ�ҵ�
        }
    }

    return 0;  // ���û���ҵ�������0
}


/**
 * @brief �ж��ַ���������û�У���error\r\n��
 * @param buf - �ַ���
 * @param len - ����
 * @return {int} 1 - ��OK, 0 - û��OK
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
static int isReturnERROR(char* buf, int len)
{
	// �����������Ƿ���Ч
    if (buf == NULL || len <= 0) {
        return 0;  // ���������Ч������0
    }

	buf[len] = '\0';//�ں������\0������

    // ʹ��strstr�������ַ���"OK"
    char* pos = strstr(buf, "ERROR\r\n");
    if (pos != NULL) {
        // ���"OK"�Ƿ���buf�ĳ��ȷ�Χ��
        if ((pos - buf + 7) <= len) {  // "error"�ĳ���Ϊ7
            return 1;  // ����ڷ�Χ�ڣ�����1��ʾ�ҵ�
        }
    }

    return 0;  // ���û���ҵ�������0
}



/**
 * @brief AT�����豸���ͽṹ���ʼ��
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
 * @brief ����AT����- �����ж��Ƿ��������ȷ
 * @param cmd - ����
 * @param iTimeoutMS - ��ʱʱ��
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
int ATCommandSend(char* cmd, int iTimeoutMS)
{
	char buf[50];//��Ŷ�ȡ������
	int i = 0;
	int pre;//��ȥ��ʱ�� 		
	int now;//���ڵ�ʱ��
	
	g_ptATIntfDev->InvalidRecvBuf(g_ptATIntfDev);//������λ�����
	g_ptATIntfDev->Write(g_ptATIntfDev, cmd, strlen(cmd));
	g_ptATIntfDev->Write(g_ptATIntfDev, "\r\n", 2);//������ĩβ����\r\n
	printf("Send command:%s\r\n",cmd);

	//ReadByte���ص�������
	//������һ���ֽ�
	//û������Ҳ���̷���
	pre = KAL_GetTime(); 
	while(iTimeoutMS)//����Ҫ�ж��ַ������Ƿ���OK\r\n
	{
		if(g_ptATIntfDev ->ReadByte(g_ptATIntfDev, &buf[i]) == 0)
		{
			printf("%c",buf[i]);		//�����յ�����Ϣ���д�ӡ
			//��û�������س�����\r\n
			if(  (i != 0) && (buf[i-1] == '\r') && (buf[i] == '\n'))
			{
				if(isReturnOK(buf,i+1))//����ָ����ȷ
					return 0;
				else if(isReturnERROR(buf,i+1))
					return -1;
				else
				{
					i = 0;//δ���յ�������Ϣ����i��0�����¶�ȡ��Ϣ
				}
			}
			i++;//��ȡ��һ���ֽ�
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


/**
 * @brief ����AT���� �� ���շ��ص���Ϣ
 * @param cmd - ����
 * @param pcRecvbuf - ���շ�����Ϣ��λ��
 * @param iTimeoutMS - ��ʱʱ��
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
	
	g_ptATIntfDev->InvalidRecvBuf(g_ptATIntfDev);//������λ�����
	g_ptATIntfDev->Write(g_ptATIntfDev, cmd, strlen(cmd));//��������
	g_ptATIntfDev->Write(g_ptATIntfDev, "\r\n", 2);
	printf("Send command:%s\r\n",cmd);

	//ReadByte���ص�������
	//������һ���ֽ�
	//û������Ҳ���̷���
	pre = KAL_GetTime(); 
	while(iTimeoutMS)
	{
		if(g_ptATIntfDev ->ReadByte(g_ptATIntfDev, &buf[i]) == 0)//��ȡһ���ֽ�
		{
			printf("%c",buf[i]);		//�����յ�����Ϣ���д�ӡ
			//��û�������س�����\r\n
			if(  (i != 0) && (buf[i-1] == '\r') && (buf[i] == '\n'))
			{
				if(isReturnOK(buf,i+1))
				{
					buf[i+1] = '\0';//����֮ǰ��Ϊ�ַ�������һ���հ׷�
					return 0;
				}
				else if(isReturnERROR(buf,i+1))
					return -1;
			}
			i++;//��ȡ��һ���ֽ�
		}
		now = KAL_GetTime();//��ȡ����ʱ��
		if(now > pre)//���ڵ�ʱ����� ��һ�λ�ȡ��ʱ��
		{
			iTimeoutMS--;
			pre = now;//ͬ�����ڵ�ʱ��Ϊ��һ�ε�ʱ��
		}
	}
	return -2;//��ʱ�˳�
}




/**
 * @brief �Խ��յ����ݽ��н���
 * @param Data - ���յ�����
 * @param piLen - ���յ����ݳ���
 * @param iTimeoutMS - ��ʱʱ��
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
int ATDataRecv(unsigned char* Data,int * piLen,int iTimeoutMS)
{
	
	//���ݸ�ʽ��+IPD,2:ab
	enum AT_STATUS {
    INIT_STATUS,
    LEN_STATUS,
    DATA_STATUS
	};
	enum AT_STATUS status = INIT_STATUS;//��ʼ��״̬
	
	char buf[50];//���յĻ�����
	int i = 0;//����������±�
	int len = 0;//���ݵĳ���
	int pre;//��һ��ʱ��
	int now;//���ڵ�ʱ��
	int m = 0;

	//ReadByte���ص�������
	//������һ���ֽ�
	//û������Ҳ���̷���
	pre = KAL_GetTime(); 
	while(iTimeoutMS)
	{
		if(g_ptATIntfDev ->ReadByte(g_ptATIntfDev, &buf[i]) == 0)
		{
			// printf("%s",buf);
			switch(status)
			{
				case INIT_STATUS://��ʼ״̬
				{
					buf[i+1] = '\0';//��ȡ��8���ֽڣ���ĩβ����'\0'
					if(strstr(buf, "+IPD,"))//�ж��Ƿ���
					{
						status = LEN_STATUS;//���볤���ж�״̬
						i = 0;//i��0�����¶�ȡ
					}
					else
					{
						i++;//��ȡ��һ���ֽ�
					}
					break;
				}
				case LEN_STATUS:
				{
					if(buf[i] == ':')//���ʱ�� i-1��ʾ�ж���λ����
					{
						//���㳤��
						for(m = 0; m < i; m++)//��ȡ':'֮ǰ������ 
						{
							len = len* 10 + buf[m] - '0';//�������
						}
						status = DATA_STATUS;//�����곤�ȣ��������ݴ���
						i = 0;//��0
					}
					else
					{
						i++;//������ȡ
					}
					break;
				}
				case DATA_STATUS:
				{
					Data[i] = buf[i];//��+IPD,2:ab ������ݷŵ������������
					i++;
					if(i == len)//У���Ƿ���յ�������һ��
					{
						if(piLen)//����Ľ������ݳ��ȵĴ洢��Ϊ��
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


