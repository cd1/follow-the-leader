#ifndef UART_H
#define UART_H

#include <stdio.h>

/**
 * Initialize the UART system.
 *
 * The UART system will be configured for a processor with frequency of 17 MHz
 * and baud rate of 9600. The variable "uart" should be used to read and write
 * to the UART system.
 */
void uart_setup();

/**
 * A stream compatible with printf/scanf used to read and write to the
 * UART system.
 *
 * The stream can be used directly with fprintf/fscanf, i.e.:
 *
 *  fprintf(&uart, "Hello world\n");
 *  fscanf(&uart, "%s", &name);
 *
 * Or by overwriting "stdout" and "stdin" so the functions printf/scanf can be
 * used, i.e.:
 *
 *  stdout = &uart;
 *  stdin = &uart;
 *  printf("Hello world\n");
 *  scanf("%s", &name);
 */
FILE uart;

#endif
