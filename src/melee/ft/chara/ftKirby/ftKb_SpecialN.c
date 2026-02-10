#include "ftKb_Init.h"
#include "types.h"

#include <placeholder.h>

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_CaptureWaitKirby.h"
#include "ft/chara/ftCommon/ftCo_Damage.h"
#include "ft/chara/ftCommon/ftCo_Escape.h"
#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/chara/ftCommon/ftCo_Jump.h"
#include "ft/chara/ftCommon/ftCo_KneeBend.h"
#include "ft/chara/ftCommon/ftCo_Lift.h"
#include "ft/chara/ftCommon/ftCo_Throw.h"
#include "ft/chara/ftCommon/ftCo_Wait.h"
#include "ft/chara/ftCommon/ftpickupitem.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C31.h"
#include "ft/ftcamera.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/ftdynamics.h"
#include "ft/ftparts.h"
#include "ft/ftwalkcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_CaptureKirby.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_Landing.h"

#include "ftKirby/forward.h"

#include "ftLink/types.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include "it/items/it_27CF.h"
#include "it/items/it_2ADA.h"
#include "it/items/it_2F28.h"
#include "it/items/itclimbersice.h"
#include "it/items/itgamewatchchef.h"
#include "it/items/itkirby_2F23.h"
#include "it/items/itkirbycutterbeam.h"
#include "it/items/itkirbygamewatchchefpan.h"
#include "it/items/itkirbyhammer.h"
#include "it/items/itkirbyyoshispecialn.h"
#include "it/items/itlinkarrow.h"
#include "it/items/itlinkbow.h"
#include "it/items/itmewtwoshadowball.h"
#include "it/items/itnesspkflush.h"
#include "it/items/itpeachtoad.h"
#include "it/items/itpeachtoadspore.h"
#include "it/items/itpikachutjoltground.h"
#include "it/items/itsamuschargeshot.h"
#include "it/items/itseakneedleheld.h"
#include "lb/lb_00B0.h"
#include "lb/lbanim.h"
#include "lb/lbvector.h"
#include "melee/lb/lbrefract.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"
#include "pl/player.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

/// External variables from ftKb_Init.c
extern bool ftKb_Init_803CB490[];

struct ftKb_Init_803CB4EC_t {
    int ints[6];
    Vec3 vec;
};
extern struct ftKb_Init_803CB4EC_t ftKb_Init_803CB4EC;

/// Forward declarations
void fn_800F9260(HSD_GObj*);
void fn_800F64C8(Fighter_GObj*);
void fn_800F6178(HSD_GObj* gobj);
static void fn_800F6210(HSD_GObj* gobj);
static void fn_800F6280(HSD_GObj* gobj);
static void fn_800F6318(HSD_GObj* gobj);
static void fn_800F6AC8(HSD_GObj* gobj);

void fn_800F1FDC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_AttackDash, 0x0C4C5082U,
                              fp->cur_anim_frame, fp->frame_speed_mul, 0,
                              NULL);
}

void ftKb_AttackDash_Anim(Fighter_GObj* gobj)
{
    ftCo_AttackDash_Anim(gobj);
}

void ftKb_AttackDash_IASA(Fighter_GObj* gobj)
{
    ftCo_AttackDash_IASA(gobj);
}

void ftKb_AttackDash_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftKb_AttackDash_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F20C4);
}

void fn_800F20C4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_AttackDashAir, 0x0C4C5082,
                              fp->cur_anim_frame, fp->frame_speed_mul, 0.0f,
                              NULL);
}

void ftKb_AttackDashAir_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_AttackDashAir_IASA(Fighter_GObj* gobj) {}

void ftKb_AttackDashAir_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ft_80085204(gobj);
    ftCommon_FallBasic(fp);
}

void ftKb_AttackDashAir_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F1FDC);
}

void ftKb_AttackDashAir_800F21C0(Fighter_GObj* gobj)
{
    ftPartGetRotX(GET_FIGHTER(gobj), 0);
}

void fn_800F21E8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct ftKb_DatAttrs* da = fp->dat_attrs;
    if (fp->mv.kb.specialhi.xC == 0 && fp->cmd_vars[2] != 0) {
        Vec3 pos;
        f32 var_f1;
        fp->cmd_vars[2] = 0;
        fp->mv.kb.specialhi.xC = 1;
        lb_8000B1CC(fp->parts[0].joint, NULL, &pos);
        if (fp->facing_dir == 1.0F) {
            var_f1 = da->specialhi_projectile_spawn_x;
        } else {
            var_f1 = -da->specialhi_projectile_spawn_x;
        }
        pos.x += var_f1;
        pos.y += da->specialhi_projectile_spawn_y;
        pos.z = 0.0F;
        efLib_8005B704(gobj, 1);
        pos.y -= 1.0F;
        it_8029BAB8(gobj, &pos, fp->facing_dir);
    }
}

void ftKb_AttackDashAir_800F22D4(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftPartSetRotX(ft, 0, 0.0F);
}

/// #ftKb_SpecialHi_Enter

/// #ftKb_SpecialAirHi_Enter

/// #ftKb_SpecialHi1_Anim

/// #ftKb_SpecialHi2_Anim

void ftKb_SpecialHi3_Anim(Fighter_GObj* gobj) {}

void ftKb_SpecialAirHiEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialLw1_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialLwEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialAirLwStart_IASA(Fighter_GObj* gobj) {}

/// #ftKb_SpecialAirLw_IASA

void ftKb_SpecialAirLwEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialNLoop_Anim(Fighter_GObj* gobj) {}

void ftKb_SpecialAirNLoop_Anim(Fighter_GObj* gobj) {}

void ftKb_EatWait_Anim(Fighter_GObj* gobj) {}

void ftKb_SpecialAirNCaptureWait_Anim(Fighter_GObj* gobj) {}

void ftKb_EatJump2_Anim(Fighter_GObj* gobj) {}

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

/// #ftKb_SpecialAirHi1_Anim

/// #ftKb_SpecialAirHi2_Anim

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

void ftKb_SpecialHi1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* temp_r30 = &fp->co_attrs;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    PAD_STACK(4); // @todo Remove This
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
    PAD_STACK(4); // @todo Remove This
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
                      fp->co_attrs.air_drift_max);
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
                          dat_attr->specialhi_horizontal_momentum,
                      fp->co_attrs.air_drift_max);
}

void ftKb_SpecialAirHiEnd_Phys(Fighter_GObj* gobj)
{
    ft_80085134(gobj);
}

inline void ftKirbyDmgInline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death2_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE74C;
    fp->take_dmg_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE7B8;
}

inline void ftKirbyDmgInline2(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE7B8;
    fp->death2_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE74C;
}

