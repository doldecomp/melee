#include "ftNess.h"

// 0x80116EBC //
// https://decomp.me/scratch/45pKw //
BOOL ftNess_CheckSpecialNHold(HSD_GObj* fighter_gobj) // Ness PK Flash Charge ASID check //
{
    Fighter* fighter_data;
    s32 ASID;

    if (fighter_gobj != NULL)
    {
        fighter_data = fighter_gobj->user_data;
        if (fighter_data != NULL)
        {
            if (fighter_data->sa.ness.x2240_flashGObj != NULL)
            {
                ASID = fighter_data->x10_action_state_index;
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
    Fighter* fighter_data;

    if (fighter_gobj != NULL)
    {
        fighter_data = fighter_gobj->user_data;
        if (fighter_data != NULL)
        {
            if (fighter_data->sa.ness.x2240_flashGObj != NULL)
            {
                fighter_data->sa.ness.x2240_flashGObj = NULL;
            }
            fighter_data->cb.x21E4_callback_OnDeath2 = NULL;
            fighter_data->cb.x21DC_callback_OnTakeDamage = NULL;
        }
    }
}

extern void func_802AAA50(HSD_GObj*);

// 0x80116F38 //
// https://decomp.me/scratch/HJkeV //
void ftNess_ItemPKFlushSetNULL(HSD_GObj* fighter_gobj)  // Clear PK Flash's owner GObj pointer, Ness's pointer to PK Flash's item GObj, and reset callbacks //
{
    Fighter* fighter_data;

    if (fighter_gobj != NULL)
    {
        fighter_data = fighter_gobj->user_data;
        if (fighter_data != NULL)
        {
            if (fighter_data->sa.ness.x2240_flashGObj != NULL)
            {
                func_802AAA50(fighter_data->sa.ness.x2240_flashGObj);
                fighter_data->sa.ness.x2240_flashGObj = NULL;
            }
            fighter_data->cb.x21E4_callback_OnDeath2 = NULL;
            fighter_data->cb.x21DC_callback_OnTakeDamage = NULL;
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
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;
    Fighter* temp_fighter;

    fighter_data = getFighterPlus(fighter_gobj);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALN_START, 0, NULL, 0.0f, 1.0f, 0.0f);

    fighter_data->x220C_ftcmd_var3 = 0;
    fighter_data->x2208_ftcmd_var2 = 0;
    fighter_data->x2204_ftcmd_var1 = 0;
    fighter_data->x2200_ftcmd_var0 = 0;

    temp_fighter = fighter_gobj->user_data;
    ness_attr = getFtSpecialAttrs(temp_fighter);

    temp_fighter->x2340_stateVar1 = (s32)ness_attr->x0_PKFLASH_TIMER1_MINCHARGEFRAMES;
    temp_fighter->x2344_stateVar2 = (s32)ness_attr->x4_PKFLASH_TIMER2_LOOPFRAMES;
    temp_fighter->x2348_stateVar3 = (s32)ness_attr->x8_PKFLASH_FALLING_ACCEL_DELAY;

    temp_fighter->sa.ness.x2240_flashGObj = NULL;
    temp_fighter->x234C_stateVar4 = (s32)ness_attr->xC_PKFLASH_RELEASE_UNK;
    temp_fighter->cb.x21E4_callback_OnDeath2 = NULL;
    temp_fighter->cb.x21DC_callback_OnTakeDamage = NULL;
    func_8006EBA4(fighter_gobj);
}

// 0x80117034 //
// https://decomp.me/scratch/ZjUdo
void ftNess_SpecialAirNStart_Action(HSD_GObj* fighter_gobj)  // Ness's aerial PK Flash Start Action State handler //
{
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;
    Fighter* temp_fighter;

    fighter_data = getFighterPlus(fighter_gobj);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRN_START, 0, NULL, 0.0f, 1.0f, 0.0f);

    fighter_data->x220C_ftcmd_var3 = 0;
    fighter_data->x2208_ftcmd_var2 = 0;
    fighter_data->x2204_ftcmd_var1 = 0;
    fighter_data->x2200_ftcmd_var0 = 0;
    fighter_data->x80_self_vel.y = 0.0f;

    temp_fighter = fighter_gobj->user_data;
    ness_attr = getFtSpecialAttrs(temp_fighter);

    temp_fighter->x2340_stateVar1 = (s32)ness_attr->x0_PKFLASH_TIMER1_MINCHARGEFRAMES;
    temp_fighter->x2344_stateVar2 = (s32)ness_attr->x4_PKFLASH_TIMER2_LOOPFRAMES;
    temp_fighter->x2348_stateVar3 = (s32)ness_attr->x8_PKFLASH_FALLING_ACCEL_DELAY;

    temp_fighter->sa.ness.x2240_flashGObj = NULL;

    temp_fighter->x234C_stateVar4 = (s32)ness_attr->xC_PKFLASH_RELEASE_UNK;

    temp_fighter->cb.x21E4_callback_OnDeath2 = NULL;
    temp_fighter->cb.x21DC_callback_OnTakeDamage = NULL;

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
    Fighter* fighter_data;
    Fighter* fighter_data2;

    fighter_data = fighter_gobj->user_data;
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
        fighter_data->x1968_jumpsUsed = (u8)fighter_data->x110_attr.x168_MaxJumps;
    }
}

extern HSD_GObj* func_802AA7E4(HSD_GObj*);
extern s32 func_802AA7F0(HSD_GObj*);

// 0x801171BC //
// https://decomp.me/scratch/W8wUK //
void ftNess_SpecialNHold_Anim(HSD_GObj* fighter_gobj)   // Ness's grounded PK Flash Charge Animation callback //
{
    s32 flashTimerMin;
    s32 flashTimerDelay;
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    flashTimerMin = fighter_data->x2340_stateVar1;
    if (flashTimerMin != 0)
    {
        fighter_data->x2340_stateVar1 = (s32)(flashTimerMin - 1);
    }
    if (fighter_data->sa.ness.x2240_flashGObj == NULL)
    {
        flashTimerDelay = fighter_data->x2344_stateVar2;
        if (flashTimerDelay != 0)
        {
            fighter_data->x2344_stateVar2 = (s32)(flashTimerDelay - 1);
        }
    }
    if (fighter_data->sa.ness.x2240_flashGObj == NULL)
    {
        if (((s32)fighter_data->x2340_stateVar1 <= 0) && ((s32)fighter_data->x2344_stateVar2 <= 0))
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALN_END, 0, NULL, 0.0f, 1.0f, 0.0f);
            return;
        }
        if ((s32)fighter_data->x10_action_state_index != AS_NESS_SPECIALN_HOLD_RELEASE)
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALN_HOLD_RELEASE, 0, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
        }
    }
    else
    {
        if (func_802AA7E4(fighter_data->sa.ness.x2240_flashGObj) != fighter_gobj)
        {
            fighter_data->sa.ness.x2240_flashGObj = NULL;
            return;
        }
        if ((func_802AA7F0(fighter_data->sa.ness.x2240_flashGObj) == 1) && ((s32)fighter_data->x10_action_state_index != AS_NESS_SPECIALN_HOLD_RELEASE))
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALN_HOLD_RELEASE, 0, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
        }
    }
}

