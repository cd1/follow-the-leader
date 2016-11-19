#include "uart.h"

int main() {
    uart_setup();

    int number;
    fprintf(&uart, "Type a number:\n");
    fscanf(&uart, "%d", &number);
    fprintf(&uart, "You typed the number %d.\n", number);

    return 0;
}
