#include "ftSk_SpecialN.h"

#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0D14.h"
#include "ft/ftcolanim.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftSeak/ftSk_Init.h"
#include "it/items/itseakneedleheld.h"

/* 1120D4 */ static void ftSk_SpecialN_801120D4(Fighter_GObj* gobj);

float ftSk_SpecialN_803CC598[] = {
    -1, -0.75, -0.5, -0.25, 0, +0.25, +0.5, +0.75, +1,
};

// Sheik_CheckAndDestroyNeedles
// https://decomp.me/scratch/rKi8R (initial work; old context)
// https://decomp.me/scratch/5rjkN
void ftSk_SpecialN_80111FBC(Fighter_GObj* fighter_gobj)
{
    Fighter* fp; // r31
    Fighter_GObj* fighter_gobj2;
    ftSeakAttributes* specialAttributes; // r29
    Vec3 sp14;
    float temp_f31;
    float var_f2;

    fp = GET_FIGHTER(fighter_gobj);
    specialAttributes = fp->dat_attrs;

    if ((u32) fp->fv.sk.x2230 != 0U) {
        fp->fv.sk.x2230 = 0U;
        temp_f31 = ftSk_SpecialN_803CC598[4];
        // temp_f31 = 0;

        while (fp->fv.sk.x222C != 0) {
            sp14 = fp->cur_pos;

            if (fp->ground_or_air == 0) {
                var_f2 = specialAttributes->x4;
            } else {
                var_f2 = specialAttributes->xC;
            }
            sp14.y += fp->x34_scale.y * var_f2;
            sp14.z = temp_f31;

            fighter_gobj2 =
                it_802AFD8C(fighter_gobj, &sp14, 0x4F, fp->facing_dir);
            if (fighter_gobj2 != 0U) {
                it_802AFEA8(fighter_gobj2, fighter_gobj, 1);
            }
            fp->fv.sk.x222C -= 1;
        }
        if ((fp->death2_cb == ftSk_Init_80110198) ||
            (fp->take_dmg_cb == ftSk_Init_80110198))
        {
            ftSk_SpecialN_801120D4(fighter_gobj);
        }
    }
    fp->fv.sk.x222C = 0;
}

// https://decomp.me/scratch/IJZbn
void ftSk_SpecialN_801120D4(Fighter_GObj* fighter_gobj)
{
    Fighter* fp;

    fp = fighter_gobj->user_data;
    fp->take_dmg_cb = 0;
    fp->death2_cb = 0;
}

// https://decomp.me/scratch/86XVe
// https://decomp.me/scratch/X0h7H
void ftSk_SpecialN_Enter(Fighter_GObj* fighter_gobj)
{
    Fighter* fp2;
    Fighter* fp = getFighterPlus(fighter_gobj);

    Fighter_ChangeMotionState(fighter_gobj, 0x155, 0, 1.0, 0, 1.0, 0);

    fp->throw_flags_b0 = 0;
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;       // x2200
    fp->mv.sk.specialn.x0 = 0; // x2340

    if (fp->fv.sk.x222C == 0) {
        fp->fv.sk.x222C = 1;
    }

    fp->mv.sk.specialn.x4 = 0;
    fp->mv.sk.specialn.x8 = 0;

    fp2 = fighter_gobj->user_data;
    fp2->take_dmg_cb = ftSk_Init_80110198;
    fp2->death2_cb = ftSk_Init_80110198;

    ftAnim_8006EBA4(fighter_gobj);
}

// https://decomp.me/scratch/i6fz7
// https://decomp.me/scratch/pBB3D
void ftSk_SpecialAirN_Enter(Fighter_GObj* fighter_gobj)
{
    Fighter* fp;
    Fighter* fp2;

    fp = getFighterPlus(fighter_gobj);

    Fighter_ChangeMotionState(fighter_gobj, 0x159, 0, 1.0, 0.0, 1.0, 0);

    fp->throw_flags_b0 = 0;
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;       // x2200
    fp->mv.sk.specialn.x0 = 0; // x2340

    if (fp->fv.sk.x222C == 0) {
        fp->fv.sk.x222C = 1;
    }

    fp->mv.sk.specialn.x4 = 0;
    fp->mv.sk.specialn.x8 = 0;

    fp2 = fighter_gobj->user_data;
    fp2->take_dmg_cb = ftSk_Init_80110198;
    fp2->death2_cb = ftSk_Init_80110198;

    ftAnim_8006EBA4(fighter_gobj);
}

