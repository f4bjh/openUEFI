#include "kernel/kernel.h"
#include "drivers/uart.h"

void _start(void) {
    uart_puts("Hello from kernel task!\n");
    kernel_init();
}
