#ifndef UEFI_H
#define UEFI_H

#include "uefi/Base.h"
#include "uefi/UefiBaseType.h"

//
//From edk2/MdePkg/Include/Uefi/UefiSpec.h
//

///
/// This provides the capabilities of the
/// real time clock device as exposed through the EFI interfaces.
///
typedef struct {
  ///
  /// Provides the reporting resolution of the real-time clock device in
  /// counts per second. For a normal PC-AT CMOS RTC device, this
  /// value would be 1 Hz, or 1, to indicate that the device only reports
  /// the time to the resolution of 1 second.
  ///
  UINT32     Resolution;
  ///
  /// Provides the timekeeping accuracy of the real-time clock in an
  /// error rate of 1E-6 parts per million. For a clock with an accuracy
  /// of 50 parts per million, the value in this field would be
  /// 50,000,000.
  ///
  UINT32     Accuracy;
  ///
  /// A TRUE indicates that a time set operation clears the device's
  /// time below the Resolution reporting level. A FALSE
  /// indicates that the state below the Resolution level of the
  /// device is not cleared when the time is set. Normal PC-AT CMOS
  /// RTC devices set this value to FALSE.
  ///
  BOOLEAN    SetsToZero;
} EFI_TIME_CAPABILITIES;

EFI_STATUS
convert_errno_to_efistatus(int err);

#endif
