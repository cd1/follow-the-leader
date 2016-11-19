#include "uart.h"
#include <avr/io.h>

/**
 * The system CPU frequency, in Hertz.
 */
const unsigned long CPU_FREQUENCY = 16e6;  // 16 MHz
/**
 * The baud rate used by the UART system, in bps.
 */
const unsigned long BAUD_RATE = 9600;  // bps

/**
 * Compute the baud prescale rate based on the system CPU frequency and the
 * desired baud rate.
 *
 * @return The baud prescale rate.
 */
unsigned int compute_baud_prescale() {
    return (CPU_FREQUENCY / (BAUD_RATE * 16)) - 1;
}

/**
 * Write one single byte to the UART system. This function is similar to the
 * stdio "fputc", but it uses the UART system instead of the provided stream.
 *
 * @param c The character to be written.
 * @param stream The stream to be written to. This parameter is not used.
 * @return Always 0 to indicate success.
 */
int uart_putc(char c, FILE *stream) {
    while ((UCSR0A & (1 << UDRE0)) == 0)
        ;
    UDR0 = c;

    return 0;
}

/**
 * Read one single byte from the UART system. This function is similar to the
 * stdio "fgetc", but it uses the UART system instead of the provided stream.
 *
 * @param stream The stream to read the byte from. This parameter is not used.
 * @return The character read from the UART system.
 */
int uart_getc(FILE *stream) {
    while ((UCSR0A & (1 << RXC0)) == 0)
        ;

    return UDR0;
}

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

FILE uart = FDEV_SETUP_STREAM(uart_putc, uart_getc, _FDEV_SETUP_RW);
