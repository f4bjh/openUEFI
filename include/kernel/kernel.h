#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include <stddef.h>
#include "kernel/errno.h"

#define BIT7 0x80
#define BIT6 0x40
#define BIT5 0x20
#define BIT4 0x10
#define BIT3 0x08
#define BIT2 0x04
#define BIT1 0x02
#define BIT0 0x01

typedef enum {
 MUKERNEL_NOT_INITIALISED,
 MUKERNEL_INITIALISED,
 MUKERNEL_INTERFACE_REGISTERED,
 MUKERNEL_STARTED,
 MUKERNEL_STOPPED
} mukernel_state_t;

typedef enum {
    MUKERNEL_OK = 0,
    MUKERNEL_ERR_INVALID_STATE,
    MUKERNEL_ERR_ALREADY_REGISTERED,
    MUKERNEL_ERR_NOT_INITIALISED,
    MUKERNEL_ERR_INTERNAL
} mukernel_err_status_t;

typedef uint8_t errno_t;
typedef  errno_t (f_init_t)(void); //faut il envisager de passer un contexte aux fonctions d'init
				//exemple : au shim, les fonctions d'appel d'interface a get_time etc etc
				//et a terme idem au bootloader sentinel (typiquement, system_table ?

typedef struct {
  mukernel_state_t state;
  f_init_t *f_init;
} mukernel_t;

void _start(void); 
mukernel_err_status_t mukernel_init(void);
mukernel_err_status_t mukernel_start(void);
errno_t mukernel_register_interface(f_init_t*);

#endif
