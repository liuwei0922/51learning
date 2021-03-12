#include <8051.h>
#include "../include/nixietube.h"
unsigned char numbers[] ={1,0,0,0,0,0,0,0};
unsigned char dat = 0;
unsigned long tmp = 0;
void config_uart (unsigned int baud);
void config_time_0(unsigned char ms);
void main (){
     //打开总中断
    EA = 1;
    config_uart(1200);
    config_time_0(2);
    while(1){
        //if(dat == 18){dat = 233;}
        number_for_show(dat,&numbers[0],8);
    }
}
// 串口中断
void interruput_uart () __interrupt 4{
    if(RI){
        RI = 0;
        dat = SBUF;
        SBUF = dat;
    }
    if(TI){
        TI = 0;
    }
}
// 定时器0 中断
void interrupt_time_0 () __interrupt 1 {
    // 数码管索引
    static unsigned char index = 0;
    // 重置定时器定时
    TH0 =(char) (tmp >>8);
    TL0 = (char) tmp;
    // 点亮数码管
    tube(index);
    lighting(numbers[index]);
    index++;
    index &= 0x07;
}
// 配置定时器0
void config_time_0(unsigned char ms){
    // 计算定时值
    tmp = 12010000 / 12;
    tmp = (tmp * ms ) / 1000;
    tmp = 65536 -tmp;
    TH0 =(char) (tmp >>8);
    TL0 = (char) tmp;
    // 定时器0 模式设置
    TMOD &= 0XF0;
    TMOD |= 0X01;
    // 使能定时器0 
    TR0 = 1;
    // 打开定时器0 中断
    ET0 = 1;
}
// 配置串口通信
void config_uart (unsigned int baud){
    // 设置串口通信
    SCON = 0X50;
    // 定时器1 的模式设定
    TMOD &= 0X0F;
    TMOD |= 0X20;
    // 定时器1 的时间设定
    TH1 = 256 - (12010000/12/32/baud);
    TL1 = TH1;
    // 打开串口中断
    ES = 1;
    // 使能定时器
    TR1 = 1;
    // 关闭定时器中断
    ET1 = 0;
}