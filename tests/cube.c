#include <conio.h>

#include <video/hercules.h>
#include <math/fixedpoint.h>
#include <math/quaternion.h>

#include "tests.h"
#include "helpers.h"

#define FRAMES      40
#define FRAMES2     10  /* # frames per benchmark iteration */
#define DIM         40  /* must be small enough to avoid overflow after rotation is applied */

static const XtVector3 points[] = {
    { XT_FIXED8(-DIM), XT_FIXED8(-DIM), XT_FIXED8(-DIM) },
    { XT_FIXED8( DIM), XT_FIXED8(-DIM), XT_FIXED8(-DIM) },
    { XT_FIXED8( DIM), XT_FIXED8( DIM), XT_FIXED8(-DIM) },
    { XT_FIXED8(-DIM), XT_FIXED8( DIM), XT_FIXED8(-DIM) },

    { XT_FIXED8(-DIM), XT_FIXED8(-DIM), XT_FIXED8( DIM) },
    { XT_FIXED8( DIM), XT_FIXED8(-DIM), XT_FIXED8( DIM) },
    { XT_FIXED8( DIM), XT_FIXED8( DIM), XT_FIXED8( DIM) },
    { XT_FIXED8(-DIM), XT_FIXED8( DIM), XT_FIXED8( DIM) },
};

static const uint16_t framebufseg[2] = {
    FP_SEG(XT_HERCULES_FRAMEBUFFER0), FP_SEG(XT_HERCULES_FRAMEBUFFER1)
};

static inline void draw_line(uint16_t bufseg, XtVector3 from, XtVector3 to) {
    xt_hercules_line(bufseg,
            360 + 2*xt_fixed_8to16(from.x), 174 + 2*xt_fixed_8to16(from.y),
            360 + 2*xt_fixed_8to16(  to.x), 174 + 2*xt_fixed_8to16(  to.y));
}

static void draw_cube(uint16_t bufseg, const XtVector3 *points) {
    for (int i = 0; i < 4; i++) {
        int nexti = (i + 1) & 3;
        draw_line(bufseg, points[  i], points[  nexti]);
        draw_line(bufseg, points[4+i], points[4+nexti]);
        draw_line(bufseg, points[  i], points[4+i]);
    }
}

static void draw_frame(uint16_t bufseg, XtFixed8 angle, XtVector3 axis) {
    XtQuaternion rot;
    XtVector3    rotpoints[8];

    xt_hercules_fill(bufseg, 0);

    rot = xt_quat_rotate_make(angle, axis);
    for (int i = 0; i < 8; i ++) {
        rotpoints[i] = xt_quat_rotate_vect(rot, points[i]);
    }

    draw_cube(bufseg, rotpoints);
}

static void cube_tester(void) {
    XtFixed8  angle = 0;
    XtVector3 axis  = { XT_FIXED8(0), XT_FIXED8(1), XT_FIXED8(1) };

    setmode_graphics();

    int fb = xt_hercules_page_get();
    while (1) {
        for (; angle < 2 * XT_FIXED8_PI; angle += XT_FIXED8_PI / FRAMES) {
            fb ^= 1;
            draw_frame(framebufseg[fb], angle, axis);

            xt_hercules_wait_vsync();
            xt_hercules_page_swap();

            if (kbhit()) {
                getch();
                goto done;
            }
        }
        angle -= 2 * XT_FIXED8_PI;
    }

done:
    setmode_text();
}

static void cube_bencher(void) {
    XtVector3 axis = { XT_FIXED8(0), XT_FIXED8(1), XT_FIXED8(1) };

    int fb = xt_hercules_page_get();
    for (XtFixed8 angle = 0; angle < 2 * XT_FIXED8_PI; angle += XT_FIXED8_PI / FRAMES2) {
        fb ^= 1;
        draw_frame(framebufseg[fb], angle, axis);
        xt_hercules_page_swap();
    }
}

const TestCase test_cube = {
    { "cube", "Draw a spinning cube" },
    cube_tester,
};

const Benchmark bench_hercules_cube = {
    { "cube", "Draw a spinning cube" },
    setmode_graphics,
    cube_bencher,
    setmode_text,
};

