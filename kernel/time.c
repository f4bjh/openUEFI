#include "kernel/kernel.h"
#include "kernel/time.h"
#include "hal/rtc.h"

errno_t mukernel_get_time(rtc_time_t *t)
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
   case HAL_RTC_ERR_NOT_INITIALIZED:
     errno=ENXIO;
     break;
   case HAL_RTC_ERR_INVALID_PARAMETER:
     errno=EINVAL;
     break;
   case HAL_RTC_ERR_INVALID_DATA:
     errno=EIO;
     break;
   case HAL_RTC_ERR_TIMEOUT:
     errno=ETIMEDOUT;
     break;
   case HAL_RTC_ERR_HW_FAILURE:
     errno=EIO;
     break;
   case HAL_RTC_ERR_UNSUPPORTED:
     errno=EPERM;
     break;
   default:
     errno=EPERM;
     break;
  }

 if (errno) {
   //set time to default value
   time.sec=0;
   time.min=0;
   time.hour=0;
   time.day=1;
   time.mon=1;
   time.year=1970;
 }
 
 t->second=time.sec;
 t->minute=time.min;
 t->hour=time.hour;
 t->date_of_the_month=time.day;
 t->month=time.mon;
 t->year=time.year;

 return errno;
}

