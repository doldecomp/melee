#include "ftkirby.h"
#include "types.h"

#include <placeholder.h>

#include "baselib/forward.h"

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_Damage.h"
#include "ft/chara/ftCommon/ftCo_Jump.h"
#include "ft/chara/ftCommon/ftCo_KneeBend.h"
#include "ft/chara/ftCommon/ftCo_Throw.h"
#include "ft/chara/ftCommon/ftCo_ThrownKirby.h"
#include "ft/chara/ftCommon/ftCo_Wait.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/ftwalkcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_CaptureKirby.h"
#include "ftCommon/ftCo_CaptureWaitKirby.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_Landing.h"
#include "ftCommon/inlines.h"

#include "ftKirby/forward.h"
#include "ftLuigi/forward.h"

#include "it/itCommonItems.h"
#include "it/items/it_2ADA.h"
#include "it/items/it_2F28.h"
#include "it/items/itdrmariopill.h"
#include "it/items/itkirby_2F23.h"
#include "it/items/itkirbyhammer.h"
#include "it/items/itluigifireball.h"
#include "it/items/itmariofireball.h"
#include "lb/lb_00B0.h"
#include "lb/lbanim.h"
#include "mp/mpcoll.h"

#include <math.h>
#include <stddef.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/random.h>

void ftKb_SpecialNCa_800F99BC(Fighter_GObj* gobj)
{
    ftKirby_MotionState msid = ftKb_MS_CaSpecialN;
    Fighter* fp = GET_FIGHTER(gobj);
    f32 zero = 0.0f;
    PAD_STACK(8);
    (void) zero;
    (void) MTXDegToRad(1);
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    fp = GET_FIGHTER(gobj);
    if (fp->u.kb.hat.kind != FTKIND_CAPTAIN) {
        msid = ftKb_MS_GnSpecialN;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0f, 1.0f, 0.0f, NULL);
    Fighter_SetEffectHitlagCallbacks(fp);
    ftAnim_8006EBA4(gobj);
}

void ftKb_SpecialNCa_800F9A54(Fighter_GObj* gobj)
{
    ftKirby_MotionState msid = ftKb_MS_CaSpecialAirN;
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    fp = GET_FIGHTER(gobj);
    if (fp->u.kb.hat.kind != FTKIND_CAPTAIN) {
        msid = ftKb_MS_GnSpecialAirN;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0f, 1.0f, 0.0f, NULL);
    Fighter_SetEffectHitlagCallbacks(fp);
    ftAnim_8006EBA4(gobj);
}

void ftKb_CaSpecialN_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_CaSpecialAirN_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_CaSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_CaSpecialAirN_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(24);

    if (fp->cmd_vars[0] != 0) {
        f32 stick_y;
        f32 abs_y;
        f32 range;
        f32 angle;
        ftKb_DatAttrs* da2;

        fp->cmd_vars[0] = 0;
        stick_y = fp->input.lstick.y;
        da2 = fp->dat_attrs;

        if (stick_y < 0.0f) {
            abs_y = -stick_y;
        } else {
            abs_y = stick_y;
        }
        if ((abs_y > da2->specialn_ca_y_axis_range) ^ 0) {
            abs_y = da2->specialn_ca_y_axis_range;
        }
        range = abs_y - da2->specialn_ca_x_axis_range;
        if (range < 0.0f) {
            range = 0.0f;
        }
        if (fp->input.lstick.y < 0.0f) {
            range = -range;
        }
        angle = MTXDegToRad(
            (range * da2->specialn_ca_angle_difference) /
            (da2->specialn_ca_y_axis_range - da2->specialn_ca_x_axis_range));
        fp->self_vel.y = da->specialn_ca_forward_momentum * sinf(angle);
        fp->self_vel.x =
            da->specialn_ca_forward_momentum * (fp->facing_dir * cosf(angle));
    }
}

