# HAL RTC Interface Specification

## 1. Purpose

This document defines the Hardware Abstraction Layer (HAL) interface for the Real-Time Clock (RTC) in openUEFI.

The goal of this interface is to:

- Abstract chipset-specific RTC implementations
- Provide a stable contract to the microkernel
- Minimize attack surface
- Avoid policy logic in the HAL
- Ensure deterministic behavior
- This interface is strictly mechanism-only (no policy).

## 2. Design Principles

- No dynamic allocation
- No parsing
- No implicit hardware probing
- No global mutable state
- No blocking behavior
- Strict input validation
- Deterministic return codes
- No side effects outside RTC domain

The HAL must not expose raw hardware registers to upper layers.

## 3. Threat Model
The RTC HAL must be resilient against:

- Uninitialized RTC hardware
- Invalid CMOS data
- Battery failure
- Corrupted time registers
- Malicious or faulty chipset behavior
- Concurrent access from multiple firmware components

The HAL is not responsible for:
- Time policy (timezone, daylight saving)
- Secure time storage
- Monotonic counters (if separate hardware exists)

The HAL must handle:

- Hardware absent
- Battery failure
- Corrupted BCD
- Unsupported platform
- Read instability


## 4. Interface definition

### 4.1 Data Structures
```
typedef struct {
    uint16_t year;      // 0-99
    uint8_t  month;     // 1–12
    uint8_t  day;       // 1–31
    uint8_t  hour;      // 0–23
    uint8_t  minute;    // 0–59
    uint8_t  second;    // 0–59
} hal_rtc_time_t;
```
Constraints:

- All fields must be validated before returning to caller.
- BCD conversion (if needed) must occur inside HAL.
- No undefined or partially filled structures allowed.

### 4.2 Status Codes
```
typedef enum {
    HAL_RTC_OK = 0,
    HAL_RTC_ERR_NOT_INITIALIZED,
    HAL_RTC_ERR_INVALID_PARAMETER,
    HAL_RTC_ERR_INVALID_DATA,
    HAL_RTC_ERR_TIMEOUT,
    HAL_RTC_ERR_HW_FAILURE,
    HAL_RTC_ERR_UNSUPPORTED
} hal_rtc_status_t;
```
### 4.1  Initialization

```
hal_rtc_status_t hal_rtc_init(void);
```

- Must configure hardware safely. (set 24 hours mode)
- Must detect hardware presence.
- Must detect invalid battery state if possible.
- Must not assume previous firmware configured RTC correctly.


### 4.2  Get Time
```
hal_rtc_status_t hal_rtc_get_time(hal_rtc_time_t *time);
```
- validate entry pointer is not NULL. Else return HAL_RTC_ERR_INVALID_PARAMETER
- wait update-in-progress bit is reset for 500ms. Else return status HAL_RTC_ERR_TIMEOUT
- validate data ranges of rtc. Else return HAL_RTC_ERR_INVALID_DATA
- convert BCD to binary internally if necessary. Else return HAL_RTC_ERR_HW_FAILURE


### 4.3  Set Time TBD
```
hal_rtc_status_t hal_rtc_set_time(const hal_rtc_time_t *time);
```
- Must validate input ranges.
- Must not accept out-of-range values.
- Must ensure atomic write if hardware requires it.
- Must return error if RTC hardware is locked or unavailable.

## 5. Memory & Privilege Constraints

- No dynamic memory allocation
- No global writable state outside module
- No access to unrelated chipset registers
- No modification of firmware runtime structures
- Must operate entirely within HAL memory region

- HAL code region: RX
- HAL data region: RW

- RTC access must be protected by a spinlock or critical section.
- No busy-wait loops longer than hardware spec allows.
- Must prevent re-entrancy.

### 6. Hardware Backends
Each chipset must provide its own implementation:

- CMOS-based RTC (legacy x86)
- SoC integrated RTC
- Virtualized RTC (QEMU test backend)

Each backend must implement the same interface. No conditional logic in upper layers.