void ftKb_SpecialHi1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirHi1, 0xC1082U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKirbyDmgInline(gobj);
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
            ftKirbyDmgInline(gobj);
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
        ftKirbyDmgInline(gobj);
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
        ftKirbyDmgInline(gobj);
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
        ftKirbyDmgInline(gobj);
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
            ftKirbyDmgInline(gobj);
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
        ftKirbyDmgInline(gobj);
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
        ftKirbyDmgInline(gobj);
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

void ftKb_SpecialHi_800F331C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    switch (fp->mv.kb.specialhi.x8.i) {
    case 1:
        fp->mv.kb.specialhi.x14++;
        break;
    case 2:
        fp->mv.kb.specialhi.x14--;
        break;
    }

    if ((fp->mv.kb.specialhi.x14 >= 0) && (fp->mv.kb.specialhi.x14 < 0x16)) {
        if (ftKb_Init_803CB490[fp->mv.kb.specialhi.x14] == 0) {
            ftParts_80074B0C(gobj, 0, 0);
            ftParts_80074B0C(gobj, 1, 0);
            ftCommon_8007F5CC(gobj, 1);
            fp->x221E_b4 = TRUE;
            fp->x2225_b2 = TRUE;
        } else {
            ftParts_80074B0C(
                gobj, 0, ftKb_Init_803CB4EC.ints[fp->mv.kb.specialhi.x10.i]);
            ftParts_80074B0C(gobj, 1, -1);
            ftCommon_8007F5CC(gobj, 0);
            fp->x221E_b4 = FALSE;
            fp->x2225_b2 = FALSE;
        }
    } else {
        fp->mv.kb.specialhi.x8.i = 0;
    }
}

void ftKb_SpecialHi_800F346C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    int new_var;

    switch (fp->cmd_vars[0]) {
    case 1:
        if (!fp->mv.kb.specialhi.x8.i && !fp->mv.kb.specialhi.xC) {
            fp->mv.kb.specialhi.x8.i = fp->cmd_vars[0];
            new_var = 1;
            fp->dmg.x1834 = dat_attr->speciallw_hp;
            fp->fv.kb.hat.x4 = fp->mv.kb.specialhi.x10.i =
                ((fp->fv.kb.hat.x4 + HSD_Randi(4)) % 5) + new_var;
            fp->mv.kb.specialhi.x14 = 0;
            fp->mv.kb.specialhi.xC = 1;
        }
        break;
    case 2:
        if (!fp->mv.kb.specialhi.x8.i && !fp->mv.kb.specialhi.xC) {
            fp->mv.kb.specialhi.x8.i = fp->cmd_vars[0];
            fp->mv.kb.specialhi.x14 = 0x16;
        }
        break;
    }
    fp->cmd_vars[0] = 0;
}

void ftKb_SpecialHi_800F3570(Fighter_GObj* gobj)
{
    Vec3 sp1C;
    Vec3 vec;
    f32 var_f3;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    fp->mv.kb.specialhi.x18 = fp->coll_data.floor.normal;
    fp->mv.kb.specialhi.xC4 =
        fp->facing_dir *
        atan2f(fp->mv.kb.specialhi.x18.x, fp->mv.kb.specialhi.x18.y);
    if (0.0f != fp->mv.kb.specialhi.x18.x) {
        vec.x = fp->cur_pos.y;
        vec.y = dat_attr->speciallw_slide_max_speed;
        vec.z = fp->cur_pos.x;
        if (fp->mv.kb.specialhi.x18.x > 0.0f) {
            var_f3 = 1.0f;
        } else {
            var_f3 = -1.0f;
        }
        if (mpCheckAllRemap(
                NULL, 0, NULL, &sp1C, -1, -1, vec.z, vec.x + vec.y,
                (fp->mv.kb.specialhi.x18.y * vec.y *
                 ((fp->mv.kb.specialhi.x18.x > 0.0f) ? 1.0f : -1.0f)) +
                    vec.z,
                vec.x - vec.y) == 0)
        {
            sp1C = ftKb_Init_803CB4EC.vec;
        }
        if (fp->mv.kb.specialhi.x18.x > 0.0f) {
            if (sp1C.x < 0.0f) {
                fp->mv.kb.specialhi.x18 = ftKb_Init_803CB4EC.vec;
                fp->mv.kb.specialhi.xC4 = 0.0f;
                fp->xE4_ground_accel_1 = 0.0f;
                fp->gr_vel = 0.0f;
            }
        } else if (sp1C.x > 0.0f) {
            fp->mv.kb.specialhi.x18 = ftKb_Init_803CB4EC.vec;
            fp->mv.kb.specialhi.xC4 = 0.0f;
            fp->xE4_ground_accel_1 = 0.0f;
            fp->gr_vel = 0.0f;
        }
    }
}

void ftKb_SpecialHi_800F36DC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.kb.speciallw.x24 = ftKb_Init_803CB4EC.vec;
    fp->mv.kb.speciallw.x54 = fp->mv.kb.speciallw.x24;
    fp->mv.kb.speciallw.x88[0] = 0.0f;
    fp->mv.kb.speciallw.x88[4] = 0.0f;
    fp->mv.kb.speciallw.x30 = ftKb_Init_803CB4EC.vec;
    fp->mv.kb.speciallw.x60 = fp->mv.kb.speciallw.x30;
    fp->mv.kb.speciallw.x88[1] = 0.0f;
    fp->mv.kb.speciallw.x88[5] = 0.0f;
    fp->mv.kb.speciallw.x3C = ftKb_Init_803CB4EC.vec;
    fp->mv.kb.speciallw.x6C = fp->mv.kb.speciallw.x3C;
    fp->mv.kb.speciallw.x88[2] = 0.0f;
    fp->mv.kb.speciallw.x88[6] = 0.0f;
    fp->mv.kb.speciallw.x48 = ftKb_Init_803CB4EC.vec;
    fp->mv.kb.speciallw.x78 = fp->mv.kb.speciallw.x48;
    fp->mv.kb.speciallw.x88[3] = 0.0f;
    fp->mv.kb.speciallw.x88[7] = 0.0f;
    fp->mv.kb.speciallw.x18 = ftKb_Init_803CB4EC.vec;
    fp->mv.kb.speciallw.x84 = 0.0f;
}