// https://decomp.me/scratch/NUVmH
void ftSk_SpecialNStart_Anim(Fighter_GObj* fighter_gobj)
{
    Fighter* fp;
    Fighter* fp2;

    fp = getFighterPlus(fighter_gobj);

    if (ftAnim_IsFramesRemaining(fighter_gobj) == 0) {
        fp->fv.sk.x2230 = it_802B19AC(fighter_gobj, &fp->cur_pos, 0x17, 0x50,
                                      fp->facing_dir);
        Fighter_ChangeMotionState(fighter_gobj, 0x156, 0, 0, 0, 1.0, 0);

        fp2 = getFighter(fighter_gobj);
        fp2->take_dmg_cb = ftSk_Init_80110198;
        fp2->death2_cb = ftSk_Init_80110198;
    }
}

// Sheik_ChargeNeedlesIncrementer
// https://decomp.me/scratch/fctpe (old/incomplete)
// https://decomp.me/scratch/tnaEG
void ftSk_SpecialNLoop_Anim(Fighter_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    switch (fp->mv.sk.specialn.x8) {
    case 0:
        ft_80088148(getFighterPlus(fighter_gobj), 0x41F36, 0x7F, 0x40);
    }

    fp->mv.sk.specialn.x8 += 1;

    if (fp->cur_anim_frame == 0) {
        fp->fv.sk.x222C += 1;
        fp->mv.sk.specialn.x8 = 0;

        if ((s32) fp->fv.sk.x222C > 6) {
            fp->fv.sk.x222C = 6;
            fp->mv.sk.specialn.x8 = 0x64;
            ftCo_800BFFD0(fp, 0x56, 0);
        }
    }
}

// https://decomp.me/scratch/39tsN
void ftSk_SpecialNCancel_Anim(Fighter_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    fp->fv.sk.x2230 = 0;

    if (ftAnim_IsFramesRemaining(fighter_gobj) == 0) {
        ft_8008A2BC(fighter_gobj);
    }
}

// https://decomp.me/scratch/sFuUX
// https://decomp.me/scratch/QoA5Q
void ftSk_SpecialNEnd_Anim(Fighter_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    s32 specialN_x0 = fp->mv.sk.specialn.x0;

    u32 _[6];

    switch (specialN_x0) {
    case 0: // % 3 == 0
    case 3:
    case 6:
    case 9:
    case 12:
    case 15:
        // fallthrough

    case 1: // % 3 == 1
    case 4:
    case 7:
    case 10:
    case 13:
    case 16:
        fp->mv.sk.specialn.x4 = 1; // 2344
        fp->fv.sk.x2230 = 0;
        // fallthrough again

    case 2: // % 3 == 2
    case 5:
    case 8:
    case 11:
    case 14:
    case 17:
        fp->mv.sk.specialn.x0 += 1;

        if (ftAnim_IsFramesRemaining(fighter_gobj) == 0) {
            ft_8008A2BC(fighter_gobj);
        }
    }
}

// https://decomp.me/scratch/Wx7qX
void ftSk_SpecialAirNStart_Anim(Fighter_GObj* fighter_gobj)
{
    Fighter* fp;  // r31
    Fighter* fp2; // r4

    fp = getFighterPlus(fighter_gobj);

    if (ftAnim_IsFramesRemaining(fighter_gobj) == 0) {
        fp->fv.sk.x2230 = it_802B19AC(fighter_gobj, &fp->cur_pos, 0x17, 0x50,
                                      fp->facing_dir);
        Fighter_ChangeMotionState((Fighter_GObj*) fighter_gobj, 0x15A, 0U, 0.0,
                                  1.0, 0.0, 0);
        fp2 = fighter_gobj->user_data;
        fp2->take_dmg_cb = ftSk_Init_80110198;
        fp2->death2_cb = ftSk_Init_80110198;
    }
}

// https://decomp.me/scratch/u10kG
void ftSk_SpecialAirNLoop_Anim(Fighter_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj); // r3
    s32 specialN_x8 = fp->mv.sk.specialn.x8;

    switch (specialN_x8) {
    case 0:
        ft_80088148(fighter_gobj->user_data, 0x41F36, 0x7F, 0x40);
    }

    fp->mv.sk.specialn.x8 += 1;

    if (fp->cur_anim_frame == 0) {
        fp->fv.sk.x222C += 1;
        fp->mv.sk.specialn.x8 = 0;

        if (fp->fv.sk.x222C > 6) {
            fp->fv.sk.x222C = 6;
            fp->mv.sk.specialn.x8 = 0x64;
            ftCo_800BFFD0(fp, 0x56, 0);
        }
    }
}

