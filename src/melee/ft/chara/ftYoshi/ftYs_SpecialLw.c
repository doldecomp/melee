#include "ftYs_SpecialLw.h"

#include "placeholder.h"

#include "baselib/forward.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"

#include "ftYoshi/forward.h"

#include "ftYoshi/types.h"
#include "it/items/ityoshistar.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>
#include <baselib/gobj.h>

/* 12E644 */ static void fn_8012E644(Fighter_GObj*);
/* 12EAD8 */ static void ftYs_SpecialS_8012EAD8(Fighter_GObj*);

void fn_8012E644(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYs_DatAttrs* da = fp->dat_attrs;
    Vec3 transn_pos, star_pos;
    PAD_STACK(4);

    lb_8000B1CC(fp->parts[FtPart_TransN].joint, NULL, &transn_pos);
    star_pos.x = (-1.0f * da->speciallw_star_offset.x) + transn_pos.x;
    star_pos.y = transn_pos.y + da->speciallw_star_offset.y;
    star_pos.z = transn_pos.z;
    it_802B2FC8(gobj, &star_pos, -1.0f);
    star_pos.x = transn_pos.x + da->speciallw_star_offset.x;
    it_802B2FC8(gobj, &star_pos, 1.0f);
    fp->accessory4_cb = NULL;
}

inline void ftYoshi_SpecialLw_SetVars(HSD_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);

    fp->cmd_vars[0] = fp->cmd_vars[1] = 0;
    fp->throw_flags_b0 = false;
    fp->self_vel.x = fp->self_vel.y = 0;
    fp->x6A4_transNOffset.y = 0;
    fp->x2223_b4 = true;
}

void ftYs_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 4);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialLw, Ft_MF_None, 0.0f, 1.0f,
                              0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftYoshi_SpecialLw_SetVars(gobj);
}

static inline void reset(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->cmd_vars[0] = fp->cmd_vars[1] = false;
    fp->throw_flags_b0 = false;
    fp->self_vel.y = 0.0f;
    fp->self_vel.x = 0.0f;
    fp->x6A4_transNOffset.y = 0.0f;
    fp->x2223_b4 = true;
}

void ftYs_SpecialAirLw_Enter(Fighter_GObj* gobj)
{
    PAD_STACK(0x18);

    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialAirLw, Ft_MF_None, 0.0f,
                              1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    reset(gobj);
}

void ftYs_SpecialLw_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftYs_SpecialS_8012EA04(gobj);
    }
}

void ftYs_SpecialAirLw_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->cmd_vars[1] = true;
    }
}

void ftYs_SpecialLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ft_80085134(gobj);
    if (fp->self_vel.y < 0.0f) {
        fp->self_vel.y = 0.0f;
    }
}

void ftYs_SpecialAirLw_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* da = fp->dat_attrs;
    PAD_STACK(4);

    ft_80085134(gobj);
    if (fp->self_vel.y < da->x114 || fp->cmd_vars[1]) {
        fp->self_vel.y = da->x114;
    }
}
void ftYs_SpecialLw_Coll(HSD_GObj* gobj)
{
    ftYs_SpecialAirLw_Coll(gobj);
}

void ftYs_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_CheckGroundAndLedge(gobj, ftGetFacingDirInt(fp))) {
        if (fp->cmd_vars[0] && fp->self_vel.y <= 0) {
            ftYs_SpecialS_8012EAD8(gobj);
        } else {
            ftCommon_8007D5D4(fp);
        }
    } else if (fp->cmd_vars[0] && ftCliffCommon_80081298(gobj)) {
        ftCliffCommon_80081370(gobj);
    }
}

void ftYs_SpecialS_8012EA04(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(
        gobj, ftYs_MS_SpecialAirLw,
        Ft_MF_SkipHit | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim |
            Ft_MF_UpdateCmd | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
            Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27,
        20.0f, 1.0f, 0.0f, NULL);
}

void ftYs_SpecialLwLanding_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftYs_SpecialLwLanding_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftYs_SpecialLwLanding_Coll(Fighter_GObj* gobj)
{
    PAD_STACK(8);

    if (ft_80082708(gobj) == GA_Ground) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftYs_SpecialS_8012EAD8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->gr_vel = 0.0f;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialLwLanding, Ft_MF_None, 0.0f,
                              1.0f, 0.0f, NULL);
    fp->accessory4_cb = fn_8012E644;
}
