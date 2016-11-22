#include "timer0.h"
#include <stdio.h>
#include "uart.h"
#include <avr/interrupt.h>

int main() {
    uart_setup();
    timer0_setup();

    sei();  // Enable Global Interrupt

    while (1) {
        fprintf(&uart, "Elapsed time: %lu s\n", timer0_millis() / 1000);
        timer0_delay(1000);
    }

    return 0;
}
