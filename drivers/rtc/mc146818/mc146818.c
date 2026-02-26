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

 //TODO
 //validate data ranges of rtc. Else return HAL_RTC_ERR_INVALID_DATA
 //convert BCD to binary internally if necessary. Else return HAL_RTC_ERR_HW_FAILURE

 return HAL_RTC_OK;
}
