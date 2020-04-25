# uefi_baremetal

Baremetal uefi application written by c++.

This application is based on uefi_baremetal tutorial paper by Takuma Ogami.

# How to build and start

This application need 

- qemu-system-x86_64
- x86_64-w64-mingw32-g++
- objcopy with --target=efi-app-x86_64

To build the project, in the root of the project, just make.

```
make
```

To run in qemu, 

```
make run
```


To debug the qemu in gdb, in another console, 

```
make gdb
```

Breakpoint to the application entrypoint "efi_main" will be automatically set.
