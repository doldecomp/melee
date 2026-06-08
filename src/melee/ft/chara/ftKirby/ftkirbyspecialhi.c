#include "ftkirbyspecialhi.h"

#include "types.h"

#include <placeholder.h>

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"

#include "ftKirby/forward.h"

#include "ftKirby/inlines.h"
#include "it/items/itkirbycutterbeam.h"
#include "lb/lb_00B0.h"

#include <common_structs.h>
#include <stddef.h>
#include <trigf.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

/* 0F21E8 */ static void fn_800F21E8(Fighter_GObj* gobj);

void fn_800F21E8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (!da->specialhi_projectile_spawn_x) { // fake match, via permuter
    }
    if (fp->mv.kb.specialhi.xC == 0 && fp->cmd_vars[2] != 0) {
        Vec3 pos;
        u8 _pad[12];
        fp->cmd_vars[2] = 0;
        fp->mv.kb.specialhi.xC = 1;
        lb_8000B1CC(fp->parts[0].joint, NULL, &pos);
        pos.x += (fp->facing_dir == 1.0F) ? da->specialhi_projectile_spawn_x
                                          : -da->specialhi_projectile_spawn_x;
        pos.y += da->specialhi_projectile_spawn_y;
        pos.z = 0.0F;
        efLib_SetFlags(gobj, 1);
        pos.y -= 1.0F;
        it_8029BAB8(gobj, &pos, fp->facing_dir);
    }
}

void ftKb_AttackDashAir_800F22D4(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftPartSetRotX(ft, 0, 0.0F);
}

void ftKb_SpecialHi_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->mv.kb.specialhi.x0 = 0;
    fp->mv.kb.specialhi.x4 = 0;
    fp->mv.kb.specialhi.x8.i = 0;
    fp->mv.kb.specialhi.xC = 0;
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialHi1, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp = GET_FIGHTER(gobj);
    efSync_Spawn(0x494, gobj);
    fp->x2219_b0 = 1;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

void ftKb_SpecialAirHi_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    fp->mv.kb.specialhi.x0 = 0;
    fp->mv.kb.specialhi.x4 = 0;
    fp->mv.kb.specialhi.x8.i = 0;
    fp->mv.kb.specialhi.xC = 0;
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirHi1, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp = GET_FIGHTER(gobj);
    efSync_Spawn(0x494, gobj);
    fp->x2219_b0 = 1;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

void ftKb_SpecialHi1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirHi2, 0xA, 0.0f, 1.0f,
                                  0.0f, NULL);
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
        fp->mv.kb.specialhi.x0 = 0;
    }
}

void ftKb_SpecialHi2_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x187, 0xA, 0.0f, 1.0f, 0.0f, NULL);
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
    }
}

void ftKb_SpecialHi3_Anim(Fighter_GObj* gobj) {}

void ftKb_SpecialHi4_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(16);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPartSetRotX(GET_FIGHTER(gobj), 0, 0.0f);
        if (fp->ground_or_air == GA_Ground) {
            ft_8008A2BC(gobj);
        } else {
            ftCo_Fall_Enter(gobj);
        }
    }
}

void ftKb_SpecialAirHi1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirHi2, 0xA, 0.0f, 1.0f,
                                  0.0f, NULL);
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
        fp->mv.kb.specialn_pe.facing_dir = 0;
    }
}

void ftKb_SpecialAirHi2_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirHi3, 0xA, 0.0F, 1.0F,
                                  0.0F, NULL);
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
    }
}

void ftKb_SpecialAirHi3_Anim(Fighter_GObj* gobj) {}

void ftKb_SpecialAirHiEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(16);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPartSetRotX(GET_FIGHTER(gobj), 0, 0.0f);
        if (fp->ground_or_air == GA_Ground) {
            ft_8008A2BC(gobj);
        } else {
            ftCo_Fall_Enter(gobj);
        }
    }
}

void ftKb_SpecialHi1_IASA(Fighter_GObj* gobj)
{
    float mag;
    float lstick_x;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    float new_var;

    if ((!fp->cmd_vars[3]) && (!fp->mv.kb.specialhi.x4)) {
        if ((lstick_x = fp->input.lstick.x) < 0.0F) {
            mag = -lstick_x;
        } else {
            mag = lstick_x;
        }
        if (mag > da->specialhi_reverse_upb_stick_range) {
            new_var = 0.0F;
            if (((fp->facing_dir == 1.0F) && (lstick_x < new_var)) ||
                ((fp->facing_dir == -1.0F) && (lstick_x > new_var)))
            {
                fp->cmd_vars[3] = 1;
                fp->mv.kb.specialhi.x4 = 1;
                ftCommon_UpdateFacing(fp);
                ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
            }
        }
    }
}

