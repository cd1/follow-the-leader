#ifndef BUTTON_PIN2_H
#define BUTTON_PIN2_H

/**
 * The moment (as of "timer0_millis()") that the button on PIN 2 was pressed for
 * the last time. If the button hasn't been clicked yet, the value of
 * "button_pin2_press" will be 0.
 */
volatile unsigned long button_pin2_press;

/**
 * Initialize the button on PIN 2.
 *
 * The button will use the interruption INT0 and every time the user presses it,
 * the variable "button_pin2_press" will be updated to the current time (as of
 * "timer0_millis()"). The module handles debounce appropriately.
 *
 * The function "timer0_setup()" MUST be called in order for this module to
 * work correctly.
 */
void button_pin2_setup();

#endif
