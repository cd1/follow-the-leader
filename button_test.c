#include <stdio.h>
#include "button-pin2.h"
#include "uart.h"

int main() {
    button_pin2_setup();

    unsigned long last_press = 0;

    while (1) {
        if (button_pin2_press > last_press) {
            fprintf(&uart, "Button pressed!\n");
            last_press = button_pin2_press;
        }
    }

    return 0;
}
