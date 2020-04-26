#include "efi.hpp"
#include "common.hpp"
#include "shell.hpp"
#include "graphics.hpp"
#include "gui.hpp"

#define MAX_COMMAND_LEN 100

void resolution(void){
    unsigned int hr = GOP->Mode->Info->HorizontalResolution;
    unsigned int vr = GOP->Mode->Info->VerticalResolution;
    wchar_t buf[100];
    strcat(buf, 100, 0, L"hr: 0x");
    intToStr(buf, 100, strlen(buf), hr);
    strcat(buf, 100, strlen(buf), L"\r\n");
    strcat(buf, 100, strlen(buf), L"vr: 0x");
    intToStr(buf, 100, strlen(buf), vr);
    unsigned int result = strcat(buf, 100, strlen(buf), L"\r\n");
    if(result) puts(buf);
    else puts(L"buf is too small!");
}

void pstat(void){
    ull status;
    EfiSimplePointerState s;
    ull wait_index;

    SPP->Reset(SPP, FALSE);

    while(1){
        ST->BootServices->WaitForEvent(1, &(SPP->WaitForInput), &wait_index);
        status = SPP->GetState(SPP, &s);
        if(!status){
            puth(s.RelativeMovementX, 8);
            puts(L" ");
            puth(s.RelativeMovementY, 8);
            puts(L" ");
            puth(s.RelativeMovementZ, 8);
            puts(L" ");
            puth(s.LeftButton, 1);
            puts(L" ");
            puth(s.RightButton, 1);
            puts(L"\r\n");
        }
    }
}

void shell(void){
    wchar_t com[MAX_COMMAND_LEN];
    Rect rect = {.x = 10, .y = 10, .w = 100, .h = 200};

    while(TRUE){
        puts(L"poiOS> ");
        if(gets(com, MAX_COMMAND_LEN) <= 0)
            continue;

        if(!strcmp(L"hello", com))
            puts(L"Hello UEFI!\r\n");
        else if(!strcmp(L"rect", com))
            draw_rect(rect, white);
        else if(!strcmp(L"clear", com))
            ClearScreen();
        else if(!strcmp(L"gui", com))
            gui();
        else if(!strcmp(L"pstat", com))
            pstat();
        else if(!strcmp(L"resolution", com))
            resolution();
        else if(!strcmp(L"exit", com))
            break;
        else
            puts(L"Command not found\r\n");
    }
}
