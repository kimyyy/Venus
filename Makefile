.PHONY: all clean run gdb mkd gdb_k

# compiler choice
CC_LLVM = clang
CXX_LLVM = clang++-10
CC_GCC = x86_64-w64-mingw32-gcc
CXX_GCC = x86_64-w64-mingw32-g++ 

INCLUDE = -I./include
FLAGS_NOEXCEPTION = -fno-exceptions -fno-unwind-tables
CFLAGS_WARN = -Wall -Wextra
CFLAGS_GCC = -m64 $(CFLAGS_WARN) $(INCLUDE) $(NEWLIB_INCLUDE) $(CXXINCLUDE) -g3 -fno-pic  -ffreestanding -nostdinc -nostdlib -fno-stack-protector -fshort-wchar -mno-red-zone -fno-builtin -MMD -MP $(FLAGS_NOEXCEPTION)
CFLAGS_LLVM = --target=x86_64-elf -gdwarf $(INCLUDE) $(FLAGS_NOEXCEPTION) -fno-stack-protector -mno-red-zone -nostdlibinc -Wall -Wpedantic

ifdef LLVM
CC = $(CC_LLVM)
CXX = $(CXX_LLVM)
CFLAGS = $(CFLAGS_LLVM)
else
CC = $(CC_GCC)
CXX = $(CXX_GCC)
CFLAGS = $(CFLAGS_GCC)
endif

# linker choice
LD_GCC = x86_64-w64-mingw32-ld
LD_LLVM = ld.lld-10

EFI_ENTRY = -e efi_main
LDFLAGS_GCC = --subsystem 10 -e efi_main
LDFLAGS_LLVM = --entry KernelMain

ifdef LLVM
LD = $(LD_LLVM)
LDFLAGS = $(LDFLAGS_LLVM)
else
LD = $(LD_GCC)
LDFLAGS = $(LDFLAGS_GCC)
endif

# directory and file
BINPATH = ./bin
FSPATH = $(BINPATH)/fs
EFIPATH = $(FSPATH)/EFI/BOOT
TARGET = $(EFIPATH)/BOOTX64.EFI
KERNEL = $(FSPATH)/kernel.elf
SRCDIR = ./src
OBJDIR = ./obj
NEWLIBPATH = ./newlib
NEWLIB_INCLUDE = -I$(NEWLIBPATH)/include
CXXINCLUDE = -I../../tools/local/lib/gcc/x86_64-none-elf/9.3.0/include

SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SRC:.cpp=.o)))
DEPENDS = $(OBJECTS:.o=.d)

# tools
QEMU = qemu-system-x86_64
QEMU_FLAGS =  -m 4G -gdb tcp::10000 -cpu qemu64
QEMU_DBG_FLAG = -S
DBG = gdb-multiarch
DBG_FLAGS = -x start.gdb
DBG_FLAGS_KERNEL = -x kernel.gdb

all: clean mkd $(TARGET)

mkd:
	mkdir -p $(OBJDIR)
	mkdir -p $(EFIPATH)

$(TARGET): $(OBJECTS) $(LIBS)
	$(LD) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -c $<  -o $@

$(OBJDIR)/%.s: $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -S -o $@ $<

run: $(TARGET)
	$(QEMU) $(QEMU_FLAGS) \
	-drive if=pflash,format=raw,readonly,file=$(HOME)/OVMF/OVMF_CODE.fd \
	-drive if=pflash,format=raw,file=$(HOME)/OVMF/OVMF_VARS.fd \
	-drive dir=$(FSPATH),driver=vvfat,rw=on \
	$(QEMU_ADDITIONAL_ARGS)

#--device qemu-xhci device usb-mouse -device usb-kbd 

gdb: $(TARGET) $(SRC)
	$(DBG) $(DBG_FLAGS) $(TARGET)

gdb_k:
	$(DBG) $(DBG_FLAGS_KERNEL) $(KERNEL)

clean:
	rm -f  $(OBJECTS) $(DEPENDS) $(TARGET)

-include $(DEPENDS)
