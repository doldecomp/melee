#include "ftFx_AppealS.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "ftFox/types.h"
#include "gr/grcorneria.h"
#include "pl/player.h"
#include "pl/plbonus.h"
#include "pl/plbonuslib.h"

#include <common_structs.h>

#define FTFOX_APPEALS_ATTACKID 0x72

bool ftFx_AppealS_CheckIfUsed(Fighter* fp)
{
    plActionStats* attackCount = Player_GetActionStats(fp->player_id);
    if (pl_800386D8(attackCount, FTFOX_APPEALS_ATTACKID) != 0 &&
        grCorneria_801E2D14())
    {
        return true;
    }

    return false;
}

static inline bool ftFox_CheckAppealSCount(void)
{
    int i;
    plActionStats* attackCount;

    for (i = 0; i < 6; i++) {
        attackCount = Player_GetActionStats(i);

        if (pl_800386D8(attackCount, 0x72) != 0) {
            return true;
        }
    }

    return false;
}

bool ftFx_AppealS_CheckInput(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 ftKind = fp->kind;

    if ((ftKind == FTKIND_FOX || ftKind == FTKIND_FALCO) &&
        grCorneria_801E2CE8() &&
        !(fp->input.held_inputs & HSD_PAD_DPADDOWN) &&
        fp->x682 == 1)
    {
        if (ftFox_CheckAppealSCount() == 0) {
            ftFx_AppealS_Enter(gobj);
            pl_80040120(fp->player_id, fp->x221F_b4);
            return true;
        }
    }

    return false;
}

static float setFloatOrder(void)
{
    return 0.0f;
}

static float setFloatOrder2(void)
{
    return 1.0f;
}

static inline bool ftFox_AppealS_GetLR(float x1, float x2)
{
    return x1 == x2 ? false : true;
}

static s32 ASID_AppealS[2][3] = {
    { ftFx_MS_AppealSStartR, ftFx_MS_AppealSR, ftFx_MS_AppealSEndR },
    { ftFx_MS_AppealSStartL, ftFx_MS_AppealSL, ftFx_MS_AppealSEndL }
};

void ftFx_AppealS_Enter(HSD_GObj* gobj)
{
    s32 facingDir;
    s32 actionDir;
    s32 animCount;
    Fighter* fp = GET_FIGHTER(gobj);

    fp->mv.fx.AppealS.animCount = 0;
    facingDir = ftFox_AppealS_GetLR(1.0f, fp->facing_dir);

    fp->mv.fx.AppealS.facingDir = facingDir;
    fp->throw_flags = 0;

    actionDir = fp->mv.fx.AppealS.facingDir;
    animCount = fp->mv.fx.AppealS.animCount;

    Fighter_ChangeMotionState(gobj, ASID_AppealS[actionDir][animCount], 0,
                              0.0f, 1.0f, 0.0f, NULL);
}

/// Fox & Falco's Special Taunt OnTakeDamage/OnDeath callback
static void ftFx_AppealS_OnTakeDamage(HSD_GObj*);

void ftFx_AppealS_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    PAD_STACK(4);

    if (ftCheckThrowB3(fp)) {
        switch (fp->kind) {
        case FTKIND_FOX:
            if (grCorneria_801E2B80()) {
                fp->death1_cb = ftFx_AppealS_OnTakeDamage;
            }

            break;

        case FTKIND_FALCO:
            if (grCorneria_801E2C34()) {
                fp->death1_cb = ftFx_AppealS_OnTakeDamage;
            }

            break;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->mv.fx.AppealS.animCount++;
        if (fp->mv.fx.AppealS.animCount >= 3) {
            ft_8008A324(gobj);
            return;
        }

        Fighter_ChangeMotionState(gobj,
                                  ASID_AppealS[fp->mv.fx.AppealS.facingDir]
                                              [fp->mv.fx.AppealS.animCount],
                                  0, 0.0f, 1.0f, 0.0f, NULL);
    }
}

void ftFx_AppealS_IASA(HSD_GObj* gobj)
{
    return;
}

void ftFx_AppealS_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftFx_AppealS_Coll(HSD_GObj* gobj)
{
    ft_80084280(gobj);
}

static void ftFx_AppealS_OnTakeDamage(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    grCorneria_801E2AF4();
    fp->death1_cb = NULL;
}
