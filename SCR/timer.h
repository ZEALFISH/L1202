#ifndef __TIMER_H__
#define __TIMER_H__
/*配置TN8的中断频率：T8N =(256-X/4)*/
#define TIMER_PERIOD_MIS    5
#define INT_PERIOD_100US  (256-25)
#define INT_PERIOD_500US  (256-100)
#define INT_PERIOD_1000US  (256-250)

#define PwmMax  249

#define ClosePwm_T13()		T13OC = 0X00  // PA7 为通用GPIO


extern void TimerInit(void);
extern void Pwm12Init(void);
extern void Pwm13Init(void);
extern void SetPwmDudy_T13(unsigned int pwmVal);



#endif
