#include <REGX51.H>


void UartInit(void)		//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	//AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T  51单片机没这个
	//AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD = 0x21;	
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1; ////禁止定时器0中断
	PT0=0; //用低优先级
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA=1;
	ES=1;
}

int urat_send (unsigned char sendbyte)
{
	
	SBUF=sendbyte;
	while(TI==0);  //判断是否发送完毕 如果TI一直是0 证明没有发送完 一直循环下去 直到变成1
	TI=0;
	
	return 0;
}

int urat_string (unsigned char* string)  //发送字符串
{
	while(*string)  //  判断字符串/0终止符
	{
	urat_send (*string++);
	}
	return 0;
}

