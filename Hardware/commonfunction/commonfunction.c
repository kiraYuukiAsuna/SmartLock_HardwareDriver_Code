#include "commonfunction.h"

/****************************************************************
//函数名：HexToStr
//作用：入口函数
****************************************************************/
int HexToStr(unsigned char* lpDes, int iMaxLength, const unsigned char* lpSrc, int iSrcLen)
{
	int iRet   = 0;
	int iIndex = 0;
	unsigned char chTmep = 0;

	if(NULL == lpSrc || NULL == lpDes || iMaxLength < (iSrcLen * 2 + 1))
	{
		return 0;
	}//end if(NULL == lpSrc || NULL == lpDes || iMaxLength < (iSrcLen*2 + 1))

	for(iIndex = 0; iIndex < iSrcLen; iIndex++)
	{
		*(lpDes + iIndex * 2)     =  ((chTmep = *(lpSrc + iIndex) / 16) >= 10) ? (chTmep - 10 + 'A') : (chTmep + '0');
		*(lpDes + iIndex * 2 + 1) =  ((chTmep = *(lpSrc + iIndex) % 16) >= 10) ? (chTmep - 10 + 'A') : (chTmep + '0');
		iRet += 2;
	}//end for(iIndex = 0; iIndex < iSrcLen; iIndex++)

	*(lpDes + iRet) = 0;
	return iRet;
}
//整形转字符，stm32不支持标准的itoa,这里自己实现
char *myitoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;
 
    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }
 
    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }
 
    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';
 
        /* Make the value positive. */
        value *= -1;
    }
 
    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;
 
        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }
 
    /* Null terminate the string. */
    *ptr = 0;
 
    return string;
 
} /* NCL_Itoa */
 
//字符串转整形，stm32不支持标准的atoi,这里自己实现
int myatoi(const char *str)
{
	int s=0;
	uint8_t falg=0;
	
	while(*str==' ')
	{
		str++;
	}
 
	if(*str=='-'||*str=='+')
	{
		if(*str=='-')
		falg=1;
		str++;
	}
 
	while(*str>='0'&&*str<='9')
	{
		s=s*10+*str-'0';
		str++;
		if(s<0)
		{
			s=2147483647;
			break;
		}
	}
	return s*(falg?-1:1);
}
