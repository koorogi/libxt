#include <conio.h>

#include <video/hercules.h>

#include "tests.h"
#include "helpers.h"

static const XtHerculesFb framebuf[2] = {
    XT_HERCULES_FRAMEBUFFER0, XT_HERCULES_FRAMEBUFFER1
};

static void cube(void) {
    setmode_graphics();

    int fb = xt_hercules_page_get();
    while (1) {
        fb ^= 1;
        xt_hercules_fill(framebuf[fb], 0);

        xt_hercules_line(framebuf[fb], 280      , 94      , 280      , 94 + 160);
        xt_hercules_line(framebuf[fb], 280 + 160, 94      , 280 + 160, 94 + 160);
        xt_hercules_line(framebuf[fb], 280      , 94      , 280 + 160, 94      );
        xt_hercules_line(framebuf[fb], 280      , 94 + 160, 280 + 160, 94 + 160);

        xt_hercules_wait_vsync();
        xt_hercules_page_swap();

        if (kbhit()) {
            break;
        }
    }

    setmode_text();
}

const TestCase test_cube = {
    { "cube", "Draw a spinning cube (WIP)" },
    cube,
};
