#ifndef _RING_BUFFER_H
#define _RING_BUFFER_H

#define BUFFER_SIZE 10 //环形缓冲区的大小

//环形缓冲区存放输入事件
typedef struct
{
	int  buffer[BUFFER_SIZE];/*缓冲区空间*/
	volatile unsigned int pW;//写地址
	volatile unsigned int pR;//读地址
} ring_buffer;

void ring_buffer_init(ring_buffer *dst_buf);

int ring_buffer_write(unsigned char c,  ring_buffer *dst_buf);


int ring_buffer_read(unsigned char *c,  ring_buffer *dst_buf);





#endif 
