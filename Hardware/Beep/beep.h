/****************************************************************
//文件名：beep.h
//作用：蜂鸣器
****************************************************************/
#include "stm32f10x.h"

//默认有源蜂鸣器端口
#define BEEP_ENABLE_PORT RCC_APB2Periph_GPIOA
#define BEEP_PORT GPIO_Pin_0
#define BEEP_PORTFAMILY GPIOA

void beepInit(void);
void beepState(BitAction bitAction);
void beepOn(void);
void beepOff(void);
void beepOneSecOn(void);
