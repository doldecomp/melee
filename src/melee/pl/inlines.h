#ifndef MELEE_PL_INLINES_H
#define MELEE_PL_INLINES_H

#include <platform.h>

#include <gm/gm_1601.h>
#include <pl/player.h>
#include <pl/plbonusinline.h>

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
}

static inline bool pl_Verify_gm_8016AEDC()
{
    if ((gm_8016AEDC() != 0U) && (gm_8016AEDC() != -2U)) {
        return true;
    } else {
        return false;
    }
}

#endif
