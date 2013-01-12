#include <string.h>

#include "unittest/unittest.h"

_Bool verbose = 0;

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--verbose") || !strcmp(argv[i], "-v")) {
            verbose = 1;
        }
    }

    for (const UnitTest *test = unittests; *test; test++) {
        (*test)();
    }
    return 0;
}

