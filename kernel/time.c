#include "kernel/kernel.h"
#include "kernel/time.h"
#include "hal/rtc.h"


errno_t fw_get_time(rtc_time_t *t)
{

 hal_rtc_time_t time;
 hal_rtc_status_t hal_rtc_status;
 errno_t  errno=0;

 if (t==NULL)
  return EINVAL;

 hal_rtc_status = hal_rtc_get_time(&time);
  
 switch(hal_rtc_status) {
   case  HAL_RTC_OK:
     errno=0;
     break;
   default:
     errno=EPERM;
     break;
//TODO
#if 0
	   HAL_RTC_ERR_NOT_INITIALIZED,
    HAL_RTC_ERR_INVALID_PARAMETER,
    HAL_RTC_ERR_INVALID_DATA,
    HAL_RTC_ERR_TIMEOUT,
    HAL_RTC_ERR_HW_FAILURE,
    HAL_RTC_ERR_UNSUPPORTED
#endif
  }

//TO DO
 //t->sec=time->second et etc pour le reste
 return errno;
}

