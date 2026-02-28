CROSS = $(TARGET)
CC = $(CROSS)gcc
LD = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy

CFLAGS = -ffreestanding -fno-builtin -nostdlib -O2 -Wall -Wextra -m32
LDFLAGS = -T link.ld -nostdlib -static

INCLUDE = -Iinclude 

SRC_KERNEL = kernel/start.c kernel/kernel.c kernel/time.c kernel/io/io.c
SRC_UEFI = uefi/shim.c uefi/runtime_services.c
SRC_DRIVERS = drivers/uart/uart.c drivers/rtc/mc146818/mc146818.c
SRC_LIB = lib/printf.c lib/string.c

SRC = $(SRC_KERNEL) $(SRC_UEFI) $(SRC_DRIVERS) $(SRC_LIB)

ELF_OUT = openuefi.elf
PAYLOAD = payload/openuefi.elf

all: $(PAYLOAD)

$(ELF_OUT):
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC) -o $(ELF_OUT) $(LDFLAGS)

# Transform ELF into Coreboot payload (just copy for Coreboot tools)
$(PAYLOAD): $(ELF_OUT)
	mkdir -p payload
	cp $(ELF_OUT) $(PAYLOAD)

clean:
	rm -f $(ELF_OUT) $(PAYLOAD)

run: all
	# Lancer QEMU avec Coreboot + payload
	qemu-system-x86_64 \
		-bios coreboot.rom \
		-device isa-debug-exit,iobase=0xf4,iosize=0x04 \
		-serial stdio \
		-display none

.PHONY: all clean run

