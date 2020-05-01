.PHONY: clean run gdb

CXX:= x86_64-w64-mingw32-g++
CFLAGS := -m64 -Wall -Wextra -g3  -ffreestanding -nostdinc -nostdlib -fno-stack-protector -fshort-wchar -mno-red-zone -fno-builtin -MMD -MP
FLAGS_NOEXCEPTION := -fno-exceptions -fno-unwind-tables
OBJCP:= objcopy
QEMU := qemu-system-x86_64
QEMU_FLAGS :=  -m 4G -gdb tcp::10000 -S -cpu qemu64

FSPATH := ./bin/fs
EFIPATH := $(FSPATH)/EFI/BOOT

INCLUDE = -I./include
TARGET = $(EFIPATH)/BOOTX64.EFI
SRCDIR = ./src
OBJDIR = ./obj

SRC:= $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(filter-out $(OBJDIR)/main.o, $(addprefix $(OBJDIR)/, $(notdir $(SRC:.cpp=.o))))
DEPENDS = $(OBJECTS:.o=.d)

EFI_ENTRY := -e efi_main

all: clean $(TARGET)

$(TARGET): $(OBJDIR)/main.o
	mkdir -p $(EFIPATH)
	$(OBJCP) --target=efi-app-x86_64 $< $@

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(OBJECTS) $(LIBS)
	$(CXX) $(CFLAGS) $(INCLUDE) $(FLAGS_NOEXCEPTION) $(EFI_ENTRY)  -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) $(FLAGS_NOEXCEPTION) $< -c  -o $@

$(OBJDIR)/%.s: $(SRCDIR)/%.cpp
	$(CXX) -S -o $@ $<

run: $(TARGET)
	$(QEMU) $(QEMU_FLAGS) \
	-drive if=pflash,format=raw,readonly,file=$(HOME)/OVMF/OVMF_CODE.fd \
	-drive if=pflash,format=raw,file=$(HOME)/OVMF/OVMF_VARS.fd \
	-drive dir=$(FSPATH),driver=vvfat,rw=on \
	$(QEMU_ADDITIONAL_ARGS)

#--device qemu-xhci device usb-mouse -device usb-kbd 

gdb: $(TARGET) $(SRC)
	gdb-multiarch -x start.gdb $(TARGET)

clean:
	rm -f $(OBJDIR)/main.o $(OBJECTS) $(DEPENDS) $(TARGET)

-include $(DEPENDS)
