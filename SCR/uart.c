#include "IncludeAll.h"

unsigned char g_UsartRecv[6];
unsigned char g_bFlagRecvedPackageData = 0;

volatile unsigned char g_UsartSend[USART_MAX_SEND_NUM]={0};

void UartInit(void)
{
	PC = 0;         //设置PC端口输出低电平
	PCT1 = 0;       //TX方向输出
	PCT0 = 1;       //RX方向输入
	BRGH = 1;       //波特率高速模式，Fosc/(16*(BRR+1))
	BRR = 103;       //设置波特率9600，BRR=2MHz/9600/16-1
	TXM = 0;        //发送8位数据格式
	TXEN = 1;       //UART发送使能
	RXM = 0;        //接收8位数据格式
	RXEN = 1;       //UART接收使能

	RXIE = 1;       //UART接收中断使能
	TXIE = 1;		//UART发送中断使能

	GIE = 1;        //开全局中断
}

void UsartSendBytes(unsigned char* buffer,unsigned char len)
{
	unsigned char i;

    g_UsartShouldSendNums = len;
	if(g_UsartSendCount) return;
    for(i = 0;i < len;i++)
    g_UsartSend[i] = buffer[i];

	TXIE = 1;
}
//串口打印数值
void PrintVal(unsigned int prtval)
{
	unsigned char str_tmp[6] = [0];
	memset(str_tmp,0,6);
	Num2Strint(prtval,str_tmp);
	UsartSendBytes(str_tmp,6);
}
void Num2Strint(unsigned int x ,unsigned char *str)
{
	str[0] = '0'+x/1000;
	str[1] = '0'+(x%1000)/100;
	str[2] = '0'+((x%1000)%100)/10;
	str[3] = '0'+(x%10);
	str[4] = '\r';
	str[5] = '\n';
}

