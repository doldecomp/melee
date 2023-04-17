#include "ftZelda_SpecialS.h"

#include "ftZelda_Init.h"

#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"

// 8013B638 - 8013B6D8 (0xA0 bytes)
// https://decomp.me/scratch/QnXK1
void ftZd_SpecialS_Enter(HSD_GObj* gobj)
{
    f32 temp_f1;
    Fighter* fp; // r31
    ftZeldaAttributes* attributes;
    Fighter* fighter2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    temp_f1 = 0;
    fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x157, 0, NULL, temp_f1, 1.0, temp_f1);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fighter2 = GET_FIGHTER(gobj);
    attributes = fighter2->x2D4_specialAttributes;
    fighter2->sv.zd.unk5.x0 = attributes->x10;
    fighter2->sv.zd.unk5.x4 = attributes->x14;
    fighter2->sv.zd.unk5.x8 = attributes->x18;
    fighter2->ev.zd.x222C = 0;
    fighter2->sv.zd.unk5.xC = attributes->x1C;
    fighter2->cb.x21E4_callback_OnDeath2 = 0;
    fighter2->cb.x21DC_callback_OnTakeDamage = 0;
    ftAnim_8006EBA4(gobj);
}

// 8013B6D8 - 8013B780 (0xA8 bytes)
// https://decomp.me/scratch/F0dW9
void ftZd_SpecialAirS_Enter(HSD_GObj* gobj)
{
    f32 temp_f1;
    Fighter* fp;
    ftZeldaAttributes* attributes;
    Fighter* fighter2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    temp_f1 = 0;
    fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x15A, 0, NULL, temp_f1, 1.0, temp_f1);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x80_self_vel.y = 0.0F;
    fighter2 = GET_FIGHTER(gobj);
    attributes = fighter2->x2D4_specialAttributes;
    fighter2->sv.zd.unk5.x0 = attributes->x10;
    fighter2->sv.zd.unk5.x4 = attributes->x14;
    fighter2->sv.zd.unk5.x8 = attributes->x18;
    fighter2->ev.zd.x222C = 0;
    fighter2->sv.zd.unk5.xC = attributes->x1C;
    fighter2->cb.x21E4_callback_OnDeath2 = 0;
    fighter2->cb.x21DC_callback_OnTakeDamage = 0;
    ftAnim_8006EBA4(gobj);
}

// 8013B780 - 8013B89C (0x11C bytes)
// https://decomp.me/scratch/g2bK5
void ftZd_SpecialSStart_Anim(HSD_GObj* gobj)
{
    Vec3 sp24;
    f32 temp_f1;
    f32 temp_f2;
    HSD_GObj* temp_r3;
    ftZeldaAttributes* attributes; // r31
    Fighter* fp;                   // r30

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    fp = GET_FIGHTER(gobj);
    attributes = fp->x2D4_specialAttributes;

    if (fp->x2200_ftcmd_var0 == 1U && fp->ev.zd.x222C == 0U) {
        fp->x2200_ftcmd_var0 = 0U;
        lb_8000B1CC(fp->x5E8_fighterBones[0x59].x0_jobj, NULL, &sp24);

        sp24.z = 0;
        temp_f2 = attributes->x20;
        sp24.x = (temp_f2 * fp->facing_dir) + sp24.x;
        sp24.y += attributes->x24;

        temp_r3 = it_802C3BAC(gobj, &sp24, fp->facing_dir, temp_f2);
        fp->ev.zd.x222C = temp_r3;

        if (temp_r3 != 0) {
            fp->cb.x21E4_callback_OnDeath2 = &ftZd_Init_801393AC;
            fp->cb.x21DC_callback_OnTakeDamage = &ftZd_Init_801393AC;
        }
        efSync_Spawn(0x4FB, gobj, fp->x5E8_fighterBones[0x4C].x0_jobj);
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        temp_f1 = 0;
        Fighter_ChangeMotionState(gobj, 0x158, 0, NULL, temp_f1, 1.0, temp_f1);
        fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
    }
}

