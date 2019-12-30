#include "IncludeAll.h"

sbit bRedIOTmpTimer;//只是读一下,以便外部中断标志位能清除


static unsigned char g_bCounterTime100us = 0;
static unsigned char g_bCounterTime5ms = 0;
static unsigned char g_bCounterTime10ms = 0;
static unsigned char g_bCounterTime35ms = 0;
static unsigned char g_bCounterTime100ms = 0;
static unsigned char g_bCounterTime500ms = 0;
static unsigned char g_bCounterTime1000ms = 0;

void isr(void) interrupt
{
	static unsigned char step = 0;
	unsigned char RecData;
	//ADC转换完成中断
	if(ADIE&ADIF)
	{
		ADIF = 0;
		......//补充。。。。。。
		
	}
	//T8N定时中断
	if(T8NIE&T8NIF)
	{
		T8NIF = 0;
		//======1ms=====
		g_bFlag1msArrived = 1;
		//======5ms=====
		if(++g_bCounterTime5ms >=5)
		{
			g_bCounterTime5ms = 0;
			g_bFlag5msArrived = 1；
			//======35ms=====
			if(++g_bCounterTime35ms>=7)
			{
				g_bCounterTime35ms = 0;
				g_bFlag35msArrived = 1;
			}
			//======10ms=====
			if(++g_bCounterTime10ms = 2)
			{
				g_bCounterTime10ms = 0;
				g_bFlag10msArrived = 1;
				//======100ms=====
				if(++g_bCounterTime100ms >= 10)
				{
					g_bCounterTime100ms = 0;
					g_bFlag100msArrived = 1;
					//=====500ms=====
					if(++g_bCounterTime500ms >= 5)
					{
						g_bCounterTime500ms = 0;
						g_bFlag500msArrived = 1;
						//=====1000ms=====
						if(++g_bCounterTime1000ms >= 2)
						{
							g_bCounterTime1000ms = 0;
							g_bFlag1000msArrived = 1;
						}
					}
				}
			}
		}
	
	}
	
	//外部按键中断
	if(KIE&KIF)
	{
		bRedIOTmpTimer = KEY_Pin;//清除按键中断标志位前要对相应的端口进行一次读或写
		KIF = 0;
		
	}

	
#ifdef UART_FUNC   //UART收发中断
	/*需要注意的是， 接收/发送中断标志位 RXIF/TXIF为只读，不可软件清零，
	读接收数据寄存器 RXB，可清除 RXIF， 写发送数据寄存器 TXB，可清除 TXIF；
	接收/发送中断使能位 RXIE/TXIE 需通过软件清除。*/
	if(REIE&RXIF)
	{
		RecData = RXB; //获得数据
		switch(step)
		{
			case 0:
			{
				if(RecData ==COMM_HEAT0)//确定包头1
				{
					g_UsartRecv[step] = 0x88;
					step = 1;
				}
			}
			break;
			case 1:
			{
				if(RecData ==COMM_HEAT1)//确定包头2
				{
					g_UsartRecv[step] = 0x77;
					step = 2;
				}
				else
				{
					step =0
				}
			}
			break;
			case 3:
				{
					g_UsartRecv[step] = RecData;
					step++;
				}
			break;
			case 4:
				{
					g_bFlagRecvedPackageData = 1;
					g_UsartRecv[step] = 0xAA;//包尾
				}
			break;
			default:break;
		}
	}

	
	if(TXIE&TXIF)
	{
		if(g_UsartSendCount<g_UsartShouldSendNums)
		{
			TXB = g_UsartSend[g_UsartSendCount++]
		}
		else
		{
			TXIE = 0;
			g_UsartSendCount = 0;
		}
	}
	#endif
}

