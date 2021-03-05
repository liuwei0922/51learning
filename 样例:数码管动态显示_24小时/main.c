#include <8051.h>
#include "../include/delay.h"
#include "../include/nixietube.h"
unsigned char __code LedBuff[] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
unsigned int msec =0;
unsigned char sec=0;
unsigned char min=4;
unsigned char hours=17;
unsigned char i =0;
void main(){
	EA=1;
	ET0=1;
	delay(1);
	while(1){
		//time translate
		if(msec>=1000){
			sec++;
			msec=0;
		}
		if(sec>=60){
			min++;
			sec=0;
		}
		if(min>=60){
			hours++;
			min=0;
		}
	}
}
void Interruputtime0() __interrupt  1 {
		TH0 = 0xFC;
		TL0 = 0x67;
		msec++;
		//lighting
		switch (i){
		case 1:
			tube(i); lighting(sec/10);i++;break;
		case 0:
			tube(i); lighting(sec%10);i++;break;
		case 3: 
			tube(i); lighting(min/10);i++;break;
		case 2:
			tube(i); lighting(min%10);i++;break;
		case 5:
			tube(i); lighting(hours/10);i=0;break;
		case 4:
			tube(i); lighting(hours%10);i++;break;

		}

}