// 8013B89C - 8013BA04 (0x168 bytes)
// https://decomp.me/scratch/uGOsz
void ftZd_SpecialSHold_Anim(HSD_GObj* gobj)
{
    Vec3 sp20;
    ftZeldaAttributes* attributes;
    Fighter* fp; // r30
    f32 temp_f1;
    f32 temp_f2;
    HSD_GObj* temp_r3;
    HSD_GObj* temp_r3_u32;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    fp = GET_FIGHTER(gobj);
    attributes = fp->x2D4_specialAttributes;

    if ((fp->x2200_ftcmd_var0 == 1U) && (fp->ev.zd.x222C == 0U)) {
        fp->x2200_ftcmd_var0 = 0U;
        lb_8000B1CC(fp->x5E8_fighterBones[0x59].x0_jobj, NULL, &sp20);

        sp20.z = 0;
        temp_f2 = attributes->x20;
        sp20.x = (temp_f2 * fp->facing_dir) + sp20.x;
        sp20.y += attributes->x24;

        temp_r3_u32 = it_802C3BAC(gobj, &sp20, fp->facing_dir, temp_f2);
        fp->ev.zd.x222C = temp_r3_u32;

        if (temp_r3_u32 != 0) {
            fp->cb.x21E4_callback_OnDeath2 = &ftZd_Init_801393AC;
            fp->cb.x21DC_callback_OnTakeDamage = &ftZd_Init_801393AC;
        }
        efSync_Spawn(0x4FB, gobj, fp->x5E8_fighterBones[0x4C].x0_jobj);
    }

    if (fp->sv.zd.unk5.x0 != 0) {
        fp->sv.zd.unk5.x0 -= 1;
    }

    if (fp->sv.zd.unk5.x4 != 0) {
        fp->sv.zd.unk5.x4 -= 1;
    }

    temp_r3_u32 = fp->ev.zd.x222C;
    if (temp_r3_u32 == NULL) {
        if (fp->sv.zd.unk5.x0 <= 0 && fp->sv.zd.unk5.x4 <= 0) {
            temp_f1 = 0;
            Fighter_ChangeMotionState(gobj, 0x159, 0, NULL, temp_f1, 1.0,
                                      temp_f1);
        }
    } else {
        temp_r3 = it_802C3AF0(fp->ev.zd.x222C);

        if (temp_r3 != gobj) {
            fp->ev.zd.x222C = NULL;
        }
    }
}

// 8013BA04 - 8013BA8C (0x88 bytes)
// https://decomp.me/scratch/TSoo9
void ftZd_SpecialSEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp;
    ftZeldaAttributes* attributes;

    fp = GET_FIGHTER(gobj);

    ftParts_8007592C(fp, 0, 0);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp = GET_FIGHTER(gobj);
        attributes = getFtSpecialAttrs(fp);

        fp->sv.zd.unk5.x0 = attributes->x10;
        fp->sv.zd.unk5.x4 = attributes->x14;
        fp->sv.zd.unk5.x8 = attributes->x18;
        fp->ev.zd.x222C = 0;
        fp->sv.zd.unk5.xC = attributes->x1C;
        fp->cb.x21E4_callback_OnDeath2 = 0;
        fp->cb.x21DC_callback_OnTakeDamage = 0;

        ft_8008A2BC(gobj);
    }
}

// 8013BA8C - 8013BBA8 (0x11C bytes)
// https://decomp.me/scratch/9hYY3
void ftZd_SpecialAirSStart_Anim(HSD_GObj* gobj)
{
    Vec3 sp24;
    f32 temp_f1;
    f32 temp_f2;
    HSD_GObj* temp_r3;
    ftZeldaAttributes* attributes;
    Fighter* fp;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    fp = GET_FIGHTER(gobj);
    attributes = fp->x2D4_specialAttributes;
    if (fp->x2200_ftcmd_var0 == 1U && fp->ev.zd.x222C == 0U) {
        fp->x2200_ftcmd_var0 = 0U;
        lb_8000B1CC(fp->x5E8_fighterBones[0x59].x0_jobj, NULL, &sp24);

        sp24.z = 0;
        temp_f2 = attributes->x20;
        sp24.x = (temp_f2 * fp->facing_dir) + sp24.x;
        sp24.y += attributes->x24;

        temp_r3 = it_802C3BAC(gobj, &sp24, fp->facing_dir, temp_f2);
        fp->ev.zd.x222C = temp_r3;

        if (temp_r3 != 0) {
            fp->cb.x21E4_callback_OnDeath2 = &ftZd_Init_801393AC;
            fp->cb.x21DC_callback_OnTakeDamage = &ftZd_Init_801393AC;
        }
        efSync_Spawn(0x4FB, gobj, fp->x5E8_fighterBones[0x4C].x0_jobj);
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        temp_f1 = 0;
        Fighter_ChangeMotionState(gobj, 0x15B, 0, NULL, temp_f1, 1.0, temp_f1);
        fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
    }
}

