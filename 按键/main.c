#include <8051.h>
#define K1 RXD
#define K2 TXD
#define K3 P3_2
#define K4 P3_3
#define LED P2_0
void main (){
    // 按键赋初值
    K1 = 1;
    K2 = 1;
    K3 = 1;
    K4 = 1;

    LED = 1;
    while (1)
    {
        if(K4==0){
            LED = 0;
        }
        if (K4 == 1)
        {
            LED = 1;
        }
        
    }
    
}