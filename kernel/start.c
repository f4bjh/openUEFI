#include "start.h"
#include "kernel/kernel.h"
#include "uefi/shim.h"

void _start(void) {

    mukernel_init();
    
    shim_register();

    mukernel_start();
}
