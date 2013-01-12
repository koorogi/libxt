#ifndef UNITTEST_H
#define UNITTEST_H

#include <stdio.h>

typedef void (*UnitTest)(void);

#define UNITTEST_SECTION(name)  {           \
    unsigned total = 0, passed = 0;         \
    printf("%s: %s\n", __FILE__, name);

#define UNITTEST_SECTION_END()              \
    printf("    %u passed + %u failed = %u total\n\n", passed, total - passed, total); \
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

