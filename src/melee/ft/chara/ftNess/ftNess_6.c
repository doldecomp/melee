#include "ftNess.h"

// 0x80116D74 //
// https://decomp.me/scratch/5NxzS //
void lbl_80116D74(HSD_GObj* fighter_gobj) // Ness's grounded PK Fire Animation callback //
{
    if (func_8006F238(fighter_gobj) == 0) 
    {
        func_8008A2BC(fighter_gobj);
    }
}

// 0x80116DB0 //
// https://decomp.me/scratch/iFFHn //
void lbl_80116DB0(HSD_GObj* fighter_gobj) // Ness's aerial PK Fire Animation callback //
{
    if (func_8006F238(fighter_gobj) == 0)
    {
        func_800CC730(fighter_gobj);
    }
}

// 0x80116DEC //
// https://decomp.me/scratch/iCZHk //
void lbl_80116DEC(HSD_GObj* fighter_gobj) // Ness's grounded PK Fire Physics callback //
{
    func_80084F3C(fighter_gobj);
}

// 0x80116E0C //
// https://decomp.me/scratch/ATut0 //
void lbl_80116E0C(HSD_GObj* fighter_gobj) // Ness's aerial PK Fire Physics callback //
{
    func_80084EEC(fighter_gobj);
}

// 0x80116E2C //
// https://decomp.me/scratch/gi1NE //
void lbl_80116E2C(HSD_GObj* fighter_gobj) // Ness's grounded PK Fire Collision callback //
{
    if (func_800827A0(fighter_gobj) == 0) 
    {
        func_800CC730(fighter_gobj);
    }
}

// 0x80116E68 //
// https://decomp.me/scratch/AEWUO //
void lbl_80116E68(HSD_GObj* fighter_gobj) // Ness's aerial PK Fire Collision callback //
{
    s32 filler[2];
    Fighter* fighter_data = fighter_gobj->user_data;
    ftNessAttributes* ness_attr;

    ness_attr = fighter_data->x2D4_specialAttributes;
    if (func_80081D0C(fighter_gobj) != 0)
    {
        func_800D5CB0(fighter_gobj, 0, ness_attr->x38_LANDING_LAG);
    }
}

