#include <stdio.h>

#include "bench.h"

static void nop(void) {}

const Benchmark bench_nop = {
    { "nop", "Call a no-op function" }, NULL, nop, NULL,
};

