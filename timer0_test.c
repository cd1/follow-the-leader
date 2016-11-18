#include "timer0.h"
#include <stdio.h>
#include "uart.h"

int main() {
    timer0_setup();

    while (1) {
        fprintf(&uart, "Elapsed time: %lu s\n", timer0_millis() / 1000);
        timer0_delay(1000);
    }

    return 0;
}
