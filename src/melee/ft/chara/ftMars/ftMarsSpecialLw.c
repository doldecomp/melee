#include "melee/ft/inlines.h"
#include <melee/ft/chara/ftMars/ftMars.h>

#include <melee/ef/efsync.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/ftparts.h>
#include <melee/lb/lbunknown_001.h>
#include <melee/lb/lbunknown_003.h>

void ftMars_SpecialLw_StartAction(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);
    fp0->x80_self_vel.y = 0;

    Fighter_ActionStateChange_800693AC(gobj, 369, 0, NULL, 0, 1, 0);
    func_8006EBA4(gobj);

    {
        Fighter* fp1 = GET_FIGHTER(gobj);
        fp1->x2204_ftcmd_var1 = 0;
        fp1->x2340_stateVar1 = 0;
    }
}

void ftMars_SpecialAirLw_StartAction(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    {
        Fighter* fp = GET_FIGHTER(gobj);
        MarsAttributes* attr = fp->x2D4_specialAttributes;
        fp->x80_self_vel.x /= attr->x4C;
        fp->x80_self_vel.y = 0;
    }

    Fighter_ActionStateChange_800693AC(gobj, 371, 0, NULL, 0, 1, 0);
    func_8006EBA4(gobj);

    {
        Fighter* fp;
        fp = GET_FIGHTER(gobj);
        fp->x2204_ftcmd_var1 = 0;
        fp->x2340_stateVar1 = 0;
    }
}

