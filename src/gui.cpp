#include "efi.hpp"
#include "common.hpp"
#include "file.hpp"
#include "graphics.hpp"
#include "shell.hpp"
#include "gui.hpp"

#define WIDTH_PER_CH 8
#define HEIGHT_PER_CH 20

EfiGraphicsOutputBitPixel cursor_tmp = {0, 0, 0, 0};
int cursor_old_x;
int cursor_old_y;

void draw_cursor(int x, int y){
    draw_pixel(x, y, white);
}

void save_cursor_area(int x, int y){
    cursor_tmp = get_pixel(x, y);
    cursor_tmp.Reserved = 0xff;
}

void load_cursor_area(int x, int y){
    draw_pixel(x, y, cursor_tmp);
}

void put_cursor(int x, int y){
    if(cursor_tmp.Reserved)
        load_cursor_area(cursor_old_x, cursor_old_y);

    save_cursor_area(x, y);

    draw_cursor(x, y);
    cursor_old_x = x;
    cursor_old_y = y;
}

int ls_gui(void){
    int file_num;
    Rect t;
    int idx;
    ClearScreen();
    ClearScreen();

    file_num = ls();
    t.x = 0;
    t.y = 0;
    t.w = (MAX_FILE_NAME_LEN - 1) * WIDTH_PER_CH;
    t.h = HEIGHT_PER_CH;
    for(idx = 0; idx < file_num;idx++){
        file_list[idx].rect.x = t.x;
        file_list[idx].rect.y = t.y;
        file_list[idx].rect.w = t.w;
        file_list[idx].rect.h = t.h;
        draw_rect(file_list[idx].rect, white);
        t.x += file_list[idx].rect.w + WIDTH_PER_CH;

        file_list[idx].is_highlight = FALSE;
    }
    return file_num;
}

void gui(void){
    ull status;
    EfiSimplePointerState s;
    int px = 0, py = 0;
    ull wait_index;
    int file_num;
    int idx;
    SPP->Reset(SPP, FALSE);

    // draw rect as a file
    file_num = ls_gui();

    while(TRUE){
        ST->BootServices->WaitForEvent(1, &(SPP->WaitForInput), &wait_index);
        status = SPP->GetState(SPP, &s);
        if(!status){
            // update mouse cursor
            px += s.RelativeMovementX >> 13;
            if(px < 0)
                px = 0;
            else if(GOP->Mode->Info->HorizontalResolution <= (unsigned int)px)
                px = GOP->Mode->Info->HorizontalResolution -1;
            py += s.RelativeMovementY >> 13;
            if(py < 0)
                py = 0;
            else if(GOP->Mode->Info->VerticalResolution <= (unsigned int)py)
                py = GOP->Mode->Info->VerticalResolution - 1;

            // draw mouse cursor
            put_cursor(px, py);

            // update file icon
            for(idx = 0; idx < file_num;idx++){
                if(is_in_rect(px, py, file_list[idx].rect)){
                    if(!file_list[idx].is_highlight){
                        draw_rect(file_list[idx].rect, yellow);
                        file_list[idx].is_highlight = TRUE;
                    }
                }else {
                    if(file_list[idx].is_highlight){
                        draw_rect(file_list[idx].rect, white);
                        file_list[idx].is_highlight = FALSE;
                    }
                }
            }
        }
    }
}
