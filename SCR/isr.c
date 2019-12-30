#include "IncludeAll.h"

sbit bRedIOTmpTimer;//ֻ�Ƕ�һ��,�Ա��ⲿ�жϱ�־λ�����


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
	//ADCת������ж�
	if(ADIE&ADIF)
	{
		ADIF = 0;
		......//���䡣����������
		
	}
	//T8N��ʱ�ж�
	if(T8NIE&T8NIF)
	{
		T8NIF = 0;
		//======1ms=====
		g_bFlag1msArrived = 1;
		//======5ms=====
		if(++g_bCounterTime5ms >=5)
		{
			g_bCounterTime5ms = 0;
			g_bFlag5msArrived = 1��
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
	
	//�ⲿ�����ж�
	if(KIE&KIF)
	{
		bRedIOTmpTimer = KEY_Pin;//��������жϱ�־λǰҪ����Ӧ�Ķ˿ڽ���һ�ζ���д
		KIF = 0;
		
	}

	
#ifdef UART_FUNC   //UART�շ��ж�
	/*��Ҫע����ǣ� ����/�����жϱ�־λ RXIF/TXIFΪֻ��������������㣬
	���������ݼĴ��� RXB������� RXIF�� д�������ݼĴ��� TXB������� TXIF��
	����/�����ж�ʹ��λ RXIE/TXIE ��ͨ����������*/
	if(REIE&RXIF)
	{
		RecData = RXB; //�������
		switch(step)
		{
			case 0:
			{
				if(RecData ==COMM_HEAT0)//ȷ����ͷ1
				{
					g_UsartRecv[step] = 0x88;
					step = 1;
				}
			}
			break;
			case 1:
			{
				if(RecData ==COMM_HEAT1)//ȷ����ͷ2
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
					g_UsartRecv[step] = 0xAA;//��β
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

