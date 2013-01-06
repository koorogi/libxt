#include <stdio.h>

#include <video/hercules.h>
#include <cmdline.h>

#include "hercules/hercules.h"

static const HerculesCommand separator = {
    { NULL, NULL }, NULL
};

static const HerculesCommand *commands[] = {
    &cmd_cardinfo,
    &separator,
    &cmd_hlines,
    NULL
};

int main(int argc, char **argv) {
    if (argc == 2) {
        const HerculesCommand *cmd = XT_CMDLINE_PARSE(HerculesCommand, commands, argv[1]);
        if (cmd) {
            cmd->action();
            return 0;
        }
    }

    printf("usage: %s <command>\n\n", argv[0]);
    printf("Available commands:\n");
    XT_CMDLINE_LIST(commands);
    return 0;
}

