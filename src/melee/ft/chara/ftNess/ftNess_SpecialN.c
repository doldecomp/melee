#include <melee/ft/chara/ftNess/ftNess.h>

// 0x80116EBC //
// https://decomp.me/scratch/45pKw //
BOOL ftNess_CheckSpecialNHold(HSD_GObj* fighter_gobj) // Ness PK Flash Charge ASID check //
{
    Fighter* fp;
    s32 ASID;

    if (fighter_gobj != NULL)
    {
        fp = fighter_gobj->user_data;
        if (fp != NULL)
        {
            if (fp->sa.ness.x2240_flashGObj != NULL)
            {
                ASID = fp->x10_action_state_index;
                if (ASID == AS_NESS_SPECIALN_HOLD || ASID == AS_NESS_SPECIALAIRN_HOLD)
                {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

// 0x80116F00 //
// https://decomp.me/scratch/84rSJ //
void ftNess_SpecialNSetNULL(HSD_GObj* fighter_gobj) // Clear Ness's callbacks and PK Flash's item GObj pointer //
{
    Fighter* fp;

    if (fighter_gobj != NULL)
    {
        fp = fighter_gobj->user_data;
        if (fp != NULL)
        {
            if (fp->sa.ness.x2240_flashGObj != NULL)
            {
                fp->sa.ness.x2240_flashGObj = NULL;
            }
            fp->cb.x21E4_callback_OnDeath2 = NULL;
            fp->cb.x21DC_callback_OnTakeDamage = NULL;
        }
    }
}

extern void func_802AAA50(HSD_GObj*);

// 0x80116F38 //
// https://decomp.me/scratch/HJkeV //
void ftNess_ItemPKFlushSetNULL(HSD_GObj* fighter_gobj)  // Clear PK Flash's owner GObj pointer, Ness's pointer to PK Flash's item GObj, and reset callbacks //
{
    Fighter* fp;

    if (fighter_gobj != NULL)
    {
        fp = fighter_gobj->user_data;
        if (fp != NULL)
        {
            if (fp->sa.ness.x2240_flashGObj != NULL)
            {
                func_802AAA50(fp->sa.ness.x2240_flashGObj);
                fp->sa.ness.x2240_flashGObj = NULL;
            }
            fp->cb.x21E4_callback_OnDeath2 = NULL;
            fp->cb.x21DC_callback_OnTakeDamage = NULL;
        }
    }
}

f32 return_void(void)   // Define float order for match //
{
    return 0.0f;
}

f32 return_void2(void)
{
    return 3.0f;
}

f32 return_void3(void)
{
    return 1.0f;
}

// 0x80116F94 //
// https://decomp.me/scratch/xOc8Y //
void ftNess_SpecialNStart_Action(HSD_GObj* fighter_gobj)  // Ness's grounded PK Flash Start Action State handler //
{
    Fighter* fp;
    ftNessAttributes* ness_attr;
    Fighter* temp_fp;

    fp = getFighterPlus(fighter_gobj);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALN_START, 0, NULL, 0.0f, 1.0f, 0.0f);

    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;

    temp_fp = fighter_gobj->user_data;
    ness_attr = getFtSpecialAttrs(temp_fp);

    temp_fp->nessVars[0].SpecialN.flashTimerLoop1 = (s32)ness_attr->x0_PKFLASH_TIMER1_LOOPFRAMES;
    temp_fp->nessVars[0].SpecialN.flashTimerLoop2 = (s32)ness_attr->x4_PKFLASH_TIMER2_LOOPFRAMES;
    temp_fp->nessVars[0].SpecialN.gravityDelay = (s32)ness_attr->x8_PKFLASH_GRAVITY_DELAY;

    temp_fp->sa.ness.x2240_flashGObj = NULL;
    temp_fp->nessVars[0].SpecialN.flashTimerMin = (s32)ness_attr->xC_PKFLASH_MINCHARGEFRAMES;
    temp_fp->cb.x21E4_callback_OnDeath2 = NULL;
    temp_fp->cb.x21DC_callback_OnTakeDamage = NULL;
    func_8006EBA4(fighter_gobj);
}

// 0x80117034 //
// https://decomp.me/scratch/ZjUdo
void ftNess_SpecialAirNStart_Action(HSD_GObj* fighter_gobj)  // Ness's aerial PK Flash Start Action State handler //
{
    Fighter* fp;
    ftNessAttributes* ness_attr;
    Fighter* temp_fp;

    fp = getFighterPlus(fighter_gobj);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRN_START, 0, NULL, 0.0f, 1.0f, 0.0f);

    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x80_self_vel.y = 0.0f;

    temp_fp = fighter_gobj->user_data;
    ness_attr = getFtSpecialAttrs(temp_fp);

    temp_fp->nessVars[0].SpecialN.flashTimerLoop1 = (s32)ness_attr->x0_PKFLASH_TIMER1_LOOPFRAMES;
    temp_fp->nessVars[0].SpecialN.flashTimerLoop2 = (s32)ness_attr->x4_PKFLASH_TIMER2_LOOPFRAMES;
    temp_fp->nessVars[0].SpecialN.gravityDelay = (s32)ness_attr->x8_PKFLASH_GRAVITY_DELAY;

    temp_fp->sa.ness.x2240_flashGObj = NULL;

    temp_fp->nessVars[0].SpecialN.flashTimerMin = (s32)ness_attr->xC_PKFLASH_MINCHARGEFRAMES;

    temp_fp->cb.x21E4_callback_OnDeath2 = NULL;
    temp_fp->cb.x21DC_callback_OnTakeDamage = NULL;

    func_8006EBA4(fighter_gobj);
}

extern HSD_GObj* func_802AA8C0(HSD_GObj*, Vec3*, s32, f32);

// 0x801170DC //
// https://decomp.me/scratch/JhiVu // 
void ftNess_SpecialNStart_Anim(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Start Animation callback //
{
    Vec3 sp28;
    void (*cb_OnDeath2)(HSD_GObj*);
    void (*cb_OnTakeDamage)(HSD_GObj*);
    f32 zero;
    f32 frameSpeedMul;
    f32 scaleMul;
    HSD_GObj* flash_GObj;
    Fighter* fp;
    Fighter* fighter_data2;

    fp = fighter_gobj->user_data;
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALN_HOLD, 0, NULL, 0.0f, 1.0f, 0.0f);
        fighter_data2 = getFighterPlus(fighter_gobj);
        if (fighter_data2->sa.ness.x2240_flashGObj == NULL) 
        {
            func_8000B1CC(fighter_data2->x5E8_fighterBones[24].x0_jobj, NULL, &sp28);
            sp28.z = 0.0f;
            sp28.y += 3.0f * fighter_data2->x34_scale.y;
            flash_GObj = func_802AA8C0(fighter_gobj, &sp28, It_Kind_Ness_PKFlush, fighter_data2->x2C_facing_direction);
            fighter_data2->sa.ness.x2240_flashGObj = flash_GObj;
            if (flash_GObj != NULL) 
            {
                fighter_data2->cb.x21E4_callback_OnDeath2 = ftNess_OnDamage;
                fighter_data2->cb.x21DC_callback_OnTakeDamage = ftNess_OnDamage;
            }
        }
        fp->x1968_jumpsUsed = (u8)fp->x110_attr.x168_MaxJumps;
    }
}

extern HSD_GObj* func_802AA7E4(HSD_GObj*);
extern s32 func_802AA7F0(HSD_GObj*);

// 0x801171BC //
// https://decomp.me/scratch/W8wUK //
void ftNess_SpecialNHold_Anim(HSD_GObj* fighter_gobj)   // Ness's grounded PK Flash Charge Animation callback //
{
    Fighter* fp;

    fp = fighter_gobj->user_data;
    if (fp->nessVars[0].SpecialN.flashTimerLoop1 != 0)
    {
        fp->nessVars[0].SpecialN.flashTimerLoop1--;
    }
    if (fp->sa.ness.x2240_flashGObj == NULL)
    {
        if (fp->nessVars[0].SpecialN.flashTimerLoop2 != 0)
        {
            fp->nessVars[0].SpecialN.flashTimerLoop2--;
        }
    }
    if (fp->sa.ness.x2240_flashGObj == NULL)
    {
        if (((s32)fp->nessVars[0].SpecialN.flashTimerLoop1 <= 0) && ((s32)fp->nessVars[0].SpecialN.flashTimerLoop2 <= 0))
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALN_END, 0, NULL, 0.0f, 1.0f, 0.0f);
            return;
        }
        if ((s32)fp->x10_action_state_index != AS_NESS_SPECIALN_HOLD_RELEASE)
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALN_HOLD_RELEASE, 0, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        }
    }
    else
    {
        if (func_802AA7E4(fp->sa.ness.x2240_flashGObj) != fighter_gobj)
        {
            fp->sa.ness.x2240_flashGObj = NULL;
            return;
        }
        if ((func_802AA7F0(fp->sa.ness.x2240_flashGObj) == TRUE) && ((s32)fp->x10_action_state_index != AS_NESS_SPECIALN_HOLD_RELEASE))
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALN_HOLD_RELEASE, 0, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        }
    }
}