void ftKb_SpecialHi2_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialHi3_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialHi4_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialAirHi1_IASA(Fighter_GObj* gobj)
{
    float mag;
    float lstick_x;
    int new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;

    if ((!fp->cmd_vars[3]) && (!fp->mv.kb.specialhi.x4)) {
        if ((lstick_x = fp->input.lstick.x) < 0.0f) {
            mag = -lstick_x;
        } else {
            mag = lstick_x;
        }
        if (mag > da->specialhi_reverse_upb_stick_range) {
            if (((fp->facing_dir == 1.0f) && (lstick_x < 0.0f)) ||
                ((fp->facing_dir == -1.0f) && (lstick_x > 0.0f)))
            {
                new_var = 3;
                fp->cmd_vars[new_var] = 1;
                fp->mv.kb.specialhi.x4 = 1;
                ftCommon_UpdateFacing(fp);
                ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
            }
        }
    }
}

void ftKb_SpecialAirHi2_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialAirHi3_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialAirHiEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialHi1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* temp_r30 = &fp->co_attrs;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    PAD_STACK(4); ///< @todo Remove This
    ft_80084FA8(gobj);
    ftCommon_8007CADC(fp, 0.0f,
                      temp_r30->air_drift_stick_mul *
                          dat_attr->specialhi_horizontal_momentum,
                      temp_r30->air_drift_max);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftKb_SpecialHi2_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* temp_r30 = &fp->co_attrs;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    PAD_STACK(4); ///< @todo Remove This
    ft_80085134(gobj);
    ftCommon_8007CADC(fp, 0.0f,
                      temp_r30->air_drift_stick_mul *
                          dat_attr->specialhi_horizontal_momentum,
                      temp_r30->air_drift_max);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftKb_SpecialHi3_Phys(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    new_var = dat_attr;
    ftCommon_8007CADC(fp, 0.0f,
                      fp->co_attrs.air_drift_stick_mul *
                          new_var->specialhi_horizontal_momentum,
                      (0, fp->co_attrs.air_drift_max));
    ftCommon_ApplyGroundMovement(gobj);
}

void ftKb_SpecialHi4_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftKb_SpecialAirHi1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 stack; // Needed For Stack?
    ftCo_DatAttrs* temp_r30 = &fp->co_attrs;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    ft_80085134(gobj);
    if (fp->self_vel.y > 0.0f) {
        fp->self_vel.y *= dat_attr->specialhi_vertical_momentum;
    }
    ftCommon_8007D3A8(fp, 0.0f,
                      temp_r30->air_drift_stick_mul *
                          dat_attr->specialhi_horizontal_momentum,
                      temp_r30->air_drift_max);
}

void ftKb_SpecialAirHi2_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 stack; // Needed For Stack?
    ftCo_DatAttrs* temp_r30 = &fp->co_attrs;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    ft_80085134(gobj);
    if (fp->self_vel.y > 0.0f) {
        fp->self_vel.y *= dat_attr->specialhi_vertical_momentum;
    }
    ftCommon_8007D3A8(fp, 0.0f,
                      temp_r30->air_drift_stick_mul *
                          dat_attr->specialhi_horizontal_momentum,
                      temp_r30->air_drift_max);
}

void ftKb_SpecialAirHi3_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    /// FAKE MATCH: comma operator required for regalloc
    ftCommon_8007D3A8(fp, 0.0f,
                      ((0, fp->co_attrs.air_drift_stick_mul)) *
                          (dat_attr->specialhi_horizontal_momentum),
                      fp->co_attrs.air_drift_max);
}

void ftKb_SpecialAirHiEnd_Phys(Fighter_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftKb_SpecialHi1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirHi1, 0xC1082U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_SpecialN_set_cbs(gobj);
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        ftPartSetRotX(fp, 0, 0.0F);
    }
}

void ftKb_SpecialHi2_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 i;
    PAD_STACK(5); // Fake
    if (fp->mv.kb.specialn_pe.facing_dir > 0x14) {
        if (1 == fp->facing_dir) {
            i = 1;
        } else {
            i = -1;
        }
        if (ft_CheckGroundAndLedge(gobj, i)) {
            fp->mv.kb.specialn_pe.facing_dir++;
            ftCommon_8007D5D4(fp);
            Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirHi4, 0xC1082U,
                                      0.0f, 1.0f, 0.0f, NULL);
            ftKb_SpecialN_set_cbs(gobj);
            fp->accessory4_cb = fn_800F21E8;
            fp->self_vel.z = 0.0f;
            fp->self_vel.y = 0.0f;
            fp->self_vel.x = 0.0f;
            fp->gr_vel = 0.0f;
            ftPartSetRotX(fp, 0,
                          fp->facing_dir *
                              atan2f(fp->coll_data.floor.normal.x,
                                     fp->coll_data.floor.normal.y));
            return;
        }
        if (ftCliffCommon_80081298(gobj)) {
            ftCliffCommon_80081370(gobj);
        }
    } else {
        fp->mv.kb.specialn_pe.facing_dir++;
        ftCommon_8007D60C(fp);
        ft_80082578(gobj);
    }
}

