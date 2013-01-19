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

static void shl(void) {
    UNITTEST_SECTION("Shift Left");

    for (uint32_t i = 0; i < 0x10000; i++) {
        UNITTEST2(asm_shl1(i)  == ((i <<   1) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shl2(i)  == ((i <<   2) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shl3(i)  == ((i <<   3) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shl4(i)  == ((i <<   4) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shl5(i)  == ((i <<   5) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shl6(i)  == ((i <<   6) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shl7(i)  == ((i <<   7) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shl8(i)  == ((i <<   8) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shl9(i)  == ((i <<   9) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shl10(i) == ((i <<  10) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shl11(i) == ((i <<  11) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shl12(i) == ((i <<  12) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shl13(i) == ((i <<  13) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shl14(i) == ((i <<  14) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shl15(i) == ((i <<  15) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shl16(i) == ((i <<  16) & 0xffff), "i = 0x%04x", (uint16_t) i);
    }

    UNITTEST_SECTION_END();
}

static void shr(void) {
    UNITTEST_SECTION("Shift Right");

    for (uint32_t i = 0; i < 0x10000; i++) {
        UNITTEST2(asm_shr1(i)  == i >>   1, "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shr2(i)  == i >>   2, "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shr3(i)  == i >>   3, "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shr4(i)  == i >>   4, "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shr5(i)  == i >>   5, "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shr6(i)  == i >>   6, "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shr7(i)  == i >>   7, "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shr8(i)  == i >>   8, "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shr9(i)  == i >>   9, "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shr10(i) == i >>  10, "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shr11(i) == i >>  11, "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shr12(i) == i >>  12, "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shr13(i) == i >>  13, "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shr14(i) == i >>  14, "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shr15(i) == i >>  15, "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_shr16(i) == i >>  16, "i = 0x%04x", (uint16_t) i);
    }

    UNITTEST_SECTION_END();
}

static void sar_ax(void) {
    UNITTEST_SECTION("Arithmetic Shift Right (in AX)");

    for (uint32_t i = 0; i < 0x8000; i++) {
        UNITTEST2(asm_sar_ax1(i)  == ((i >>   1) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax2(i)  == ((i >>   2) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax3(i)  == ((i >>   3) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax4(i)  == ((i >>   4) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax5(i)  == ((i >>   5) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax6(i)  == ((i >>   6) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax7(i)  == ((i >>   7) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax8(i)  == ((i >>   8) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax9(i)  == ((i >>   9) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax10(i) == ((i >>  10) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax11(i) == ((i >>  11) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax12(i) == ((i >>  12) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax13(i) == ((i >>  13) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax14(i) == ((i >>  14) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax15(i) == ((i >>  15) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax16(i) == ((i >>  16) & 0xffff), "i = 0x%04x", (uint16_t) i);
    }

    for (uint32_t i = 0xffffffff; i >= 0xffff8000; i++) {
        UNITTEST2(asm_sar_ax1(i)  == ((i >>   1) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax2(i)  == ((i >>   2) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax3(i)  == ((i >>   3) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax4(i)  == ((i >>   4) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax5(i)  == ((i >>   5) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax6(i)  == ((i >>   6) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax7(i)  == ((i >>   7) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax8(i)  == ((i >>   8) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax9(i)  == ((i >>   9) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax10(i) == ((i >>  10) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax11(i) == ((i >>  11) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax12(i) == ((i >>  12) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax13(i) == ((i >>  13) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax14(i) == ((i >>  14) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax15(i) == ((i >>  15) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_ax16(i) == ((i >>  16) & 0xffff), "i = 0x%04x", (uint16_t) i);
    }

    UNITTEST_SECTION_END();
}

static void sar_bx(void) {
    UNITTEST_SECTION("Arithmetic Shift Right (in BX)");

    for (uint32_t i = 0; i < 0x8000; i++) {
        UNITTEST2(asm_sar_bx1(i)  == ((i >>   1) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx2(i)  == ((i >>   2) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx3(i)  == ((i >>   3) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx4(i)  == ((i >>   4) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx5(i)  == ((i >>   5) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx6(i)  == ((i >>   6) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx7(i)  == ((i >>   7) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx8(i)  == ((i >>   8) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx9(i)  == ((i >>   9) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx10(i) == ((i >>  10) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx11(i) == ((i >>  11) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx12(i) == ((i >>  12) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx13(i) == ((i >>  13) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx14(i) == ((i >>  14) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx15(i) == ((i >>  15) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx16(i) == ((i >>  16) & 0xffff), "i = 0x%04x", (uint16_t) i);
    }

    for (uint32_t i = 0xffffffff; i >= 0xffff8000; i++) {
        UNITTEST2(asm_sar_bx1(i)  == ((i >>   1) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx2(i)  == ((i >>   2) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx3(i)  == ((i >>   3) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx4(i)  == ((i >>   4) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx5(i)  == ((i >>   5) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx6(i)  == ((i >>   6) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx7(i)  == ((i >>   7) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx8(i)  == ((i >>   8) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx9(i)  == ((i >>   9) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx10(i) == ((i >>  10) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx11(i) == ((i >>  11) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx12(i) == ((i >>  12) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx13(i) == ((i >>  13) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx14(i) == ((i >>  14) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx15(i) == ((i >>  15) & 0xffff), "i = 0x%04x", (uint16_t) i);
        UNITTEST2(asm_sar_bx16(i) == ((i >>  16) & 0xffff), "i = 0x%04x", (uint16_t) i);
    }

    UNITTEST_SECTION_END();
}

void utest_bitshift(void) {
    shl();
    shr();
    sar_ax();
    sar_bx();
}