// https://decomp.me/scratch/suLGJ
void ftSk_SpecialAirNCancel_Anim(Fighter_GObj* fighter_gobj)
{
    Fighter* fp = getFighterPlus(fighter_gobj);          // r4
    ftSeakAttributes* specialAttributes = fp->dat_attrs; // r31

    fp->fv.sk.x2230 = 0;

    if (ftAnim_IsFramesRemaining(fighter_gobj) == 0) {
        if (specialAttributes->x10 == 0) {
            ftCo_800CC730(fighter_gobj);
        } else {
            ftCo_80096900(fighter_gobj, 1, 0, 1, 1.0, specialAttributes->x10);
        }
    }
}

// https://decomp.me/scratch/pfUaf
void ftSk_SpecialAirNEnd_Anim(Fighter_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);             // r4
    ftSeakAttributes* specialAttributes = fp->dat_attrs; // r31
    // s32 unused[8];

    u32 _[8];

    switch (fp->mv.sk.specialn.x0) {
    case 0: // % 3 == 0
    case 3:
    case 6:
    case 9:
    case 12:
    case 15:
        // fallthrough

    case 1: // % 3 == 1
    case 4:
    case 7:
    case 10:
    case 13:
    case 16:
        fp->mv.sk.specialn.x4 = 1; // 2344
        fp->fv.sk.x2230 = 0;
        // fallthrough again

    case 2: // % 3 == 2
    case 5:
    case 8:
    case 11:
    case 14:
    case 17:
        break;
    }

    fp->mv.sk.specialn.x0 += 1;

    if (ftAnim_IsFramesRemaining(fighter_gobj) == 0) {
        if (specialAttributes->x10 == 0) {
            ftCo_800CC730(fighter_gobj);
        } else {
            ftCo_80096900(fighter_gobj, 1, 0, 1, 1.0, specialAttributes->x10);
        }
    }
}

void ftSk_SpecialNStart_IASA(Fighter_GObj* fighter_gobj) {}

// https://decomp.me/scratch/qkbGV
void ftSk_SpecialNLoop_IASA(Fighter_GObj* fighter_gobj)
{
    Fighter* fp;
    Fighter* fp2;
    Fighter* fp3;
    float lbl_804D9650;
    float lbl_804D9654;

    fp = fighter_gobj->user_data;

    if (!(fp->input.held_inputs & 0x200)) {
        fp->mv.sk.specialn.x0 = 0;

        lbl_804D9650 = 0;
        lbl_804D9654 = 1.0;
        Fighter_ChangeMotionState(fighter_gobj, 0x158, 0, lbl_804D9650,
                                  lbl_804D9654, lbl_804D9650, 0);

        fp2 = GET_FIGHTER(fighter_gobj);
        fp2->take_dmg_cb = &ftSk_Init_80110198;
        fp2->death2_cb = &ftSk_Init_80110198;

        fp->accessory4_cb = &ftSk_ShootNeedles;

    } else if (fp->input.x668 & 0x80000000) {
        lbl_804D9650 = 0;
        lbl_804D9654 = 1.0;
        Fighter_ChangeMotionState(fighter_gobj, 0x157, 0, lbl_804D9650,
                                  lbl_804D9654, lbl_804D9650, 0);

        fp3 = GET_FIGHTER(fighter_gobj);
        fp3->take_dmg_cb = &ftSk_Init_80110198;
        fp3->death2_cb = &ftSk_Init_80110198;
    }
}

void ftSk_SpecialNCancel_IASA(Fighter_GObj* fighter_gobj) {}

void ftSk_SpecialNEnd_IASA(Fighter_GObj* fighter_gobj) {}

void ftSk_SpecialAirNStart_IASA(Fighter_GObj* fighter_gobj) {}

// https://decomp.me/scratch/jz1FA
void ftSk_SpecialAirNLoop_IASA(Fighter_GObj* fighter_gobj)
{
    Fighter* fp;  // r31
    Fighter* fp2; // r4
    Fighter* fp3; // r5

    fp = fighter_gobj->user_data;

    if (!(fp->input.held_inputs & 0x200)) {
        fp->mv.sk.specialn.x0 = 0; // x2340

        Fighter_ChangeMotionState(fighter_gobj, 0x15C, 0U, 0, 1.0, 0, NULL);
        fp3 = GET_FIGHTER(fighter_gobj);
        fp3->take_dmg_cb = ftSk_Init_80110198;
        fp3->death2_cb = ftSk_Init_80110198;

        fp->accessory4_cb = &ftSk_ShootNeedles;

    } else if (fp->input.x668 & 0x80000000) {
        Fighter_ChangeMotionState(fighter_gobj, 0x15B, 0U, 0, 1.0, 0, NULL);
        fp2 = GET_FIGHTER(fighter_gobj);
        fp2->take_dmg_cb = ftSk_Init_80110198;
        fp2->death2_cb = ftSk_Init_80110198;
    }
}

