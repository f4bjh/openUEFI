#include "kernel/kernel.h"
#include "kernel/debug.h"
#include "drivers/uart.h"

static void itoa_dec(int value, char *buffer)
{
    char tmp[16];
    int i = 0;
    int j = 0;
    int is_negative = 0;

    if (value == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    if (value < 0)
    {
        is_negative = 1;
        value = -value;
    }

    while (value > 0)
    {
        tmp[i++] = '0' + (value % 10);
        value /= 10;
    }

    if (is_negative)
        tmp[i++] = '-';

    // reverse
    while (i > 0)
        buffer[j++] = tmp[--i];

    buffer[j] = '\0';
}

void mukernel_log_impl(
const char *level,
const char *file,
const char *func,
int line,
const char *trace)
{
   char buf[4];
  
    uart_puts("[openUEFI/mukernel][");
 
    if (level)
     uart_puts(level);
    uart_puts("] ");
 
    if (file)
      uart_puts(file);
    uart_puts(":");

    if (line<=9999) {    
      itoa_dec(line, buf);
      uart_puts(buf);
    }
    uart_puts(" in ");

    if (func)
      uart_puts(func);
    uart_puts(" ");

    uart_puts(trace);
}
