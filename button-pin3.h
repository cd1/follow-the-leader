#ifndef BUTTON_PIN3_H
#define BUTTON_PIN3_H

/**
 * The moment (as of "timer0_millis()") that the button on PIN 3 was pressed for
 * the last time. If the button hasn't been clicked yet, the value of
 * "button_pin3_press" will be 0.
 */
volatile unsigned long button_pin3_press;

/**
 * Initialize the button on PIN 3.
 *
 * The button will use the interruption INT1 and every time the user presses it,
 * the variable "button_pin3_press" will be updated to the current time (as of
 * "timer0_millis()"). The module handles debounce appropriately.
 *
 * The function "timer0_setup()" MUST be called in order for this module to
 * work correctly.
 */
void button_pin3_setup();

#endif
