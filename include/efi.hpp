#include "common.hpp"
#include <stdint.h>
#include <stddef.h>

#pragma once

typedef uint64_t UINTN;
typedef int64_t INTN;

typedef void* EfiHandle;
typedef UINTN EfiStatus;

typedef uint64_t EfiPhysicalAddress;
typedef uint64_t EfiVirtualAddress;


// Open Modes
#define EFI_FILE_MODE_READ 0x0000000000000001
#define EFI_FILE_MODE_WRITE 0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000

// File Attributes
#define EFI_FILE_READ_ONLY 0x0000000000000001

// EFI_STATUS
#define EFI_SUCCESS	0
#define EFI_ERROR	0x8000000000000000
#define EFI_UNSUPPORTED	(EFI_ERROR | 3)

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL	0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL		0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL		0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER	0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER		0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE		0x00000020

enum EfiAllocateType {
    AllocateAnyPages,
    AllocateMaxAddress,
    AllocateAddress,
    MaxAllocateType
};

enum EfiMemoryType {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiMaxMemoryType
};

enum EfiTimerDelay {
    TimerCancel,
    TimerPeriodic,
    TimerRelative,
};

enum EfiResetType {
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
};

struct EfiInputKey {
  wchar_t ScanCode;
  wchar_t UnicodeChar;
};

struct EfiGuid {
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t Data4[8];
};

struct EfiDevicePathProtocol {
    uint8_t Type;
    uint8_t SubType;
    uint8_t Length[2];
};

struct EfiSimpleTextOutputProtocol {
  EfiStatus _buf;
  EfiStatus (*OutputString)(EfiSimpleTextOutputProtocol *This, const wchar_t *String);
  EfiStatus _buf2[4];
  EfiStatus (*ClearScreen)(EfiSimpleTextOutputProtocol *This);
};

struct EfiSimpleTextInputProtocol {
  EfiStatus (*Reset)();
  EfiStatus (*ReadKeyStroke)(EfiSimpleTextInputProtocol *This, EfiInputKey *Key);
  void *WaitForKey;
};

struct EfiRuntimeServices {
    char _buf_rs1[24];

    // Time Services
    ull _buf_rs2[4];

    // Virtual Memory Services
    ull _buf_rs3[2];

    // variable Services
    ull _buf_rs4[3];

    // Miscellaneous Services
    ull _buf_rs5;
    void (*ResetSystem)(EfiResetType ResetType, ull ResetStatus, ull DataSize, void *ResetData);
};

struct EfiMemoryDescriptor {
    EfiMemoryType Type;
    EfiPhysicalAddress PhysicalStart;
    EfiVirtualAddress VirtualStart;
    uint64_t NumberOfPages;
    uint64_t Attribute;
};

struct EfiBootServices {
    char _buf1[24];

    // Task Priority Services
    EfiStatus _buf2[2];
    
    // Memory Services
    EfiStatus (*AllocatePages)(EfiAllocateType Type, EfiMemoryType MemoryType, UINTN Pages, EfiPhysicalAddress *PhysicalAddress);
    EfiStatus (*FreePages) (EfiPhysicalAddress PhysicalAddress, UINTN Pages);
    EfiStatus (*GetMemoryMap)(UINTN *MemoryMapsize, EfiMemoryDescriptor *MemoryMap, UINTN *MapKey, UINTN *DescriptorSize, uint32_t *DescriptorVersion);
    EfiStatus (*AllocatePool)(EfiMemoryType PoolType, UINTN Size, void **Buffer);
    EfiStatus (*FreePool)(void *Buffer);

    // Event and Timer Services
    EfiStatus (*CreateEvent)(
            uint32_t Type,
            ull NotifyTpl,
            void (*NotifyFunction)(void *Event, void *Context),
            void *NotifyContext,
            void *Event);
    EfiStatus (*SetTimer)(void *Event, EfiTimerDelay Type, ull TriggerTime);
    EfiStatus (*WaitForEvent) (ull NumberOfEvents, void **Event, ull *Index);
    EfiStatus _buf4_2[3];

