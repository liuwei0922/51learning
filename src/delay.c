#include <8051.h>
unsigned char T0RH = 0;
unsigned char T0RL = 0;
void delay(unsigned char times){
	//unsigned char mnt = 0;
	TMOD =0x01;
	TH0 = 0xFC;	 
	TL0 = 0x67;
	TR0 = 1; 
	/*
	while (mnt<=times){
		if(TF0==1){
			TF0=0;
			TH0 = 0xFC;
			TL0 = 0x67;
			mnt++;
		}
	}
	*/
}
void config_time_0(unsigned char ms){
	unsigned long tmp;
	tmp = 11059200 / 12; //计时器频率
	tmp = (tmp*ms)/1000; //计时器计数值
	tmp = 65536 - tmp; //计时器重载值
	T0RH = (char)(tmp>>8);//高位 
	T0RL = (char)(tmp);//低位
	TMOD &= 0XF0;//定时模式
	TMOD |= 0X01;
	TH0 = T0RH;
	TL0 = T0RL;
	ET0 = 1;
	TR0 = 1;
}
void config_time_1(unsigned char ms){
	unsigned long tmp;
	tmp = 11059200 / 12; //计时器频率
	tmp = (tmp*ms)/1000; //计时器计数值
	tmp = 65536 - tmp; //计时器重载值
	T0RH = (char)(tmp>>8);//高位 
	T0RL = (char)(tmp);//低位
	TMOD &= 0X0f;//定时模式
	TMOD |= 0X10;
	TH1 = T0RH;
	TL1 = T0RL;
	ET1 = 1;
	TR1 = 1;
}