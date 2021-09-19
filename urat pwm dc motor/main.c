#include <REGX51.H>
#include "Delay.h"
#include "urat.h"
sbit led1=P2^1; //in1
unsigned char receive_byte=0x32;
int a=50;
sbit IN0=P2^0;
sbit E=P2^2;
int i=0;

void main ()
{
E=1;
IN0=0;
UartInit();
urat_send (a);
	
TH0=(64535)/256;  //溢出后会清0 在这里重新赋值 才能循环
TL0=(64535)%256;

	while (1)
	{		
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

void pwm () interrupt 1
{
  TH0=(64535-(400*a))/256;  //溢出后会清0 在这里重新赋值 才能循环
  TL0=(64535-(400*a))%256;	
  led1=~led1;
}
		
		
