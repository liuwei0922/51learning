#ifndef _Nixie_tube
#define _Nixie_tube
#define ADDR0 = P2_2
#define ADDR1 = P2_3
#define ADDR2 = P2_4


extern void tube(unsigned char led);
extern void lighting(unsigned char times);
void number_for_show(unsigned long number,unsigned char number_to_out[]);
#endif
