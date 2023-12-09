/*
 * UART1 example with STC15W404AS
*/
#include <mcs51reg.h>

#define BAUDRATE    115200

__sfr __at (0x8E) AUXR;
__sfr __at (0xD6) T2H;
__sfr __at (0xD7) T2L;

volatile unsigned char busy;

void send_byte(unsigned char);
void send_string(char *);

void Uart1_ISR() __interrupt (4)   /* Uart1 interrupt service routine (ISR) */
{
    ES = 0;
    if ( RI ) {
        RI = 0;
        P0 = SBUF;
        // RB8
    }
    if ( TI ) {
        TI = 0;
        busy = 0;
    }
    ES = 1;
}

void main() {
    SCON = 0x50;   /* None parity */
    busy = 0;
    /* Timer2 registers */
    T2H = 0xff;
    T2L = 0xe7;
    AUXR = 0x14;   /* Timer2 in 1T mode */
    AUXR |= 0x01;  /* Timer2 as UART1 baudrate generator*/
    ES = 1;        /* Enable UART1 interrupt */
    EA = 1;        /* Enable global interrupt */
    for(;;) {
        send_string("Hello world!\n");
        while(69);
    }
}

void send_byte(unsigned char data) {
    while(busy);
    ACC = data;
    busy = 1;
    SBUF = ACC;
}

void send_string(char *str) {
    while(*str)
        send_byte(*str++);
}
