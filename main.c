#include <reg52.h>
#include <delay.h>
#include <nixietube.h>
unsigned char code LedBuff[] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
unsigned int msec =0;
unsigned int sec=0;
unsigned char i =0;
void main(){
	EA=1;
	ET0=1;
	delay(1);
	while(1){
		// ±º‰≈–∂œ
		if(msec>=1000){
			sec++;
			msec=0;
		}
	}
}
void Interruputtime0() interrupt  1 {
		TH0 = 0xFC;
		TL0 = 0x67;
		msec++;
		//¡¡µ∆
		if(sec<10){
			tube(0);
			lighting(sec);
		}
		else if(sec>=10&&sec<100){
			if(i==1){
				tube(i);
				lighting(sec/10);
				i=0	;
			}
			else{
				tube(i);
				lighting(sec%10);
				i=1;
			}
		}
}
