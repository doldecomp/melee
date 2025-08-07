#include <placeholder.h>

#include "forward.h"
#include "ft/forward.h"

#include "ftPr_SpecialN.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftPurin/types.h"

#include <common_structs.h>
#include <math.h>
#include <baselib/archive.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/objalloc.h>

void ftPr_SpecialS_8013D658(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObjSetScale(jobj, &fp->fv.pr.x2230);
    ftParts_80075AF0(fp, FtPart_TopN, M_PI_2 * fp->facing_dir);
    if (fp->mv.pr.specialn.facing_dir != 0) {
        fp->facing_dir = fp->mv.pr.specialn.facing_dir;
    }
    fp->mv.pr.specialn.facing_dir = 0;
}

void ftPr_SpecialS_8013D764(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 9) |
                          (1 << 18) | (1 << 19) | (1 << 22) | (1 << 26) |
                          (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    PAD_STACK(4);

    fp->mv.pr.specialn.xC = 0;
    switch (fp->motion_id) {
    case ftPr_MS_SpecialNRelease:
    case ftPr_MS_SpecialNTurn:
    case ftPr_MS_SpecialAirNChargeRelease:
    case ftPr_MS_SpecialAirNStartTurn:
        fp->mv.pr.specialn.x0 -= da->x38;
        fp->facing_dir = fp->mv.pr.specialn.x34.x;

        ftColl_8007AFF8(gobj);
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialNHit, mf,
                                  fp->cur_anim_frame, 0, 0, NULL);

        fp->death2_cb = ftPr_SpecialS_8013D658;
        fp->take_dmg_cb = ftPr_SpecialS_8013D658;
        fp->deal_dmg_cb = NULL;

        if (fp->ground_or_air == GA_Ground) {
            fp->self_vel.x = fp->gr_vel * da->specialn_vel.x;
            ftCommon_8007D5D4(fp);
        } else {
            fp->self_vel.x *= da->specialn_vel.x;
        }

        fp->self_vel.y = da->specialn_vel.y;
        fp->x74_anim_vel.x = fp->x74_anim_vel.y = 0;
        fp->xE4_ground_accel_1 = 0;
        fp->gr_vel = 0;
        fp->mv.pr.specialn.facing_dir = 0;

        ftParts_80075AF0(fp, FtPart_TopN, M_PI_2);
        ft_PlaySFX(fp, 250070, 127, 64);
    }
}

void ftPr_SpecialS_8013D8B0(Fighter_GObj* gobj)
{
    ft_80089824(gobj);
    ft_800892A0(gobj);
}

/// #ftPr_SpecialS_8013D8E4

/// #ftPr_SpecialS_8013DA24

/// #ftPr_SpecialS_8013DC64

/// #ftPr_SpecialS_8013DD54

void ftPr_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 4);
    fp->mv.pr.specialn.x34.x = fp->facing_dir;
    {
        int msid;
        if (fp->mv.pr.specialn.x34.x == 1) {
            msid = ftPr_MS_SpecialNStartR;
        } else {
            msid = ftPr_MS_SpecialNStartL;
        }
        Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
    }
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftAnim_8006EBA4(gobj);
    ftPr_SpecialS_8013DC64(gobj);
    fp->x74_anim_vel.y = 0;
    fp->self_vel.y = 0;
    fp->mv.pr.specialn.x1C = da->x44;
}

/// #ftPr_SpecialAirN_Enter

/// #ftPr_SpecialNStart_Anim

/// #ftPr_SpecialNLoop_Anim

/// #ftPr_SpecialNFull_Anim

/// #ftPr_SpecialNRelease_Anim

/// #ftPr_SpecialNTurn_Anim

/// #ftPr_SpecialNEnd_Anim

static inline void setupPurinCallbacks(HSD_GObj* gobj)
{
    Fighter* temp_r5;
    temp_r5 = gobj->user_data;
    temp_r5->death2_cb = ftPr_SpecialS_8013D658;
    temp_r5->take_dmg_cb = ftPr_SpecialS_8013D658;
    temp_r5->deal_dmg_cb = ftPr_SpecialS_8013D764;
    temp_r5->x21F8 = ftPr_SpecialN_8014222C;
}

