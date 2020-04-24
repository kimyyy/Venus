.PHONY: clean qemu uefi gdb

all: main.efi

main.efi: main.o Makefile
	objcopy --target=efi-app-x86_64 $< $@

main.o: main.cpp Makefile
	x86_64-w64-mingw32-g++ -m64 -Wall -Wextra -g3  -nostdinc -nostdlib -fno-stack-protector -fshort-wchar -mno-red-zone -fno-builtin -e efi_main -o $@ $<

#x86_64-w64-mingw32-g++-win32 -Wall -Wextra -g3  -nostdinc -nostdlib -fno-stack-protector -fshort-wchar -mno-red-zone -fno-builtin -e efi_main -o $@ $<

qemu: Makefile
	cp main.efi fs/EFI/BOOT/BOOTX64.EFI
	qemu-system-x86_64 -bios /usr/share/ovmf/OVMF.fd -gdb tcp::10000 -S -drive file=fat:rw:fs

uefi: Makefile
	qemu-system-x86_64 -bios /usr/share/ovmf/OVMF.fd

gdb: Makefile fs/EFI/BOOT/BOOTX64.EFI
	gdb-multiarch fs/EFI/BOOT/BOOTX64.EFI

clean:
	rm -rf *.o *.efi
