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
	/*T8N控制寄存器*/
	T8NC = 0B10001100;//   F=16/2/32=1/4M ;4us计数周期
	/*设置T8N的中断周期*/
	T8N = CONFIG_TN8_INTERRUPT_PERIOD + TIMER_PERIOD_MIS;
	/*T8N溢出中断使能*/
	T8NIE=1;
	T8NEN = 1;
}	
//灯
void Pwm12Init(void)
{
	/*pwm周期=（T12P+1）×（1/16MHz）×预分频比*/
	T12PL = PwmMax;     //设置PWM周期寄存器初始值
	T12PH = 0x00;
	T12RL = 0;
	T12CH = 0x17;		//00010111,预分频器2
	T12C = 0x80;		//设计为PWM工作模式
	TI2OC = 0X00;		//初始化时先不打开pwm功能
	PWM2C = 0X02;		//占空比低有效
	T12EN = 0;			//先禁止
}
//温度
void Pwm13Init(void)
{
#if 0
	//设置PWM周期寄存器初始值: 0X03E7 = 999
	T13PL = 0XE7;
	T13PH &= 0X00;
	T13PH |= 0X03;
#endif
	
#if 1
	//设置PWM周期寄存器初始值: 0X01F3 = 499
	T13PL = 0XF3;
	T13PH &= 0X00;
	T13PH |= 0X01;
#endif
	
	T13RL = 0;			//设置pwm精度寄存器，决定占空比的大小
	T13PH &= 0X0F;		//高四位
	T13CH = 0X00;		//预分频器1
	T13C = 0xFB ;		//预分频32，后分频16
	T13OC =   ;			//设置IO端口输出
	PWM3C |= 0x04;		//占空比高有效
	T13EN = 1;			//开启T13定时器时钟
	ClosePwm_T13;		//设置为非GPIO功能
}

//设置占空比大小函数
void SetPwmDudy_T13(unsigned int pwmVal)
{
	T13RL = (pwmVal & 0xFF);
	T13PH &= 0X0F;
	T13PH |= (((pwmVal & 0x0F00)>>8)<<4);
}

