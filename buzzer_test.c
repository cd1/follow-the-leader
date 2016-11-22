#include "buzzer.h"

int main() {
    buzzer_setup();

    while (1) {
        buzzer_tone(100, 1000);
        buzzer_tone(400, 1000);
    }

    return 0;
}
