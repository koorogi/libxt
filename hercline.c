#include <inttypes.h>
#include <conio.h>

#include <video/hercules.h>

int main() {
    XtHerculesFb framebuf = XT_HERCULES_FRAMEBUFFER0;

    xt_hercules_mode_set(XtHerculesMode_Graphics);
    xt_hercules_fill(framebuf, 0);

    /* draw various horizontal lines */
    for (int width = 1; width <= 16; width++) {
        for (int y = 0; y < XT_HERCULES_GRAPHICS_ROWS; y++) {
            int startx = 32 * width + y - 104;
            xt_hercules_line_horiz(framebuf, startx, startx + width, y);
        }
    }

    getch();

    xt_hercules_mode_set(XtHerculesMode_Text);
    return 0;
}

