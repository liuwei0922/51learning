#include <8051.h>
#include "../include/lcd.h"
unsigned long tmp = 0;
unsigned char dat[16];
__bit flag = 0;
unsigned char str[]="I,get you !";
// 设置字符串缓冲区
unsigned char strbuff[32+sizeof(str)];
void array_convert(unsigned char str[]);
void config_time_0(unsigned char ms);
void config_uart(unsigned int baud);

void main(){
    // 缓冲索引
    unsigned char index = 0;
    // 配置液晶屏
    config_lcd();
    // 打开总中断
    EA = 1;
    // 配置串口通信
    config_uart(1200);
    // 配置定时器0
    config_time_0(15);
    // 调整数组
    //array_convert(str);
    while(1){
        array_convert(dat);
        if(flag){
            flag = 0;
            lcd_for_show(0,0,strbuff+index,16);
            index++;
            if(index >16+(sizeof(str)-1)){
                index = 0;
            }
        }
        //lcd_for_show(0,0,str,sizeof(str)-1);
    }
}
// 串口通信中断
void interruput_uart () __interrupt 4{
    static unsigned char i = 0;
    if(RI){
        RI = 0;
        dat[i] = SBUF;
        SBUF = dat[i];
        i++;
    }
    if(TI){
        TI = 0;
    }
}
// 定时器0 中断
void interrupt_time_0() __interrupt 1{
    static unsigned char time = 0;
    // 重置定时器值
    TH0 = (char)(tmp >>8);
    TL0 = (char)tmp;
    // 更新液晶
    time++;
    if(time>= 50){
        time = 0;
        flag = 1;
    }
}
void config_time_0(unsigned char ms){
    // 计算定时时间
    tmp = 12010000/12;
    tmp = (tmp * ms)/1000;
    tmp = 65536 - tmp;
    // 设置定时器值
    TH0 = (char)(tmp >> 8);
    TL0 = (char)tmp;
    // 设置定时器模式
    TMOD &= 0XF0;
    TMOD |= 0X01;
    // 打开定时器
    TR0 = 1;
    // 打开定时器中断
    ET0 = 1;
}
void config_uart(unsigned int baud){
    // 串口设置
    SCON = 0X50;
    // 设置定时器模式
    TMOD &= 0X0F;
    TMOD |= 0X20;
    // 定时时间计算
    TH1 = 256-(12010000/12/32/baud);
    TL1 = TH1;
    // 打开串口中断
    ES = 1;
    // 打开定时器1
    TR1 = 1;
    // 关闭定时器中断
    ET1 = 0;
}
void array_convert(unsigned char str[]){
    unsigned char i;
    for(i = 0;i<16;i++){
        strbuff[i]=' ';
    }
    for(i = 0;i<(sizeof(str)-1);i++){
        strbuff[i+16]=str[i];
    }
    for (i= 16+(sizeof(str)-1); i <sizeof(strbuff); i++)
    {
        strbuff[i]=' ';
    }
}