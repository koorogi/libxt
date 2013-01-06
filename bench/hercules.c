#include <string.h>
#include <stdio.h>

#include <video/hercules.h>

#include "bench.h"

const Benchmark bench_hercules_vsync = {
    { "hercules_vsync", "Wait for vertical sync" },
    NULL,
    xt_hercules_wait_vsync,
    NULL,
};

static void setmode_graphics(void) {
    xt_hercules_mode_set(XtHerculesMode_Graphics);
    xt_hercules_fill(XT_HERCULES_FRAMEBUFFER0, 0);
}

static void setmode_text(void) {
    xt_hercules_mode_set(XtHerculesMode_Text);
}

/* benchmarks for different ways to clear the screen */

static void clear_libxt(void) {
    xt_hercules_fill(XT_HERCULES_FRAMEBUFFER0, 0);
}

static void clear_memset(void) {
    _fmemset(XT_HERCULES_FRAMEBUFFER0, 0, 0x8000);
}

static void clear_memset2(void) {
    for (uint16_t offset = 0; offset < 0x8000; offset += 0x2000) {
        _fmemset(XT_HERCULES_FRAMEBUFFER0 + offset, 0, 7830);
    }
}

void hercules_fillscreen_asm(XtHerculesFb fb, uint8_t fill);

static void clear_asm(void) {
    hercules_fillscreen_asm(XT_HERCULES_FRAMEBUFFER0, 0);
}

const Benchmark bench_hercules_clear = {
    { "hercules_clear", "Clear display (libxt method)" },
    setmode_graphics,
    clear_libxt,
    setmode_text,
};

const Benchmark bench_hercules_clear2 = {
    { "hercules_clear2", "Clear display (simple memset)" },
    setmode_graphics,
    clear_memset,
    setmode_text,
};

const Benchmark bench_hercules_clear3 = {
    { "hercules_clear3", "Clear display (smarter memset)" },
    setmode_graphics,
    clear_memset2,
    setmode_text,
};

const Benchmark bench_hercules_clear4 = {
    { "hercules_clear4", "Clear display (assembly)" },
    setmode_graphics,
    clear_asm,
    setmode_text,
};

/* horizontal lines */

static void hlines_short(void) {
    int y = 0;
    for (int offset = 0; offset < 8; offset++) {
        for (int len = 1; len < 16 - offset; len++) {
            for (int i = 0; i < 640; i += 128) {
                xt_hercules_line_horiz(XT_HERCULES_FRAMEBUFFER0, i + offset, i + offset + len - 1, y);
            }
            y++;
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

