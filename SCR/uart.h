#ifndef __UART_H__
#define __UART_H__

extern unsigned char g_UsartShouldSendNums;
extern unsigned char g_UsartSendCount;
extern volatile unsigned char g_UsartSend[USART_MAX_SEND_NUM];


extern void UartInit(void);
extern void UsartSendBytes(unsigned char* buffer,unsigned char len);
extern void PrintVal(unsigned int prtval);
extern void Num2Strint(unsigned int x ,unsigned char *str);


#endif
