#include "efi.hpp"
#include "common.hpp"
#include "file.hpp"
#include "shell.hpp"
#include "graphics.hpp"
#include "gui.hpp"

#define MAX_COMMAND_LEN 100


int ls(void){
    ull status;
    EfiFileProtocol *root;
    ull buf_size;
    wchar_t file_buf[MAX_FILE_BUF];
    EfiFileInfo *file_info;
    int index = 0;
    int file_num;
    
    status = SFSP->OpenVolume(SFSP, &root);
    assert(status, L"SFSP->OpenVolume");

    while(1) {
        buf_size = MAX_FILE_BUF;
        status = root->Read(root, &buf_size, (void *)file_buf);
        assert(status, L"root->Read");
        if(!buf_size)break;
        
        file_info = (EfiFileInfo *)file_buf;
        strncpy(file_list[index].name, file_info->FileName, MAX_FILE_NAME_LEN - 1);
        file_list[index].name[MAX_FILE_NAME_LEN - 1] = L'\0';
        puts(file_list[index].name);
        puts(L" ");

        index++;
    }
    puts(L"\r\n");
    file_num = index;

    root->Close(root);

    return file_num;
}

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

void frame(void){
    resolution();
    unsigned int hr = GOP->Mode->Info->HorizontalResolution;
    unsigned int vr = GOP->Mode->Info->VerticalResolution;
    Rect rect = {0, 0, hr, vr};
    draw_rect(rect, white);
}

void cat(const wchar_t *file_name){
    ull status;
    EfiFileProtocol *root;
    EfiFileProtocol *file;
    ull buf_size = MAX_FILE_BUF;
    wchar_t file_buf[MAX_FILE_BUF / 2];

    status = SFSP->OpenVolume(SFSP, &root);
    assert(status, L"SFSP->OpenVolume");

    status = root->Open(root, &file, file_name, EFI_FILE_MODE_READ, 0);
    assert(status, L"root->Open");

    status = file->Read(file, &buf_size, (void *)file_buf);
    assert(status, L"file->Read");

    puts(file_buf);

    file->Close(file);
    root->Close(root);
}

void edit(const wchar_t *file_name){
    ull status;
    EfiFileProtocol *root;
    EfiFileProtocol *file;
    ull buf_size = MAX_FILE_BUF;
    wchar_t file_buf[MAX_FILE_BUF /2 ];
    int i = 0;
    wchar_t ch;

    ClearScreen();
    while(TRUE){
        ch = getc();

        if(ch == SC_ESC){
            break;
        }

        putc(ch);
        file_buf[i++] = ch;

        if(ch == L'\r'){
            putc(L'\n');
            file_buf[i++] = L'\n';
        }
    }
    file_buf[i] = L'\0';

    status = SFSP->OpenVolume(SFSP, &root);
    assert(status, L"SFSP->OpenVolume");

    status = root->Open(root, &file, file_name, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0);
    assert(status, L"root->Open");

    status = file->Write(file, &buf_size, (void *)file_buf);
    assert(status, L"file->Write");

    file->Flush(file);
    file->Close(file);
    root->Close(root);
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
        //puts(com);

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
        else if(!strcmp(L"ls", com))
            ls();
        else if(!strcmp(L"cat",com))
            cat(L"abc");
        else if(!strcmp(L"edit", com))
            edit(L"abc");
        else if(!strcmp(L"frame", com))
            frame();
        else if(!strcmp(L"exit", com))
            break;
        else{
            puts(L"Command not found: ");
            puts(com);
            puts(L"\r\n");
        }
    }
}
