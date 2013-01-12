#include <math/fixedpoint.h>

#include "unittest.h"

static void convert(void) {
    UNITTEST_SECTION("Fixed Point Conversions");
    UNITTEST(xt_fixed_16to8(  -128) == 0x8000);
    UNITTEST(xt_fixed_16to8(   -64) == 0xc000);
    UNITTEST(xt_fixed_16to8(     0) == 0x0000);
    UNITTEST(xt_fixed_16to8(     1) == 0x0100);
    UNITTEST(xt_fixed_16to8(    64) == 0x4000);
    UNITTEST(xt_fixed_16to8(   127) == 0x7f00);
    UNITTEST(xt_fixed_8to16(0x8000) ==   -128);
    UNITTEST(xt_fixed_8to16(0xc000) ==    -64);
    UNITTEST(xt_fixed_8to16(0x0000) ==      0);
    UNITTEST(xt_fixed_8to16(0x0100) ==      1);
    UNITTEST(xt_fixed_8to16(0x4000) ==     64);
    UNITTEST(xt_fixed_8to16(0x7f00) ==    127);
}

static void multiply(void) {
    UNITTEST_SECTION("Fixed Point Multiplication");
    UNITTEST(xt_fixed_8x8(0xffff, 0x0100) == 0xffff);
    UNITTEST(xt_fixed_8x8(0x7fff, 0x0100) == 0x7fff);
    UNITTEST(xt_fixed_8x8(0x0fff, 0x0100) == 0x0fff);
    UNITTEST(xt_fixed_8x8(0x00ff, 0x0100) == 0x00ff);
    UNITTEST(xt_fixed_8x8(0xffff, 0x0200) == 0xfffe);
    UNITTEST(xt_fixed_8x8(0x0fff, 0x0200) == 0x1ffe);
    UNITTEST(xt_fixed_8x8(0x00ff, 0x0200) == 0x01fe);

    UNITTEST(xt_fixed_8x8(0x0100, 0x0080) == 0x0080);
    UNITTEST(xt_fixed_8x8(0x0010, 0x0080) == 0x0008);
    UNITTEST(xt_fixed_8x8(0x0001, 0x0080) == 0x0000);

    UNITTEST(xt_fixed_8x8(0x0500, 0x0280) == 0x0c80);
}

static void divide(void) {
    UNITTEST_SECTION("Fixed Point Division");
    UNITTEST(xt_fixed_8d8(0xffff, 0x0100) == 0xffff);
    UNITTEST(xt_fixed_8d8(0x7fff, 0x0100) == 0x7fff);
    UNITTEST(xt_fixed_8d8(0x0fff, 0x0100) == 0x0fff);
    UNITTEST(xt_fixed_8d8(0x00ff, 0x0100) == 0x00ff);
    UNITTEST(xt_fixed_8d8(0xffff, 0x0200) == 0x0000);
    UNITTEST(xt_fixed_8d8(0x0fff, 0x0200) == 0x07ff);
    UNITTEST(xt_fixed_8d8(0x00ff, 0x0200) == 0x007f);

    UNITTEST(xt_fixed_8d8(0x0100, 0x0080) == 0x0200);
    UNITTEST(xt_fixed_8d8(0x0010, 0x0080) == 0x0020);
    UNITTEST(xt_fixed_8d8(0x0001, 0x0080) == 0x0002);

    UNITTEST(xt_fixed_8d8(0x0c80, 0x0280) == 0x0500);
}

void utest_fixedpoint(void) {
    convert();
    multiply();
    divide();
}

