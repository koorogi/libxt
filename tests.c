#include <stdio.h>

#include <video/hercules.h>
#include <cmdline.h>

#include "tests/tests.h"

static const TestCase separator = {
    { NULL, NULL }, NULL
};

static const TestCase *test_cases[] = {
    &test_cardinfo,
    &separator,
    &test_alines,
    &test_hlines,
    &test_vlines,
    &separator,
    &test_cube,
    &separator,
    &test_sqrt_libxt,
    &test_sqrt_turkowski,
    &test_sqrt_arm,
    NULL
};

int main(int argc, char **argv) {
    if (argc == 2) {
        const TestCase *test = XT_CMDLINE_PARSE(TestCase, test_cases, argv[1]);
        if (test) {
            test->test();
            return 0;
        }
    }

    printf("usage: %s <command>\n\n", argv[0]);
    printf("Available commands:\n");
    XT_CMDLINE_LIST(test_cases);
    return 0;
}

