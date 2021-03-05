#include <8051.h>
#include "../include/nixietube.h"
#include "../include/hc595.h"
#include "../include/delay.h"
#define K1 RXD
#define K2 TXD
#define ADD P3_2
#define SUBTRACT P3_3
#define LED P0
unsigned char number = 0;
__bit add_key = 1;
__bit sub_key = 1;
void delays (){
    unsigned int i = 1000;
    while (i--);
    
    
}


void main (){
    
    __bit add_keybackup = 1;
    __bit sub_keybackup = 1;
    // 启动定时器中断
    EA = 1;
    ET0 = 1;
    TMOD = 1;
    TH0 = 0xFC;	 
	TL0 = 0x67;
    TR0 = 1;
    
    // 按键赋初值
    K1 = 1;
    K2 = 1;
    ADD = 1;
    SUBTRACT = 1;
    // 关闭LED点阵
    HC595(0x00);
    
    while (1)
    {
        if (add_key != add_keybackup)
        {
            if (add_key == ADD)
            {
                if (add_keybackup == 0)
                {
                    number ++;
                }
                add_keybackup = add_key;
            }
            
            
            
        }
        if (sub_key != sub_keybackup)
        {
            if (sub_key == SUBTRACT)
            {
                if (sub_keybackup == 0)
                {
                    number --;
                }
                sub_keybackup = sub_key;
            }
            
            
            
        }
        

    }
}
void InterruputTime0() __interrupt  1 {
    // 按键状态
    static unsigned char add_keybuff = 1;
    static unsigned char sub_keybuff = 1;
    // 亮灯索引
    static unsigned char index = 0;
    // 保证定时器工作
    TH0 = 0xFC;	 
	TL0 = 0x67;
    // 数码管亮灯
    tube(index);
    switch (index)
    {
    case 0:
        lighting(number%10);break;
    case 1:
        lighting((number/10)%10);break;
    case 2:
        lighting((number/100)%10);break;
    default: break;
    }
    (index >=3) ? (index=0) : (index++);
    // 按键状态更新
    add_keybuff = (add_keybuff<<1)|ADD;
    switch (add_keybuff)
    {
    case 0xff:
        add_key = 1;break;
    case 0x00:
        add_key = 0;break;
    default: break;
    }
    sub_keybuff = (sub_keybuff<<1)|SUBTRACT;
    switch (sub_keybuff)
    {
    case 0xff:
        sub_key = 1;break;
    case 0x00:
        sub_key = 0;break;
    default: break;
    }
    
    

}