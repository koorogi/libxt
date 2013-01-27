#include <conio.h>
#include <i86.h>

#include <video/hercules.h>

#include "tests.h"
#include "helpers.h"

static void hlines_short(void) {
    for (int width = 1; width <= 16; width++) {
        for (int y = 0; y < XT_HERCULES_GRAPHICS_ROWS; y++) {
            int startx = 32 * width + y - 104;
            xt_hercules_line_horiz(FP_SEG(XT_HERCULES_FRAMEBUFFER0), startx, startx + width - 1, y);
        }
    }
}

static void hlines_long(void) {
    int y = 0;
    for (int offset = 0; offset < 8; offset++) {
        for (int len = 16; len < 640; len += 16) {
            xt_hercules_line_horiz(FP_SEG(XT_HERCULES_FRAMEBUFFER0), offset, offset + len - 1, y++);
        }
    }
}

static void angled_lines(void) {
    static struct { int x, y; } points[] = {
        { 32, 0 }, { 30, 10 }, { 26, 19 }, { 19, 26 }, { 10, 30 }
    };

    for (int centerx = 48; centerx <= 720 - 48; centerx += 78) {
        for (int centery = 48; centery <= 348 - 48; centery += 84) {
            for (int i = 0; i < 5; i++) {
                int dx = points[i].x;
                int dy = points[i].y;
                xt_hercules_line(FP_SEG(XT_HERCULES_FRAMEBUFFER0), centerx, centery, centerx + dx, centery + dy);
                xt_hercules_line(FP_SEG(XT_HERCULES_FRAMEBUFFER0), centerx, centery, centerx + dy, centery - dx);
                xt_hercules_line(FP_SEG(XT_HERCULES_FRAMEBUFFER0), centerx, centery, centerx - dx, centery - dy);
                xt_hercules_line(FP_SEG(XT_HERCULES_FRAMEBUFFER0), centerx, centery, centerx - dy, centery + dx);
            }
        }
    }
}

const Benchmark bench_hercules_hlines_short = {
    { "hlines", "Draw short horizontal lines" },
    setmode_graphics,
    hlines_short,
    setmode_text,
};

const Benchmark bench_hercules_hlines_long = {
    { "hlines2", "Draw long horizontal lines" },
    setmode_graphics,
    hlines_long,
    setmode_text,
};

const Benchmark bench_hercules_alines = {
    { "alines", "Draw angled lines" },
    setmode_graphics,
    angled_lines,
    setmode_text,
};

#define TESTCASE(name,func)             \
    static void name ## _tester(void) { \
        setmode_graphics();             \
        func();                         \
        getch();                        \
        setmode_text();                 \
    }

TESTCASE(hlines, hlines_short)
TESTCASE(alines, angled_lines)

const TestCase test_alines = {
    { "alines", "Draw angled lines" },
    alines_tester,
};

const TestCase test_hlines = {
    { "hlines", "Draw horizontal lines" },
    hlines_tester,
};

static void vlines(void) {
    uint16_t bufseg = FP_SEG(XT_HERCULES_FRAMEBUFFER0);

    xt_hercules_mode_set(XtHerculesMode_Graphics);
    xt_hercules_fill(bufseg, 0);

    for (int i = 0; i < 87; i++) {
        xt_hercules_line_vert(bufseg, 8 * (i + 1), i, 348 - 86 + i);
    }

    getch();
    xt_hercules_mode_set(XtHerculesMode_Text);
}

const TestCase test_vlines = {
    { "vlines", "Draw vertical lines" },
    vlines,
};

