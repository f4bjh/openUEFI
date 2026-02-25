# Shim Runtime Interface Specification

## 1. Purpose
Expose runtime services to the OS shim.

## 2. Functions

### 2.1 GetTime()
#### 2.1.1 Signature
```
typedef
EFI_STATUS
GetTime (
   OUT EFI_TIME                  *Time,
   OUT EFI_TIME_CAPABILITIES     *Capabilities OPTIONAL
  );
```

#### 2.1.2 Description
Retrieve current RTC time from hardware abstraction layer.
- must validate entry pointers
- call kernel [fw_get_time](kernel_runtime_interface.md#2)
- manage error code status returned
- fill EFI_TIME.Time output data
- TBD : management of Capabilities

### 2.2 SetTime()

