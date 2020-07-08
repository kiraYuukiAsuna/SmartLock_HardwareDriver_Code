#include "servo.h"

//����һ����ʼ��������ͬʱ��ʼ��ʱ��������Ƚ�
void TIM3_PWM_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //ѡ��Timer3������ӳ��
//ѡ��ʱ��3��ͨ��2��ΪPWM���������TIM3_CH2->PB5    GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�������칦��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ������

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//�����ʼ���ṹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʹ�ܶ�ʱ��3ʱ��
//��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = 199; //�Զ���װ�ؼĴ�����ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t)7199; //TIMXԤ��Ƶ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //�������Ϲ��ܶԶ�ʱ�����г�ʼ��

	TIM_OCInitTypeDef  TIM_OCInitStructure;//����ṹ��
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//ѡ��ʱ��ģʽ��TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//����Ƚϼ��Ե�
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);//���ݽṹ����Ϣ���г�ʼ��
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ�ܶ�ʱ��TIM2��CCR2�ϵ�Ԥװ��ֵ

	TIM_Cmd(TIM3, ENABLE);  //ʹ�ܶ�ʱ��TIM3
}
