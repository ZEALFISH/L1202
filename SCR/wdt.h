#ifndef __WDT_H__
#define __WDT_H__

#define WRST_TIME_16MS		(0)
#define WRST_TIME_32MS		(1)
#define WRST_TIME_64MS		(2)
#define WRST_TIME_128MS		(3)
#define WRST_TIME_256MS		(4)
#define WRST_TIME_512MS		(5)
#define WRST_TIME_1024MS	(6)
#define WRST_TIME_2048MS	(7)

#define ClrWdt() __Asm CWDT

extern void WdtInit(void);
#endif
