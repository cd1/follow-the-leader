#include <avr/interrupt.h>
#include <avr/io.h>

#include "button-pin3.h"
#include "timer0.h"

/**
 * The minimum threshold between two consecutives putton presses so they are
 * considered distinct. If two button presses happen in an interval less than
 * this value, the first one is ignored.
 */
const unsigned long BOUNCE_THRESHOLD_PIN3 = 200;  // ms

/**
 * The moment (as of "timer0_millis()") that the button on PIN 3 was pressed for
 * the last time. This includes the erroneous presses not debounced, so this
 * value should not be considered as the actual time the button was pressed. Use
 * "button_pin3_press" to get that value correctly.
 */
volatile unsigned long hard_button_pin3_press;

void button_pin3_setup() {
    // set button as input
    DDRD &= ~(1 << DDD3);

    // allow interrupts
    EIMSK = (1 << INT1);

    // request falling edge changes
    EICRA &= ~(1 << ISC10);
    EICRA |= (1 << ISC11);

    button_pin3_press = 0;
    hard_button_pin3_press = 0;
    timer0_setup();
    sei();
}

/**
 * The routine which handles the button press. The variable "button_pin3_press"
 * is set to the actual button press moment (as of "timer0_millis()");
 * debouncing is handled here.
 */
ISR(INT1_vect) {
    unsigned long now = timer0_millis();

    if ((now - hard_button_pin3_press) >= BOUNCE_THRESHOLD_PIN3) {
        button_pin3_press = now;
    }

    hard_button_pin3_press = now;
}
