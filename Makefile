.PHONY: clean run gdb

CXX:= x86_64-w64-mingw32-g++
CFLAGS := -m64 -Wall -Wextra -g3  -nostdinc -nostdlib -fno-stack-protector -fshort-wchar -mno-red-zone -fno-builtin
OBJCP:= objcopy
QEMU := qemu-system-x86_64

EFIPATH := fs/EFI/BOOT/BOOTX64.EFI
EFI_ENTRY := efi_main

all: main.efi

main.efi: main.o Makefile
	$(OBJCP) --target=efi-app-x86_64 $< $@

main.o: main.cpp Makefile
	$(CXX) $(CFLAGS) -e $(EFI_ENTRY)  -o $@ $<


run: main.efi Makefile
	cp $< $(EFIPATH)
	$(QEMU) -bios /usr/share/ovmf/OVMF.fd -gdb tcp::10000 -S -drive file=fat:rw:fs

gdb: Makefile fs/EFI/BOOT/BOOTX64.EFI
	gdb-multiarch $(EFIPATH)

clean:
	rm -rf *.o *.efi
