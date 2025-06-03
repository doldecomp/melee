#include "lb_0192.h"

#include "lbcardgame.h"

#include <dolphin/dvd.h>

/* 019230 */ static enum_t lb_80019230(void);

enum_t lb_80019230(void)
{
    switch (DVDGetDriveStatus()) {
    case 5:
        return 0;
    case 4:
        return 1;
    case 6:
        return 2;
    case 11:
        return 3;
    case -1:
        return 4;
    case 1:
        return 5;
    default:
        return -1;
    }
}

void lb_800195D0(void)
{
    lb_800192A8(lb_8001955C);
    lb_8001CC84();
}
