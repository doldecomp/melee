#include <platform.h>
#include "forward.h"
#include <dolphin/mtx/forward.h>

#include "ftMt_SpecialLw.h"

#include "ftMt_Init.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftMewtwo/types.h"
#include "it/items/it_27CF.h"
#include "it/items/itmewtwodisable.h"
#include "lb/lb_00B0.h"

// SpecialLw/SpecialAirLw

#define FTMEWTWO_SPECIALLW_COLL_FLAG                                          \
    Ft_MF_KeepGfx | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd | \
        Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |            \
        Ft_MF_SkipModelFlags | Ft_MF_Unk27

// 0x80146198
// https://decomp.me/scratch/QML6g // Reset Disable Stall flag
void ftMt_SpecialLw_ClearDisableGObj(HSD_GObj* gobj)
{
    GET_FIGHTER(gobj)->fv.mt.x222C_disableGObj = NULL;
}

// 0x801461A8
// https://decomp.me/scratch/d5gF6 // Remove Disable projectile
void ftMt_SpecialLw_RemoveDisable(HSD_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->fv.mt.x222C_disableGObj != NULL) {
        it_802C49E0(GET_FIGHTER(gobj)->fv.mt.x222C_disableGObj);
        GET_FIGHTER(gobj)->fv.mt.x222C_disableGObj = NULL;
    }
}

// 0x801461F0
// https://decomp.me/scratch/WnODY // Mewtwo's grounded Disable Motion State
// handler
void ftMt_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    fp->fv.mt.x222C_disableGObj = NULL;

    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialLw, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);

    fp->accessory4_cb = ftMt_SpecialLw_CreateDisable;
}

// 0x80146264
// https://decomp.me/scratch/fX4aP // Mewtwo's aerial Disable Motion State
// handler
void ftMt_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    fp->fv.mt.x222C_disableGObj = NULL;
    fp->self_vel.y = 0.0f;

    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirLw, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);

    fp->accessory4_cb = ftMt_SpecialLw_CreateDisable;
}

// 0x801462DC
//  https://decomp.me/scratch/2no6L // Mewtwo's grounded Disable Animation
//  callback
void ftMt_SpecialLw_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (GET_FIGHTER(gobj)->fv.mt.x222C_disableGObj != NULL) {
            it_802C49E0(GET_FIGHTER(gobj)->fv.mt.x222C_disableGObj);
            GET_FIGHTER(gobj)->fv.mt.x222C_disableGObj = NULL;
        }

        ft_8008A2BC(gobj);
    }
}

// 0x80146338 - Mewtwo's aerial Disable Animation callback
void ftMt_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (GET_FIGHTER(gobj)->fv.mt.x222C_disableGObj != NULL) {
            it_802C49E0(GET_FIGHTER(gobj)->fv.mt.x222C_disableGObj);
            GET_FIGHTER(gobj)->fv.mt.x222C_disableGObj = NULL;
        }
        ftCo_800CC730(gobj);
    }
}

// 0x80146394 - Mewtwo's grounded Disable IASA callback
void ftMt_SpecialLw_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80146398 - Mewtwo's aerial Disable IASA callback
void ftMt_SpecialAirLw_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x8014639C - Mewtwo's grounded Disable Physics callback
void ftMt_SpecialLw_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 0x801463BC
// https://decomp.me/scratch/haV3L // Mewtwo's aerial Disable Physics callback
void ftMt_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);
    ftCo_DatAttrs* ca = getFtAttrs(fp);

    ftCommon_8007D494(fp, mewtwoAttrs->x78_MEWTWO_DISABLE_GRAVITY,
                      mewtwoAttrs->x7C_MEWTWO_DISABLE_TERMINAL_VELOCITY);
    ftCommon_8007CE94(fp, ca->aerial_friction);
}

inline void ftMewtwo_SpecialLw_SetCall(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.mt.x222C_disableGObj != NULL) {
        fp->death2_cb = ftMt_Init_OnDeath2;
        fp->take_dmg_cb = ftMt_Init_OnTakeDamage;
    }
}

// 0x80146410
// https://decomp.me/scratch/ktqvT // Mewtwo's ground -> air Disable Action
// State handler
void ftMt_SpecialLw_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);

    fp->self_vel.y = 0.0f;

    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirLw,
                              FTMEWTWO_SPECIALLW_COLL_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);

    fp->accessory4_cb = ftMt_SpecialLw_CreateDisable;

    ftMewtwo_SpecialLw_SetCall(gobj);

    ftCommon_8007D468(fp);
}

// 0x801464B0
// https://decomp.me/scratch/xNFhq // Mewtwo's air -> ground Disable Action
// State handler
void ftMt_SpecialAirLw_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialLw,
                              FTMEWTWO_SPECIALLW_COLL_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);

    fp->accessory4_cb = ftMt_SpecialLw_CreateDisable;

    ftMewtwo_SpecialLw_SetCall(gobj);
}

// 0x80146544 - Mewtwo's grounded Disable Collision callback
void ftMt_SpecialLw_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, ftMt_SpecialLw_GroundToAir);
}

// 0x8014656C - Mewtwo's aerial Disable Collision callback
void ftMt_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, ftMt_SpecialAirLw_AirToGround);
}

// 0x80146594
// https://decomp.me/scratch/rAoIe // Create Disable projectile
void ftMt_SpecialLw_CreateDisable(HSD_GObj* gobj)
{
    Vec3 sp18;
    Fighter* fp = getFighter(gobj);
    ftMewtwoAttributes* mewtwoAttrs;

    u8 _[4];

    if ((u32) fp->cmd_vars[0] != 0U) {
        mewtwoAttrs = getFtSpecialAttrsD(fp);

        lb_8000B1CC(fp->parts[FtPart_L3rdNb].joint, NULL, &sp18);

        sp18.x += (mewtwoAttrs->x80_MEWTWO_DISABLE_OFFSET_X * fp->facing_dir);
        sp18.y += mewtwoAttrs->x84_MEWTWO_DISABLE_OFFSET_Y;

        fp->fv.mt.x222C_disableGObj = it_802C4A40(gobj, &sp18, fp->facing_dir);

        ftMewtwo_SpecialLw_SetCall(gobj);

        fp->cmd_vars[0] = 0;
    }
}
