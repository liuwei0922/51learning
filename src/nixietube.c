#include <8051.h>
#define ADD0  P2_2
#define ADD1  P2_3
#define ADD2  P2_4

void tube (unsigned char led) {
	P0 =  ~ 0xFF;
	P2 &= 0xf1|(led<<1);
}
void lighting(unsigned char num){
	P0 =  ~ 0xFF;
  	unsigned char __code  Led[]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,0x80,0x90,0xff};
	P0 = ~ Led[num];
}
void number_for_show(unsigned long number,unsigned char number_to_out[],unsigned char length){
    signed char i;
    unsigned char num_buff[6];
    for ( i = 0; i < length ; i++)
    {
        num_buff[i] = number%10;
        number /= 10;
    }
    for ( i = length -1; i>=1; i--)
    {
        if (num_buff[i] == 0)
        {
            number_to_out[i]=10;
        }
        else{
            break;
        }
        
    }
    for ( ; i >= 0; i--)
    {
        number_to_out[i]= num_buff[i];
    }
}