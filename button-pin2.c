#include "button-pin2.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "timer0.h"

const int BOUNCE_THRESHOLD = 150;  // ms

long hard_button_pin2_press;

void button_pin2_setup() {
    // set button as input
    DDRD &= ~(1 << DDD2);

    // allow interrupts
    EIMSK = (1 << INT0);

    // request falling edge changes
    EICRA &= ~(1 << ISC00);
    EICRA |= (1 << ISC01);

    button_pin2_press = 0;
    hard_button_pin2_press = 0;
}

ISR(INT0_vect) {
    unsigned long now = timer0_millis();

    if (now - hard_button_pin2_press >= BOUNCE_THRESHOLD) {
        button_pin2_press = now;
    }

    hard_button_pin2_press = now;
}