void ftKb_SpecialHi_800F37EC(Fighter_GObj* gobj)
{
    f32 temp_f5 = 0;
    s32 i;
    s32 j;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    fp->mv.kb.speciallw.x48 = fp->mv.kb.speciallw.x3C;
    fp->mv.kb.speciallw.x78 = fp->mv.kb.speciallw.x6C;
    fp->mv.kb.speciallw.x88[3] = fp->mv.kb.speciallw.x88[2];
    fp->mv.kb.speciallw.x88[7] = fp->mv.kb.speciallw.x88[6];
    fp->mv.kb.speciallw.x3C = fp->mv.kb.speciallw.x30;
    fp->mv.kb.speciallw.x6C = fp->mv.kb.speciallw.x60;
    fp->mv.kb.speciallw.x88[2] = fp->mv.kb.speciallw.x88[1];
    fp->mv.kb.speciallw.x88[6] = fp->mv.kb.speciallw.x88[5];
    fp->mv.kb.speciallw.x30 = fp->mv.kb.speciallw.x24;
    fp->mv.kb.speciallw.x60 = fp->mv.kb.speciallw.x54;
    fp->mv.kb.speciallw.x88[1] = fp->mv.kb.speciallw.x88[0];
    fp->mv.kb.speciallw.x88[5] = fp->mv.kb.speciallw.x88[4];
    fp->mv.kb.speciallw.x24 = fp->mv.kb.speciallw.x18;
    fp->mv.kb.speciallw.x88[0] = fp->mv.kb.speciallw.x84;
    fp->mv.kb.speciallw.x54.z = 0.0f;
    fp->mv.kb.speciallw.x54.y = 0.0f;
    fp->mv.kb.speciallw.x54.x = 0.0f;
    fp->mv.kb.speciallw.x88[4] = 0.0f;
    fp->mv.kb.speciallw.x54.x += fp->mv.kb.speciallw.x24.x;
    fp->mv.kb.speciallw.x54.y += fp->mv.kb.speciallw.x24.y;
    fp->mv.kb.speciallw.x54.z += fp->mv.kb.speciallw.x24.z;
    fp->mv.kb.speciallw.x88[4] += fp->mv.kb.speciallw.x88[0];
    fp->mv.kb.speciallw.x54.x += fp->mv.kb.speciallw.x30.x;
    fp->mv.kb.speciallw.x54.y += fp->mv.kb.speciallw.x30.y;
    fp->mv.kb.speciallw.x54.z += fp->mv.kb.speciallw.x30.z;
    fp->mv.kb.speciallw.x88[4] += fp->mv.kb.speciallw.x88[1];
    fp->mv.kb.speciallw.x54.x += fp->mv.kb.speciallw.x3C.x;
    fp->mv.kb.speciallw.x54.y += fp->mv.kb.speciallw.x3C.y;
    fp->mv.kb.speciallw.x54.z += fp->mv.kb.speciallw.x3C.z;
    fp->mv.kb.speciallw.x88[4] += fp->mv.kb.speciallw.x88[2];
    fp->mv.kb.speciallw.x54.x += fp->mv.kb.speciallw.x48.x;
    fp->mv.kb.speciallw.x54.y += fp->mv.kb.speciallw.x48.y;
    fp->mv.kb.speciallw.x54.z += fp->mv.kb.speciallw.x48.z;
    fp->mv.kb.speciallw.x88[4] += fp->mv.kb.speciallw.x88[3];
    lbVector_Normalize(&fp->mv.kb.speciallw.x54);
    i = 3;
    fp->mv.kb.speciallw.x88[4] *= 0.25f;
    fp->mv.kb.speciallw.x88[8] = 1.0f;
    for (i = 3; i > 0; i--) {
        if (ABS(fp->mv.kb.speciallw.x88[i]) >
            dat_attr->speciallw_min_slant_angle_slide)
        {
            for (j = i; j >= 0; j--) {
                if (ABS(fp->mv.kb.speciallw.x88[j]) <=
                    dat_attr->speciallw_min_slant_angle_slide)
                {
                    fp->mv.kb.speciallw.x88[8] = 0.9f;
                    j = -1;
                    i = -1;
                } else if (fp->mv.kb.speciallw.x88[j] > 0.0f) {
                    if (temp_f5 < 0.0f) {
                        fp->mv.kb.speciallw.x88[8] -= 0.25f;
                        if (fp->mv.kb.speciallw.x88[8] < 0.0f) {
                            fp->mv.kb.speciallw.x88[8] = 0.0f;
                        }
                    } else if (fp->mv.kb.speciallw.x88[j] > 0.0f) {
                        fp->mv.kb.speciallw.x88[8] -= 0.25f;
                        if (fp->mv.kb.speciallw.x88[8] < 0.0f) {
                            fp->mv.kb.speciallw.x88[8] = 0.0f;
                        }
                    }
                }
            }
        }
    }
}

void ftKb_SpecialHi_800F3B28(Fighter_GObj* gobj)
{
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f3;
    f32 var_f1_2;
    f32 var_f31;
    f32 var_f4;
    f32 var_f5;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    var_f31 = fp->mv.kb.speciallw.x88[4];
    ftPartSetRotX(fp, 0, var_f31);
    if (ABS(var_f31) < dat_attr->speciallw_min_slant_angle_slide) {
        var_f31 = 0.0f;
    }
    if (var_f31 > dat_attr->speciallw_max_slant_angle_slide) {
        var_f31 = dat_attr->speciallw_max_slant_angle_slide;
    }
    if (var_f31 < -dat_attr->speciallw_max_slant_angle_slide) {
        var_f31 = -dat_attr->speciallw_max_slant_angle_slide;
    }
    temp_f1 = ft_GetGroundFrictionMultiplier(fp);
    if (ABS(var_f31) < 0.017453292f) {
        var_f5 = 0.0f;
        temp_f3 = fp->gr_vel;
        temp_f2 =
            temp_f1 * (fp->mv.co.common.x58.x * fp->co_attrs.gr_friction);
        var_f1_2 = ABS(fp->gr_vel);
        if (ABS(temp_f2) > var_f1_2) {
            var_f4 = -fp->gr_vel;
        } else {
            if (temp_f3 > 0.0f) {
                var_f4 = -temp_f2;
            } else {
                var_f4 = temp_f2;
            }
        }
    } else {
        var_f4 = 0.0f;
        var_f5 =
            (1.0f + (1.0f - temp_f1)) *
            (fp->mv.co.common.x4C.z * dat_attr->speciallw_slide_acceleration);
    }
    fp->xE4_ground_accel_1 = fp->mv.kb.speciallw.x88[8] * (var_f5 + var_f4);
    fp->gr_vel *= fp->mv.kb.speciallw.x88[8];
    if (fp->gr_vel < -dat_attr->speciallw_slide_max_speed) {
        fp->gr_vel = -dat_attr->speciallw_slide_max_speed;
    } else if (fp->gr_vel > dat_attr->speciallw_slide_max_speed) {
        fp->gr_vel = dat_attr->speciallw_slide_max_speed;
    }
    if (fp->gr_vel + fp->xE4_ground_accel_1 <
        -dat_attr->speciallw_slide_max_speed)
    {
        fp->xE4_ground_accel_1 =
            -dat_attr->speciallw_slide_max_speed - fp->gr_vel;
    } else if (fp->gr_vel + fp->xE4_ground_accel_1 >
               dat_attr->speciallw_slide_max_speed)
    {
        fp->xE4_ground_accel_1 =
            dat_attr->speciallw_slide_max_speed - fp->gr_vel;
    }
    fp->x74_anim_vel.x = fp->mv.co.common.x58.x * fp->xE4_ground_accel_1;
    fp->x74_anim_vel.y = -fp->mv.co.common.x4C.z * fp->xE4_ground_accel_1;
    fp->x74_anim_vel.z = 0.0f;
    fp->self_vel.x = fp->mv.co.common.x58.x * fp->gr_vel;
    fp->self_vel.y = -fp->mv.co.common.x4C.z * fp->gr_vel;
    fp->self_vel.z = 0.0f;
}

