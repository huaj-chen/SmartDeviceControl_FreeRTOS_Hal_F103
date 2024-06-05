#ifndef __DRIVER_KEY_H
#define __DRIVER_KEY_H

#include "KAL_Time.h"
#include "stm32f1xx.h"
#include "cmsis_os2.h" 

#define KEY_PRESSED             (0)
#define KEY_RELEASED             (1)


#define KEY1_Pin GPIO_PIN_3
#define KEY2_Pin GPIO_PIN_4

#define KEY1_GPIO_Port GPIOE
#define KEY2_GPIO_Port GPIOE

#define KEY1_GPIO_CLK_EN()           __HAL_RCC_GPIOE_CLK_ENABLE();
#define KEY2_GPIO_CLK_EN()           __HAL_RCC_GPIOE_CLK_ENABLE();

#define K1_STATUS             HAL_GPIO_ReadPin (KEY1_GPIO_Port, KEY1_Pin)
#define K2_STATUS             HAL_GPIO_ReadPin (KEY2_GPIO_Port, KEY2_Pin)

uint8_t KEY1_Value(void);
uint8_t KEY2_Value(void);

extern void KEY_GPIO_ReInit(void);
extern uint8_t KEY1_Value(void);
extern uint8_t KEY2_Value(void);






#endif //__DRIVER_KEY_H


