#include "Ring_buffer.h"

static ring_buffer g_tInputBuffer;



void ring_buffer_init(ring_buffer *dst_buf)
{
	dst_buf->pW = 0;
	dst_buf->pR = 0;
}



int ring_buffer_write(unsigned char c,  ring_buffer *dst_buf)
{
	int i = (dst_buf->pW + 1) % BUFFER_SIZE;//��д��ַ�����ڴ�С֮�ڣ��ҵ�����С
	
	if(i != dst_buf->pR)//д��ַ�����ڶ�ȡ��ַ�����λ�����û��д��
	{
		dst_buf-> buffer[dst_buf->pW] = c;//�����ݷ��뻷�λ�����
		dst_buf->pW = i;//��д��ַ���µ��ṹ����
	}
}




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
