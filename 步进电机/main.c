#include <REGX51.H>
#include <urat.h>

//8步控制 1001,1100,0110,0011,0011,0110,1100,1001
//换成二进制

unsigned char st[]={0x09,0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09,0x08,};

int count,n,c=0;
unsigned char receive_byte = 1;
unsigned char a=10;

void delay(unsigned int n)
{
	unsigned int i=0,j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<120;j++);
	}

}	
	
void time_init()
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	
	TMOD = 0x21;	
	
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	
	//TMOD = 0x01;		//设置定时器模式
	TH0=(65536-50000)/256; //50ms
	TH0=(65536-50000)%256;
	TR0=1;
	ET0 = 1;		//定时器0开始计时
	
	EA=1;
	ES=1;
	
}

	

void start()
{
	int i=0;
	for(i=0;i<7;i++)
	{
		P2=st[i];
		delay(100);
	}

	for(i=7;i>0;i--) //反转
	{
		P2=st[i];
		delay(100);
	}
	
}



int main()
{
	time_init();
	while(1)
	{
		a=receive_byte*10;
		
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

void time_str() interrupt 1
{
	TH0=0x3c; //50ms
	TH0=0xb0;
	count++;
	if(count==a) //20*50ms
	{
		if(n<10)
		{
			P2=st[n];
		}
		if(c>9)
		{
		P2=st[19-c];
		}
		if(c==18)
		{
		n=0;
		c=0;
		}
		n++;
		c++;
		count=0;
	}
	
}