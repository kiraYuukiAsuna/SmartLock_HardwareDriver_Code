#ifndef _RC522_H_
#define _RC522_H_

#include "stm32f10x.h"

//端口定义
#define MF522_RST_PIN                    GPIO_Pin_1
#define MF522_RST_PORT                   GPIOA
#define MF522_RST_CLK                    RCC_APB2Periph_GPIOA

#define MF522_MISO_PIN                   GPIO_Pin_4
#define MF522_MISO_PORT                  GPIOA
#define MF522_MISO_CLK                   RCC_APB2Periph_GPIOA

#define MF522_MOSI_PIN                   GPIO_Pin_5
#define MF522_MOSI_PORT                  GPIOA
#define MF522_MOSI_CLK                   RCC_APB2Periph_GPIOA

#define MF522_SCK_PIN                    GPIO_Pin_6
#define MF522_SCK_PORT                   GPIOA
#define MF522_SCK_CLK                    RCC_APB2Periph_GPIOA

#define MF522_NSS_PIN                    GPIO_Pin_7
#define MF522_NSS_PORT                   GPIOA
#define MF522_NSS_CLK                    RCC_APB2Periph_GPIOA

//指示灯
#define LED_PIN                          GPIO_Pin_13
#define LED_PORT                         GPIOC
#define LED_CLK                          RCC_APB2Periph_GPIOC

#define RST_H                            GPIO_SetBits(MF522_RST_PORT, MF522_RST_PIN)
#define RST_L                            GPIO_ResetBits(MF522_RST_PORT, MF522_RST_PIN)
#define MOSI_H                           GPIO_SetBits(MF522_MOSI_PORT, MF522_MOSI_PIN)
#define MOSI_L                           GPIO_ResetBits(MF522_MOSI_PORT, MF522_MOSI_PIN)
#define SCK_H                            GPIO_SetBits(MF522_SCK_PORT, MF522_SCK_PIN)
#define SCK_L                            GPIO_ResetBits(MF522_SCK_PORT, MF522_SCK_PIN)
#define NSS_H                            GPIO_SetBits(MF522_NSS_PORT, MF522_NSS_PIN)
#define NSS_L                            GPIO_ResetBits(MF522_NSS_PORT, MF522_NSS_PIN)
#define READ_MISO                        GPIO_ReadInputDataBit(MF522_MISO_PORT, MF522_MISO_PIN)
#define LED_ON                           GPIO_SetBits(LED_PORT, LED_PIN)
#define LED_OFF                          GPIO_ResetBits(LED_PORT, LED_PIN)

#define TRUE 1
#define FALSE 0

#endif
