#ifndef LIBXT_VIDEO_MDA_H
#define LIBXT_VIDEO_MDA_H

#include <inttypes.h>
#include <conio.h>
#include <i86.h>

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

typedef uint16_t far *XtMdaTextBuffer;

#define XT_MDA_TEXTBUFFER               ((XtMdaTextBuffer) MK_FP(0xb000, 0))

#include <video/textattr.h>

#define XT_MDA_TEXTATTR_BLINK           XT_TEXTATTR_BLINK
#define XT_MDA_TEXTATTR_BRIGHT          XT_TEXTATTR_BRIGHT
#define XT_MDA_TEXTATTR_UNDERLINE       XT_TEXTATTR_COLOR_FG(1)
#define XT_MDA_TEXTATTR_NORMAL          XT_TEXTATTR_COLOR_FG(7)
#define XT_MDA_TEXTATTR_REVERSE         XT_TEXTATTR_COLOR_BG(7)

void xt_mda_clear(void);

#endif

