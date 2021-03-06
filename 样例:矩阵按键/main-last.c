#include <8051.h>
#include "../include/nixietube.h"
#include "../include/hc595.h"
#define KEY P1
#define KEY_IN_1  P1_3;
#define KEY_IN_2  P1_3;
#define KEY_IN_3  P1_1;
#define KEY_IN_4  P1_0;
#define KEY_OUT_1  P1_7;
#define KEY_OUT_2  P1_6;
#define KEY_OUT_3  P1_5;
#define KEY_OUT_4  P1_4;
// 键盘键码
unsigned char __code keys_code[4][4]={ //矩阵按键编号到标准键盘键码的映射表
    { 0x31, 0x32, 0x33, 0x26 }, //数字键 1、数字键 2、数字键 3、向上键
    { 0x34, 0x35, 0x36, 0x25 }, //数字键 4、数字键 5、数字键 6、向左键
    { 0x37, 0x38, 0x39, 0x28 }, //数字键 7、数字键 8、数字键 9、向下键
    { 0x30, 0x1B, 0x0D, 0x27 } //数字键 0、ESC 键、 回车键、 向右键
};
// 键盘状态
unsigned char  keys_sta[4][4]=
                            {{1,1,1,1},
                            {1,1,1,1},
                            {1,1,1,1},
                            {1,1,1,1}};
// 显示数字
unsigned long number_to_out = 0;
// 操作数字
unsigned long number = 0 ;
// 函数声明
void tube_light (unsigned long number);
void keys_driver();
void keys_action(unsigned char key_code);
void keys_scan();


void main(){
    
    // 打开定时器中断
    EA= 1;
    ET0 = 1;
    // 定时器0设置
    TMOD = 1;
    TH0 = 0xFC;	 
	TL0 = 0x67;
    TR0 = 1;
    // 关闭LED点阵
    HC595(0);

    while (1){
        keys_driver();
    }
    

}
void interrupt_time_0 () __interrupt 1 {
    // 定时器恢复定时
    TH0 = 0xFC;	 
	TL0 = 0x67;
    // 显示数码管
    // 亮管索引
    static unsigned char index = 0;
    // 亮管
    tube(index);
    (index >= 5) ? (index = 0):(index++);
    keys_scan();   
}
// 数码管亮管实现
void tube_light (unsigned long number){
    unsigned char num_arr[8];
    unsigned char array_index,i;
    // 用一个数组存放每一位数字
    for(array_index = 0 ;array_index <8;array_index ++){
        num_arr[array_index]=number%10;
        number = number / 10;
    }
    // 亮数字
    for ( i = 0; i < 8; i++)
    {   
        lighting(num_arr[i]);
    }
    
    
}
void keys_driver(){
    // 按键状态备份
    static unsigned char keys_backup[4][4]={{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
    // 按键坐标
    unsigned char i,j;
    // 循环检测键盘状态
    for ( i = 0; i < 4; i++)
    {
        for ( j = 0; j < 4; j++)
        {   

            if (keys_sta[i][j]!=keys_backup[i][j])
            {
                if (keys_backup[i][j] != 0)
                {
                    keys_action(keys_code[i][j]);
                }
                keys_backup[i][j] = keys_sta[i][j];
                
            }
            
        }
        
    }
    

}
void keys_action(unsigned char key_code){
    //unsigned long number_backup = 0;
    static unsigned long result = 0; //用于保存运算结果
    static unsigned long addend = 0; //用于保存输入的加数
   
    if ((key_code>=0x30) && (key_code<=0x39)){ //输入 0-9 的数字
        //整体十进制左移，新数字进入个位
        addend = (addend*10)+(key_code-0x30);
        number_to_out = addend;
        tube_light(addend); //运算结果显示到数码管
        //向上键用作加号，执行加法或连加运算
    }else if (key_code == 0x26){
        result += addend;  //进行加法运算
        addend = 0;
        number_to_out = result;
        tube_light(result);  //运算结果显示到数码管
        //回车键，执行加法运算(实际效果与加号相同)
    }else if (key_code == 0x0D){
        result += addend;  //进行加法运算
        addend = 0;
        number_to_out = result;
        tube_light(result); //运算结果显示到数码管
    }else if (key_code == 0x1B){ //Esc 键，清零结果
        addend = 0;
        result = 0;
        number_to_out = addend;
        tube_light(addend); //清零后的加数显示到数码管
    } 
}
void keys_scan (){
    unsigned char i;
    //矩阵按键扫描输出索引
    static unsigned char keyout = 0;
   
    static unsigned char keybuf[4][4] = { //矩阵按键扫描缓冲区
        {0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF}
    };
    //将一行的 4 个按键值移入缓冲区
    keybuf[keyout][0] = (keybuf[keyout][0] << 1) | KEY_IN_1;
    keybuf[keyout][1] = (keybuf[keyout][1] << 1) | KEY_IN_2;
    keybuf[keyout][2] = (keybuf[keyout][2] << 1) | KEY_IN_3;
    keybuf[keyout][3] = (keybuf[keyout][3] << 1) | KEY_IN_4;
    //消抖后更新按键状态
    //每行 4 个按键，所以循环 4 次
    for (i=0; i<4; i++){
        //连续 4 次扫描值为 0，即 4*4ms 内都是按下状态时，可认为按键已稳定的按下
        if ((keybuf[keyout][i] & 0x0F) == 0x00){
            keys_sta[keyout][i] = 0;
        //连续 4 次扫描值为 1，即 4*4ms 内都是弹起状态时，可认为按键已稳定的弹起
        }else if ((keybuf[keyout][i] & 0x0F) == 0x0F){
            keys_sta[keyout][i] = 1;
        }
    }
    //执行下一次的扫描输出
    keyout++; //输出索引递增
    keyout = keyout & 0x03; //索引值加到 4 即归零
    //根据索引，释放当前输出引脚，拉低下次的输出引脚
    switch (keyout){
        case 0: P1_4 = 1; P1_7 = 0; break;
        case 1: P1_7 = 1; P1_6 = 0; break;
        case 2: P1_6 = 1; P1_5 = 0; break;
        case 3: P1_5 = 1; P1_4 = 0; break;
        default: break;
    }
}