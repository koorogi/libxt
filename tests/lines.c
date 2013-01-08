#include <conio.h>

#include <video/hercules.h>

#include "tests.h"
#include "helpers.h"

static void hlines_short(void) {
    for (int width = 1; width <= 16; width++) {
        for (int y = 0; y < XT_HERCULES_GRAPHICS_ROWS; y++) {
            int startx = 32 * width + y - 104;
            xt_hercules_line_horiz(XT_HERCULES_FRAMEBUFFER0, startx, startx + width - 1, y);
        }
    }
}

static void hlines_long(void) {
    int y = 0;
    for (int offset = 0; offset < 8; offset++) {
        for (int len = 16; len < 640; len += 16) {
            xt_hercules_line_horiz(XT_HERCULES_FRAMEBUFFER0, offset, offset + len - 1, y++);
        }
    }
}

const Benchmark bench_hercules_hlines_short = {
    { "hercules_hlines_short", "Draw short horizontal lines" },
    setmode_graphics,
    hlines_short,
    setmode_text,
};

const Benchmark bench_hercules_hlines_long = {
    { "hercules_hlines_long", "Draw long horizontal lines" },
    setmode_graphics,
    hlines_long,
    setmode_text,
};

static void hlines(void) {
    setmode_graphics();
    hlines_short();
    getch();
    setmode_text();
}

const TestCase test_hlines = {
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

const TestCase test_vlines = {
    { "vlines", "Draw vertical lines" },
    vlines,
};

