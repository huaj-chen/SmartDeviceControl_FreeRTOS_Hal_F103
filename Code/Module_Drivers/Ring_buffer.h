#ifndef _RING_BUFFER_H
#define _RING_BUFFER_H

#define BUFFER_SIZE 10 //���λ������Ĵ�С

//���λ�������������¼�
typedef struct
{
	int  buffer[BUFFER_SIZE];/*�������ռ�*/
	volatile unsigned int pW;//д��ַ
	volatile unsigned int pR;//����ַ
} ring_buffer;

void ring_buffer_init(ring_buffer *dst_buf);

int ring_buffer_write(unsigned char c,  ring_buffer *dst_buf);


int ring_buffer_read(unsigned char *c,  ring_buffer *dst_buf);





#endif 
