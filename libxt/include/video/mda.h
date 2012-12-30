#ifndef LIBXT_MDA_H
#define LIBXT_MDA_H

#include <inttypes.h>
#include <conio.h>

#define MDA_PORT_MODE_CTRL          0x03b8
#define MDA_PORT_STATUS             0x03ba

#define MDA_MODE_BLINK              0x20
#define MDA_MODE_ENABLE_VIDEO       0x08
#define MDA_MODE_HIRES              0x01

static inline void mda_modereg_write(uint8_t mode) {
    /* MDA_MODE_HIRES must always be set, or we risk hanging the machine */
    outp(MDA_PORT_MODE_CTRL, mode | MDA_MODE_HIRES);
}

#define MDA_STATUS_DRAWING(status)  ((status) & 0x08)
#define MDA_STATUS_HSYNC(status)    ((status) & 0x01)

#define MDA_PIXELBUFFER             ((volatile uint8_t  *) 0xb0000)
#define MDA_TEXTBUFFER              ((volatile uint16_t *) 0xb0000)

#define TEXT_BLINK                  0x80
#define TEXT_BRIGHT                 0x08

#define TEXT_COLOR_BG(c)            (((c) &  7) << 4)
#define TEXT_COLOR_FG(c)            (((c) & 15) << 0)

#define TEXT_MONO_INVERT            (TEXT_COLOR_BG(7) | TEXT_COLOR_FG(7))

#endif

