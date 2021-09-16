#include <REGX51.H>
#include "Delay.h"
#include "urat.h"
sbit led1=P2^1;
unsigned char receive_byte=0x00;
int a=10;

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
