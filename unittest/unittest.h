#ifndef UNITTEST_H
#define UNITTEST_H

#include <stdio.h>

typedef void (*UnitTest)(void);

#define UNITTEST_SECTION(name)  printf("\n%s: %s\n", __FILE__, name)
#define UNITTEST(expr)          printf("    %s: %s\n", (expr) ? "PASS" : "FAIL", #expr )

extern const UnitTest unittests[];

void utest_fixedpoint(void);

#endif

