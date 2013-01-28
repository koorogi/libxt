#include <video/hercules.h>
#include <video/mda.h>

#include "tests.h"

static const uint16_t chars[] = {
    0,
    0xb0 | (XT_MDA_TEXTATTR_NORMAL << 8),
    0xb1 | (XT_MDA_TEXTATTR_NORMAL << 8),
    0xdb | (XT_MDA_TEXTATTR_NORMAL << 8),
};

static void setmode(XtHerculesMode mode) {
    xt_hercules_mode_set(mode);
    xt_mda_clear();
}

static void fillscreen(void) {
    XtMdaTextBuffer buf = XT_MDA_TEXTBUFFER;

    for (int y = 0; y < 59; y++) {
        for (int x = 0; x < 80; x++) {
            uint16_t val = ('0' + (y & 7));
            val |= y < 25 ? (XT_MDA_TEXTATTR_NORMAL << 8) : (XT_MDA_TEXTATTR_REVERSE << 8);
            *buf++ = val; //chars[(x + y) & 3];
        }
    }
}

static void resolution(void) {
    fillscreen();
    getch();
    setmode(XtHerculesMode_Text80x58);
    fillscreen();
    getch();
    setmode(XtHerculesMode_Text80x25);
}

const TestCase test_resolution = {
    { "hires", "High resolution text mode" },
    resolution,
};
