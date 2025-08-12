#include "ftMs_SpecialN.h"

#include "math.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/eflib.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"

#include "ftMars/forward.h"

#include "ftMars/ftMs_Init.h"
#include "ftMars/types.h"

#include "lb/forward.h"

#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <baselib/forward.h>

#include <common_structs.h>
#include <dolphin/mtx.h>

void ftMs_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 2);
    fp->x21EC = ftMs_SpecialN_80136730;
    fp->gr_vel /= da->specialn_friction;
    Fighter_ChangeMotionState(gobj, ftMs_MS_SpecialNStart, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
}

void ftMs_SpecialAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 2);
    fp->x21EC = ftMs_SpecialN_80136730;
    fp->self_vel.x /= da->specialn_friction;
    if (fp->self_vel.y <= 0) {
        fp->self_vel.y = 0;
    }
    Fighter_ChangeMotionState(gobj, ftMs_MS_SpecialAirNStart, Ft_MF_None, 0, 1,
                              0, NULL);
    ftAnim_8006EBA4(gobj);
}

static inline void doStartAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
        {
            Fighter* fp = GET_FIGHTER(gobj);
            if (fp->kind == FTKIND_MARS) {
                ftCo_800BFFD0(fp, 99, 0);
            } else {
                ftCo_800BFFD0(fp, 100, 0);
            }
        }
    }
}

void ftMs_SpecialNStart_Anim(HSD_GObj* gobj)
{
    doStartAnim(gobj, ftMs_SpecialN_80136E74);
}

void ftMs_SpecialAirNStart_Anim(HSD_GObj* gobj)
{
    doStartAnim(gobj, ftMs_SpecialN_80136EAC);
}

void ftMs_SpecialNStart_IASA(HSD_GObj* gobj) {}

void ftMs_SpecialAirNStart_IASA(HSD_GObj* gobj) {}

void ftMs_SpecialNStart_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 2);
    ftCommon_8007C930(fp, da->x10);
    ftCommon_8007CB74(gobj);
}

void ftMs_SpecialAirNStart_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 2);
    ftCommon_8007D4B8(fp);
    ftCommon_8007CE94(fp, da->x10);
}

void ftMs_SpecialNStart_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftMs_SpecialN_80136A1C(gobj);
    }
}

void ftMs_SpecialAirNStart_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftMs_SpecialN_80136A7C(gobj);
    }
}

void ftMs_SpecialN_80136A1C(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 2) | (1 << 7) | (1 << 12) | (1 << 14) |
                          (1 << 18) | (1 << 19) | (1 << 22) | (1 << 26) |
                          (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftMs_MS_SpecialAirNStart, mf,
                              fp->cur_anim_frame, 1, 0, NULL);
}

void ftMs_SpecialN_80136A7C(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 2) | (1 << 7) | (1 << 12) | (1 << 14) |
                          (1 << 18) | (1 << 19) | (1 << 22) | (1 << 26) |
                          (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftMs_MS_SpecialNStart, mf,
                              fp->cur_anim_frame, 1, 0, 0);
}

static inline void doLoopAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    FORCE_PAD_STACK_8;
    {
        Fighter* fp = GET_FIGHTER(gobj);
        MarsAttributes* da = fp->dat_attrs;
        FORCE_PAD_STACK_16;
        {
            Vec3 pos;
            if (fp->mv.ms.specialn.cur_frame % 30 == 0) {
                lb_8000B1CC(
                    fp->parts[ftParts_GetBoneIndex(fp, FtPart_HipN)].joint,
                    NULL, &pos);
                lb_800119DC(&pos, 10, 0.5, 0.05, 60 * deg_to_rad);
            }
            ++fp->mv.ms.specialn.cur_frame;
            if (fp->mv.ms.specialn.cur_frame > da->x0 * 30) {
                fp->cmd_vars[0] = true;
                cb(gobj);
            }
        }
    }
}

void ftMs_SpecialNLoop_Anim(HSD_GObj* gobj)
{
    doLoopAnim(gobj, ftMs_SpecialN_80137354);
}

void ftMs_SpecialAirNLoop_Anim(HSD_GObj* gobj)
{
    doLoopAnim(gobj, ftMs_SpecialN_801373B8);
}

static inline void doLoopIasa(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->cmd_vars[0] = 0;
        cb(gobj);
    }
}

/// Interrupt_MarthNeutralBCharge
void ftMs_SpecialNLoop_IASA(HSD_GObj* gobj)
{
    doLoopIasa(gobj, ftMs_SpecialN_80137354);
}

void ftMs_SpecialAirNLoop_IASA(HSD_GObj* gobj)
{
    doLoopIasa(gobj, ftMs_SpecialN_801373B8);
}

