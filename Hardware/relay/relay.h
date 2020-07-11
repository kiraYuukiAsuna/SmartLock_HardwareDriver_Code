#include "stm32f10x.h"

#define RELAY_ENABLE_PORT RCC_APB2Periph_GPIOB
#define RELAY_PORTFAMILY GPIOB
#define RELAY_PORT	GPIO_Pin_7

void relay_init(void);
void relay_on(void);
void relay_off(void);
