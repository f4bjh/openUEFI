# Bootloader Sentinel Interface Specification

## 1. Purpose
Load an external bootloader (GRUB, EFI stub,...). If several bootloader are available, user will have to choose which one.
Bootloader sentinel is loaded by the microkernel firmware. It is using API provided by the microkernel firmware. But these API are read only feature on hardware devices.
Bootloader may use UEFI shim interface it exposes, as it has to load an external bootloader, to remain UEFI compliant.

## 2. Functions

### 2.1 bl_sentinel()
#### 2.1.1 Signature
```
typedef
TBD
bl_sentinel (
   TBD
  );
```

#### 2.1.2 Description
- Start the bootloader sentinel
- get bootables peripherals from microkernel firmware : enumerate_devices()
- for each bootables peripherals, read partition to llok for bootable file (GRUB or EFI stub) : read_partition(device_id, offset, size)
- check hash/signature : compute_hash(data) -> hash SHA256 (optionnel)
- load binary in memory, read only from microkernel point of view
- get EFI_SYSTEM_TABLE from UEFI shim :  TBD
- load EFI_SYSTEM_TABLE to binary
- get device path of device to boot : get_device_path(device_id) -> chemin / partition / type
- jump into binary entry point, with device path and needed boot parameters 


TO DO : 
Gestion des erreurs

Si aucun binaire valide n’est trouvé → échec propre et contrôlé.
Affichage d’un message minimal (si console disponible).
Aucune tentative d’écriture pour corriger / modifier les périphériques.
Aucun fallback automatique vers un mécanisme non validé.