void ftKb_SpecialLw_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* temp_r28;
    s32 temp_r30;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    PAD_STACK(0x18);

    temp_r28 = fp->parts[FtPart_YRotN].joint;
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->mv.kb.speciallw.x0 = dat_attr->speciallw_max_time_in_stone;
    fp->mv.kb.speciallw.x2 = dat_attr->speciallw_min_time_in_stone;
    fp->mv.kb.speciallw.x4 = 0;
    fp->mv.kb.speciallw.x6 = 0;
    fp->mv.kb.speciallw.x8 = 0;
    fp->mv.kb.speciallw.xC = 0;
    fp->mv.kb.speciallw.x10 = -1;
    fp->mv.kb.speciallw.x14 = -1;
    ftKb_SpecialHi_800F36DC(gobj);
    fp->dmg.x1834 = 0.0f;
    fp->x221C_b4 = 0;
    temp_r30 = fp->x221C_b4;
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialLw1, 0U, 0.0f, 1.0f, 0.0f,
                              NULL);
    fp->x221C_b4 = temp_r30;
    ftKirbyDmgInline2(gobj);
    ftAnim_8006EBA4(gobj);
    efSync_Spawn(0x49B, (HSD_GObj*) gobj, temp_r28);
}

void ftKb_SpecialAirLw_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* temp_r28;
    s32 temp_r30;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    PAD_STACK(0x18);

    temp_r28 = fp->parts[FtPart_YRotN].joint;
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->mv.kb.speciallw.x0 = dat_attr->speciallw_max_time_in_stone;
    fp->mv.kb.speciallw.x2 = dat_attr->speciallw_min_time_in_stone;
    fp->mv.kb.speciallw.x4 = 0;
    fp->mv.kb.speciallw.x6 = 0;
    fp->mv.kb.speciallw.x8 = 0;
    fp->mv.kb.speciallw.xC = 0;
    fp->mv.kb.speciallw.x10 = -1;
    fp->mv.kb.speciallw.x14 = -1;
    ftKb_SpecialHi_800F36DC(gobj);
    fp->dmg.x1834 = 0.0f;
    fp->x221C_b4 = 0;
    temp_r30 = fp->x221C_b4;
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirLwStart, 0U, 0.0f, 1.0f,
                              0.0f, NULL);
    fp->x221C_b4 = temp_r30;
    ftKirbyDmgInline2(gobj);
    ftAnim_8006EBA4(gobj);
    efSync_Spawn(0x49B, (HSD_GObj*) gobj, temp_r28);
}

void ftKb_SpecialLw1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 temp_r30;

    fp->x221C_b4 = 0;
    ftKb_SpecialHi_800F346C(gobj);
    ftKb_SpecialHi_800F331C(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        temp_r30 = fp->x221C_b4;
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialLw, 0x04440012U, 0.0f,
                                  0.0f, 0.0f, NULL);
        fp->x221C_b4 = temp_r30;
        ftAnim_SetAnimRate(gobj, 0.0f);
    }
}

inline void ftKbUnkInline(Fighter_GObj* gobj, int val)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x221C_b4 = val;
    ftKb_SpecialHi_800F346C(gobj);
    ftKb_SpecialHi_800F331C(gobj);
}

void ftKb_SpecialLw_Anim(Fighter_GObj* gobj)
{
    ftKbUnkInline(gobj, 1);
}

void ftKb_SpecialLwEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    ftKbUnkInline(gobj, 0);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        fp->dmg.x1834 = 0.0f;
        fp->x221C_b4 = 0;
        if (dat_attr->speciallw_freefall_toggle == 0.0f) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1.0f,
                      dat_attr->speciallw_freefall_toggle);
    }
}

void ftKb_SpecialAirLwStart_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 temp_r30;
    fp->x221C_b4 = 0;
    ftKb_SpecialHi_800F346C(gobj);
    ftKb_SpecialHi_800F331C(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        temp_r30 = fp->x221C_b4;
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirLw, 0x04440012U,
                                  0.0f, 0.0f, 0.0f, NULL);
        fp->x221C_b4 = temp_r30;
        ftAnim_SetAnimRate(gobj, 0.0f);
    }
}

void ftKb_SpecialAirLw_Anim(Fighter_GObj* gobj)
{
    ftKbUnkInline(gobj, 1);
}

void ftKb_SpecialAirLwEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    ftKbUnkInline(gobj, 0);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        fp->dmg.x1834 = 0.0f;
        fp->x221C_b4 = 0;
        if (dat_attr->speciallw_freefall_toggle == 0.0f) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1.0f,
                      dat_attr->speciallw_freefall_toggle);
    }
}

inline static bool fbKb_SpecialLw_IASA_Inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool result;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    if (fp->mv.kb.speciallw.x0 <= 0) {
        result = 1;
    } else if ((fp->mv.kb.speciallw.x0 <=
                (s32) (dat_attr->speciallw_max_time_in_stone -
                       dat_attr->speciallw_min_time_in_stone)) &&
               (fp->input.x668 & 0x200))
    {
        result = 1;
    } else {
        if (fp->mv.kb.speciallw.x0 > 0) {
            fp->mv.kb.speciallw.x0--;
        }
        result = 0;
    }

    return result;
}

void ftKb_SpecialLw_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 temp_r28;
    HSD_JObj* temp_r30 = fp->parts[FtPart_YRotN].joint;
    PAD_STACK(16);

    if (fbKb_SpecialLw_IASA_Inline(gobj)) {
        ftCommon_8007D5D4(fp);
        temp_r28 = fp->x221C_b4;
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialLwEnd, 0x04440012U,
                                  0.0f, 1.0f, 0.0f, NULL);
        fp->x221C_b4 = temp_r28;
        ftKirbyDmgInline(gobj);
        efSync_Spawn(0x49C, gobj, temp_r30);
    }
}

void ftKb_SpecialLw1_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftKb_SpecialLw_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ft_80084FA8(gobj);
    fp->self_vel.y = 0.0F;
    ftKb_SpecialHi_800F3B28(gobj);
}

