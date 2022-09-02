#include <melee/ft/chara/ftFox/ftfox.h>

extern u32 func_800386D8(void*, s32);
extern BOOL func_801E2D14();

// 0x800E5970
// https://decomp.me/scratch/sI1ge // Check if Special Taunt has already been performed
BOOL ftFox_AppealS_CheckIfUsed(Fighter* fp)
{
    void* attackCount = Player_GetTotalAttackCountPtr((s32)fp->xC_playerID);
    if ((func_800386D8(attackCount, FTFOX_APPEALS_ATTACKID) != 0U) && (func_801E2D14() != FALSE))
    {
        return TRUE;
    }
    return FALSE;
}

void ftFox_AppealS_Action(HSD_GObj*);
extern void func_80040120(u8, s32);
extern s32 func_801E2CE8();

inline BOOL ftFox_CheckAppealSCount()
{
    s32 i;
    void* attackCount;

    for (i = 0; i < 6; i++)
    {
        attackCount = Player_GetTotalAttackCountPtr(i);
        if (func_800386D8(attackCount, 0x72)) return TRUE;
    }
    return FALSE;
}

// 0x800E59BC
// https://decomp.me/scratch/by7uz // Check if Fox/Falco has pressed D-Pad Down
BOOL ftFox_AppealS_CheckInput(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    s32 ftKind = fp->x4_fighterKind;

    if (((ftKind == FTKIND_FOX) || (ftKind == FTKIND_FALCO)) && (func_801E2CE8() != FALSE) && ((fp->input.x65C_heldInputs & HSD_BUTTON_DPAD_DOWN) == FALSE) && ((u8)fp->x682 == TRUE))
    {
        if (ftFox_CheckAppealSCount() == 0)
        {
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

inline BOOL ftFox_AppealS_GetLR(f32 x1, f32 x2)
{
    if (x1 == x2)
    {
        return 0;
    }
    else return 1;
}

static s32 ASID_AppealS[2][3] = { AS_FOX_APPEALS_START_R, AS_FOX_APPEALS_R, AS_FOX_APPEALS_END_R, AS_FOX_APPEALS_START_L, AS_FOX_APPEALS_L, AS_FOX_APPEALS_END_L };

// 0x800E5A90
// https://decomp.me/scratch/PFxY9 // Fox & Falco's Special Taunt Action State handler
void ftFox_AppealS_Action(HSD_GObj* fighter_gobj)
{
    s32 facingDir;
    s32 actionDir;
    s32 animCount;
    Fighter* fp = fighter_gobj->user_data;

    fp->foxVars[0].AppealS.animCount = 0;
    facingDir = ftFox_AppealS_GetLR(1.0f, fp->x2C_facing_direction);

    fp->foxVars[0].AppealS.facingDir = facingDir;
    fp->x2210_ThrowFlags.flags = 0;

    actionDir = fp->foxVars[0].AppealS.facingDir;
    animCount = fp->foxVars[0].AppealS.animCount;

    Fighter_ActionStateChange_800693AC(fighter_gobj, ASID_AppealS[actionDir][animCount], 0, NULL, 0.0f, 1.0f, 0.0f);
}

extern void func_8008A324(HSD_GObj*);
extern s32 func_801E2B80();
extern s32 func_801E2C34();
extern void ftFox_AppealS_OnTakeDamage(HSD_GObj*);

// 0x800E5B18
// https://decomp.me/scratch/7DvuI // Fox & Falco's Special Taunt Start Animation callback
void ftFox_AppealS_Anim(HSD_GObj* fighter_gobj)
{
    s32 ftKind;
    s32 flag;
    s32 var1;
    s32 var2;
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2210_ThrowFlags.b3 != 0)
    {
        fp->x2210_ThrowFlags.b3 = 0;
        flag = TRUE;
    }
    else flag = FALSE;

    if (flag != FALSE)
    {
        ftKind = fp->x4_fighterKind;

        switch (ftKind)
        {
        case FTKIND_FOX:
            if (func_801E2B80() != FALSE)
            {
                fp->cb.x21E0_callback_OnDeath = ftFox_AppealS_OnTakeDamage;
            }
            break;

        case FTKIND_FALCO:
            if (func_801E2C34() != FALSE)
            {
                fp->cb.x21E0_callback_OnDeath = ftFox_AppealS_OnTakeDamage;
            }
            break;
        }
    }
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        fp->foxVars[0].AppealS.animCount++;
        if ((s32)fp->foxVars[0].AppealS.animCount >= 3)
        {
            func_8008A324(fighter_gobj);
            return;
        }
        Fighter_ActionStateChange_800693AC(fighter_gobj, ASID_AppealS[fp->foxVars[0].AppealS.facingDir][fp->foxVars[0].AppealS.animCount], 0, NULL, 0.0f, 1.0f, 0.0f);
    }
}

// 0x800E5C38 - Fox & Falco's Special Taunt Start IASA callback
void ftFox_AppealS_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800E5C3C - Fox & Falco's Special Taunt Physics callback
void ftFox_AppealS_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

extern void func_80084280(HSD_GObj*);

// 0x800E5C5C - Fox & Falco's Special Taunt Collision callback
void ftFox_AppealS_Coll(HSD_GObj* fighter_gobj)
{
    func_80084280(fighter_gobj);
}

extern void func_801E2AF4();

// 0x800E5C7C
// https://decomp.me/scratch/VkVGw // Fox & Falco's Special Taunt OnTakeDamage/OnDeath callback
void ftFox_AppealS_OnTakeDamage(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_801E2AF4();
    fp->cb.x21E0_callback_OnDeath = NULL;
}
