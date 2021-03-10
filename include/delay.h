#ifndef _DELAY_ 
#define	_DELAY_ 
extern unsigned char T0RH ;
extern unsigned char T0RL ;
extern void delay(unsigned char times);
extern void config_time_0(unsigned char ms);
extern void config_time_1(unsigned char ms);
extern void mod2_time_0(unsigned int baud);
#endif 

