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
#include <placeholder.h>
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

extern float const ftPr_Init_804D9C48;

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
        ft_80088148(fp, 250070, 127, 64);
    }
}

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
    int state;
    Fighter* fp;
    u8 _[8];

    fp = gobj->user_data;
    if (ft_80082708((Fighter_GObj*) gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        if (ftPr_Init_804D9C50 == fp->mv.pr.specialn.x34.x) {
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
