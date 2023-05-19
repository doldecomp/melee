#include "forward.h"

#include "ftFx_AppealS.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/inlines.h"
#include "gr/grcorneria.h"
#include "it/it_26B1.h"
#include "pl/pl_0371.h"

#define FTFOX_APPEALS_ATTACKID 0x72

bool ftFx_AppealS_CheckIfUsed(Fighter* fp)
{
    s32* attackCount = Player_GetTotalAttackCountPtr((s32) fp->xC_playerID);
    if ((pl_800386D8(attackCount, FTFOX_APPEALS_ATTACKID) != 0U) &&
        (grCorneria_801E2D14() != false))
    {
        return true;
    }

    return false;
}

static inline bool ftFox_CheckAppealSCount(void)
{
    int i;
    s32* attackCount;

    for (i = 0; i < 6; i++) {
        attackCount = Player_GetTotalAttackCountPtr(i);

        if (pl_800386D8(attackCount, 0x72)) {
            return true;
        }
    }

    return false;
}

bool ftFx_AppealS_CheckInput(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 ftKind = fp->kind;

    if (((ftKind == FTKIND_FOX) || (ftKind == FTKIND_FALCO)) &&
        (grCorneria_801E2CE8() != false) &&
        ((fp->input.held_inputs & HSD_PAD_DPADDOWN) == false) &&
        ((u8) fp->x682 == true))
    {
        if (ftFox_CheckAppealSCount() == 0) {
            ftFx_AppealS_Enter(gobj);
            pl_80040120(fp->xC_playerID, fp->x221F_flag.bits.b4);
            return true;
        }
    }

    return false;
}

static f32 setFloatOrder(void)
{
    return 0.0f;
}

static f32 setFloatOrder2(void)
{
    return 1.0f;
}

static inline bool ftFox_AppealS_GetLR(f32 x1, f32 x2)
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
    fp->throw_flags.flags = 0;

    actionDir = fp->mv.fx.AppealS.facingDir;
    animCount = fp->mv.fx.AppealS.animCount;

    Fighter_ChangeMotionState(gobj, ASID_AppealS[actionDir][animCount], 0,
                              NULL, 0.0f, 1.0f, 0.0f);
}

/// Fox & Falco's Special Taunt OnTakeDamage/OnDeath callback
static void ftFx_AppealS_OnTakeDamage(HSD_GObj*);

void ftFx_AppealS_Anim(HSD_GObj* gobj)
{
    FighterKind ftKind;
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (ftCheckThrowB3(fp)) {
        ftKind = fp->kind;

        switch (ftKind) {
        case FTKIND_FOX:
            if (grCorneria_801E2B80() != false) {
                fp->cb.x21E0_callback_OnDeath = ftFx_AppealS_OnTakeDamage;
            }

            break;

        case FTKIND_FALCO:
            if (grCorneria_801E2C34() != false) {
                fp->cb.x21E0_callback_OnDeath = ftFx_AppealS_OnTakeDamage;
            }

            break;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->mv.fx.AppealS.animCount++;
        if ((s32) fp->mv.fx.AppealS.animCount >= 3) {
            ft_8008A324(gobj);
            return;
        }

        Fighter_ChangeMotionState(gobj,
                                  ASID_AppealS[fp->mv.fx.AppealS.facingDir]
                                              [fp->mv.fx.AppealS.animCount],
                                  0, NULL, 0.0f, 1.0f, 0.0f);
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
    fp->cb.x21E0_callback_OnDeath = NULL;
}
