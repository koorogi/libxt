#include <conio.h>

#include <video/hercules.h>

#include "hercules.h"

static void hlines(void) {
    XtHerculesFb framebuf = XT_HERCULES_FRAMEBUFFER0;

    xt_hercules_mode_set(XtHerculesMode_Graphics);
    xt_hercules_fill(framebuf, 0);

    for (int width = 1; width <= 16; width++) {
        for (int y = 0; y < XT_HERCULES_GRAPHICS_ROWS; y++) {
            int startx = 32 * width + y - 104;
            xt_hercules_line_horiz(framebuf, startx, startx + width - 1, y);
        }
    }

    getch();
    xt_hercules_mode_set(XtHerculesMode_Text);
}

const HerculesCommand cmd_hlines = {
    { "hlines", "Draw horizontal lines" },
    hlines,
};

static void vlines(void) {
    XtHerculesFb framebuf = XT_HERCULES_FRAMEBUFFER0;

    xt_hercules_mode_set(XtHerculesMode_Graphics);
    xt_hercules_fill(framebuf, 0);

    for (int i = 0; i < 87; i++) {
        xt_hercules_line_vert(framebuf, 8 * (i + 1), i, 348 - 86 + i);
    }

    getch();
    xt_hercules_mode_set(XtHerculesMode_Text);
}

const HerculesCommand cmd_vlines = {
    { "vlines", "Draw vertical lines" },
    vlines,
};