// 0x80116EBC //
// https://decomp.me/scratch/45pKw //
s32 func_80116EBC(HSD_GObj* fighter_gobj) // Ness PK Flash Charge ASID check //
{
    Fighter* fighter_data;
    int ASID;

    if (fighter_gobj != 0)
    {
        fighter_data = fighter_gobj->user_data;
        if (fighter_data != 0)
        {
            if (fighter_data->sa.ness.x2240 != 0U)
            {
                ASID = fighter_data->x10_action_state_index;
                if (ASID == 0x15D || ASID == 0x161)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

// 0x80116F00 //
// https://decomp.me/scratch/84rSJ //
void func_80116F00(HSD_GObj* fighter_gobj) // Clear Ness's callbacks and PK Flash's item GObj pointer //
{
    Fighter* fighter_data;

    if (fighter_gobj != 0U)
    {
        fighter_data = fighter_gobj->user_data;
        if (fighter_data != 0U)
        {
            if ((u32)fighter_data->sa.ness.x2240 != 0U)
            {
                fighter_data->sa.ness.x2240 = 0U;
            }
            fighter_data->cb.x21E4_callback_OnDeath2 = 0;
            fighter_data->cb.x21DC_callback_OnTakeDamage = 0;
        }
    }
}

extern void func_802AAA50(HSD_GObj*);

// 0x80116F38 //
// https://decomp.me/scratch/HJkeV //
void func_80116F38(HSD_GObj* fighter_gobj)  // Clear PK Flash's owner GObj pointer, Ness's pointer to PK Flash's item GObj, and reset callbacks //
{
    Fighter* fighter_data;

    if (fighter_gobj != 0U)
    {
        fighter_data = fighter_gobj->user_data;
        if (fighter_data != 0U)
        {
            if (fighter_data->sa.ness.x2240 != 0U)
            {
                func_802AAA50(fighter_data->sa.ness.x2240);
                fighter_data->sa.ness.x2240 = 0U;
            }
            fighter_data->cb.x21E4_callback_OnDeath2 = 0;
            fighter_data->cb.x21DC_callback_OnTakeDamage = 0;
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
void func_80116F94(HSD_GObj* fighter_gobj)  // Ness's grounded PK Flash Start Action State handler //
{
    s32 filler[6];
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;
    Fighter* temp_fighter;

    fighter_data = fighter_gobj->user_data;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15C, 0, 0, 0.0f, 1.0f, 0.0f);
    fighter_data->x220C_ftcmd_var3 = 0;
    fighter_data->x2208_ftcmd_var2 = 0;
    fighter_data->x2204_ftcmd_var1 = 0;
    fighter_data->x2200_ftcmd_var0 = 0;
    temp_fighter = fighter_gobj->user_data;
    ness_attr = temp_fighter->x2D4_specialAttributes;
    temp_fighter->x2340_stateVar1 = (s32)ness_attr->x0_PKFLASH_TIMER1_MINCHARGEFRAMES;
    temp_fighter->x2344_stateVar2 = (s32)ness_attr->x4_PKFLASH_TIMER2_LOOPFRAMES;
    temp_fighter->x2348_stateVar3 = (s32)ness_attr->x8_FALLING_ACCELERATION_DELAY;
    temp_fighter->sa.ness.x2240 = 0;
    temp_fighter->x234C_stateVar4 = (s32)ness_attr->xC_RELEASE_UNK;
    temp_fighter->cb.x21E4_callback_OnDeath2 = 0;
    temp_fighter->cb.x21DC_callback_OnTakeDamage = 0;
    func_8006EBA4(fighter_gobj);
}

// 0x80117034 //
// https://decomp.me/scratch/ZjUdo
void func_80117034(HSD_GObj* fighter_gobj)  // Ness's aerial PK Flash Start Action State handler //
{
    s32 filler[6];
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;
    Fighter* temp_fighter;

    fighter_data = fighter_gobj->user_data;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x160, 0, 0, 0.0f, 1.0f, 0.0f);
    fighter_data->x220C_ftcmd_var3 = 0;
    fighter_data->x2208_ftcmd_var2 = 0;
    fighter_data->x2204_ftcmd_var1 = 0;
    fighter_data->x2200_ftcmd_var0 = 0;
    fighter_data->x80_self_vel.y = 0.0f;
    temp_fighter = fighter_gobj->user_data;
    ness_attr = temp_fighter->x2D4_specialAttributes;
    temp_fighter->x2340_stateVar1 = (s32)ness_attr->x0_PKFLASH_TIMER1_MINCHARGEFRAMES;
    temp_fighter->x2344_stateVar2 = (s32)ness_attr->x4_PKFLASH_TIMER2_LOOPFRAMES;
    temp_fighter->x2348_stateVar3 = (s32)ness_attr->x8_FALLING_ACCELERATION_DELAY;
    temp_fighter->sa.ness.x2240 = 0;
    temp_fighter->x234C_stateVar4 = (s32)ness_attr->xC_RELEASE_UNK;
    temp_fighter->cb.x21E4_callback_OnDeath2 = 0;
    temp_fighter->cb.x21DC_callback_OnTakeDamage = 0;
    func_8006EBA4(fighter_gobj);
}

extern HSD_GObj* func_802AA8C0(HSD_GObj*, Vec3*, s32, f32);

// 0x801170DC //
// https://decomp.me/scratch/JhiVu // 
void lbl_801170DC(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Start Animation callback //
{
    Vec3 sp28;
    s32 filler[7];
    HSD_GObj* flash_GObj;
    Fighter* fighter_data;
    Fighter* fighter_data2;

    fighter_data = fighter_gobj->user_data;
    if (func_8006F238(fighter_gobj) == 0)
    {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15D, 0, 0, 0.0f, 1.0f, 0.0f);
        fighter_data2 = fighter_gobj->user_data;
        if ((u32)fighter_data2->sa.ness.x2240 == 0U) 
        {
            func_8000B1CC(fighter_data2->x5E8_fighterBones[24].x0_jobj, 0, &sp28);
            sp28.z = 0.0f;
            sp28.y += 3.0f * fighter_data2->x34_scale.y;
            flash_GObj = func_802AA8C0(fighter_gobj, &sp28, 0x44, fighter_data2->x2C_facing_direction);
            fighter_data2->sa.ness.x2240 = flash_GObj;
            if (flash_GObj != 0) 
            {
                fighter_data2->cb.x21E4_callback_OnDeath2 = func_801148F8;
                fighter_data2->cb.x21DC_callback_OnTakeDamage = func_801148F8;
            }
        }
        fighter_data->x1968_jumpsUsed = (u8)fighter_data->x110_attr.x168_MaxJumps;
    }
}

extern HSD_GObj* func_802AA7E4(HSD_GObj*);
extern s32 func_802AA7F0(HSD_GObj*);

// 0x801171BC //
// https://decomp.me/scratch/W8wUK //
void lbl_801171BC(HSD_GObj* fighter_gobj)   // Ness's grounded PK Flash Charge Animation callback //
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
    if ((u32)fighter_data->sa.ness.x2240 == 0U)
    {
        flashTimerDelay = fighter_data->x2344_stateVar2;
        if (flashTimerDelay != 0)
        {
            fighter_data->x2344_stateVar2 = (s32)(flashTimerDelay - 1);
        }
    }
    if ((u32)fighter_data->sa.ness.x2240 == 0U)
    {
        if (((s32)fighter_data->x2340_stateVar1 <= 0) && ((s32)fighter_data->x2344_stateVar2 <= 0))
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15F, 0, 0, 0.0f, 1.0f, 0.0f);
            return;
        }
        if ((s32)fighter_data->x10_action_state_index != 0x15E)
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15E, 0, 0, fighter_data->x894, 1.0f, 0.0f);
        }
    }
    else
    {
        if (func_802AA7E4(fighter_data->sa.ness.x2240) != fighter_gobj)
        {
            fighter_data->sa.ness.x2240 = 0U;
            return;
        }
        if ((func_802AA7F0(fighter_data->sa.ness.x2240) == 1) && ((s32)fighter_data->x10_action_state_index != 0x15E))
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15E, 0, 0, fighter_data->x894, 1.0f, 0.0f);
        }
    }
}

