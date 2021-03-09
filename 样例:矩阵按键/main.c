#include <8051.h>
#include "../include/nixietube.h"
#include "../include/keysdriver.h"

//unsigned char buff[]={0};
unsigned char number_to_out[]={0,0,0,0,0,0,0,0};
unsigned long result = 0;
unsigned long var = 0;
unsigned char flag = 0;
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
void keys_action(unsigned char key_code,unsigned char number_to_out[] ){
    // 数字
    if (key_code >= 96&&key_code <= 105)
    {
        if (flag == 108)
        {
            
        }
        
        var=(var*10)+key_code-96; 
        number_for_show(var,number_to_out);  
    }
    // 加
    if (key_code == 107)
    {
        if (flag == 0)
        {
            result += var;
            var = 0;
            number_for_show(result,number_to_out);
            flag = 0;
        }
        else{
            goto equal;
        }
        
    }
    // 减
    if (key_code == 109)
    { 
        // 连减
        if (flag == 109)
        {
            result -= var;
            var = 0;
            number_for_show(result,number_to_out);
        }
        else{
            result =var;
            var = 0;
            flag = 109;//减法标记
        }
     }
    //乘
    if (key_code == 106)
    {
        // 连乘
        if (flag ==106)
        {
            result *= var;
            var = 0;
            number_for_show(result,number_to_out);
        }
        else{
            result =var;
            var = 0;
            flag = 106;//乘法标记
        }
    }
    //除
    if (key_code == 111)
    {
        // 连除
        if (flag == 111)
        {
            result /= var;
            var = 0;
            number_for_show(result,number_to_out);
        }
        else{
            result =var;
            var = 0;
            flag = 111;//除法标记
        }
    }
    
    // 等于
    if (key_code == 108)
    {   
        equal:
        switch (flag)//上一次的按键
        {
        case 109:
            result = result -var;
            number_for_show(result,number_to_out);
            var = 0;
            break;
        case 106: 
            result = result *var;
            number_for_show(result,number_to_out);
            var = 0;
            break;
        case 111:
            result = result /var;
            number_for_show(result,number_to_out);
            var = 0;
            break;
        default:
            result += var;
            var = 0;
            number_for_show(result,number_to_out);
            break;
        }
        flag = 108;
    }  
}