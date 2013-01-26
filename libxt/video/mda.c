#include <video/mda.h>

void xt_mda_clear(void) {
    for (int i = 0; i < 80*25; i ++) {
        XT_MDA_TEXTBUFFER[i] = ' ' | (XT_MDA_TEXTATTR_NORMAL << 8);
    }
}
