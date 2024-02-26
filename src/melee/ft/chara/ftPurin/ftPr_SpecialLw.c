#include "forward.h"

#include "ftPr_SpecialLw.h"

#include "ftPr_SpecialHi.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftPurin/types.h"

#include <common_structs.h>
#include <placeholder.h>
#include <baselib/archive.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/objalloc.h>

extern float const ftPr_Init_804D9C20;
extern float const ftPr_Init_804D9C24;
extern float const ftPr_Init_804D9C28;

void ftPr_SpecialLw_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    u8 _[8];

    if (ftPr_Init_804D9C20 == fp->facing_dir) {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialLwL, 0U,
                                  ftPr_Init_804D9C24, ftPr_Init_804D9C28,
                                  ftPr_Init_804D9C24, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialLwR, 0U,
                                  ftPr_Init_804D9C24, ftPr_Init_804D9C28,
                                  ftPr_Init_804D9C24, NULL);
    }
    ftAnim_8006EBA4(gobj);
    fp = gobj->user_data;
    fp->cmd_vars[0] = 0;
    fp->accessory4_cb = &ftPr_SpecialHi_8013CE7C;
}

void ftPr_SpecialAirLw_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    u8 _[8];

    if (ftPr_Init_804D9C20 == fp->facing_dir) {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirLwL, 0U,
                                  ftPr_Init_804D9C24, ftPr_Init_804D9C28,
                                  ftPr_Init_804D9C24, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirLwR, 0U,
                                  ftPr_Init_804D9C24, ftPr_Init_804D9C28,
                                  ftPr_Init_804D9C24, NULL);
    }
    ftAnim_8006EBA4(gobj);
    fp = gobj->user_data;
    fp->cmd_vars[0] = 0;
    fp->accessory4_cb = &ftPr_SpecialHi_8013CE7C;
}

void ftPr_SpecialLw_Anim(Fighter_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ft_8008A2BC(fighter_gobj);
    }
}

void ftPr_SpecialAirLw_Anim(Fighter_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ftCo_800CC730(fighter_gobj);
    }
}

void ftPr_SpecialLw_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialAirLw_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialLw_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPr_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftPr_SpecialLw_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftPr_SpecialLw_8013D104(gobj);
    }
}

void ftPr_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftPr_SpecialLw_8013D19C(gobj);
    }
}

void ftPr_SpecialLw_8013D104(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    if (ftPr_Init_804D9C20 == fp->facing_dir) {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirLwL, 0x0C4C508EU,
                                  fp->cur_anim_frame, ftPr_Init_804D9C28,
                                  ftPr_Init_804D9C24, NULL);
        return;
    }
    Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirLwR, 0x0C4C508EU,
                              fp->cur_anim_frame, ftPr_Init_804D9C28,
                              ftPr_Init_804D9C24, NULL);
}

void ftPr_SpecialLw_8013D19C(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D7FC(fp);
    if (ftPr_Init_804D9C20 == fp->facing_dir) {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialLwL, 0x0C4C508EU,
                                  fp->cur_anim_frame, ftPr_Init_804D9C28,
                                  ftPr_Init_804D9C24, NULL);
        return;
    }
    Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialLwR, 0x0C4C508EU,
                              fp->cur_anim_frame, ftPr_Init_804D9C28,
                              ftPr_Init_804D9C24, NULL);
}

extern float const ftPr_Init_804D9C30;
extern float const ftPr_Init_804D9C38;

void ftPr_SpecialS_Enter(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter = GET_FIGHTER(fighter_gobj);
    Fighter_ChangeMotionState(fighter_gobj, 0x16B, 0, ftPr_Init_804D9C30,
                              ftPr_Init_804D9C38, ftPr_Init_804D9C30, NULL);
    ftAnim_8006EBA4(fighter_gobj);
    fighter->cmd_vars[0] = fighter->cmd_vars[1] = fighter->cmd_vars[2] =
        fighter->cmd_vars[3] = 0;
}

void ftPr_SpecialAirS_Enter(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter = GET_FIGHTER(fighter_gobj);

    Fighter_ChangeMotionState(fighter_gobj, 0x16C, 0, ftPr_Init_804D9C30,
                              ftPr_Init_804D9C38, ftPr_Init_804D9C30, NULL);
    ftAnim_8006EBA4(fighter_gobj);
    fighter->cmd_vars[0] = fighter->cmd_vars[1] = fighter->cmd_vars[2] =
        fighter->cmd_vars[3] = 0;
}

void ftPr_SpecialS_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

void ftPr_SpecialAirS_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCo_800CC730(gobj);
    }
}

