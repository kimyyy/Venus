#pragma once

#include "graphics.hpp"

#define MAX_FILE_NAME_LEN 4
#define MAX_FILE_NUM 10
#define MAX_FILE_BUF 1024

struct File {
    Rect rect;
    unsigned char is_highlight;
    wchar_t name[MAX_FILE_NAME_LEN];
};

extern File file_list[MAX_FILE_NUM];
