#include "timer0.h"
#include <avr/interrupt.h>
#include <avr/io.h>

volatile unsigned long millis;

void timer0_setup() {
    // set mode to "interval"
    TCCR0A |= (1 << WGM01);
    // enable ISR(COMPA)
    TIMSK0 |= (1 << OCIE0A);
    // set initial value
    TCNT0 = 0;
    // set interval count
    OCR0A = 250;
    // set prescaler to /64
    TCCR0B |= (1 << CS01) | (1 << CS00);
    // Enable Global Interrupt
    sei();

    millis = 0;
}

unsigned long timer0_millis() { return millis; }

void timer0_delay(unsigned long ms) {
    unsigned long start_time = millis;
    while ((millis - start_time) < ms)
        ;
}

ISR(TIMER0_COMPA_vect) { millis++; }
