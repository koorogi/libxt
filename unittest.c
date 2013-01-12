#include "unittest/unittest.h"

int main() {
    for (const UnitTest *test = unittests; *test; test++) {
        (*test)();
    }
    return 0;
}

