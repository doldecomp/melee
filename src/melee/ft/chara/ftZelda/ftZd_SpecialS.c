#include "ftZd_SpecialS.h"

#include "ftZd_Init.h"

#include <platform.h>

#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftZelda/types.h"
#include "it/items/itzeldadinfire.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>

/// 8013B638 - 8013B6D8 (160 bytes)
/// https://decomp.me/scratch/QnXK1
void ftZd_SpecialS_Enter(HSD_GObj* gobj)
{
    float temp_f1;
    Fighter* fp; // r31
    ftZelda_DatAttrs* attributes;
    Fighter* fighter2;

    u8 _[20];

    temp_f1 = 0;
    fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 343, 0, temp_f1, 1.0, temp_f1, NULL);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fighter2 = GET_FIGHTER(gobj);
    attributes = fighter2->dat_attrs;
    fighter2->mv.zd.specials.x0 = attributes->x10;
    fighter2->mv.zd.specials.x4 = attributes->x14;
    fighter2->mv.zd.specials.x8 = attributes->x18;
    fighter2->fv.zd.x222C = 0;
    fighter2->mv.zd.specials.xC = attributes->x1C;
    fighter2->death2_cb = 0;
    fighter2->take_dmg_cb = 0;
    ftAnim_8006EBA4(gobj);
}

/// 8013B6D8 - 8013B780 (168 bytes)
/// https://decomp.me/scratch/F0dW9
void ftZd_SpecialAirS_Enter(HSD_GObj* gobj)
{
    float temp_f1;
    Fighter* fp;
    ftZelda_DatAttrs* attributes;
    Fighter* fighter2;

    u8 _[20];

    temp_f1 = 0;
    fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 346, 0, temp_f1, 1.0, temp_f1, NULL);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->self_vel.y = 0.0F;
    fighter2 = GET_FIGHTER(gobj);
    attributes = fighter2->dat_attrs;
    fighter2->mv.zd.specials.x0 = attributes->x10;
    fighter2->mv.zd.specials.x4 = attributes->x14;
    fighter2->mv.zd.specials.x8 = attributes->x18;
    fighter2->fv.zd.x222C = 0;
    fighter2->mv.zd.specials.xC = attributes->x1C;
    fighter2->death2_cb = 0;
    fighter2->take_dmg_cb = 0;
    ftAnim_8006EBA4(gobj);
}

/// 8013B780 - 8013B89C (284 bytes)
/// https://decomp.me/scratch/g2bK5
void ftZd_SpecialSStart_Anim(HSD_GObj* gobj)
{
    Vec3 sp24;
    float temp_f1;
    float temp_f2;
    HSD_GObj* temp_r3;
    ftZelda_DatAttrs* attributes; // r31
    Fighter* fp;                  // r30

    u8 _[20];

    fp = GET_FIGHTER(gobj);
    attributes = fp->dat_attrs;

    if (fp->cmd_vars[0] == 1U && fp->fv.zd.x222C == 0U) {
        fp->cmd_vars[0] = 0U;
        lb_8000B1CC(fp->parts[89].joint, NULL, &sp24);

        sp24.z = 0;
        temp_f2 = attributes->x20;
        sp24.x = (temp_f2 * fp->facing_dir) + sp24.x;
        sp24.y += attributes->x24;

        temp_r3 = it_802C3BAC(gobj, &sp24, fp->facing_dir, temp_f2);
        fp->fv.zd.x222C = temp_r3;

        if (temp_r3 != 0) {
            fp->death2_cb = &ftZd_Init_801393AC;
            fp->take_dmg_cb = &ftZd_Init_801393AC;
        }
        efSync_Spawn(1275, gobj, fp->parts[76].joint);
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        temp_f1 = 0;
        Fighter_ChangeMotionState(gobj, 344, 0, temp_f1, 1.0, temp_f1, NULL);
        fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
    }
}

