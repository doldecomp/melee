#include <placeholder.h>

#include "ft/forward.h"
#include "ftSeak/forward.h"

#include "ftSk_SpecialHi.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Pass.h"
#include "it/items/itseakvanish.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"

#include <math.h>
#include <baselib/gobj.h>

/* 08A2BC */ static void ft_8008A2BC(Fighter_GObj* gobj);

/* 112ED8 */ static void fn_80112ED8(Fighter_GObj* gobj);
/* 112F48 */ static void ftSk_SpecialHi_80112F48(Fighter_GObj* gobj);
/* 112FA8 */ static void ftSk_SpecialHi_80112FA8(Fighter_GObj* gobj);
/* 113038 */ static void fn_80113038(Fighter_GObj* gobj);
/* 113324 */ static void ftSk_SpecialHi_80113324(Fighter_GObj* gobj);
/* 113390 */ static void ftSk_SpecialHi_80113390(Fighter_GObj* gobj);
/* 11374C */ static void ftSk_SpecialHi_8011374C(Fighter_GObj* gobj);
/* 1137C8 */ static void ftSk_SpecialHi_801137C8(Fighter_GObj* gobj);
/* 113838 */ static void ftSk_SpecialHi_80113838(Fighter_GObj* gobj);
/* 113A30 */ static void ftSk_SpecialHi_80113A30(Fighter_GObj* gobj);
/* 113E40 */ static void ftSk_SpecialHi_80113E40(Fighter_GObj* gobj);
/* 113EAC */ static void ftSk_SpecialHi_80113EAC(Fighter_GObj* gobj);
/* 113F68 */ static void ftSk_SpecialHi_80113F68(Fighter_GObj* gobj);

static float const ftSk_Init_804D9660 = 0;
static float const ftSk_Init_804D9664 = 1;
static double const ftSk_Init_804D9668 = S32_TO_F32;
static float const ftSk_Init_804D9670 = deg_to_rad;
static float const ftSk_Init_804D9674 = 90;
static double const ftSk_Init_804D9678 = 0.5;
static double const ftSk_Init_804D9680 = 3;
static float const ftSk_Init_804D9688 = M_PI / 2;
static float const ftSk_Init_804D968C = 35;
static float const ftSk_Init_804D9690 = 0.001;
static float const ftSk_Init_804D9694 = 10;

void fn_80112ED8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        ftSk_SpecialHi_80112F48(gobj);
        ftSk_SpecialHi_80112FA8(gobj);
        ft_80088148(fp, 115, 127, 64);
    }
    fp->accessory4_cb = NULL;
}

void ftSk_SpecialHi_80112F48(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[4];
    {
        Vec3 pos;
        u8 _[4];
        lb_8000B1CC(fp->parts[FtPart_HipN].joint, 0, &pos);
        pos.z = 0;
        it_802B1C60(gobj, &pos, fp->facing_dir);
    }
}

void ftSk_SpecialHi_80112FA8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    lb_8000B1CC(fp->parts[FtPart_HipN].joint, 0, &pos);
    if (!fp->x2219_b0) {
        efSync_Spawn(1284, gobj, &pos);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

void fn_80113038(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    if (!fp->x2219_b0) {
        lb_8000B1CC(fp->parts[FtPart_HipN].joint, 0, &pos);
        efSync_Spawn(1285, gobj, &pos);
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

void ftSk_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[20];
    fp->cmd_vars[0] = 0;
    fp->mv.sk.specialhi.xC = 0;
    Fighter_ChangeMotionState(gobj, ftSk_MS_SpecialHiStart_0, 0, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
}

void ftSk_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* da = fp->dat_attrs;
    u8 _[20];
    fp->cmd_vars[0] = 0;
    fp->mv.sk.specialhi.xC = 0;
    fp->self_vel.y = da->self_vel_y;
    Fighter_ChangeMotionState(gobj, ftSk_MS_SpecialAirHiStart_0, 0, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
}

/// #fn_80112ED8

/// #ftSk_SpecialHi_80112F48

/// #ftSk_SpecialHi_80112FA8

/// #fn_80113038

/// #ftSk_SpecialHi_Enter

/// #ftSk_SpecialAirHi_Enter

// Gelatart's scratch at https://decomp.me/scratch/ysptk
void ftSk_SpecialHiStart_0_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining((Fighter_GObj*) gobj) == 0) {
        ftSk_SpecialHi_80113838(gobj);
    }
}

// Gelatart's scratch at https://decomp.me/scratch/Ws01S, forked from a
// kipcode66 scratch
void ftSk_SpecialAirHiStart_0_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining((Fighter_GObj*) gobj) == 0) {
        ftSk_SpecialHi_80113A30(gobj);
    }
}

