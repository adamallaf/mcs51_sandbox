#include <mcs51reg.h>


volatile unsigned char ticks = 0;

/*
 * this delay is not working for values > 255,
 * the asm code below shows how sdcc compiler
 * is dealing with "while(ticks < ms)" when 
 * ticks is unsigned int:
;	timer0.c:8: while(ticks < ms);
00101$:
	clr	c
	mov	a,_ticks
	subb	a,r6
	mov	a,(_ticks + 1)
	subb	a,r7
	jc	00101$
;	timer0.c:9: }
	ret
*/
void delay_ms(unsigned int ms) {
    unsigned int t = ms;
    while (t > 750) {
        ticks = 0;
        while(ticks < 250);
        t = t - 250;
    }
    if (t > 500) {
        ticks = 0;
        while(ticks < 250);
        t = t - 250;
    }
    if (t > 250) {
        ticks = 0;
        while(ticks < 250);
        t = t - 250;
    }
    ticks = 0;
    while(ticks < t);
}

void Timer_init() {
    //PCON2 &= 0x00;
    TMOD = 0x01;    /* Timer0 mode1 16-bit */
    TH0 = 0xf4;     /* 1ms timer value for 12T @35MHz */
    TL0 = 0x9b;
    TR0 = 1;        /* Start timer0 */
}

void Timer0_ISR() __interrupt (1)   /* Timer0 interrupt service routine (ISR) */
{
    ticks++;
    TH0 = 0xf4;     /* 1ms timer value */
    TL0 = 0x9b;
}

void main(void) {
    EA  = 1;        /* Enable global interrupt */
    ET0 = 1;        /* Enable timer0 interrupt */
    Timer_init();
    while(1) {
        P3 ^= 0x40;
        delay_ms(19);
        P3 ^= 0x40;
        delay_ms(1);
    }
}
