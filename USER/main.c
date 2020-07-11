/****************************************************************
//文件名：main.cpp
//作用：入口
****************************************************************/
//包含文件
#include "main.h"

#define DEBUG_MODE 0	//是否为调试模式 0为非调试模式 1为调试模式

//函数声明
void RC522_System_Init(void);
void genRandCode(u8* Des);
//全局变量
unsigned char card1[5] = {0x20, 0x25, 0x35, 0x55, 0x3F}; //卡序列号
unsigned char card2[4] = {0xDE, 0x8A, 0xDF, 0x2B}; //卡序列号

unsigned char snr, buf[16] = " ", bufr[16], TagType[2], SelectedSnr[4], DefaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
unsigned char Read_Data[16], PassWd[6], WriteData[16], RevBuffer[30], MLastSelectedSnr[4], NewKey[16];
char cardID[4];
char status;

u8 securityCode[7];

u8 modeFlag = 0; //0为读取验证模式，1为录入卡号模式，不要轻易更改，注意后面的代码
/****************************************************************
//函数名：main
//作用：入口函数
****************************************************************/
int main(void)
{
	RC522_System_Init();//初始化所有外部模块
	/*Start*/
	//显示开机欢迎界面
	OLED_Clear();
	OLED_ShowString(0, 0, "Welcome!", 16, 1);
	OLED_ShowString(0, 16, "RFID System", 16, 1);
	OLED_ShowString(0, 32, "Powered by WRL", 16, 1);
	OLED_ShowString(0, 48, "Version:0.01", 16, 1);
	OLED_Refresh();
	ws2812bSetAll(YELLOW);
	beepOneSecOn();

	if(Key_Scan(GPIOB, GPIO_Pin_12) == KEY_ON)//通电开机如果按键被按下则进入注册卡号模式
	{
		modeFlag = 1;
	}
	
	/*Discarded:
	TIM3_PWM_Init();//50Hz  1/50*1000=20ms
	TIM_SetCompare2(TIM3,6);
	*/
	
	//rainbow(30);
	//delay_ms(10);
	//rainbowCycle(10);

	//WIFI Connect
	char * ok = "OK";
	char * at = "AT\r\n";
	char * at_cwmode = "AT+CWMODE=1\r\n";
	char * at_rst = "AT+RST\r\n";
	char * at_cifsr = "AT+CIFSR\r\n";
	char * at_cipmux = "AT+CIPMUX=0\r\n";
	char * at_cipmode = "AT+CIPMODE=1\r\n";
	char * at_cipstart = "AT+CIPSTART=\"TCP\",\"192.168.0.13\",27015\r\n";
	char * at_cipsend = "AT+CIPSEND\r\n";

	char * WIFI_SSID = "Skye";  //wifi名称
	char * WIFI_KEY = "19790908";    //wifi密码

	char at_cwjap[64];
	memset(at_cwjap, 0, sizeof(at_cwjap));
	strcat(at_cwjap, "AT+CWJAP=\"");
	strcat(at_cwjap, WIFI_SSID);
	strcat(at_cwjap, "\",\"");
	strcat(at_cwjap, WIFI_KEY);
	strcat(at_cwjap, "\"\r\n");

	OLED_Clear();
	OLED_ShowString(0, 0, "Connect WIFI:", 16, 1);
	OLED_ShowString(0, 16, (u8*) WIFI_SSID, 16, 1);
	OLED_ShowString(0, 32, "Password:", 16, 1);
	OLED_ShowString(0, 48, (u8*) WIFI_KEY, 16, 1);
	OLED_Refresh();

	//第一条AT语句带一个空格因为不知道为什么最开始的一个字符会丢掉,好像和寄存器初始值有关,
	//经测试现在好像不用带了，不过为了保险起见还是多加上一句
	USART1_Send_Data("+++", strlen("+++"));
	delay_ms(100);//需要加延时不然会被后面发送的数据干扰导致无法退出透传模式
	USART1_Send_Data("+++", strlen("+++"));
	delay_ms(100);//需要加延时不然会被后面发送的数据干扰导致无法退出透传模式

	while(ESP8266_Send_Answer(at, ok)) {
		delay_ms(100);
	}
	while(ESP8266_Send_Answer(at_cwmode, ok)) {
		delay_ms(100);
	}
	while(ESP8266_Send_Answer(at_rst, ok)) {
		delay_ms(100);
	}
	while(ESP8266_Send_Answer(at_cwjap, ok)) {
		delay_ms(100);
	}
	OLED_Clear();
	OLED_ShowString(0, 0, "Connect WIFI:", 16, 1);
	OLED_ShowString(0, 16, "State: OK", 16, 1);
	OLED_ShowString(0, 32, "Ready TO:", 16, 1);
	OLED_ShowString(0, 48, "Server", 16, 1);
	OLED_Refresh();
	while(ESP8266_Send_Answer(at_cifsr, ok)) {
		delay_ms(100);
	}
	while(ESP8266_Send_Answer(at_cipmux, ok)) {
		delay_ms(100);
	}
	while(ESP8266_Send_Answer(at_cipmode, ok)) {
		delay_ms(100);
	}
	while(ESP8266_Send_Answer(at_cipstart, ok)) {
		delay_ms(100);
	}
	OLED_Clear();
	OLED_ShowString(0, 0, "Connect Server:", 16, 1);
	OLED_ShowString(0, 16, "State: OK", 16, 1);
	OLED_ShowString(0, 32, "Ready To:", 16, 1);
	OLED_ShowString(0, 48, "Communication", 16, 1);
	OLED_Refresh();
	while(ESP8266_Send_Answer(at_cipsend, ok)) {
		delay_ms(100);
	}

	//发送客户端身份识别编码
	char idCode[8] = "0000001";
	USART1_Send_Data(idCode, strlen(idCode));
	delay_ms(100);

	genRandCode(securityCode);

	beepOneSecOn();

	if(modeFlag == 0)
	{
		OLED_Clear();
		OLED_ShowString(0, 0, "Welcome!", 16, 0);
		OLED_ShowString(0, 16, "Use Card/Code Unlock", 12, 1);
		OLED_ShowString(0, 32, "Security Code:", 16, 1);
		OLED_ShowString(0, 48, securityCode, 16, 1);
		OLED_Refresh();
	}
	else if(modeFlag == 1)
	{
		OLED_Clear();
		OLED_ShowString(0, 0, "Welcome!", 16, 0);
		OLED_ShowString(0, 16, "New Card Regist", 16, 1);
		OLED_ShowString(0, 32, "Waiting For Card", 16, 1);
		OLED_ShowString(0, 48, "......", 16, 1);
		OLED_Refresh();
	}

	while (1)
	{
		if(URecv_Index) {
			if(strstr(URecv, "mode1state:ok") != NULL)
			{
				OLED_Clear();
				OLED_ShowString(0, 0, "Verify OK", 16, 0);
				OLED_ShowString(0, 16, "Opening Now!", 16, 1);
#if DEBUG_MODE==1
				OLED_ShowString(0, 32, "Server Return:", 16, 1);
				OLED_ShowString(0, 48, (u8*)URecv, 16, 1);

#endif
				OLED_Refresh();
				beepOneSecOn();
				
				relay_on();//继电器开启
				delay_ms(2000);
				relay_off();
			}
			else if(strstr(URecv, "mode0state:ok") != NULL)
			{
				OLED_Clear();
				OLED_ShowString(0, 0, "Registing OK", 16, 0);
				OLED_ShowString(0, 16, "Successfully!", 16, 1);
#if DEBUG_MODE==1
				OLED_ShowString(0, 32, "Server Return:", 16, 1);
				OLED_ShowString(0, 48, (u8*)URecv, 16, 1);

#endif
				OLED_Refresh();
				beepOneSecOn();
			}
			else
			{
				OLED_Clear();
				OLED_ShowString(0, 0, "Failed!", 16, 0);
				OLED_ShowString(0, 16, "Unknow Error!", 16, 1);
#if DEBUG_MODE==1
				OLED_ShowString(0, 32, "Server Return:", 16, 1);
				OLED_ShowString(0, 48, (u8*)URecv, 16, 1);

#endif
				OLED_Refresh();
				beepOneSecOn();
				delay_ms(200);
				beepOneSecOn();
			}


			if(modeFlag == 0)
			{
				genRandCode(securityCode);
				OLED_Clear();
				OLED_ShowString(0, 0, "Welcome!", 16, 0);
				OLED_ShowString(0, 16, "Use Card/Code Unlock", 12, 1);
				OLED_ShowString(0, 32, "Security Code:", 16, 1);
				OLED_ShowString(0, 48, securityCode, 16, 1);
				OLED_Refresh();
			}
			else if(modeFlag == 1)
			{
				OLED_Clear();
				OLED_ShowString(0, 0, "Welcome!", 16, 0);
				OLED_ShowString(0, 16, "New Card Regist", 16, 1);
				OLED_ShowString(0, 32, "Waiting For Card", 16, 1);
				OLED_ShowString(0, 48, "......", 16, 1);
				OLED_Refresh();
			}

			URecv_Index = 0;
			memset(URecv, 0, sizeof(URecv));
		}

		status = PcdRequest(REQ_ALL, TagType);
		if(!status)
		{
			status = PcdAnticoll(SelectedSnr);
			if(!status)
			{
				status = PcdSelect(SelectedSnr);
				if(!status)
				{
					snr = 1;  //扇区号1
					status = PcdAuthState(KEYA, (snr * 4 + 3), DefaultKey, SelectedSnr); // 校验1扇区密码，密码位于每一扇区第3块
					{
						if(!status)
						{
							status = PcdRead((snr * 4 + 0), buf); // 读卡，读取1扇区0块数据到buf[0]-buf[16]
							//buf[0]=2;buf[1]=2;buf[2]=3;buf[3]=4;buf[4]=5;buf[6]=1;;buf[7]=1;buf[8]=1;buf[9]=9;
							//status = PcdWrite((snr * 4 + 0), buf); // 写卡，将buf[0]-buf[16]写入1扇区0块
							if(!status)//process card
							{
								u8 cardIDChar[9], sendBuff[16];
								memset(cardIDChar,0,sizeof(cardIDChar));
								memset(sendBuff,0,sizeof(sendBuff));
								
								HexToStr(cardIDChar, 9, SelectedSnr, 4);

								if(modeFlag == 0)
								{
									sendBuff[0] = '0'; //模式标识符
									sendBuff[1] = 'D'; //默认卡
									sendBuff[2] = 0;
									strcat((char*)sendBuff, (char*)cardIDChar);
									USART1_Send_Data((char*)sendBuff, strlen((char*)sendBuff));
									delay_ms(100);

									OLED_Clear();
									OLED_ShowString(0, 0, "Verifying...", 16, 0);
									OLED_ShowString(0, 16, "Please Waiting!", 16, 1);
#if DEBUG_MODE==1
									OLED_ShowString(0, 32, "Card ID:", 16, 1);
									OLED_ShowString(0, 48, cardIDChar, 16, 1);
#endif
									OLED_Refresh();

								}
								else if(modeFlag == 1)
								{
									sendBuff[0] = '1'; //模式标识符
									sendBuff[1] = 'D'; //默认卡
									sendBuff[2] = 0;
									strcat((char*)sendBuff, (char*)cardIDChar);
									USART1_Send_Data((char*)sendBuff, strlen((char*)sendBuff));
									delay_ms(100);

									OLED_Clear();
									OLED_ShowString(0, 0, "Registing...", 16, 0);
									OLED_ShowString(0, 16, "Please Waiting!", 16, 1);
#if DEBUG_MODE==1
									OLED_ShowString(0, 32, "Card ID:", 16, 1);
									OLED_ShowString(0, 48, cardIDChar, 16, 1);
#endif
									OLED_Refresh();
								}

								LED_ON;
								//PcdAuthState(KEYA, (snr * 4 + 3), DefaultKey, SelectedSnr);
								//status = PcdRead((snr * 4 + 0), bufr);
								WaitCardOff();
							}
						}
					}
				}
			}
		}
		LED_OFF;
	}
}

