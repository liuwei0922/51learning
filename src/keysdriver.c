#include <8051.h>
#include "../include/keysaction.h"
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
unsigned int keys_down_time = 0;
unsigned int keys_time = 1000;
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
                if (keys_down_time >= keys_time)
                {
                    keys_action(keys_code[i][j],number_to_out);
                    keys_time+=200;
                }else{
                    keys_time = 1000;
                }
                
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
            keys_down_time+=4;
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
