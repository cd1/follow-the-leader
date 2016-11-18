#include "buzzer.h"
#include <avr/io.h>
#include "timer0.h"

void buzzer_setup() { DDRB |= (1 << DDB0); }

void buzzer_tone(unsigned int frequency, unsigned long duration) {
    unsigned long delay_ms = 1000 / frequency;

    unsigned long start_time = timer0_millis();
    while ((timer0_millis() - start_time) < duration) {
        PORTB |= (1 << DDB0);
        timer0_delay(delay_ms);
        PORTB &= ~(1 << DDB0);
        timer0_delay(delay_ms);
    }
}
