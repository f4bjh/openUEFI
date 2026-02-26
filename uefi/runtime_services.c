#include "uefi.h"
#include "runtime_services.h"
	
EFI_STATUS
GetTime (
   OUT EFI_TIME                  *Time,
   OUT EFI_TIME_CAPABILITIES     *Capabilities OPTIONAL
  )
{


// must validate entry pointers
// call kernel [fw_get_time](kernel_runtime_interface.md#2)
// manage error code status returned
// fill EFI_TIME.Time output data
// TBD : management of Capabilities


  return EFI_SUCCESS;
}
