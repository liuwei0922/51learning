#include <8051.h>
#include "../include/nixietube.h"
#include "../include/keysdriver.h"

//unsigned char buff[]={0};
unsigned char number_to_out[]={0,0,0,0,0,0,0,0};
void main (){
    //打开定时器中断
    EA = 1;
    ET0 = 1;
    //定时器设置
    TMOD = 1;
    TH0 = 0XFC;
    TL0 = 0X67;
    TR0 = 1;
    // 开始操作
    while (1)
    {
        keys_driver(number_to_out);
    }
    

}
void interrupt_time_0 () __interrupt 1 {
    // 定时器归位
    TH0 = 0XFC;
    TL0 = 0X67;
    
    // 数码管显示
    static unsigned char tube_index = 0;
    tube(tube_index);
    lighting(number_to_out[tube_index]);
    (tube_index>=6)?(tube_index = 0):(tube_index++);
    // 扫描键盘
    keys_scan();
}
