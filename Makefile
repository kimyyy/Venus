.PHONY: all clean run gdb mkd gdb_k

# compiler choice
CC_LLVM = clang
CXX_LLVM = clang++-10
CC_GCC = x86_64-w64-mingw32-gcc
CXX_GCC = x86_64-w64-mingw32-g++ 

INCLUDE_LOADER = -I./include/loader
FLAGS_NOEXCEPTION = -fno-exceptions -fno-unwind-tables
CFLAGS_WARN = -Wall -Wextra
CFLAGS_GCC = -m64 $(CFLAGS_WARN) $(INCLUDE_LOADER) $(NEWLIB_INCLUDE) $(CXXINCLUDE) -g3 -fno-pic  -ffreestanding -nostdinc -nostdlib -fno-stack-protector -fshort-wchar -mno-red-zone -fno-builtin -MMD -MP $(FLAGS_NOEXCEPTION)
CFLAGS_LLVM = --target=x86_64-elf -gdwarf $(INCLUDE_LOADER) $(FLAGS_NOEXCEPTION) -fno-stack-protector -mno-red-zone -nostdlibinc -Wall -Wpedantic

ifdef LLVM
CC_LOADER = $(CC_LLVM)
CXX_LOADER = $(CXX_LLVM)
CFLAGS_LOADER = $(CFLAGS_LLVM)
else
CC_LOADER = $(CC_GCC)
CXX_LOADER = $(CXX_GCC)
CFLAGS_LOADER = $(CFLAGS_GCC)
endif

# linker choice
LD_GCC = x86_64-w64-mingw32-ld
LD_LLVM = ld.lld-10

EFI_ENTRY = -e efi_main
LDFLAGS_GCC = --subsystem 10 -e efi_main
LDFLAGS_LLVM = --entry KernelMain

ifdef LLVM
LD_LOADER = $(LD_LLVM)
LDFLAGS_LOADER = $(LDFLAGS_LLVM)
else
LD_LOADER = $(LD_GCC)
LDFLAGS_LOADER = $(LDFLAGS_GCC)
endif

# directory and file
BINPATH = ./bin
FSPATH = $(BINPATH)/fs
EFIPATH = $(FSPATH)/EFI/BOOT
TARGET = $(EFIPATH)/BOOTX64.EFI
KERNEL = $(FSPATH)/kernel.elf
SRCDIR = ./src
SRCDIR_LOADER = $(SRCDIR)/loader
OBJDIR = ./obj
OBJDIR_LOADER = $(OBJDIR)/loader

SRC_LOADER = $(wildcard $(SRCDIR_LOADER)/*.cpp)
OBJECTS_LOADER = $(addprefix $(OBJDIR_LOADER)/, $(notdir $(SRC_LOADER:.cpp=.o)))
DEPENDS = $(OBJECTS_LOADER:.o=.d)
ASMS = $(wildcard $(OBJDIR_LOADER)/*.s)

# thirdparty
NEWLIBPATH = ./newlib
NEWLIB_INCLUDE = -I$(NEWLIBPATH)/include
CXXINCLUDE = -I../../tools/local/lib/gcc/x86_64-none-elf/9.3.0/include

# tools
QEMU = qemu-system-x86_64
QEMU_FLAGS =  -m 4G -gdb tcp::10000 -cpu qemu64
QEMU_DBG_FLAG = -S
DBG = gdb-multiarch
DBG_FLAGS = -x start.gdb
DBG_FLAGS_KERNEL = -x kernel.gdb


# start recipe
all: clean mkd $(TARGET)

mkd:
	mkdir -p $(OBJDIR_LOADER)
	mkdir -p $(EFIPATH)

$(TARGET): $(OBJECTS_LOADER) $(LIBS)
	$(LD_LOADER) $(LDFLAGS_LOADER) -o $@ $^

$(OBJDIR_LOADER)/%.o: $(SRCDIR_LOADER)/%.cpp
	$(CXX_LOADER) $(CFLAGS_LOADER) -c $<  -o $@

$(OBJDIR_LOADER)/%.s: $(SRCDIR_LOADER)/%.cpp
	$(CXX_LOADER) $(CFLAGS_LOADER) -S -o $@ $<


# use tools
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
	rm -f  $(OBJECTS) $(DEPENDS) $(ASMS) $(TARGET)

-include $(DEPENDS)
