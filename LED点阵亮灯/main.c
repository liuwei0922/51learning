#include <8051.h>
#include "hc595.h"
#define LED P0
#define switchs P1_0
unsigned char __code LEDBUFF[]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0x00,0x00,
0xFF,0x00,0xE7,0xE7,0xE7,0xE7,0xE7,0x00,0xFF,0x3C,0x3C,0x3C,0x3C,0x3C,0x00,0x00,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};


void main(){
    // 打开总中断
    EA = 1;
    // 定时中断
    ET0 = 1;
    // 定时模式
    TMOD = 0X01;
    // 定时大小为1ms
    TH0 = 0xFC;
	TL0 = 0x67;
    // 打开定时器
    TR0 = 1;
    // P1低电位
    switchs = 0;
    // 全灭
    LED = 0X00;
    //unsigned char i =0;
    while (1);
    
    //HC595(0b10000000);
}
void InterruputTime0() __interrupt 1 {
    static unsigned char  times = 0 ;
    static unsigned char hcvar = 0b00000001;
    // 图片索引
    static unsigned char index = 0;
    // 时间索引，250ms刷新一次图片，index+1
    static unsigned char secs = 0;

    TH0 = 0xFC;
	TL0 = 0x67;
    // 不要闪烁
    LED = 0Xff;
    // 竖坐标亮
    HC595(hcvar); 
    hcvar <<= 1; 
    // 横坐标亮
    LED = LEDBUFF[(index+times)];
    times ++ ;
    if(times >=8){
        times = 0; 
        hcvar = 1;
    }
    secs ++;

    if (secs>=250)
    {
        secs = 0;
        index++;
        if (index >=32)
        {
            index = 0;
        }
        
    }
    
           
}