void ftPr_SpecialAirNStart_Anim(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 18);
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 4);
    fp->mv.pr.specialn.facing_dir = 0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftPr_MS_SpecialAirNChargeLoop, mf, 0,
                                  0, 0, NULL);
        setupPurinCallbacks(gobj);
        fp->cur_anim_frame = 0;
        ftAnim_SetAnimRate(gobj, 0);
        fp->self_vel.x = fp->facing_dir * 0.0001f;
        fp->x74_anim_vel.x = 0;
        ftParts_80075AF0(fp, 0, M_PI_2);
    }
}
/// #ftPr_SpecialAirNChargeLoop_Anim

/// #ftPr_SpecialAirNChargeFull_Anim

/// #ftPr_SpecialAirNChargeRelease_Anim

/// #ftPr_SpecialAirNStartTurn_Anim

/// #ftPr_SpecialAirNEnd_Anim

/// #ftPr_SpecialNHit_Anim

void ftPr_SpecialNStart_IASA(HSD_GObj* arg0) {}

/// #ftPr_SpecialNLoop_IASA

/// #ftPr_SpecialNFull_IASA

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
    Fighter* fp = GET_FIGHTER(gobj);
    fp->xE4_ground_accel_1 = 0;
    fp->gr_vel = 0;
    fp->self_vel.x = fp->facing_dir * 0.0001f;
    fp->self_vel.y = 0;
    fp->x74_anim_vel.y = 0;
    fp->x74_anim_vel.x = 0;
}

void ftPr_SpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ftPr_SpecialNStart_Phys(gobj);
}

void ftPr_SpecialNFull_Phys(Fighter_GObj* gobj)
{
    ftPr_SpecialNStart_Phys(gobj);
}

/// #ftPr_SpecialNRelease_Phys

/// #ftPr_SpecialNTurn_Phys

void ftPr_SpecialNEnd_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
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
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
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
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    ftCommon_8007D494(fp, da->x3C, da->x40);
}

void ftPr_SpecialNHit_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPurinAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 2);

    if (fp->self_vel.y <= -da->x40) {
        ftCommon_8007D268(fp);
    }
    ftCommon_8007D494(fp, da->x3C, da->x40);
}

void ftPr_SpecialNStart_Coll(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        {
            int msid;
            if (fp->mv.pr.specialn.x34.x == 1) {
                msid = ftPr_MS_SpecialAirNStartR;
            } else {
                msid = ftPr_MS_SpecialAirNStartL;
            }
            Fighter_ChangeMotionState(gobj, msid, mf, fp->cur_anim_frame, 1, 0,
                                      NULL);
        }
        {
            Fighter* fp = GET_FIGHTER(gobj);
            fp->death2_cb = ftPr_SpecialS_8013D658;
            fp->take_dmg_cb = ftPr_SpecialS_8013D658;
            fp->deal_dmg_cb = ftPr_SpecialS_8013D764;
            fp->x21F8 = ftPr_SpecialN_8014222C;
        }
    }
}

/// #ftPr_SpecialNLoop_Coll

/// #ftPr_SpecialNFull_Coll

/// #ftPr_SpecialNRelease_Coll

/// #ftPr_SpecialNTurn_Coll

void ftPr_SpecialNEnd_Coll(Fighter_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        ftPr_SpecialS_8013DA24(gobj, true, mf, fp->cur_anim_frame);
    }
}

/// #ftPr_SpecialAirNStart_Coll

/// #ftPr_SpecialAirNChargeLoop_Coll

/// #ftPr_SpecialAirNChargeFull_Coll

/// #ftPr_SpecialAirNChargeRelease_Coll

/// #ftPr_SpecialAirNStartTurn_Coll

/// @todo Maybe shared inline with #ftPr_SpecialNEnd_Coll?
void ftPr_SpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        ftPr_SpecialS_8013DA24(gobj, false, mf, fp->cur_anim_frame);
    }
}

/// #ftPr_SpecialNHit_Coll

/// #ftPr_SpecialN_8014222C
