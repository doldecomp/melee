#include "ftFox/ftFox_AppealS.h"

#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ftFox/ftfox.h"
#include "gr/grcorneria.h"
#include "it/item2.h"
#include "pl/pl_unknown_001.h"

bool ftFox_AppealS_CheckIfUsed(Fighter* fp)
{
    s32* attackCount = Player_GetTotalAttackCountPtr((s32) fp->xC_playerID);
    if ((func_800386D8(attackCount, FTFOX_APPEALS_ATTACKID) != 0U) &&
        (func_801E2D14() != false))
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

        if (func_800386D8(attackCount, 0x72))
            return true;
    }

    return false;
}

bool ftFox_AppealS_CheckInput(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 ftKind = fp->x4_fighterKind;

    if (((ftKind == FTKIND_FOX) || (ftKind == FTKIND_FALCO)) &&
        (func_801E2CE8() != false) &&
        ((fp->input.x65C_heldInputs & HSD_BUTTON_DPAD_DOWN) == false) &&
        ((u8) fp->x682 == true))
    {
        if (ftFox_CheckAppealSCount() == 0) {
            ftFox_AppealS_Action(gobj);
            func_80040120(fp->xC_playerID, fp->x221F_flag.bits.b4);
            return true;
        }
    }

    return false;
}

f32 setFloatOrder(void)
{
    return 0.0f;
}

f32 setFloatOrder2(void)
{
    return 1.0f;
}

static inline bool ftFox_AppealS_GetLR(f32 x1, f32 x2)
{
    return x1 == x2 ? false : true;
}

static s32 ASID_AppealS[2][3] = {
    { MS_FOX_APPEALS_START_R, MS_FOX_APPEALS_R, MS_FOX_APPEALS_END_R },
    { MS_FOX_APPEALS_START_L, MS_FOX_APPEALS_L, MS_FOX_APPEALS_END_L }
};

void ftFox_AppealS_Action(HSD_GObj* gobj)
{
    s32 facingDir;
    s32 actionDir;
    s32 animCount;
    Fighter* fp = GET_FIGHTER(gobj);

    fp->mv.fx.AppealS.animCount = 0;
    facingDir = ftFox_AppealS_GetLR(1.0f, fp->facing_dir);

    fp->mv.fx.AppealS.facingDir = facingDir;
    fp->x2210_ThrowFlags.flags = 0;

    actionDir = fp->mv.fx.AppealS.facingDir;
    animCount = fp->mv.fx.AppealS.animCount;

    Fighter_ChangeMotionState(gobj, ASID_AppealS[actionDir][animCount], 0,
                              NULL, 0.0f, 1.0f, 0.0f);
}

/// Fox & Falco's Special Taunt OnTakeDamage/OnDeath callback
static void ftFox_AppealS_OnTakeDamage(HSD_GObj*);

void ftFox_AppealS_Anim(HSD_GObj* gobj)
{
    FighterKind ftKind;
    bool flag;
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (fp->x2210_ThrowFlags.b3) {
        fp->x2210_ThrowFlags.b3 = false;
        flag = true;
    } else {
        flag = false;
    }

    if (flag != false) {
        ftKind = fp->x4_fighterKind;

        switch (ftKind) {
        case FTKIND_FOX:
            if (func_801E2B80() != false)
                fp->cb.x21E0_callback_OnDeath = ftFox_AppealS_OnTakeDamage;

            break;

        case FTKIND_FALCO:
            if (func_801E2C34() != false)
                fp->cb.x21E0_callback_OnDeath = ftFox_AppealS_OnTakeDamage;

            break;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->mv.fx.AppealS.animCount++;
        if ((s32) fp->mv.fx.AppealS.animCount >= 3) {
            func_8008A324(gobj);
            return;
        }

        Fighter_ChangeMotionState(gobj,
                                  ASID_AppealS[fp->mv.fx.AppealS.facingDir]
                                              [fp->mv.fx.AppealS.animCount],
                                  0, NULL, 0.0f, 1.0f, 0.0f);
    }
}

void ftFox_AppealS_IASA(HSD_GObj* gobj)
{
    return;
}

void ftFox_AppealS_Phys(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void ftFox_AppealS_Coll(HSD_GObj* gobj)
{
    func_80084280(gobj);
}

static void ftFox_AppealS_OnTakeDamage(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_801E2AF4();
    fp->cb.x21E0_callback_OnDeath = NULL;
}
