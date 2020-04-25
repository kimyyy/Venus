#include "common.hpp"

#pragma once

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

struct EfiSimpleTextOutputProtocol {
  ull _buf;
  ull (*OutputString)(EfiSimpleTextOutputProtocol *This, wchar_t *String);
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
    ull _buf6[5];

    // Miscellaneous Services
    ull _buf7[2];
    ull (*SetWatchdogTimer) (ull Timeout, ull WatchdogCode, ull DataSize, wchar_t *WatchdogData);

    // DriverSupport Services
    ull _buf8[2];

    // Open and Close Protocol Services
    ull _buf9[3];

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

struct EfiSystemTable {
    char _buf[44];
    EfiSimpleTextInputProtocol *ConIn;
    ull _buf2;
    EfiSimpleTextOutputProtocol *ConOut;
    ull _buf3[3];
    EfiBootServices *BootServices;
};

extern EfiSystemTable *ST;
extern EfiGraphicsOutputPtorocol *GOP;
extern EfiSimplePointerProtocol *SPP;

void efi_init(EfiSystemTable *SystemTable);

