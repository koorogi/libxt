#include <inttypes.h>
#include <conio.h>
#include <assert.h>

#include <video/crtc6845.h>
#include <video/mda.h>
#include <video/hercules.h>

#define OFFSET(rowdiv4)     (90 * (rowdiv4))
#define FB_ROW(rowdiv4)     OFFSET(rowdiv4),            \
                            OFFSET(rowdiv4) + 0x2000,   \
                            OFFSET(rowdiv4) + 0x4000,   \
                            OFFSET(rowdiv4) + 0x6000

const xt_hercules_fb_row_offset[348] = {
    FB_ROW( 0), FB_ROW( 1), FB_ROW( 2), FB_ROW( 3), FB_ROW( 4),
    FB_ROW( 5), FB_ROW( 6), FB_ROW( 7), FB_ROW( 8), FB_ROW( 9),
    FB_ROW(10), FB_ROW(11), FB_ROW(12), FB_ROW(13), FB_ROW(14),
    FB_ROW(15), FB_ROW(16), FB_ROW(17), FB_ROW(18), FB_ROW(19),
    FB_ROW(20), FB_ROW(21), FB_ROW(22), FB_ROW(23), FB_ROW(24),
    FB_ROW(25), FB_ROW(26), FB_ROW(27), FB_ROW(28), FB_ROW(29),
    FB_ROW(30), FB_ROW(31), FB_ROW(32), FB_ROW(33), FB_ROW(34),
    FB_ROW(35), FB_ROW(36), FB_ROW(37), FB_ROW(38), FB_ROW(39),
    FB_ROW(40), FB_ROW(41), FB_ROW(42), FB_ROW(43), FB_ROW(44),
    FB_ROW(45), FB_ROW(46), FB_ROW(47), FB_ROW(48), FB_ROW(49),
    FB_ROW(50), FB_ROW(51), FB_ROW(52), FB_ROW(53), FB_ROW(54),
    FB_ROW(55), FB_ROW(56), FB_ROW(57), FB_ROW(58), FB_ROW(59),
    FB_ROW(60), FB_ROW(61), FB_ROW(62), FB_ROW(63), FB_ROW(64),
    FB_ROW(65), FB_ROW(66), FB_ROW(67), FB_ROW(68), FB_ROW(69),
    FB_ROW(70), FB_ROW(71), FB_ROW(72), FB_ROW(73), FB_ROW(74),
    FB_ROW(75), FB_ROW(76), FB_ROW(77), FB_ROW(78), FB_ROW(79),
    FB_ROW(80), FB_ROW(81), FB_ROW(82), FB_ROW(83), FB_ROW(84),
    FB_ROW(85), FB_ROW(86)
};

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

void xt_hercules_wait_vsync(void) {
    while ( XT_HERCULES_STATUS_VSYNC(inp(XT_MDA_PORT_STATUS))) { }
    while (!XT_HERCULES_STATUS_VSYNC(inp(XT_MDA_PORT_STATUS))) { }
}

