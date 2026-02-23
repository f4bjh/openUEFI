# Tutorial for installing and using gcc for i386

This list of commands helps you to install locally gcc for i386.  
Then, you'll get `i386-elf-gcc` used currently by makefile.  

Intented to be used for qemu-i440fx (QEMU x86 i440fx/piix4)

```
$  mkdir cross
$  cd cross/
$  wget https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.xz
$  wget https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.xz
$  tar xf binutils-2.42.tar.xz
$  tar xf gcc-13.2.0.tar.xz
```

Following env variables will be used by `make` command of openUEFI.
```
$  export PREFIX="$HOME/cross/i386-elf"
$  export TARGET=i386-elf
$  export PATH="$PREFIX/bin:$PATH"
```

```
$ mkdir build-binutils
$ cd build-binutils
$  ../binutils-2.42/configure     --target=$TARGET     --prefix=$PREFIX     --with-sysroot     --disable-nls     --disable-werror
$  make -j$(nproc)
$  make install
$  cd ..
```

```
$  mkdir build-gcc
$  cd build-gcc
$  ../gcc-13.2.0/configure     --target=$TARGET     --prefix=$PREFIX     --disable-nls     --enable-languages=c     --without-headers
$  make all-gcc -j$(nproc)
$  make all-target-libgcc -j$(nproc)
$  make install-gcc
$  make install-target-libgcc
```

Vérification :  
```
$ i386-elf-gcc -v
$ i386-elf-ld -v
```

```
$ echo "int _start() { for(;;); }" > test.c
$ i386-elf-gcc -ffreestanding -nostdlib test.c -o test.elf
$ readelf -h test.elf
```
