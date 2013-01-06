#ifndef LIBXT_CMDLINE_H
#define LIBXT_CMDLINE_H

typedef struct {
    const char *name;
    const char *description;
} XtCommand;

void xt_cmdline_list(const XtCommand **commands);
const XtCommand *xt_cmdline_parse(const XtCommand **commands, const char *arg);

#define XT_CMDLINE_LIST(cmds)               xt_cmdline_list((const XtCommand **) cmds)
#define XT_CMDLINE_PARSE(type,cmds,arg)     ((const type *) xt_cmdline_parse((const XtCommand **) (cmds), arg))

#endif

