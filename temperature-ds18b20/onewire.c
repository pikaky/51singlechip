#include <REGX51.H>

sbit onewire_DQ=P3^7;


unsigned char  onewire_init(void)
{
  unsigned char ackbit;
	unsigned char i;
	onewire_DQ=1;  //看图 先拉低
	onewire_DQ=0;
	
	i = 247;while (--i);   //延时500us；
	
	onewire_DQ=1;
	
	i = 32;while (--i); //延时70us；
	ackbit=onewire_DQ;
	
	i = 247;while (--i);  //再延时500us；结束初始化
	return ackbit;
	
}

void onewire_sentbit(unsigned char BIT)
{
	unsigned char i; 
	onewire_DQ=0;  
	i = 4;while (--i);   //延时10us
	onewire_DQ=BIT;      //发送bit=1时，在10us时，dq变成1，30us时判断高，表示发送了1
	                     //发送bit=0时，在10us时，dq还是0，30us时判断低，表示发送了0
	i = 24;while (--i);  //延时50us
	onewire_DQ=1;   //释放总线
}
unsigned char onewire_receivebit(void)
{
	unsigned char i; 
	unsigned char BIT;  //看图 先拉低
	onewire_DQ=0;
	
	i = 2;while (--i);  //延时8us
	onewire_DQ=1; //释放总线
	i = 2;while (--i);  //延时8us 给机器反应时间
	BIT=onewire_DQ; //接受数据
	i = 24;while (--i); //延时48us
	
	return BIT;
}
void onewire_sendbyte(unsigned char byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		onewire_sentbit(byte&(0x01<<i)); //低位在前 从后往前读数
	}
}

unsigned char onewire_receivebyte(void)
{
	unsigned char i;
	unsigned char byte=0x00;
	for(i=0;i<8;i++)
	{
		if(onewire_receivebit()){byte|=(0x01<<i);} //byte原来是0x00，每遇到一次1，|0x01<<i 变成1，0还是0.一位一位置1
	
	}
	
	return byte;
}
