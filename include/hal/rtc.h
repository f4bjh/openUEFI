#ifndef RTC_STATUS_CODE_H
#define RTC_STATUS_CODE_H

typedef enum {
    HAL_RTC_OK = 0,
    HAL_RTC_ERR_NOT_INITIALIZED,
    HAL_RTC_ERR_INVALID_PARAMETER,
    HAL_RTC_ERR_INVALID_DATA,
    HAL_RTC_ERR_TIMEOUT,
    HAL_RTC_ERR_HW_FAILURE,
    HAL_RTC_ERR_UNSUPPORTED
} hal_rtc_status_t;

typedef struct {
   uint8_t sec;
   uint8_t min;
   uint8_t hour;
   uint8_t day;
   uint8_t mon;
   uint8_t year;
} hal_rtc_time_t;

hal_rtc_status_t hal_rtc_init(void);
hal_rtc_status_t hal_rtc_get_time(hal_rtc_time_t *time);

#endif
