#ifndef _Nixie_tube
#define _Nixie_tube
unsigned char code Led[]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,0x80,0x90};
sbit LED = P2^0;
sbit ADDR0 = P2^2;
sbit ADDR1 = P2^3;
sbit ADDR2 = P2^4;
void tube(unsigned char led){
	  P0=~0xFF;
	  switch (led){
			case 0: 
				ADDR0=0;	ADDR1=0;	ADDR2=0;	//P0=~Led[led];
				break;
			case 1: 
				ADDR0=1;	ADDR1=0;	ADDR2=0;	//P0=~Led[led];
				break;
			case 2: 
				ADDR0=0;	ADDR1=1;	ADDR2=0;	//P0=~Led[led];
				break;
			case 3: 
				ADDR0=1;	ADDR1=1;	ADDR2=0;	//P0=~Led[led];
				break;
			case 4: 
				ADDR0=0;	ADDR1=0;	ADDR2=1;	///P0=~Led[led];
				break;
			case 5: 
				ADDR0=1;	ADDR1=0;	ADDR2=1;	//P0=~Led[led];
				break;
			case 6: 
				ADDR0=0;	ADDR1=1;	ADDR2=1;	//P0=~Led[led];
				break;
			case 7: 
				ADDR0=1;	ADDR1=1;	ADDR2=1;	//P0=~Led[led];
				break;
			default: break;
		}
}
void lighting(unsigned char num){
	P0=~Led[num];
}