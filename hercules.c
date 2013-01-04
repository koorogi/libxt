#include <string.h>
#include <stdio.h>

#include <video/hercules.h>

static void cardinfo(void) {
    fputs("Hercules Card: ", stdout);

    switch (xt_hercules_card()) {
    case XtHerculesCard_None:
        puts("Not Hercules Compatible");
        break;

    case XtHerculesCard_Hercules:
        puts("Hercules");
        break;

    case XtHerculesCard_HerculesPlus:
        puts("Hercules Plus");
        break;

    case XtHerculesCard_HerculesInColor:
        puts("Hercules InColor");
        break;

    case XtHerculesCard_Unknown:
    default:
        puts("Unknown Hercules Compatible");
        break;
    }
}

static void lines_horiz(void) {
    XtHerculesFb framebuf = XT_HERCULES_FRAMEBUFFER0;

    xt_hercules_mode_set(XtHerculesMode_Graphics);
    xt_hercules_fill(framebuf, 0);

    for (int width = 1; width <= 16; width++) {
        for (int y = 0; y < XT_HERCULES_GRAPHICS_ROWS; y++) {
            int startx = 32 * width + y - 104;
            xt_hercules_line_horiz(framebuf, startx, startx + width, y);
        }
    }

    getch();
    xt_hercules_mode_set(XtHerculesMode_Text);
}

typedef void (*Command)(void);

typedef struct {
    Command     command;
    const char *name;
    const char *description;
} ProgramMode;

#define SEPARATOR { NULL, "", "" }
static const ProgramMode modes[] = {
    { cardinfo,    "cardinfo", "Display information about installed graphics card" },
    SEPARATOR,
    { lines_horiz, "hlines",   "Draw horizontal lines"                             },
    { NULL, NULL, NULL }
};

static void help(const char *progname) {
    printf("usage: %s <command>\n\n", progname);
    printf("Available commands:\n");
    for (const ProgramMode *mode = modes; mode->name; mode++) {
        printf("    %-16s\t%s\n", mode->name, mode->description);
    }
}

int main(int argc, char **argv) {
    if (argc == 2) {
        for (const ProgramMode *mode = modes; mode->name; mode++) {
            if (!strcmp(mode->name, argv[1])) {
                mode->command();
                return 0;
            }
        }
    }

    help(argv[0]);
    return 0;
}

