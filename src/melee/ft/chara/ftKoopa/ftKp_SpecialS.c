#include <platform.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"
#include "ftKoopa/forward.h"
#include <baselib/forward.h>

#include "ft/fighter.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_CaptureDamageKoopa.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_ThrownKoopa.h"
#include "ftKoopa/ftKp_Init.h"

#include <baselib/gobj.h>

inline void inlineA0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.kp.specials.x4) {
        Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialAirSHit1,
                                  Ft_MF_SkipMatAnim, 0, 1, 0, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialAirSHit0_0, Ft_MF_None,
                                  0, 1, 0, NULL);
    }
    fp->x2222_b2 = true;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E2FC(gobj);
    fp->mv.kp.specials.b_held = false;
    fp->cmd_vars[0] = 0;
}

static inline void inlineA1(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKp_MS_SpecialAirSHit0_1,
                              Ft_MF_SkipMatAnim | Ft_MF_Unk19,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftAnim_8006F0FC(gobj, 0);
    fp->mv.kp.specials.b_held = false;
    fp->cmd_vars[0] = 0;
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftKp_SpecialAirSHit_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 2);
    if (fp->cmd_vars[0] != 0 && fp->mv.kp.specials.x4) {
        ftColl_8007ABD0(fp->x914, da->x2C, gobj);
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.kp.specials.b_held) {
            fp->mv.kp.specials.x4 = true;
            inlineA0(gobj);
            ftCo_800BCAF4(fp->victim_gobj);
        } else {
            inlineA1(gobj);
        }
    }
}

void ftKp_SpecialSWait_Anim(HSD_GObj* gobj) {}

void ftKp_SpecialAirSWait_Anim(HSD_GObj* gobj) {}

