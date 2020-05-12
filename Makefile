.PHONY: all clean run gdb mkd gdb_k

# compiler choice
CC_LLVM = clang
CXX_LLVM = clang++-10
CC_LOADER_GCC = x86_64-w64-mingw32-gcc
CXX_LOADER_GCC = x86_64-w64-mingw32-g++ 
CC_KERNEL_GCC = x86_64-none-elf-gcc
CXX_KERNEL_GCC = x86_64-none-elf-g++

INCLUDE_COMMON = -I./include/common
INCLUDE_LOADER = -I./include/loader $(INCLUDE_COMMON)
INCLUDE_KERNEL = -I./include/kernel $(INCLUDE_COMMON)
FLAGS_NOEXCEPTION = -fno-exceptions -fno-unwind-tables
CFLAGS_WARN = -Wall -Wextra
CFLAGS_GCC = -m64 $(CFLAGS_WARN) $(NEWLIB_INCLUDE) $(CXXINCLUDE) -g3 -fno-pic  -ffreestanding -nostdinc -nostdlib -fno-stack-protector -fshort-wchar -mno-red-zone -fno-builtin -MMD -MP $(FLAGS_NOEXCEPTION)
CFLAGS_LLVM = --target=x86_64-elf -gdwarf $(FLAGS_NOEXCEPTION) -fno-stack-protector -mno-red-zone -nostdlibinc -Wall -Wpedantic

ifdef LLVM
CC_LOADER = $(CC_LLVM)
CC_KERNEL = $(CC_LLVM)
CXX_LOADER = $(CXX_LLVM)
CXX_KERNEL = $(CXX_LLVM)
CFLAGS_LOADER = $(CFLAGS_LLVM) $(INCLUDE_LOADER)
CFLAGS_KERNEL = $(CFLAGS_LLVM) $(INCLUDE_KERNEL)
else
CC_LOADER = $(CC_LOADER_GCC)
CC_KERNEL =  $(CC_KERNEL_GCC)
CXX_LOADER = $(CXX_LOADER_GCC)
CXX_KERNEL = $(CXX_KERNEL_GCC)
CFLAGS_LOADER = $(CFLAGS_GCC) $(INCLUDE_LOADER)
CFLAGS_KERNEL = $(CFLAGS_GCC) $(INCLUDE_KERNEL)
endif

# linker choice
LD_LOADER_GCC = x86_64-w64-mingw32-ld
LD_LOADER_LLVM = ld.lld-10
LD_KERNEL_GCC = x86_64-none-elf-ld
LD_KERNEL_LLVM = ld.lld-10

LDFLAGS_LOADER_GCC = --subsystem 10 -e efi_main
LDFLAGS_LOADER_LLVM = --entry efi_main
LDFLAGS_KERNEL_GCC = -static -T $(SRCDIR_KERNEL)/kernel.ld
LDFLAGS_KERNEL_LLVM = $(LDFLAGS_KERNEL_GCC)

ifdef LLVM
LD_LOADER = $(LD_LOADER_LLVM)
LDFLAGS_LOADER = $(LDFLAGS_LOADER_LLVM)
LD_KERNEL = $(LD_KERNEL_LLVM)
LDFLAGS_KERNEL = $(LDFLAGS_KERNEL_LLVM)
else
LD_LOADER = $(LD_LOADER_GCC)
LD_KERNEL = $(LD_KERNEL_GCC)
LDFLAGS_LOADER = $(LDFLAGS_LOADER_GCC)
LDFLAGS_KERNEL = $(LDFLAGS_KERNEL_GCC)
endif

# directory
BINPATH = ./bin
FSPATH = $(BINPATH)/fs
EFIPATH = $(FSPATH)/EFI/BOOT
SRCDIR = ./src
SRCDIR_LOADER = $(SRCDIR)/loader
SRCDIR_KERNEL = $(SRCDIR)/kernel
SRCDIR_COMMON = $(SRCDIR)/common
OBJDIR = ./obj
OBJDIR_LOADER = $(OBJDIR)/loader
OBJDIR_KERNEL = $(OBJDIR)/kernel
OBJDIR_COMMON = $(OBJDIR)/common
OBJDIRS = $(OBJDIR_LOADER) $(OBJDIR_KERNEL) $(OBJDIR_COMMON)

