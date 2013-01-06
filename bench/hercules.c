#include <stdio.h>

#include <video/hercules.h>

#include "bench.h"

const Benchmark bench_hercules_vsync = {
    { "hercules_vsync", "Wait for vertical sync" },
    NULL,
    xt_hercules_wait_vsync,
    NULL,
};

