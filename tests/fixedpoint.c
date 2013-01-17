#include <stdio.h>

#include <math/fixedpoint.h>

#include "tests.h"

/* the compiler can optimize away all calls to some of the libxt functions
 * if it can detect that we don't use the results. This is here to provide
 * a way of "using" the results to prevent this benchmark-invalidating
 * optimization */
volatile XtFixed8 killoptim;

/* square root */

/* assembly implementations */
XtFixed8 sqrt_6389443(XtFixed8);

#define TEST(name,fn,min,max)                                       \
    static void printtbl_sqrt_ ## name(void) {                      \
        for (XtFixed8 val = min; (uint16_t) val < max; val++) {     \
            printf("%d\n", fn(val));                                \
        }                                                           \
    }                                                               \
    static void benchmark_sqrt_ ## name(void) {                     \
        XtFixed8 accum = 0;                                         \
        for (XtFixed8 val = min; (uint16_t) val < max; val++) {     \
            accum |= fn(val);                                       \
        }                                                           \
        killoptim = accum;                                          \
    }                                                               \
    const Benchmark bench_sqrt_ ## name = {                         \
        { "sqrt_" #name, "Fixed point square root (" #name ")" },   \
        NULL, benchmark_sqrt_ ## name, NULL                         \
    };                                                              \
    const TestCase test_sqrt_ ## name = {                           \
        { "sqrt_" #name, "Fixed point square root (" #name ")" },   \
        printtbl_sqrt_ ## name                                      \
    };

#define SQRT(name,fn)   TEST(name,fn,0,0x8000)

SQRT(libxt,   xt_fixed_sqrt)