void ftKb_CaSpecialN_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool throw_b1;
    s64 pad;
    if (fp->throw_flags_b1) {
        fp->throw_flags_b1 = false;
        throw_b1 = true;
    } else {
        throw_b1 = false;
    }
    if (throw_b1) {
        if (!fp->x2219_b0) {
            switch (fp->u.kb.hat.kind) {
            case FTKIND_CAPTAIN:
                efSync_Spawn(1195, gobj, fp->parts[0].joint,
                             fp->parts[44].joint);
                break;
            case FTKIND_GANON:
                efSync_Spawn(1203, gobj, fp->parts[0].joint,
                             fp->parts[44].joint);
                break;
            default:
                break;
            }
            fp->x2219_b0 = true;
        } else {
            ftCommon_8007DB24(gobj);
        }
    }
    ft_80084FA8(gobj);
}

void ftKb_CaSpecialAirN_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    bool throw_b1;
    PAD_STACK(16);
    if (fp->throw_flags_b1) {
        fp->throw_flags_b1 = false;
        throw_b1 = true;
    } else {
        throw_b1 = false;
    }
    if (throw_b1) {
        if (!fp->x2219_b0) {
            switch (fp->u.kb.hat.kind) {
            case FTKIND_CAPTAIN:
                efSync_Spawn(1195, gobj, fp->parts[0].joint,
                             fp->parts[44].joint);
                break;
            case FTKIND_GANON:
                efSync_Spawn(1203, gobj, fp->parts[0].joint,
                             fp->parts[44].joint);
                break;
            default:
                break;
            }
            fp->x2219_b0 = true;
        } else {
            ftCommon_8007DB24(gobj);
        }
    }
    switch (fp->cmd_vars[1]) {
    case 0:
        ft_80084EEC(gobj);
        return;
    case 1:
        fp->self_vel.y *= da->specialn_ca_additional_vertical_momentum;
        fp->self_vel.x *= da->specialn_ca_additional_vertical_momentum;
        return;
    case 2:
        ft_80084DB0(gobj);
        return;
    }
}

static u32 const ftKb_Ca_transition_flags =
    Ft_MF_KeepGfx | Ft_MF_SkipMatAnim | Ft_MF_SkipRumble | Ft_MF_UpdateCmd |
    Ft_MF_SkipColAnim | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
    Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27;

void ftKb_CaSpecialN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp;
    Fighter* fp2;
    ftKirby_MotionState msid;
    PAD_STACK(8);

    if (ft_800827A0(gobj) == false) {
        fp = getFighter(gobj);
        ftCommon_8007D5D4(fp);
        fp2 = getFighter(gobj);
        msid = ftKb_MS_CaSpecialAirN;
        {
            f32 anim_frame = fp->cur_anim_frame;
            if (fp2->u.kb.hat.kind != FTKIND_CAPTAIN) {
                msid = ftKb_MS_GnSpecialAirN;
            }
            Fighter_ChangeMotionState(gobj, msid, ftKb_Ca_transition_flags,
                                      anim_frame, 1.0f, 0.0f, NULL);
        }
        Fighter_SetEffectHitlagCallbacks(fp2);
        ftCommon_ClampAirDrift(fp);
    }
}

void ftKb_CaSpecialAirN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp;
    Fighter* fp2;
    ftKirby_MotionState msid;
    PAD_STACK(8);

    if (ft_80081D0C(gobj) != GA_Ground) {
        fp = getFighter(gobj);
        ftCommon_8007D7FC(fp);
        fp2 = getFighter(gobj);
        msid = ftKb_MS_CaSpecialN;
        {
            f32 anim_frame = fp->cur_anim_frame;
            if (fp2->u.kb.hat.kind != FTKIND_CAPTAIN) {
                msid = ftKb_MS_GnSpecialN;
            }
            Fighter_ChangeMotionState(gobj, msid, ftKb_Ca_transition_flags,
                                      anim_frame, 1.0f, 0.0f, NULL);
        }
        Fighter_SetEffectHitlagCallbacks(fp2);
    }
}
