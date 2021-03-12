#include <8051.h>
#define LCD_DB P0
#define LCD_RS P2_6
#define LCD_RW P2_5
#define LCD_E P2_7
// 初始化液晶
void init_lcd(){
    unsigned char sta;
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_DB = 0xff;
    do{
        LCD_E = 1;
        sta = LCD_DB;
        LCD_E = 0;
    }while(sta & 0x80);
}
// 输入命令
void lcd_cmd(unsigned char cmd){
    init_lcd();
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_DB = cmd;
    LCD_E = 1;
    LCD_E = 0;
}
// 输入数据
void lcd_dat(unsigned char dat){
    init_lcd();
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_DB = dat;
    LCD_E = 1;
    LCD_E = 0;
}
// 光标位置
void lcd_cur(unsigned char x,unsigned char y){
    unsigned char addr;
    if(y == 0){
        addr = 0x00+x;
    }
    else{
        addr = 0x40+x;
    }
    lcd_cmd(addr|0x80);
}
// 显示数据
void lcd_for_show(unsigned char x,unsigned char y, unsigned char * ptrlcd){
    lcd_cur(x,y);
    while(*ptrlcd != 0){
        lcd_dat(*ptrlcd);
        ptrlcd ++;
    }
}
void config_lcd(){
    // 显示模式
    lcd_cmd(0x38);
    // 设置光标关闭，显示器开
    lcd_cmd(0x0c);
    // 地址+1，字符不动
    lcd_cmd(0x06);
    // 清屏
    lcd_cmd(0x01);
}