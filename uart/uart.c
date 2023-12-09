/*
 * UART1 example with STC15W404AS
*/
#include <mcs51reg.h>
#include <stdlib.h>

#define BAUDRATE    115200

typedef unsigned char uint8_t;

__sfr __at (0x8E) AUXR;
__sfr __at (0xD6) T2H;
__sfr __at (0xD7) T2L;

volatile uint8_t txbusy;
volatile uint8_t rxbusy;

void write_byte(uint8_t);
void write_string(char *);
uint8_t read_byte();
uint8_t *read_bytes(uint8_t);

void Uart1_ISR() __interrupt (4)   /* Uart1 interrupt service routine (ISR) */
{
    ES = 0;
    if ( RI ) {
        RI = 0;
        P0 = SBUF;
        rxbusy = 0;
    }
    if ( TI ) {
        TI = 0;
        txbusy = 0;
    }
    ES = 1;
}

void main() {
    SCON = 0x50;   /* None parity */
    txbusy = 0;
    /* Timer2 registers */
    T2H = 0xff;    /* hex( int( 65536 - 16e6 / 4 / BAUDRATE ) ) */
    T2L = 0xdc;
    AUXR = 0x14;   /* Timer2 in 1T mode */
    AUXR |= 0x01;  /* Timer2 as UART1 baudrate generator*/
    ES = 1;        /* Enable UART1 interrupt */
    EA = 1;        /* Enable global interrupt */
    for(;;) {
//        write_byte(read_byte());
        uint8_t *p = read_bytes(5);
        write_string(p);
        free(p);
//        write_string("Hello world!\n");
//        while(69);
    }
}

void write_byte(uint8_t data) {
    while(txbusy);
    ACC = data;
    txbusy = 1;
    SBUF = ACC;
}

void write_string(char *str) {
    while ( *str )
        write_byte(*str++);
}

uint8_t read_byte() {
    rxbusy = 1;
    while(rxbusy);
    uint8_t data = SBUF;
    return data;
}

uint8_t *read_bytes(uint8_t n) {
    uint8_t *data = (uint8_t *) malloc(n + 1);
    uint8_t *d = data;
    uint8_t i;
    for ( i = 0; i < n; i++ )
        *d++ = read_byte();
    *d = 0;
    return data;
}
