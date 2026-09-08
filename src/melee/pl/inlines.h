#ifndef MELEE_PL_INLINES_H
#define MELEE_PL_INLINES_H

#include <melee/gm/gmvs.h>
#include <melee/pl/player.h>

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

static inline bool pl_Verify_gm_8016AEDC(void)
{
    if ((gm_GetFrameCount() != 0U) && (gm_GetFrameCount() != -2U)) {
        return true;
    } else {
        return false;
    }
}

#endif
