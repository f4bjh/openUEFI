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
  rtc_time_t time;
  errno_t errno;
  EFI_STATUS Status;

 if (Time==NULL)
   return EFI_INVALID_PARAMETER;

 errno=fw_get_time(&time);

 Status = convert_errno_to_efistatus(errno);

 Time->Year = time.year;
 Time->Month = time.month;
 Time->Day = time.date_of_the_month;
 Time->Hour = time.hour;
 Time->Minute = time.minute;
 Time->Second = time.second;

 //following variable will have to be mananged when not using mc146818
 Time->Pad1 = 0xFF;
 Time->Nanosecond = 0;
 Time->TimeZone = 0;
 Time->Daylight = 0;
 Time->Pad2=0;
	 
 // TBD and TODO : management of Capabilities


  return Status;
}
