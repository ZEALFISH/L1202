#include "IncludeAll.h"

volatile unsigned char g_bSwitchChlCnt;
volatile unsigned char g_bFlag1msArrived;
volatile unsigned char g_bFlag5msArrived;
volatile unsigned char g_bFlag10msArrived;
volatile unsigned char g_bFlag35msArrived;
volatile unsigned char g_bFlag100msArrived;
volatile unsigned char g_bFlag500msArrived;
volatile unsigned char g_bFlag1000msArrived;

void TimerInit(void)
{	
	/*T8N���ƼĴ���*/
	T8NC = 0B10001100;//   F=16/2/32=1/4M ;4us��������
	/*����T8N���ж�����*/
	T8N = CONFIG_TN8_INTERRUPT_PERIOD + TIMER_PERIOD_MIS;
	/*T8N����ж�ʹ��*/
	T8NIE=1;
	T8NEN = 1;
}	
//��
void Pwm12Init(void)
{
	/*pwm����=��T12P+1������1/16MHz����Ԥ��Ƶ��*/
	T12PL = PwmMax;     //����PWM���ڼĴ�����ʼֵ
	T12PH = 0x00;
	T12RL = 0;
	T12CH = 0x17;		//00010111,Ԥ��Ƶ��2
	T12C = 0x80;		//���ΪPWM����ģʽ
	TI2OC = 0X00;		//��ʼ��ʱ�Ȳ���pwm����
	PWM2C = 0X02;		//ռ�ձȵ���Ч
	T12EN = 0;			//�Ƚ�ֹ
}
//�¶�
void Pwm13Init(void)
{
#if 0
	//����PWM���ڼĴ�����ʼֵ: 0X03E7 = 999
	T13PL = 0XE7;
	T13PH &= 0X00;
	T13PH |= 0X03;
#endif
	
#if 1
	//����PWM���ڼĴ�����ʼֵ: 0X01F3 = 499
	T13PL = 0XF3;
	T13PH &= 0X00;
	T13PH |= 0X01;
#endif
	
	T13RL = 0;			//����pwm���ȼĴ���������ռ�ձȵĴ�С
	T13PH &= 0X0F;		//����λ
	T13CH = 0X00;		//Ԥ��Ƶ��1
	T13C = 0xFB ;		//Ԥ��Ƶ32�����Ƶ16
	T13OC =   ;			//����IO�˿����
	PWM3C |= 0x04;		//ռ�ձȸ���Ч
	T13EN = 1;			//����T13��ʱ��ʱ��
	ClosePwm_T13;		//����Ϊ��GPIO����
}

//����ռ�ձȴ�С����
void SetPwmDudy_T13(unsigned int pwmVal)
{
	T13RL = (pwmVal & 0xFF);
	T13PH &= 0X0F;
	T13PH |= (((pwmVal & 0x0F00)>>8)<<4);
}