void ftSk_SpecialAirNCancel_IASA(Fighter_GObj* fighter_gobj) {}

void ftSk_SpecialAirNEnd_IASA(Fighter_GObj* fighter_gobj) {}

void ftSk_SpecialNStart_Phys(Fighter_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

void ftSk_SpecialNLoop_Phys(Fighter_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

void ftSk_SpecialNCancel_Phys(Fighter_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

void ftSk_SpecialNEnd_Phys(Fighter_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

void ftSk_SpecialAirNStart_Phys(Fighter_GObj* fighter_gobj)
{
    ft_80084EEC(fighter_gobj);
}

void ftSk_SpecialAirNLoop_Phys(Fighter_GObj* fighter_gobj)
{
    ft_80084EEC(fighter_gobj);
}

void ftSk_SpecialAirNCancel_Phys(Fighter_GObj* fighter_gobj)
{
    ft_80084EEC(fighter_gobj);
}

void ftSk_SpecialAirNEnd_Phys(Fighter_GObj* fighter_gobj)
{
    ft_80084EEC(fighter_gobj);
}

// https://decomp.me/scratch/wmQQW
void ftSk_SpecialNStart_Coll(Fighter_GObj* fighter_gobj)
{
    Fighter* fp;  // r31
    Fighter* fp2; // r4

    fp = getFighterPlus(fighter_gobj);

    if (ft_80082708(fighter_gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);

        Fighter_ChangeMotionState(fighter_gobj, 0x159, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0, 0.0, NULL);

        fp2 = fighter_gobj->user_data;
        fp2->take_dmg_cb = ftSk_Init_80110198; // x21DC
        fp2->death2_cb = ftSk_Init_80110198;   // x21E4
    }
}

// https://decomp.me/scratch/UvU3k
void ftSk_SpecialNLoop_Coll(Fighter_GObj* fighter_gobj)
{
    Fighter* fp;  // r31
    Fighter* fp2; // r4

    fp = getFighterPlus(fighter_gobj);

    if (ft_80082708(fighter_gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);

        Fighter_ChangeMotionState(fighter_gobj, 0x15A, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0, 0.0, NULL);

        fp2 = fighter_gobj->user_data;
        fp2->take_dmg_cb = ftSk_Init_80110198; // x21DC
        fp2->death2_cb = ftSk_Init_80110198;   // x21E4
    }
}

// https://decomp.me/scratch/mwRgz
void ftSk_SpecialNCancel_Coll(Fighter_GObj* fighter_gobj)
{
    ftSeakAttributes* specialAttributes; // r31
    Fighter* fp;                         // r3

    fp = getFighterPlus(fighter_gobj);
    specialAttributes = fp->dat_attrs;

    if (ft_80082708(fighter_gobj) == GA_Ground) {
        fp = getFighter(fighter_gobj);
        fp->take_dmg_cb = 0; // x21DC
        fp->death2_cb = 0;   // x21E4

        if (specialAttributes->x10 == 0.0f) {
            ftCo_800CC730(fighter_gobj);
        } else {
            ftCo_80096900(fighter_gobj, 1, 0, 1, 1.0, specialAttributes->x10);
        }
    }
}

// https://decomp.me/scratch/M5S4j
void ftSk_SpecialNEnd_Coll(Fighter_GObj* fighter_gobj)
{
    ftSeakAttributes* specialAttributes; // r30
    Fighter* fp;                         // r31
    Fighter* fp2;                        // r3

    fp = getFighterPlus(fighter_gobj);
    specialAttributes = fp->dat_attrs;

    if (ft_80082708((Fighter_GObj*) fighter_gobj) == GA_Ground) {
        fp2 = fighter_gobj->user_data;
        fp2->take_dmg_cb = 0; // x21DC
        fp2->death2_cb = 0;   // x21E4

        fp->fv.sk.x222C = 0;
        fp->mv.sk.specialn.x4 = 0;

        if (specialAttributes->x10 == 0.0f) {
            ftCo_800CC730((Fighter_GObj*) fighter_gobj);
        } else {
            ftCo_80096900((Fighter_GObj*) fighter_gobj, 1, 0, 1, 1.0,
                          specialAttributes->x10);
        }
    }
}

// https://decomp.me/scratch/a2Cj5
void ftSk_SpecialAirNStart_Coll(Fighter_GObj* fighter_gobj)
{
    Fighter* fp;
    Fighter* fp2;

    fp = getFighter(fighter_gobj);

    if (ft_80081D0C(fighter_gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(fighter_gobj, 0x155, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0, 0.0, NULL);

        fp2 = getFighter(fighter_gobj);
        fp2->take_dmg_cb = ftSk_Init_80110198; // x21DC
        fp2->death2_cb = ftSk_Init_80110198;   // x21E4
    }
}

// https://decomp.me/scratch/NlYTd
void ftSk_SpecialAirNLoop_Coll(Fighter_GObj* fighter_gobj)
{
    Fighter* fp;  // r31
    Fighter* fp2; // r4

    fp = getFighterPlus(fighter_gobj);

    if (ft_80081D0C(fighter_gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);

        Fighter_ChangeMotionState(fighter_gobj, 0x156, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0, 0.0, NULL);

        fp2 = fighter_gobj->user_data;
        fp2->take_dmg_cb = ftSk_Init_80110198; // x21DC
        fp2->death2_cb = ftSk_Init_80110198;   // x21E4
    }
}

// https://decomp.me/scratch/rmdBY
void ftSk_SpecialAirNCancel_Coll(Fighter_GObj* fighter_gobj)
{
    Fighter* fp;

    if (ft_80081D0C((Fighter_GObj*) fighter_gobj) != GA_Ground) {
        ftCo_800D5BF8((Fighter_GObj*) fighter_gobj);
        fp = getFighterPlus(fighter_gobj);
        fp->take_dmg_cb = 0; // x21DC
        fp->death2_cb = 0;   // x21E4
    }
}

// https://decomp.me/scratch/7AUrU
void ftSk_SpecialAirNEnd_Coll(Fighter_GObj* fighter_gobj)
{
    Fighter* fp;
    Fighter* fp2;

    fp = getFighterPlus(fighter_gobj);

    if (ft_80081D0C(fighter_gobj) != GA_Ground) {
        fp2 = fighter_gobj->user_data;
        fp2->take_dmg_cb = 0; // x21DC
        fp2->death2_cb = 0;   // x21E4

        fp->fv.sk.x222C = 0;
        fp->mv.sk.specialn.x4 = 0;

        ftCo_800D5BF8(fighter_gobj);
    }
}

void ftSk_Sheik_ShootNeedles(Fighter_GObj* fighter_gobj)
{
    Vec3 vec;
    Fighter* fp; // r31
    Fighter_GObj* gobj;
    ftSeakAttributes* specialAttributes; // r29
    float xVector, yVector;
    s32 rand;

    fp = getFighter(fighter_gobj);
    specialAttributes = fp->dat_attrs;

    if ((s32) fp->mv.sk.specialn.x4 != 0) {
        fp->mv.sk.specialn.x4 = 0;

        if ((s32) fp->fv.sk.x222C > 0) {
            vec = fp->cur_pos;

            if ((s32) fp->ground_or_air == GA_Ground) {
                xVector = specialAttributes->x0 * fp->facing_dir;
                vec.x += fp->x34_scale.y * xVector;
                rand = HSD_Randi(9);
                yVector = specialAttributes->x4 + ftSk_SpecialN_803CC598[rand];
                vec.y += fp->x34_scale.y * yVector;
            } else {
                xVector = specialAttributes->x8 * fp->facing_dir;
                vec.x += fp->x34_scale.y * xVector;
                rand = HSD_Randi(9);
                yVector = (2.0 * ftSk_SpecialN_803CC598[rand]) +
                          specialAttributes->xC;
                vec.y += fp->x34_scale.y * yVector;
            }
            vec.z = 0.0;

            gobj = it_802AFD8C(fighter_gobj, &vec, 0x4F, fp->facing_dir);
            if (gobj != 0U) {
                gobj = it_802AFEA8(gobj, fighter_gobj, 0);
            }

            fp->fv.sk.x222C -= 1;

            efSync_Spawn(0x503, fighter_gobj, &vec);
            ft_80088148(fp, 0x41F3C, 0x7F, 0x40);
        }
    }
}
