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
extern const Benchmark bench_hercules_vsync;

#endif

