#include <string.h>
#include <stdio.h>
#include <i86.h>

#include <video/hercules.h>

#include "tests.h"
#include "helpers.h"

const Benchmark bench_hercules_vsync = {
    { "hercules_vsync", "Wait for vertical sync" },
    NULL,
    xt_hercules_wait_vsync,
    NULL,
};

/* benchmarks for different ways to clear the screen */

static void clear_libxt(void) {
    xt_hercules_fill(FP_SEG(XT_HERCULES_FRAMEBUFFER0), 0);
}

static void clear_memset(void) {
    _fmemset(XT_HERCULES_FRAMEBUFFER0, 0, 0x8000);
}

static void clear_memset2(void) {
    for (uint16_t offset = 0; offset < 0x8000; offset += 0x2000) {
        _fmemset(XT_HERCULES_FRAMEBUFFER0 + offset, 0, 7830);
    }
}

void hercules_fillscreen_asm(uint16_t bufseg, uint8_t fill);

static void clear_asm(void) {
    hercules_fillscreen_asm(FP_SEG(XT_HERCULES_FRAMEBUFFER0), 0);
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