// 8013BBA8 - 8013BD10 (0x168 bytes)
// https://decomp.me/scratch/llKUS
void ftZd_SpecialAirSHold_Anim(HSD_GObj* gobj)
{
    Vec3 sp20;
    f32 temp_f1;
    f32 temp_f2;
    HSD_GObj* temp_r3;
    ftZeldaAttributes* attributes; // r31
    Fighter* fp;                   // r30

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    fp = GET_FIGHTER(gobj);
    attributes = fp->x2D4_specialAttributes;

    if (fp->x2200_ftcmd_var0 == 1U && fp->ev.zd.x222C == 0U) {
        fp->x2200_ftcmd_var0 = 0U;
        lb_8000B1CC(fp->x5E8_fighterBones[0x59].x0_jobj, NULL, &sp20);

        sp20.z = 0;
        temp_f2 = attributes->x20;
        sp20.x = temp_f2 * fp->facing_dir + sp20.x;
        sp20.y += attributes->x24;

        temp_r3 = it_802C3BAC(gobj, &sp20, fp->facing_dir, temp_f2);
        fp->ev.zd.x222C = temp_r3;

        if (temp_r3 != 0) {
            fp->cb.x21E4_callback_OnDeath2 = &ftZd_Init_801393AC;
            fp->cb.x21DC_callback_OnTakeDamage = &ftZd_Init_801393AC;
        }
        efSync_Spawn(0x4FB, gobj, fp->x5E8_fighterBones[0x4C].x0_jobj);
    }

    if (fp->sv.zd.unk5.x0 != 0) {
        fp->sv.zd.unk5.x0 -= 1;
    }

    if (fp->sv.zd.unk5.x4 != 0) {
        fp->sv.zd.unk5.x4 -= 1;
    }

    if (fp->ev.zd.x222C == 0U) {
        if (fp->sv.zd.unk5.x0 <= 0 && fp->sv.zd.unk5.x4 <= 0) {
            temp_f1 = 0;
            Fighter_ChangeMotionState(gobj, 0x15C, 0, NULL, temp_f1, 1.0,
                                      temp_f1);
        }
    } else {
        temp_r3 = it_802C3AF0(fp->ev.zd.x222C);

        if (temp_r3 != gobj) {
            fp->ev.zd.x222C = NULL;
        }
    }
}

// 8013BD10 - 8013BDD0 (0xC0 bytes)
// https://decomp.me/scratch/fsXpu
void ftZd_SpecialAirSEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftZeldaAttributes* sa = fp->x2D4_specialAttributes;

    ftParts_8007592C(fp, 0, 0);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        {
            /// @todo Unused stack.
#ifdef MUST_MATCH
            u8 _[4];
#endif

            Fighter* fp = GET_FIGHTER(gobj);
            ftZeldaAttributes* sa = getFtSpecialAttrs(fp);

            fp->sv.zd.unk5.x0 = sa->x10;
            fp->sv.zd.unk5.x4 = sa->x14;
            fp->sv.zd.unk5.x8 = sa->x18;
            fp->ev.zd.x222C = 0;
            fp->sv.zd.unk5.xC = sa->x1C;
            fp->cb.x21E4_callback_OnDeath2 = 0;
            fp->cb.x21DC_callback_OnTakeDamage = 0;
        }

        if (sa->x34 == 0) {
            ft_800CC730(gobj);
        } else {
            ft_80096900(gobj, 1, 0, 1, 1, sa->x34);
        }
    }
}

void ftZd_SpecialSStart_IASA(HSD_GObj* gobj) {}

// 8013BDD4 - 8013BE50 (0x7C bytes)
// https://decomp.me/scratch/MaYEA
void ftZd_SpecialSHold_IASA(HSD_GObj* gobj)
{
    f32 temp_f1;
    s32 var_r0;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    fp->sv.zd.unk5.xC -= 1;

    if (fp->sv.zd.unk5.xC <= 0) {
        fp->sv.zd.unk5.xC = 0;
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }

    if ((var_r0 == 1) && !(fp->input.x65C_heldInputs & 0x200)) {
        temp_f1 = 0;
        Fighter_ChangeMotionState(gobj, 0x159, 0, NULL, temp_f1, 1.0, temp_f1);
    }
}

void ftZd_SpecialSEnd_IASA(HSD_GObj* gobj) {}

void ftZd_SpecialAirSStart_IASA(HSD_GObj* gobj) {}

// 8013BE58 - 8013BED4 (0x7C bytes)
// https://decomp.me/scratch/Zxkmg
void ftZd_SpecialAirSHold_IASA(HSD_GObj* gobj)
{
    f32 temp_f1;
    s32 var_r0;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    fp->sv.zd.unk5.xC -= 1;

    if (fp->sv.zd.unk5.xC <= 0) {
        fp->sv.zd.unk5.xC = 0;
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }

    if (var_r0 == 1 && !(fp->input.x65C_heldInputs & 0x200)) {
        temp_f1 = 0;
        Fighter_ChangeMotionState(gobj, 0x15C, 0, NULL, temp_f1, 1.0, temp_f1);
    }
}

void ftZd_SpecialAirSEnd_IASA(HSD_GObj* gobj)
{
    return;
}