void ftKb_SpecialLwEnd_Phys(Fighter_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftKb_SpecialAirLwStart_Phys(Fighter_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftKb_SpecialAirLw_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    ft_80085134(gobj);
    fp->self_vel.y = -da->speciallw_gravity;
}

void ftKb_SpecialAirLwEnd_Phys(Fighter_GObj* gobj)
{
    ft_80085134(gobj);
}

/// #ftKb_SpecialLw1_Coll

/// #ftKb_SpecialLw_Coll

/// #ftKb_SpecialLwEnd_Coll

/// #ftKb_SpecialAirLwStart_Coll

/// #ftKb_SpecialAirLw_Coll

/// #ftKb_SpecialAirLwEnd_Coll

void ftKb_SpecialAirLw_800F5318(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007F5CC(gobj, 1);
    fp->x221E_b4 = true;
    fp->x2225_b2 = true;
    fp->dmg.x1834 = 0.0f;
    fp->x221C_b4 = false;
    ftPartSetRotX(fp, 0, 0.0f);
    efLib_DestroyAll(gobj);
}

void ftKb_SpecialAirLw_800F539C(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->fv.kb.hat.x0 = 0;
}

/// #fn_800F53AC

void ftKb_SpecialAirLw_800F5524(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.x0 != NULL) {
        it_802ADC34(fp->fv.kb.hat.x0);
        fp->fv.kb.hat.x0 = NULL;
    }
}

void ftKb_SpecialS_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialS, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = &fn_800F53AC;
}

/// #ftKb_SpecialAirS_Enter

void ftKb_SpecialS_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_SpecialAirS_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(0x08);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_SpecialS_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirS_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialS_Coll(Fighter_GObj* gobj)
{
    Fighter* fp;
    if (ft_80082708(gobj) != 0) {
        return;
    }
    fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.x0 != NULL) {
        it_802ADC34(fp->fv.kb.hat.x0);
        fp->fv.kb.hat.x0 = NULL;
    }
    ftCo_Fall_Enter(gobj);
}

void ftKb_SpecialAirS_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    if (ft_80081D0C(gobj)) {
        Fighter* fp2 = GET_FIGHTER(gobj);
        if (fp2->fv.kb.hat.x0 != NULL) {
            it_802AEAB4(fp2->fv.kb.hat.x0);
            fp2->fv.kb.hat.x0 = NULL;
        }
        fp->fv.kb.x64 = false;
        ftCo_LandingFallSpecial_Enter(gobj, 0, da->specials_landing_lag);
    }
}

void ftKb_SpecialN_800F5800(HSD_GObj* gobj, Vec3* vec)
{
    Fighter* ft = GET_FIGHTER(gobj);
    *vec = ft->cur_pos;
}

void ftKb_SpecialN_800F5820(Fighter_GObj* gobj,
                            ftCollisionBox* victim_coll_box,
                            float victim_scale_x)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    victim_coll_box->top = da->specialn_unk1 * victim_scale_x;
    victim_coll_box->bottom =
        da->specialn_swallow_star_y_release * victim_scale_x;
    victim_coll_box->left.x = da->specialn_unk2 * victim_scale_x;
    victim_coll_box->left.y = da->specialn_unk3 * victim_scale_x;
    victim_coll_box->right.x = da->specialn_unk4 * victim_scale_x;
    victim_coll_box->right.y = da->specialn_unk5 * victim_scale_x;
}

void ftKb_SpecialN_800F5874(Vec2* arg0)
{
    ftCommonData* cd = gFtDataList[FTKIND_KIRBY]->ext_attr;
    arg0->x = cd->x9C_radians;
    arg0->y = cd->xA0_radians;
}

HSD_Joint* ftKb_SpecialN_800F5898(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftData* ca = fp->ft_data;
    return M2C_FIELD(&ca->x48_items[0], HSD_Joint**, 0x10);
}

float ftKb_SpecialN_800F58AC(Fighter_GObj* gobj, Vec3* victim_self_vel,
                             float victim_facing_dir)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    victim_self_vel->x = -victim_facing_dir *
                         da->specialn_ground_spit_initial_horizontal_velocity;
    victim_self_vel->z = 0.0f;
    victim_self_vel->y = 0.0f;
    return da->specialn_spit_deceleration_rate;
}

float ftKb_SpecialN_800F58D8(Fighter_GObj* gobj, Vec3* victim_self_vel,
                             float victim_facing_dir)
{
    float new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    new_var = 0.0F;
    victim_self_vel->x = victim_facing_dir *
                         da->specialn_swallow_star_vertical_velocity *
                         cosf(da->specialn_spit_out_release_angle);
    victim_self_vel->y = da->specialn_swallow_star_vertical_velocity *
                         sinf(da->specialn_spit_out_release_angle);
    victim_self_vel->z = new_var;
    return da->specialn_swallow_star_gravity;
}

void ftKb_SpecialN_800F5954(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    mpUpdateFloorSkip(&ft->coll_data);
}

bool ftKb_SpecialN_800F597C(Fighter_GObj* gobj)
{
    return M2C_FIELD(GET_FIGHTER(gobj), s32*, 0x840) & 0x100;
}

void ftKb_SpecialN_800F598C(Fighter_GObj* gobj, int arg1)
{
    f32 new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (fp->ground_or_air == GA_Ground) {
        new_var = (f32) arg1;
        mpUpdateFloorSkip(&fp->coll_data);
        fp->self_vel.y = da->specialn_stop_momentum * new_var;
    }
}

void ftKb_SpecialN_800F5A04(Fighter_GObj* gobj, f32 arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    if (!fp->ground_or_air) {
        fp->gr_vel = arg1 * dat_attr->specialn_stop_momentum;
        return;
    }
    fp->self_vel.x = arg1 * dat_attr->specialn_stop_momentum;
}

bool ftKb_SpecialN_800F5A38(Fighter_GObj* gobj, Fighter* victim_fp)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId id = fp->motion_id;
    if (id == ftKb_MS_EatWait || id == ftKb_MS_EatFall) {
        return 1;
    }
    return 0;
}

float ftKb_SpecialN_800F5A60(Fighter_GObj* gobj)
{
    return -GET_FIGHTER(gobj)->facing_dir;
}

float ftKb_SpecialN_800F5A70(void)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_gravity_of_inhaled;
}

f32 ftKb_SpecialN_800F5A88(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* da = GET_FIGHTER(gobj)->dat_attrs;
    return da->specialn_star_base_duration;
}

f32 ftKb_SpecialN_800F5A98(void)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_spit_spin;
}

f32 ftKb_SpecialN_800F5AB0(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* da = GET_FIGHTER(gobj)->dat_attrs;
    return da->specialn_frames_in_swallow_star;
}

f32 ftKb_SpecialN_800F5AC0(void)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_star_duration_divisor;
}

f32 ftKb_SpecialN_800F5AD8(void)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_star_deceleration_rate;
}

f32 ftKb_SpecialN_800F5AF0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    return da->specialn_base_duration;
}

f32 ftKb_SpecialN_800F5B00(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    return da->specialn_duration_divisor;
}

f32 ftKb_SpecialN_800F5B10(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    return da->specialn_inhale_resistance;
}

void ftKb_SpecialN_800F5B20(Fighter_GObj* gobj, Vec2* out)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct ftKb_DatAttrs* da = fp->dat_attrs;
    out->x = da->specialn_velocity_outer_grab_box;
    out->y = da->specialn_velocity_inner_grab_box;
}

