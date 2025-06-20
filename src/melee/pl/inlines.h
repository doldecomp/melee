#ifndef MELEE_PL_INLINES_H
#define MELEE_PL_INLINES_H

#include <melee/gm/gm_1601.h>
#include <melee/it/it_26B1.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonusinline.h>
#include <melee/pl/types.h>

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

static inline void pl_80039450_inline(int slot)
{
    pl_StaleMoveTableExt_t* var_r26;
    int i;

    var_r26 = Player_GetStaleMoveTableIndexPtr2(slot);

    for (i = 0; i < 215; ++i) {
        if (gm_8016F1B8(i) == 0) {
            var_r26->x0_staleMoveTable.x904[0] = 0;
        }
        var_r26 = (pl_StaleMoveTableExt_t*) ((char*) var_r26 + 4);
    }
}

static inline int fn_8003EE2C_inline(HSD_GObj* gobj)
{
    int kind = itGetKind(gobj);
    if ((kind >= 0) && (kind < 0x23)) {
        return kind;
    } else {
        switch (kind) {
        case 0xCD:
            kind = 0x23;
            break;
        case 0xE1:
            kind = 0x24;
            break;
        case 0xE2:
            kind = 0x25;
            break;
        case 0x28:
            kind = 0x26;
            break;
        default:
            kind = -1;
            break;
        }
    }
    return kind;
}

#endif