void RC522_System_Init(void)
{
	beepInit();
	RC522_Init();
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
	OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	ESP8266_Init();
	ws2812bInit();
	buttonInit(key1_GPIO_CLK, key1_GPIO_PORT, key1_pin);
	relay_init();
	
	LED_OFF;
	delay_10ms(10);
	PcdReset();
	PcdAntennaOff();
	PcdAntennaOn();
	M500PcdConfigISOType( 'A' );
	LED_ON;
	delay_10ms(10);
	LED_OFF;
	delay_10ms(10);
	LED_ON;
	delay_10ms(10);
	LED_OFF;
}

void genRandCode(u8* Des)
{
	u8 temp[6], tempint[13];
	getRND(temp, 6);
	HexToStr(tempint, 13, temp, 6);
	int i, j = 0;
	for (i = 0; i < 6; i++)
	{
		if (tempint[i * 2] >= 65 && tempint[i * 2] <= 70)
		{
			tempint[i * 2] -= 6;
			j++;
		}
		if (tempint[i * 2 + 1] >= 65 && tempint[i * 2 + 1] <= 70)
		{
			tempint[i * 2 + 1] -= 6;
			j++;
		}
		Des[i] = (tempint[i * 2] + tempint[i * 2 + 1] - 7 * j) / 2;
		j = 0;
	}
}
