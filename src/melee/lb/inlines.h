#ifndef MELEE_LB_INLINES_H
#define MELEE_LB_INLINES_H

#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>

/// @todo Is a macro the best way?
#define SKIP_CMD(cmd, n)                                                      \
    do {                                                                      \
        int i;                                                                \
        for (i = 0; i < (n); i++) {                                           \
            ++(cmd)->u;                                                       \
        }                                                                     \
    } while (0);

#define NEXT_CMD(cmd)                                                         \
    do {                                                                      \
        ++(cmd)->u;                                                           \
    } while (0);

static inline void lbCardGame_SetupArchive(void)
{
    lbCardNew_AllocWorkArea();
    lbCardGame_LoadArchive(0);
    lbCardGame_UpdatePowerTime();
}

#endif
