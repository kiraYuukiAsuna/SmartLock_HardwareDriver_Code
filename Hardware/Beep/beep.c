/****************************************************************
//文件名：beep.c
//作用：蜂鸣器
****************************************************************/
#include "beep.h"
#include "delay.h"

void beepInit(void)
{
	delay_init();
	
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(BEEP_ENABLE_PORT, ENABLE);

	GPIO_InitStructure.GPIO_Pin = BEEP_PORT ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(BEEP_PORTFAMILY, &GPIO_InitStructure);

	beepState(Bit_SET);
}

void beepState(BitAction bitAction)
{
	GPIO_WriteBit(BEEP_PORTFAMILY, BEEP_PORT, bitAction);
}

void beepOn(void)
{
	beepState(Bit_RESET);
}

void beepOff()
{
	beepState(Bit_SET);
}

void beepOneSecOn()
{
	beepState(Bit_RESET);
	delay_ms(200);
	beepState(Bit_SET);
}
