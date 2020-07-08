#ifndef _RND_H
#define _RND_H

#include "stm32f10x.h"
#include "string.h"

#define RND_GPIOx       GPIOC
#define RND_Pinx        GPIO_Pin_0

#define RND_ADCx        ADC2
#define RND_CHx         ADC_Channel_10

#define RND_RCC_APBxPeriphClockCmd  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC2,ENABLE)

void getRND(u8 *dat, u16 len);
void initRND(void);

#endif
