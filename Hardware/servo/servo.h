#include "stm32f10x.h"

/*��ʹ��TIM1��ͨ��1*/
#define            GENERAL_TIM                   TIM3
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM3
//����Ԥ��Ƶ�Ĵ���PSC��ֵΪ(7200-1),�ڲ�ʱ��Ϊ72MHz�������һ�ε�ʱ��Ϊ(7200/72000000)s=0.1ms;
#define            GENERAL_TIM_Prescaler         (72000-1)
//�����Զ�װ�ؼĴ���ARR��ֵΪ(200-1)����ô����һ�μ����жϵ�����Ϊ20ms�������������Ҫ���������
#define            GENERAL_TIM_Period            (20-1)

// TIM3 ����Ƚ�ͨ��1
#define            GENERAL_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM_CH1_PORT          GPIOB
#define            GENERAL_TIM_CH1_PIN           GPIO_Pin_5

void TIM3_PWM_Init(void);
