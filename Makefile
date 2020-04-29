.PHONY: clean run gdb

CC:= x86_64-w64-mingw32-g++
CFLAGS := -m64 -Wall -Wextra -g3  -nostdinc -nostdlib -fno-stack-protector -fshort-wchar -mno-red-zone -fno-builtin
OBJCP:= objcopy
QEMU := qemu-system-x86_64
QEMU_FLAG :=  -gdb tcp::10000 -S -cpu qemu64 -drive file=fat:rw:fs

SRC:= main.cpp efi.cpp common.cpp shell.cpp graphics.cpp gui.cpp file.cpp

EFIPATH := fs/EFI/BOOT/BOOTX64.EFI
EFI_ENTRY := efi_main

all: $(EFIPATH)

$(EFIPATH): main.o $(SRC)
	$(OBJCP) --target=efi-app-x86_64 $< $@

main.o: $(SRC)
	$(CC) $(CFLAGS) -e $(EFI_ENTRY)  -o $@ $^

run: $(EFIPATH) $(SRC)
	$(QEMU) -bios /usr/share/ovmf/OVMF.fd $(QEMU_FLAG)

#--device qemu-xhci device usb-mouse -device usb-kbd 

gdb: $(EFIPATH) $(SRC)
	gdb-multiarch -x start.gdb $(EFIPATH)

clean:
	rm -rf *.o *.efi
