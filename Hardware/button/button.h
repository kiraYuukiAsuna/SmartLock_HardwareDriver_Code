#ifndef _BSP_KEYSCAN_H
#define _BSP_KEYSCAN_H
#include "stm32f10x.h"

/*************************引脚定义***********************/
#define		key1_pin		  		GPIO_Pin_12
#define		key1_GPIO_PORT        	GPIOB
#define		key1_GPIO_CLK			RCC_APB2Periph_GPIOB

#define		KEY_ON		0			//按键对地，上拉输入
#define		KEY_OFF		1

void buttonInit(uint32_t Button_ENABLE_PORT, GPIO_TypeDef* Button_PORTFAMILY, uint16_t Button_PORT);
uint8_t	Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin );

#endif
