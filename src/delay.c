#include <8051.h>
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
