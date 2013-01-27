#include <inttypes.h>
#include <string.h>
#include <i86.h>

#include <video/hercules.h>
#include <util.h>

/* assumes 0 < x1 < x2 <= HGC_GRAPHICS_COLS, 0 <= y < HGC_GRAPHICS_ROWS */
void xtintl_hercules_line_horiz(uint16_t bufseg, int y, int x1, int x2);

static void line_horiz(uint16_t bufseg, int y, int x1, int x2) {
    xtintl_hercules_line_horiz(bufseg, y, x1, x2);
}

void xt_hercules_line_horiz(uint16_t bufseg, int x1, int x2, int y) {
    if (y < 0 || y >= XT_HERCULES_GRAPHICS_ROWS) {
        return;
    }

    if (x1 > x2) {
        XT_SWAP(int, x1, x2);
    }
    x1 = XT_CLIP(x1,  0, XT_HERCULES_GRAPHICS_COLS);
    x2 = XT_CLIP(x2, -1, XT_HERCULES_GRAPHICS_COLS - 1);
    if (x1 <= x2) {
        xtintl_hercules_line_horiz(bufseg, y, x1, x2);
    }
}

static void line_vert(uint16_t bufseg, int x, int y1, int y2) {
    XtHerculesFb buf = MK_FP(bufseg, x >> 3);
    uint8_t      bit = 0x80 >> (x & 7);

    for (; y1 <= y2; y1++) {
        buf[xt_hercules_fb_row_offset[y1]] |= bit;
    }
}

void xt_hercules_line_vert(uint16_t bufseg, int x, int y1, int y2) {
    if (x < 0 || x >= XT_HERCULES_GRAPHICS_COLS) {
        return;
    }

    if (y1 > y2) {
        XT_SWAP(int, y1, y2);
    }
    y1 = XT_CLIP(y1,  0, XT_HERCULES_GRAPHICS_ROWS);
    y2 = XT_CLIP(y2, -1, XT_HERCULES_GRAPHICS_ROWS - 1);
    if (y1 <= y2) {
        line_vert(bufseg, x, y1, y2);
    }
}

void xt_hercules_line(uint16_t bufseg, int x1, int y1, int x2, int y2) {
    if (x1 == x2) {
        xt_hercules_line_vert(bufseg, x1, y1, y2);
    } else if (y1 == y2){
        xt_hercules_line_horiz(bufseg, x1, x2, y1);
    } else {
        void (*draw)(uint16_t, int, int, int);

        int deltax = XT_ABS(x2 - x1);
        int deltay = XT_ABS(y2 - y1);
        if (deltay >= deltax) {
            draw = line_vert;
            XT_SWAP(int, x1, y1);
            XT_SWAP(int, x2, y2);
            XT_SWAP(int, deltax, deltay);
        } else {
            // HACK: taking the address of the assembly function directly here
            // doesn't work correctly, but taking the address of a thin wrapper does.
            draw = line_horiz;
        }
        if (x1 > x2) {
            XT_SWAP(int, x1, x2);
            XT_SWAP(int, y1, y2);
        }

        int ystep = XT_SIGN(y2 - y1);
        int error = deltax >> 1;

        while (x1 <= x2) {
            int startx = x1;

            for (; x1 < x2 && error >= deltay; x1++) {
                error -= deltay;
            }

            draw(bufseg, y1, startx, x1++);
            error += deltax - deltay;
            y1    += ystep;
        }
    }
}

