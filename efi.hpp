#include "common.hpp"

#pragma once

#define EFI_FILE_MODE_READ 0x0000000000000001
#define EFI_FILE_MODE_WRITE 0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000

#define EFI_FILE_READ_ONLY 0x0000000000000001

#define EFI_SUCCESS	0
#define EFI_ERROR	0x8000000000000000
#define EFI_UNSUPPORTED	(EFI_ERROR | 3)

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL	0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL		0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL		0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER	0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER		0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE		0x00000020

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

struct EfiBootServices {
    char _buf1[24];

    // Task Priority Services
    ull _buf2[2];
    
    // Memory Services
    ull _buf3[5];

    // Event and Timer Services
    ull _buf4[2];
    ull (*WaitForEvent) (ull NumberOfEvents, void **Event, ull *Index);
    ull _buf4_2[3];

    // Protorcol Handler Services
    ull _buf5[9];

    // Image Services
    ull (*LoadImage)(
            unsigned char BootPolicy,
            void *ParentImageHandle,
            EfiDevicePathProtocol *DevicePath,
            void *SourceBuffer,
            ull SourceSize,
            void **ImageHandle);
    ull _buf6[4];

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

struct EfiFileInfo {
    unsigned char _buf[80];
    wchar_t FileName[];
};

struct EfiFileProtocol {
    ull _buf;
    ull (*Open)(EfiFileProtocol *This, EfiFileProtocol **NewHandle, const wchar_t *FileName, ull OpenMode, ull Attributes);
    ull (*Close)(EfiFileProtocol *This);
    ull _buf2;
    ull (*Read)(EfiFileProtocol *This, ull *BufferSize, void *Buffer);
    ull (*Write)(EfiFileProtocol *This, ull *BufferSize, void *Buffer);
    ull _buf3[4];
    ull (*Flush)(EfiFileProtocol *This);
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
    ull _buf3[3];
    EfiBootServices *BootServices;
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

void efi_init(EfiSystemTable *SystemTable);

