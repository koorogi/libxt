#ifndef LIBXT_VIDEO_TEXTATTR_H
#define LIBXT_VIDEO_TEXTATTR_H

#define XT_TEXTATTR_BLINK           0x80
#define XT_TEXTATTR_BRIGHT          0x08
#define XT_TEXTATTR_COLOR_BG(n)     (((n) &  7) << 4)
#define XT_TEXTATTR_COLOR_FG(n)     (((n) & 15) << 0)

#endif

