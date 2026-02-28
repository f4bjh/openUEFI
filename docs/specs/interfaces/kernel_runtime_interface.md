# Kernel Runtime Interface Specification

## 1. Purpose
Expose minimal runtime services to the UEFI shim.

## 2. Function: mukernel_get_time

### Signature (conceptuelle)
errno_t mukernel_get_time(struct rtc_time *t)

### Direction
Caller : Shim 

### Description
Retrieve current RTC time from hardware abstraction layer.

### Input
- Pointer to struct rtc_time allocated by caller.
```
typedef struct {
uint8_t second;
uint8_t minute;
uint8_t hour;
uint8_t date_of_the_month;
uint8_t month;
uint8_t year;
} rtc_time;
```
 
### Output
- Structure filled with current time.

### Memory ownership
- Caller allocates.
- Kernel does not retain pointer.

### Thread safety
- Must be reentrant.
- No global state modification.

### Error handling
- Return 0 on success
- Non-zero error code on failure
tableau
    HAL_RTC_ERR_NOT_INITIALIZED
    HAL_RTC_ERR_INVALID_PARAMETER,
    HAL_RTC_ERR_INVALID_DATA,
    HAL_RTC_ERR_TIMEOUT,
    HAL_RTC_ERR_HW_FAILURE,
    HAL_RTC_ERR_UNSUPPORTED
  
### Security constraints
- Pointer must be validated.
- No direct hardware exposure.