void ftPr_SpecialS_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialAirS_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialS_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

extern float const ftPr_Init_804D9C34;

/// #ftPr_SpecialAirS_Phys

void ftPr_SpecialS_Coll(Fighter_GObj* gobj)
{
    if (ft_800827A0(gobj) == GA_Ground) {
        ftPr_SpecialS_8013D590(gobj);
    }
}

void ftPr_SpecialAirS_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftPr_SpecialS_8013D5F0(gobj);
    }
}

void ftPr_SpecialS_8013D590(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirS, 0x0C4C508AU,
                              fp->cur_anim_frame, ftPr_Init_804D9C38,
                              ftPr_Init_804D9C30, NULL);
}

void ftPr_SpecialS_8013D5F0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialS, 0x0C4C508AU,
                              fp->cur_anim_frame, ftPr_Init_804D9C38,
                              ftPr_Init_804D9C30, NULL);
    ftCommon_8007D468(fp);
}

extern char* ftPr_Init_804D3E98;
extern char* ftPr_Init_804D3EA0;
extern char* ftPr_Init_804D3EA8;
extern f64 const ftPr_Init_804D9C40;
extern float const ftPr_Init_804D9C48;

/// #ftPr_SpecialS_8013D658

extern float const ftPr_Init_804D9C4C;

/// #ftPr_SpecialS_8013D764

void ftPr_SpecialS_8013D8B0(Fighter_GObj* gobj)
{
    ft_80089824(gobj);
    ft_800892A0(gobj);
}

/// #ftPr_SpecialS_8013D8E4

extern float const ftPr_Init_804D9C50;

/// #ftPr_SpecialS_8013DA24

/// #ftPr_SpecialS_8013DC64

extern f64 const ftPr_Init_804D9C58;
extern float const ftPr_Init_804D9C60;

/// #ftPr_SpecialS_8013DD54

/// #ftPr_SpecialN_Enter

/// #ftPr_SpecialAirN_Enter

extern float const ftPr_Init_804D9C64;

/// #ftPr_SpecialNStart_Anim

extern float const ftPr_Init_804D9C68;
extern f64 const ftPr_Init_804D9C70;

/// #ftPr_SpecialNLoop_Anim

/// #ftPr_SpecialNFull_Anim

extern f64 const ftPr_Init_804D9C78;
extern f64 const ftPr_Init_804D9C80;
extern f64 const ftPr_Init_804D9C88;

/// #ftPr_SpecialNRelease_Anim

/// #ftPr_SpecialNTurn_Anim

/// #ftPr_SpecialNEnd_Anim

/// #ftPr_SpecialAirNStart_Anim

/// #ftPr_SpecialAirNChargeLoop_Anim

/// #ftPr_SpecialAirNChargeFull_Anim

/// #ftPr_SpecialAirNChargeRelease_Anim

/// #ftPr_SpecialAirNStartTurn_Anim

/// #ftPr_SpecialAirNEnd_Anim

/// #ftPr_SpecialNHit_Anim

void ftPr_SpecialNStart_IASA(HSD_GObj* arg0) {}

/// #ftPr_SpecialNLoop_IASA

/// #ftPr_SpecialNFull_IASA

extern float const ftPr_Init_804D9C90;

/// #ftPr_SpecialNRelease_IASA

void ftPr_SpecialNTurn_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialNEnd_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialAirNStart_IASA(HSD_GObj* arg0) {}

/// #ftPr_SpecialAirNChargeLoop_IASA

/// #ftPr_SpecialAirNChargeFull_IASA

void ftPr_SpecialAirNChargeRelease_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialAirNStartTurn_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialAirNEnd_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialNHit_IASA(HSD_GObj* arg0) {}

void ftPr_SpecialNStart_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->xE4_ground_accel_1 = ftPr_Init_804D9C48;
    fp->gr_vel = ftPr_Init_804D9C48;
    fp->self_vel.x = ftPr_Init_804D9C64 * fp->facing_dir;
    fp->self_vel.y = ftPr_Init_804D9C48;
    fp->x74_anim_vel.y = ftPr_Init_804D9C48;
    fp->x74_anim_vel.x = ftPr_Init_804D9C48;
}

void ftPr_SpecialNLoop_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->xE4_ground_accel_1 = ftPr_Init_804D9C48;
    fp->gr_vel = ftPr_Init_804D9C48;
    fp->self_vel.x = ftPr_Init_804D9C64 * fp->facing_dir;
    fp->self_vel.y = ftPr_Init_804D9C48;
    fp->x74_anim_vel.y = ftPr_Init_804D9C48;
    fp->x74_anim_vel.x = ftPr_Init_804D9C48;
}

