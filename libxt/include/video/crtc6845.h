#ifndef LIBXT_VIDEO_CRTC6845_H
#define LIBXT_VIDEO_CRTC6845_H

#define XT_CRTC6845_PORT_ADDR               0x03b4
#define XT_CRTC6845_PORT_DATA               0x03b5

/* register addresses */
typedef enum {
    XtCrtc6854Reg_HorizTotal = 0,
    XtCrtc6854Reg_HorizDisplayed,
    XtCrtc6854Reg_HorizSyncPos,
    XtCrtc6854Reg_SyncWidth,
    XtCrtc6854Reg_VertTotal,
    XtCrtc6854Reg_VertTotalAdjust,
    XtCrtc6854Reg_VertDisplayed,
    XtCrtc6854Reg_VertSyncPos,
    XtCrtc6854Reg_InterlaceSkew,
    XtCrtc6854Reg_MaxRasterAddr,
    XtCrtc6854Reg_CursorStart,
    XtCrtc6854Reg_CursorEnd,
    XtCrtc6854Reg_StartAddrLo,
    XtCrtc6854Reg_StartAddrHi,
    XtCrtc6854Reg_CursorLo,
    XtCrtc6854Reg_CursorHi,
    XtCrtc6854Reg_LightPenLo,
    XtCrtc6854Reg_LightPenHi,
} XtCrtc6845Reg;

/* calculate the value for the sync width register.
 * h = width of horizontal sync in multiples of character clock (1-15)
 * v = width of vertical sync in raster lines (1-16)
 */
#define XT_CRTC6845_SYNC_WIDTH(h,v)             (((h) & 15) | (((v) & 15) << 4))

#define XT_CRTC6845_CURSOR_CONSTANT             0x00
#define XT_CRTC6845_CURSOR_OFF                  0x20
#define XT_CRTC6845_CURSOR_FAST                 0x40
#define XT_CRTC6845_CURSOR_SLOW                 0x60

#define XT_CRTC6845_CURSOR_START(start,mode)    ((mode) | ((start) & 31))

static inline void xt_crtc6845_reg_write(XtCrtc6845Reg reg, uint8_t data) {
    outp(XT_CRTC6845_PORT_ADDR, reg);
    outp(XT_CRTC6845_PORT_DATA, data);
}

static inline uint8_t xt_crtc6845_reg_read(XtCrtc6845Reg reg) {
    outp(XT_CRTC6845_PORT_ADDR, reg);
    return inp(XT_CRTC6845_PORT_DATA);
}

#endif