inline void SetPKFlashAttr(HSD_GObj* fighter_gobj) // Inline to set all variables and match ASM register data //
{
    Fighter* fighter_data = getFighter(fighter_gobj);
    ftNessAttributes* ness_attr = fighter_data->x2D4_specialAttributes;
    fighter_data->x2340_stateVar1 = ness_attr->x0_PKFLASH_TIMER1_MINCHARGEFRAMES;
    fighter_data->x2344_stateVar2 = ness_attr->x4_PKFLASH_TIMER2_LOOPFRAMES;
    fighter_data->x2348_stateVar3 = ness_attr->x8_PKFLASH_FALLING_ACCEL_DELAY;
    fighter_data->sa.ness.x2240_flashGObj = NULL;
    fighter_data->x234C_stateVar4 = ness_attr->xC_PKFLASH_RELEASE_UNK;
    fighter_data->cb.x21E4_callback_OnDeath2 = NULL;
    fighter_data->cb.x21DC_callback_OnTakeDamage = NULL;
}

// 0x801172F0 //
// https://decomp.me/scratch/SxwKV //
void ftNess_SpecialNEnd_Anim(HSD_GObj* fighter_gobj)   // Ness's grounded PK Flash Release Animation callback //
{
    Fighter* fighter_data = getFighterPlus(fighter_gobj);

    SetPKFlashAttr(fighter_gobj);
    func_8007592C(fighter_data, 0, 0.0f);
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
    Fighter* fighter_data;
    Fighter* fighter_data2;

    fighter_data = fighter_gobj->user_data;
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
        fighter_data->x1968_jumpsUsed = (u8)fighter_data->x110_attr.x168_MaxJumps;
    }
}

