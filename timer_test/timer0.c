#include <mcs51reg.h>

__sfr __at (0x8E) AUXR;

volatile unsigned int ticks = 0;

// void T0Delay(void);

void tm0(void) __interrupt (1)
{
    ticks += 1;
}


void main(void) {
    // AUXR &= 0x7f;
    AUXR |= 0x80;
    TMOD = 0x01;
    TL0 = 0x39;
    TH0 = 0x2c;
    TR0 = 1;
    ET0 = 1;
    EA = 1;
    while(1) {
        P3 ^= 0x40;
        ticks = 0;
        while(ticks < 209);
    }
}


// void T0Delay(void) {
//     TMOD = 0x01;
//     TL0 = 0x34;
//     TH0 = 0x49;
//     TR0 = 1;
//     while(TF0 == 0);
//     TR0 = 0;
//     TF0 = 0;
// }
