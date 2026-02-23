//#include "shim.h"
#include "drivers/uart.h"

// Minimal EFI_SYSTEM_TABLE placeholder
typedef struct {
    void *BootServices;
    void *RuntimeServices;
} EFI_SYSTEM_TABLE;

static EFI_SYSTEM_TABLE system_table;

void shim_init(void) {
    uart_puts("==== UEFI Shim Initialized ====\n");

    // Passe-plat fictif vers EFI
    system_table.BootServices = (void*)0xdeadbeef;
    system_table.RuntimeServices = (void*)0xcafebabe;
}