// 0x80117458 //
// https://decomp.me/scratch/L7e33 //
void ftNess_SpecialAirNHold_Anim(HSD_GObj* fighter_gobj)   // Ness's aerial PK Flash Charge Animation callback //
{
    s32 flashTimerMin;
    s32 flashTimerDelay;
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    flashTimerMin = fighter_data->x2340_stateVar1;
    if (flashTimerMin != 0)
    {
        fighter_data->x2340_stateVar1 = (s32)(flashTimerMin - 1);
    }
    if (fighter_data->sa.ness.x2240_flashGObj == NULL)
    {
        flashTimerDelay = fighter_data->x2344_stateVar2;
        if (flashTimerDelay != 0)
        {
            fighter_data->x2344_stateVar2 = (s32)(flashTimerDelay - 1);
        }
    }
    if (fighter_data->sa.ness.x2240_flashGObj == NULL)
    {
        if (((s32)fighter_data->x2340_stateVar1 <= 0) && ((s32)fighter_data->x2344_stateVar2 <= 0))
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRN_END, 0, NULL, 0.0f, 1.0f, 0.0f);
            return;
        }
        if ((s32)fighter_data->x10_action_state_index != AS_NESS_SPECIALAIRN_HOLD_RELEASE)
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRN_HOLD_RELEASE, 0, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
        }
    }
    else
    {
        if (func_802AA7E4(fighter_data->sa.ness.x2240_flashGObj) != fighter_gobj)
        {
            fighter_data->sa.ness.x2240_flashGObj = NULL;
            return;
        }
        if ((func_802AA7F0(fighter_data->sa.ness.x2240_flashGObj) == TRUE) && ((s32)fighter_data->x10_action_state_index != AS_NESS_SPECIALAIRN_HOLD_RELEASE))
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRN_HOLD_RELEASE, 0, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
        }
    }
}

