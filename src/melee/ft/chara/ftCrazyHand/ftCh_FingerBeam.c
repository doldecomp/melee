#include "ftCh_FingerBeam.h"

#include "ftCh_Init.h"
#include "types.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/fighter.h"
#include "ft/ft_084E.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCrazyHand/ftCh_CaptureCrazyHand.h"
#include "ftCrazyHand/ftCh_CaptureWaitCrazyHand.h"
#include "ftCrazyHand/ftCh_FingerGun2.h"
#include "ftCrazyHand/ftCh_TagCancel.h"
#include "ftMasterHand/types.h"
#include "lb/lbvector.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

static inline float my_sqrtf(float x)
{
    static const double _half = .5;
    static const double _three = 3.0;

    u32 pad;

    volatile float y;
    if (x > 0) {
        double guess = __frsqrte((double) x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        y = (float) (x * guess);
        return y;
    }
    return x;
}

static inline float my_lbVector_Len(Vec3* vec)
{
    return my_sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

void fn_80159288(HSD_GObj* gobj);

void ftCh_Init_80158B3C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x16A, 0, fp->cur_anim_frame, 1.0f, 0.0f,
                              NULL);
    ftAnim_SetAnimRate(gobj, da->xCC_pos.x);
    fp->mv.ch.unk0.x8 = da->xC4_pos.y;
}

void ftCh_FingerBeamLoop_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int timer = fp->mv.ch.unk0.x8 - 1;
    int is_zero = timer == 0;
    fp->mv.ch.unk0.x8 = timer;

    if (is_zero) {
        ftAnim_SetAnimRate(gobj, 1);
        ftCh_Init_80158DFC(gobj);
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, 0x16A, 0, 0, 1.0f, 0.0f, NULL);
        ftAnim_8006EBA4(gobj);
    }
}

void ftCh_FingerBeamLoop_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_FingerBeamLoop_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    float len;
    float speed;
    Vec3 sp28_pos;
    Vec3 vel;

    u32 pad;

    ft_80085134(gobj);
    ftBossLib_8015C208(gobj, &sp28_pos);
    sp28_pos.x += da->xBC_pos.y;
    sp28_pos.y += da->xC4_pos.x;
    sp28_pos.z = 0;
    lbVector_Diff(&sp28_pos, &fp->cur_pos, &vel);
    len = my_lbVector_Len(&vel);
    if (len < da->x14) {
        fp->self_vel.x = vel.x;
        fp->self_vel.y = vel.y;
    } else {
        lbVector_Normalize(&vel);
        speed = len * da->x10;
        vel.x *= speed;
        vel.y *= speed;
        vel.z *= speed;
        fp->self_vel.x = vel.x;
        fp->self_vel.y = vel.y;
    }
}

void ftCh_FingerBeamLoop_Coll(HSD_GObj* gobj) {}

void ftCh_Init_80158DFC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x16B, 0, 0, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2D0(fp, 0x100, fn_80159288, NULL, fn_8015B548);
    fp->mv.ch.unk0.x20 = 0;
}

void ftCh_FingerBeamEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
        ftCh_GrabUnk1_8015AC50(gobj);
    }
}

void ftCh_FingerBeamEnd_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_FingerBeamEnd_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_FingerBeamEnd_Coll(HSD_GObj* gobj) {}

void ftCh_Init_80158F34(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x172, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.ch.unk0.xC.x = da->x18;
    fp->mv.ch.unk0.xC.y = da->x1C;
    fp->mv.ch.unk0.xC.z = 0.0f;
}

void ftCh_BackPunch_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_BackPunch_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_BackPunch_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.ch.unk0.xC, &fp->mv.ch.unk0.x18, da->x14,
                       da->x10);
}

void ftCh_BackPunch_Coll(HSD_GObj* gobj) {}

void ftCh_Init_80159098(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x16C, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.ch.unk0.x24 = da->xD8;
    fp->cmd_vars[0] = 1;
    fp->self_vel.x = 0;
    fp->self_vel.y = 0;
    fp->self_vel.z = 0;
    fp->mv.ch.unk0.xC.x = da->x18;
    fp->mv.ch.unk0.xC.y = da->x1C;
    fp->mv.ch.unk0.xC.z = 0;
}

void ftCh_FingerGun1_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (--fp->mv.ch.unk0.x24 <= 0 && fp->cmd_vars[0]) {
        ftCh_GrabUnk1_8015B800(fp->victim_gobj);
        fp->mv.ch.unk0.x20 = 0;
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_FingerGun1_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_FingerGun1_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.ch.unk0.xC, &fp->mv.ch.unk0.x18, da->x14,
                       da->x10);
}

void ftCh_FingerGun1_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.ch.unk0.x18 == 0) {
        fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
    }
}

void fn_80159288(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.z = 0;
    fp->self_vel.y = 0;
    fp->self_vel.x = 0;
    fp->mv.ch.unk0.x20 = true;
    fp->x221E_b6 = false;
    ftCh_GrabUnk1_8015ABD0(gobj);
}