void ftKb_SpecialHi3_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 i;

    if (1.0f == fp->facing_dir) {
        i = 1;
    } else {
        i = -1;
    }
    if (ft_CheckGroundAndLedge(gobj, i)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirHi4, 0xC1082U, 0.0f,
                                  1.0f, 0.0f, NULL);
        ftKb_SpecialN_set_cbs(gobj);
        fp->accessory4_cb = fn_800F21E8;
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        fp->self_vel.x = 0.0f;
        fp->gr_vel = 0.0f;
        ftPartSetRotX(fp, 0,
                      fp->facing_dir * atan2f(fp->coll_data.floor.normal.x,
                                              fp->coll_data.floor.normal.y));
        return;
    }
    if (ftCliffCommon_80081298(gobj)) {
        ftCliffCommon_80081370(gobj);
    }
}

void ftKb_SpecialHi4_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirHi4, 0xC1082U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_SpecialN_set_cbs(gobj);
        fp->accessory4_cb = fn_800F21E8;
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        ftPartSetRotX(fp, 0, 0.0F);
        return;
    }
    ftPartSetRotX(fp, 0,
                  fp->facing_dir * atan2f(fp->coll_data.floor.normal.x,
                                          fp->coll_data.floor.normal.y));
}

void ftKb_SpecialAirHi1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialHi1, 0xC1082U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_SpecialN_set_cbs(gobj);
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
    }
}

void ftKb_SpecialAirHi2_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 i;
    PAD_STACK(6); // Fix
    if (fp->mv.kb.specialn_pe.facing_dir > 0x14) {
        if (1.0f == fp->facing_dir) {
            i = 1;
        } else {
            i = -1;
        }
        if (ft_CheckGroundAndLedge(gobj, i)) {
            fp->mv.kb.specialn_pe.facing_dir++;
            ftCommon_8007D7FC(fp);
            Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialHi4, 0xC1082U, 0.0f,
                                      1.0f, 0.0f, NULL);
            ftKb_SpecialN_set_cbs(gobj);
            fp->accessory4_cb = fn_800F21E8;
            fp->self_vel.z = 0.0f;
            fp->self_vel.y = 0.0f;
            fp->self_vel.x = 0.0f;
            fp->gr_vel = 0.0f;
            ftPartSetRotX(fp, 0,
                          fp->facing_dir *
                              atan2f(fp->coll_data.floor.normal.x,
                                     fp->coll_data.floor.normal.y));
            return;
        }
        if (ftCliffCommon_80081298(gobj)) {
            ftCliffCommon_80081370(gobj);
        }
    } else {
        fp->mv.kb.specialn_pe.facing_dir++;
        ftCommon_8007D60C(fp);
        ft_80082578(gobj);
    }
}

void ftKb_SpecialAirHi3_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 i;
    if (fp->facing_dir == 1.0f) {
        i = 1;
    } else {
        i = -1;
    }
    if (ft_CheckGroundAndLedge(gobj, i)) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialHi4, 0xC1082U, 0.0f,
                                  1.0f, 0.0f, NULL);
        ftKb_SpecialN_set_cbs(gobj);
        fp->accessory4_cb = fn_800F21E8;
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        fp->self_vel.x = 0.0f;
        fp->gr_vel = 0.0f;
        ftPartSetRotX(fp, 0,
                      fp->facing_dir * atan2f(fp->coll_data.floor.normal.x,
                                              fp->coll_data.floor.normal.y));
        return;
    }
    if (ftCliffCommon_80081298(gobj)) {
        ftCliffCommon_80081370(gobj);
    }
}

void ftKb_SpecialAirHiEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialHi4, 0xC1082U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_SpecialN_set_cbs(gobj);
        fp->accessory4_cb = fn_800F21E8;
        fp->self_vel.z = 0.0f;
        fp->self_vel.y = 0.0f;
        ftPartSetRotX(fp, 0,
                      fp->facing_dir * atan2f(fp->coll_data.floor.normal.x,
                                              fp->coll_data.floor.normal.y));
        return;
    }
    ftPartSetRotX(fp, 0, 0.0F);
}
