#include <inttypes.h>

#include "unittest.h"

/* assembly functions to shift by fixed numbers of bits */
#define DEFINE_FUNC(fn)             \
    uint16_t fn ##  1(uint16_t);   \
    uint16_t fn ##  2(uint16_t);   \
    uint16_t fn ##  3(uint16_t);   \
    uint16_t fn ##  4(uint16_t);   \
    uint16_t fn ##  5(uint16_t);   \
    uint16_t fn ##  6(uint16_t);   \
    uint16_t fn ##  7(uint16_t);   \
    uint16_t fn ##  8(uint16_t);   \
    uint16_t fn ##  9(uint16_t);   \
    uint16_t fn ## 10(uint16_t);   \
    uint16_t fn ## 11(uint16_t);   \
    uint16_t fn ## 12(uint16_t);   \
    uint16_t fn ## 13(uint16_t);   \
    uint16_t fn ## 14(uint16_t);   \
    uint16_t fn ## 15(uint16_t);   \
    uint16_t fn ## 16(uint16_t)    \

DEFINE_FUNC(asm_shl);
DEFINE_FUNC(asm_shr);

/* For arithmetic shifts, the assembly has different code paths based on
   whether the operand is in the ax register or not.  We test them both */
DEFINE_FUNC(asm_sar_ax);
DEFINE_FUNC(asm_sar_bx);

#define SHIFTTEST1(fn,i,o)                              \
    UNITTEST2(fn(i) == ((o) & 0xffff),                  \
        "in = 0x%04" PRIx16 ", out = 0x%04" PRIx16 ", expected = 0x%04" PRIx16, \
        (uint16_t) (i), (uint16_t) fn(i), (uint16_t) (o))

#define SHIFTTEST(fn,i,op)              \
    SHIFTTEST1(fn ##  1, i, i op  1);   \
    SHIFTTEST1(fn ##  2, i, i op  2);   \
    SHIFTTEST1(fn ##  3, i, i op  3);   \
    SHIFTTEST1(fn ##  4, i, i op  4);   \
    SHIFTTEST1(fn ##  5, i, i op  5);   \
    SHIFTTEST1(fn ##  6, i, i op  6);   \
    SHIFTTEST1(fn ##  7, i, i op  7);   \
    SHIFTTEST1(fn ##  8, i, i op  8);   \
    SHIFTTEST1(fn ##  9, i, i op  9);   \
    SHIFTTEST1(fn ## 10, i, i op 10);   \
    SHIFTTEST1(fn ## 11, i, i op 11);   \
    SHIFTTEST1(fn ## 12, i, i op 12);   \
    SHIFTTEST1(fn ## 13, i, i op 13);   \
    SHIFTTEST1(fn ## 14, i, i op 14);   \
    SHIFTTEST1(fn ## 15, i, i op 15);   \
    SHIFTTEST1(fn ## 16, i, i op 16)

static void shl(void) {
    UNITTEST_SECTION("Shift Left");

    for (uint32_t i = 0; i < 0x10000; i++) {
        SHIFTTEST(asm_shl, i, <<);
    }

    UNITTEST_SECTION_END();
}

static void shr(void) {
    UNITTEST_SECTION("Shift Right");

    for (uint32_t i = 0; i < 0x10000; i++) {
        SHIFTTEST(asm_shr, i, >>);
    }

    UNITTEST_SECTION_END();
}

static void sar_ax(void) {
    UNITTEST_SECTION("Arithmetic Shift Right (in AX)");

    for (uint32_t i = 0; i < 0x8000; i++) {
        SHIFTTEST(asm_sar_ax, i, >>);
    }

    for (uint32_t i = 0xffffffff; i >= 0xffff8000; i++) {
        SHIFTTEST(asm_sar_ax, i, >>);
    }

    UNITTEST_SECTION_END();
}

static void sar_bx(void) {
    UNITTEST_SECTION("Arithmetic Shift Right (in BX)");

    for (uint32_t i = 0; i < 0x8000; i++) {
        SHIFTTEST(asm_sar_bx, i, >>);
    }

    for (uint32_t i = 0xffffffff; i >= 0xffff8000; i++) {
        SHIFTTEST(asm_sar_bx, i, >>);
    }

    UNITTEST_SECTION_END();
}

void utest_bitshift(void) {
    shl();
    shr();
    sar_ax();
    sar_bx();
}
