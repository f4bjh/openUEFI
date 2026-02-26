#ifndef RUNTIME_SERVICES_H
#define RUNTIME_SERVICES_H

typedef
EFI_STATUS
GetTime (
   OUT EFI_TIME                  *Time,
   OUT EFI_TIME_CAPABILITIES     *Capabilities OPTIONAL
  );

#endif
