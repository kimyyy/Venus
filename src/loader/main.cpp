#include "common_loader.hpp"
#include "efi.hpp"
#include "shell.hpp"
#include "graphics.hpp"
#include "cstring.hpp"
#include "memmanage.hpp"
#include "wstring.hpp"
#include "serial.hpp"
#include "bootInfo.hpp"
#include <elf.h>

static_assert(sizeof(EfiSystemTable) == 104, "invalid size of SystemTable");

EfiGuid EfiFileInfoGuid = {0x09576e92, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};

EfiFileProtocol *openRootFile(EfiHandle ImageHandle){
    EfiFileProtocol *root;
    EfiLoadedImageProtocol* lip;
    EfiStatus status = ST->BootServices->HandleProtocol(ImageHandle, &lip_guid, (void**)&lip);
    assert_status(status, L"getLoadedImageProtocol");

    status = ST->BootServices->HandleProtocol(lip->DeviceHandle, &sfsp_guid, (void**)&SFSP);
    assert_status(status, L"getSympleFileSystemProtocol");

    status = SFSP->OpenVolume(SFSP, &root);
    assert_status(status, L"getroot");

    return root;
}

void jumpToKernel(void *entry_point, BootInfo* info){
    asm volatile("mov %%rdx, %%rdi":: "d" (info));
    asm volatile("call %%rcx":: "c" (entry_point));
}

extern "C"
int efi_main(EfiHandle ImageHandle , EfiSystemTable *SystemTable){

    efi_init(SystemTable);
    EfiFileProtocol *kernelFile;
    EfiFileProtocol *root;

    EfiPhysicalAddress elfbufAddr = 0x100000000;
    uint64_t elfbufSize;

    char kernelFileInfoBuf[200];
    EfiFileInfo *kernelFileInfo;
    UINTN kernelFileInfoBuffersize = 200;

    Elf64_Ehdr *elfHeader;
    Elf64_Phdr *elfPhdr;
    EfiStatus status;


    // open root from where we boot
    root = openRootFile(ImageHandle);

    // open and read kernel.elf
    status = root->Open(root, &kernelFile, L"\\kernel.elf", EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
    assert_status(status, L"OpenkernelFile");

    kernelFile->GetInfo(kernelFile, &EfiFileInfoGuid, &kernelFileInfoBuffersize,
            (void *)kernelFileInfoBuf);
    assert_status(status, L"GetkernelFileInfo");

    kernelFileInfo = reinterpret_cast<EfiFileInfo*>(kernelFileInfoBuf);
    puts(kernelFileInfo->FileName);
    puts(L"\r\n");

    // allocate buffer for elf file
    uint64_t page_size = (kernelFileInfo->FileSize + EfiPageSize - 1) /EfiPageSize;
    elfbufSize = page_size * EfiPageSize;
    status = ST->BootServices->AllocatePages(AllocateMaxAddress, EfiLoaderData,
            page_size, (UINTN *)&elfbufAddr);
    assert_status(status, L"AllocatePageForKernelElfBuf");

    status = kernelFile->Read(kernelFile, &elfbufSize, (void *)elfbufAddr);
    assert_status(status, L"ReadKernelElf");

    // parse elf header
    elfHeader = reinterpret_cast<Elf64_Ehdr *>(elfbufAddr);
    puts(L"Elf Header: ");
    puts(L" e_phoff: ");
    puth(elfHeader->e_phoff, 8);
    puts(L" e_ehsize: ");
    puth(elfHeader->e_ehsize, 8);
    puts(L"\r\n");
    // parse program header
    elfPhdr = reinterpret_cast<Elf64_Phdr *>(elfbufAddr + elfHeader->e_phoff);
    for(int i = 0; i < elfHeader->e_phnum;i++){
        puts(L"Program Header: ");
        puth(i, 1);
        puts(L"\r\n");
        puts(L"p_type: ");
        puth(elfPhdr[i].p_type, 2);
        puts(L" p_offset: ");
        puth(elfPhdr[i].p_offset, 8);
        puts(L" p_vaddr: ");
        puth(elfPhdr[i].p_vaddr, 8);
        puts(L" p_filesz: ");
        puth(elfPhdr[i].p_filesz, 8);
        puts(L" p_memsz: ");
        puth(elfPhdr[i].p_memsz, 8);
        puts(L"\r\n");

        if(elfPhdr[i].p_type != PT_LOAD)continue;
        // if PT_LOAD, load to memory
        puts(L"copy from: ");
        puth(elfbufAddr + elfPhdr[i].p_offset, 16);
        puts(L" to: ");
        puth(elfPhdr[i].p_paddr, 16);
        puts(L" for :");
        puth(elfPhdr[i].p_filesz, 8);
        puts(L" bytes \r\n");
        memcpy(reinterpret_cast<char *>(elfPhdr[i].p_vaddr),
                reinterpret_cast<char *>(elfbufAddr + elfPhdr[i].p_offset),
                elfPhdr[i].p_filesz);
        puts(L"zeromem ");
        puth(elfPhdr[i].p_vaddr + elfPhdr[i].p_filesz, 16);
        puts(L" for: ");
        puth(elfPhdr[i].p_memsz - elfPhdr[i].p_filesz, 8);
        puts(L" bytes \r\n");
        memzero(reinterpret_cast<char*>(elfPhdr[i].p_vaddr + elfPhdr[i].p_filesz), elfPhdr[i].p_memsz - elfPhdr[i].p_filesz);
    }
    // get framebuffer info
    FrameBufferInfo fb;
    fb.base = GOP->Mode->FrameBufferBase;
    fb.size = GOP->Mode->FrameBufferSize;
    fb.hr = GOP->Mode->Info->HorizontalResolution;
    fb.vr = GOP->Mode->Info->VerticalResolution;

    UINTN heap_pages = 10;
    uint64_t heap_size = 10 * 1<<12;
    EfiPhysicalAddress heap_start = 0x120000000;
    status = ST->BootServices->AllocatePages(AllocateAddress, EfiLoaderData,heap_pages, &heap_start);
    assert_status(status, L"AllocateHeap");
    HeapInfo hp = {heap_start, heap_size};

    // get memory map
    UINTN memorymap_size = 4096;
    EfiMemoryDescriptor *memorymap = (EfiMemoryDescriptor*)malloc(memorymap_size);
    UINTN mapkey;
    UINTN descriptorsize;
    status = ST->BootServices->GetMemoryMap(&memorymap_size, memorymap, &mapkey, &descriptorsize, NULL);
    assert_status(status,L"getmemorymap");

    ClearScreen();

    // exit boot services
    status = ST->BootServices->ExitBootServices(ImageHandle, mapkey);
    assert_status(status, L"ExitBOotServices");

    BootInfo bi;
    bi.fb = fb;
    bi.heapinfo = hp;
    jumpToKernel((void*)elfHeader->e_entry, &bi);

    // panic
    while(TRUE);
    return 0;
}
