#include <8051.h>
#define ADD0  P2_2
#define ADD1  P2_3
#define ADD2  P2_4

void tube (unsigned char led) {
	 P0 =  ~ 0xFF;
	 switch (led){
		case 0:
		 	ADD0 = 0;
			ADD1 = 0;
			ADD2 = 0;
			break;
		case 1: 
			ADD0 = 1;
			ADD1 = 0;
			ADD2 = 0;
			break;
		case 2: 
			ADD0=0;	
			ADD1=1;	
			ADD2=0;
			break;
		case 3: 
			ADD0=1;
			ADD1=1;
			ADD2=0;	
			break;
		case 4: 
			ADD0=0;
			ADD1=0;	
			ADD2=1;
			break;
		case 5: 
			ADD0=1;
			ADD1=0;
			ADD2=1;
			break;
		case 6: 			
			ADD0=0;	
			ADD1=1;	
			ADD2=1;
			break;
		case 7:
			ADD0=1;	
			ADD1=1;
			ADD2=1;
			break;
		default: break;
		}
}
void lighting(unsigned char num){
  	unsigned char __code  Led[]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,0x80,0x90};
	P0 = ~ Led[num];
}

