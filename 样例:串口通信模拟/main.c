#include <8051.h>
#include "../include/delay.h"
#define pin_rxd P3_0
#define pin_txd P3_1
__bit rxd_or_txd = 0;
__bit rxd_end = 0;
__bit txd_end = 0;
unsigned char txd_buff = 0;
unsigned char rxd_buff = 0;
void start_rxd();
void start_txd(unsigned char dat);
void main (){
    EA = 1;
    mod2_time_0(600);
    while (1)
    {
        while (pin_rxd);
        start_rxd();
        while(!rxd_end);
        start_txd(rxd_buff);
        while(!txd_end);
    }
    
}
void interrupt_time_0 () __interrupt 1{
    static unsigned char count = 0;
    if(rxd_or_txd)
    {
        count++;
        if (count <= 8)
        {
            pin_txd = txd_buff & 0x01;
            txd_buff >>= 1;
        }else if (count == 9)
        {
            pin_txd = 1;
        }else{
            count = 0;
            TR0 = 0;
            txd_end = 1;
        }
    }
    else{
        if (count == 0 )
        {
            if (!pin_rxd)
            {
                rxd_buff = 0;
                count ++;
            }
            else{
                TR0 = 0;
            }
        }
        else if (count <= 8)
        {
            rxd_buff >>1;
            //rxd_buff = rxd_buff|(pin_rxd<<7);
            if (pin_rxd)
            {
                rxd_buff |= 0x80;
            }
            count++;
        }else{
            count = 0;
            TR0 =0;
            if (pin_rxd)
            {
                rxd_end = 1;
            }
            
        }
    }
}
void start_rxd(){
    TL0 = 256 - ((256 - TH0 )>>1);
    ET0 = 1;
    TR0 = 1;
    rxd_end = 0;
    rxd_or_txd = 0;

}
void start_txd(unsigned char dat){
    txd_buff = dat;
    TL0 = TH0 ;
    ET0 = 1;
    TR0 = 1;
    pin_txd = 0;
    txd_end = 0;
    rxd_or_txd = 1;
}
