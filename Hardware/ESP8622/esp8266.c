#include "esp8266.h"

char URecv[128] = {0x0};
u16 URecv_Index = 0;

void Uart1_Init(u32 baud)
{
	int i = 0;
	u8 baud_valid = 0;
	u32 baud_all[8] = {1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200};
	u32 baud232 = baud;

	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9

	//USART1_RX	  GPIOA.10初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10

	//USART 初始化设置
	for(i = 0; i < 8; i++) {
		if(baud232 == baud_all[i]) {
			baud_valid = 1;
			continue;
		}
	}
	if(!baud_valid) {
		baud232 = 115200;
	}
	USART_InitStructure.USART_BaudRate = baud232;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART1, &USART_InitStructure); //初始化串口1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接收中断
	//USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//开启串口空闲中断
	USART_Cmd(USART1, ENABLE);                    //使能串口1

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3 ; //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
}

void USART1_IRQHandler(void)
{
	u8 clear = clear;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		URecv[URecv_Index++] = USART1->DR;
		if(URecv_Index == 128) {
			URecv_Index = 0;
		}
	}
}

void USART1_Send_Data(char *buf, u16 len)
{
	u16 t;
	for(t = 0; t < len; t++) {
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); //循环发送,直到发送完毕
		USART_SendData(USART1, buf[t]);
	}
}

void ESP8266_Init()
{
	delay_init();

	Uart1_Init(9600);
}

char ESP8266_Send_Answer(char *cmd, char * answer)
{
	char timeout = 10;
	char exec = 0;
	USART1_Send_Data(cmd, strlen((const char *)cmd));
	while(timeout --) {
		if(URecv_Index) {
			if(strstr(URecv, answer) != NULL) {
				exec = 1;
				break;
			}
		}
		delay_ms(100);
	}
	URecv_Index = 0;
	memset(URecv, 0, sizeof(URecv));
	if(exec) {
		return 0;
	} else {
		return 1;
	}
}
