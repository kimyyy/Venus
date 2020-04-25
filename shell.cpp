#include "common.hpp"
#include "shell.hpp"
#include "graphics.hpp"

#define MAX_COMMAND_LEN 100

void shell(void){
    wchar_t com[MAX_COMMAND_LEN];
    Rect rect = {.x = 10, .y = 10, .w = 100, .h = 10};

    while(TRUE){
        puts(L"poiOS> ");
        if(gets(com, MAX_COMMAND_LEN) <= 0)
            continue;

        if(!strcmp(L"hello", com))
            puts(L"Hello UEFI!\r\n");
        else if(!strcmp(L"rect", com))
            draw_rect(rect, white);
        else if(!strcmp(L"clear", com))
            clear();
        else if(!strcmp(L"exit", com))
            break;
        else
            puts(L"Command not found\r\n");
    }
}
