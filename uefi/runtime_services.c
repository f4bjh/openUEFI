#include "kernel/kernel.h"
#include "kernel/time.h"
#include "uefi/uefi.h"
#include "uefi/runtime_services.h"
	
EFI_STATUS
GetTime (
   OUT EFI_TIME                  *Time,
   OUT EFI_TIME_CAPABILITIES     *Capabilities OPTIONAL
  )
{
//TODO

// must validate entry pointers
//
 if (Time==NULL)
   return EFI_INVALID_PARAMETER;

// call kernel [fw_get_time](kernel_runtime_interface.md#2)
// manage error code status returned
// fill EFI_TIME.Time output data
// TBD : management of Capabilities


  return EFI_SUCCESS;
}
