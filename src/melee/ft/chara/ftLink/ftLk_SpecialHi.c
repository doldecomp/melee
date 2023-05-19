#include <platform.h>
#include "ft/forward.h"
#include <baselib/forward.h>

#include "ftLk_SpecialHi.h"

#include "ftLk_Init.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftLink/types.h"

#include <common_structs.h>

/* 0EBA4C */ static void onAccessory4(HSD_GObj* gobj);
/* 0EBE64 */ static void doColl(HSD_GObj* gobj);

static void onAccessory4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj0 = fp->parts[ftParts_8007500C(fp, FtPart_TransN)].joint;
    HSD_JObj* jobj1;
    if (fp->kind == FTKIND_LINK) {
        jobj1 = fp->parts[FtPart_L2ndNa].joint;
    } else {
        jobj1 = fp->parts[FtPart_L3rdNa].joint;
    }
    if (!fp->x2219_b0) {
        if (fp->ground_or_air == GA_Ground) {
            efSync_Spawn(1211, gobj, jobj0, jobj1);
        } else {
            efSync_Spawn(1212, gobj, jobj0, jobj1);
        }
        fp->x2219_b0 = true;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

void ftLk_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialHi, Ft_MF_None, NULL, 0, 1,
                              0);
    ftAnim_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 = onAccessory4;
}

void ftLk_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialAirHi, Ft_MF_None, NULL, 0,
                              1, 0);
    ftAnim_8006EBA4(gobj);
    fp->self_vel.x *= da->x34;
    fp->self_vel.y = da->x40;
    fp->x1968_jumpsUsed = fp->co_attrs.x168_MaxJumps;
    fp->cb.x21BC_callback_Accessory4 = onAccessory4;
}

void ftLk_SpecialHi_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftLk_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    ftLk_DatAttrs* da = GET_FIGHTER(gobj)->dat_attrs;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_80096900(gobj, 1, 1, false, da->specialairhi_drift_stick_mul,
                    da->x30);
    }
}

void ftLk_SpecialHi_IASA(HSD_GObj* gobj) {}

void ftLk_SpecialAirHi_IASA(HSD_GObj* gobj) {}

void ftLk_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* ca = &fp->co_attrs;
    ftLk_DatAttrs* da = fp->dat_attrs;
    ftCommon_8007D494(fp, ca->grav * da->specialhi_grav_mul, ca->terminal_vel);
    ftCommon_8007D344(
        fp, 0, ca->air_drift_stick_mul * da->specialairhi_drift_stick_mul,
        ca->air_drift_max * da->specialairhi_drift_max_mul);
}

void ftLk_SpecialHi_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        ftLk_SpecialAirHi_Phys(gobj);
    } else {
        ft_80084F3C(gobj);
    }
}

void ftLk_SpecialHi_Coll(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif
    if (!ft_80082708(gobj)) {
        doColl(gobj);
    }
}

void ftLk_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj)->dat_attrs;
    if (ft_CheckGroundAndLedge(gobj, 0)) {
        ft_800D5CB0(gobj, 0, fp->x30_facingDirectionRepeated);
    } else if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

static void doColl(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    MotionFlags const coll_mf =
        Ft_MF_KeepGfx | Ft_MF_SkipHit | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim |
        Ft_MF_UpdateCmd | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
        Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialAirHi, coll_mf, NULL,
                              fp->cur_anim_frame, 1, 0);
}

void ftLk_SpecialHi_ProcessPartLThumbNb(HSD_GObj* gobj)
{
    ftParts_8007500C(GET_FIGHTER(gobj), FtPart_LThumbNb);
}

void ftLk_SpecialHi_GetPosWithAdjustedY(HSD_GObj* gobj, Vec3* pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    *pos = fp->cur_pos;
    pos->y += da->specialhi_pos_y_offset;
}

int ftLk_SpecialHi_GetFv4(HSD_GObj* gobj)
{
    return GET_FIGHTER(gobj)->fv.lk.x4;
}
