#include  "IncludeAll.h"


static unsigned char  g_bKeyReadata;
static unsigned char  g_bKeyTrigger;
static unsigned char  g_bKeyContinue;
static unsigned char  g_bKeyReleased;

static void ReadKey(void)
{
	g_bKeyReadata  = KEY_PORT ^ 0XFF;
	g_bKeyTrigger  = g_bKeyReadata ^ g_bKeyContinue;
	g_bKeyTrigger  = g_bKeyReadata & g_bKeyTrigger;
	g_bKeyReleased = g_bKeyReadata ^ g_bKeyTrigger;
	g_bKeyReleased = g_bKeyReleased ^ g_bKeyContinue;
	g_bKeyContinue = g_bKeyReadata;
}


void KeyScan(void)
{
	






}