float ftKb_SpecialN_800F5B3C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct ftKb_DatAttrs* da = fp->dat_attrs;
    return da->specialn_gravity_of_inhaled;
}

f32 ftKb_SpecialN_800F5B4C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    return da->specialn_z_offset_inhaled;
}

void ftKb_SpecialN_800F5B5C(Fighter_GObj* gobj, Vec3* output)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    *output = fp->cur_pos;
    output->x += da->specialn_x_offset_inhaled * fp->facing_dir;
    output->y += da->specialn_y_offset_inhaled;
}

void ftKb_SpecialN_800F5BA4(Fighter* fp)
{
    ftKb_DatAttrs* da = fp->dat_attrs;
    if ((s32) fp->kind == FTKIND_KIRBY &&
        (s32) fp->fv.kb.hat.kind != FTKIND_KIRBY && !fp->fv.kb.xF4_b0 &&
        (u32) fp->victim_gobj == 0U && (u32) fp->dmg.x1860_element != 0xAU &&
        HSD_Randi((s32) da->specialn_odds_lose_ability_on_hit) == 0)
    {
        ftKb_SpecialN_800F5D04(fp->gobj, 1);
    }
}

void ftKb_SpecialN_800F5C34(Fighter* fp)
{
    ftKb_DatAttrs* da = fp->dat_attrs;
    if ((s32) fp->kind == FTKIND_KIRBY &&
        (s32) fp->fv.kb.hat.kind != FTKIND_KIRBY && !fp->fv.kb.xF4_b0 &&
        (u32) fp->victim_gobj == 0U &&
        HSD_Randi((s32) da->specialn_odds_lose_ability_on_hit) == 0)
    {
        s32 msid = fp->motion_id;
        if (msid >= 0x18F && msid < 0x220) {
            ftCo_8008EC90(fp->gobj);
            ftKb_SpecialN_800F5D04(fp->gobj, 1);
            if ((s32) fp->ground_or_air == GA_Ground) {
                ft_8008A2BC(fp->gobj);
            } else {
                ftCo_Fall_Enter(fp->gobj);
            }
            return;
        }
        ftKb_SpecialN_800F5D04(fp->gobj, 1);
    }
}

void ftKb_SpecialN_800F5D04(Fighter_GObj* gobj, bool arg1)
{
    Vec3 pos;
    Vec3 vel;
    int pad;
    Fighter* new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da;
    ftKb_SpecialN_800F19AC(gobj);
    ftKb_SpecialN_800F190C(gobj, fp->fv.kb.hat.kind);
    ftKb_SpecialN_800EEEC4(gobj, fp->fv.kb.hat.kind);
    new_var = fp;
    if ((s32) fp->fv.kb.hat.kind != FTKIND_KIRBY && arg1 == 1) {
        Fighter* fp2 = GET_FIGHTER(gobj);
        da = fp2->dat_attrs;
        pos.x = fp2->cur_pos.x;
        pos.y = fp2->cur_pos.y + da->specialn_ability_loss_star_x;
        pos.z = 0.0F;
        vel.x = da->specialn_ability_loss_star_y * fp2->facing_dir;
        vel.y = da->specialn_ability_loss_star_z;
        vel.z = 0.0F;
        it_802ADA1C(&pos, &vel, fp2->facing_dir);
        ft_PlaySFX(fp, 0x22305, 0x7F, 0x40);
    }
    new_var->fv.kb.hat.kind = 4;
}

/// #ftKb_SpecialN_800F5DE8

/// #ftKb_SpecialN_800F5EA8

void ftKb_SpecialN_800F5F68(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4 * 14);

    fp->throw_flags = 0;
    fp->cmd_vars[0] = fp->cmd_vars[1] = 0;
    fp->fv.kb.xE0 = 4;

    // Ends up being 00 28 according to data sheet
    fp->fv.kb.xE4 = da->jumpaerial_unk;

    fp->fv.kb.xE8 = lbAnim_8001E8F8(ftData_80085E50(fp, ftCo_MS_HammerFall));
    fp->fv.kb.xEC = lbAnim_8001E8F8(ftData_80085E50(fp, ftCo_MS_HammerJump));
    fp->fv.kb.xF0 =
        lbAnim_8001E8F8(ftData_80085E50(fp, ftCo_MS_HammerLanding));

    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialN, 0, 0, 1, 0, NULL);
    fp->x2222_b2 = true;
    ftAnim_8006EBA4(gobj);
    {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007E2D0(fp, 16, fn_800F6210, fn_800F6178, ftCo_800BD1DC);
        fp->x2225_b1 = true;
    }
}

void ftKb_SpecialN_800F6070(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4 * 14);

    fp->throw_flags = 0;
    fp->cmd_vars[0] = fp->cmd_vars[1] = 0;
    fp->fv.kb.xE0 = 4;
    fp->fv.kb.xE4 = da->jumpaerial_unk;
    fp->fv.kb.xE8 = lbAnim_8001E8F8(ftData_80085E50(fp, ftCo_MS_HammerFall));
    fp->fv.kb.xEC = lbAnim_8001E8F8(ftData_80085E50(fp, ftCo_MS_HammerJump));
    fp->fv.kb.xF0 =
        lbAnim_8001E8F8(ftData_80085E50(fp, ftCo_MS_HammerLanding));

    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirN, 0, 0, 1, 0, NULL);
    fp->x2222_b2 = true;
    ftAnim_8006EBA4(gobj);
    {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007E2D0(fp, 16, fn_800F6318, fn_800F6280, ftCo_800BD1DC);
        fp->x2225_b1 = true;
    }
}

void fn_800F6178(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    it_802F23EC(fp->target_item_gobj, gobj, -fp->facing_dir);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialNCapture1,
                              Ft_MF_KeepGfx | Ft_MF_SkipModel | Ft_MF_KeepSfx,
                              0, 1, 0, NULL);
    fp->x2222_b2 = true;
    fp->fv.kb.xF4_b0 = true;
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

static void fn_800F6210(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialNCapture0, 0x212, 0.0f,
                              1.0f, 0.0f, NULL);
    fp->x2222_b2 = true;
    fp->fv.kb.xF4_b0 = false;
    ftCommon_8007E2F4(fp, 0x1FF);
}

static void fn_800F6280(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    it_802F23EC(fp->target_item_gobj, gobj, -fp->facing_dir);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirNCapture1,
                              Ft_MF_KeepGfx | Ft_MF_SkipModel | Ft_MF_KeepSfx,
                              0, 1, 0, NULL);
    fp->x2222_b2 = true;
    fp->fv.kb.xF4_b0 = true;
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

