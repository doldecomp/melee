#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"
#include <baselib/forward.h>

#include "ftLk_AttackAir.h"

#include "ftLk_Init.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ftLink/types.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"

/* 0EB484 */ static void lwOnHit(HSD_GObj* gobj);
/* 0EB528 */ static void lwOnAnim(HSD_GObj* gobj);

void ftLk_AttackAir_800EB3BC(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x5F8 == 0) {
        ftLk_DatAttrs* da = fp->dat_attrs;
        ftColl_8007B1B8(gobj, &da->xC4, ftLk_800EB334);
        fp->x221B_b3 = true;
        fp->x221B_b4 = true;
        fp->x221B_b2 = true;
    }
}

void ftLk_AttackAir_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ft_8008CF70();
    if (fp->motion_id == ftCo_MS_AttackAirLw) {
        fp->cb.x21C0_callback_OnGiveDamage = lwOnHit;
        fp->cb.x21A0_callback_Anim = lwOnAnim;
        fp->mv.lk.attackair.lw_frame_start = 0;
    }
}

static void lwOnHit(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    float frame_len = da->attackairlw_hit_anim_frame_end -
                      da->attackairlw_hit_anim_frame_start;
    ftColl_8007AFF8(gobj);
    fp->self_vel.y = da->attackairlw_hit_vel_y;
    fp->x221A_flag.bits.b4 = false;
    fp->mv.lk.attackair.lw_frame_start = da->attackairlw_hit_anim_frame_start;
    if (fp->cur_anim_frame > frame_len) {
        Fighter_ChangeMotionState(gobj, ftCo_MS_AttackAirLw, Ft_MF_None, NULL,
                                  frame_len, 1, 0);
    }
}

static void lwDoAnimHitCapsule(HSD_GObj* gobj, ssize_t idx)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    ftColl_8007B064(gobj, idx);
    ftColl_8007ABD0(&fp->x914[idx], da->attackairlw_anim_flags[idx], gobj);
}

static void lwOnAnim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[40];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    float frame_start = fp->mv.lk.attackair.lw_frame_start;
    ftLk_DatAttrs* da = fp->dat_attrs;
    if (frame_start > 0) {
        fp->mv.lk.attackair.lw_frame_start =
            frame_start - fp->x89C_frameSpeedMul;
        if (fp->mv.lk.attackair.lw_frame_start <= 0 &&
            fp->cur_anim_frame < da->attackairlw_hit_anim_frame_end)
        {
            lwDoAnimHitCapsule(gobj, 0);
            lwDoAnimHitCapsule(gobj, 1);
            lwDoAnimHitCapsule(gobj, 2);
        }
    }
    ftCo_AttackAir_Anim(gobj);
}

void ftLk_AttackAir_SetupParts(HSD_GObj* gobj)
{
    ftParts_80074A4C(gobj, 2, 0);
    ftParts_80074B0C(gobj, 2, 0);
}