# files
SRC_LOADER = $(wildcard $(SRCDIR_LOADER)/*.cpp)
SRC_KERNEL = $(wildcard $(SRCDIR_KERNEL)/*.cpp)
SRC_COMMON = $(wildcard $(SRCDIR_COMMON)/*.cpp)
OBJECTS = $(OBJECTS_KERNEL) $(OBJECTS_LOADER)
OBJECTS_LOADER = $(addprefix $(OBJDIR_LOADER)/, $(notdir $(SRC_LOADER:.cpp=.o))) $(addprefix $(OBJDIR_COMMON)/, $(notdir $(SRC_COMMON:.cpp=.loader.o)))
OBJECTS_KERNEL = $(addprefix $(OBJDIR_KERNEL)/, $(notdir $(SRC_KERNEL:.cpp=.o))) $(addprefix $(OBJDIR_COMMON)/, $(notdir $(SRC_COMMON:.cpp=.kernel.o)))
DEPENDS = $(DEPENDS_KERNEL) $(DEPENDS_LOADER)
DEPENDS_LOADER = $(OBJECTS_LOADER:.o=.d)
DEPENDS_KERNEL = $(OBJECTS_KERNEL:.o=.d)
ASMS = $(OBJECTS:.o=.s)

LOADER = $(EFIPATH)/BOOTX64.EFI
KERNEL = $(FSPATH)/kernel.elf

TARGET = $(LOADER) $(KERNEL)

# thirdparty
NEWLIBPATH = ./newlib
NEWLIB_INCLUDE = -I$(NEWLIBPATH)/include
CXXINCLUDE = -I../../tools/local/lib/gcc/x86_64-none-elf/9.3.0/include

# tools
QEMU = qemu-system-x86_64
QEMU_FLAGS =  -m 4G -gdb tcp::10000 -cpu qemu64
QEMU_ADDITIONAL_ARGS = -nographic
QEMU_DBG_FLAG = -S
DBG = gdb-multiarch
DBG_FLAGS = -x start.gdb
DBG_FLAGS_KERNEL = -x kernel.gdb


# start recipe
all: clean mkd $(TARGET)

mkd:
	mkdir -p $(OBJDIRS)
	mkdir -p $(EFIPATH)

# loader

$(LOADER): $(OBJECTS_LOADER) $(LIBS)
	$(LD_LOADER) $(LDFLAGS_LOADER) -o $@ $^

$(OBJDIR_LOADER)/%.o: $(SRCDIR_LOADER)/%.cpp
	$(CXX_LOADER) $(CFLAGS_LOADER) -c $<  -o $@

$(OBJDIR_COMMON)/%.loader.o: $(SRCDIR_COMMON)/%.cpp
	$(CXX_LOADER) $(CFLAGS_LOADER) -c $< -o $@

$(OBJDIR_LOADER)/%.s: $(SRCDIR_LOADER)/%.cpp
	$(CXX_LOADER) $(CFLAGS_LOADER) -S -o $@ $<


# kernel

$(KERNEL): $(OBJECTS_KERNEL)
	$(LD_KERNEL) $(LDFLAGS_KERNEL) -o $@ $^

$(OBJDIR_KERNEL)/%.o : $(SRCDIR_KERNEL)/%.cpp
	$(CXX_KERNEL) $(CFLAGS_KERNEL) -c $< -o $@

$(OBJDIR_COMMON)/%.kernel.o: $(SRCDIR_COMMON)/%.cpp
	$(CXX_KERNEL) $(CFLAGS_KERNEL) -c $< -o $@

$(OBJDIR_KERNEL)/%.s : $(SRCDIR_KERNEL)/%.cpp
	$(CXX_KERNEL) $(CFLAGS_KERNEL) -s -o $@ $<



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
