#ifndef UNITTEST_H
#define UNITTEST_H

#include <inttypes.h>
#include <stdio.h>

typedef void (*UnitTest)(void);

#define UNITTEST_SECTION(name)  {           \
    uint32_t total = 0, passed = 0;         \
    printf("%s: %s\n", __FILE__, name);

#define UNITTEST_SECTION_END()              \
    printf("    %" PRIu32 " passed + %" PRIu32 " failed = %" PRIu32 " total\n\n", passed, total - passed, total); \
    }

#define UNITTEST(expr)                      \
    do {                                    \
        _Bool pass = !!(expr);              \
        passed    += pass;                  \
        total++;                            \
        if (!pass || verbose) {             \
            printf("    %s: %s\n", pass ? "PASS" : "FAIL", #expr ); \
        }                                   \
    } while(0)

extern _Bool verbose;
extern const UnitTest unittests[];

void utest_fixedpoint(void);

#endif

