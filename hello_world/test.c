#include <8051.h>


char n = 0x40;

void delay(void);

void main(void) {
    while(1){
        P3 |= n;
        delay();
        delay();
        delay();
        delay();
        delay();
        delay();
        P3 &= ~n;
        delay();
        delay();
        delay();
        delay();
        delay();
        delay();
        delay();
        delay();
    }
}

void delay(void) {
    int i, j, k, l, m, n;
    for(i = 0; i < 0xff; i++)
        for(j = 0; j < 0xff; j++);
            for(k = 0; k < 0xff; k++);
                for(l = 0; l < 0xff; l++);
                    for(m = 0; m < 0xff; m++);
                        for(n = 0; n < 0xff; n++);
}
