#ifndef LIBXT_UTIL_H
#define LIBXT_UTIL_H

#define XT_SIGN(a)              ((a) < 0 ? -1 : 1)
#define XT_ABS(a)               ((a) < 0 ? -(a) : (a))

#define XT_MIN(a,b)             ((a) < (b) ? (a) : (b))
#define XT_MAX(a,b)             ((a) > (b) ? (a) : (b))

#define XT_CLIP(val,min,max)    XT_MIN(max, XT_MAX(min, val))

#define XT_SWAP(type,a,b)       {   \
        type tmp = a;               \
        a = b;                      \
        b = tmp;                    \
    }

#endif

