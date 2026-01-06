#include "ftMt_SpecialS.h"

#include <platform.h>

#include "forward.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_CaptureCut.h"
#include "ftCommon/ftCo_CaptureMewtwo.h"
#include "ftCommon/ftCo_DamageFall.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_Throw.h"
#include "ftMewtwo/types.h"

#include <dolphin/mtx.h>

// Flag values read during Confusion's reflect think function

#define CONFUSION_REFLECT_NONE                                                \
    0 // Effectively a "wait" state for Confusion (i.e. wait until the flag is
      // either 1 or 2 because 0 does nothing).

#define CONFUSION_REFLECT_ON 1 // Toggle reflect bubble on.

#define CONFUSION_REFLECT_OFF 2 // Toggle reflect bubble off.

// SpecialS/SpecialAirS

#define FTMEWTWO_SPECIALS_COLL_FLAG                                           \
    Ft_MF_KeepGfx | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd | \
        Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |            \
        Ft_MF_SkipModelFlags | Ft_MF_Unk27

// 0x8014665C
// https://decomp.me/scratch/ktG8y // Set flags
static void ftMt_SpecialS_SetFlags(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E2FC(gobj);
    fp->x221E_b6 = 0;
    fp->x2222_b2 = 1;
}

static inline void ftMewtwo_SpecialS_SetGrab(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->victim_gobj == NULL) {
        ftCommon_8007E2D0(fp, 0x40, ftMt_SpecialS_SetFlags, NULL,
                          ftCo_800BCF18);
    } else {
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

// 0x801466C4
// https://decomp.me/scratch/X6OTU // Mewtwo's grounded Confusion Motion State
// handler
void ftMt_SpecialS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    fp->mv.mt.SpecialS.isConfusionReflect = false;

    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialS, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);

    ftMewtwo_SpecialS_SetGrab(gobj);
    fp->accessory4_cb = ftMt_SpecialS_ReflectThink;
}

static inline void ftMewtwo_SpecialAirS_SetGrab(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->victim_gobj == NULL) {
        ftCommon_8007E2D0(fp, 0x40, ftMt_SpecialS_SetFlags, NULL,
                          ftCo_800BD000);
    } else {
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

// 0x8014677C
// https://decomp.me/scratch/4DvVc // Mewtwo's aerial Confusion Motion State
// handler
void ftMt_SpecialAirS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);

    u8 _[8];

    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    fp->mv.mt.SpecialS.isConfusionReflect = false;

    if (fp->fv.mt.x223C_isConfusionBoost == false) {
        fp->self_vel.y = mewtwoAttrs->x18_MEWTWO_CONFUSION_AIR_BOOST;
        fp->fv.mt.x223C_isConfusionBoost = true;
    }

    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirS, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);

    ftMewtwo_SpecialAirS_SetGrab(gobj);
    fp->accessory4_cb = ftMt_SpecialS_ReflectThink;
}

static inline void ftMewtwo_SetGrabVictim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* victimGObj;

    if ((u32) fp->cmd_vars[0] != 0) {
        victimGObj = fp->victim_gobj;
        if (victimGObj != NULL) {
            ftCommon_8007E2F4(fp, 0);
            ftCo_800DE2A8(gobj, victimGObj);
            ftCo_80090780(victimGObj);
            fp->cmd_vars[0] = 0;
        }
    }
}

// 0x80146858
// https://decomp.me/scratch/PYxCI // Mewtwo's grounded Confusion Animation
// callback
void ftMt_SpecialS_Anim(HSD_GObj* gobj)
{
    ftMewtwo_SetGrabVictim(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

// 0x801468EC
// https://decomp.me/scratch/rpTDv // Mewtwo's aerial Confusion Animation
// callback
void ftMt_SpecialAirS_Anim(HSD_GObj* gobj)
{
    ftMewtwo_SetGrabVictim(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

// 0x80146980 - Mewtwo's grounded Confusion IASA callback
void ftMt_SpecialS_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80146984 - Mewtwo's aerial Confusion IASA callback
void ftMt_SpecialAirS_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80146988
// https://decomp.me/scratch/o5TC6 // Mewtwo's grounded Confusion Physics
// callback
void ftMt_SpecialS_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEF8(gobj);
}

// 0x801469BC
// https://decomp.me/scratch/o5TC6 // Mewtwo's aerial Confusion Physics
// callback
void ftMt_SpecialAirS_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
    ftColl_8007AEF8(gobj);
}

static inline void ftMewtwo_SpecialS_SetReflect(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.mt.SpecialS.isConfusionReflect) {
        fp->reflecting = true;
        fp->x2218_b4 = true;
        fp->reflect_hit_cb = ftMt_SpecialS_OnReflect;
    }
}

// 0x801469F0
// https://decomp.me/scratch/W9wyx // Mewtwo's ground -> air Confusion Action
// State handler
void ftMt_SpecialS_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialAirS,
                              FTMEWTWO_SPECIALS_COLL_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);

    ftCommon_ClampAirDrift(fp);

    ftMewtwo_SpecialAirS_SetGrab(gobj);

    fp->accessory4_cb = ftMt_SpecialS_ReflectThink;

    ftMewtwo_SpecialS_SetReflect(gobj);
}

// 0x80146AD4
// https://decomp.me/scratch/gv2WK // Mewtwo's air -> ground Confusion Action
// State handler
void ftMt_SpecialAirS_AirToGround(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftMt_MS_SpecialS,
                              FTMEWTWO_SPECIALS_COLL_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);

    ftMewtwo_SpecialS_SetGrab(gobj);

    fp->accessory4_cb = ftMt_SpecialS_ReflectThink;
    fp->fv.mt.x223C_isConfusionBoost = false;

    ftMewtwo_SpecialS_SetReflect(gobj);
}

// 0x80146BB8 - Mewtwo's grounded Confusion Collision callback
void ftMt_SpecialS_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, ftMt_SpecialS_GroundToAir);
}

// 0x80146BE0 - Mewtwo's aerial Confusion Collision callback
void ftMt_SpecialAirS_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, ftMt_SpecialAirS_AirToGround);
}

// 0x80146C08
// https://decomp.me/scratch/BDCzb // Confusion Reflect think function
void ftMt_SpecialS_ReflectThink(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);
    s32 reflectFlag;

    reflectFlag = fp->cmd_vars[1];
    switch (reflectFlag) {
    case CONFUSION_REFLECT_ON:
        ftColl_CreateReflectHit(
            gobj, &mewtwoAttrs->x1C_MEWTWO_CONFUSION_REFLECTION,
            ftMt_SpecialS_OnReflect); // Really? A callback that simply
                                      // returns instead of just NULL?
        fp->x2218_b4 =
            1; // Here it is... the reason Confusion cannot change ownership.
        fp->mv.mt.SpecialS.isConfusionReflect = true;
        fp->cmd_vars[1] = CONFUSION_REFLECT_NONE;
        return;

    case CONFUSION_REFLECT_OFF:
        if (fp->mv.mt.SpecialS.isConfusionReflect != false) {
            fp->reflecting = false;
            fp->x2218_b4 = false;
            fp->reflect_hit_cb = NULL;
            fp->mv.mt.SpecialS.isConfusionReflect = false;
        }
        fp->cmd_vars[1] = CONFUSION_REFLECT_NONE;
        return;
    }
}

// 0x80146CC8 - Mewtwo's OnReflect callback
void ftMt_SpecialS_OnReflect(HSD_GObj* gobj)
{
    return;
}
