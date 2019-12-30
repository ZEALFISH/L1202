#include "IncludeAll.h" 

//*****************************************************************************
//                                Flash读函数
//*****************************************************************************
void ReadFlash(void)
{
    FRAH = FlashAddr.Byte[1];   //设置读出的起始地址
    FRAL = FlashAddr.Byte[0];
    GIE = 0;					//若开启了全局中断，则禁止中断
    __asm
	{
        TBR                     //查表读，读取数据到ROMDH/ROMDL寄存器
		NOP
		NOP
		NOP
		NOP
    }
    FlashData.Byte[1] = ROMDH;
    FlashData.Byte[0] = ROMDL;
    GIE = 1;					//重新开启全局中断
}
//*****************************************************************************
//                                Flash擦除函数
//*****************************************************************************
void EraseFlash(void)
{
    FRAH = FlashAddr.Byte[1];
    FRAL = FlashAddr.Byte[0];
    
    __asm
	{
        BCC INTG,GIE       //若开启了全局中断，则禁止中断
        BSS ROMCL,FPEE     //选择Flash擦除
        BSS ROMCL,WREN     //使能Flash擦除
        MOVI 0x55
        MOVA ROMCH         //0x55写入虚拟存储器
        NOP                //8个NOP指令
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        MOVI 0xAA
        MOVA ROMCH         //0xAA写入虚拟存储器
        NOP                //8个NOP指令
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        BSS ROMCL,WR       //启动擦除
		NOP
		NOP			  
        JBC ROMCL,WR       //判断是否擦除结束标志
        GOTO $-1           //等待擦除结束
        BCC ROMCL,WREN     //禁止Flash擦除
        BSS INTG,GIE       //重新开启全局中断
    }
}
 
//*****************************************************************************
//                                Flash写函数
//*****************************************************************************    
void WriteFlash(void)
{
    FRAH=FlashAddr.Byte[1];     //设置写入的起始地址
    FRAL=FlashAddr.Byte[0];
    ROMDH=FlashData.Byte[1];    //设置写入的数据
    ROMDL=FlashData.Byte[0];
    __asm
	{
        BCC  INTG,GIE      //关闭全局中断
        BCC  ROMCL,FPEE    //选择写功能
        BSS  ROMCL,WREN    //使能写
        MOVI 0x55
        MOVA ROMCH         //0x55写入虚拟存储器
        NOP                //8个NOP指令
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        MOVI 0xAA
        MOVA ROMCH         //0xAA写入虚拟存储器
        NOP                //8个NOP指令
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
        BSS ROMCL,WR       //启动写  
		NOP
		NOP
        JBC ROMCL,WR       //判断是否写结束标志
        GOTO $-1           //等待写结束
        BCC ROMCL,WREN     //禁止Flash写
        BSS INTG,GIE       //重新开启全局中断
    }
}

