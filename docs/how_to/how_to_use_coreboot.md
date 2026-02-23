# Tutorial for using openUEFI with coreboot

Note that, soon or later, coreboot is not mandatory. And goal is even to delete this dependency.
At this time, coreboot is used to be able to generate a relevant BIOS binary firmware, that is loadable and executable by qemu.
Even if, I don't know really why for now it is so loadable...


## Build prerequisites

Build openUEFI firmware

```
$ cd openUEFI
$ make
```

You'll get `openuefi.elf` firmware binary file in the `payload` directory.

## Install and use coreboot


```
$ sudo apt-get install -y bison build-essential curl flex git gnat libncurses-dev libssl-dev zlib1g-dev pkgconf
```

```
$ git clone https://review.coreboot.org/coreboot
$ cd coreboot
```

```
make crossgcc-i386 CPUS=$(nproc) 
```

Copy the openUEFI firmware binary into the root directory of coreboot

```
$ cd ../openUEFI
$ cp payload/openuefi.elf ../coreboot
$ cd ../coreboot
```

```
$ make menuconfig

select 'Mainboard' menu
Beside 'Mainboard vendor' should be '(Emulation)'
Beside 'Mainboard model' should be 'QEMU x86 i440fx/piix4'
select < Exit >
```
```
select 'Payload' menu
select 'Payload to add (SeaBIOS) --->'
choose 'An ELF executable payload'
select 'Payload path and filename'
enter 'openuefi.elf'
select < Exit >
select < Exit >
select < Yes >
```

```
make savedefconfig
cat defconfig
```

build coreboot
```
make
```
## Run in qemu

```
$ qemu-system-x86_64 \
		-bios coreboot.rom \
		-serial stdio 
```


Note : to install qemu : `$ sudo apt-get install -y qemu-system`
