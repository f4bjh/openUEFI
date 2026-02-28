#ifndef IO_H
#define IO_H

#define REGISTER_INDEX_PORT 0x70
#define REGISTER_DATA_PORT  0x71

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t value);

#endif
