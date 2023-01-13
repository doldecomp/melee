#include <melee/ft/chara/ftFox/ftfox.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/gr/grcorneria.h>
#include <melee/it/item2.h>
#include <melee/pl/pl_unknown_001.h>

BOOL ftFox_AppealS_CheckIfUsed(Fighter* fp)
{
    s32* attackCount = Player_GetTotalAttackCountPtr((s32) fp->xC_playerID);
    if ((func_800386D8(attackCount, FTFOX_APPEALS_ATTACKID) != 0U) &&
        (func_801E2D14() != FALSE))
    {
        return TRUE;
    }

    return FALSE;
}

static inline BOOL ftFox_CheckAppealSCount(void)
{
    int i;
    s32* attackCount;

    for (i = 0; i < 6; i++) {
        attackCount = Player_GetTotalAttackCountPtr(i);

        if (func_800386D8(attackCount, 0x72))
            return TRUE;
    }

    return FALSE;
}

BOOL ftFox_AppealS_CheckInput(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    s32 ftKind = fp->x4_fighterKind;

    if (((ftKind == FTKIND_FOX) || (ftKind == FTKIND_FALCO)) &&
        (func_801E2CE8() != FALSE) &&
        ((fp->input.x65C_heldInputs & HSD_BUTTON_DPAD_DOWN) == FALSE) &&
        ((u8) fp->x682 == TRUE))
    {
        if (ftFox_CheckAppealSCount() == 0) {
            ftFox_AppealS_Action(fighter_gobj);
            func_80040120(fp->xC_playerID, fp->x221F_flag.bits.b4);
            return TRUE;
        }
    }

    return FALSE;
}

f32 setFloatOrder(void)
{
    return 0.0f;
}

f32 setFloatOrder2(void)
{
    return 1.0f;
}

static inline BOOL ftFox_AppealS_GetLR(f32 x1, f32 x2)
{
    return x1 == x2 ? FALSE : TRUE;
}

static s32 ASID_AppealS[2][3] = {
    { AS_FOX_APPEALS_START_R, AS_FOX_APPEALS_R, AS_FOX_APPEALS_END_R },
    { AS_FOX_APPEALS_START_L, AS_FOX_APPEALS_L, AS_FOX_APPEALS_END_L }
};

void ftFox_AppealS_Action(HSD_GObj* fighter_gobj)
{
    s32 facingDir;
    s32 actionDir;
    s32 animCount;
    Fighter* fp = fighter_gobj->user_data;

    fp->foxVars[0].AppealS.animCount = 0;
    facingDir = ftFox_AppealS_GetLR(1.0f, fp->facing_dir);

    fp->foxVars[0].AppealS.facingDir = facingDir;
    fp->x2210_ThrowFlags.flags = 0;

    actionDir = fp->foxVars[0].AppealS.facingDir;
    animCount = fp->foxVars[0].AppealS.animCount;

    Fighter_ActionStateChange_800693AC(fighter_gobj,
                                       ASID_AppealS[actionDir][animCount], 0,
                                       NULL, 0.0f, 1.0f, 0.0f);
}

/// Fox & Falco's Special Taunt OnTakeDamage/OnDeath callback
static void ftFox_AppealS_OnTakeDamage(HSD_GObj*);

void ftFox_AppealS_Anim(HSD_GObj* fighter_gobj)
{
    s32 ftKind;
    s32 flag;
    s32 var1;
    s32 var2;
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2210_ThrowFlags.b3 != 0) {
        fp->x2210_ThrowFlags.b3 = 0;
        flag = TRUE;
    } else {
        flag = FALSE;
    }

    if (flag != FALSE) {
        ftKind = fp->x4_fighterKind;

        switch (ftKind) {
        case FTKIND_FOX:
            if (func_801E2B80() != FALSE)
                fp->cb.x21E0_callback_OnDeath = ftFox_AppealS_OnTakeDamage;

            break;

        case FTKIND_FALCO:
            if (func_801E2C34() != FALSE)
                fp->cb.x21E0_callback_OnDeath = ftFox_AppealS_OnTakeDamage;

            break;
        }
    }
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        fp->foxVars[0].AppealS.animCount++;
        if ((s32) fp->foxVars[0].AppealS.animCount >= 3) {
            func_8008A324(fighter_gobj);
            return;
        }

        Fighter_ActionStateChange_800693AC(
            fighter_gobj,
            ASID_AppealS[fp->foxVars[0].AppealS.facingDir]
                        [fp->foxVars[0].AppealS.animCount],
            0, NULL, 0.0f, 1.0f, 0.0f);
    }
}

void ftFox_AppealS_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

void ftFox_AppealS_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

void ftFox_AppealS_Coll(HSD_GObj* fighter_gobj)
{
    func_80084280(fighter_gobj);
}

static void ftFox_AppealS_OnTakeDamage(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_801E2AF4();
    fp->cb.x21E0_callback_OnDeath = NULL;
}