void lbl_80138AA8(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* attr = getFtSpecialAttrsD(fp);

    if (fp->x2204_ftcmd_var1 == 1) {
        fp->x2204_ftcmd_var1 = 2;
        func_8007B1B8(gobj, &attr->x64, &lbl_80139140);
        fp->x221B_b1 = true;
        fp->x19B4_shieldUnk = attr->x60;
        fp->x19B8_shieldUnk = attr->x60;
    } else if (fp->x2204_ftcmd_var1 == 0) {
        fp->x221B_b0 = false;
    }

    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

void lbl_80138B64(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* attr = getFtSpecialAttrsD(fp);

    if (fp->x2204_ftcmd_var1 == 1) {
        fp->x2204_ftcmd_var1 = 2;
        func_8007B1B8(gobj, &attr->x64, &lbl_80139140);
        fp->x221B_b1 = true;
        fp->x19B4_shieldUnk = attr->x60;
        fp->x19B8_shieldUnk = attr->x60;
    } else if (fp->x2204_ftcmd_var1 == 0) {
        fp->x221B_b0 = false;
    }

    if (!ftAnim_IsFramesRemaining(gobj))
        func_800CC730(gobj);
}

void lbl_80138C20(HSD_GObj* gobj) {}

void lbl_80138C24(HSD_GObj* gobj) {}

void lbl_80138C28(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
    func_8007AEE0(gobj);
}

void lbl_80138C5C(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = getFtSpecialAttrsD(fp);
    func_8007D494(fp, attr->x54, attr->x58);
    func_8007CE94(fp, attr->x50);
    func_8007AEE0(gobj);
}

// 80138CC0 001358A0
// https://decomp.me/scratch/PQPYD
void lbl_80138CC0(HSD_GObj* gobj)
{
    if (func_800827A0(gobj) == 0) {
        func_80138D38(gobj);
    }
}

// 80138CFC 001358DC
// https://decomp.me/scratch/ZAAJM
void lbl_80138CFC(HSD_GObj* gobj)
{
    if (func_80081D0C(gobj) != 0) {
        func_80138DD0(gobj);
    }
}

void func_80138D38(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    {
        Fighter* fp = gobj->user_data;
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(gobj, 371, 0x0C4C508C, NULL,
                                           fp->x894_currentAnimFrame, 1, 0);
    }

    {
        Fighter* fp = gobj->user_data;
        MarsAttributes* attr = getFtSpecialAttrsD(fp);

        if (fp->x2204_ftcmd_var1 == 2) {
            func_8007B1B8(gobj, &attr->x64, &lbl_80139140);
            fp->x221B_b1 = true;
        }
    }
}

void func_80138DD0(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    {
        Fighter* fp0 = gobj->user_data;
        func_8007D7FC(fp0);
        Fighter_ActionStateChange_800693AC(gobj, 369, 0x0C4C508C, NULL,
                                           fp0->x894_currentAnimFrame, 1, 0);
    }

    {
        Fighter* fp = gobj->user_data;
        MarsAttributes* attr = getFtSpecialAttrsD(fp);

        if (fp->x2204_ftcmd_var1 == 2) {
            func_8007B1B8(gobj, &attr->x64, &lbl_80139140);
            fp->x221B_b1 = true;
        }
    }
}

void lbl_80138E68(HSD_GObj* gobj)
{
    ssize_t idx;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    s32 hb;
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    s32 sv1 = fp->x2340_stateVar1;

    /// @todo required for some reason
    fp->x2340_stateVar1;

    if (sv1 > 0 && func_800872A4(gobj) == FTKIND_EMBLEM) {
/// @todo register swap:
#ifndef MUST_MATCH
        for (idx = 0; idx < 4; idx++) {
            if (fp->x914[idx].state == HitCapsule_Enabled) {
                func_8007ABD0(&fp->x914[idx], fp->x2340_stateVar1, gobj);
            }
        }

// matches but gross:
#else
        idx = 0;
        hb = (s32) fp;
        while (idx < 4) {
            if (*(s32*) (hb + 0x914) == HitCapsule_Enabled) {
                func_8007ABD0((HitCapsule*) (hb + 0x914), fp->x2340_stateVar1,
                              gobj);
            }
            idx++;
            hb += 0x138;
        }
#endif
    }

    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

// https://decomp.me/scratch/Jx7Ov
void lbl_80138F14(HSD_GObj* gobj)
{
    ssize_t idx;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    s32 hb;
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    s32 sv1 = fp->x2340_stateVar1;

    /// @todo required for some reason
    fp->x2340_stateVar1;

    if (sv1 > 0 && func_800872A4(gobj) == FTKIND_EMBLEM) {
/// @todo register swap:
#ifndef MUST_MATCH
        for (idx = 0; idx < 4; idx++) {
            if (fp->x914[idx].state == HitCapsule_Enabled) {
                func_8007ABD0(&fp->x914[idx], fp->x2340_stateVar1, gobj);
            }
        }

// matches but gross:
#else
        idx = 0;
        hb = (s32) fp;
        while (idx < 4) {
            if (*(s32*) (hb + 0x914) == HitCapsule_Enabled) {
                func_8007ABD0((HitCapsule*) (hb + 0x914), fp->x2340_stateVar1,
                              gobj);
            }
            idx++;
            hb += 0x138;
        }
#endif
    }

    if (!ftAnim_IsFramesRemaining(gobj))
        func_800CC730(gobj);
}

// 80138FC0 00135BA0
void lbl_80138FC0(HSD_GObj* gobj) {}

// 80138FC4 00135BA4
void lbl_80138FC4(HSD_GObj* gobj) {}

// 80138FC8 00135BA8
// https://decomp.me/scratch/u66PG
void lbl_80138FC8(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

// 80138FE8 00135BC8
// https://decomp.me/scratch/QnjxB
void lbl_80138FE8(HSD_GObj* gobj)
{
    func_80084EEC(gobj);
}

// 80139008 00135BE8
// https://decomp.me/scratch/2SGFK
void lbl_80139008(HSD_GObj* gobj)
{
    if (func_80082708(gobj) == 0) {
        func_80139080(gobj);
    }
}

// 80139044 00135C24
// https://decomp.me/scratch/3W48X
void lbl_80139044(HSD_GObj* gobj)
{
    if (func_80081D0C(gobj) != 0) {
        func_801390E0(gobj);
    }
}

// 80139080 00135C60
// https://decomp.me/scratch/w0qtf
void func_80139080(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(gobj, 0x174, 0x0C4C508E, NULL,
                                       fp->x894_currentAnimFrame, 1, 0);
}

// 801390E0 00135CC0
// https://decomp.me/scratch/qAmn3
void func_801390E0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(gobj, 0x172, 0x0C4C508E, NULL,
                                       fp->x894_currentAnimFrame, 1, 0);
}

void lbl_80139140(HSD_GObj* gobj)
{
    s32 temp_r0;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused0[4];
#endif
    Vec3 sp18;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused1[12];
#endif

    {
        Fighter* fp = gobj->user_data;
        MarsAttributes* attr = fp->x2D4_specialAttributes;

        fp->facing_dir = fp->x19AC;
        temp_r0 = (s32) fp->x19A4;

        if (temp_r0 > 0)
            fp->x2340_stateVar1 = (s32) (temp_r0 * attr->x5C);

        func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 4)].x0_jobj, 0,
                      &sp18);
        func_800119DC(&sp18, 0x78, 0.9f, 0.02f, 1.0471975803375244f);

        {
            enum_t asid;

            if (fp->xE0_ground_or_air == GA_Ground)
                asid = 0x172;
            else
                asid = 0x174;

            Fighter_ActionStateChange_800693AC(gobj, asid, 0, NULL, 0, 1, 0);
        }
    }

    {
        Fighter* ft_2;
        ft_2 = gobj->user_data;
        ft_2->x2219_flag; // required for regalloc
        if (ft_2->x2219_flag.bits.b0 == 0) {
            switch (func_800872A4(gobj)) {
            case 0x12:
                ef_Spawn(
                    0x4F1, gobj,
                    ft_2->x5E8_fighterBones[func_8007500C(ft_2, 0x23)].x0_jobj,
                    &ft_2->facing_dir);
                break;
            case 0x1A:
                ef_Spawn(
                    0x510, gobj,
                    ft_2->x5E8_fighterBones[func_8007500C(ft_2, 0x23)].x0_jobj,
                    &ft_2->facing_dir);
                break;
            }
            ft_2->x2219_flag.bits.b0 = 1;
        }

        ft_2->cb.x21D4_callback_EnterHitlag = 0;
        ft_2->cb.x21D8_callback_ExitHitlag = 0;
        ft_2->cb.x21BC_callback_Accessory4 = 0;
    }
}
