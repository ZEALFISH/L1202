#include "IncludeAll.h"

void AdcInit(void)
{
	//Setp1：选择AD高速转换模式
 	ADHSEN =1;
	ADVCMHS = 1;
	//Step2：选择ADC转换时钟，
	ADCKS2 = 1;   
	ADCKS1 = 0;
	ADCKS0 = 1;//101：Fosc/32 = 1/32MHz
	//Step 3：选择ADC参考电压源，通过ADCCH寄存器中的ADVREFS <1:0>位进行选择。
	ADVREFS1 = 0;  //01：参考电压正端为内部VREF，负端为VSS
	ADVREFS0 = 1;
	/*VRC3：参考电压控制寄存器3
	Bit 7 客户需设置为1
	Bit 6 VREFSEL：ADC和运放模块的参考电压选择位
			0：1.8V
			1：2.5V
	Bit 5~1 保留未用
	Bit 0 客户需设置为1
		0b 1100  0001,	选2.5V */
	VREFEN = 1;
	VRC3 = 0xC9;
	//Step 4：选择ADC采样时间，通过ADCCH寄存器中的A/D采样时间选择位ADST <1:0>设定
	ADST1 = 1;	//11：大约16 个Tadclk
	ADST0 = 1;
	//Step 5：选择ADC采样模式，通过ADCCL寄存器中的A/D采样模式选择位SMPS选择
	SMPS = 1;  //1:硬件模式
	//Step 6：设置复用端口设为模拟类型，即选择哪些管脚作为ADC转换输入管脚，由端口数模控制寄存器ANSL、ANSH控制选择。在I/0处已经初始化了
	//ANSL = 0xFF;
	//ANSH = 0xF3;	   // 1111 0011  OUT_CHK,BAT_CHK
	//Step 7：选择模拟信号输入通道AINx，通过ADCCL寄存器中的ADCHS <3:0>选择ADC模拟通道。
	/*********** 一上电选择BAT通道***************************/
	ADCHS3 = 1;
	ADCHS2 = 0;
	ADCHS1 = 0;
	ADCHS0 = 1;//暂时先设置通道AIN9
	//Step 8：设置转换结果对齐方式，通过ADCCH寄存器中的ADFM位，选择高位对齐放置还是低位对齐放置。
	ADFM = 1;	//1：低位对齐（ADCRH<3:0>, ADCRL<7:0>)
	//Step 9：如果要使用中断，则中断控制寄存器需要正确地设置，以确保A/D 中断功能被正确激活
	//ADIE = 1;
	ADIE = 0;//中断先关闭

	GIEL = 0;
	///////////////////////GIE = 1;////////////////////////////////
	//Step 10：使能ADC电路，将ADCCL寄存器中的ADC使能位ADEN设置为“1”。
	ADEN = 1;
	//Step 11：当ADCCL寄存器中的SMPS=0时，选择软件采样模式，设置ADCCL寄存器中的SMPON=1启动采样，ADCCL寄存器中的ADTRG位硬件自动置1；
	//SMPON = 1;
	//Step 12：轮询ADCCL寄存器中的转换状态位ADTRG位，确定此次A/D转换是否完成。
	//Step 13：读取ADCRH和ADCRL寄存器中的转换结果。

	//初始设置为电池采集通道
	ADCCL = (ADCCL&0x0F)|((BAT_CHL<<4));
	ADTRG = 0;

	//============PWM边沿触发ADC的配置======================
	PWM3ADEN = 0;//PWM沿启动 ADC关闭
	PWM3ADS = 0; //内部计数器在 PWM 的上升沿开始计数
	TMRADC = 2;	//当计数器计数值大于TMRADC 时，产生启动 A/D 转换的触发信号


}