static void fn_800F6318(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirNCapture0, 0x212, 0.0f,
                              1.0f, 0.0f, NULL);
    fp->x2222_b2 = true;
    fp->fv.kb.xF4_b0 = false;
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftKb_SpecialN_800F6388(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_EatWait, 0x10, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftKb_SpecialN_800F63EC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_EatFall, 0x10, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6450(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_EatFall, 0x90, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

/// #fn_800F64C8

void fn_800F6528(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_EatLanding, 0x12, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftAnim_8006EBA4(gobj);
}

void fn_800F6588(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirN, 0x0C4C529A,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp = GET_FIGHTER(gobj);
    ftCommon_8007E2D0(fp, 0x10, fn_800F6318, fn_800F6280, ftCo_800BD1DC);
    fp->x2225_b1 = true;
}

void fn_800F6638(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialN, 0x0C4C529A,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp = GET_FIGHTER(gobj);
    ftCommon_8007E2D0(fp, 0x10, fn_800F6210, fn_800F6178, ftCo_800BD1DC);
    fp->x2225_b1 = true;
}

void fn_800F66E8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirNLoop, 0x0C4C5A9A,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp = GET_FIGHTER(gobj);
    ftCommon_8007E2D0(fp, 0x10, fn_800F6318, fn_800F6280, ftCo_800BD1DC);
    fp->x2225_b1 = true;
}

void fn_800F6798(HSD_GObj* gobj)
{
    Fighter* new_var;
    volatile unsigned long long pad;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialNLoop, 0x0C4C5A9A,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp = GET_FIGHTER(gobj);
    ftCommon_8007E2D0(fp, 0x10, fn_800F6210, fn_800F6178, ftCo_800BD1DC);
    new_var = fp;
    new_var->x2225_b1 = true;
}

void fn_800F6848(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirNEnd, 0x0C4C5082,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
}

void fn_800F68A8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialNEnd, 0x0C4C5082,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
}

void fn_800F6908(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirNCapture1, 0x0C4C5092,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F697C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirNCapture0, 0x0C4C5092,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F69E8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialNCapture1, 0x0C4C5092,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6A5C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialNCapture0, 0x0C4C5092,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    ftCommon_8007E2F4(fp, 0x1FF);
}

/// Fighter_CollGround_PassLedgeCB
static void fn_800F6AC8(HSD_GObj* gobj)
{
    /// @@todo Named flags.
    static u32 const mf = (1 << 1) | (1 << 4) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_EatAir, mf, fp->cur_anim_frame, 1,
                              0, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6B3C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_Eat, 0x0C4C5092,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftKb_SpecialS_800F6BB0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_EatFall, 0x0C4C5090,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6C24(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirNSpit1, 0x0C4C5092,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6C98(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirNSpit0, 0x0C4C5092,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6D0C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialNSpit1, 0x0C4C5092,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6D80(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialNSpit0, 0x0C4C5092,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6DF4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirNDrink1, 0x0C4C5082,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6E68(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirNDrink0, 0x0C4C5082,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6EDC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialNDrink1, 0x0C4C5082,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6F50(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialNDrink0, 0x0C4C5082,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6FC4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_EatTurnAir, 0x0C4C5092,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialN_800F9070(gobj);
}

void fn_800F702C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_EatTurn, 0x0C4C5092,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

/// #ftKb_SpecialN_Anim

/// #ftKb_SpecialAirN_Anim

void ftKb_SpecialNEnd_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_SpecialAirNEnd_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

/// #ftKb_SpecialNCapture0_Anim

/// #ftKb_SpecialNCapture_Anim

void ftKb_SpecialNCapture1_Anim(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800F5DE8(gobj);
}

void ftKb_SpecialAirNCapture_Anim(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800F5EA8(gobj);
}

void ftKb_Eat_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        PAD_STACK(4);
        Fighter_ChangeMotionState(gobj, ftKb_MS_EatWait, Ft_MF_SkipModel, 0, 1,
                                  0, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

void ftKb_SpecialAirNCaptured_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_EatFall, 0x90, 0.0f, 1.0f,
                                  0.0f, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

/// #ftKb_SpecialNSpit0_Anim

/// #ftKb_SpecialNSpit_Anim

/// #ftKb_SpecialNSpit1_Anim

/// #ftKb_SpecialAirNSpit_Anim

/// #ftKb_SpecialNDrink0_Anim

/// #ftKb_SpecialNDrink_Anim

/// #ftKb_SpecialNDrink1_Anim

/// #ftKb_SpecialAirNDrink_Anim

void ftKb_EatTurn_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->facing_dir = -fp->facing_dir;
        fp = GET_FIGHTER(gobj);
        Fighter_ChangeMotionState(gobj, ftKb_MS_EatWait, Ft_MF_SkipModel, 0.0f,
                                  0.0f, 0.0f, NULL);
        ftAnim_8006EBA4(gobj);
        ftKb_SpecialN_800F9070(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

void ftKb_SpecialAirNCaptureTurn_Anim(Fighter_GObj* gobj)
{
    Fighter_GObj* new_var;
    Fighter_GObj* new_var2;
    Fighter* fp = GET_FIGHTER(gobj);
    new_var = gobj;
    new_var2 = new_var;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->facing_dir = -fp->facing_dir;
        fp = new_var2->user_data;
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_EatFall, 0x90, 0.0f, 1.0f,
                                  0.0f, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

void ftKb_EatWalk_Anim(Fighter_GObj* gobj)
{
    ftWalkCommon_800DFDDC(gobj);
}

/// #ftKb_EatJump1_Anim

void ftKb_EatLanding_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        PAD_STACK(4);
        Fighter_ChangeMotionState(gobj, ftKb_MS_EatWait, Ft_MF_SkipModel, 0, 1,
                                  0, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

/// #ftKb_SpecialNLoop_IASA

/// #ftKb_SpecialAirNLoop_IASA

/// #ftKb_EatWait_IASA

/// #ftKb_SpecialAirNCaptureWait_IASA

/// #ftKb_EatWalk_IASA

void ftKb_EatJump1_IASA(Fighter_GObj* gobj)
{
    ftCo_KneeBend_Check_ShortHop(gobj);
}

void ftKb_SpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialNCapture0_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNCapture_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNCapture1_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialAirNCapture_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_Eat_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirNCaptured_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_EatWait_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirNCaptureWait_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialNSpit0_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNSpit_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNSpit1_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialAirNSpit_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialNDrink0_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNDrink_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNDrink1_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialAirNDrink_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_EatTurn_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirNCaptureTurn_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_EatWalk_Phys(Fighter_GObj* gobj)
{
    ftWalkCommon_800E0060(gobj);
}

void ftKb_EatJump1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_EatJump2_Phys(Fighter_GObj* gobj)
{
    ftCo_Jump_Phys_Inner(gobj);
}

void ftKb_EatLanding_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialN_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6588);
}

void ftKb_SpecialAirN_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6638);
}

void ftKb_SpecialNLoop_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F66E8);
}

void ftKb_SpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6798);
}

void ftKb_SpecialNEnd_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6848);
}

