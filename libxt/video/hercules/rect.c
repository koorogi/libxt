#include <inttypes.h>
#include <string.h>
#include <i86.h>

#include <video/hercules.h>

void xt_hercules_fill(uint16_t bufseg, uint8_t fill) {
    uint16_t offset = 0;
    for (int linemod4 = 0; linemod4 < 4; linemod4++) {
        _fmemset(MK_FP(bufseg, offset), fill, (XT_HERCULES_GRAPHICS_ROWS >> 2) * (XT_HERCULES_GRAPHICS_COLS >> 3));
        offset += 0x2000;
    }
}