void ftMs_SpecialNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftMs_SpecialAirNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftMs_SpecialNLoop_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftMs_SpecialN_80136DB4(gobj);
    }
}

void ftMs_SpecialAirNLoop_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftMs_SpecialN_80136E14(gobj);
    }
}

void ftMs_SpecialN_80136DB4(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 2) | (1 << 7) | (1 << 9) |
                          (1 << 11) | (1 << 12) | (1 << 14) | (1 << 18) |
                          (1 << 19) | (1 << 22) | (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftMs_MS_SpecialAirNLoop, mf,
                              fp->cur_anim_frame, 1, 0, NULL);
}

void ftMs_SpecialN_80136E14(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 2) | (1 << 7) | (1 << 9) |
                          (1 << 11) | (1 << 12) | (1 << 14) | (1 << 18) |
                          (1 << 19) | (1 << 22) | (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftMs_MS_SpecialNLoop, mf,
                              fp->cur_anim_frame, 1, 0, NULL);
}

void ftMs_SpecialN_80136E74(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMs_MS_SpecialNLoop,
                              Ft_MF_KeepSfx | Ft_MF_SkipColAnim, 0, 1, 0,
                              NULL);
}

void ftMs_SpecialN_80136EAC(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMs_MS_SpecialAirNLoop,
                              Ft_MF_KeepSfx | Ft_MF_SkipColAnim, 0, 1, 0,
                              NULL);
}

static inline void inlineA0(Fighter_GObj* gobj, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* da = fp->dat_attrs;
    int i;
    if (fp->cmd_vars[0] == 0) {
        FORCE_PAD_STACK_16;
        i = 0;
        while (i < (signed) ARRAY_SIZE(fp->x914)) {
            if (fp->x914[i].state == HitCapsule_Enabled) {
                ftColl_8007ABD0(
                    &fp->x914[i],
                    (float) (da->x4 +
                             fp->mv.ms.specialn.cur_frame / 30 * da->x8),
                    gobj);
            }
            i++;
        }
    }
    if (fp->cur_anim_frame == 9) {
        Vec3 position;
        lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_HipN)].joint, 0,
                    &position);
        lb_800119DC(&position, 120, 0.9f, 0.02f, 60 * deg_to_rad);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

void ftMs_SpecialNEnd_Anim(Fighter_GObj* gobj)
{
    inlineA0(gobj, ft_8008A2BC);
}

void ftMs_SpecialAirNEnd_Anim(Fighter_GObj* gobj)
{
    inlineA0(gobj, ftCo_Fall_Enter);
}

void ftMs_SpecialNEnd_IASA(HSD_GObj* gobj) {}

void ftMs_SpecialAirNEnd_IASA(HSD_GObj* gobj) {}

void ftMs_SpecialNEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftMs_SpecialAirNEnd_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftMs_SpecialNEnd_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftMs_SpecialN_801371FC(gobj);
    }
}

void ftMs_SpecialAirNEnd_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftMs_SpecialN_801372A8(gobj);
    }
}

void ftMs_SpecialN_801371FC(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 7) |
                          (1 << 12) | (1 << 14) | (1 << 18) | (1 << 19) |
                          (1 << 22) | (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftMars_MotionState msid;
    if (!fp->cmd_vars[0]) {
        msid = ftMs_MS_SpecialAirNEnd0;
    } else {
        msid = ftMs_MS_SpecialAirNEnd1;
    }
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, msid, mf, fp->cur_anim_frame, 1, 0, NULL);
    if (fp->x2219_b0 == true) {
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
    }
}

void ftMs_SpecialN_801372A8(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 7) |
                          (1 << 12) | (1 << 14) | (1 << 18) | (1 << 19) |
                          (1 << 22) | (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftMars_MotionState msid;
    if (!fp->cmd_vars[0]) {
        msid = ftMs_MS_SpecialNEnd0;
    } else {
        msid = ftMs_MS_SpecialNEnd1;
    }
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, msid, mf, fp->cur_anim_frame, 1, 0, NULL);
    if (fp->x2219_b0 == true) {
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
    }
}

void ftMs_SpecialN_80137354(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMars_MotionState msid;
    if (!fp->cmd_vars[0]) {
        msid = ftMs_MS_SpecialNEnd0;
    } else {
        msid = ftMs_MS_SpecialNEnd1;
    }
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 1, 1, 0, NULL);
    fp->accessory4_cb = ftMs_SpecialN_801365A8;
}

void ftMs_SpecialN_801373B8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMars_MotionState msid;
    if (!fp->cmd_vars[0]) {
        msid = ftMs_MS_SpecialAirNEnd0;
    } else {
        msid = ftMs_MS_SpecialAirNEnd1;
    }
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 1, 1, 0, NULL);
    fp->accessory4_cb = ftMs_SpecialN_8013666C;
}
