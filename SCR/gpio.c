#include "IncludeAll.h"

/******��ģ�˿ڿ��ƼĴ�����ANSL��ANSH��
0��ģ������,
1����������
PA����----->ANSL
PB����----->ANSH
******/

/******�˿�����������ƼĴ�����PAT��
0�����״̬
1������״̬
PA2�̶�Ϊ����״̬
******/

/******�˿����������ƼĴ�����PAPU��
0����ֹ
1��ʹ��
******/

/******�˿����������ƼĴ�����PAPD��
0����ֹ
1��ʹ��
******/

//PA0

void GpioInit(void)
{
/******PA�˿�*******/
	ANSL =		;// 1111 1111
	PAT  =		;// 1111 1111
	PAPD =		;// 1111 1111
	PAPU =		;// 1111 1111
/******PB�˿�*******/
	ANSH =		;// 1111 1111
	PBT  =		;// 1111 1111
	PBPD =		;// 1111 1111
	PBPU =		;// 1111 1111
/******PC�˿�******/
	PCT0  = 0;			/* PC0: ����Ϊ���*/
	PCPU0 = 1;			/* PC0: �������� */
	PC0   = 1;			/* PC0: ����ߵ�ƽ */

	PCT1  = 0;			/* PC1: ����Ϊ���*/
	PCPU1 = 1;			/* PC1: �������� */
	PC1   = 1;			/* PC1: ����ߵ�ƽ */
}

void DevInit(void)
{


}
void SetUnUsedGpio(void)
{


}