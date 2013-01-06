#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>

#include "bench/bench.h"

#define TIMER_INTR      0x1c

/* convert ticks into seconds -- this is an approximation */
#define TICKS(seconds)  (uint16_t) (18.2 * (seconds))

/* 5 seconds was chosen because it is (very) nearly a whole number of ticks */
#define DEFAULT_SECONDS 5
#define MAX_SECONDS     3600

static uint16_t seconds, total_ticks;

static volatile _Bool    started;
static volatile _Bool    done;
static volatile uint16_t ticks;

static void (__interrupt __far *prev_handler)(void);
static void __interrupt __far timer_handler(void) {
    started = 1;
    if (ticks) {
        done = --ticks == 0;
    } else {
        done = 1;
    }
    _chain_intr(prev_handler);
}

static void bench_start(void) {
    prev_handler = _dos_getvect(TIMER_INTR);

    started = 0;
    done    = 0;
    ticks   = total_ticks + 1;
    _dos_setvect(TIMER_INTR, timer_handler);
    while (!started) {}
}

static int bench_check(void) {
    if (done) {
        _dos_setvect(TIMER_INTR, prev_handler);
        return 1;
    }
    return 0;
}

static uint32_t run(const Benchmark *bench) {
    uint32_t iterations;

    if (bench->init) {
        bench->init();
    }

    bench_start();
    for (iterations = 0; !bench_check(); iterations++) {
        bench->iter();
    }

    if (bench->fini) {
        bench->fini();
    }
    return iterations;
}

static uint16_t parse_seconds(const char *arg) {
    char *end;
    long int parsed = strtol(arg, &end, 10);

    /* if we got a non-numeric value, return 0 indicating that the argument
     * was actually a benchmark name and not the number of seconds to test */
    if (*end) {
        return 0;
    }

    /* if we got a numeric value, but it's out of range, use the default time */
    if (parsed < 1 || parsed > MAX_SECONDS) {
        return DEFAULT_SECONDS;
    }

    return (uint16_t) parsed;
}

static const Benchmark *benchmarks[] = {
    &bench_nop,
    NULL
};

typedef struct {
    const Benchmark *benchmark;
    uint32_t         iterations;
} BenchmarkResult;

int main(int argc, char **argv) {
    int firstarg = 1;

    if (argc > 1) {
        seconds = parse_seconds(argv[1]);
        if (seconds) {
            firstarg ++;
        } else {
            seconds = DEFAULT_SECONDS;
        }
    }
    total_ticks = TICKS(seconds);

    if (argc < firstarg + 1) {
        printf("usage: %s [seconds] <benchmark> [...]\n\n", argv[0]);
        printf("Available benchmarks:\n");
        XT_CMDLINE_LIST(benchmarks);
        return 0;
    }

    BenchmarkResult *results = malloc(sizeof(*results) * (argc - 1));
    _Bool invalid = 0;
    int   count   = 0;

    for (int i = firstarg; i < argc; i++) {
        const Benchmark *bench = XT_CMDLINE_PARSE(Benchmark, benchmarks, argv[i]);
        if (bench) {
            results[count++].benchmark = bench;
        } else {
            printf("Unknown benchmark `%s'\n", argv[i]);
            invalid = 1;
        }
    }

    if (invalid) {
        puts("");
        puts("Rerun with no arguments to see valid benchmark names.");
        return 0;
    }

    for (int i = 0; i < count; i++) {
        results[i].iterations = run(results[i].benchmark);
    }

    printf("%-24s \t%-10s \t%-12s\n", "Benchmark", "Iterations", "Iters/Second");
    for (int i = 0; i < count; i++) {
        printf("%-24s \t%10" PRIu32 " \t%12" PRIu32 "\n",
                results[i].benchmark->command.name,
                results[i].iterations, results[i].iterations / seconds);
    }

    free(results);
    return 0;
}

