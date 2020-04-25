#include "efi.hpp"
#include "common.hpp"
#include "graphics.hpp"
#include "gui.hpp"

void gui(void){
    Rect r = {10, 10, 20, 20};
    ClearScreen();

    draw_rect(r, white);

    while(TRUE);
}
