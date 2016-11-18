#include "button-pin3.h"
#include <avr/io.h>

long actual_button_pin3_press;
long hard_button_pin3_press;

void button_pin3_setup() {
    // set button as input
    DDRD &= ~(1 << DDD2);

    // allow interrupts
    EIMSK = (1 << INT0);

    // request falling edge changes
    EICRA &= ~(1 << ISC00);
    EICRA |= (1 << ISC01);

    hard_button_pin3_press = 0;
    actual_button_pin3_press = 0;
}