// 0x8011758C //
// https://decomp.me/scratch/tSQAQ //
void ftNess_SpecialAirNEnd_Anim(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Release Animation callback //
{
    Fighter* fighter_data = fighter_gobj->user_data;
    ftNessAttributes* ness_attr = getFtSpecialAttrs(fighter_data);
    f32 landingLag;
    s32 filler;

    SetPKFlashAttr(fighter_gobj);
    func_8007592C(fighter_data, 0, 0.0f);
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        landingLag = ness_attr->x1C_PKFLASH_LANDING_LAG;
        if (landingLag == 0.0f)
        {
            func_800CC730(fighter_gobj);
            return;
        }
        func_80096900(fighter_gobj, 1, 0, 1, 1.0f, ness_attr->x1C_PKFLASH_LANDING_LAG);
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
    Fighter* fighter_data;
    s32 phi_r0;

    fighter_data = fighter_gobj->user_data;
    fighter_data->x234C_stateVar4 = (s32)(fighter_data->x234C_stateVar4 - 1);
    if ((s32)fighter_data->x234C_stateVar4 <= 0) 
    {
        fighter_data->x234C_stateVar4 = 0;
        phi_r0 = TRUE;
    }
    else 
    {
        phi_r0 = FALSE;
    }
    if ((phi_r0 == TRUE) && ((fighter_data->input.x65C & B_BUTTON_HELD) == FALSE) && (fighter_gobj != NULL))
    {
        fighter_data = fighter_gobj->user_data;
        if (fighter_data != NULL) 
        {
            if (fighter_data->sa.ness.x2240_flashGObj != NULL) 
            {
                fighter_data->sa.ness.x2240_flashGObj = NULL;
            }
            fighter_data->cb.x21E4_callback_OnDeath2 = NULL;
            fighter_data->cb.x21DC_callback_OnTakeDamage = NULL;
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
    Fighter* fighter_data;
    s32 phi_r0;

    fighter_data = fighter_gobj->user_data;
    fighter_data->x234C_stateVar4 = (s32)(fighter_data->x234C_stateVar4 - 1);
    if ((s32)fighter_data->x234C_stateVar4 <= 0)
    {
        fighter_data->x234C_stateVar4 = 0;
        phi_r0 = TRUE;
    }
    else
    {
        phi_r0 = FALSE;
    }
    if ((phi_r0 == TRUE) && ((fighter_data->input.x65C & B_BUTTON_HELD) == FALSE) && (fighter_gobj != NULL))
    {
        fighter_data = fighter_gobj->user_data;
        if (fighter_data != NULL)
        {
            if (fighter_data->sa.ness.x2240_flashGObj != NULL)
            {
                fighter_data->sa.ness.x2240_flashGObj = NULL;
            }
            fighter_data->cb.x21E4_callback_OnDeath2 = NULL;
            fighter_data->cb.x21DC_callback_OnTakeDamage = NULL;
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
    Fighter* fighter_data;
    s32 gravityDelay;

    fighter_data = fighter_gobj->user_data;
    gravityDelay = fighter_data->x2348_stateVar3;
    if (gravityDelay != 0)
    {
        fighter_data->x2348_stateVar3 = (s32)(gravityDelay - 1);
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
    Fighter* fighter_data = getFighter(fighter_gobj);
    s32 gravityDelay = fighter_data->x2348_stateVar3;
    ftNessAttributes* ness_attr = fighter_data->x2D4_specialAttributes;
    f32 airFriction;
    f32 fallAccel;
    f32 terminalVelocity;

    if (gravityDelay != 0)
    {
        fighter_data->x2348_stateVar3 = (s32)(gravityDelay - 1);
        goto block_friction;
    }
    func_8007D494(fighter_data, ness_attr->x14_PKFLASH_FALL_ACCEL, fighter_data->x110_attr.x170_TerminalVelocity);

block_friction:
    airFriction = fighter_data->x110_attr.x180_AerialFriction;
    func_8007CE94(fighter_data, airFriction);
}

// 0x80117828 //
// https://decomp.me/scratch/y7fPm //
void ftNess_SpecialAirNHold_Phys(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Charge Physics callback //
{
    Fighter* fighter_data = getFighter(fighter_gobj);
    s32 gravityDelay = fighter_data->x2348_stateVar3;
    ftNessAttributes* ness_attr = fighter_data->x2D4_specialAttributes;
    f32 airFriction;
    f32 fallAccel;
    f32 terminalVelocity;

    if (gravityDelay != 0)
    {
        fighter_data->x2348_stateVar3 = (s32)(gravityDelay - 1);
        goto block_friction;
    }
    func_8007D494(fighter_data, ness_attr->x14_PKFLASH_FALL_ACCEL, fighter_data->x110_attr.x170_TerminalVelocity);

block_friction:
    airFriction = fighter_data->x110_attr.x180_AerialFriction;
    func_8007CE94(fighter_data, airFriction);
}

// 0x80117888 //
// https://decomp.me/scratch/J7MZG //
void ftNess_SpecialAirNEnd_Phys(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Release Physics callback //
{
    Fighter* fighter_data = getFighter(fighter_gobj);
    s32 gravityDelay = fighter_data->x2348_stateVar3;
    ftNessAttributes* ness_attr = fighter_data->x2D4_specialAttributes;
    f32 airFriction;
    f32 fallAccel;
    f32 terminalVelocity;

    if (gravityDelay != 0)
    {
        fighter_data->x2348_stateVar3 = (s32)(gravityDelay - 1);
        goto block_friction;
    }
    func_8007D494(fighter_data, ness_attr->x14_PKFLASH_FALL_ACCEL, fighter_data->x110_attr.x170_TerminalVelocity);

block_friction:
    airFriction = fighter_data->x110_attr.x180_AerialFriction;
    func_8007CE94(fighter_data, airFriction);
}

// 0x801178E8 //
// https://decomp.me/scratch/vWsFm //
void ftNess_SpecialNStart_Coll(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Start Collision callback //
{
    Fighter* fighter_data = getFighter(fighter_gobj);

    if (func_80082708(fighter_gobj) == FALSE) 
    {
        func_8007D5D4(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRN_START, NESS_SPECIALN_COLL_FLAG, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x80117954 //
// https://decomp.me/scratch/6leYl //
void ftNess_SpecialNHold_Coll(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Charge Collision callback //
{
    Fighter* fighter_data = getFighter(fighter_gobj);

    if (func_80082708(fighter_gobj) == FALSE)
    {
        func_8007D5D4(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRN_HOLD, NESS_SPECIALN_COLL_FLAG, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x801179C0 //
// https://decomp.me/scratch/4QY4r //
void ftNess_SpecialNEnd_Coll(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Release Collision callback //
{
    Fighter* fighter_data = getFighter(fighter_gobj);

    if (func_80082708(fighter_gobj) == FALSE)
    {
        func_8007D5D4(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRN_END, NESS_SPECIALN_COLL_FLAG, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x80117A2C //
// https://decomp.me/scratch/ODFbf //
void ftNess_SpecialAirNStart_Coll(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Start Collision callback //
{
    Fighter* fighter_data = getFighter(fighter_gobj);

    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        func_8007D7FC(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALN_START, NESS_SPECIALN_COLL_FLAG, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x80117A98 //
// https://decomp.me/scratch/qbobW //
void ftNess_SpecialAirNHold_Coll(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Charge Collision callback //
{
    Fighter* fighter_data = getFighter(fighter_gobj);

    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        func_8007D7FC(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALN_HOLD, NESS_SPECIALN_COLL_FLAG, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

// 0x80117B04 //
// https://decomp.me/scratch/cYdeE //
void ftNess_SpecialAirNEnd_Coll(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Release Collision callback //
{
    Fighter* fighter_data = getFighter(fighter_gobj);

    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        func_8007D7FC(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALN_END, NESS_SPECIALN_COLL_FLAG, NULL, fighter_data->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}