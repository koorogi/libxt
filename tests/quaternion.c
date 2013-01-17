#include <stdio.h>

#include <math/fixedpoint.h>
#include <math/quaternion.h>

#include "tests.h"

/* conjugation */
static const XtQuaternion conj_input = { 1, 2, 3, 4 };

XtQuaternion quat_conj_asm(XtQuaternion q);

static XtQuaternion quat_conj_c(XtQuaternion q) {
    q.x = -q.x;
    q.y = -q.y;
    q.z = -q.z;
    return q;
}

static void conj_libxt(void) {
    xt_quat_conj(conj_input);
}

static void conj_asm(void) {
    quat_conj_asm(conj_input);
}

static void conj_c(void) {
    quat_conj_c(conj_input);
}

const Benchmark bench_quat_conj = {
    { "conjugate", "Conjugate quaternion (libxt)" },
    NULL, conj_libxt, NULL,
};

const Benchmark bench_quat_conj2 = {
    { "conjugate2", "Conjugate quaternion (assembly)" },
    NULL, conj_asm, NULL,
};

const Benchmark bench_quat_conj3 = {
    { "conjugate3", "Conjugate quaternion (c)" },
    NULL, conj_c, NULL,
};

