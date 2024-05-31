#include "Ring_buffer.h"

static ring_buffer g_tInputBuffer;



/**
 * @brief 环形缓冲区初始化
 * @param dst_buf - 环形缓冲区结构体
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
 * @brief 向环形缓冲区写入数据
 * @param c - 要写入的字符
 * @param dst_buf - 环形缓冲区结构体
 * @return {int} 
 * @version 1.0
 * @Author huaj 
 * @date 2024-05-30
*/
int ring_buffer_write(unsigned char c,  ring_buffer *dst_buf)
{
	int i = (dst_buf->pW + 1) % BUFFER_SIZE;//将写地址控制在大小之内，且调整大小
	
	if(i != dst_buf->pR)//写地址不等于读取地址，环形缓冲区没有写满
	{
		dst_buf-> buffer[dst_buf->pW] = c;//将数据放入环形缓冲区
		dst_buf->pW = i;//将写地址更新到结构体里
	}
}



/**
 * @brief 从环形缓冲区读取数据
 * @param c - 存放读取的数据
 * @param dst_buf - 环形缓冲区结构体
 * @return {int} -1 - 读取失败 ， 0 - 读取成功
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
		*c = dst_buf->buffer[dst_buf->pR];//将环形缓冲区读位置的数据给
		dst_buf->pR = (dst_buf->pR + 1) % BUFFER_SIZE;//控制读地址的大小，让其增加
		return 0;
	}
}
