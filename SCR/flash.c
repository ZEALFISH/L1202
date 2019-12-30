#include "IncludeAll.h" 

//*****************************************************************************
//                                Flash������
//*****************************************************************************
void ReadFlash(void)
{
    FRAH = FlashAddr.Byte[1];   //���ö�������ʼ��ַ
    FRAL = FlashAddr.Byte[0];
    GIE = 0;					//��������ȫ���жϣ����ֹ�ж�
    __asm
	{
        TBR                     //��������ȡ���ݵ�ROMDH/ROMDL�Ĵ���
		NOP
		NOP
		NOP
		NOP
    }
    FlashData.Byte[1] = ROMDH;
    FlashData.Byte[0] = ROMDL;
    GIE = 1;					//���¿���ȫ���ж�
}
//*****************************************************************************
//                                Flash��������
//*****************************************************************************
void EraseFlash(void)
{
    FRAH = FlashAddr.Byte[1];
    FRAL = FlashAddr.Byte[0];
    
    __asm
	{
        BCC INTG,GIE       //��������ȫ���жϣ����ֹ�ж�
        BSS ROMCL,FPEE     //ѡ��Flash����
        BSS ROMCL,WREN     //ʹ��Flash����
        MOVI 0x55
        MOVA ROMCH         //0x55д������洢��
        NOP                //8��NOPָ��
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        MOVI 0xAA
        MOVA ROMCH         //0xAAд������洢��
        NOP                //8��NOPָ��
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        BSS ROMCL,WR       //��������
		NOP
		NOP			  
        JBC ROMCL,WR       //�ж��Ƿ����������־
        GOTO $-1           //�ȴ���������
        BCC ROMCL,WREN     //��ֹFlash����
        BSS INTG,GIE       //���¿���ȫ���ж�
    }
}
 
//*****************************************************************************
//                                Flashд����
//*****************************************************************************    
void WriteFlash(void)
{
    FRAH=FlashAddr.Byte[1];     //����д�����ʼ��ַ
    FRAL=FlashAddr.Byte[0];
    ROMDH=FlashData.Byte[1];    //����д�������
    ROMDL=FlashData.Byte[0];
    __asm
	{
        BCC  INTG,GIE      //�ر�ȫ���ж�
        BCC  ROMCL,FPEE    //ѡ��д����
        BSS  ROMCL,WREN    //ʹ��д
        MOVI 0x55
        MOVA ROMCH         //0x55д������洢��
        NOP                //8��NOPָ��
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        MOVI 0xAA
        MOVA ROMCH         //0xAAд������洢��
        NOP                //8��NOPָ��
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        BSS ROMCL,WR       //����д  
		NOP
		NOP
        JBC ROMCL,WR       //�ж��Ƿ�д������־
        GOTO $-1           //�ȴ�д����
        BCC ROMCL,WREN     //��ֹFlashд
        BSS INTG,GIE       //���¿���ȫ���ж�
    }
}