void ftSk_SpecialHiStart_0_IASA(HSD_GObj* gobj) {}

// Interrupt_SheikUpBStartAir
void ftSk_SpecialAirHiStart_0_IASA(HSD_GObj* gobj) {}

// Kipcode66's scratch at https://decomp.me/scratch/ANgXI seems to match this
void ftSk_SpecialHiStart_0_Phys(HSD_GObj* gobj)
{
    ft_80084F3C((Fighter_GObj*) gobj);
}

// Gelatart's scratch at https://decomp.me/scratch/8aRxF
void ftSk_SpecialAirHiStart_0_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes = fp->dat_attrs;
    struct ftCo_DatAttrs* attributes2 = &fp->co_attrs;
    Vec2 vec;

    vec.x = attributes->x30;
    vec.y = attributes->x34;

    ftCommon_8007D494(fp, vec.x, vec.y);
    ftCommon_8007D268(fp);
}

// Gelatart's scratch at https://decomp.me/scratch/xhYaR, forked from a
// kipcode66 scratch
void ftSk_SpecialHiStart_0_Coll(HSD_GObj* gobj)
{
    if (ft_80082708((Fighter_GObj*) gobj) == GA_Ground) {
        ftSk_SpecialHi_80113324(gobj);
    }
}

// Ribbanya's scratch at https://decomp.me/scratch/JHPTX seems to match this
void ftSk_SpecialAirHiStart_0_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 direction; // r4
    s32 groundOrLedge;

    if (fp->facing_dir < ftSk_Init_804D9660) {
        direction = -1;
    } else {
        direction = 1;
    }

    groundOrLedge = ft_CheckGroundAndLedge((Fighter_GObj*) gobj, direction);

    if (groundOrLedge != 0) {
        ftSk_SpecialHi_80113390(gobj);
    } else {
        RETURN_IF(ftCliffCommon_80081298((Fighter_GObj*) gobj));
    }
}

// Kipcode66's scratch at https://decomp.me/scratch/eQhs5 seems to match this
void ftSk_SpecialHi_80113324(Fighter_GObj* arg0)
{
    Fighter* temp_r31;

    temp_r31 = arg0->user_data;
    ftCommon_8007D60C(temp_r31);
    Fighter_ChangeMotionState(arg0, 0x166, 0x0C4C508EU,
                              temp_r31->cur_anim_frame, ftSk_Init_804D9664,
                              ftSk_Init_804D9660, NULL);
    temp_r31->accessory4_cb = fn_80112ED8;
}

// Kipcode66's scratch at https://decomp.me/scratch/Lda2E seems to match this
void ftSk_SpecialHi_80113390(Fighter_GObj* arg0)
{
    Fighter* temp_r31;

    temp_r31 = arg0->user_data;
    ftCommon_8007D7FC(temp_r31);
    Fighter_ChangeMotionState(arg0, 0x163, 0x0C4C508EU,
                              temp_r31->cur_anim_frame, ftSk_Init_804D9664,
                              ftSk_Init_804D9660, NULL);
    temp_r31->accessory4_cb = fn_80112ED8;
}

// Kipcode66's scratch at https://decomp.me/scratch/6l76B seems to match this
void ftSk_SpecialHiStart_1_Anim(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    fp->mv.sk.specialn.x0 -= 1;

    if (0 >= fp->mv.sk.specialn.x0) {
        ftSk_SpecialHi_80113EAC(gobj);
    }
}

// Animation_SheikUpBTravel

