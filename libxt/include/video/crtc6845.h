#ifndef LIBXT_CRTC6845_H
#define LIBXT_CRTC6845_H

#define CRTC6845_PORT_ADDR                  0x03b4
#define CRTC6845_PORT_DATA                  0x03b5

/* register addresses */
typedef enum {
    CRTC6854_REG_HORIZ_TOTAL = 0,
    CRTC6854_REG_HORIZ_DISPLAYED,
    CRTC6854_REG_HORIZ_SYNC_POS,
    CRTC6854_REG_SYNC_WIDTH,
    CRTC6854_REG_VERT_TOTAL,
    CRTC6854_REG_VERT_TOTAL_ADJUST,
    CRTC6854_REG_VERT_DISPLAYED,
    CRTC6854_REG_VERT_SYNC_POS,
    CRTC6854_REG_INTERLACE_SKEW,
    CRTC6854_REG_MAX_RASTER_ADDR,
    CRTC6854_REG_CURSOR_START,
    CRTC6854_REG_CURSOR_END,
    CRTC6854_REG_START_ADDR_LO,
    CRTC6854_REG_START_ADDR_HI,
    CRTC6854_REG_CURSOR_LO,
    CRTC6854_REG_CURSOR_HI,
    CRTC6854_REG_LIGHT_PEN_LO,
    CRTC6854_REG_LIGHT_PEN_HI,
} Crtc6845Register;

/* calculate the value for the sync width register.
 * h = width of horizontal sync in multiples of character clock (1-15)
 * v = width of vertical sync in raster lines (1-16)
 */
#define CRTC6845_SYNC_WIDTH(h,v)            (((h) & 15) | (((v) & 15) << 4))

#define CRTC6845_CURSOR_CONSTANT            0x00
#define CRTC6845_CURSOR_OFF                 0x20
#define CRTC6845_CURSOR_FAST                0x40
#define CRTC6845_CURSOR_SLOW                0x60

#define CRTC6845_CURSOR_START(start,mode)   ((mode) | ((start) & 31))

static inline void crtc6845_reg_write(Crtc6845Register reg, uint8_t data) {
    outp(CRTC6845_PORT_ADDR, reg);
    outp(CRTC6845_PORT_DATA, data);
}

static inline uint8_t crtc6845_reg_read(Crtc6845Register reg) {
    outp(CRTC6845_PORT_ADDR, reg);
    return inp(CRTC6845_PORT_DATA);
}

#endif

