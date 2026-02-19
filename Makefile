# ==================================================
# Makefile Phase 0 - openUEFI freestanding ELF -> Coreboot payload
# ==================================================

CROSS = i386-elf-
CC = $(CROSS)gcc
LD = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy

CFLAGS = -ffreestanding -fno-builtin -nostdlib -O2 -Wall -Wextra -m32
LDFLAGS = -T link.ld -nostdlib -static

INCLUDE = -Iinclude -Idrivers/uart -Iuefi -Ikernel

SRC_KERNEL = kernel/start.c kernel/kernel.c
SRC_UEFI = uefi/shim.c
SRC_DRIVERS = drivers/uart/uart.c
SRC_LIB = lib/printf.c lib/string.c

SRC = $(SRC_KERNEL) $(SRC_UEFI) $(SRC_DRIVERS) $(SRC_LIB)

ELF_OUT = openuefi.elf
PAYLOAD = payload/openuefi.elf

# ==================================================
# Targets
# ==================================================

all: $(PAYLOAD)

# Compile freestanding ELF
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