void ftPr_SpecialNFull_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->xE4_ground_accel_1 = ftPr_Init_804D9C48;
    fp->gr_vel = ftPr_Init_804D9C48;
    fp->self_vel.x = ftPr_Init_804D9C64 * fp->facing_dir;
    fp->self_vel.y = ftPr_Init_804D9C48;
    fp->x74_anim_vel.y = ftPr_Init_804D9C48;
    fp->x74_anim_vel.x = ftPr_Init_804D9C48;
}

/// #ftPr_SpecialNRelease_Phys

/// #ftPr_SpecialNTurn_Phys

void ftPr_SpecialNEnd_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007C930(fp, fp->co_attrs.gr_friction);
    ftCommon_8007CB74(gobj);
}

void ftPr_SpecialAirNStart_Phys(HSD_GObj* gobj)
{
    Fighter* fp;
    ftPurinAttributes* da;

    fp = gobj->user_data;
    da = fp->dat_attrs;
    ftCommon_8007D494(fp, da->x3C, da->x40);
}

void ftPr_SpecialAirNChargeLoop_Phys(HSD_GObj* gobj)
{
    Fighter* fp;
    ftPurinAttributes* da;

    fp = gobj->user_data;
    da = fp->dat_attrs;
    ftCommon_8007D494(fp, da->x3C, da->x40);
}

void ftPr_SpecialAirNChargeFull_Phys(HSD_GObj* gobj)
{
    Fighter* fp;
    ftPurinAttributes* da;

    fp = gobj->user_data;
    da = fp->dat_attrs;
    ftCommon_8007D494(fp, da->x3C, da->x40);
}

/// #ftPr_SpecialAirNChargeRelease_Phys

/// #ftPr_SpecialAirNStartTurn_Phys

void ftPr_SpecialAirNEnd_Phys(HSD_GObj* gobj)
{
    Fighter* fp;
    ftPurinAttributes* da;

    fp = gobj->user_data;
    da = fp->dat_attrs;
    ftCommon_8007D494(fp, da->x3C, da->x40);
}

void ftPr_SpecialNHit_Phys(HSD_GObj* gobj)
{
    Fighter* fp;
    ftPurinAttributes* da;
    u8 _[8];

    fp = gobj->user_data;
    da = fp->dat_attrs;

    if (fp->self_vel.y <= -da->x40) {
        ftCommon_8007D268(fp);
    }
    ftCommon_8007D494(fp, da->x3C, da->x40);
}

// Non-matching due to float allocation https://decomp.me/scratch/OYlcJ
void ftPr_SpecialNStart_Coll(HSD_GObj* gobj)
{
    s32 state;
    Fighter* fp;
    u8 _[8];

    fp = gobj->user_data;
    if (ft_80082708((Fighter_GObj*) gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        if (ftPr_Init_804D9C50 == fp->mv.pr.specialn.x34) {
            state = ftPr_MS_SpecialAirNStartR;
        } else {
            state = ftPr_MS_SpecialAirNStartL;
        }
        Fighter_ChangeMotionState((Fighter_GObj*) gobj, state, 0x0C4C5092U,
                                  fp->cur_anim_frame, ftPr_Init_804D9C50,
                                  ftPr_Init_804D9C48, NULL);
        fp = gobj->user_data;
        fp->death2_cb = ftPr_SpecialS_8013D658;
        fp->take_dmg_cb = ftPr_SpecialS_8013D658;
        fp->deal_dmg_cb = ftPr_SpecialS_8013D764;
        fp->x21F8 = ftPr_SpecialN_8014222C;
    }
}

/// #ftPr_SpecialNLoop_Coll

/// #ftPr_SpecialNFull_Coll

extern float const ftPr_Init_804D9C54;

/// #ftPr_SpecialNRelease_Coll

/// #ftPr_SpecialNTurn_Coll

void ftPr_SpecialNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        ftPr_SpecialS_8013DA24(gobj, 1, 0x0C4C5092, fp->cur_anim_frame);
    }
}

/// #ftPr_SpecialAirNStart_Coll

/// #ftPr_SpecialAirNChargeLoop_Coll

/// #ftPr_SpecialAirNChargeFull_Coll

/// #ftPr_SpecialAirNChargeRelease_Coll

/// #ftPr_SpecialAirNStartTurn_Coll

void ftPr_SpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        ftPr_SpecialS_8013DA24(gobj, 0, 0x0C4C5092, fp->cur_anim_frame);
    }
}

/// #ftPr_SpecialNHit_Coll

/// #ftPr_SpecialN_8014222C