inline void SetPKFlashAttr(HSD_GObj* fighter_gobj) // Inline to set all variables and match ASM register data //
{
    Fighter* fp = getFighter(fighter_gobj);
    ftNessAttributes* ness_attr = fp->x2D4_specialAttributes;

    fp->nessVars[0].SpecialN.flashTimerLoop1 = ness_attr->x0_PKFLASH_TIMER1_LOOPFRAMES;
    fp->nessVars[0].SpecialN.flashTimerLoop2 = ness_attr->x4_PKFLASH_TIMER2_LOOPFRAMES;
    fp->nessVars[0].SpecialN.gravityDelay = ness_attr->x8_PKFLASH_GRAVITY_DELAY;
    fp->sa.ness.x2240_flashGObj = NULL;
    fp->nessVars[0].SpecialN.flashTimerMin = ness_attr->xC_PKFLASH_MINCHARGEFRAMES;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

// 0x801172F0 //
// https://decomp.me/scratch/SxwKV //
void ftNess_SpecialNEnd_Anim(HSD_GObj* fighter_gobj)   // Ness's grounded PK Flash Release Animation callback //
{
    Fighter* fp = getFighterPlus(fighter_gobj);

    SetPKFlashAttr(fighter_gobj);
    func_8007592C(fp, 0, 0.0f);
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_8008A2BC(fighter_gobj);
    }
}

