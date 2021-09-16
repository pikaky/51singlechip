#include <REGX51.H>
#include "Delay.h"
#include "urat.h"
sbit led1=P2^1;
unsigned char receive_byte=0x00;
int a=10;

//char zhuan16_10 (int he)
//{
//int re=0;   // 保存转换为10进制的结果
//int k=16;   // 16进制
//int n=1;    // 位权
//re += (he%10)*n;  // 取出各位位码值，并乘以对应的位权值
//he /= 10;   // 去掉16进制数的最低位，次低位变为最低位
//n *= k;     // 位权乘以16
//return re;
//}


int pwm()
{
	// 占空比 
	led1=1;
  Delay(100-a);
	led1=0;
	Delay(a);
	led1=1;
	return 0;
}

void main ()
{
int b =0x32;
UartInit();
urat_send (0x66);
	
	while (1)
	{
		pwm();
		a=receive_byte;
		
	}

}

void urat_receive (void) interrupt 4	
{
	if(RI==1)  //收到中断信号 
	{
	receive_byte=SBUF;	
	RI=0;
	}
}