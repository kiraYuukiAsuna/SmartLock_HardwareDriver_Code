#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"

void hexToStr(u8 * sSrc, u8 * sDest, int nSrcLen);
int HexToStr(unsigned char* lpDes, int iMaxLength, const unsigned char* lpSrc, int iSrcLen);
char *myitoa(int value, char *string, int radix);
int myatoi(const char *str);
