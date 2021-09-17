#include <REGX51.H>
#include "LCD1602.h"
#include "onewire.h"
#include "ds18b20.h"
#include "Delay.h"

float a;
unsigned char i, j;
void main()
{
LCD_Init();
ds18b20_convert();	
	i = 180;
	j = 73;
	do
	{
		while (--j);
	} while (--i);		
while(1)
{

ds18b20_convert();	
a=ds18b20_readt();	
	
LCD_ShowNum(2,2,a,2);

}
}