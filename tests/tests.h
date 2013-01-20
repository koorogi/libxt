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
extern const Benchmark bench_hercules_alines;
extern const Benchmark bench_hercules_hlines_short;
extern const Benchmark bench_hercules_hlines_long;
extern const Benchmark bench_hercules_cube;
extern const Benchmark bench_hercules_vsync;

extern const Benchmark bench_sqrt_libxt;
extern const Benchmark bench_sqrt_turkowski;
extern const Benchmark bench_sqrt_arm;
extern const Benchmark bench_sqrt_lut;

extern const Benchmark bench_quat_conj;
extern const Benchmark bench_quat_conj2;
extern const Benchmark bench_quat_conj3;

typedef struct {
    XtCommand command;
    void (*test)(void);
} TestCase;

extern const TestCase test_cardinfo;
extern const TestCase test_cube;
extern const TestCase test_alines;
extern const TestCase test_hlines;
extern const TestCase test_vlines;

extern const TestCase test_sqrt_libxt;
extern const TestCase test_sqrt_turkowski;
extern const TestCase test_sqrt_arm;
extern const TestCase test_sqrt_lut;

#endif

