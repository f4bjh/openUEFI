# Microkernel → UEFI Shim Interface

```
+----------------------------------------------------------+
|                        OS (Linux HPC)                    |
|----------------------------------------------------------|
|   Appelle EFI Runtime Service : GetValue()               |
+----------------------------▲-----------------------------+
                             |
                             | EFI_TIME
                             |
+----------------------------|-----------------------------+
|                    UEFI SHIM (Runtime layer)             |
|----------------------------------------------------------|
|  - Implémente EFI Runtime Services                       |
|  - Convertit rtc_time -> EFI_TIME                        |
|  - N'accède JAMAIS directement au hardware               |
|                                                          |
|  GetValue()                                              |
|     ↓                                                    |
|  mukernel_get_value(&value)      <--- pointeur vers API kernel |
+----------------------------▲-----------------------------+
                             |
                             | API interne stable
                             |
+----------------------------|----------------------------+
|                  Microkernel Firmware                   |
|---------------------------------------------------------|
|  - Gestion mémoire runtime                              |
|  - Protection des structures partagées                  |
|  - Logique minimale                                     |
|                                                         |
|  mukernel_get_value(struct type_of_value *value)              |
|     ↓                                                   |
|  hal_hw_get_value(value)                                |
+----------------------------▲-----------------------------+
                             |
                             | HAL abstraction
                             |
+----------------------------|-----------------------------+
|                      HAL (Lightweight)                   |
|----------------------------------------------------------|
|  Implémentation spécifique plateforme :                 |
|                                                          |
|  - QEMU x86_64 : CMOS I/O 0x70 / 0x71                   |
|  - Intel NUC : PCH RTC                                  |
|  - ARM board : MMIO RTC controller                      |
|                                                          |
|  hal_hw_get_value()                                     |
|     ↓                                                   |
|  Lecture registres matériels                            |
+----------------------------▲-----------------------------+
                             |
                             | Accès direct hardware
                             |
+----------------------------|-----------------------------+
|                         Hardware                         |
|----------------------------------------------------------|
|                     RTC / CMOS                           |
+----------------------------------------------------------+

```



## 1. Entry Contract

- Register state
- Stack guarantees
- Memory layout guarantees

## 2. Services Provided

ajouter une liste la plus exhaustive qui soit des services expose par mon BIOS

- Memory allocation
- Timer services
- Interrupt routing
- Console / debug output
- exemple : mettre un lien implementation/runtime_services/gettime.md

## 3. Error Handling Model

- Return conventions  
All functions implemented by HAL and the microkernel firmware must follow the rules of the standard `errno`

<https://github.com/torvalds/linux/blob/master/tools/arch/mips/include/uapi/asm/errno.h>
<https://github.com/torvalds/linux/blob/master/include/uapi/asm-generic/errno-base.h>

- Panic behavior
- Recovery model
