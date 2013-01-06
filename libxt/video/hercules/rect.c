#include <inttypes.h>
#include <string.h>

#include <video/hercules.h>

void xt_hercules_fill(XtHerculesFb buf, uint8_t fill) {
    for (int linemod4 = 0; linemod4 < 4; linemod4++) {
        _fmemset(buf, fill, (XT_HERCULES_GRAPHICS_ROWS >> 2) * (XT_HERCULES_GRAPHICS_COLS >> 3));
        buf += 0x2000;
    }
}

