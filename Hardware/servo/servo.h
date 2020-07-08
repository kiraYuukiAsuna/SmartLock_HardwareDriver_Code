#include "stm32f10x.h"

/*先使用TIM1的通道1*/
#define            GENERAL_TIM                   TIM3
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM3
//配置预分频寄存器PSC的值为(7200-1),内部时钟为72MHz，则计数一次的时间为(7200/72000000)s=0.1ms;
#define            GENERAL_TIM_Prescaler         (72000-1)
//配置自动装载寄存器ARR的值为(200-1)，那么产生一次计数中断的周期为20ms，与驱动舵机需要的周期相符
#define            GENERAL_TIM_Period            (20-1)

// TIM3 输出比较通道1
#define            GENERAL_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM_CH1_PORT          GPIOB
#define            GENERAL_TIM_CH1_PIN           GPIO_Pin_5

void TIM3_PWM_Init(void);