    // Protorcol Handler Services
    EfiStatus (*InstallProtocolInterface)();
    EfiStatus (*ReintallProtocolInterface)();
    EfiStatus (*UninstallProtocolInterface)();
    EfiStatus (*HandleProtocol)(void* Handle, EfiGuid *guid, void **Interface);
    void* Reserved;
    EfiStatus (*RegisterProtocolNotify)();
    EfiStatus (*LocateHandle)();
    EfiStatus (*LocateDevicePath)();
    EfiStatus (*InstallConfigurationTable)();

    // Image Services
    EfiStatus (*LoadImage)(
            uint8_t BootPolicy,
            void *ParentImageHandle,
            EfiDevicePathProtocol *DevicePath,
            void *SourceBuffer,
            ull SourceSize,
            void **ImageHandle);
    EfiStatus (*StartImage)(
            void *ImageHandle,
            ull *ExitDataSize,
            uint16_t **ExitData);
    EfiStatus (*Exit)(void *ImageHandle, ull ExitStatus, ull ExitDataSize, wchar_t *ExitData);;
    EfiStatus (*UnloadImage)(void *ImageHandle);
    EfiStatus (*ExitBootServices)(void *ImageHandle, ull MapKey);

    // Miscellaneous Services
    EfiStatus _buf7[2];
    EfiStatus (*SetWatchdogTimer) (ull Timeout, ull WatchdogCode, ull DataSize, wchar_t *WatchdogData);

    // DriverSupport Services
    EfiStatus _buf8[2];

    // Open and Close Protocol Services
    EfiStatus (*OpenProtocol) (
            void *Handle,
            EfiGuid *Protocol,
            void **Interface,
            void *AgentHandle,
            void *ControllerHandle,
            uint32_t Attributes
            );
    EfiStatus _buf9[2];

    // Library Services
    EfiStatus _buf10[2];
    EfiStatus (*LocateProtocol) (EfiGuid *Protocol, void *Registration, void **Interface);
    EfiStatus _buf10_2[2];

    // 32-bit CRC Servies
    EfiStatus _buf11;

    // Miscellaneous Services
    EfiStatus _buf12[3];
};

struct EfiGraphicsOutputBitPixel {
    uint8_t Blue;
    uint8_t Green;
    uint8_t Red;
    uint8_t Reserved;
};

struct EfiGraphicsOutputModeInfo {
    uint32_t Version;
    uint32_t HorizontalResolution;
    uint32_t VerticalResolution;
    enum EfiGraphicsPixelFormat {
        PixelRedGreenBlueReserved8BitPerColor,
        PixelBlueGreenRedReserved8BitPerColor,
        PixelBitMask,
        PixelBltOnly,
        PixelFormatMax
    } PixelFormat;
};

struct EfiGraphicsOutputPtorocolMode {
    uint32_t MaxMode;
    uint32_t Mode;
    EfiGraphicsOutputModeInfo * Info;
    ull SizeOfInfo;
    ull FrameBufferBase;
};

struct EfiGraphicsOutputPtorocol {
    ull _buf[3];
    EfiGraphicsOutputPtorocolMode *Mode;
};

struct EfiSimplePointerState{
    int32_t RelativeMovementX;
    int32_t RelativeMovementY;
    int32_t RelativeMovementZ;
    uint8_t LeftButton;
    uint8_t RightButton;
};

struct EfiSimplePointerProtocol{
    ull (*Reset) (EfiSimplePointerProtocol *This, uint8_t ExtendedVerification);
    ull (*GetState) (EfiSimplePointerProtocol *This, EfiSimplePointerState *State);
    void *WaitForInput;
};

struct EfiTime {
    uint16_t year;
    uint8_t Month;
    uint8_t Day;
    uint8_t Hour;
    uint8_t Minute;
    uint8_t Second;
    uint8_t Pad1;
    uint32_t Nanosecond;
    short Timezone;
    uint8_t Daylight;
    uint8_t Pad2;
};

