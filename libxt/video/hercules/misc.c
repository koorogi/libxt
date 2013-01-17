#include <inttypes.h>
#include <conio.h>
#include <assert.h>

#include <video/crtc6845.h>
#include <video/mda.h>
#include <video/hercules.h>

XtHerculesCard xt_hercules_card(void) {
    uint8_t status = inp(XT_MDA_PORT_STATUS);
    _Bool   vsync  = XT_HERCULES_STATUS_VSYNC(status);

    for (unsigned i = 0; i < 0x8000; i++) {
        if (vsync != XT_HERCULES_STATUS_VSYNC(inp(XT_MDA_PORT_STATUS))) {
            return XT_HERCULES_STATUS_CARD_ID(status);
        }
    }

    return XtHerculesCard_None;
}

static uint8_t crtc_mode_data[XtHerculesMode_Count][12] = {
    [XtHerculesMode_Text] = {
        [XtCrtc6854Reg_HorizTotal]      = 98 - 1,
        [XtCrtc6854Reg_HorizDisplayed]  = 80,      /* 80 chars * 9 pixels = 720 pixels */
        [XtCrtc6854Reg_HorizSyncPos]    = 83 - 1,
        [XtCrtc6854Reg_SyncWidth]       = XT_CRTC6845_SYNC_WIDTH(15, 16),
        [XtCrtc6854Reg_VertTotal]       = 26 - 1,
        [XtCrtc6854Reg_VertTotalAdjust] =  6,
        [XtCrtc6854Reg_VertDisplayed]   = 25,
        [XtCrtc6854Reg_VertSyncPos]     = 26 - 1,
        [XtCrtc6854Reg_InterlaceSkew]   =  2,      /* TODO */
        [XtCrtc6854Reg_MaxRasterAddr]   = 14 - 1,  /* chars are 14 pixels tall */
        [XtCrtc6854Reg_CursorStart]     = XT_CRTC6845_CURSOR_START(11, XT_CRTC6845_CURSOR_CONSTANT),
        [XtCrtc6854Reg_CursorEnd]       = 12,
    },

    [XtHerculesMode_Graphics] = {
        [XtCrtc6854Reg_HorizTotal]      = 54 - 1,
        [XtCrtc6854Reg_HorizDisplayed]  = 45,      /* 45 chars * 16 pixels = 720 pixels */
        [XtCrtc6854Reg_HorizSyncPos]    = 47 - 1,
        [XtCrtc6854Reg_SyncWidth]       = XT_CRTC6845_SYNC_WIDTH(7, 16),
        [XtCrtc6854Reg_VertTotal]       = 92 - 1,
        [XtCrtc6854Reg_VertTotalAdjust] =  2,
        [XtCrtc6854Reg_VertDisplayed]   = 87,
        [XtCrtc6854Reg_VertSyncPos]     = 88 - 1,
        [XtCrtc6854Reg_InterlaceSkew]   =  2,      /* TODO */
        [XtCrtc6854Reg_MaxRasterAddr]   =  4 - 1,  /* chars are 4 pixels tall */
        [XtCrtc6854Reg_CursorStart]     = XT_CRTC6845_CURSOR_START(0, XT_CRTC6845_CURSOR_CONSTANT),
        [XtCrtc6854Reg_CursorEnd]       =  0,
    },
};

/* TODO: expand this to support 90 column text, and different text heights */
void xt_hercules_mode_set(XtHerculesMode mode) {
    uint8_t ctrl;

    switch (mode) {
    case XtHerculesMode_Text:
        ctrl = XT_HERCULES_MODE_TEXT | XT_MDA_MODE_BLINK;
        break;

    case XtHerculesMode_Graphics:
        ctrl = XT_HERCULES_MODE_GRAPHICS | XT_HERCULES_MODE_GRAPHICS_PAGE(0);
        break;

    default:
        assert(0);
    }

    outp(XT_HERCULES_PORT_GRAPHICS, XT_HERCULES_GRAPHICS_ENABLE_PAGE0 | XT_HERCULES_GRAPHICS_ENABLE_PAGE1);
    xt_mda_modereg_write(ctrl);
    for (int reg = 0; reg < 12; reg++) {
        xt_crtc6845_reg_write(reg, crtc_mode_data[mode][reg]);
    }
    xt_mda_modereg_write(ctrl | XT_MDA_MODE_ENABLE_VIDEO);
}