/// 8013B89C - 8013BA04 (360 bytes)
/// https://decomp.me/scratch/uGOsz
void ftZd_SpecialSLoop_Anim(HSD_GObj* gobj)
{
    Vec3 sp20;
    ftZelda_DatAttrs* attributes;
    Fighter* fp; // r30
    float temp_f1;
    float temp_f2;
    HSD_GObj* temp_r3;
    HSD_GObj* temp_r3_u32;

    u8 _[16];

    fp = GET_FIGHTER(gobj);
    attributes = fp->dat_attrs;

    if ((fp->cmd_vars[0] == 1U) && (fp->fv.zd.x222C == 0U)) {
        fp->cmd_vars[0] = 0U;
        lb_8000B1CC(fp->parts[89].joint, NULL, &sp20);

        sp20.z = 0;
        temp_f2 = attributes->x20;
        sp20.x = (temp_f2 * fp->facing_dir) + sp20.x;
        sp20.y += attributes->x24;

        temp_r3_u32 = it_802C3BAC(gobj, &sp20, fp->facing_dir, temp_f2);
        fp->fv.zd.x222C = temp_r3_u32;

        if (temp_r3_u32 != 0) {
            fp->death2_cb = &ftZd_Init_801393AC;
            fp->take_dmg_cb = &ftZd_Init_801393AC;
        }
        efSync_Spawn(1275, gobj, fp->parts[76].joint);
    }

    if (fp->mv.zd.specials.x0 != 0) {
        fp->mv.zd.specials.x0 -= 1;
    }

    if (fp->mv.zd.specials.x4 != 0) {
        fp->mv.zd.specials.x4 -= 1;
    }

    temp_r3_u32 = fp->fv.zd.x222C;
    if (temp_r3_u32 == NULL) {
        if (fp->mv.zd.specials.x0 <= 0 && fp->mv.zd.specials.x4 <= 0) {
            temp_f1 = 0;
            Fighter_ChangeMotionState(gobj, 345, 0, temp_f1, 1.0, temp_f1,
                                      NULL);
        }
    } else {
        temp_r3 = it_802C3AF0(fp->fv.zd.x222C);

        if (temp_r3 != gobj) {
            fp->fv.zd.x222C = NULL;
        }
    }
}

/// 8013BA04 - 8013BA8C (136 bytes)
/// https://decomp.me/scratch/TSoo9
void ftZd_SpecialSEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp;
    ftZelda_DatAttrs* attributes;

    fp = GET_FIGHTER(gobj);

    ftPartSetRotX(fp, 0, 0);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp = GET_FIGHTER(gobj);
        attributes = getFtSpecialAttrs(fp);

        fp->mv.zd.specials.x0 = attributes->x10;
        fp->mv.zd.specials.x4 = attributes->x14;
        fp->mv.zd.specials.x8 = attributes->x18;
        fp->fv.zd.x222C = 0;
        fp->mv.zd.specials.xC = attributes->x1C;
        fp->death2_cb = 0;
        fp->take_dmg_cb = 0;

        ft_8008A2BC(gobj);
    }
}

/// 8013BA8C - 8013BBA8 (284 bytes)
/// https://decomp.me/scratch/9hYY3
void ftZd_SpecialAirSStart_Anim(HSD_GObj* gobj)
{
    Vec3 sp24;
    float temp_f1;
    float temp_f2;
    HSD_GObj* temp_r3;
    ftZelda_DatAttrs* attributes;
    Fighter* fp;

    u8 _[20];

    fp = GET_FIGHTER(gobj);
    attributes = fp->dat_attrs;
    if (fp->cmd_vars[0] == 1U && fp->fv.zd.x222C == 0U) {
        fp->cmd_vars[0] = 0U;
        lb_8000B1CC(fp->parts[89].joint, NULL, &sp24);

        sp24.z = 0;
        temp_f2 = attributes->x20;
        sp24.x = (temp_f2 * fp->facing_dir) + sp24.x;
        sp24.y += attributes->x24;

        temp_r3 = it_802C3BAC(gobj, &sp24, fp->facing_dir, temp_f2);
        fp->fv.zd.x222C = temp_r3;

        if (temp_r3 != 0) {
            fp->death2_cb = &ftZd_Init_801393AC;
            fp->take_dmg_cb = &ftZd_Init_801393AC;
        }
        efSync_Spawn(1275, gobj, fp->parts[76].joint);
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        temp_f1 = 0;
        Fighter_ChangeMotionState(gobj, 347, 0, temp_f1, 1.0, temp_f1, NULL);
        fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
    }
}

