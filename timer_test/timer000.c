#include <reg51.h>


void T0Delay(void);


void main(void) {
    while(1) {
        P3 ^= 0x40;
        T0Delay();
        T0Delay();
        T0Delay();
        T0Delay();
        T0Delay();
        T0Delay();
        T0Delay();
        T0Delay();
        T0Delay();
        T0Delay();
        T0Delay();
        T0Delay();
        T0Delay();
        T0Delay();
        T0Delay();
        T0Delay();
        T0Delay();
        T0Delay();
        T0Delay();
        T0Delay();
    }
}


void T0Delay(void) {
    TMOD = 0x01;
    TL0 = 0x34;
    TH0 = 0x49;
    TR0 = 1;
    while(TF0 == 0);
    TR0 = 0;
    TF0 = 0;
}
