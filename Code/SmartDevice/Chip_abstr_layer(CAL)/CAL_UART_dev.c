#include "CAL_UART_dev.h"



int CAL_UART3Write( char* Data, int iLen)
{
	USART3_SendBytes(Data, iLen);
	return 0;
}



