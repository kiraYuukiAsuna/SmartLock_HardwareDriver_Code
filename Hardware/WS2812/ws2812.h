#ifndef __WS2812B_H__
#define __WS2812B_H__

#include <stdbool.h>
#include <stm32f10x_conf.h>
#include"delay.h"

#define RED 	0xff0000
#define ORANGE 	0xff7f00
#define YELLOW 	0xffff00
#define GREEN 	0x00ff00
#define BLUE 	0x0000ff
#define INDIGO 	0x4b0082
#define VIOLET 	0x9400d3
#define WHITE 	0xffffff

#define WS2812B_TEST                     0
#define WS2812B_GPIO_PERIF               RCC_APB2Periph_GPIOA
#define WS2812B_TIM_PERIF                RCC_APB2Periph_TIM1
#define WS2812B_TIM                      TIM1
#define WS2812B_DMA                      RCC_AHBPeriph_DMA1
#define WS2812B_DMA_CHANNEL              DMA1_Channel2
#define WS2812B_DMA_NVIC_IRQChannel      DMA1_Channel2_IRQn
#define WS2812B_GPIO_PORT                GPIOA
#define WS2812B_GPIO_PIN                 GPIO_Pin_8
#define WS2812B_TMI_CLOCK                24000000
#define WS2812B_TIM_PERIOD               29

#define WS2812B_NUM                      8
#define WS2812B_PULSE_BIT_SIZE           24
#define WS2812B_BUFF_SIZE                (24 * (WS2812B_NUM) + 43)   // Buffer size needs to be the number of LEDs times 24 bits plus 43 trailing bit
#define WS2812B_NVIC_PRI                 10
#define WS2812B_DMA_PeripheralBaseAddr   (uint32_t)&TIM1->CCR1;

#define WS2812B_PWM_HIGH_PULSE_WIDTH           19                    // Duty cycle of pwm signal for a logical 1 to be read by the ws2812 chip
#define WS2812B_PWM_LOW_PULSE_WIDTH            9                     // Duty cycle of pwm signal for a logical 0 to be read by the ws2812 chip
#define WS2812B_ALL_INDEX                      0

#define WS2812B_CREATE_PULSE_BUFF() do { \
        clr = color; \
        for (j = 0; j < WS2812B_PULSE_BIT_SIZE; j++) { \
            ws2812bBuff[k++] = clr & 0x800000 ? WS2812B_PWM_HIGH_PULSE_WIDTH : WS2812B_PWM_LOW_PULSE_WIDTH; \
            clr <<= 1; \
        } \
    } while(0)

void ws2812bInit(void);
bool ws2812bTest(void);
void ws2812bClear(const int index);
void ws2812bClearAll(void);
void ws2812bSet(const int index,  int color);
void ws2812bSet_RGB(const int index, uint32_t r, uint32_t g, uint32_t b);
uint32_t GRB_to_RGB(const uint32_t color);
void ws2812bSetAll(const int32_t color);
uint32_t setvalue(uint32_t red, uint32_t green, uint32_t blue);

void rainbow(uint8_t wait);
uint32_t Wheel(uint8_t WheelPos);	
void rainbowCycle(uint8_t wait);	
#endif
