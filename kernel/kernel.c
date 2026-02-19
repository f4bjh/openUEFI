#include "kernel/kernel.h"
#include "uefi/shim.h"
#include "drivers/uart.h"

void kernel_init(void)
{
    uart_puts("Kernel initialized!\n");

    // Appel du shim minimal
    shim_init();
}

