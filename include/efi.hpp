#include "common.hpp"

#pragma once

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
    unsigned int Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
};

struct EfiDevicePathProtocol {
    unsigned char Type;
    unsigned char SubType;
    unsigned char Length[2];
};

struct EfiSimpleTextOutputProtocol {
  ull _buf;
  ull (*OutputString)(EfiSimpleTextOutputProtocol *This, const wchar_t *String);
  ull _buf2[4];
  ull (*ClearScreen)(EfiSimpleTextOutputProtocol *This);
};

struct EfiSimpleTextInputProtocol {
  ull _buf;
  ull (*ReadKeyStroke)(EfiSimpleTextInputProtocol *This, EfiInputKey *Key);
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
    ull PhysicalStart;
    ull VirtualStart;
    ull NumberOfPages;
    ull Attribute;
};

struct EfiBootServices {
    char _buf1[24];

    // Task Priority Services
    ull _buf2[2];
    
    // Memory Services
    ull (*AllocatePages)(EfiAllocateType Type, EfiMemoryType MemoryType, ull Pages, ull *PhysicalAddress);
    ull (*FreePages) (ull PhysicalAddress, ull Pages);
    ull (*GetMemoryMap)(ull *MemoryMapsize, EfiMemoryDescriptor *MemoryMap, ull *MapKey, ull *DescriptorSize, unsigned int *DescriptorVersion);
    ull (*AllocatePool)(EfiMemoryType PoolType, ull Size, void **Buffer);
    ull (*FreePool)(void *Buffer);

    // Event and Timer Services
    ull (*CreateEvent)(
            unsigned int Type,
            ull NotifyTpl,
            void (*NotifyFunction)(void *Event, void *Context),
            void *NotifyContext,
            void *Event);
    ull (*SetTimer)(void *Event, EfiTimerDelay Type, ull TriggerTime);
    ull (*WaitForEvent) (ull NumberOfEvents, void **Event, ull *Index);
    ull _buf4_2[3];

    // Protorcol Handler Services
    ull (*InstallProtocolInterface)();
    ull (*ReintallProtocolInterface)();
    ull (*UninstallProtocolInterface)();
    ull (*HandleProtocol)(void* Handle, EfiGuid *guid, void **Interface);
    void* Reserved;
    ull (*RegisterProtocolNotify)();
    ull (*LocateHandle)();
    ull (*LocateDevicePath)();
    ull (*InstallConfigurationTable)();

    // Image Services
    ull (*LoadImage)(
            unsigned char BootPolicy,
            void *ParentImageHandle,
            EfiDevicePathProtocol *DevicePath,
            void *SourceBuffer,
            ull SourceSize,
            void **ImageHandle);
    ull (*StartImage)(
            void *ImageHandle,
            ull *ExitDataSize,
            unsigned short **ExitData);
    ull (*Exit)(void *ImageHandle, ull ExitStatus, ull ExitDataSize, wchar_t *ExitData);;
    ull (*UnloadImage)(void *ImageHandle);
    ull (*ExitBootServices)(void *ImageHandle, ull MapKey);

    // Miscellaneous Services
    ull _buf7[2];
    ull (*SetWatchdogTimer) (ull Timeout, ull WatchdogCode, ull DataSize, wchar_t *WatchdogData);

    // DriverSupport Services
    ull _buf8[2];

    // Open and Close Protocol Services
    ull (*OpenProtocol) (
            void *Handle,
            EfiGuid *Protocol,
            void **Interface,
            void *AgentHandle,
            void *ControllerHandle,
            unsigned int Attributes
            );
    ull _buf9[2];

    // Library Services
    ull _buf10[2];
    ull (*LocateProtocol) (EfiGuid *Protocol, void *Registration, void **Interface);
    ull _buf10_2[2];

    // 32-bit CRC Servies
    ull _buf11;

    // Miscellaneous Services
    ull _buf12[3];
};

struct EfiGraphicsOutputBitPixel {
    unsigned char Blue;
    unsigned char Green;
    unsigned char Red;
    unsigned char Reserved;
};

