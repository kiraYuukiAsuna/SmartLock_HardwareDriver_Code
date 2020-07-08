#include "button.h"

void buttonInit(uint32_t Button_ENABLE_PORT,GPIO_TypeDef* Button_PORTFAMILY,uint16_t Button_PORT)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(Button_ENABLE_PORT, ENABLE);

	GPIO_InitStructure.GPIO_Pin = Button_PORT ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//�����Եأ���������
	GPIO_Init(Button_PORTFAMILY, &GPIO_InitStructure);
}

/*
*�������±�־��
*����������Ϊ�ߵ�ƽ������KEY_ON = 1 , KEY_OFF = 0
*����������Ϊ�͵�ƽ������KEY_ON = 0 , KEY_OFF = 1 ����
*/
 
/**
	* @brief		����Ƿ��а�������
	* @param		GPIOx:����Ķ˿ڣ�x�����ǣ�A...K��
	* @param		GPIO_PIN:����Ķ˿�λ��������GPIO_PIN_x(x������0...15)
	* @retval		������״̬
	* @arg  		KEY_ON  :��������
	* @arg			KEY_OFF :����û����
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
