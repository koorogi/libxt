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
extern const Benchmark bench_hercules_hlines_short;
extern const Benchmark bench_hercules_hlines_long;
extern const Benchmark bench_hercules_vsync;

typedef struct {
    XtCommand command;
    void (*test)(void);
} TestCase;

extern const TestCase test_cardinfo;
extern const TestCase test_hlines;
extern const TestCase test_vlines;

#endif

