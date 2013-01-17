#ifndef BENCH_H
#define BENCH_H

#include <cmdline.h>

typedef struct {
    XtCommand command;

    void (*init)(void);
    void (*iter)(void);
    void (*fini)(void);
} Benchmark;

extern const Benchmark bench_nop;
extern const Benchmark bench_hercules_clear;
extern const Benchmark bench_hercules_clear2;
extern const Benchmark bench_hercules_clear3;
extern const Benchmark bench_hercules_clear4;
extern const Benchmark bench_hercules_vsync;

#endif

