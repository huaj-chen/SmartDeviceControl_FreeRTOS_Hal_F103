#include "Ring_buffer.h"

static ring_buffer g_tInputBuffer;



/**
 * @brief ���λ�������ʼ��
 * @param dst_buf - ���λ������ṹ��
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
void ring_buffer_init(ring_buffer *dst_buf)
{
	dst_buf->pW = 0;
	dst_buf->pR = 0;
}


/**
 * @brief ���λ�����д������
 * @param c - Ҫд����ַ�
 * @param dst_buf - ���λ������ṹ��
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
int ring_buffer_write(unsigned char c,  ring_buffer *dst_buf)
{
	int i = (dst_buf->pW + 1) % BUFFER_SIZE;//��д��ַ�����ڴ�С֮�ڣ��ҵ�����С
	
	if(i != dst_buf->pR)//д��ַ�����ڶ�ȡ��ַ�����λ�����û��д��
	{
		dst_buf-> buffer[dst_buf->pW] = c;//�����ݷ��뻷�λ�����
		dst_buf->pW = i;//��д��ַ���µ��ṹ����
	}
}



/**
 * @brief �ӻ��λ�������ȡ����
 * @param c - ��Ŷ�ȡ������
 * @param dst_buf - ���λ������ṹ��
 * @return {int} -1 - ��ȡʧ�� �� 0 - ��ȡ�ɹ�
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
int ring_buffer_read(unsigned char *c,  ring_buffer *dst_buf)
{
	if(dst_buf->pR == dst_buf->pW)
	{
		return -1;
	}
	else
	{
		*c = dst_buf->buffer[dst_buf->pR];//�����λ�������λ�õ����ݸ�
		dst_buf->pR = (dst_buf->pR + 1) % BUFFER_SIZE;//���ƶ���ַ�Ĵ�С����������
		return 0;
	}
}