static inline void doEndFAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FORCE_PAD_STACK(4 * 2);
    if (ftCheckThrowB4(fp)) {
        fp->facing_dir = -fp->facing_dir;
        fp->mv.kp.specials.xC = true;
    }
    if (fp->cmd_vars[0] != 0) {
        HSD_GObj* victim_gobj = fp->victim_gobj;
        if (victim_gobj != NULL) {
            ftCommon_8007E2F4(fp, 0);
            ftCo_800DE2A8(gobj, victim_gobj);
            ftCo_800DE7C0(victim_gobj, 0, 0);
            fp->cmd_vars[0] = 0;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

void ftKp_SpecialSEndF_Anim(HSD_GObj* gobj)
{
    doEndFAnim(gobj, ft_8008A2BC);
}

static inline void doEndBAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    FORCE_PAD_STACK(4 * 2);
    ftKp_SpecialS_80132E30(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

void ftKp_SpecialSEndB_Anim(HSD_GObj* gobj)
{
    doEndBAnim(gobj, ft_8008A2BC);
}

void ftKp_SpecialAirSEndF_Anim(HSD_GObj* gobj)
{
    doEndFAnim(gobj, ftCo_800CC730);
}

void ftKp_SpecialAirSEndB_Anim(HSD_GObj* gobj)
{
    doEndBAnim(gobj, ftCo_800CC730);
}

inline void ftKoopa_SpecialS_ChangeAction(HSD_GObj* gobj,
                                          ftKoopa_MotionState kp_msid_f,
                                          ftCommon_MotionState victim_msid_f,
                                          ftKoopa_MotionState kp_msid_b,
                                          ftCommon_MotionState victim_msid_b)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    if (fp->mv.kp.specials.facing_dir == +1) {
        Fighter_ChangeMotionState(gobj, kp_msid_f, Ft_MF_Unk19, 0, 1, 0, NULL);
        ftCo_800BCDE0(fp->victim_gobj, victim_msid_f);
    } else {
        Fighter_ChangeMotionState(gobj, kp_msid_b, Ft_MF_Unk19, 0, 1, 0, NULL);
        ftCo_800BCDE0(fp->victim_gobj, victim_msid_b);
    }
}

/// @todo Shared inline with #ftKp_SpecialAirSHit_IASA.
void ftKp_SpecialSHit_IASA(HSD_GObj* gobj)
{
    int facing_dir;
    /// @todo @c da can't move below @ fp.
    ftKoopaAttributes* da;
    Fighter* fp = GET_FIGHTER(gobj);
    da = fp->dat_attrs;
    PAD_STACK(4 * 4);
    facing_dir = 0;
    if (fp->input.x668 & HSD_PAD_B) {
        fp->mv.kp.specials.b_held = true;
    }
    if (fp->input.lstick1.x > -da->x30 && fp->input.lstick.x < -da->x30) {
        facing_dir = -1;
    }
    if (fp->input.lstick1.x < da->x30 && fp->input.lstick.x > da->x30) {
        facing_dir = +1;
    }
    fp->mv.kp.specials.facing_dir = fp->facing_dir * facing_dir;

    if (facing_dir != 0) {
        ftKoopa_SpecialS_ChangeAction(
            gobj, ftKp_MS_SpecialSEndF, ftCo_MS_ThrownKoopaF,
            ftKp_MS_SpecialSEndB, ftCo_MS_ThrownKoopaB);
    }
}

/// @todo Shared inline with #ftKp_SpecialSHit_IASA.
void ftKp_SpecialAirSHit_IASA(HSD_GObj* gobj)
{
    int facing_dir;
    /// @todo @c da can't move below @ fp.
    ftKoopaAttributes* da;
    Fighter* fp = GET_FIGHTER(gobj);
    da = fp->dat_attrs;
    PAD_STACK(4 * 4);
    facing_dir = 0;
    if (fp->input.x668 & HSD_PAD_B) {
        fp->mv.kp.specials.b_held = true;
    }
    if (fp->input.lstick1.x > -da->x30 && fp->input.lstick.x < -da->x30) {
        facing_dir = -1;
    }
    if (fp->input.lstick1.x < da->x30 && fp->input.lstick.x > da->x30) {
        facing_dir = +1;
    }
    fp->mv.kp.specials.facing_dir = fp->facing_dir * facing_dir;

    if (facing_dir != 0) {
        ftKoopa_SpecialS_ChangeAction(
            gobj, ftKp_MS_SpecialAirSEndF, ftCo_MS_ThrownKoopaAirF,
            ftKp_MS_SpecialAirSEndB, ftCo_MS_ThrownKoopaAirB);
    }
}

/// #ftKp_SpecialSWait_IASA

/// #ftKp_SpecialAirSWait_IASA

/// #ftKp_SpecialSStart_Phys

/// #ftKp_SpecialAirSStart_Phys

/// #ftKp_SpecialSHit_Phys

/// #ftKp_SpecialAirSHit_Phys

/// #ftKp_SpecialSWait_Phys

/// #ftKp_SpecialAirSWait_Phys

/// #ftKp_SpecialSEndF_Phys

/// #ftKp_SpecialSEndB_Phys

/// #ftKp_SpecialAirSEndF_Phys

/// #ftKp_SpecialAirSEndB_Phys

/// #ftKp_SpecialSStart_Coll

/// #ftKp_SpecialAirSStart_Coll

/// #ftKp_SpecialSHit_Coll

/// #ftKp_SpecialAirSHit_Coll

/// #ftKp_SpecialSWait_Coll

/// #ftKp_SpecialAirSWait_Coll

/// #ftKp_SpecialSEndF_Coll

/// #ftKp_SpecialSEndB_Coll

/// #ftKp_SpecialAirSEndF_Coll

/// #ftKp_SpecialAirSEndB_Coll

/// #fn_80134518

/// #fn_80134590

/// #ftKp_SpecialLw_Enter

/// #ftKp_SpecialAirLw_Enter

/// #ftKp_SpecialLw_Anim

/// #ftKp_SpecialAirLw_Anim

/// #ftKp_SpecialLw_Phys

/// #ftKp_SpecialAirLw_Phys

/// #ftKp_SpecialLw_Coll

/// #ftKp_SpecialAirLw_Coll

/// #ftKp_SpecialLw_80134988

/// #ftKp_SpecialLwLanding_Anim

/// #ftKp_SpecialLwLanding_Phys

/// #ftKp_SpecialLwLanding_Coll

/// #ftKp_SpecialLw_80134A5C

/// #ftKp_SpecialLw_80134ACC

/// #ftKp_SpecialLw_80134D78

/// #ftKp_SpecialLw_80134DE0

/// #ftKp_SpecialLw_80134E1C

/// #ftKp_SpecialN_Enter

/// #ftKp_SpecialAirN_Enter

/// #ftKp_SpecialNStart_Anim

/// #ftKp_SpecialN_Anim

/// #ftKp_SpecialNEnd_Anim

/// #ftKp_SpecialAirNStart_Anim

/// #ftKp_SpecialAirN_Anim

/// #ftKp_SpecialAirNEnd_Anim

void ftKp_SpecialNStart_IASA(HSD_GObj* gobj) {}

/// #ftKp_SpecialN_IASA

void ftKp_SpecialNEnd_IASA(HSD_GObj* gobj) {}

void ftKp_SpecialAirNStart_IASA(HSD_GObj* gobj) {}

/// #ftKp_SpecialAirN_IASA

void ftKp_SpecialAirNEnd_IASA(HSD_GObj* gobj) {}

/// #ftKp_SpecialNStart_Phys

/// #ftKp_SpecialN_Phys

/// #ftKp_SpecialNEnd_Phys

/// #ftKp_SpecialAirNStart_Phys

/// #ftKp_SpecialAirN_Phys

/// #ftKp_SpecialAirNEnd_Phys

/// #ftKp_SpecialNStart_Coll

/// #ftKp_SpecialN_Coll

/// #ftKp_SpecialNEnd_Coll

/// #ftKp_SpecialAirNStart_Coll

/// #ftKp_SpecialAirN_Coll

/// #ftKp_SpecialAirNEnd_Coll

/// #ftKp_SpecialN_80135780

/// #ftKp_SpecialHi_Enter

/// #ftKp_SpecialAirHi_Enter

/// #ftKp_SpecialHi_Anim

/// #ftKp_SpecialAirHi_Anim

void ftKp_SpecialHi_IASA(HSD_GObj* gobj) {}

void ftKp_SpecialAirHi_IASA(HSD_GObj* gobj) {}

/// #ftKp_SpecialHi_Phys

/// #ftKp_SpecialAirHi_Phys

/// #ftKp_SpecialHi_Coll

/// #ftKp_SpecialAirHi_Coll