// 0x80117378 //
// https://decomp.me/scratch/YNAD8 //
void ftNess_SpecialAirNStart_Anim(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Start Animation callback //
{
    Vec3 sp28;
    void (*cb_OnDeath2)(HSD_GObj*);
    void (*cb_OnTakeDamage)(HSD_GObj*);
    f32 zero;
    f32 frameSpeedMul;
    f32 scaleMul;
    HSD_GObj* flash_GObj;
    Fighter* fp;
    Fighter* fighter_data2;

    fp = fighter_gobj->user_data;
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRN_HOLD, 0, NULL, 0.0f, 1.0f, 0.0f);
        fighter_data2 = getFighterPlus(fighter_gobj);
        if (fighter_data2->sa.ness.x2240_flashGObj == NULL)
        {
            func_8000B1CC(fighter_data2->x5E8_fighterBones[24].x0_jobj, NULL, &sp28);
            sp28.z = 0.0f;
            sp28.y += 3.0f * fighter_data2->x34_scale.y;
            flash_GObj = func_802AA8C0(fighter_gobj, &sp28, It_Kind_Ness_PKFlush, fighter_data2->x2C_facing_direction);
            fighter_data2->sa.ness.x2240_flashGObj = flash_GObj;
            if (flash_GObj != NULL)
            {
                fighter_data2->cb.x21E4_callback_OnDeath2 = ftNess_OnDamage;
                fighter_data2->cb.x21DC_callback_OnTakeDamage = ftNess_OnDamage;
            }
        }
        fp->x1968_jumpsUsed = (u8)fp->x110_attr.x168_MaxJumps;
    }
}

// 0x80117458 //
// https://decomp.me/scratch/L7e33 //
void ftNess_SpecialAirNHold_Anim(HSD_GObj* fighter_gobj)   // Ness's aerial PK Flash Charge Animation callback //
{
    Fighter* fp = fighter_gobj->user_data;
    
    if (fp->nessVars[0].SpecialN.flashTimerLoop1 != 0)
    {
        fp->nessVars[0].SpecialN.flashTimerLoop1--;
    }
    if (fp->sa.ness.x2240_flashGObj == NULL)
    {
        if (fp->nessVars[0].SpecialN.flashTimerLoop2 != 0)
        {
            fp->nessVars[0].SpecialN.flashTimerLoop2--;
        }
    }
    if (fp->sa.ness.x2240_flashGObj == NULL)
    {
        if (((s32)fp->nessVars[0].SpecialN.flashTimerLoop1 <= 0) && ((s32)fp->nessVars[0].SpecialN.flashTimerLoop2 <= 0))
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRN_END, 0, NULL, 0.0f, 1.0f, 0.0f);
            return;
        }
        if ((s32)fp->x10_action_state_index != AS_NESS_SPECIALAIRN_HOLD_RELEASE)
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRN_HOLD_RELEASE, 0, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        }
    }
    else
    {
        if (func_802AA7E4(fp->sa.ness.x2240_flashGObj) != fighter_gobj)
        {
            fp->sa.ness.x2240_flashGObj = NULL;
            return;
        }
        if ((func_802AA7F0(fp->sa.ness.x2240_flashGObj) == TRUE) && ((s32)fp->x10_action_state_index != AS_NESS_SPECIALAIRN_HOLD_RELEASE))
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRN_HOLD_RELEASE, 0, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        }
    }
}