void SetPKFlashAttr(HSD_GObj* fighter_gobj) // Inline to set all variables and match ASM register data //
{
    Fighter* fighter_data = fighter_gobj->user_data;
    ftNessAttributes* ness_attr = fighter_data->x2D4_specialAttributes;
    fighter_data->x2340_stateVar1 = ness_attr->x0_PKFLASH_TIMER1_MINCHARGEFRAMES;
    fighter_data->x2344_stateVar2 = ness_attr->x4_PKFLASH_TIMER2_LOOPFRAMES;
    fighter_data->x2348_stateVar3 = ness_attr->x8_FALLING_ACCELERATION_DELAY;
    fighter_data->sa.ness.x2240 = 0;
    fighter_data->x234C_stateVar4 = ness_attr->xC_RELEASE_UNK;
    fighter_data->cb.x21E4_callback_OnDeath2 = 0;
    fighter_data->cb.x21DC_callback_OnTakeDamage = 0;
}

// 0x801172F0 //
// https://decomp.me/scratch/SxwKV //
void lbl_801172F0(HSD_GObj* fighter_gobj)   // Ness's grounded PK Flash Release Animation callback //
{
    Fighter* fighter_data = fighter_gobj->user_data;
    s32 filler[4];

    SetPKFlashAttr(fighter_gobj);
    func_8007592C(fighter_data, 0, 0.0f);
    if (func_8006F238(fighter_gobj) == 0)
    {
        func_8008A2BC(fighter_gobj);
    }
}

