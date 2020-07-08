#include "rand.h"

static u8 isInitRND = 0;

/*
���ܣ�  ȡ��������ܳ�ʼ��
����1�� ��
���أ�  ��
*/
void initRND(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RND_RCC_APBxPeriphClockCmd;

    GPIO_InitStructure.GPIO_Pin = RND_Pinx;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(RND_GPIOx, &GPIO_InitStructure);

    ADC_DeInit(RND_ADCx);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(RND_ADCx, &ADC_InitStructure);

    ADC_Cmd(RND_ADCx, ENABLE);

    ADC_ResetCalibration(RND_ADCx);
    while(ADC_GetResetCalibrationStatus(RND_ADCx));
    ADC_StartCalibration(RND_ADCx);
    while(ADC_GetCalibrationStatus(RND_ADCx));

    ADC_RegularChannelConfig(RND_ADCx, RND_CHx, 1, ADC_SampleTime_239Cycles5);
	isInitRND=1;
}

/*
���ܣ�  ȡ�����
����1�� ��������
����2�� ����
���أ�  ��
*/
void getRND(u8 *dat, u16 len)
{
    uint8_t i;
    uint16_t value;

    if(!isInitRND)
    {
        initRND();
        isInitRND = 1;
    }
    memset(dat, 0, len);
    while(len)
    {
        for(i = 0; i < 8; i++)
        {
            ADC_SoftwareStartConvCmd(RND_ADCx, ENABLE);
            while(!ADC_GetFlagStatus(RND_ADCx, ADC_FLAG_EOC));

            value = ADC_GetConversionValue(RND_ADCx);
			
            dat[len - 1] <<= 1;
            dat[len - 1] |= (value & 0x01);
        }
        len--;
    }
}
