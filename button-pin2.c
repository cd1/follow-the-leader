#include <avr/interrupt.h>
#include <avr/io.h>

#include "button-pin2.h"
#include "timer0.h"

/**
 * The minimum threshold between two consecutives putton presses so they are
 * considered distinct. If two button presses happen in an interval less than
 * this value, the first one is ignored.
 */
const unsigned long BOUNCE_THRESHOLD_PIN2 = 200;  // ms

/**
 * The moment (as of "timer0_millis()") that the button on PIN 2 was pressed for
 * the last time. This includes the erroneous presses not debounced, so this
 * value should not be considered as the actual time the button was pressed. Use
 * "button_pin2_press" to get that value correctly.
 */
volatile unsigned long hard_button_pin2_press;

void button_pin2_setup() {
    // set button as input
    DDRD &= ~(1 << DDD2);

    // allow interrupts
    EIMSK |= (1 << INT0);

    // request falling edge changes
    EICRA &= ~(1 << ISC00);
    EICRA |= (1 << ISC01);

    button_pin2_press = 0;
    hard_button_pin2_press = 0;
    timer0_setup();
    sei();
}

/**
 * The routine which handles the button press. The variable "button_pin2_press"
 * is set to the actual button press moment (as of "timer0_millis()");
 * debouncing is handled here.
 */
ISR(INT0_vect) {
    unsigned long now = timer0_millis();

    if ((now - hard_button_pin2_press) >= BOUNCE_THRESHOLD_PIN2) {
        button_pin2_press = now;
    }

    hard_button_pin2_press = now;
}
