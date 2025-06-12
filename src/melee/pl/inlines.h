#ifndef MELEE_PL_INLINES_H
#define MELEE_PL_INLINES_H

#include <platform.h>

#include "player.h"

#include <gm/gm_1601.h>

static inline bool pl_CheckIfSameTeam(int slotA, int slotB)
{
    int teamA;
    int teamB;

    if (gm_8016B168()) {
        teamA = Player_GetTeam(slotA);
        teamB = Player_GetTeam(slotB);
        if (teamB == teamA) {
            return true;
        }
    }
    return false;
};

#endif
