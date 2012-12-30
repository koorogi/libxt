#ifndef LIBXT_HERCULES_H
#define LIBXT_HERCULES_H

#include <conio.h>

/* the hercules also supports MDA_PORT_MODE_CTRL, MDA_PORT_STATUS */
#define HGC_PORT_LIGHTPEN_SET       0x03b9
#define HGC_PORT_LIGHTPEN_RESET     0x03bb
#define HGC_PORT_GRAPHICS           0x03bf

static inline void hercules_lightpen_set(_Bool value) {
    outp(value ? HGC_PORT_LIGHTPEN_SET : HGC_PORT_LIGHTPEN_RESET, 1);
}

/* additional bits that can be set in MDA_PORT_MODE_CTRL */
#define HGC_MODE_GRAPHICS_PAGE(n)   ((n) == 1 ? 0x80 : 0)
#define HGC_MODE_TEXT               0x00
#define HGC_MODE_GRAPHICS           0x02

/* additional bits that can be read from MDA_PORT_STATUS */
#define HGC_STATUS_VSYNC(status)    !((status) & 0x80)
#define HGC_STATUS_CARD_ID(status)  (((status) & 0x70) >> 4)
#define HGC_STATUS_LIGHTPEN(status) ( (status) & 0x02)

typedef enum {
    HGC_CARD_NONE             = -1,
    HGC_CARD_HERCULES         =  0,
    HGC_CARD_HERCULES_PLUS    =  1,
    HGC_CARD_HERCULES_INCOLOR =  5,
    HGC_CARD_UNKNOWN          =  7,
} HerculesCard;

extern HerculesCard hercules_card(void);

#define HGC_GRAPHICS_ENABLE_PAGE0   0x01
#define HGC_GRAPHICS_ENABLE_PAGE1   0x02

typedef enum {
    HERCULES_MODE_TEXT = 0,
    HERCULES_MODE_GRAPHICS,

    HERCULES_MODE_COUNT
} HerculesMode;

extern void hercules_mode_set(HerculesMode mode);

#endif

