#include "drivers/uart.h"
#include <stdint.h>

#define COM1 0x3F8

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void uart_init(void)
{
    outb(COM1 + 1, 0x00);    // Disable all interrupts
    outb(COM1 + 3, 0x80);    // Enable DLAB
    outb(COM1 + 0, 0x03);    // 38400 baud divisor low
    outb(COM1 + 1, 0x00);    // divisor high
    outb(COM1 + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(COM1 + 2, 0xC7);    // FIFO control
    outb(COM1 + 4, 0x0B);    // Modem control
}

void uart_puts(const char *s)
{
    while(*s)
    {
        outb(COM1, *s++);
    }
}

