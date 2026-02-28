#include "kernel/errno.h"
#include "drivers/uart.h"
#include "uefi/UefiBaseType.h"

// Minimal EFI_SYSTEM_TABLE placeholder
typedef struct {
    void *BootServices;
    void *RuntimeServices;
} EFI_SYSTEM_TABLE;

static EFI_SYSTEM_TABLE system_table;

EFI_STATUS
convert_errno_to_efistatus(int err)
{
    switch (err) {

        case 0:
            return EFI_SUCCESS;

        /* Paramètre invalide */
        case EINVAL:
            return EFI_INVALID_PARAMETER;

        /* Mémoire */
        case ENOMEM:
            return EFI_OUT_OF_RESOURCES;

        /* Fichier / objet */
        case ENOENT:
            return EFI_NOT_FOUND;

        case EEXIST:
            return EFI_ALREADY_STARTED;

        /* Permissions */
        case EPERM:
        case EACCES:
            return EFI_ACCESS_DENIED;

        /* I/O */
        case EIO:
            return EFI_DEVICE_ERROR;

        /* Non supporté */
        case ENOTSUP:
        case EOPNOTSUPP:
            return EFI_UNSUPPORTED;

        /* Timeout */
        case ETIMEDOUT:
            return EFI_TIMEOUT;

        /* Busy */
        case EBUSY:
            return EFI_NOT_READY;

        /* Taille buffer */
        case ENOBUFS:
        case EMSGSIZE:
            return EFI_BUFFER_TOO_SMALL;

        /* Par défaut : erreur générique */
        default:
            return EFI_DEVICE_ERROR;
    }
}

void shim_init(void) {
    uart_puts("==== UEFI Shim Initialized ====\n");

    // Passe-plat fictif vers EFI
    system_table.BootServices = (void*)0xdeadbeef;
    system_table.RuntimeServices = (void*)0xcafebabe;
}
