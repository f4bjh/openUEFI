#include <stdint.h>
#include <stdbool.h>
#include "kernel/kernel.h"
#include "kernel/io/io.h"
#include "hal/rtc.h"
#include "drivers/mc146818.h"

static uint8_t 
mc146818_read(uint8_t reg) 
{
    outb(REGISTER_INDEX_PORT, reg);
    return inb(REGISTER_DATA_PORT);
}

#if 0
static void 
mc146818_write(uint8_t reg, uint8_t val) 
{
    outb(REGISTER_INDEX_PORT, reg);
    outb(REGISTER_DATA_PORT, val);
}
#endif

static void 
mc146818_get_time(
hal_rtc_time_t  *rtc_time
)
{

    rtc_time->sec  = mc146818_read(MC146818_REGISTER_SECOND);
    rtc_time->min  = mc146818_read(MC146818_REGISTER_MINUTES);
    rtc_time->hour = mc146818_read(MC146818_REGISTER_HOURS);
    rtc_time->day  = mc146818_read(MC146818_REGISTER_DATE_OF_MONTH);
    rtc_time->mon  = mc146818_read(MC146818_REGISTER_MONTH);
    rtc_time->year = mc146818_read(MC146818_REGSITER_YEAR);

}

static bool
mc146818_get_uip_bit(
void)
{
 uint8_t reg_A = mc146818_read(MC146818_REGISTER_A); 

 if (reg_A & MC146818_REGISTER_A_UIP)
	return true; 
 else
	 return false;
}

static uint8_t 
bcd_to_bin(uint8_t val) {
    return (val & 0x0F) + ((val >> 4) * 10);
}

hal_rtc_status_t hal_rtc_init(void)
{

	//TO DO
  return HAL_RTC_OK;
}

hal_rtc_status_t hal_rtc_get_time(
hal_rtc_time_t *time
)
{
 uint16_t  timeout = MC146818_TIMEOUT_MS;
 hal_rtc_time_t  rtc_time;

 
 if (time==NULL)
   return HAL_RTC_ERR_INVALID_PARAMETER;

 while (timeout && mc146818_get_uip_bit())
	 timeout--;

 if (!timeout)
	return HAL_RTC_ERR_TIMEOUT;


 mc146818_get_time(&rtc_time);

 //convert BCD to binary internally if necessary.
 if ( mc146818_read(MC146818_REGISTER_B) & BIT2) {
  rtc_time.sec = bcd_to_bin(rtc_time.sec);
  rtc_time.min = bcd_to_bin(rtc_time.min);
  rtc_time.hour = bcd_to_bin(rtc_time.hour);
  rtc_time.day = bcd_to_bin(rtc_time.day);
  rtc_time.mon = bcd_to_bin(rtc_time.mon);
  rtc_time.year = bcd_to_bin(rtc_time.year);
 }
 
 //validate data ranges of rtc. 
 if (rtc_time.sec<0 || rtc_time.sec > 0x3B)
   return HAL_RTC_ERR_INVALID_DATA;
 if (rtc_time.min<0 || rtc_time.min > 0x3B)
   return HAL_RTC_ERR_INVALID_DATA;
 if (!(mc146818_read(MC146818_REGISTER_B) & BIT1)){ // mode 12H
    if (rtc_time.hour>=0x81 && rtc_time.hour <= 0x8B)
      rtc_time.hour -= 0x74;
    else if (rtc_time.hour == 0x8C)
      rtc_time.hour = 0;
    else if (rtc_time.hour<0x01 && rtc_time.hour > 0x0C)
      return HAL_RTC_ERR_INVALID_DATA;
 } else {
   if (rtc_time.hour<0x00 || rtc_time.hour > 0x17)
      return HAL_RTC_ERR_INVALID_DATA;
 }
 if (rtc_time.day<0x01 || rtc_time.day > 0x1F)
   return HAL_RTC_ERR_INVALID_DATA;
 if (rtc_time.mon<0x01 || rtc_time.mon > 0x0C)
   return HAL_RTC_ERR_INVALID_DATA;
 if (rtc_time.year<0x00 || rtc_time.year > 0x63)
   return HAL_RTC_ERR_INVALID_DATA;
 
 return HAL_RTC_OK;
}