// 0x8011758C //
// https://decomp.me/scratch/tSQAQ //
void ftNess_SpecialAirNEnd_Anim(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Release Animation callback //
{
    Fighter* fp = fighter_gobj->user_data;
    ftNessAttributes* ness_attr = getFtSpecialAttrs(fp);
    f32 landingLag;
    s32 filler;

    SetPKFlashAttr(fighter_gobj);
    func_8007592C(fp, 0, 0.0f);
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        landingLag = ness_attr->x1C_PKFLASH_LANDING_LAG;
        if (landingLag == 0.0f)
        {
            func_800CC730(fighter_gobj);
            return;
        }
        func_80096900(fighter_gobj, 1, 0, IS_INTERRUPTIBLE, 1.0f, ness_attr->x1C_PKFLASH_LANDING_LAG);
    }
}

// 0x80117648 //
// https://decomp.me/scratch/z6MCh //
void ftNess_SpecialNStart_IASA(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Start IASA callback //
{
    return;
}

// 0x8011764C //
// https://decomp.me/scratch/4Za9q //
void ftNess_SpecialNHold_IASA(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Charge IASA callback //
{
    HSD_GObj* flash_GObj;
    Fighter* fp;
    s32 phi_r0;

    fp = fighter_gobj->user_data;
    fp->nessVars[0].SpecialN.flashTimerMin--;
    if ((s32)fp->nessVars[0].SpecialN.flashTimerMin <= 0) 
    {
        fp->nessVars[0].SpecialN.flashTimerMin = 0;
        phi_r0 = TRUE;
    }
    else 
    {
        phi_r0 = FALSE;
    }
    if ((phi_r0 == TRUE) && ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == FALSE) && (fighter_gobj != NULL))
    {
        fp = fighter_gobj->user_data;
        if (fp != NULL) 
        {
            if (fp->sa.ness.x2240_flashGObj != NULL) 
            {
                fp->sa.ness.x2240_flashGObj = NULL;
            }
            fp->cb.x21E4_callback_OnDeath2 = NULL;
            fp->cb.x21DC_callback_OnTakeDamage = NULL;
        }
    }
}

// 0x801176C8 //
// https://decomp.me/scratch/GikiI //
void ftNess_SpecialNEnd_IASA(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Release IASA callback //
{
    return;
}

// 0x801176CC //
// https://decomp.me/scratch/3Ea5R //
void ftNess_SpecialAirNStart_IASA(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Start IASA callback //
{
    return;
}

// 0x801176D0 //
// https://decomp.me/scratch/5oIpZ //
void ftNess_SpecialAirNHold_IASA(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Charge IASA callback //
{
    HSD_GObj* flash_GObj;
    Fighter* fp;
    s32 phi_r0;

    fp = fighter_gobj->user_data;
    fp->nessVars[0].SpecialN.flashTimerMin = (s32)(fp->nessVars[0].SpecialN.flashTimerMin - 1);
    if ((s32)fp->nessVars[0].SpecialN.flashTimerMin <= 0)
    {
        fp->nessVars[0].SpecialN.flashTimerMin = 0;
        phi_r0 = TRUE;
    }
    else
    {
        phi_r0 = FALSE;
    }
    if ((phi_r0 == TRUE) && ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == FALSE) && (fighter_gobj != NULL))
    {
        fp = fighter_gobj->user_data;
        if (fp != NULL)
        {
            if (fp->sa.ness.x2240_flashGObj != NULL)
            {
                fp->sa.ness.x2240_flashGObj = NULL;
            }
            fp->cb.x21E4_callback_OnDeath2 = NULL;
            fp->cb.x21DC_callback_OnTakeDamage = NULL;
        }
    }
}

// 0x8011774C //
// https://decomp.me/scratch/zCYgB //
void ftNess_SpecialAirNEnd_IASA(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Release IASA callback //
{
    return;
}

inline void GravityDelay(HSD_GObj* fighter_gobj) // Inline to set remaining frames of gravity delay //
{
    Fighter* fp = fighter_gobj->user_data;
    
    if (fp->nessVars[0].SpecialN.gravityDelay != 0)
    {
        fp->nessVars[0].SpecialN.gravityDelay--;
    }
}

// 0x80117750 //
// https://decomp.me/scratch/YCEpR //
void ftNess_SpecialNStart_Phys(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Start Physics callback //
{
    GravityDelay(fighter_gobj);
    func_80084F3C(fighter_gobj);
}

// 0x80117788 //
// https://decomp.me/scratch/ukjDF //
void ftNess_SpecialNHold_Phys(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Charge Physics callback //
{
    func_80084F3C(fighter_gobj);
}

// 0x801177A8 //
// https://decomp.me/scratch/jSr9q //
void ftNess_SpecialNEnd_Phys(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Release Physics callback //
{
    func_80084F3C(fighter_gobj);
}

// 0x801177C8 //
// https://decomp.me/scratch/pIHN2 //
void ftNess_SpecialAirNStart_Phys(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Start Physics callback //
{
    Fighter* fp = getFighter(fighter_gobj);
    ftNessAttributes* ness_attr = fp->x2D4_specialAttributes;
    f32 airFriction;
    f32 fallAccel;
    f32 terminalVelocity;

    if (fp->nessVars[0].SpecialN.gravityDelay != 0)
    {
        fp->nessVars[0].SpecialN.gravityDelay--;
    }
    else func_8007D494(fp, ness_attr->x14_PKFLASH_FALL_ACCEL, fp->x110_attr.x170_TerminalVelocity);

    airFriction = fp->x110_attr.x180_AerialFriction;
    func_8007CE94(fp, airFriction);
}

// 0x80117828 //
// https://decomp.me/scratch/y7fPm //
void ftNess_SpecialAirNHold_Phys(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Charge Physics callback //
{
    Fighter* fp = getFighter(fighter_gobj);
    ftNessAttributes* ness_attr = fp->x2D4_specialAttributes;
    f32 airFriction;
    f32 fallAccel;
    f32 terminalVelocity;

    if (fp->nessVars[0].SpecialN.gravityDelay != 0)
    {
        fp->nessVars[0].SpecialN.gravityDelay--;
    }
    else func_8007D494(fp, ness_attr->x14_PKFLASH_FALL_ACCEL, fp->x110_attr.x170_TerminalVelocity);

    airFriction = fp->x110_attr.x180_AerialFriction;
    func_8007CE94(fp, airFriction);
}

// 0x80117888 //
// https://decomp.me/scratch/J7MZG //
void ftNess_SpecialAirNEnd_Phys(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Release Physics callback //
{
    Fighter* fp = getFighter(fighter_gobj);
    ftNessAttributes* ness_attr = fp->x2D4_specialAttributes;
    f32 airFriction;
    f32 fallAccel;
    f32 terminalVelocity;

    if (fp->nessVars[0].SpecialN.gravityDelay != 0)
    {
        fp->nessVars[0].SpecialN.gravityDelay--;
    }
    else func_8007D494(fp, ness_attr->x14_PKFLASH_FALL_ACCEL, fp->x110_attr.x170_TerminalVelocity);

    airFriction = fp->x110_attr.x180_AerialFriction;
    func_8007CE94(fp, airFriction);
}

// 0x801178E8 //
// https://decomp.me/scratch/vWsFm //
void ftNess_SpecialNStart_Coll(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Start Collision callback //
{
    Fighter* fp = getFighter(fighter_gobj);

    if (func_80082708(fighter_gobj) == FALSE) 
    {
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRN_START, FTNESS_SPECIALN_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x80117954 //
// https://decomp.me/scratch/6leYl //
void ftNess_SpecialNHold_Coll(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Charge Collision callback //
{
    Fighter* fp = getFighter(fighter_gobj);

    if (func_80082708(fighter_gobj) == FALSE)
    {
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRN_HOLD, FTNESS_SPECIALN_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x801179C0 //
// https://decomp.me/scratch/4QY4r //
void ftNess_SpecialNEnd_Coll(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Release Collision callback //
{
    Fighter* fp = getFighter(fighter_gobj);

    if (func_80082708(fighter_gobj) == FALSE)
    {
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRN_END, FTNESS_SPECIALN_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x80117A2C //
// https://decomp.me/scratch/ODFbf //
void ftNess_SpecialAirNStart_Coll(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Start Collision callback //
{
    Fighter* fp = getFighter(fighter_gobj);

    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        func_8007D7FC(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALN_START, FTNESS_SPECIALN_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x80117A98 //
// https://decomp.me/scratch/qbobW //
void ftNess_SpecialAirNHold_Coll(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Charge Collision callback //
{
    Fighter* fp = getFighter(fighter_gobj);

    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        func_8007D7FC(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALN_HOLD, FTNESS_SPECIALN_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x80117B04 //
// https://decomp.me/scratch/cYdeE //
void ftNess_SpecialAirNEnd_Coll(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Release Collision callback //
{
    Fighter* fp = getFighter(fighter_gobj);

    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        func_8007D7FC(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALN_END, FTNESS_SPECIALN_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}
