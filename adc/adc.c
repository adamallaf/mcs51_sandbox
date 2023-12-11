#include <mcs51reg.h>


typedef unsigned char uint8_t;

__sfr __at (0x8E) AUXR;
__sfr __at (0xD6) T2H;
__sfr __at (0xD7) T2L;
__sfr __at (0xBC) ADC_CTRL;
__sfr __at (0xBD) ADC_RESH;
__sfr __at (0xBE) ADC_RESL;
__sfr __at (0x9D) P1ASF;

/* ADC CTRL consts & masks */
#define ADC_POWER      0x80
#define ADC_FLAG       0x10
#define ADC_START      0x08
#define ADC_SPEED_0    0
#define ADC_SPEED_1    0x20
#define ADC_SPEED_2    0x40
#define ADC_SPEED_3    0x60
#define ADC_CH0        0
#define ADC_CH1        1
#define ADC_CH2        2

volatile uint8_t txbusy;
volatile uint8_t rxbusy;
volatile uint8_t adcbusy;
volatile uint8_t adch;
volatile uint8_t adcl;
volatile uint8_t da_value;

void write_byte(uint8_t data);


void main() {
    SCON = 0x50;   /* None parity */
    txbusy = 0;
    adcbusy = 1;
    /* Timer2 registers */
    T2H = 0xff;    /* hex( int( 65536 - 16e6 / 4 / BAUDRATE ) ) */
    T2L = 0xdc;
    AUXR = 0x14;   /* Timer2 in 1T mode */
    AUXR |= 0x01;  /* Timer2 as UART1 baudrate generator*/
    ES = 1;        /* Enable UART1 interrupt */

    P1ASF = 0xff;
    ADC_RESH = 0;
    ADC_CTRL = ADC_POWER | ADC_START | ADC_SPEED_0 | ADC_CH0;

    IP |= 0x20;
    IE = 0xa0;     /* Enable ADC interrupt, start A/D conversion */
    EA = 1;        /* Enable global interrupt */

    __asm
        NOP
        NOP
        NOP
        NOP
    __endasm;
    for(;;) {
        while(adcbusy);
        P2 = ~adch; /* For debugging P2 */
        write_byte('A');
        write_byte('D');
        write_byte('C');
        write_byte('=');
        /* Decimal adjust adch
         * this converts adch value to BCD
         * and its resolution is 2 digits, so the range is 0-99
         * need to figure out how to make it 0-9999
         * and need to make it to work as atoi()
        */
        __asm
          MOV a, _adch
          DA a
          MOV _da_value, a
        __endasm;
        write_byte(48 + (da_value >> 4));
        write_byte(48 + (da_value & 0x0f));
        write_byte(adch);
        write_byte('\n');
        adcbusy = 1;
    }
}

/* ADC interrupt service routine (ISR) */
void Adc_ISR() __interrupt (5) {
    ADC_CTRL &= !ADC_FLAG;
    adch = ADC_RESH;
    adcl = ADC_RESL;
    adcbusy = 0;
    ADC_CTRL = ADC_POWER | ADC_START | ADC_SPEED_0 | ADC_CH0;
    ES = 1;  /* Enable UART Interrupt */
}

/* Uart1 interrupt service routine (ISR) */
void Uart1_ISR() __interrupt (4) {
    if ( RI ) {
        RI = 0;
        P0 = SBUF;
        rxbusy = 0;
    }
    if ( TI ) {
        TI = 0;
        txbusy = 0;
    }
}

void write_byte(uint8_t data) {
    while(txbusy);
    txbusy = 1;
    SBUF = data;
}