/// 8013BBA8 - 8013BD10 (360 bytes)
/// https://decomp.me/scratch/llKUS
void ftZd_SpecialAirSLoop_Anim(HSD_GObj* gobj)
{
    Vec3 sp20;
    float temp_f1;
    float temp_f2;
    HSD_GObj* temp_r3;
    ftZelda_DatAttrs* attributes; // r31
    Fighter* fp;                  // r30

    u8 _[16];

    fp = GET_FIGHTER(gobj);
    attributes = fp->dat_attrs;

    if (fp->cmd_vars[0] == 1U && fp->fv.zd.x222C == 0U) {
        fp->cmd_vars[0] = 0U;
        lb_8000B1CC(fp->parts[89].joint, NULL, &sp20);

        sp20.z = 0;
        temp_f2 = attributes->x20;
        sp20.x = temp_f2 * fp->facing_dir + sp20.x;
        sp20.y += attributes->x24;

        temp_r3 = it_802C3BAC(gobj, &sp20, fp->facing_dir, temp_f2);
        fp->fv.zd.x222C = temp_r3;

        if (temp_r3 != NULL) {
            fp->death2_cb = &ftZd_Init_801393AC;
            fp->take_dmg_cb = &ftZd_Init_801393AC;
        }
        efSync_Spawn(1275, gobj, fp->parts[76].joint);
    }

    if (fp->mv.zd.specials.x0 != 0) {
        fp->mv.zd.specials.x0 -= 1;
    }

    if (fp->mv.zd.specials.x4 != 0) {
        fp->mv.zd.specials.x4 -= 1;
    }

    if (fp->fv.zd.x222C == 0U) {
        if (fp->mv.zd.specials.x0 <= 0 && fp->mv.zd.specials.x4 <= 0) {
            temp_f1 = 0;
            Fighter_ChangeMotionState(gobj, 348, 0, temp_f1, 1.0, temp_f1,
                                      NULL);
        }
    } else {
        temp_r3 = it_802C3AF0(fp->fv.zd.x222C);

        if (temp_r3 != gobj) {
            fp->fv.zd.x222C = NULL;
        }
    }
}

/// 8013BD10 - 8013BDD0 (192 bytes)
/// https://decomp.me/scratch/fsXpu
void ftZd_SpecialAirSEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftZelda_DatAttrs* sa = fp->dat_attrs;

    ftPartSetRotX(fp, 0, 0);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        {
            u8 _[4];

            Fighter* fp = GET_FIGHTER(gobj);
            ftZelda_DatAttrs* sa = getFtSpecialAttrs(fp);

            fp->mv.zd.specials.x0 = sa->x10;
            fp->mv.zd.specials.x4 = sa->x14;
            fp->mv.zd.specials.x8 = sa->x18;
            fp->fv.zd.x222C = 0;
            fp->mv.zd.specials.xC = sa->x1C;
            fp->death2_cb = 0;
            fp->take_dmg_cb = 0;
        }

        if (sa->x34 == 0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1, sa->x34);
        }
    }
}

void ftZd_SpecialSStart_IASA(HSD_GObj* gobj) {}

/// 8013BDD4 - 8013BE50 (124 bytes)
/// https://decomp.me/scratch/MaYEA
void ftZd_SpecialSLoop_IASA(HSD_GObj* gobj)
{
    float temp_f1;
    s32 var_r0;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    fp->mv.zd.specials.xC -= 1;

    if (fp->mv.zd.specials.xC <= 0) {
        fp->mv.zd.specials.xC = 0;
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }

    if ((var_r0 == 1) && !(fp->input.held_inputs & 512)) {
        temp_f1 = 0;
        Fighter_ChangeMotionState(gobj, 345, 0, temp_f1, 1.0, temp_f1, NULL);
    }
}

void ftZd_SpecialSEnd_IASA(HSD_GObj* gobj) {}

void ftZd_SpecialAirSStart_IASA(HSD_GObj* gobj) {}

/// 8013BE58 - 8013BED4 (124 bytes)
/// https://decomp.me/scratch/Zxkmg
void ftZd_SpecialAirSLoop_IASA(HSD_GObj* gobj)
{
    float temp_f1;
    s32 var_r0;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    fp->mv.zd.specials.xC -= 1;

    if (fp->mv.zd.specials.xC <= 0) {
        fp->mv.zd.specials.xC = 0;
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }

    if (var_r0 == 1 && !(fp->input.held_inputs & 512)) {
        temp_f1 = 0;
        Fighter_ChangeMotionState(gobj, 348, 0, temp_f1, 1.0, temp_f1, NULL);
    }
}

void ftZd_SpecialAirSEnd_IASA(HSD_GObj* gobj)
{
    return;
}

/// 8013BED8 - 8013BF10 (56 bytes)
/// https://decomp.me/scratch/Sb7RS
void ftZd_SpecialSStart_Phys(HSD_GObj* gobj)
{
    s32 stateVar;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    stateVar = fp->mv.zd.specials.x8;

    if (stateVar) {
        fp->mv.zd.specials.x8 -= 1;
    }

    ft_80084F3C(gobj);
}

