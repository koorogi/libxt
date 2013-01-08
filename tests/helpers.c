#include <video/hercules.h>

#include "helpers.h"

void setmode_graphics(void) {
    xt_hercules_mode_set(XtHerculesMode_Graphics);
    xt_hercules_fill(XT_HERCULES_FRAMEBUFFER0, 0);
}

void setmode_text(void) {
    xt_hercules_mode_set(XtHerculesMode_Text);
}
