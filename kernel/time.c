#include "time.h"


errno_t fw_get_time(struct t_rtc_time *t)
{

 hal_rtc_time_t time;
 hal_rtc_status_t hal_rtc_status;
 errno_t  errno=0;

 hal_rtc_status = hal_rtc_get_time(&time);
  
 switch(status) {
	 case  HAL_RTC_OK:
           errno=0;
	   break;
	       HAL_RTC_ERR_NOT_INITIALIZED,
    HAL_RTC_ERR_INVALID_PARAMETER,
    HAL_RTC_ERR_INVALID_DATA,
    HAL_RTC_ERR_TIMEOUT,
    HAL_RTC_ERR_HW_FAILURE,
    HAL_RTC_ERR_UNSUPPORTED


 return errno;
}

