#include <REGX51.H>
#include "onewire.h"

#define ds18b20_skip_rom    0xcc

void ds18b20_convert(void)
{

	onewire_init();
	
	onewire_sendbyte(0xcc); //看图
	
	onewire_sendbyte(0x44); //send 一个 convert 
	
}


float ds18b20_readt(void)
{
	int temp;  //int 有16个位
	float t;
	unsigned char tlsb,tmsb; //看图 第1个byte是lsb 第2个msb
	onewire_init();
	onewire_sendbyte(0xcc); //看图
	onewire_sendbyte(0xbe); //看图
	
	tlsb=onewire_receivebyte();
	tmsb=onewire_receivebyte();
	
	temp=(tmsb<<8)|tlsb;  //2个8位合在一起
	t=temp/16.0;  //移走了 除回去; 2的4次方 补码
	return t;
	
	
	
}