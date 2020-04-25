#include "common.hpp"
#include "shell.hpp"

#define MAX_COMMAND_LEN 100

void shell(void){
    wchar_t com[MAX_COMMAND_LEN];

    while(TRUE){
        puts(L"poiOS> ");
        if(gets(com, MAX_COMMAND_LEN) <= 0)
            continue;

        if(!strcmp(L"hello", com))
            puts(L"Hello UEFI!\r\n");
        else
            puts(L"Command not found\r\n");
    }
}