// 0x80117378 //
// https://decomp.me/scratch/YNAD8 //
void lbl_80117378(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Start Animation callback //
{
    Vec3 sp28;
    s32 filler[7];
    HSD_GObj* flash_GObj;
    Fighter* fighter_data;
    Fighter* fighter_data2;

    fighter_data = fighter_gobj->user_data;
    if (func_8006F238(fighter_gobj) == 0)
    {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x161, 0, 0, 0.0f, 1.0f, 0.0f);
        fighter_data2 = fighter_gobj->user_data;
        if ((u32)fighter_data2->sa.ness.x2240 == 0U)
        {
            func_8000B1CC(fighter_data2->x5E8_fighterBones[24].x0_jobj, 0, &sp28);
            sp28.z = 0.0f;
            sp28.y += 3.0f * fighter_data2->x34_scale.y;
            flash_GObj = func_802AA8C0(fighter_gobj, &sp28, 0x44, fighter_data2->x2C_facing_direction);
            fighter_data2->sa.ness.x2240 = flash_GObj;
            if (flash_GObj != 0)
            {
                fighter_data2->cb.x21E4_callback_OnDeath2 = func_801148F8;
                fighter_data2->cb.x21DC_callback_OnTakeDamage = func_801148F8;
            }
        }
        fighter_data->x1968_jumpsUsed = (u8)fighter_data->x110_attr.x168_MaxJumps;
    }
}

// 0x80117458 //
// https://decomp.me/scratch/L7e33 //
void lbl_80117458(HSD_GObj* fighter_gobj)   // Ness's aerial PK Flash Charge Animation callback //
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
    if ((u32)fighter_data->sa.ness.x2240 == 0U)
    {
        flashTimerDelay = fighter_data->x2344_stateVar2;
        if (flashTimerDelay != 0)
        {
            fighter_data->x2344_stateVar2 = (s32)(flashTimerDelay - 1);
        }
    }
    if ((u32)fighter_data->sa.ness.x2240 == 0U)
    {
        if (((s32)fighter_data->x2340_stateVar1 <= 0) && ((s32)fighter_data->x2344_stateVar2 <= 0))
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x163, 0, 0, 0.0f, 1.0f, 0.0f);
            return;
        }
        if ((s32)fighter_data->x10_action_state_index != 0x162)
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x162, 0, 0, fighter_data->x894, 1.0f, 0.0f);
        }
    }
    else
    {
        if (func_802AA7E4(fighter_data->sa.ness.x2240) != fighter_gobj)
        {
            fighter_data->sa.ness.x2240 = 0U;
            return;
        }
        if ((func_802AA7F0(fighter_data->sa.ness.x2240) == 1) && ((s32)fighter_data->x10_action_state_index != 0x162))
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, 0x162, 0, 0, fighter_data->x894, 1.0f, 0.0f);
        }
    }
}

