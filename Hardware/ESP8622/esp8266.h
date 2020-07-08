#include "delay.h"
#include <stdlib.h>
#include <string.h>

extern char URecv[256];
extern u16 URecv_Index;

void ESP8266_Init(void);
char ESP8266_Send_Answer(char *cmd, char * answer);
void USART1_Send_Data(char *buf, u16 len);
