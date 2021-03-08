#include <8051.h>
#include "../include/moto.h"
#define moto  P1
void delay(unsigned int i){
    while (i--);
    
}
void main (){
    moto = 0x0;
    while (1){
        moto = 0Xf;
        delay(2000);
    }
    
}