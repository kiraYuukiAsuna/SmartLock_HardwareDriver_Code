#include "relay.h"

void relay_init(void)

{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RELAY_ENABLE_PORT, ENABLE);

	GPIO_InitStructure.GPIO_Pin = RELAY_PORT ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(RELAY_PORTFAMILY, &GPIO_InitStructure);
}          

//relay on PB7
void relay_on(void)
{
  GPIO_SetBits(GPIOB,RELAY_PORT);
}

//relay off PB7
void relay_off(void)
{ 
  GPIO_ResetBits(GPIOB,RELAY_PORT);
}
