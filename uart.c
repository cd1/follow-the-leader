#include "uart.h"
#include <avr/io.h>

const unsigned long CPU_FREQUENCY = 16e6;  // Hz
const unsigned long BAUD_RATE = 115200;    // bps

unsigned int compute_baud_prescale() {
    return (CPU_FREQUENCY / (BAUD_RATE * 16)) - 1;
}

int uart_putchar(char c, FILE *stream) {
    while ((UCSR0A & (1 << UDRE0)) == 0)
        ;
    UDR0 = c;

    return 0;
}

int uart_getchar(FILE *stream) { return -1; }

void uart_setup() {
    // enable Tx and Rx
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    // set character size to 8 bits
    UCSR0B &= ~(1 << UCSZ02);
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);

    // set baud rate
    unsigned int baud_ps = compute_baud_prescale();
    UBRR0H = (baud_ps >> 8);
    UBRR0L = baud_ps;
}

FILE uart = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);
