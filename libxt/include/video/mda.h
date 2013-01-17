#ifndef LIBXT_VIDEO_MDA_H
#define LIBXT_VIDEO_MDA_H

#include <inttypes.h>
#include <conio.h>

#define XT_MDA_PORT_MODE_CTRL           0x03b8
#define XT_MDA_PORT_STATUS              0x03ba

#define XT_MDA_MODE_BLINK               0x20
#define XT_MDA_MODE_ENABLE_VIDEO        0x08
#define XT_MDA_MODE_HIRES               0x01

static inline void xt_mda_modereg_write(uint8_t mode) {
    /* MDA_MODE_HIRES must always be set, or we risk hanging the machine */
    outp(XT_MDA_PORT_MODE_CTRL, mode | XT_MDA_MODE_HIRES);
}

#define XT_MDA_STATUS_DRAWING(status)   ((status) & 0x08)
#define XT_MDA_STATUS_HSYNC(status)     ((status) & 0x01)

typedef volatile uint16_t far *XtMdaTextBuffer;

#define XT_MDA_TEXTBUFFER               ((XtMdaTextBuffer) 0xb0000)

#include <video/textattr.h>

#define XT_MDA_TEXTATTR_BLINK           XT_TEXTATTR_BLINK
#define XT_MDA_TEXTATTR_BRIGHT          XT_TEXTATTR_BRIGHT
#define XT_MDA_TEXTATTR_INVERT          (XT_TEXTATTR_COLOR_BG(7) | XT_TEXTATTR_COLOR_FG(7))

#endif

