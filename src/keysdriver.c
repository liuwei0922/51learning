#include <8051.h>
#include "../include/nixietube.h"
// 按位操作
#define set_bit(var, n) (var |= (1<<n))
#define get_bit(var, n) (var & (1<<n))
// 键盘键码
unsigned char __code keys_code[4][4]={
    {97,98,99,107},{100,101,102,109},
    {103,104,105,106},{96,108,12,111}
};
unsigned char keys_sta[4][4]={
    {1,1,1,1},{1,1,1,1},
    {1,1,1,1},{1,1,1,1}
};
unsigned long result = 0;
unsigned long var = 0;
unsigned char flag = 0;
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
void keys_driver(unsigned char  number_to_out[]){
    unsigned char i,j;
    //static unsigned char k=0;
    static unsigned char keys_backup[4][4]={
        {1,1,1,1},{1,1,1,1},
        {1,1,1,1},{1,1,1,1}
    };
    for ( i = 0; i < 4; i++)
    {
        for ( j = 0; j < 4; j++)
        {
            if (keys_backup[i][j]!= keys_sta[i][j])
            {
                if (keys_backup[i][j] )
                {

                    keys_action(keys_code[i][j],number_to_out);
                }
                keys_backup[i][j]= keys_sta[i][j];
            }
            
        }
        
    }
    
}

void keys_scan(){
    // 扫描索引
    unsigned char key_in_index;
    static unsigned char key_out_index = 0 ;
    // 键盘缓冲区
    static unsigned char keys_buff[4][4]={
        {0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF}
    };
    // 保存P1的位状态
    __bit key_in_bit = 1;
    // 按键进入缓冲区
    for ( key_in_index = 0; key_in_index <4;key_in_index++)
    {
        key_in_bit = get_bit(P1,key_in_index);
        
        keys_buff[key_out_index][((~key_in_index)& 0x03)]=(keys_buff[key_out_index][((~key_in_index)& 0x03)]<<1)|key_in_bit;
    }
    // 判断按键状态
    for ( key_in_index = 0; key_in_index < 4; key_in_index++)
    {   
        if ( (keys_buff[key_out_index][key_in_index] & 0x0f) == 0x00)
        {
            keys_sta[key_out_index][key_in_index]= 0;
        }
        if ((keys_buff[key_out_index][key_in_index] & 0x0f) == 0x0f)
        {
            keys_sta[key_out_index][key_in_index]= 1;
        }
        
        
    }
    // 拉起下一列判断
    key_out_index++;
    key_out_index = (key_out_index & 0x03);
    //number_for_show(P1,number_to_out);
    switch (key_out_index){
        case 0: P1_4 = 1; P1_7 = 0; break;
        case 1: P1_7 = 1; P1_6 = 0; break;
        case 2: P1_6 = 1; P1_5 = 0; break;
        case 3: P1_5 = 1; P1_4 = 0; break;
        default: break;
    }
}
