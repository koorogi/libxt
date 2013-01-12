#ifndef LIBXT_MATH_FIXEDPOINT_H
#define LIBXT_MATH_FIXEDPOINT_H

#include <inttypes.h>

typedef int16_t XtFixed8;

#define XT_FIXED8(real)     ((XtFixed8) (256 * (real)))

#define XT_FIXED8_PI        ((XtFixed8) 0x0324)

/* conversion */
static inline int16_t xt_fixed_8to16(XtFixed8 a) {
    return a >> 8;
}

static inline XtFixed8 xt_fixed_16to8(int16_t a) {
    return a << 8;
}

/* conversions to/from floating point. discouraged due to speed */
static inline double xt_fixed_8toF(XtFixed8 a) {
    return a / 256.0;
}

static inline XtFixed8 xt_fixed_Fto8(double a) {
    return a * 256.0;
}

/* multiplication */
XtFixed8 xt_fixed_8x8(XtFixed8 a, XtFixed8 b);

/* division */
XtFixed8 xt_fixed_8d8(XtFixed8 num, XtFixed8 den);
#pragma aux xt_fixed_8d8    \
    parm caller [ax] [bx]   \
    value [ax]              \
    modify [ax dx]

#include <math.h>

/* TODO: replace these with native fixed point implementations */
static inline XtFixed8 xt_fixed_sqrt(XtFixed8 a) {
    return xt_fixed_Fto8(sqrt(xt_fixed_8toF(a)));
}

static inline XtFixed8 xt_fixed_sin(XtFixed8 a) {
    return xt_fixed_Fto8(sin(xt_fixed_8toF(a)));
}

static inline XtFixed8 xt_fixed_cos(XtFixed8 a) {
    return xt_fixed_Fto8(cos(xt_fixed_8toF(a)));
}

#endif

