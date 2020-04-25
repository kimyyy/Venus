.PHONY: clean run gdb

CC:= x86_64-w64-mingw32-g++
CFLAGS := -m64 -Wall -Wextra -g3  -nostdinc -nostdlib -fno-stack-protector -fshort-wchar -mno-red-zone -fno-builtin
OBJCP:= objcopy
QEMU := qemu-system-x86_64

EFIPATH := fs/EFI/BOOT/BOOTX64.EFI
EFI_ENTRY := efi_main

all: main.efi

main.efi: main.o
	$(OBJCP) --target=efi-app-x86_64 $^ $@

main.o: main.cpp efi.cpp common.cpp shell.cpp graphics.cpp gui.cpp
	$(CC) $(CFLAGS) -e $(EFI_ENTRY)  -o $@ $^

run: main.efi
	cp $< $(EFIPATH)
	$(QEMU) -bios /usr/share/ovmf/OVMF.fd -gdb tcp::10000 -S -cpu qemu64 -drive file=fat:rw:fs
#--device qemu-xhci device usb-mouse -device usb-kbd 
gdb: Makefile fs/EFI/BOOT/BOOTX64.EFI
	gdb-multiarch -x start.gdb $(EFIPATH)

clean:
	rm -rf *.o *.efi
