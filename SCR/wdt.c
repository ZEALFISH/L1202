#include  "IncludeAll.h"
void WdtInit(void)
{
 	RCEN = 1;
	WDTC = ((1<<3)|CONFIG_WRESET_TIME);
}


