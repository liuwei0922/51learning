#include <8051.h>
#include "hc595.h"
#define LED P0_0

void main(){
    LED = 0;
    HC595(0b10000000);
}