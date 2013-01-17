#include <stdio.h>

#include <video/hercules.h>

int main() {
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

    return 0;
}

