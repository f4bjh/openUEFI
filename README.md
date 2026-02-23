# openUEFI
Modular microkernel-based UEFI firmware implementation.

# openUEFI

openUEFI est un microkernel firmware standalone, extensible et UEFI-compliant via un shim dédié.  
L’objectif est de séparer strictement le kernel pur du passe-plat UEFI, tout en restant testable et freestanding.

---

## 🏗 Architecture globale et Boot Flow

CPU Reset
   
   
Kernel Microkernel Standalone
   - Initialise le hardware (UART, PIT, etc.)
   - Initialise le scheduler coopératif
   - Initialise la registry statique
   - Autres services internes
   - Appelle UEFI Shim

UEFI Shim
   - Transforme le kernel registry en EFI protocols
   - Initialise EFI_SYSTEM_TABLE
   - Expose BootServices & RuntimeServices
   - Permet aux applications EFI de fonctionner


Applications EFI
   - Appellent uniquement les services exposés par le shim

---
**Principes clés :**  
- Le kernel est **indépendant de l’UEFI**  
- Le shim ne contient **aucune logique kernel**, seulement l’adaptation vers UEFI  
- Les applications EFI utilisent uniquement le shim  

---

## 🔹 Boot Flow

1. **CPU Reset** → exécution du microkernel standalone  
2. **Kernel init** : UART, scheduler, registry et services internes  
3. **Kernel appelle shim** → shim expose :  
   - `EFI_SYSTEM_TABLE`  
   - `EFI_BOOT_SERVICES`  
   - `EFI_RUNTIME_SERVICES`  
   - Mapping de la registry interne vers les protocoles EFI  
4. **Applications EFI** peuvent utiliser le kernel via le shim  

---

## 🔹 Règles de séparation

- **Kernel** : indépendant de UEFI, testable seul  
- **Shim** : adaptateur vers UEFI, dépend du kernel mais pas l’inverse  
- **Applications** : dépendent uniquement du shim  

---

## 🔹 Notes

- Cette architecture permet **d’avoir un kernel freestanding**, tout en étant UEFI-compliant  
- Le kernel peut évoluer (drivers, secure boot, SMM, etc.) sans toucher au shim  
- Shim peut évoluer indépendamment pour ajouter de nouvelles interfaces UEFI  

## 🔹 Execution

```
$ qemu-system-x86_64 \
    -machine q35 \
    -bios openuefi.bin \
    -serial stdio \
    -display none
```

## 🔹 pré-requis

```
sudo apt update
sudo apt install build-essential gcc-multilib g++-multilib
sudo apt install binutils
sudo apt install gcc-x86-64-linux-gnu
```

```
sudo apt install build-essential bison flex libgmp3-dev \
                 libmpc-dev libmpfr-dev texinfo libisl-dev
```
