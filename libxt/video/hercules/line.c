#include <inttypes.h>
#include <string.h>

#include <video/hercules.h>
#include <util.h>

/* 0 < x1 < x2 <= HGC_GRAPHICS_COLS, 0 <= y < HGC_GRAPHICS_ROWS */
static void line_horiz(XtHerculesFb buf, int y, int x1, int x2) {
    XtHerculesFb row = buf + xt_hercules_fb_row_offset[y] + (x1 >> 3);

    int count = x2 - x1 + 1;
    int skip  = x1 & 7;
    if (skip) {
        int firstbyte = 8 - skip;
        if (count < firstbyte) {
            *row   |= (0xff & (0xff << (8 - count))) >> skip;
            return;
        } else {
            *row++ |= 0xff >> skip;
            count  -= firstbyte;
        }
    }

    int bytes = count >> 3;
    _fmemset(row, 0xff, bytes);
    row += bytes;

    count &= 7;
    if (count) {
        *row |= (0xff00 >> count) & 0xff;
    }
}

void xt_hercules_line_horiz(XtHerculesFb buf, int x1, int x2, int y) {
    if (y < 0 || y >= XT_HERCULES_GRAPHICS_ROWS) {
        return;
    }

    if (x1 > x2) {
        XT_SWAP(int, x1, x2);
    }
    x1 = XT_CLIP(x1,  0, XT_HERCULES_GRAPHICS_COLS);
    x2 = XT_CLIP(x2, -1, XT_HERCULES_GRAPHICS_COLS - 1);
    if (x1 <= x2) {
        line_horiz(buf, y, x1, x2);
    }
}

static void line_vert(XtHerculesFb buf, int x, int y1, int y2) {
    uint8_t bit = 0x80 >> (x & 7);
    buf += x >> 3;

    for (; y1 <= y2; y1++) {
        buf[xt_hercules_fb_row_offset[y1]] |= bit;
    }
}

void xt_hercules_line_vert(XtHerculesFb buf, int x, int y1, int y2) {
    if (x < 0 || x >= XT_HERCULES_GRAPHICS_COLS) {
        return;
    }

    if (y1 > y2) {
        XT_SWAP(int, y1, y2);
    }
    y1 = XT_CLIP(y1,  0, XT_HERCULES_GRAPHICS_ROWS);
    y2 = XT_CLIP(y2, -1, XT_HERCULES_GRAPHICS_ROWS - 1);
    if (y1 <= y2) {
        line_vert(buf, x, y1, y2);
    }
}

