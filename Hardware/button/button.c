#include "button.h"

void buttonInit(uint32_t Button_ENABLE_PORT,GPIO_TypeDef* Button_PORTFAMILY,uint16_t Button_PORT)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(Button_ENABLE_PORT, ENABLE);

	GPIO_InitStructure.GPIO_Pin = Button_PORT ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//按键对地，上拉输入
	GPIO_Init(Button_PORTFAMILY, &GPIO_InitStructure);
}

/*
*按键按下标志宏
*按按键按下为高电平，设置KEY_ON = 1 , KEY_OFF = 0
*若按键按下为低电平，设置KEY_ON = 0 , KEY_OFF = 1 即可
*/
 
/**
	* @brief		检测是否有按键按下
	* @param		GPIOx:具体的端口，x可以是（A...K）
	* @param		GPIO_PIN:具体的端口位，可以是GPIO_PIN_x(x可以是0...15)
	* @retval		按键的状态
	* @arg  		KEY_ON  :按键按下
	* @arg			KEY_OFF :按键没按下
	*/
uint8_t	Key_Scan(GPIO_TypeDef* GPIOx , uint16_t GPIO_Pin )
{
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON)                  //Detect whether the key is pressed
	{
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);     //Loosen the detection
		return KEY_ON;
	}
	else
	{
		return KEY_OFF;
	}
}
