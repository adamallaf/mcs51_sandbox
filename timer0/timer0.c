#include <reg51.h>

volatile unsigned int ticks = 0;

void delay_ms(unsigned int ms) {
    ticks = 0;
    while(ticks < ms);
}

void Timer_init() {
    //PCON2 &= 0x00;
    TMOD = 0x01;    /* Timer0 mode1 */
    TH0 = 0xfc;     /* 50ms timer value */
    TL0 = 0x18;
    TR0 = 1;        /* Start timer0 */
}

void Timer0_ISR() __interrupt (1)   /* Timer0 interrupt service routine (ISR) */
{
    ticks++;
    TH0 = 0xfc;     /* 50ms timer value */
    TL0 = 0x18;
}

void main(void) {
    EA  = 1;        /* Enable global interrupt */
    ET0 = 1;        /* Enable timer0 interrupt */
    Timer_init();
    while(1) {
        P3 ^= 0x40;
        delay_ms(1000);
    }
}
