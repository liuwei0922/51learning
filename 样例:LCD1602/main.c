#include <8051.h>
#include "../include/lcd.h"
void main(){
    unsigned char str[]="i,get,u";
    config_lcd();
    lcd_for_show(2,0,str);
    while(1);
}

