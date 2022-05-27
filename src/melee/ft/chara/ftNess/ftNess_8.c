#include "ftNess.h"

// 0x80119E14 //
// https://decomp.me/scratch/LwTKg //
void func_80119E14(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet Start Action State handler //
{
    s32 filler[7];
    ftNessAttributes* ness_attr;
    Fighter* temp_fighter;

    temp_fighter = fighter_gobj->user_data;
    ness_attr = temp_fighter->x2D4_specialAttributes;
    temp_fighter->x2340_stateVar1 = (s32)ness_attr->x74_COOLDOWN_AFTER_RELEASE;
    temp_fighter->x2348_stateVar3 = 0;
    temp_fighter->x234C_stateVar4 = (s32)ness_attr->x84_PSI_MAGNET_FRAMES_BEFORE_GRAVITY;
    temp_fighter->x2350_stateVar5 = 0;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16F, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
}

// 0x80119E90 //
// https://decomp.me/scratch/ckNxx //
void func_80119E90(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet Start Action State handler //
{
    s32 filler[7];
    Fighter* temp_fighter;
    ftNessAttributes* ness_attr;

    temp_fighter = fighter_gobj->user_data;
    ness_attr = temp_fighter->x2D4_specialAttributes;
    temp_fighter->x2340_stateVar1 = (s32)ness_attr->x74_COOLDOWN_AFTER_RELEASE;
    temp_fighter->x2348_stateVar3 = 0;
    temp_fighter->x234C_stateVar4 = (s32)ness_attr->x84_PSI_MAGNET_FRAMES_BEFORE_GRAVITY;
    temp_fighter->x2350_stateVar5 = 0;
    temp_fighter->x80_self_vel.y = 0.0f;
    temp_fighter->x80_self_vel.x /= ness_attr->x88_PSI_MAGNET_MOMENTUM_PRESERVATION;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x174, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
}

// 0x80119F20 //
// https://decomp.me/scratch/frKYd //
void lbl_80119F20(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet Start Animation callback //
{
    Fighter* fighter_data;
    Fighter* fighter_data2;
    s32 unused[2];

    fighter_data2 = fighter_gobj->user_data;

    if ((fighter_data2->input.x65C & 0x200) == 0)
    {
        fighter_data2->x2348_stateVar3 = 1;
    }

    if (func_8006F238(fighter_gobj) == 0)
    {
        fighter_data = fighter_gobj->user_data;

        if (fighter_data->x2219_flag.bits.b0 == 0)
        {

            efAsync_Spawn(fighter_gobj, &fighter_data->x60C, 0U, 0x4F0U, fighter_data->x5E8_fighterBones[23].x0_jobj);
            fighter_data->x2219_flag.bits.b0 = 1;
        }
        fighter_data->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fighter_data->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
        fighter_data2->x2350_stateVar5 = 0;
        if ((s32)fighter_data2->xE0_ground_or_air == 0)
        {
            func_8011A650(fighter_gobj);
            return;
        }
        func_8011A6A8(fighter_gobj);
    }
}

// 0x8011A000
// https://decomp.me/scratch/psrOE //
void lbl_8011A000(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet Start Animation callback //
{
    Fighter* fighter_data2;
    Fighter* fighter_data;
    s32 unused[4];

    fighter_data2 = fighter_data = fighter_gobj->user_data;

    if ((fighter_data2->input.x65C & 0x200) == 0)
    {
        fighter_data2->x2348_stateVar3 = 1;
    }

    if (func_8006F238(fighter_gobj) == 0)
    {
        fighter_data = fighter_gobj->user_data;

        if (fighter_data->x2219_flag.bits.b0 == 0)
        {
            efAsync_Spawn(fighter_gobj, &fighter_data->x60C, 0U, 0x4F0U, fighter_data->x5E8_fighterBones[23].x0_jobj);
            fighter_data->x2219_flag.bits.b0 = 1;
        }
        fighter_data->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fighter_data->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
        fighter_data2->x2350_stateVar5 = 0;
        if ((s32)fighter_data2->xE0_ground_or_air == 0)
        {
            func_8011A650(fighter_gobj);
            return;
        }
        func_8011A6A8(fighter_gobj);
    }
}

// 0x8011A0E0 //
void lbl_8011A0E0(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet Start IASA callback //
{
    return;
}

// 0x8011A0E4 //
void lbl_8011A0E4(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet Start IASA callback //
{
    return;
}

// 0x8011A0E8 //
// https://decomp.me/scratch/GCJrl //
void lbl_8011A0E8(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet Start Physics callback //
{
    func_80084F3C(fighter_gobj);
}

// 0x8011A108 //
// https://decomp.me/scratch/4zHBZ //
void lbl_8011A108(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet Start Physics callback //
{
    Fighter* fighter_data;
    s32 unused[2];
    s32 gravityDelay;
    attr* attr;
    ftNessAttributes* ness_attr;

    fighter_data = fighter_gobj->user_data;
    attr = &fighter_data->x110_attr;
    ness_attr = fighter_data->x2D4_specialAttributes;
    gravityDelay = fighter_data->x234C_stateVar4;
    if (gravityDelay != 0)
    {
        fighter_data->x234C_stateVar4 = gravityDelay - 1;
        goto block_end;
    }

    func_8007D494(fighter_data, ness_attr->x8C_PSI_MAGNET_FALL_ACCELERATION, attr->x170_TerminalVelocity);
block_end:
    func_8007CF58(fighter_data);
}

// 0x8011A168 //
// https://decomp.me/scratch/S8g3b //
void lbl_8011A168(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet Start Collision callback //
{
    if (func_80082708(fighter_gobj) == 0)
    {
        func_8011A1E0(fighter_gobj);
    }
}

// 0x8011A1A4 //
// https://decomp.me/scratch/eNYIn //
void lbl_8011A1A4(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet Start Collision callback //
{
    if (func_80081D0C(fighter_gobj) != 0)
    {
        func_8011A240(fighter_gobj);
    }
}

// 0x8011A1E0 //
// https://decomp.me/scratch/erSzB //
void func_8011A1E0(HSD_GObj* fighter_gobj) // Ness's ground->air PSI Magnet Start Action State handler //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    func_8007D5D4(fighter_data);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x174, 0x0C4C5082, 0, fighter_data->x894, 1.0f, 0.0f);
}

extern void func_8007D468(Fighter*);

// 0x8011A240 //
// https://decomp.me/scratch/153K2 //
void func_8011A240(HSD_GObj* fighter_gobj) // Ness's air->ground PSI Magnet Start Action State handler //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    func_8007D7FC(fighter_data);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16F, 0x0C4C5082, 0, fighter_data->x894, 1.0f, 0.0f);
    func_8007D468(fighter_data);
}

extern void func_80088478(Fighter*, s32, s32, s32);

// 0x8011A2A8 //
// https://decomp.me/scratch/Wlutx //
void lbl_8011A2A8(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet Hold Animation callback //
{
    s32 unused[2];
    s32 timer_var;
    Fighter* temp_r31;
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    if ((fighter_data->input.x65C & 0x200) == 0)
    {
        fighter_data->x2348_stateVar3 = 1;
    }

    if (fighter_data->x2340_stateVar1 > 0)
    {
        fighter_data->x2340_stateVar1 = (s32)(fighter_data->x2340_stateVar1 - 1);
    }
    if (((s32)fighter_data->x2340_stateVar1 <= 0) && ((s32)fighter_data->x2348_stateVar3 != 0))
    {
        if ((s32)fighter_data->xE0_ground_or_air == 0)
        {
            func_8011B4AC(fighter_gobj);
        }
        else
        {
            func_8011B4E4(fighter_gobj);
        }
    }
    temp_r31 = fighter_gobj->user_data;

    temp_r31->x2350_stateVar5 = (s32)(temp_r31->x2350_stateVar5 - 1);

    if ((s32)temp_r31->x2350_stateVar5 <= 0)
    {
        func_80088478(temp_r31, 0x334A1, 0x7F, 0x40);
        temp_r31->x2350_stateVar5 = 0x28;
    }
}

// 0x8011A370 //
// https://decomp.me/scratch/UbQAr //
void lbl_8011A370(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet Hold Animation callback //
{
    s32 unused[4];
    s32 timer_var;
    Fighter* temp_r31;
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    if ((fighter_data->input.x65C & 0x200) == 0)
    {
        fighter_data->x2348_stateVar3 = 1;
    }

    if (fighter_data->x2340_stateVar1 > 0)
    {
        fighter_data->x2340_stateVar1 = (s32)(fighter_data->x2340_stateVar1 - 1);
    }
    if (((s32)fighter_data->x2340_stateVar1 <= 0) && ((s32)fighter_data->x2348_stateVar3 != 0))
    {
        if ((s32)fighter_data->xE0_ground_or_air == 0)
        {
            func_8011B4AC(fighter_gobj);
        }
        else
        {
            func_8011B4E4(fighter_gobj);
        }
    }
    temp_r31 = fighter_gobj->user_data;

    temp_r31->x2350_stateVar5 = (s32)(temp_r31->x2350_stateVar5 - 1);

    if ((s32)temp_r31->x2350_stateVar5 <= 0)
    {
        func_80088478(temp_r31, 0x334A1, 0x7F, 0x40);
        temp_r31->x2350_stateVar5 = 0x28;
    }
}

// 0x8011A438 //
void lbl_8011A438(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet Hold IASA callback //
{
    return;
}

// 0x8011A43C //
void lbl_8011A43C(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet Hold IASA callback //
{
    return;
}

extern void func_8007AF10(HSD_GObj*);

// 0x8011A440 //
// https://decomp.me/scratch/knaIL //
void lbl_8011A440(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet Hold Physics callback //
{
    func_80084F3C(fighter_gobj);
    func_8007AF10(fighter_gobj);
}

// 0x8011A474 //
// https://decomp.me/scratch/R46Uj //
void lbl_8011A474(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet Hold Physics callback //
{
    Fighter* fighter_data;
    s32 unused[6];
    s32 magnetTimer;
    ftNessAttributes* ness_attr;
    attr* attr;

    fighter_data = fighter_gobj->user_data;
    ness_attr = fighter_data->x2D4_specialAttributes;
    attr = &fighter_data->x110_attr;

    magnetTimer = fighter_data->x234C_stateVar4;
    if (magnetTimer != 0)
    {
        fighter_data->x234C_stateVar4 = magnetTimer - 1;
        goto block_end;
    }
    func_8007D494(fighter_data, ness_attr->x8C_PSI_MAGNET_FALL_ACCELERATION, attr->x170_TerminalVelocity);
block_end:
    func_8007CF58(fighter_data);
    func_8007AF10(fighter_gobj);
}

// 0x8011A4E8 //
// https://decomp.me/scratch/SNaVN //
void lbl_8011A4E8(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet Hold Collision callback //
{
    if (func_80082708(fighter_gobj) == 0)
    {
        func_8011A560(fighter_gobj);
    }
}

// 0x8011A524 //
// https://decomp.me/scratch/dS3Sn //
void lbl_8011A524(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet Hold Collision callback
{
    if (func_80081D0C(fighter_gobj) != 0)
    {
        func_8011A5D4(fighter_gobj);
    }
}

extern void func_8007B2C4(HSD_GObj*, void*);

// 0x8011A560 //
// https://decomp.me/scratch/noqpv //
void func_8011A560(HSD_GObj* fighter_gobj) // Ness's ground->air PSI Magnet Hold Action State handler //
{
    s32 filler[6];
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;

    fighter_data = fighter_gobj->user_data;
    func_8007D5D4(fighter_data);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x175, 0x0C4C5082, 0, fighter_data->x894, 1.0f, 0.0f);
    fighter_data = fighter_gobj->user_data;
    ness_attr = fighter_data->x2D4_specialAttributes;
    func_8007B2C4(fighter_gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION_BUBBLE_BONE_ID);
}

// 0x8011A5D4 //
// https://decomp.me/scratch/PCAft //
void func_8011A5D4(HSD_GObj* fighter_gobj) // Ness's air->ground PSI Magnet Hold Action State handler //
{
    s32 filler[6];
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;

    fighter_data = fighter_gobj->user_data;
    func_8007D7FC(fighter_data);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x170, 0x0C4C5082, 0, fighter_data->x894, 1.0f, 0.0f);
    func_8007D468(fighter_data);
    fighter_data = fighter_gobj->user_data;
    ness_attr = fighter_data->x2D4_specialAttributes;
    func_8007B2C4(fighter_gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION_BUBBLE_BONE_ID);
}

// 0x8011A650 //
// https://decomp.me/scratch/YoMqy //
void func_8011A650(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet Hold Action State handler //
{
    s32 filler[4];
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x170, 2, 0, 0.0f, 1.0f, 0.0f);
    fighter_data = fighter_gobj->user_data;
    ness_attr = fighter_data->x2D4_specialAttributes;
    func_8007B2C4(fighter_gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION_BUBBLE_BONE_ID);
}

// 0x8011A6A8 //
// https://decomp.me/scratch/TjjOK //
void func_8011A6A8(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet Hold Action State handler //
{
    s32 filler[4];
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x175, 2, 0, 0.0f, 1.0f, 0.0f);
    fighter_data = fighter_gobj->user_data;
    ness_attr = fighter_data->x2D4_specialAttributes;
    func_8007B2C4(fighter_gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION_BUBBLE_BONE_ID);
}

extern f32 func_80075F48(Fighter*, s32);

inline f32 returnStateVar(s32 stateVar)
{
    return (f32)stateVar;
}

inline void GetAttrStuff(HSD_GObj* arg0)
{
    Fighter* temp_r30 = arg0->user_data;
    ftNessAttributes* temp_r31 = temp_r30->x2D4_specialAttributes;
    temp_r30->x2344_stateVar2 += -1;

    if (((u32)temp_r30->x2200_ftcmd_var0 == 0U) && ((returnStateVar(temp_r30->x2344_stateVar2)) <= temp_r31->x78_PSI_MAGNET_UNK1)) 
    {
        temp_r30->x2200_ftcmd_var0 = 1;
        temp_r30->x2C_facing_direction = -temp_r30->x2C_facing_direction;
    }
    func_80075AF0(temp_r30, 0, -((0.01745329238474369f * (180.0f / temp_r31->x78_PSI_MAGNET_UNK1)) - func_80075F48(temp_r30, 0)));
}

// 0x8011A700 //
// https://decomp.me/scratch/ZgMh8 //
void lbl_8011A700(HSD_GObj* arg0) // Ness's grounded PSI Magnet Turnaround Animation callback - unused // 
{
    ftNessAttributes* temp_r31;
    Fighter* temp_r30;
    Fighter* temp_r29 = temp_r30 = arg0->user_data;

    if ((temp_r29->input.x65C & 0x200) == 0)
    {
        temp_r29->x2348_stateVar3 = 1;
    }
    if (temp_r29->x2340_stateVar1 > 0)
    {
        temp_r29->x2340_stateVar1 = temp_r29->x2340_stateVar1 - 1;
    }

    GetAttrStuff(arg0);

    if ((s32)temp_r29->x2344_stateVar2 <= 0)
    {
        func_8011AB10(arg0);
    }
}

// 0x8011A810 //
// https://decomp.me/scratch/UQm4N // Ness's aerial PSI Magnet Turnaround Animation callback - unused //
void lbl_8011A810(HSD_GObj* arg0)
{
    s32 filler[2];
    ftNessAttributes* temp_r31;
    Fighter* temp_r30;
    Fighter* temp_r29 = temp_r30 = arg0->user_data;

    if ((temp_r29->input.x65C & 0x200) == 0)
    {
        temp_r29->x2348_stateVar3 = 1;
    }

    if (temp_r29->x2340_stateVar1 > 0)
    {
        temp_r29->x2340_stateVar1 = temp_r29->x2340_stateVar1 - 1;
    }

    GetAttrStuff(arg0);

    if ((s32)temp_r29->x2344_stateVar2 <= 0) 
    {
        func_8011AB10(arg0);
    }
}

// 0x8011A920 //
void lbl_8011A920(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet Turnaround IASA callback - unused //
{
    return;
}

// 0x8011A924 //
void lbl_8011A924(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet Turnaround IASA callback - unused //
{
    return;
}

// 0x8011A928 //
void lbl_8011A928(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet Turnaround Physics callback - unused //
{
    func_80084F3C(fighter_gobj);
    func_8007AF10(fighter_gobj);
}

// 0x8011A95C //
void lbl_8011A95C(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet Turnaround Physics callback - unused //
{
    Fighter* fighter_data;
    s32 unused[6];
    s32 magnetTimer;
    ftNessAttributes* ness_attr;
    attr* attr;

    fighter_data = fighter_gobj->user_data;
    ness_attr = fighter_data->x2D4_specialAttributes;
    attr = &fighter_data->x110_attr;

    magnetTimer = fighter_data->x234C_stateVar4;
    if (magnetTimer != 0)
    {
        fighter_data->x234C_stateVar4 = magnetTimer - 1;
        goto block_end;
    }
    func_8007D494(fighter_data, ness_attr->x8C_PSI_MAGNET_FALL_ACCELERATION, attr->x170_TerminalVelocity);
block_end:
    func_8007CF58(fighter_data);
    func_8007AF10(fighter_gobj);
}

// 0x8011A9D0 //
// https://decomp.me/scratch/E3jqW //
void lbl_8011A9D0(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet Turnaround Collision callback - unused //
{
    if (func_80082708(fighter_gobj) == 0)
    {
        func_8011AA48(fighter_gobj);
    }
}

// 0x8011AA0C //
// https://decomp.me/scratch/qkeXm //
void lbl_8011AA0C(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet Turnaround Collision callback - unused //
{
    if (func_80081D0C(fighter_gobj) != 0) 
    {
        func_8011AAA8(fighter_gobj);
    }
}

// 0x8011AA48 //
// https://decomp.me/scratch/Myul8 //
void func_8011AA48(HSD_GObj* fighter_gobj) // Ness's ground->air PSI Magnet Turnaround Action State handler - unused //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    func_8007D5D4(fighter_data);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x178, 0x0C4C5082, 0, fighter_data->x894, 1.0f, 0.0f);
}

// 0x8011AAA8 //
// https://decomp.me/scratch/rfuLo //
void func_8011AAA8(HSD_GObj* fighter_gobj) // Ness's air->ground PSI Magnet Turnaround Action State handler - unused //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    func_8007D7FC(fighter_data);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x173, 0x0C4C5082, 0, fighter_data->x894, 1.0f, 0.0f);
    func_8007D468(fighter_data);
}

// 0x8011AB10 //
// https://decomp.me/scratch/HzpAw //
s32 func_8011AB10(HSD_GObj* arg0) // Ness's PSI Magnet Absorb callback //
{
    s32 unused[10];
    Fighter* temp_r3;
    ftNessAttributes* attrs;

    temp_r3 = arg0->user_data;
    if (((s32)temp_r3->x2340_stateVar1 <= 0) && ((s32)temp_r3->x2348_stateVar3 != 0)) 
    {
        if ((s32)temp_r3->xE0_ground_or_air == 0)
        {
            func_8011B4AC(arg0);
        }
        else
        {
            func_8011B4E4(arg0);
        }
        return 0;
    }
    if ((s32)temp_r3->xE0_ground_or_air == 0)
    {
        Fighter_ActionStateChange_800693AC(arg0, 0x170, 2, 0, 0.0f, 1.0f, 0.0f);
        temp_r3 = arg0->user_data;
        attrs = temp_r3->x2D4_specialAttributes;
        func_8007B2C4(arg0, &attrs->x98_PSI_MAGNET_ABSORPTION_BUBBLE_BONE_ID);
    }
    else
    {
        Fighter_ActionStateChange_800693AC(arg0, 0x175, 2, 0, 0.0f, 1.0f, 0.0f);
        temp_r3 = arg0->user_data;
        attrs = temp_r3->x2D4_specialAttributes;
        func_8007B2C4(arg0, &attrs->x98_PSI_MAGNET_ABSORPTION_BUBBLE_BONE_ID);
    }
    return 1;
}

inline void MagnetStateVarCalc(HSD_GObj* fighter_gobj)
{
    Fighter* fighter_data = fighter_gobj->user_data;
    fighter_data->x2350_stateVar5 = fighter_data->x2350_stateVar5 - 1;
    if ((s32)fighter_data->x2350_stateVar5 <= 0)
    {
        func_80088478(fighter_data, 0x334A1, 0x7F, 0x40);
        fighter_data->x2350_stateVar5 = 0x28;
    }
}

// 0x8011ABF8 //
// https://decomp.me/scratch/jbsQw //
void lbl_8011ABF8(HSD_GObj* arg0) // Ness's grounded PSI Magnet Absorb Animation callback //
{
    s32 unused[10];
    f32 temp_f1;
    f32 temp_f1_2;

    Fighter* temp_r30;
    Fighter* temp_r3_2;
    Fighter* temp_r4;
    s32 phi_r0;

    Fighter* temp_e1;
    Fighter* temp_e2;
    ftNessAttributes* attr;
    Fighter* temp_r31;

    temp_r4 = arg0->user_data;
    if ((temp_r4->input.x65C & 0x200) == 0)
    {
        temp_r4->x2348_stateVar3 = 1;
    }

    if (temp_r4->x2340_stateVar1 > 0)
    {
        temp_r4->x2340_stateVar1 = (s32)(temp_r4->x2340_stateVar1 - 1);
    }
    if (func_8006F238(arg0) == 0)
    {
        temp_r3_2 = arg0->user_data;
        if (((s32)temp_r3_2->x2340_stateVar1 <= 0) && ((s32)temp_r3_2->x2348_stateVar3 != 0))
        {
            if ((s32)temp_r3_2->xE0_ground_or_air == 0)
            {
                func_8011B4AC(arg0);
            }
            else
            {
                func_8011B4E4(arg0);
            }
            phi_r0 = 0;
        }
        else
        {
            if ((s32)temp_r3_2->xE0_ground_or_air == 0)
            {
                Fighter_ActionStateChange_800693AC(arg0, 0x170, 2, 0, 0.0f, 1.0f, 0.0f);

                temp_e1 = arg0->user_data;
                attr = temp_e1->x2D4_specialAttributes;
                func_8007B2C4(arg0, &attr->x98_PSI_MAGNET_ABSORPTION_BUBBLE_BONE_ID);
            }
            else
            {
                Fighter_ActionStateChange_800693AC(arg0, 0x175, 2, 0, 0.0f, 1.0f, 0.0f);
                temp_e2 = arg0->user_data;
                attr = temp_e2->x2D4_specialAttributes;
                func_8007B2C4(arg0, &attr->x98_PSI_MAGNET_ABSORPTION_BUBBLE_BONE_ID);
            }
            phi_r0 = 1;
        }
        if (phi_r0 != 0)
        {
            func_8007DB24(arg0);
            temp_r30 = arg0->user_data;
            if (temp_r30->x2219_flag.bits.b0 == 0)
            {
                efAsync_Spawn(arg0, &temp_r30->x60C, 0U, 0x4F0U, temp_r30->x5E8_fighterBones[23].x0_jobj);
                temp_r30->x2219_flag.bits.b0 = 1;
            }
            temp_r30->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
            temp_r30->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
        }
    }

    MagnetStateVarCalc(arg0);
}

// 0x8011ADC8 //
// https://decomp.me/scratch/VSNzs //
void lbl_8011ADC8(HSD_GObj* arg0) // Ness's aerial PSI Magnet Absorb Animation callback //
{
    s32 unused[6];
    Fighter* temp_r31;
    Fighter* temp_r31_2;
    Fighter* temp_r4;

    temp_r4 = arg0->user_data;
    if ((temp_r4->input.x65C & 0x200) == 0)
    {
        temp_r4->x2348_stateVar3 = 1;
    }

    if (temp_r4->x2340_stateVar1 > 0)
    {
        temp_r4->x2340_stateVar1 = (s32)(temp_r4->x2340_stateVar1 - 1);
    }
    if ((func_8006F238(arg0) == 0) && (func_8011AB10(arg0) != 0))
    {
        func_8007DB24(arg0);
        temp_r31 = arg0->user_data;
        if (temp_r31->x2219_flag.bits.b0 == 0)
        {
            efAsync_Spawn(arg0, &temp_r31->x60C, 0U, 0x4F0U, temp_r31->x5E8_fighterBones[23].x0_jobj);
            temp_r31->x2219_flag.bits.b0 = 1;
        }
        temp_r31->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        temp_r31->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    }
    temp_r31_2 = arg0->user_data;
    temp_r31_2->x2350_stateVar5 = (s32)(temp_r31_2->x2350_stateVar5 - 1);
    if ((s32)temp_r31_2->x2350_stateVar5 <= 0)
    {
        func_80088478(temp_r31_2, 0x334A1, 0x7F, 0x40);
        temp_r31_2->x2350_stateVar5 = 0x28;
    }
}

// 0x8011AEE0 //
void lbl_8011AEE0(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet Absorb IASA callback //
{
    return;
}

// 0x8011AEE4 //
void lbl_8011AEE4(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet Absorb IASA callback //
{
    return;
}

// 0x8011AEE8 //
// https://decomp.me/scratch/wKRWI //
void lbl_8011AEE8(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet Absorb Physics callback //
{
    func_80084F3C(fighter_gobj);
    func_8007AF10(fighter_gobj);
}

// 0x8011AF1C //
// https://decomp.me/scratch/SfvyO // 
void lbl_8011AF1C(HSD_GObj* arg0) // Ness's aerial PSI Magnet Absorb Physics callback //
{
    s32 unused[6];
    Fighter* temp_r31;
    s32 temp_r3;
    ftNessAttributes* attrs;
    attr* attributes;

    temp_r31 = arg0->user_data;
    attrs = temp_r31->x2D4_specialAttributes;
    attributes = &temp_r31->x110_attr;

    temp_r3 = temp_r31->x234C_stateVar4;
    if (temp_r3 != 0) {
        temp_r31->x234C_stateVar4 = temp_r3 - 1;
        goto end_part;
    }
    func_8007D494(temp_r31, attrs->x8C_PSI_MAGNET_FALL_ACCELERATION, attributes->x170_TerminalVelocity);
end_part:
    func_8007CF58(temp_r31);
    func_8007AF10(arg0);
}

// 0x8011AF90 //
// https://decomp.me/scratch/XSIRp //
void lbl_8011AF90(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet Absorb Collision callback //
{
    if (func_80082708(fighter_gobj) == 0)
    {
        func_8011B008(fighter_gobj);
    }
}

// 0x8011AFCC //
// https://decomp.me/scratch/Lq3zN //
void lbl_8011AFCC(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet Absorb Collision callback //
{
    if (func_80081D0C(fighter_gobj) != 0)
    {
        func_8011B07C(fighter_gobj);
    }
}

// 0x8011B008 //
// https://decomp.me/scratch/LkmRj //
void func_8011B008(HSD_GObj* fighter_gobj) // Ness's ground->air PSI Magnet Absorb Action State handler //
{
    s32 filler[6];
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;

    fighter_data = fighter_gobj->user_data;
    func_8007D5D4(fighter_data);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x176, 0x0C4C5082, 0, fighter_data->x894, 1.0f, 0.0f);
    fighter_data = fighter_gobj->user_data;
    ness_attr = fighter_data->x2D4_specialAttributes;
    func_8007B2C4(fighter_gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION_BUBBLE_BONE_ID);
}

// 0x8011B07C //
// https://decomp.me/scratch/uVIed //
void func_8011B07C(HSD_GObj* fighter_gobj) // Ness's air->ground PSI Magnet Absorb Action State handler //
{
    s32 filler[6];
    Fighter* fighter_data;
    ftNessAttributes* ness_attr;

    fighter_data = fighter_gobj->user_data;
    func_8007D7FC(fighter_data);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x171, 0x0C4C5082, 0, fighter_data->x894, 1.0f, 0.0f);
    func_8007D468(fighter_data);
    fighter_data = fighter_gobj->user_data;
    ness_attr = fighter_data->x2D4_specialAttributes;
    func_8007B2C4(fighter_gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION_BUBBLE_BONE_ID);
}

// 0x8011B0F8 //
// https://decomp.me/scratch/H0osU //
void func_8011B0F8(HSD_GObj* gobj) // Ness's PSI Magnet OnAbsorb hook //
{
    s32 filler[2];
    f32 temp_f1;
    f32 temp_f31;
    s32 temp_r0;
    Fighter* temp_r31;
    ftNessAttributes* temp_r30;
    s32 phi_r4;

    temp_r31 = gobj->user_data;
    temp_r30 = temp_r31->x2D4_specialAttributes;
    temp_f31 = (f32)(s32)((f32)temp_r31->x1A44 * func_8011495C(temp_r31));
    temp_r31->dmg.x1830_percent -= temp_f31;
    temp_f1 = temp_r31->dmg.x1830_percent;

    if (temp_r31->dmg.x1830_percent < 0.0f)
    {
        temp_f31 = temp_f1 + temp_f31;
        temp_r31->dmg.x1830_percent = 0.0f;
    }
    Player_SetHPByIndex((s32)temp_r31->xC_playerID, temp_r31->x221F_flag.bits.b4, (s32)temp_r31->dmg.x1830_percent);
    func_80040B8C(temp_r31->xC_playerID, temp_r31->x221F_flag.bits.b4, (s32)temp_f31);
    temp_r31->x2C_facing_direction = (f32)temp_r31->x1A40;
    temp_r0 = temp_r31->x10_action_state_index;

    if (((temp_r0 != 0x171) && (temp_r0 != 0x176)) || !(temp_r31->x894 <= temp_r30->x7C_PSI_MAGNET_UNK2))
    {
        if ((s32)temp_r31->xE0_ground_or_air == 0)
        {
            phi_r4 = 0x171;
        }
        else
        {
            phi_r4 = 0x176;
        }
        Fighter_ActionStateChange_800693AC(gobj, phi_r4, 2, 0, 0.0f, 1.0f, 0.0f);
        func_8007B2C4(gobj, &temp_r30->x98_PSI_MAGNET_ABSORPTION_BUBBLE_BONE_ID);
    }
}

// 0x8011B25C //
// https://decomp.me/scratch/H32Eg //
void lbl_8011B25C(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet End Animation callback //
{
    s32 unused[2];

    if (func_8006F238(fighter_gobj) == 0)
    {
        func_8007DB24(fighter_gobj);
        func_8007D92C(fighter_gobj);
    }
}

// 0x8011B2A0 //
// https://decomp.me/scratch/uLilE //
void lbl_8011B2A0(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet End Animation callback //
{
    s32 unused[2];
    if (func_8006F238(fighter_gobj) == 0)
    {
        func_8007DB24(fighter_gobj);
        func_8007D92C(fighter_gobj);
    }
}

// 0x8011B2E4 //
void lbl_8011B2E4(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet End IASA callback //
{
    return;
}

// 0x8011B2E8 //
void lbl_8011B2E8(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet End IASA callback //
{
    return;
}

// 0x8011B2EC //
// https://decomp.me/scratch/ccQxd //
void lbl_8011B2EC(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet End Physics callback //
{
    func_80084F3C(fighter_gobj);
}

// 0x8011B30C //
// https://decomp.me/scratch/EkqUN //
void lbl_8011B30C(HSD_GObj* arg0) // Ness's aerial PSI Magnet End Physics callback //
{
    s32 unused[6];
    Fighter* temp_r31;
    s32 temp_r3;
    ftNessAttributes* attrs;
    attr* attributes;

    temp_r31 = arg0->user_data;
    attrs = temp_r31->x2D4_specialAttributes;
    attributes = &temp_r31->x110_attr;

    temp_r3 = temp_r31->x234C_stateVar4;
    if (temp_r3 != 0)
    {
        temp_r31->x234C_stateVar4 = temp_r3 - 1;
        goto end_part;
    }
    func_8007D494(temp_r31, attrs->x8C_PSI_MAGNET_FALL_ACCELERATION, attributes->x170_TerminalVelocity);
end_part:
    func_8007CF58(temp_r31);
}

// 0x8011B36C //
// https://decomp.me/scratch/5ROxm //
void lbl_8011B36C(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet End Collision callback //
{
    if (func_80082708(fighter_gobj) == 0)
    {
        func_8011B3E4(fighter_gobj);
    }
}

// 0x8011B3A8 //
// https://decomp.me/scratch/phduU //
void lbl_8011B3A8(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet End Collision callback //
{
    if (func_80081D0C(fighter_gobj) != 0) 
    {
        func_8011B444(fighter_gobj);
    }
}

// 0x8011B3E4 //
// https://decomp.me/scratch/9ihkO //
void func_8011B3E4(HSD_GObj* fighter_gobj) // Ness's ground->air PSI Magnet End Action State handler //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    func_8007D5D4(fighter_data);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x177, 0x0C4C5080, 0, fighter_data->x894, 1.0f, 0.0f);
}

// 0x8011B444 //
// https://decomp.me/scratch/uJw37 //
void func_8011B444(HSD_GObj* fighter_gobj) // Ness's air->ground PSI Magnet End Action State handler //
{
    Fighter* temp_r31;

    temp_r31 = fighter_gobj->user_data;
    func_8007D7FC(temp_r31);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x172, 0x0C4C5080, 0, temp_r31->x894, 1.0f, 0.0f);
    func_8007D468(temp_r31);
}

// 0x8011B4AC //
// https://decomp.me/scratch/6wpwg //
void func_8011B4AC(HSD_GObj* fighter_gobj) // Ness's grounded PSI Magnet End Action State handler //
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x172, 0, 0, 0.0f, 1.0f, 0.0f);
}

// 0x8011B4E4 //
// https://decomp.me/scratch/sbrLt //
void func_8011B4E4(HSD_GObj* fighter_gobj) // Ness's aerial PSI Magnet End Action State handler //
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x177, 0, 0, 0.0f, 1.0f, 0.0f);
}

