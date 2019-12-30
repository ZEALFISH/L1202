#include "IncludeAll.h"

unsigned char g_UsartRecv[6];
unsigned char g_bFlagRecvedPackageData = 0;

volatile unsigned char g_UsartSend[USART_MAX_SEND_NUM]={0};

void UartInit(void)
{
	PC = 0;         //����PC�˿�����͵�ƽ
	PCT1 = 0;       //TX�������
	PCT0 = 1;       //RX��������
	BRGH = 1;       //�����ʸ���ģʽ��Fosc/(16*(BRR+1))
	BRR = 103;       //���ò�����9600��BRR=2MHz/9600/16-1
	TXM = 0;        //����8λ���ݸ�ʽ
	TXEN = 1;       //UART����ʹ��
	RXM = 0;        //����8λ���ݸ�ʽ
	RXEN = 1;       //UART����ʹ��

	RXIE = 1;       //UART�����ж�ʹ��
	TXIE = 1;		//UART�����ж�ʹ��

	GIE = 1;        //��ȫ���ж�
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
//���ڴ�ӡ��ֵ
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

