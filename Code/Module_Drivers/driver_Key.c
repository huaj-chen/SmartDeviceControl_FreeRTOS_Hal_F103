#include <Input_system.h>
#include <Input_buffer.h>
#include <GPIO_Key.h>
#include <stdio.h>
#include "driver_Key.h"
//这一层具体到芯片的实现
static volatile uint8_t key1_val = KEY_RELEASED;
static volatile uint8_t key2_val = KEY_RELEASED;

void KEY_GPIO_ReInit (void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	KEY1_GPIO_CLK_EN();
	KEY2_GPIO_CLK_EN();
	
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;

	GPIO_InitStruct.Pin = KEY1_Pin;
	HAL_GPIO_Init (KEY1_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = KEY2_Pin;
	HAL_GPIO_Init (KEY2_GPIO_Port, &GPIO_InitStruct);

	HAL_NVIC_SetPriority (EXTI3_IRQn, 0, 0);
	HAL_NVIC_SetPriority (EXTI4_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ (EXTI3_IRQn);
	HAL_NVIC_EnableIRQ (EXTI4_IRQn);
}

void EXTI3_IRQHandler(void)
{	
	HAL_GPIO_EXTI_IRQHandler(KEY1_Pin);
}

void EXTI4_IRQHandler(void)
{	
	HAL_GPIO_EXTI_IRQHandler(KEY2_Pin);
}

void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin)
{
	InputEvent event;
	if(KEY1_Pin == GPIO_Pin)
	{
		event.time = KAL_GetTime();//Kal
		event.itype = INPUT_EVENT_TYPE_KEY;
		event.ikey = K1_CODE;
		event.ipressure = !K1_STATUS;//读取GPIO电平,按下电平为0，按下时压力为1
		PutInputEvent (&event);
		key1_val = K1_STATUS;
	}

	else if(KEY2_Pin == GPIO_Pin)
	{
		event.time = KAL_GetTime();//Kal
		event.itype = INPUT_EVENT_TYPE_KEY;//读取GPIO电平,按下电平为0,按下时压力为1
		event.ikey = K2_CODE;
		event.ipressure = !K2_STATUS;//读取GPIO电平
		PutInputEvent (&event);
		key2_val = K2_STATUS;
	}

}

uint8_t KEY1_Value(void)
{
	return key1_val;
	
}

uint8_t KEY2_Value(void)
{
	return key2_val;
	
}