// Gelatart's scratch at https://decomp.me/scratch/tHxCH, forked from a
// kipcode66 scratch
void ftSk_SpecialAirHiStart_1_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.sk.specialhi.x0 -= 1;

    if (fp->mv.sk.specialhi.x0 <= 0) {
        ftSk_SpecialHi_80113F68(gobj);
    }
}

void ftSk_SpecialHiStart_1_IASA(HSD_GObj* gobj) {}

// Interrupt_SheikUpBTravelAir
void ftSk_SpecialAirHiStart_1_IASA(HSD_GObj* gobj) {}

// Physics_SheikUpBTravelAir

// Kipcode66's scratch at https://decomp.me/scratch/jKQKo seems to match this
void ftSk_SpecialHiStart_1_Phys(HSD_GObj* gobj)
{
    ftCommon_8007CB74((Fighter_GObj*) gobj);
}

void ftSk_SpecialAirHiStart_1_Phys(HSD_GObj* gobj) {}

// Kipcode66's scratch at https://decomp.me/scratch/dULMS seems to match this
void ftSk_SpecialHiStart_1_Coll(HSD_GObj* gobj)
{
    s32 temp_r3;
    s32 temp_r3_2;
    Fighter* fp; // r4
    CollData* collData;

    fp = gobj->user_data;
    collData = &fp->coll_data;

    if (ft_80082708((Fighter_GObj*) gobj) == GA_Ground) {
        temp_r3 = collData->env_flags;

        if ((temp_r3 & 0x3F) || (temp_r3 & 0xFC0)) {
            ftCommon_8007D60C((Fighter*) fp);
            ftSk_SpecialHi_80113F68(gobj);
            return;
        }
        ftSk_SpecialHi_8011374C(gobj);
        return;
    }
    temp_r3_2 = collData->env_flags;

    if ((temp_r3_2 & 0x3F) || (temp_r3_2 & 0xFC0)) {
        ftSk_SpecialHi_80113EAC(gobj);
    }
}

/* Kipcode66's scratch at https://decomp.me/scratch/fE7Dq matches this, someone
 * else had to add includes to code to get it to work */
void ftSk_SpecialAirHiStart_1_Coll(HSD_GObj* gobj)
{
    s32 var_r0;
    s32 direction;
    Fighter* fp;             // r31
    Fighter* fp2;            // r3
    ftSeakAttributes* attr;  // r30
    ftSeakAttributes* attr2; // r30
    CollData* collData;      // r29
    s32 unused[6];

    fp = gobj->user_data;
    collData = &fp->coll_data;
    attr = fp->dat_attrs;
    fp->mv.sk.specialhi.xC = (s32) (fp->mv.sk.specialhi.xC + 1);

    if (fp->facing_dir < ftSk_Init_804D9660) {
        direction = -1;
    } else {
        direction = 1;
    }

    if (ft_CheckGroundAndLedge((Fighter_GObj*) gobj, direction) != 0) {
        fp2 = gobj->user_data;
        attr2 = fp2->dat_attrs;
        // M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
        if ((f32) fp2->mv.sk.specialhi.xC >= attr2->x3C) {
            var_r0 = 1;
        } else if (ftCo_8009A134((Fighter_GObj*) gobj) != 0) {
            var_r0 = 0;
        } else {
            var_r0 = 1;
        }
        if (var_r0 != 0) {
            ftSk_SpecialHi_801137C8(gobj);
            return;
        }
    }

    if (ftCliffCommon_80081298((Fighter_GObj*) gobj) == 0) {
        if ((collData->env_flags & 0x6000) &&
            (lbVector_AngleXY(&collData->ceiling.normal, &fp->self_vel) >
             (ftSk_Init_804D9670 * (ftSk_Init_804D9674 + (f32) attr->x50))))
        {
            ftSk_SpecialHi_80113F68(gobj);
        }
        if ((collData->env_flags & 0x3F) &&
            (lbVector_AngleXY(&collData->right_wall.normal, &fp->self_vel) >
             (ftSk_Init_804D9670 * (ftSk_Init_804D9674 + (f32) attr->x50))))
        {
            ftSk_SpecialHi_80113F68(gobj);
        }
        if ((collData->env_flags & 0xFC0) &&
            (lbVector_AngleXY(&collData->left_wall.normal, &fp->self_vel) >
             (ftSk_Init_804D9670 * (ftSk_Init_804D9674 + (f32) attr->x50))))
        {
            ftSk_SpecialHi_80113F68(gobj);
        }
    }
}

