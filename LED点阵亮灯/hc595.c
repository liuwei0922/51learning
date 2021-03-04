#include <8051.h>

#define _nop_() __asm NOP __endasm
#define RCLK P3_5
#define SRCLK P3_6
#define SER P3_4

// 74HC595 的使用，让点阵亮一个点
void HC595(unsigned char _data_){
    // 定义for循环的变量
    unsigned char var;
    // 初始化，都是高电位
    RCLK = 1;
    SRCLK =1;
    
    // 传入数据
    for ( var = 0; var < 8; var++)
    {
        // 串口导入数据，并且每导入一位，扔掉高位，直到都8位导入
        SER = _data_ >> 7;
        _data_ <<= 1 ;
        // 串口数据导入内部存储
        SRCLK = 0;
        _nop_() ;
        _nop_() ;
        SRCLK = 1;
    
    }
    // 内部存储转移到并口
    RCLK =0;
    _nop_();
    _nop_();
    RCLK =1;
}