void ftKb_SpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F68A8);
}

void ftKb_SpecialNCapture0_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6908);
}

void ftKb_SpecialNCapture_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F697C);
}

void ftKb_SpecialNCapture1_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F69E8);
}

void ftKb_SpecialAirNCapture_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6A5C);
}

void ftKb_Eat_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6AC8);
}

void ftKb_SpecialAirNCaptured_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6B3C);
}

void ftKb_EatWait_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, ftKb_SpecialS_800F6BB0);
}

void ftKb_SpecialAirNCaptureWait_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6528);
}

void ftKb_SpecialNSpit0_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6C24);
}

void ftKb_SpecialNSpit_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6C98);
}

void ftKb_SpecialNSpit1_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6D0C);
}

void ftKb_SpecialAirNSpit_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6D80);
}

void ftKb_SpecialNDrink0_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6DF4);
}

void ftKb_SpecialNDrink_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6E68);
}

void ftKb_SpecialNDrink1_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6EDC);
}

void ftKb_SpecialAirNDrink_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6F50);
}

void ftKb_EatTurn_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6FC4);
}

void ftKb_SpecialAirNCaptureTurn_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F702C);
}

void ftKb_EatWalk_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6450);
}

void ftKb_EatJump1_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6450);
}

void ftKb_EatJump2_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6528);
}

void ftKb_EatLanding_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6450);
}

void ftKb_SpecialN_800F9070(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death3_cb = ftKb_Init_800EE74C;
    fp->death1_cb = ftKb_Init_800EE7B8;
}

void ftKb_SpecialN_800F9090(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->target_item_gobj != NULL && fp->kind == FTKIND_KIRBY &&
        fp->fv.kb.hat.kind == FTKIND_KIRBY)
    {
        bool capturing = false;
        if (fp->motion_id == ftKb_MS_SpecialNCapture1 ||
            fp->motion_id == ftKb_MS_SpecialAirNCapture1)
        {
            capturing = true;
        }
        it_802F28C8(fp->target_item_gobj, capturing, 0);
        fp->x1A64 = NULL;
        fp->target_item_gobj = NULL;
    }
}

void ftKb_SpecialN_800F9110(Fighter_GObj* gobj)
{
    int new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKirby_MotionState msid = ftKb_MS_MrSpecialN;
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->fv.kb.hat.kind != FTKIND_MARIO) {
            new_var = 0x200;
            msid = new_var;
        }
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_800F9260;
}

void ftKb_MrSpecialN_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_MrSpecialN_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (ft->cmd_vars[0] != 0) {
        ftCo_Wait_IASA(gobj);
    }
}

void ftKb_MrSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MrSpecialN_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftKb_SpecialNLg_800F951C(gobj);
    }
}

/// #fn_800F9260

void ftKb_SpecialNMr_800F93CC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid = ftKb_MS_MrSpecialAirN;
    PAD_STACK(8);
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    if (GET_FIGHTER(gobj)->fv.kb.hat.kind != FTKIND_MARIO) {
        msid = ftKb_MS_DrSpecialAirN;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0F, 1.0F, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_800F9260;
}

void ftKb_MrSpecialAirN_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_MrSpecialAirN_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (ft->cmd_vars[0] != 0) {
        ftCo_Fall_IASA_Inner(gobj);
    }
}

void ftKb_MrSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKb_MrSpecialAirN_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftKb_SpecialNLg_800F9598(gobj);
    }
}

static void fn_800F98F4(Fighter_GObj*);

/// #ftKb_SpecialNLg_800F951C

/// #ftKb_SpecialNLg_800F9598

void ftKb_SpecialNLg_800F9614(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    Fighter_ChangeMotionState(gobj, ftKb_MS_LgSpecialN, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_800F98F4;
}

void ftKb_SpecialNLg_800F9684(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    Fighter_ChangeMotionState(gobj, ftKb_MS_LgSpecialAirN, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_800F98F4;
}

void ftKb_LgSpecialN_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_LgSpecialAirN_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_LgSpecialN_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (ft->cmd_vars[0] != 0) {
        ftCo_Wait_IASA(gobj);
    }
}

void ftKb_LgSpecialAirN_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (ft->cmd_vars[0] != 0) {
        ftCo_Fall_IASA_Inner(gobj);
    }
}

void ftKb_LgSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_LgSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

/// #ftKb_LgSpecialN_Coll

/// #ftKb_LgSpecialAirN_Coll

/// #fn_800F98F4

void ftKb_SpecialNCa_800F99BC(Fighter_GObj* gobj)
{
    ftKirby_MotionState msid = ftKb_MS_CaSpecialN;
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.kind != FTKIND_CAPTAIN) {
        msid = ftKb_MS_GnSpecialN;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    ftAnim_8006EBA4(gobj);
}

void ftKb_SpecialNCa_800F9A54(Fighter_GObj* gobj)
{
    ftKirby_MotionState msid = ftKb_MS_CaSpecialAirN;
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.kind != FTKIND_CAPTAIN) {
        msid = ftKb_MS_GnSpecialAirN;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
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

/// #ftKb_CaSpecialAirN_IASA

void ftKb_CaSpecialN_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool throw_b1;
    long long pad;
    if (fp->throw_flags_b1) {
        fp->throw_flags_b1 = false;
        throw_b1 = true;
    } else {
        throw_b1 = false;
    }
    if (throw_b1) {
        if (!fp->x2219_b0) {
            switch (fp->fv.kb.hat.kind) {
            case FTKIND_CAPTAIN:
                efSync_Spawn(1195, gobj, fp->parts[0].joint,
                             fp->parts[44].joint);
                break;
            case FTKIND_GANON:
                efSync_Spawn(1203, gobj, fp->parts[0].joint,
                             fp->parts[44].joint);
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
    if (fp->throw_flags_b1) {
        fp->throw_flags_b1 = false;
        throw_b1 = true;
    } else {
        throw_b1 = false;
    }
    if (throw_b1) {
        if (!fp->x2219_b0) {
            switch (fp->fv.kb.hat.kind) {
            case FTKIND_CAPTAIN:
                efSync_Spawn(1195, gobj, fp->parts[0].joint,
                             fp->parts[44].joint);
                break;
            case FTKIND_GANON:
                efSync_Spawn(1203, gobj, fp->parts[0].joint,
                             fp->parts[44].joint);
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

/// #ftKb_CaSpecialN_Coll

/// #ftKb_CaSpecialAirN_Coll

void ftKb_SpecialNPk_800F9FD4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid = ftKb_MS_PkSpecialN;
    PAD_STACK(8);
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_PIKACHU:
        break;
    case FTKIND_PICHU:
        msid = ftKb_MS_PcSpecialN;
        break;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0F, 1.0F, 0.0F, NULL);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftAnim_8006EBA4(gobj);
}