// 0x8011758C //
// https://decomp.me/scratch/tSQAQ //
void lbl_8011758C(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Release Animation callback //
{
    Fighter* fighter_data = fighter_gobj->user_data;
    ftNessAttributes* ness_attr = fighter_data->x2D4_specialAttributes;
    s32 filler[6];

    SetPKFlashAttr(fighter_gobj);
    func_8007592C(fighter_data, 0, 0.0f);
    if (func_8006F238(fighter_gobj) == 0)
    {
        if (ness_attr->x1C_LANDING_LAG == 0.0f)
        {
            func_800CC730(fighter_gobj);
            return;
        }
        func_80096900(fighter_gobj, 1, 0, 1, 1.0f, ness_attr->x1C_LANDING_LAG);
    }
}

// 0x80117648 //
// https://decomp.me/scratch/z6MCh //
void lbl_80117648(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Start IASA callback //
{
    return;
}

// 0x8011764C //
// https://decomp.me/scratch/4Za9q //
void lbl_8011764C(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Charge IASA callback //
{
    HSD_GObj* flash_GObj;
    Fighter* fighter_data;
    s32 phi_r0;

    fighter_data = fighter_gobj->user_data;
    fighter_data->x234C_stateVar4 = (s32)(fighter_data->x234C_stateVar4 - 1);
    if ((s32)fighter_data->x234C_stateVar4 <= 0) 
    {
        fighter_data->x234C_stateVar4 = 0;
        phi_r0 = 1;
    }
    else 
    {
        phi_r0 = 0;
    }
    if ((phi_r0 == 1) && ((fighter_data->input.x65C & 0x200) == 0) && (fighter_gobj != 0U))
    {
        fighter_data = fighter_gobj->user_data;
        if (fighter_data != 0U) 
        {
            if ((u32)fighter_data->sa.ness.x2240 != 0U) 
            {
                fighter_data->sa.ness.x2240 = 0U;
            }
            fighter_data->cb.x21E4_callback_OnDeath2 = 0;
            fighter_data->cb.x21DC_callback_OnTakeDamage = 0;
        }
    }
}

// 0x801176C8 //
// https://decomp.me/scratch/GikiI //
void lbl_801176C8(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Release IASA callback //
{
    return;
}

// 0x801176CC //
// https://decomp.me/scratch/3Ea5R //
void lbl_801176CC(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Start IASA callback //
{
    return;
}

// 0x801176D0 //
// https://decomp.me/scratch/5oIpZ //
void lbl_801176D0(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Charge IASA callback //
{
    HSD_GObj* flash_GObj;
    Fighter* fighter_data;
    s32 phi_r0;

    fighter_data = fighter_gobj->user_data;
    fighter_data->x234C_stateVar4 = (s32)(fighter_data->x234C_stateVar4 - 1);
    if ((s32)fighter_data->x234C_stateVar4 <= 0)
    {
        fighter_data->x234C_stateVar4 = 0;
        phi_r0 = 1;
    }
    else
    {
        phi_r0 = 0;
    }
    if ((phi_r0 == 1) && ((fighter_data->input.x65C & 0x200) == 0) && (fighter_gobj != 0U))
    {
        fighter_data = fighter_gobj->user_data;
        if (fighter_data != 0U)
        {
            if ((u32)fighter_data->sa.ness.x2240 != 0U)
            {
                fighter_data->sa.ness.x2240 = 0U;
            }
            fighter_data->cb.x21E4_callback_OnDeath2 = 0;
            fighter_data->cb.x21DC_callback_OnTakeDamage = 0;
        }
    }
}

// 0x8011774C //
// https://decomp.me/scratch/zCYgB //
void lbl_8011774C(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Release IASA callback //
{
    return;
}

void GravityDelay(HSD_GObj* fighter_gobj) // Inline to set remaining frames of gravity delay //
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
void lbl_80117750(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Start Physics callback //
{
    GravityDelay(fighter_gobj);
    func_80084F3C(fighter_gobj);
}

// 0x80117788 //
// https://decomp.me/scratch/ukjDF //
void lbl_80117788(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Charge Physics callback //
{
    func_80084F3C(fighter_gobj);
}

// 0x801177A8 //
// https://decomp.me/scratch/jSr9q //
void lbl_801177A8(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Release Physics callback //
{
    func_80084F3C(fighter_gobj);
}

// 0x801177C8 //
// https://decomp.me/scratch/pIHN2 //
void lbl_801177C8(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Start Physics callback //
{
    Fighter* fighter_data = fighter_gobj->user_data;
    s32 gravityDelay = fighter_data->x2348_stateVar3;
    ftNessAttributes* ness_attr = fighter_data->x2D4_specialAttributes;
    f32 airFriction;
    s32 filler[2];

    if (gravityDelay != 0)
    {
        fighter_data->x2348_stateVar3 = (s32)(gravityDelay - 1);
        goto block_friction;
    }
    func_8007D494(fighter_data, ness_attr->x14_FALL_ACCELERATION, fighter_data->x110_attr.x170_TerminalVelocity);

block_friction:
    airFriction = fighter_data->x110_attr.x180_AerialFriction;
    func_8007CE94(fighter_data, airFriction);
}

// 0x80117828 //
// https://decomp.me/scratch/y7fPm //
void lbl_80117828(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Charge Physics callback //
{
    Fighter* fighter_data = fighter_gobj->user_data;
    s32 gravityDelay = fighter_data->x2348_stateVar3;
    ftNessAttributes* ness_attr = fighter_data->x2D4_specialAttributes;
    f32 airFriction;
    s32 filler[2];

    if (gravityDelay != 0)
    {
        fighter_data->x2348_stateVar3 = (s32)(gravityDelay - 1);
        goto block_friction;
    }
    func_8007D494(fighter_data, ness_attr->x14_FALL_ACCELERATION, fighter_data->x110_attr.x170_TerminalVelocity);

block_friction:
    airFriction = fighter_data->x110_attr.x180_AerialFriction;
    func_8007CE94(fighter_data, airFriction);
}

// 0x80117888 //
// https://decomp.me/scratch/J7MZG //
void lbl_80117888(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Release Physics callback //
{
    Fighter* fighter_data = fighter_gobj->user_data;
    s32 gravityDelay = fighter_data->x2348_stateVar3;
    ftNessAttributes* ness_attr = fighter_data->x2D4_specialAttributes;
    f32 airFriction;
    s32 filler[2];

    if (gravityDelay != 0)
    {
        fighter_data->x2348_stateVar3 = (s32)(gravityDelay - 1);
        goto block_friction;
    }
    func_8007D494(fighter_data, ness_attr->x14_FALL_ACCELERATION, fighter_data->x110_attr.x170_TerminalVelocity);

block_friction:
    airFriction = fighter_data->x110_attr.x180_AerialFriction;
    func_8007CE94(fighter_data, airFriction);
}

// 0x801178E8 //
// https://decomp.me/scratch/vWsFm //
void lbl_801178E8(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Start Collision callback //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    if (func_80082708(fighter_gobj) == 0) 
    {
        func_8007D5D4(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x160, 0x0C4C5080, 0, fighter_data->x894, 1.0f, 0.0f);
    }
}

// 0x80117954 //
// https://decomp.me/scratch/6leYl //
void lbl_80117954(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Charge Collision callback //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    if (func_80082708(fighter_gobj) == 0)
    {
        func_8007D5D4(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x161, 0x0C4C5080, 0, fighter_data->x894, 1.0f, 0.0f);
    }
}

// 0x801179C0 //
// https://decomp.me/scratch/4QY4r //
void lbl_801179C0(HSD_GObj* fighter_gobj) // Ness's grounded PK Flash Release Collision callback //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    if (func_80082708(fighter_gobj) == 0)
    {
        func_8007D5D4(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x163, 0x0C4C5080, 0, fighter_data->x894, 1.0f, 0.0f);
    }
}

// 0x80117A2C //
// https://decomp.me/scratch/ODFbf //
void lbl_80117A2C(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Start Collision callback //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    if (func_80081D0C(fighter_gobj) != 0)
    {
        func_8007D7FC(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15C, 0x0C4C5080, 0, fighter_data->x894, 1.0f, 0.0f);
    }
}

// 0x80117A98 //
// https://decomp.me/scratch/qbobW //
void lbl_80117A98(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Charge Collision callback //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    if (func_80081D0C(fighter_gobj) != 0)
    {
        func_8007D7FC(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15D, 0x0C4C5080, 0, fighter_data->x894, 1.0f, 0.0f);
    }
}

// 0x80117B04 //
// https://decomp.me/scratch/cYdeE //
void lbl_80117B04(HSD_GObj* fighter_gobj) // Ness's aerial PK Flash Release Collision callback //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    if (func_80081D0C(fighter_gobj) != 0)
    {
        func_8007D7FC(fighter_data);
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15F, 0x0C4C5080, 0, fighter_data->x894, 1.0f, 0.0f);
    }
}