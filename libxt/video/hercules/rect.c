#include <inttypes.h>
#include <string.h>

#include <video/hercules.h>

void xt_hercules_fill(XtHerculesFb buf, uint8_t fill) {
    XtHerculesFb16 buf16 = (XtHerculesFb16) buf;
    uint16_t      fill16 = fill | (fill << 8);

    for (int linemod4 = 0; linemod4 < 4; linemod4++) {
        XtHerculesFb16 line = buf16;
        for (int i = 0; i < (XT_HERCULES_GRAPHICS_ROWS >> 2) * (XT_HERCULES_GRAPHICS_COLS >> 4); i++) {
            *line++ = fill16;
        }
        buf16 += 0x1000;
    }
}

