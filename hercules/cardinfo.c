#include <stdio.h>

#include <video/hercules.h>

#include "hercules.h"

static void cardinfo(void) {
    const char *cardname;

    switch (xt_hercules_card()) {
    case XtHerculesCard_None:
        cardname = "Not Hercules Compatible";
        break;

    case XtHerculesCard_Hercules:
        cardname = "Hercules";
        break;

    case XtHerculesCard_HerculesPlus:
        cardname = "Hercules Plus";
        break;

    case XtHerculesCard_HerculesInColor:
        cardname = "Hercules InColor";
        break;

    case XtHerculesCard_Unknown:
    default:
        cardname = "Unknown Hercules Compatible";
        break;
    }

    printf("Hercules Card: %s\n", cardname);
}

const HerculesCommand cmd_cardinfo = {
    { "cardinfo", "Information about installed graphics card" },
    cardinfo,
};