// AS_SheikUpBGroundtoAirFall?
// PsiLupan's scratch at https://decomp.me/scratch/HAj21 seems to match this
// Scratch has a comment defining static MotionFlags const coll_mf
void ftSk_SpecialHi_8011374C(Fighter_GObj* gobj)
{
    u32 fighterFlags;
    Fighter* fp = getFighterPlus(gobj);

    ftCommon_8007D60C(fp);

    fighterFlags =
        // 0xC4C
        Ft_MF_SkipModelPartVis | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
        Ft_MF_SkipModelFlags | Ft_MF_Unk27;

    fighterFlags =
        fighterFlags +
        // 0x508E
        (Ft_MF_KeepGfx | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipHit |
         Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd);

    Fighter_ChangeMotionState(gobj, 0x167, fighterFlags, fp->cur_anim_frame,
                              0.0f, 0.0f, 0);

    fp->x2223_b4 = true;
    fp->x221E_b0 = true;
}

// AS_SheikUpBLand
/*
Vicious Grasshopper (anon)'s scratch at https://decomp.me/scratch/p2npY
seems to match this.

Scratch had several warnings at the end about structs not
being defined, if that's of note
*/
void ftSk_SpecialHi_801137C8(Fighter_GObj* gobj)
{
    u32 fighterFlags;
    // f32 animStart, animSpeed;
    // float animFrame;
    Fighter* fp = gobj->user_data;

    ftCommon_8007D7FC(fp);

    fighterFlags =
        // 0xC4C
        Ft_MF_SkipModelPartVis | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
        Ft_MF_SkipModelFlags | Ft_MF_Unk27;

    fighterFlags =
        fighterFlags +
        // 0x508E
        (Ft_MF_KeepGfx | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipHit |
         Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd);

    Fighter_ChangeMotionState(gobj, 0x164, fighterFlags, fp->cur_anim_frame,
                              0.0, 0.0, NULL);
    // fp->unk221E = (u8) (fp->unk221E | 0x80);
    fp->x221E_b0 = true;
}

// AS_SheikUpBTravelGround
/// #ftSk_SpecialHi_80113838

// AS_SheikUpBTravelAir
/// #ftSk_SpecialHi_80113A30

// Grumpy Zebra (anon)'s fork at https://decomp.me/scratch/eGfdU of Gelatart's
// scratch
void ftSk_SpecialHi_Anim(HSD_GObj* gobj)
{
    FORCE_PAD_STACK_8;

    if (ftAnim_IsFramesRemaining((Fighter_GObj*) gobj) == 0) {
        ft_8008A2BC((Fighter_GObj*) gobj);
    }
}

/// #ftSk_SpecialAirHi_Anim

void ftSk_SpecialHi_IASA(HSD_GObj* gobj) {}

// Interrupt_SheikUpBEndAir
void ftSk_SpecialAirHi_IASA(HSD_GObj* gobj) {}

// Gelatart's scratch at https://decomp.me/scratch/dKeEf
void ftSk_SpecialHi_Phys(HSD_GObj* gobj)
{
    ft_80084F3C((Fighter_GObj*) gobj);
}

/// #ftSk_SpecialAirHi_Phys

// Gelatart's scratch at https://decomp.me/scratch/AWQjm
void ftSk_SpecialHi_Coll(HSD_GObj* gobj)
{
    if (ft_800827A0((Fighter_GObj*) gobj) == 0) {
        ftSk_SpecialHi_80113E40(gobj);
    }
}

/// #ftSk_SpecialAirHi_Coll

// Gelatart's scratch at https://decomp.me/scratch/QTuAS
void ftSk_SpecialHi_80113E40(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 0x168, 0x0C4C508AU, fp->cur_anim_frame,
                              ftSk_Init_804D9664, ftSk_Init_804D9660, NULL);
    fp->accessory4_cb = fn_80113038;
}

/// #ftSk_SpecialHi_80113EAC

// AS_SheikUpBFall
/// #ftSk_SpecialHi_80113F68
