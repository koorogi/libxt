#include <inttypes.h>
#include <conio.h>
#include <assert.h>

#include <video/crtc6845.h>
#include <video/mda.h>
#include <video/hercules.h>

HerculesCard hercules_card(void) {
    uint8_t status = inp(MDA_PORT_STATUS);
    _Bool   vsync  = HGC_STATUS_VSYNC(status);

    for (unsigned i = 0; i < 0x8000; i++) {
        if (vsync != HGC_STATUS_VSYNC(inp(MDA_PORT_STATUS))) {
            return HGC_STATUS_CARD_ID(status);
        }
    }

    return HGC_CARD_NONE;
}

static uint8_t crtc_mode_data[HERCULES_MODE_COUNT][12] = {
    [HERCULES_MODE_TEXT] = {
        [CRTC6854_REG_HORIZ_TOTAL]       = 98 - 1,
        [CRTC6854_REG_HORIZ_DISPLAYED]   = 80,      /* 80 chars * 9 pixels = 720 pixels */
        [CRTC6854_REG_HORIZ_SYNC_POS]    = 83 - 1,
        [CRTC6854_REG_SYNC_WIDTH]        = CRTC6845_SYNC_WIDTH(15, 16),
        [CRTC6854_REG_VERT_TOTAL]        = 26 - 1,
        [CRTC6854_REG_VERT_TOTAL_ADJUST] =  6,
        [CRTC6854_REG_VERT_DISPLAYED]    = 25,
        [CRTC6854_REG_VERT_SYNC_POS]     = 26 - 1,
        [CRTC6854_REG_INTERLACE_SKEW]    =  2,      /* TODO */
        [CRTC6854_REG_MAX_RASTER_ADDR]   = 14 - 1,  /* chars are 14 pixels tall */
        [CRTC6854_REG_CURSOR_START]      = CRTC6845_CURSOR_START(11, CRTC6845_CURSOR_CONSTANT),
        [CRTC6854_REG_CURSOR_END]        = 12,
    },

    [HERCULES_MODE_GRAPHICS] = {
        [CRTC6854_REG_HORIZ_TOTAL]       = 54 - 1,
        [CRTC6854_REG_HORIZ_DISPLAYED]   = 45,      /* 45 chars * 16 pixels = 720 pixels */
        [CRTC6854_REG_HORIZ_SYNC_POS]    = 47 - 1,
        [CRTC6854_REG_SYNC_WIDTH]        = CRTC6845_SYNC_WIDTH(7, 16),
        [CRTC6854_REG_VERT_TOTAL]        = 92 - 1,
        [CRTC6854_REG_VERT_TOTAL_ADJUST] =  2,
        [CRTC6854_REG_VERT_DISPLAYED]    = 87,
        [CRTC6854_REG_VERT_SYNC_POS]     = 88 - 1,
        [CRTC6854_REG_INTERLACE_SKEW]    =  2,      /* TODO */
        [CRTC6854_REG_MAX_RASTER_ADDR]   =  4 - 1,  /* chars are 4 pixels tall */
        [CRTC6854_REG_CURSOR_START]      = CRTC6845_CURSOR_START(0, CRTC6845_CURSOR_CONSTANT),
        [CRTC6854_REG_CURSOR_END]        =  0,
    },
};

/* TODO: expand this to support 90 column text, and different text heights */
void hercules_mode_set(HerculesMode mode) {
    uint8_t ctrl;

    switch (mode) {
    case HERCULES_MODE_TEXT:
        ctrl = HGC_MODE_TEXT | MDA_MODE_BLINK;
        break;

    case HERCULES_MODE_GRAPHICS:
        ctrl = HGC_MODE_GRAPHICS | HGC_MODE_GRAPHICS_PAGE(0);
        break;

    default:
        assert(0);
    }

    outp(HGC_PORT_GRAPHICS, HGC_GRAPHICS_ENABLE_PAGE0 | HGC_GRAPHICS_ENABLE_PAGE1);
    mda_modereg_write(ctrl);
    for (int reg = 0; reg < 12; reg++) {
        crtc6845_reg_write(reg, crtc_mode_data[mode][reg]);
    }
    mda_modereg_write(ctrl | MDA_MODE_ENABLE_VIDEO);
}

