#include "start.h"
#include "kernel/kernel.h"
#include "uefi/shim.h"

void _start(void) {
mukernel_err_status_t mukernel_status;
    
    mukernel_status = mukernel_init();
    if (mukernel_status)
	return ;

    mukernel_status = shim_register();
    if (mukernel_status)
	return ;


    mukernel_status = mukernel_start();
    if (mukernel_status)
	return ;
}