// 8013BED8 - 8013BF10 (0x38 bytes)
// https://decomp.me/scratch/Sb7RS
void ftZd_SpecialSStart_Phys(HSD_GObj* gobj)
{
    s32 stateVar;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    stateVar = fp->sv.zd.unk5.x8;

    if (stateVar) {
        fp->sv.zd.unk5.x8 -= 1;
    }

    ft_80084F3C(gobj);
}

// 8013BED8 - 8013BF30 (0x20 bytes)
void ftZd_SpecialSHold_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 8013BF30 - 8013BF50 (0x20 bytes)
void ftZd_SpecialSEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 8013BF50 - 8013BFB0 (0x60 bytes)
// https://decomp.me/scratch/suE14
void ftZd_SpecialAirSStart_Phys(HSD_GObj* gobj)
{
    Fighter* fp;
    s32 temp_r3;
    ftZeldaAttributes* charAttr;
    attr* fighterAttr;
    f32 aerialFriction;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    fp = GET_FIGHTER(gobj);
    temp_r3 = fp->sv.zd.unk5.x8;
    charAttr = fp->x2D4_specialAttributes;

    if (temp_r3 != 0) {
        fp->sv.zd.unk5.x8 = temp_r3 - 1;
    } else {
        fighterAttr = &fp->x110_attr;
        ftCommon_8007D494(fp, charAttr->x2C,
                          fighterAttr->x170_TerminalVelocity);
    }

    aerialFriction = fp->x110_attr.x180_AerialFriction;
    ftCommon_8007CE94(fp, aerialFriction);
}

// 8013BFB0 - 8013C010 (0x60 bytes)
// https://decomp.me/scratch/BxLXt
void ftZd_SpecialAirSHold_Phys(HSD_GObj* gobj)
{
    Fighter* fp;
    s32 temp_r3;
    ftZeldaAttributes* charAttr;
    attr* fighterAttr;
    f32 aerialFriction;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    fp = GET_FIGHTER(gobj);
    temp_r3 = fp->sv.zd.unk5.x8;
    charAttr = fp->x2D4_specialAttributes;

    if (temp_r3 != 0) {
        fp->sv.zd.unk5.x8 = temp_r3 - 1;
    } else {
        fighterAttr = &fp->x110_attr;
        ftCommon_8007D494(fp, charAttr->x2C,
                          fighterAttr->x170_TerminalVelocity);
    }

    aerialFriction = fp->x110_attr.x180_AerialFriction;
    ftCommon_8007CE94(fp, aerialFriction);
}

// 8013C010 - 8013C070 (0x60 bytes)
// https://decomp.me/scratch/54a1x
void ftZd_SpecialAirSEnd_Phys(HSD_GObj* gobj)
{
    Fighter* fp;
    s32 temp_r3;
    ftZeldaAttributes* charAttr;
    attr* fighterAttr;
    f32 aerialFriction;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    fp = GET_FIGHTER(gobj);
    temp_r3 = fp->sv.zd.unk5.x8;
    charAttr = fp->x2D4_specialAttributes;

    if (temp_r3 != 0) {
        fp->sv.zd.unk5.x8 = temp_r3 - 1;
    } else {
        fighterAttr = &fp->x110_attr;
        ftCommon_8007D494(fp, charAttr->x2C,
                          fighterAttr->x170_TerminalVelocity);
    }

    aerialFriction = fp->x110_attr.x180_AerialFriction;
    ftCommon_8007CE94(fp, aerialFriction);
}

// 8013C070 - 8013C0DC (0x6C bytes)
// https://decomp.me/scratch/947er
void ftZd_SpecialSStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == 0) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x15A, 0x0C4C5082, NULL,
                                  fp->x894_currentAnimFrame, 1.0, 0);
    }
}

// 8013C0DC - 8013C148 (0x6C bytes)
// https://decomp.me/scratch/x1Nmd
void ftZd_SpecialSHold_Coll(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == 0) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x15B, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0, 0);
    }
}

// 8013C148 - 8013C1B4 (0x6C bytes)
void ftZd_SpecialSEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == 0) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x15C, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0, 0);
    }
}

// 8013C1B4 - 8013C220 (0x6C bytes)
void ftZd_SpecialAirSStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != 0) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x157, 0x0C4C5082, NULL,
                                  fp->x894_currentAnimFrame, 1.0, 0);
    }
}

// 8013C220 - 8013C28C (0x6C bytes)
void ftZd_SpecialAirSHold_Coll(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != 0) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x158, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0, 0);
    }
}

// 8013C28C - 8013C2F8 (0x6C bytes)
void ftZd_SpecialAirSEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != 0) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x159, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0, 0);
    }
}