struct EfiGraphicsOutputModeInfo {
    unsigned int Version;
    unsigned int HorizontalResolution;
    unsigned int VerticalResolution;
    enum EfiGraphicsPixelFormat {
        PixelRedGreenBlueReserved8BitPerColor,
        PixelBlueGreenRedReserved8BitPerColor,
        PixelBitMask,
        PixelBltOnly,
        PixelFormatMax
    } PixelFormat;
};

struct EfiGraphicsOutputPtorocolMode {
    unsigned int MaxMode;
    unsigned int Mode;
    EfiGraphicsOutputModeInfo * Info;
    ull SizeOfInfo;
    ull FrameBufferBase;
};

struct EfiGraphicsOutputPtorocol {
    ull _buf[3];
    EfiGraphicsOutputPtorocolMode *Mode;
};

struct EfiSimplePointerState{
    int RelativeMovementX;
    int RelativeMovementY;
    int RelativeMovementZ;
    unsigned char LeftButton;
    unsigned char RightButton;
};

struct EfiSimplePointerProtocol{
    ull (*Reset) (EfiSimplePointerProtocol *This, unsigned char ExtendedVerification);
    ull (*GetState) (EfiSimplePointerProtocol *This, EfiSimplePointerState *State);
    void *WaitForInput;
};

struct EfiTime {
    unsigned short year;
    unsigned char Month;
    unsigned char Day;
    unsigned char Hour;
    unsigned char Minute;
    unsigned char Second;
    unsigned char Pad1;
    unsigned long Nanosecond;
    short Timezone;
    unsigned char Daylight;
    unsigned char Pad2;
};

struct EfiFileInfo {
    //unsigned char _buf[80];
    ull size;
    ull FileSize;
    ull PhysicalSize;
    EfiTime CreateTime;
    EfiTime LastAccessTime;
    EfiTime ModificationTime;
    ull Attribute;
    wchar_t FileName[];
};

struct EfiFileProtocol {
    ull Revision;
    ull (*Open)(EfiFileProtocol *This, EfiFileProtocol **NewHandle, const wchar_t *FileName, ull OpenMode, ull Attributes);
    ull (*Close)(EfiFileProtocol *This);
    ull (*Delete)();
    ull (*Read)(EfiFileProtocol *This, ull *BufferSize, void *Buffer);
    ull (*Write)(EfiFileProtocol *This, ull *BufferSize, void *Buffer);
    ull (*GetPosition)();
    ull (*SetPosition)();
    ull (*GetInfo)(EfiFileProtocol *This, EfiGuid *InformationType, ull *BufferSize, void *Buffer);
    ull (*SetInfo)();
    ull (*Flush)(EfiFileProtocol *This);
    // Extra functions (if revision 2)
};

struct EfiSimpleFileSystemProtocol {
    ull Revision;
    ull (*OpenVolume)(EfiSimpleFileSystemProtocol *This, EfiFileProtocol **Root);
};

struct EfiSystemTable {
    char _buf[44];
    EfiSimpleTextInputProtocol *ConIn;
    ull _buf2;
    EfiSimpleTextOutputProtocol *ConOut;
    ull _buf3[2];
    EfiRuntimeServices *RuntimeServices;
    EfiBootServices *BootServices;
};

struct EfiLoadedImageProtocol {
    unsigned int Revision;
    void *ParentHandle;
    EfiSystemTable *SystemTable;
    // Source location of the image
    void *DeviceHandle;
    EfiDevicePathProtocol *FilePath;
    void *Reserved;
    // Image's load options
    unsigned int LoadOptionSize;
    void *LoadOptions;
    // Location where image was loaded
    void *ImageBase;
    ull ImageSize;
    EfiMemoryType ImageCodeType;
    EfiMemoryType ImageDataType;
    ull (*Unload)(void *ImageHandle);
};

struct EfiDevicePathToTextProtocol {
    ull _buf;
    wchar_t *(*ConvertDevicePathToText)(const EfiDevicePathProtocol *DeviceNode, unsigned char DisplayOnly, unsigned char AllowShortcuts);
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