struct EfiFileInfo {
    //uint8_t _buf[80];
    uint64_t size;
    uint64_t FileSize;
    uint64_t PhysicalSize;
    EfiTime CreateTime;
    EfiTime LastAccessTime;
    EfiTime ModificationTime;
    uint64_t Attribute;
    wchar_t FileName[];
};

struct EfiFileProtocol {
    uint64_t Revision;
    EfiStatus (*Open)(EfiFileProtocol *This, EfiFileProtocol **NewHandle, const wchar_t *FileName, uint64_t OpenMode, uint64_t Attributes);
    EfiStatus (*Close)(EfiFileProtocol *This);
    EfiStatus (*Delete)(EfiFileProtocol *This);
    EfiStatus (*Read)(EfiFileProtocol *This, UINTN *BufferSize, void *Buffer);
    EfiStatus (*Write)(EfiFileProtocol *This, UINTN *BufferSize, void *Buffer);
    EfiStatus (*GetPosition)(EfiFileProtocol *This, uint64_t *Position);
    EfiStatus (*SetPosition)(EfiFileProtocol *This, uint64_t Position);
    EfiStatus (*GetInfo)(EfiFileProtocol *This, EfiGuid *InformationType, UINTN *BufferSize, void *Buffer);
    EfiStatus (*SetInfo)(EfiFileProtocol *This, EfiGuid *InformationType, UINTN *BufferSize, void *Buffer);
    EfiStatus (*Flush)(EfiFileProtocol *This);
    // Extra functions (if revision 2)
};

struct EfiSimpleFileSystemProtocol {
    uint64_t Revision;
    EfiStatus (*OpenVolume)(EfiSimpleFileSystemProtocol *This, EfiFileProtocol **Root);
};

struct EfiSystemTable {
    char _buf[44];
    EfiSimpleTextInputProtocol *ConIn;
    uint64_t _buf2;
    EfiSimpleTextOutputProtocol *ConOut;
    uint64_t _buf3[2];
    EfiRuntimeServices *RuntimeServices;
    EfiBootServices *BootServices;
};

struct EfiLoadedImageProtocol {
    uint32_t Revision;
    EfiHandle ParentHandle;
    EfiSystemTable *SystemTable;
    // Source location of the image
    EfiHandle DeviceHandle;
    EfiDevicePathProtocol *FilePath;
    void *Reserved;
    // Image's load options
    uint32_t LoadOptionSize;
    void *LoadOptions;
    // Location where image was loaded
    void *ImageBase;
    uint64_t ImageSize;
    EfiMemoryType ImageCodeType;
    EfiMemoryType ImageDataType;
    EfiStatus (*Unload)(void *ImageHandle);
};

struct EfiDevicePathToTextProtocol {
    ull _buf;
    wchar_t *(*ConvertDevicePathToText)(const EfiDevicePathProtocol *DeviceNode, uint8_t DisplayOnly, uint8_t AllowShortcuts);
};

struct EfiDevicePathFromTextProtocol {
    ull _buf;
    EfiDevicePathProtocol *(*ConvertTextToDevicePath) (const wchar_t *TextDevicePath);
};

struct EfiDevicePathUtilitiesProtocol {
    ull _buf[3];
    EfiDevicePathProtocol *(*AppendDeviceNode)(const EfiDevicePathProtocol *DevicePath, EfiDevicePathProtocol *DeviceNode);
};


extern EfiSystemTable *ST;
extern EfiGraphicsOutputPtorocol *GOP;
extern EfiSimplePointerProtocol *SPP;
extern EfiSimpleFileSystemProtocol *SFSP;
extern EfiDevicePathToTextProtocol *DPTTP;
extern EfiDevicePathFromTextProtocol *DPFTP;
extern EfiDevicePathUtilitiesProtocol *DPUP;
extern EfiGuid lip_guid;
extern EfiGuid dpp_guid;
extern EfiGuid sfsp_guid;

void efi_init(EfiSystemTable *SystemTable);

