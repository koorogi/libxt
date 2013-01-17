#ifndef LIBXT_VIDEO_HERCULES_H
#define LIBXT_VIDEO_HERCULES_H

#include <conio.h>

/* the hercules also supports MDA_PORT_MODE_CTRL, MDA_PORT_STATUS */
#define XT_HERCULES_PORT_LIGHTPEN_SET       0x03b9
#define XT_HERCULES_PORT_LIGHTPEN_RESET     0x03bb
#define XT_HERCULES_PORT_GRAPHICS           0x03bf

static inline void xt_hercules_lightpen_set(_Bool value) {
    outp(value ? XT_HERCULES_PORT_LIGHTPEN_SET : XT_HERCULES_PORT_LIGHTPEN_RESET, 1);
}

/* additional bits that can be set in MDA_PORT_MODE_CTRL */
#define XT_HERCULES_MODE_GRAPHICS_PAGE(n)   ((n) == 1 ? 0x80 : 0)
#define XT_HERCULES_MODE_TEXT               0x00
#define XT_HERCULES_MODE_GRAPHICS           0x02

/* additional bits that can be read from MDA_PORT_STATUS */
#define XT_HERCULES_STATUS_VSYNC(status)    !((status) & 0x80)
#define XT_HERCULES_STATUS_CARD_ID(status)  (((status) & 0x70) >> 4)
#define XT_HERCULES_STATUS_LIGHTPEN(status) ( (status) & 0x02)

typedef enum {
    XtHerculesCard_None            = -1,
    XtHerculesCard_Hercules        =  0,
    XtHerculesCard_HerculesPlus    =  1,
    XtHerculesCard_HerculesInColor =  5,
    XtHerculesCard_Unknown         =  7,
} XtHerculesCard;

XtHerculesCard xt_hercules_card(void);

#define XT_HERCULES_GRAPHICS_ENABLE_PAGE0   0x01
#define XT_HERCULES_GRAPHICS_ENABLE_PAGE1   0x02

typedef enum {
    XtHerculesMode_Text = 0,
    XtHerculesMode_Graphics,

    XtHerculesMode_Count
} XtHerculesMode;

void xt_hercules_mode_set(XtHerculesMode mode);

#endif

