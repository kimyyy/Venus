.PHONY: clean run gdb

CXX:= x86_64-w64-mingw32-g++
CFLAGS := -m64 -Wall -Wextra -g3  -ffreestanding -nostdinc -nostdlib -fno-stack-protector -fshort-wchar -mno-red-zone -fno-builtin -fno-permissive
FLAGS_NOEXCEPTION := -fno-exceptions -fno-unwind-tables
OBJCP:= objcopy
QEMU := qemu-system-x86_64
QEMU_FLAGS :=  -m 4G -gdb tcp::10000 -S -cpu qemu64

SRC:= main.cpp efi.cpp common.cpp memmanage.cpp cstring.cpp shell.cpp graphics.cpp gui.cpp file.cpp
SRC_TMP := main.cpp efi.cpp common.cpp cstring.cpp memmanage.cpp wstring.cpp

EFIPATH := fs/EFI/BOOT/BOOTX64.EFI
EFI_ENTRY := efi_main

all: $(EFIPATH)

$(EFIPATH): main.o $(SRC)
	$(OBJCP) --target=efi-app-x86_64 $< $@

main.o: $(SRC_TMP)
	$(CXX) $(CFLAGS) $(FLAGS_NOEXCEPTION) -e $(EFI_ENTRY)  -o $@ $^

main.s: $(SRC)
	$(CXX) -S -o main.s main.cpp

run: $(EFIPATH) $(SRC)
	$(QEMU) $(QEMU_FLAGS) \
	-drive if=pflash,format=raw,readonly,file=$(HOME)/OVMF/OVMF_CODE.fd \
	-drive if=pflash,format=raw,file=$(HOME)/OVMF/OVMF_VARS.fd \
	-drive dir=fs,driver=vvfat,rw=on \
	$(QEMU_ADDITIONAL_ARGS)

#--device qemu-xhci device usb-mouse -device usb-kbd 

gdb: $(EFIPATH) $(SRC)
	gdb-multiarch -x start.gdb $(EFIPATH)

clean:
	rm -rf *.o *.efi
