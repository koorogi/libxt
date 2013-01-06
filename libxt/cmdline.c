#include <string.h>
#include <stdio.h>

#include <cmdline.h>

void xt_cmdline_list(const XtCommand **commands) {
    for (const XtCommand **cur = commands; *cur; cur++) {
        const XtCommand *cmd = *cur;
        if (cmd->name) {
            printf("    %-24s\t%s\n", cmd->name, cmd->description);
        } else {
            puts("");
        }
    }
}

const XtCommand *xt_cmdline_parse(const XtCommand **commands, const char *arg) {
    for (const XtCommand **cur = commands; *cur; cur++) {
        const XtCommand *cmd = *cur;
        if (!strcmp(cmd->name, arg)) {
            return cmd;
        }
    }

    return NULL;
}