/// 8013BED8 - 8013BF30 (32 bytes)
void ftZd_SpecialSLoop_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// 8013BF30 - 8013BF50 (32 bytes)
void ftZd_SpecialSEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// 8013BF50 - 8013BFB0 (96 bytes)
/// https://decomp.me/scratch/suE14
void ftZd_SpecialAirSStart_Phys(HSD_GObj* gobj)
{
    Fighter* fp;
    s32 temp_r3;
    ftZelda_DatAttrs* charAttr;
    ftCo_DatAttrs* fighterAttr;
    float aerialFriction;

    u8 _[4];

    fp = GET_FIGHTER(gobj);
    temp_r3 = fp->mv.zd.specials.x8;
    charAttr = fp->dat_attrs;

    if (temp_r3 != 0) {
        fp->mv.zd.specials.x8 = temp_r3 - 1;
    } else {
        fighterAttr = &fp->co_attrs;
        ftCommon_Fall(fp, charAttr->x2C, fighterAttr->terminal_vel);
    }

    aerialFriction = fp->co_attrs.aerial_friction;
    ftCommon_ApplyFrictionAir(fp, aerialFriction);
}

/// 8013BFB0 - 8013C010 (96 bytes)
/// https://decomp.me/scratch/BxLXt
void ftZd_SpecialAirSLoop_Phys(HSD_GObj* gobj)
{
    Fighter* fp;
    s32 temp_r3;
    ftZelda_DatAttrs* charAttr;
    ftCo_DatAttrs* fighterAttr;
    float aerialFriction;

    u8 _[4];

    fp = GET_FIGHTER(gobj);
    temp_r3 = fp->mv.zd.specials.x8;
    charAttr = fp->dat_attrs;

    if (temp_r3 != 0) {
        fp->mv.zd.specials.x8 = temp_r3 - 1;
    } else {
        fighterAttr = &fp->co_attrs;
        ftCommon_Fall(fp, charAttr->x2C, fighterAttr->terminal_vel);
    }

    aerialFriction = fp->co_attrs.aerial_friction;
    ftCommon_ApplyFrictionAir(fp, aerialFriction);
}

/// 8013C010 - 8013C070 (96 bytes)
/// https://decomp.me/scratch/54a1x
void ftZd_SpecialAirSEnd_Phys(HSD_GObj* gobj)
{
    Fighter* fp;
    s32 temp_r3;
    ftZelda_DatAttrs* charAttr;
    ftCo_DatAttrs* fighterAttr;
    float aerialFriction;

    u8 _[4];

    fp = GET_FIGHTER(gobj);
    temp_r3 = fp->mv.zd.specials.x8;
    charAttr = fp->dat_attrs;

    if (temp_r3 != 0) {
        fp->mv.zd.specials.x8 = temp_r3 - 1;
    } else {
        fighterAttr = &fp->co_attrs;
        ftCommon_Fall(fp, charAttr->x2C, fighterAttr->terminal_vel);
    }

    aerialFriction = fp->co_attrs.aerial_friction;
    ftCommon_ApplyFrictionAir(fp, aerialFriction);
}

/// 8013C070 - 8013C0DC (108 bytes)
/// https://decomp.me/scratch/947er
void ftZd_SpecialSStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == 0) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 346, 0x0C4C5082, fp->cur_anim_frame,
                                  1.0, 0, NULL);
    }
}

/// 8013C0DC - 8013C148 (108 bytes)
/// https://decomp.me/scratch/x1Nmd
void ftZd_SpecialSLoop_Coll(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == 0) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 347, 0x0C4C5080, fp->cur_anim_frame,
                                  1.0, 0, NULL);
    }
}

/// 8013C148 - 8013C1B4 (108 bytes)
void ftZd_SpecialSEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == 0) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 348, 0x0C4C5080, fp->cur_anim_frame,
                                  1.0, 0, NULL);
    }
}

/// 8013C1B4 - 8013C220 (108 bytes)
void ftZd_SpecialAirSStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != 0) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 343, 0x0C4C5082, fp->cur_anim_frame,
                                  1.0, 0, NULL);
    }
}

/// 8013C220 - 8013C28C (108 bytes)
void ftZd_SpecialAirSLoop_Coll(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != 0) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 344, 0x0C4C5080, fp->cur_anim_frame,
                                  1.0, 0, NULL);
    }
}

/// 8013C28C - 8013C2F8 (108 bytes)
void ftZd_SpecialAirSEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != 0) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 345, 0x0C4C5080, fp->cur_anim_frame,
                                  1.0, 0, NULL);
    }
}
