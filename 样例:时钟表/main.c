#include <8051.h>
#include "../include/delay.h"
#include "../include/keysdriver.h"
#include "../include/nixietube.h"
unsigned char number_to_out[8]={0,0,0,0,0,0,0,0};
unsigned int ms = 0;
unsigned char sec = 0;
unsigned char min = 0;
unsigned char hour = 0;
void main (){
    
    EA = 1;
    //ET0 = 0;
    config_time_0(1);
    while (1)
    {
        if (ms>=1000)
        {
            ms = 0;
            sec++;
        }
        if (sec>=60)
        {
            sec = 0;
            min ++;
        }
        if (min >=60)
        {
            min = 0;
            hour ++;
        }
        keys_driver(number_to_out);
        // 改变数组中的值，显示相应的值       
        number_for_show(sec ,&number_to_out[0],2);
        number_for_show(hour,&number_to_out[4],2);
        number_for_show(min,&number_to_out[2],2);
    }
}
void interrupt_time_0() __interrupt 1{
    static unsigned char index = 0;
   
    // 关闭定时中断
    ET0 = 0 ;
    // 恢复定时
    TH0 = T0RH;
    TL0 = T0RL;
    // 中断次数改变
    ms++;
    
    // 扫描键盘
    keys_scan();
    //显示数码管
    tube(index);
    lighting(number_to_out[index]);
    index++;
    index &= 0x07;
    // 打开定时中断
    ET0 = 1 ;
}
void keys_action(unsigned char key_code,unsigned char num_to_out[]){
    switch (key_code)
    {
    case 107:
        sec++;
        break;
    case 109:
        sec --;
        break;
    case 106:
        min ++;
        break;
    case 111:
        min --;
        break;
    default:
        break;
    }
}