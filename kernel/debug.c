#include <stdarg.h> 
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
const char *fmt, ...)
{
   char buf[16];
   va_list args;
  

//TODO find a way to a smarter log implementation with format input data (%d, %s, and so on...)

    uart_puts("[openUEFI/mukernel][");
 
    uart_puts(level);
    uart_puts("] ");
 
    va_start(args, fmt);
    uart_puts(args);
    va_end(args);
    uart_puts(" ");
 



    uart_puts(file);
    uart_puts(":");

    itoa_dec(line, buf);
    uart_puts(buf);
    uart_puts(" in ");


    uart_puts(func);


#if 0
    TODO
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
#endif

    uart_puts("\n");
}
