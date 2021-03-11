#include <8051.h>
#define _nop_() __asm NOP __endasm
void config_communication(unsigned int baud );
void main(){
    EA = 1;
    config_communication(600);
    while(1);
}
void interrupt_urt () __interrupt 4{
    if(RI){
        RI = 0;
        SBUF = SBUF+1;
    }
    if(TI){
        TI = 0;
    }
    
}
void config_communication(unsigned int baud){
    SCON = 0X50;
    TMOD &= 0X0F;
    TMOD |= 0X20;
    TH1 = 256 - (12010000/12/32/baud);
    TL1 = TH1;
    //PCON = 0X80;
    ET1 = 0;
    TR1 = 1;
    ES = 1;
}