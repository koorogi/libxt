#ifndef HERCULES_H
#define HERCULES_H

#include <cmdline.h>

typedef struct {
    XtCommand command;
    void (*action)(void);
} HerculesCommand;

extern const HerculesCommand cmd_cardinfo;
extern const HerculesCommand cmd_hlines;
extern const HerculesCommand cmd_vlines;

#endif

