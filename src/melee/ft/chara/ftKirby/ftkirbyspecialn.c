#include "ftkirby.h"
#include "types.h"

#include <placeholder.h>

#include "baselib/forward.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_Damage.h"
#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
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

#include "ftKirby/forward.h"

#include "ftKirby/inlines.h"
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
#include "lb/lbvector.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"

#include <common_structs.h>
#include <stddef.h>
#include <trigf.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

/// External variables from ftkirby.c
extern bool ftKb_Init_803CB490[];

struct ftKb_Init_803CB4EC_t {
    int ints[6];
    Vec3 vec;
};

struct ftKb_Init_803CB490_layout {
    char pad[0x74];
    Vec3 vec;
};

extern struct ftKb_Init_803CB4EC_t ftKb_Init_803CB4EC;

extern char ftKb_Init_803CB510[];

/// Forward declarations
void fn_800F9260(HSD_GObj*);
void fn_800F64C8(Fighter_GObj*, float);
void fn_800F6178(HSD_GObj* gobj);
static void fn_800F6210(HSD_GObj* gobj);
static void fn_800F6280(HSD_GObj* gobj);
static void fn_800F6318(HSD_GObj* gobj);
static void fn_800F6AC8(HSD_GObj* gobj);

static inline bool fbKb_SpecialLw_IASA_Inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool result;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;

    if (fp->mv.kb.speciallw.x0 <= 0) {
        result = true;
    } else if ((fp->mv.kb.speciallw.x0 <=
                (s32) (dat_attr->speciallw_max_time_in_stone -
                       dat_attr->speciallw_min_time_in_stone)) &&
               (fp->input.x668 & 0x200))
    {
        result = true;
    } else {
        if (fp->mv.kb.speciallw.x0 > 0) {
            fp->mv.kb.speciallw.x0--;
        }
        result = false;
    }

    return result;
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
        if (!fp->mv.kb.specialhi.x8.i && fp->mv.kb.specialhi.xC == 1) {
            fp->mv.kb.specialhi.x8.i = fp->cmd_vars[0];
            fp->mv.kb.specialhi.x14 = 0x16;
        }
        break;
    }
    fp->cmd_vars[0] = 0;
}

void ftKb_SpecialHi_800F3570(Fighter_GObj* gobj)
{
    UNUSED u8 pad[24];
    Vec3 sp1C;
    f32 pos_y;
    f32 slide_speed;
    f32 pos_x;
    f32 top_y;
    f32 bottom_y;
    f32 floor_normal_x_sign;
    Fighter* fp = GET_FIGHTER(gobj);
    struct ftKb_Init_803CB490_layout* p =
        (struct ftKb_Init_803CB490_layout*) ftKb_Init_803CB490;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    PAD_STACK(12);

    fp->mv.kb.specialhi.x18 = fp->coll_data.floor.normal;
    fp->mv.kb.specialhi.xC4 =
        fp->facing_dir *
        atan2f(fp->mv.kb.specialhi.x18.x, fp->mv.kb.specialhi.x18.y);
    if (0.0f != fp->mv.kb.specialhi.x18.x) {
        pos_y = fp->cur_pos.y;
        slide_speed = dat_attr->speciallw_slide_max_speed;
        top_y = pos_y + slide_speed;
        floor_normal_x_sign = fp->mv.kb.specialhi.x18.x > 0.0f ? 1.0f : -1.0f;
        bottom_y = pos_y - slide_speed;
        pos_x = fp->cur_pos.x;
        if (mpCheckAllRemap(NULL, 0, NULL, &sp1C, -1, -1, pos_x, top_y,
                            (fp->mv.kb.specialhi.x18.y * slide_speed *
                             floor_normal_x_sign) +
                                pos_x,
                            bottom_y) == 0)
        {
            sp1C = p->vec;
        }
        if (fp->mv.kb.specialhi.x18.x > 0.0f) {
            if (sp1C.x < 0.0f) {
                fp->mv.kb.specialhi.x18 = p->vec;
                fp->mv.kb.specialhi.xC4 = 0.0f;
                fp->xE4_ground_accel_1 = 0.0f;
                fp->gr_vel = 0.0f;
            }
        } else if (sp1C.x > 0.0f) {
            fp->mv.kb.specialhi.x18 = p->vec;
            fp->mv.kb.specialhi.xC4 = 0.0f;
            fp->xE4_ground_accel_1 = 0.0f;
            fp->gr_vel = 0.0f;
        }
    }
}

void ftKb_SpecialHi_800F36DC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct ftKb_Init_803CB490_layout* p =
        (struct ftKb_Init_803CB490_layout*) ftKb_Init_803CB490;
    fp->mv.kb.speciallw.x24 = p->vec;
    fp->mv.kb.speciallw.x54 = fp->mv.kb.speciallw.x24;
    fp->mv.kb.speciallw.x88[0] = 0.0f;
    fp->mv.kb.speciallw.x88[4] = 0.0f;
    fp->mv.kb.speciallw.x30 = p->vec;
    fp->mv.kb.speciallw.x60 = fp->mv.kb.speciallw.x30;
    fp->mv.kb.speciallw.x88[1] = 0.0f;
    fp->mv.kb.speciallw.x88[5] = 0.0f;
    fp->mv.kb.speciallw.x3C = p->vec;
    fp->mv.kb.speciallw.x6C = fp->mv.kb.speciallw.x3C;
    fp->mv.kb.speciallw.x88[2] = 0.0f;
    fp->mv.kb.speciallw.x88[6] = 0.0f;
    fp->mv.kb.speciallw.x48 = p->vec;
    fp->mv.kb.speciallw.x78 = fp->mv.kb.speciallw.x48;
    fp->mv.kb.speciallw.x88[3] = 0.0f;
    fp->mv.kb.speciallw.x88[7] = 0.0f;
    fp->mv.kb.speciallw.x18 = p->vec;
    fp->mv.kb.speciallw.x84 = 0.0f;
}

void ftKb_SpecialHi_800F37EC(Fighter_GObj* gobj)
{
    f32 abs_slide_angle;
    f32 slide_angle;
    s32 i;
    s32 j;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    PAD_STACK(16);
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
    fp->mv.kb.speciallw.x88[4] *= 0.25f;
    fp->mv.kb.speciallw.x88[8] = 1.0f;
    for (i = 3; i > 0; i--) {
        if (ABS(fp->mv.kb.speciallw.x88[i]) >
            dat_attr->speciallw_min_slant_angle_slide)
        {
            for (j = i; j >= 0; j--) {
                if ((slide_angle = fp->mv.kb.speciallw.x88[j]) < 0.0f) {
                    abs_slide_angle = -slide_angle;
                } else {
                    abs_slide_angle = slide_angle;
                }
                if (abs_slide_angle <=
                    dat_attr->speciallw_min_slant_angle_slide)
                {
                    fp->mv.kb.speciallw.x88[8] = 0.9f;
                    j = -1;
                    i = -1;
                } else if (fp->mv.kb.speciallw.x88[i] > 0.0f) {
                    if (slide_angle < 0.0f) {
                        fp->mv.kb.speciallw.x88[8] -= 0.25f;
                        if (fp->mv.kb.speciallw.x88[8] < 0.0f) {
                            fp->mv.kb.speciallw.x88[8] = 0.0f;
                        }
                    }
                } else if (slide_angle > 0.0f) {
                    fp->mv.kb.speciallw.x88[8] -= 0.25f;
                    if (fp->mv.kb.speciallw.x88[8] < 0.0f) {
                        fp->mv.kb.speciallw.x88[8] = 0.0f;
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
    ftKb_SpecialN_set_cbs2(gobj);
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
    ftKb_SpecialN_set_cbs2(gobj);
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

void ftKb_SpecialLw1_IASA(Fighter_GObj* gobj) {}

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
        ftKb_SpecialN_set_cbs2(gobj);
        efSync_Spawn(0x49C, gobj, temp_r30);
    }
}

void ftKb_SpecialLwEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialAirLwStart_IASA(Fighter_GObj* gobj) {}

void ftKb_SpecialAirLw_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 temp_r28;
    HSD_JObj* temp_r31 = fp->parts[FtPart_YRotN].joint;
    PAD_STACK(16);

    if (fbKb_SpecialLw_IASA_Inline(gobj)) {
        temp_r28 = fp->x221C_b4;
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirLwEnd,
                                  0x04440012U, 0.0f, 1.0f, 0.0f, NULL);
        fp->x221C_b4 = temp_r28;
        ftKb_SpecialN_set_cbs2(gobj);
        efSync_Spawn(0x49C, gobj, temp_r31);
    }
}

void ftKb_SpecialAirLwEnd_IASA(Fighter_GObj* gobj) {}

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

void ftKb_SpecialLw1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* fp2;
    Fighter* fp3;
    s32 temp;
    struct ftKb_Init_803CB490_layout* p =
        (struct ftKb_Init_803CB490_layout*) ftKb_Init_803CB490;
    PAD_STACK(16);

    if (ft_80082708(gobj) == GA_Ground) {
        fp2 = GET_FIGHTER(gobj);
        fp2->mv.kb.speciallw.x24 = p->vec;
        fp2->mv.kb.speciallw.x54 = fp2->mv.kb.speciallw.x24;
        fp2->mv.kb.speciallw.x88[0] = 0.0f;
        fp2->mv.kb.speciallw.x88[4] = 0.0f;
        fp2->mv.kb.speciallw.x30 = p->vec;
        fp2->mv.kb.speciallw.x60 = fp2->mv.kb.speciallw.x30;
        fp2->mv.kb.speciallw.x88[1] = 0.0f;
        fp2->mv.kb.speciallw.x88[5] = 0.0f;
        fp2->mv.kb.speciallw.x3C = p->vec;
        fp2->mv.kb.speciallw.x6C = fp2->mv.kb.speciallw.x3C;
        fp2->mv.kb.speciallw.x88[2] = 0.0f;
        fp2->mv.kb.speciallw.x88[6] = 0.0f;
        fp2->mv.kb.speciallw.x48 = p->vec;
        fp2->mv.kb.speciallw.x78 = fp2->mv.kb.speciallw.x48;
        fp2->mv.kb.speciallw.x88[3] = 0.0f;
        fp2->mv.kb.speciallw.x88[7] = 0.0f;
        fp2->mv.kb.speciallw.x18 = p->vec;
        fp2->mv.kb.speciallw.x84 = 0.0f;
        fp->self_vel.x = 0.0f;
        ftCommon_8007D5D4(fp);
        temp = fp->x221C_b4;
        Fighter_ChangeMotionState(gobj, 0x18C, 0x0C4C5092U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        fp->x221C_b4 = temp;
        fp3 = GET_FIGHTER(gobj);
        fp3->take_dmg_cb = ftKb_Init_800EE7B8;
        fp3->death2_cb = ftKb_Init_800EE74C;
        ftPartSetRotX(fp, 0, 0.0f);
    } else {
        ftKb_SpecialHi_800F3570(gobj);
        ftKb_SpecialHi_800F37EC(gobj);
    }
}

void ftKb_SpecialLw_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* fp2;
    Fighter* fp3;
    s32 temp;
    struct ftKb_Init_803CB490_layout* p =
        (struct ftKb_Init_803CB490_layout*) ftKb_Init_803CB490;
    PAD_STACK(16);

    if (ft_80082708(gobj) == GA_Ground) {
        fp2 = GET_FIGHTER(gobj);
        fp2->mv.kb.speciallw.x24 = p->vec;
        fp2->mv.kb.speciallw.x54 = fp2->mv.kb.speciallw.x24;
        fp2->mv.kb.speciallw.x88[0] = 0.0f;
        fp2->mv.kb.speciallw.x88[4] = 0.0f;
        fp2->mv.kb.speciallw.x30 = p->vec;
        fp2->mv.kb.speciallw.x60 = fp2->mv.kb.speciallw.x30;
        fp2->mv.kb.speciallw.x88[1] = 0.0f;
        fp2->mv.kb.speciallw.x88[5] = 0.0f;
        fp2->mv.kb.speciallw.x3C = p->vec;
        fp2->mv.kb.speciallw.x6C = fp2->mv.kb.speciallw.x3C;
        fp2->mv.kb.speciallw.x88[2] = 0.0f;
        fp2->mv.kb.speciallw.x88[6] = 0.0f;
        fp2->mv.kb.speciallw.x48 = p->vec;
        fp2->mv.kb.speciallw.x78 = fp2->mv.kb.speciallw.x48;
        fp2->mv.kb.speciallw.x88[3] = 0.0f;
        fp2->mv.kb.speciallw.x88[7] = 0.0f;
        fp2->mv.kb.speciallw.x18 = p->vec;
        fp2->mv.kb.speciallw.x84 = 0.0f;
        fp->self_vel.x = 0.0f;
        ftCommon_8007D5D4(fp);
        temp = fp->x221C_b4;
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirLw, 0x0C4C1092U,
                                  0.0f, 0.0f, 0.0f, NULL);
        fp->x221C_b4 = temp;
        ftAnim_SetAnimRate(gobj, 0.0f);
        fp3 = GET_FIGHTER(gobj);
        fp3->take_dmg_cb = ftKb_Init_800EE7B8;
        fp3->death2_cb = ftKb_Init_800EE74C;
        ftPartSetRotX(fp, 0, 0.0f);
    } else {
        ftKb_SpecialHi_800F3570(gobj);
        ftKb_SpecialHi_800F37EC(gobj);
    }
}

void ftKb_SpecialLwEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* fp2;
    struct ftKb_Init_803CB490_layout* p =
        (struct ftKb_Init_803CB490_layout*) ftKb_Init_803CB490;
    PAD_STACK(8);
    ft_80081D0C(gobj);
    fp2 = GET_FIGHTER(gobj);
    fp2->mv.kb.speciallw.x24 = p->vec;
    fp2->mv.kb.speciallw.x54 = fp2->mv.kb.speciallw.x24;
    fp2->mv.kb.speciallw.x88[0] = 0.0f;
    fp2->mv.kb.speciallw.x88[4] = 0.0f;
    fp2->mv.kb.speciallw.x30 = p->vec;
    fp2->mv.kb.speciallw.x60 = fp2->mv.kb.speciallw.x30;
    fp2->mv.kb.speciallw.x88[1] = 0.0f;
    fp2->mv.kb.speciallw.x88[5] = 0.0f;
    fp2->mv.kb.speciallw.x3C = p->vec;
    fp2->mv.kb.speciallw.x6C = fp2->mv.kb.speciallw.x3C;
    fp2->mv.kb.speciallw.x88[2] = 0.0f;
    fp2->mv.kb.speciallw.x88[6] = 0.0f;
    fp2->mv.kb.speciallw.x48 = p->vec;
    fp2->mv.kb.speciallw.x78 = fp2->mv.kb.speciallw.x48;
    fp2->mv.kb.speciallw.x88[3] = 0.0f;
    fp2->mv.kb.speciallw.x88[7] = 0.0f;
    fp2->mv.kb.speciallw.x18 = p->vec;
    fp2->mv.kb.speciallw.x84 = 0.0f;
    ftPartSetRotX(fp, 0, 0.0f);
}

void ftKb_SpecialAirLwStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    Fighter* fp2;
    Fighter* fp3;
    s32 temp;
    f32 angle;
    struct ftKb_Init_803CB490_layout* p =
        (struct ftKb_Init_803CB490_layout*) ftKb_Init_803CB490;
    PAD_STACK(16);

    if (ft_80081D0C(gobj) == GA_Air) {
        ftKb_SpecialHi_800F3570(gobj);
        ftKb_SpecialHi_800F37EC(gobj);
        fp->self_vel.y = 0.0f;
        ftCommon_8007D7FC(fp);
        temp = fp->x221C_b4;
        Fighter_ChangeMotionState(gobj, 0x189, 0x0C4C5092U, fp->cur_anim_frame,
                                  1.0f, 0.0f, NULL);
        fp->x221C_b4 = temp;
        fp2 = GET_FIGHTER(gobj);
        fp2->take_dmg_cb = ftKb_Init_800EE7B8;
        fp2->death2_cb = ftKb_Init_800EE74C;
        ft_PlaySFX(fp, 0x222E7, 0x7F, 0x40);
        Camera_80030E44(4, &fp->cur_pos);
        ftCommon_8007EBAC(fp, 0xE, 0x14);
        fp3 = GET_FIGHTER(gobj);
        angle = fp->mv.kb.specialhi.xC4;
        fp3->mv.kb.speciallw.x54.x = fp3->mv.kb.speciallw.x24.x =
            fp->mv.kb.speciallw.x18.x;
        fp3->mv.kb.speciallw.x54.y = fp3->mv.kb.speciallw.x24.y =
            fp->mv.kb.speciallw.x18.y;
        fp3->mv.kb.speciallw.x54.z = fp3->mv.kb.speciallw.x24.z =
            fp->mv.kb.speciallw.x18.z;
        fp3->mv.kb.speciallw.x88[4] = fp3->mv.kb.speciallw.x88[0] = angle;
        fp3->mv.kb.speciallw.x60.x = fp3->mv.kb.speciallw.x30.x =
            fp->mv.kb.speciallw.x18.x;
        fp3->mv.kb.speciallw.x60.y = fp3->mv.kb.speciallw.x30.y =
            fp->mv.kb.speciallw.x18.y;
        fp3->mv.kb.speciallw.x60.z = fp3->mv.kb.speciallw.x30.z =
            fp->mv.kb.speciallw.x18.z;
        fp3->mv.kb.speciallw.x88[5] = fp3->mv.kb.speciallw.x88[1] = angle;
        fp3->mv.kb.speciallw.x6C.x = fp3->mv.kb.speciallw.x3C.x =
            fp->mv.kb.speciallw.x18.x;
        fp3->mv.kb.speciallw.x6C.y = fp3->mv.kb.speciallw.x3C.y =
            fp->mv.kb.speciallw.x18.y;
        fp3->mv.kb.speciallw.x6C.z = fp3->mv.kb.speciallw.x3C.z =
            fp->mv.kb.speciallw.x18.z;
        fp3->mv.kb.speciallw.x88[6] = fp3->mv.kb.speciallw.x88[2] = angle;
        fp3->mv.kb.speciallw.x78.x = fp3->mv.kb.speciallw.x48.x =
            fp->mv.kb.speciallw.x18.x;
        fp3->mv.kb.speciallw.x78.y = fp3->mv.kb.speciallw.x48.y =
            fp->mv.kb.speciallw.x18.y;
        fp3->mv.kb.speciallw.x78.z = fp3->mv.kb.speciallw.x48.z =
            fp->mv.kb.speciallw.x18.z;
        fp3->mv.kb.speciallw.x88[7] = fp3->mv.kb.speciallw.x88[3] = angle;
        fp3->mv.kb.speciallw.x18.x = fp->mv.kb.speciallw.x18.x;
        fp3->mv.kb.speciallw.x18.y = fp->mv.kb.speciallw.x18.y;
        fp3->mv.kb.speciallw.x18.z = fp->mv.kb.speciallw.x18.z;
        fp3->mv.kb.specialhi.xC4 = angle;
        angle = fp->mv.kb.specialhi.xC4;
        if (angle < 0.0f) {
            angle = -angle;
        }
        if (angle >= da->speciallw_min_slant_angle_slide) {
            fp->gr_vel = fp->mv.co.common.x18 * da->speciallw_slide_max_speed;
        }
    } else {
        fp2 = GET_FIGHTER(gobj);
        fp2->mv.kb.speciallw.x24 = p->vec;
        fp2->mv.kb.speciallw.x54 = fp2->mv.kb.speciallw.x24;
        fp2->mv.kb.speciallw.x88[0] = 0.0f;
        fp2->mv.kb.speciallw.x88[4] = 0.0f;
        fp2->mv.kb.speciallw.x30 = p->vec;
        fp2->mv.kb.speciallw.x60 = fp2->mv.kb.speciallw.x30;
        fp2->mv.kb.speciallw.x88[1] = 0.0f;
        fp2->mv.kb.speciallw.x88[5] = 0.0f;
        fp2->mv.kb.speciallw.x3C = p->vec;
        fp2->mv.kb.speciallw.x6C = fp2->mv.kb.speciallw.x3C;
        fp2->mv.kb.speciallw.x88[2] = 0.0f;
        fp2->mv.kb.speciallw.x88[6] = 0.0f;
        fp2->mv.kb.speciallw.x48 = p->vec;
        fp2->mv.kb.speciallw.x78 = fp2->mv.kb.speciallw.x48;
        fp2->mv.kb.speciallw.x88[3] = 0.0f;
        fp2->mv.kb.speciallw.x88[7] = 0.0f;
        fp2->mv.kb.speciallw.x18 = p->vec;
        fp2->mv.kb.speciallw.x84 = 0.0f;
        ftPartSetRotX(fp, 0, 0.0f);
    }
}

void ftKb_SpecialAirLw_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    Fighter* fp2;
    Fighter* fp3;
    s32 temp;
    f32 angle;
    struct ftKb_Init_803CB490_layout* p =
        (struct ftKb_Init_803CB490_layout*) ftKb_Init_803CB490;
    PAD_STACK(16);

    if (ft_80081D0C(gobj) == GA_Air) {
        ftKb_SpecialHi_800F3570(gobj);
        ftKb_SpecialHi_800F37EC(gobj);
        fp->self_vel.y = 0.0f;
        ftCommon_8007D7FC(fp);
        temp = fp->x221C_b4;
        Fighter_ChangeMotionState(gobj, 0x18A, 0x0C4C5092U, 0.0f, 0.0f, 0.0f,
                                  NULL);
        fp->x221C_b4 = temp;
        ftAnim_SetAnimRate(gobj, 0.0f);
        fp2 = GET_FIGHTER(gobj);
        fp2->take_dmg_cb = ftKb_Init_800EE7B8;
        fp2->death2_cb = ftKb_Init_800EE74C;
        ft_PlaySFX(fp, 0x222E7, 0x7F, 0x40);
        Camera_80030E44(4, &fp->cur_pos);
        ftCommon_8007EBAC(fp, 0xE, 0x14);
        fp3 = GET_FIGHTER(gobj);
        angle = fp->mv.kb.specialhi.xC4;
        fp3->mv.kb.speciallw.x54.x = fp3->mv.kb.speciallw.x24.x =
            fp->mv.kb.speciallw.x18.x;
        fp3->mv.kb.speciallw.x54.y = fp3->mv.kb.speciallw.x24.y =
            fp->mv.kb.speciallw.x18.y;
        fp3->mv.kb.speciallw.x54.z = fp3->mv.kb.speciallw.x24.z =
            fp->mv.kb.speciallw.x18.z;
        fp3->mv.kb.speciallw.x88[4] = fp3->mv.kb.speciallw.x88[0] = angle;
        fp3->mv.kb.speciallw.x60.x = fp3->mv.kb.speciallw.x30.x =
            fp->mv.kb.speciallw.x18.x;
        fp3->mv.kb.speciallw.x60.y = fp3->mv.kb.speciallw.x30.y =
            fp->mv.kb.speciallw.x18.y;
        fp3->mv.kb.speciallw.x60.z = fp3->mv.kb.speciallw.x30.z =
            fp->mv.kb.speciallw.x18.z;
        fp3->mv.kb.speciallw.x88[5] = fp3->mv.kb.speciallw.x88[1] = angle;
        fp3->mv.kb.speciallw.x6C.x = fp3->mv.kb.speciallw.x3C.x =
            fp->mv.kb.speciallw.x18.x;
        fp3->mv.kb.speciallw.x6C.y = fp3->mv.kb.speciallw.x3C.y =
            fp->mv.kb.speciallw.x18.y;
        fp3->mv.kb.speciallw.x6C.z = fp3->mv.kb.speciallw.x3C.z =
            fp->mv.kb.speciallw.x18.z;
        fp3->mv.kb.speciallw.x88[6] = fp3->mv.kb.speciallw.x88[2] = angle;
        fp3->mv.kb.speciallw.x78.x = fp3->mv.kb.speciallw.x48.x =
            fp->mv.kb.speciallw.x18.x;
        fp3->mv.kb.speciallw.x78.y = fp3->mv.kb.speciallw.x48.y =
            fp->mv.kb.speciallw.x18.y;
        fp3->mv.kb.speciallw.x78.z = fp3->mv.kb.speciallw.x48.z =
            fp->mv.kb.speciallw.x18.z;
        fp3->mv.kb.speciallw.x88[7] = fp3->mv.kb.speciallw.x88[3] = angle;
        fp3->mv.kb.speciallw.x18.x = fp->mv.kb.speciallw.x18.x;
        fp3->mv.kb.speciallw.x18.y = fp->mv.kb.speciallw.x18.y;
        fp3->mv.kb.speciallw.x18.z = fp->mv.kb.speciallw.x18.z;
        fp3->mv.kb.specialhi.xC4 = angle;
        angle = fp->mv.kb.specialhi.xC4;
        if (angle < 0.0f) {
            angle = -angle;
        }
        if (angle >= da->speciallw_min_slant_angle_slide) {
            fp->gr_vel = fp->mv.co.common.x18 * da->speciallw_slide_max_speed;
        }
    } else {
        fp2 = GET_FIGHTER(gobj);
        fp2->mv.kb.speciallw.x24 = p->vec;
        fp2->mv.kb.speciallw.x54 = fp2->mv.kb.speciallw.x24;
        fp2->mv.kb.speciallw.x88[0] = 0.0f;
        fp2->mv.kb.speciallw.x88[4] = 0.0f;
        fp2->mv.kb.speciallw.x30 = p->vec;
        fp2->mv.kb.speciallw.x60 = fp2->mv.kb.speciallw.x30;
        fp2->mv.kb.speciallw.x88[1] = 0.0f;
        fp2->mv.kb.speciallw.x88[5] = 0.0f;
        fp2->mv.kb.speciallw.x3C = p->vec;
        fp2->mv.kb.speciallw.x6C = fp2->mv.kb.speciallw.x3C;
        fp2->mv.kb.speciallw.x88[2] = 0.0f;
        fp2->mv.kb.speciallw.x88[6] = 0.0f;
        fp2->mv.kb.speciallw.x48 = p->vec;
        fp2->mv.kb.speciallw.x78 = fp2->mv.kb.speciallw.x48;
        fp2->mv.kb.speciallw.x88[3] = 0.0f;
        fp2->mv.kb.speciallw.x88[7] = 0.0f;
        fp2->mv.kb.speciallw.x18 = p->vec;
        fp2->mv.kb.speciallw.x84 = 0.0f;
        ftPartSetRotX(fp, 0, 0.0f);
    }
}

void ftKb_SpecialAirLwEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* fp2;
    struct ftKb_Init_803CB490_layout* p =
        (struct ftKb_Init_803CB490_layout*) ftKb_Init_803CB490;
    PAD_STACK(8);
    ft_80081D0C(gobj);
    fp2 = GET_FIGHTER(gobj);
    fp2->mv.kb.speciallw.x24 = p->vec;
    fp2->mv.kb.speciallw.x54 = fp2->mv.kb.speciallw.x24;
    fp2->mv.kb.speciallw.x88[0] = 0.0f;
    fp2->mv.kb.speciallw.x88[4] = 0.0f;
    fp2->mv.kb.speciallw.x30 = p->vec;
    fp2->mv.kb.speciallw.x60 = fp2->mv.kb.speciallw.x30;
    fp2->mv.kb.speciallw.x88[1] = 0.0f;
    fp2->mv.kb.speciallw.x88[5] = 0.0f;
    fp2->mv.kb.speciallw.x3C = p->vec;
    fp2->mv.kb.speciallw.x6C = fp2->mv.kb.speciallw.x3C;
    fp2->mv.kb.speciallw.x88[2] = 0.0f;
    fp2->mv.kb.speciallw.x88[6] = 0.0f;
    fp2->mv.kb.speciallw.x48 = p->vec;
    fp2->mv.kb.speciallw.x78 = fp2->mv.kb.speciallw.x48;
    fp2->mv.kb.speciallw.x88[3] = 0.0f;
    fp2->mv.kb.speciallw.x88[7] = 0.0f;
    fp2->mv.kb.speciallw.x18 = p->vec;
    fp2->mv.kb.speciallw.x84 = 0.0f;
    ftPartSetRotX(fp, 0, 0.0f);
}

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

static inline void fn_800F53AC_SpawnEffect(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 ef_id;
    if (fp->ground_or_air == GA_Air) {
        ef_id = 0x497;
    } else {
        ef_id = 0x496;
    }
    efSync_Spawn(ef_id, gobj, fp->parts[FtPart_HipN].joint, &fp->facing_dir);
    fp->x2219_b0 = true;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

static inline void fn_800F53AC_CleanupItem(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Item_GObj* item = fp->fv.kb.hat.x0;
    if (item != NULL) {
        it_802ADC34(item);
        fp->fv.kb.hat.x0 = NULL;
    }
}

void fn_800F53AC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;

    if (fp->cmd_vars[0] == 1) {
        f32 dir;
        lb_8000B1CC(fp->parts[FtPart_R3rdNa].joint, NULL, &pos);
        dir = fp->facing_dir;
        fp->fv.kb.hat.x0 =
            it_802ADC54(gobj, &pos, FtPart_R3rdNa, fp->ground_or_air, dir);
        fp->x1984_heldItemSpec = fp->fv.kb.hat.x0;
        fp->cmd_vars[0] = 0;
        if (fp->fv.kb.hat.x0 != NULL) {
            if (fp->death2_cb != NULL && fp->death2_cb != ftKb_Init_800EE74C) {
                HSD_ASSERTREPORT(0x66, 0, ftKb_Init_803CB510);
            }
            fp->death2_cb = ftKb_Init_800EE74C;
            fp->take_dmg_cb = ftKb_Init_800EE7B8;
            fn_800F53AC_SpawnEffect(gobj);
        }
    }
    if (fp->cmd_vars[0] == 2) {
        fn_800F53AC_CleanupItem(gobj);
        fp->cmd_vars[0] = 0;
    }
}

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

void ftKb_SpecialAirS_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    fp->cmd_vars[0] = 0;
    if (!fp->fv.kb.x64) {
        fp->self_vel.y = da->specials_aerial_vertical_momentum;
        fp->fv.kb.x64 = true;
    }
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirS, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = &fn_800F53AC;
}

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
    if (ft_80081D0C(gobj)) {
        Fighter* fp2 = GET_FIGHTER(gobj);
        if (fp2->fv.kb.hat.x0 != NULL) {
            it_802ADC34(fp2->fv.kb.hat.x0);
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

HSD_Joint* ftKb_SpecialN_800F5898(Fighter_GObj* gobj)
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
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    float cos_val = cosf(da->specialn_spit_out_release_angle);
    float temp = da->specialn_swallow_star_vertical_velocity * cos_val;

    victim_self_vel->x = victim_facing_dir * temp;
    victim_self_vel->y = da->specialn_swallow_star_vertical_velocity *
                         sinf(da->specialn_spit_out_release_angle);
    victim_self_vel->z = 0.0f;

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
        ftKb_SpecialS_800F6BB0(gobj);
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

/// #ftKb_SpecialN_800F5B5C

/// #ftKb_SpecialN_800F5BA4

/// #ftKb_SpecialN_800F5C34

/// #ftKb_SpecialN_800F5D04

/// #ftKb_SpecialN_800F5DE8

/// #ftKb_SpecialN_800F5EA8

/// #ftKb_SpecialN_800F5F68

/// #ftKb_SpecialN_800F6070

/// #fn_800F6178

/// #fn_800F6210

/// #fn_800F6280

/// #fn_800F6318

/// #ftKb_SpecialN_800F6388

/// #ftKb_SpecialN_800F63EC

/// #fn_800F6450

/// #fn_800F64C8

/// #fn_800F6528

/// #fn_800F6588

/// #fn_800F6638

/// #fn_800F66E8

/// #fn_800F6798

/// #fn_800F6848

/// #fn_800F68A8

/// #fn_800F6908

/// #fn_800F697C

/// #fn_800F69E8

/// #fn_800F6A5C

/// #fn_800F6AC8

/// #fn_800F6B3C

/// #ftKb_SpecialS_800F6BB0

/// #fn_800F6C24

/// #fn_800F6C98

/// #fn_800F6D0C

/// #fn_800F6D80

/// #fn_800F6DF4

/// #fn_800F6E68

/// #fn_800F6EDC

/// #fn_800F6F50

/// #fn_800F6FC4

/// #fn_800F702C

/// #ftKb_SpecialN_Anim

/// #ftKb_SpecialAirN_Anim

void ftKb_SpecialNLoop_Anim(Fighter_GObj* gobj) {}

void ftKb_SpecialAirNLoop_Anim(Fighter_GObj* gobj) {}

/// #ftKb_SpecialNEnd_Anim

/// #ftKb_SpecialAirNEnd_Anim

/// #ftKb_SpecialNCapture0_Anim

/// #ftKb_SpecialNCapture_Anim

/// #ftKb_SpecialNCapture1_Anim

/// #ftKb_SpecialAirNCapture_Anim

/// #ftKb_Eat_Anim

/// #ftKb_SpecialAirNCaptured_Anim

void ftKb_EatWait_Anim(Fighter_GObj* gobj) {}

void ftKb_SpecialAirNCaptureWait_Anim(Fighter_GObj* gobj) {}

/// #ftKb_SpecialNSpit0_Anim

/// #ftKb_SpecialNSpit_Anim

/// #ftKb_SpecialNSpit1_Anim

/// #ftKb_SpecialAirNSpit_Anim

/// #ftKb_SpecialNDrink0_Anim

/// #ftKb_SpecialNDrink_Anim

/// #ftKb_SpecialNDrink1_Anim

/// #ftKb_SpecialAirNDrink_Anim

/// #ftKb_EatTurn_Anim

/// #ftKb_SpecialAirNCaptureTurn_Anim

/// #ftKb_EatWalk_Anim

/// #ftKb_EatJump1_Anim

void ftKb_EatJump2_Anim(Fighter_GObj* gobj) {}

/// #ftKb_EatLanding_Anim

/// #ftKb_SpecialNLoop_IASA

/// #ftKb_SpecialAirNLoop_IASA

/// #ftKb_EatWait_IASA

/// #ftKb_SpecialAirNCaptureWait_IASA

/// #ftKb_EatWalk_IASA

/// #ftKb_EatJump1_IASA

/// #ftKb_SpecialN_Phys

/// #ftKb_SpecialAirN_Phys

/// #ftKb_SpecialNLoop_Phys

/// #ftKb_SpecialAirNLoop_Phys

/// #ftKb_SpecialNEnd_Phys

/// #ftKb_SpecialAirNEnd_Phys

/// #ftKb_SpecialNCapture0_Phys

/// #ftKb_SpecialNCapture_Phys

/// #ftKb_SpecialNCapture1_Phys

/// #ftKb_SpecialAirNCapture_Phys

/// #ftKb_Eat_Phys

/// #ftKb_SpecialAirNCaptured_Phys

/// #ftKb_EatWait_Phys

/// #ftKb_SpecialAirNCaptureWait_Phys

/// #ftKb_SpecialNSpit0_Phys

/// #ftKb_SpecialNSpit_Phys

/// #ftKb_SpecialNSpit1_Phys

/// #ftKb_SpecialAirNSpit_Phys

/// #ftKb_SpecialNDrink0_Phys

/// #ftKb_SpecialNDrink_Phys

/// #ftKb_SpecialNDrink1_Phys

/// #ftKb_SpecialAirNDrink_Phys

/// #ftKb_EatTurn_Phys

/// #ftKb_SpecialAirNCaptureTurn_Phys

/// #ftKb_EatWalk_Phys

/// #ftKb_EatJump1_Phys

/// #ftKb_EatJump2_Phys

/// #ftKb_EatLanding_Phys

/// #ftKb_SpecialN_Coll

/// #ftKb_SpecialAirN_Coll

/// #ftKb_SpecialNLoop_Coll

/// #ftKb_SpecialAirNLoop_Coll

/// #ftKb_SpecialNEnd_Coll

/// #ftKb_SpecialAirNEnd_Coll

/// #ftKb_SpecialNCapture0_Coll

/// #ftKb_SpecialNCapture_Coll

/// #ftKb_SpecialNCapture1_Coll

/// #ftKb_SpecialAirNCapture_Coll

/// #ftKb_Eat_Coll

/// #ftKb_SpecialAirNCaptured_Coll

/// #ftKb_EatWait_Coll

/// #ftKb_SpecialAirNCaptureWait_Coll

/// #ftKb_SpecialNSpit0_Coll

/// #ftKb_SpecialNSpit_Coll

/// #ftKb_SpecialNSpit1_Coll

/// #ftKb_SpecialAirNSpit_Coll

/// #ftKb_SpecialNDrink0_Coll

/// #ftKb_SpecialNDrink_Coll

/// #ftKb_SpecialNDrink1_Coll

/// #ftKb_SpecialAirNDrink_Coll

/// #ftKb_EatTurn_Coll

/// #ftKb_SpecialAirNCaptureTurn_Coll

/// #ftKb_EatWalk_Coll

/// #ftKb_EatJump1_Coll

/// #ftKb_EatJump2_Coll

/// #ftKb_EatLanding_Coll

/// #ftKb_SpecialN_800F9070

/// #ftKb_SpecialN_800F9090

/// #ftKb_SpecialN_800F9110

/// #ftKb_MrSpecialN_Anim

/// #ftKb_MrSpecialN_IASA

/// #ftKb_MrSpecialN_Phys

/// #ftKb_MrSpecialN_Coll

/// #fn_800F9260

/// #ftKb_SpecialNMr_800F93CC

/// #ftKb_MrSpecialAirN_Anim

/// #ftKb_MrSpecialAirN_IASA

/// #ftKb_MrSpecialAirN_Phys

/// #ftKb_MrSpecialAirN_Coll

/// #ftKb_SpecialNLg_800F951C

/// #ftKb_SpecialNLg_800F9598

/// #ftKb_SpecialNLg_800F9614

/// #ftKb_SpecialNLg_800F9684

/// #ftKb_LgSpecialN_Anim

/// #ftKb_LgSpecialAirN_Anim

/// #ftKb_LgSpecialN_IASA

/// #ftKb_LgSpecialAirN_IASA

/// #ftKb_LgSpecialN_Phys

/// #ftKb_LgSpecialAirN_Phys

/// #ftKb_LgSpecialN_Coll

/// #ftKb_LgSpecialAirN_Coll

/// #fn_800F98F4

/// #ftKb_SpecialNCa_800F99BC

/// #ftKb_SpecialNCa_800F9A54

/// #ftKb_CaSpecialN_Anim

/// #ftKb_CaSpecialAirN_Anim

/// #ftKb_CaSpecialN_IASA

/// #ftKb_CaSpecialAirN_IASA

/// #ftKb_CaSpecialN_Phys

/// #ftKb_CaSpecialAirN_Phys

/// #ftKb_CaSpecialN_Coll

/// #ftKb_CaSpecialAirN_Coll

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
        (s32) fp->fv.kb.hat.kind != FTKIND_KIRBY && !fp->fv.kb.hat.x8_b0 &&
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
        (s32) fp->fv.kb.hat.kind != FTKIND_KIRBY && !fp->fv.kb.hat.x8_b0 &&
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
    Vec3 vel;
    Vec3 pos;
    Fighter* new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da;
    PAD_STACK(8);
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

void ftKb_SpecialN_800F5DE8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    Vec3 pos = fp->cur_pos;
    PAD_STACK(20);

    pos.x += da->specialn_x_offset_inhaled * fp->facing_dir;
    pos.y += da->specialn_y_offset_inhaled;
    if (it_802F23AC(fp->target_item_gobj, &pos) <
        da->specialn_inhale_velocity * da->specialn_inhale_velocity)
    {
        it_802F2810(fp->target_item_gobj);
        if (fp->ground_or_air == GA_Air) {
            ftKb_SpecialN_800F63EC(gobj);
        } else {
            ftKb_SpecialN_800F6388(gobj);
        }
    }
}

void ftKb_SpecialN_800F5EA8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    Vec3 pos = fp->cur_pos;
    PAD_STACK(20);

    pos.x += da->specialn_x_offset_inhaled * fp->facing_dir;
    pos.y += da->specialn_y_offset_inhaled;
    if (ftCo_800BD19C(fp->victim_gobj, &pos) <
        da->specialn_inhale_velocity * da->specialn_inhale_velocity)
    {
        ftCo_800BD620(fp->victim_gobj);
        if (fp->ground_or_air == GA_Air) {
            ftKb_SpecialN_800F63EC(gobj);
        } else {
            ftKb_SpecialN_800F6388(gobj);
        }
    }
}

void ftKb_SpecialN_800F5F68(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4 * 12);

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
    PAD_STACK(4 * 12);

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
    Fighter_ChangeMotionState(gobj, ftKb_MS_Eat, 0x10, 0.0F, 1.0F, 0.0F, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftKb_SpecialN_800F63EC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_EatAir, 0x10, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftKb_SpecialN_800F9070(gobj);
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

void fn_800F64C8(Fighter_GObj* gobj, float anim_start)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* ca = getFtAttrs(fp);
    ftKb_DatAttrs* da = fp->dat_attrs;
    ftWalkCommon_800DFCA4(gobj, ftKb_MS_EatWalkSlow, Ft_MF_SkipModel,
                          anim_start, fp->fv.kb.xE8, fp->fv.kb.xEC,
                          fp->fv.kb.xF0, ca->slow_walk_max, ca->mid_walk_point,
                          ca->fast_walk_min, da->specialn_walk_speed);
    ftCommon_8007E2F4(fp, 0x1FF);
}

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
    void* new_var2;
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* new_var;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirN, 0x0C4C529A,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    new_var = fp;
    new_var->pre_hitlag_cb = efLib_PauseAll;
    new_var->post_hitlag_cb = efLib_ResumeAll;
    new_var2 = HSD_GObjGetUserData(gobj);
    fp = (Fighter*) new_var2;
    ftCommon_8007E2D0(fp, 0x10, fn_800F6318, fn_800F6280, ftCo_800BD1DC);
    fp->x2225_b1 = true;
}

void fn_800F6638(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void* new_var;
    void (*new_var2)(Fighter_GObj* gobj, Fighter_GObj* victim_gobj);
    new_var2 = ftCo_800BD1DC;
    ftCommon_8007D7FC(fp);
    if (new_var2) {
    }
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialN, 0x0C4C529A,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    new_var = HSD_GObjGetUserData(gobj);
    fp = (Fighter*) new_var;
    ftCommon_8007E2D0(fp, 0x10, fn_800F6210, fn_800F6178, ftCo_800BD1DC);
    fp->x2225_b1 = true;
}

void fn_800F66E8(HSD_GObj* gobj)
{
    void (*new_var2)(HSD_GObj* gobj);
    Fighter* fp = (Fighter*) HSD_GObjGetUserData(gobj);
    void (*new_var)(HSD_GObj* gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirNLoop, 0x0C4C5A9A,
                              fp->cur_anim_frame, 1.0f, 0.0f, 0L);
    new_var = efLib_PauseAll;
    new_var2 = efLib_ResumeAll;
    fp->pre_hitlag_cb = new_var;
    fp->post_hitlag_cb = new_var2;
    fp = (Fighter*) HSD_GObjGetUserData(gobj);
    ftCommon_8007E2D0(fp, 0x10, fn_800F6318, fn_800F6280, ftCo_800BD1DC);
    fp->x2225_b1 = 1;
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
    fp = HSD_GObjGetUserData(gobj);
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
    /// @todo Named flags.
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

static inline void ftKb_SpecialN_SetHitlagCb(Fighter_GObj* gobj, s32 ms,
                                             MotionFlags mf)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ms, mf, 0.0f, 1.0f, 0.0f, NULL);
    fp->x2222_b2 = true;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

static inline void
ftKb_SpecialN_SetThrowCb(Fighter_GObj* gobj, s32 mask,
                         HSD_GObjEvent capture_cb, HSD_GObjEvent release_cb,
                         void (*throw_cb)(HSD_GObj*, HSD_GObj*))
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007E2D0(fp, mask, capture_cb, release_cb, throw_cb);
    fp->x2225_b1 = true;
}

void ftKb_SpecialN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* joint = fp->parts[FtPart_YRotN].joint;
    PAD_STACK(16);

    if (fp->cmd_vars[0] != 0) {
        efAsync_Spawn(gobj, &fp->x60C, 3, 0x49A, joint, &fp->facing_dir);
        fp->x2219_b0 = true;
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKb_SpecialN_SetHitlagCb(gobj, 0x162, 0x212);
        ftKb_SpecialN_SetThrowCb(gobj, 0x10, fn_800F6210, fn_800F6178,
                                 ftCo_800BD1DC);
    }
}

void ftKb_SpecialAirN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* joint = fp->parts[FtPart_YRotN].joint;
    PAD_STACK(16);

    if (fp->cmd_vars[0] != 0) {
        efAsync_Spawn(gobj, &fp->x60C, 3, 0x49A, joint, &fp->facing_dir);
        fp->x2219_b0 = true;
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKb_SpecialN_SetHitlagCb(gobj, 0x174, 0x212);
        ftKb_SpecialN_SetThrowCb(gobj, 0x10, fn_800F6318, fn_800F6280,
                                 ftCo_800BD1DC);
    }
}

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

static inline void ftKb_SpecialNCapture_EnterState(Fighter_GObj* gobj, s32 ms)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ms, 0x10, 0.0f, 1.0f, 0.0f, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftKb_SpecialNCapture0_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    Vec3 pos = fp->cur_pos;
    u8 _pad[32];

    pos.x += da->specialn_x_offset_inhaled * fp->facing_dir;
    pos.y += da->specialn_y_offset_inhaled;
    if (it_802F23AC(fp->target_item_gobj, &pos) <
        SQ(da->specialn_inhale_velocity))
    {
        it_802F2810(fp->target_item_gobj);
        if (fp->ground_or_air == GA_Air) {
            ftKb_SpecialNCapture_EnterState(gobj, 0x178);
        } else {
            ftKb_SpecialNCapture_EnterState(gobj, 0x166);
        }
        fp->facing_dir = fp->facing_dir; // fake match, via permuter
    }
}

void ftKb_SpecialNCapture_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    Vec3 pos = fp->cur_pos;
    u8 _pad[32];

    pos.x += da->specialn_x_offset_inhaled * fp->facing_dir;
    pos.y += da->specialn_y_offset_inhaled;
    if (ftCo_800BD19C(fp->victim_gobj, &pos) <
        SQ(da->specialn_inhale_velocity))
    {
        ftCo_800BD620(fp->victim_gobj);
        if (fp->ground_or_air == GA_Air) {
            ftKb_SpecialNCapture_EnterState(gobj, 0x178);
        } else {
            ftKb_SpecialNCapture_EnterState(gobj, 0x166);
        }
        fp->facing_dir = fp->facing_dir; // fake match, via permuter
    }
}

#pragma dont_inline on
void ftKb_SpecialNCapture1_Anim(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800F5DE8(gobj);
}

void ftKb_SpecialAirNCapture_Anim(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800F5EA8(gobj);
}
#pragma dont_inline off

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
        Fighter* fp = (0, GET_FIGHTER(gobj));
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_EatFall, 0x90, 0.0f, 1.0f,
                                  0.0f, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

static inline void ftKb_SpecialNSpit_Anim_inline(Fighter_GObj* gobj,
                                                 Fighter_GObj* victim)
{
    if (victim != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter* victim_fp = victim->user_data;
        ftCommon_8007E2F4(fp, 0);
        ftCo_800DE2CC(gobj, victim);
        ftCo_800BDB58(victim, gobj);
        ftColl_8007B8CC(victim_fp, gobj);
        fp->cmd_vars[0] = 0;
    }
}

void ftKb_SpecialNSpit0_Anim(Fighter_GObj* gobj)
{
    UNUSED u32 unused1;
    Fighter* fp = getFighter(gobj);
    Item_GObj* item_gobj;
    ftKb_DatAttrs* da;
    struct itUnk2_DatAttrs attr;
    PAD_STACK(0x40);

    if (fp->cmd_vars[0] != 0 && (item_gobj = fp->target_item_gobj) != NULL) {
        ftCommon_8007E2F4(fp, 0);
        lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN2)].joint,
                    NULL, &attr.pos);
        {
            f32 neg_facing = -fp->facing_dir;
            da = getFighter(gobj)->dat_attrs;
            attr.vel.x = -neg_facing *
                         da->specialn_ground_spit_initial_horizontal_velocity;
            attr.vel.z = 0.0f;
            attr.vel.y = 0.0f;
            attr.float2 = da->specialn_spit_deceleration_rate;
            attr.float1 = ((ftKb_DatAttrs*) getFighter(gobj)->dat_attrs)
                              ->specialn_star_base_duration;
            it_802F28C8(item_gobj, 0, it_802F295C(gobj, &attr));
        }
        fp->x1A64 = NULL;
        fp->target_item_gobj = NULL;
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_SpecialNSpit_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(16);

    if (fp->cmd_vars[0] != 0) {
        ftKb_SpecialNSpit_Anim_inline(gobj, fp->victim_gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_SpecialAirNSpit_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(16);

    if (fp->cmd_vars[0] != 0) {
        ftKb_SpecialNSpit_Anim_inline(gobj, fp->victim_gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_SpecialNSpit1_Anim(Fighter_GObj* gobj)
{
    UNUSED u32 unused1;
    Fighter* fp = getFighter(gobj);
    Item_GObj* item_gobj;
    ftKb_DatAttrs* da;
    itUnk2_DatAttrs attr;
    PAD_STACK(0x40);

    if (fp->cmd_vars[0] != 0 && (item_gobj = fp->target_item_gobj) != NULL) {
        ftCommon_8007E2F4(fp, 0);
        lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN2)].joint,
                    NULL, &attr.pos);
        {
            f32 neg_facing = -fp->facing_dir;
            da = getFighter(gobj)->dat_attrs;
            attr.vel.x = -neg_facing *
                         da->specialn_ground_spit_initial_horizontal_velocity;
            attr.vel.z = 0.0f;
            attr.vel.y = 0.0f;
            attr.float2 = da->specialn_spit_deceleration_rate;
            attr.float1 = ((ftKb_DatAttrs*) getFighter(gobj)->dat_attrs)
                              ->specialn_star_base_duration;
            it_802F28C8(item_gobj, 0, it_802F295C(gobj, &attr));
        }
        fp->x1A64 = NULL;
        fp->target_item_gobj = NULL;
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_SpecialNDrink0_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    Item_GObj* item_gobj;
    PAD_STACK(16);
    if (fp->cmd_vars[0] != 0 && (item_gobj = fp->target_item_gobj) != NULL) {
        ftCommon_8007E2F4(fp, 0);
        ft_PlaySFX(fp, 0x222F6, 0x7F, 0x40);
        it_802F28C8(item_gobj, 0, 0.0F);
        fp->x1A64 = NULL;
        fp->target_item_gobj = NULL;
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

static inline void ftKb_SpecialNDrink_Anim_inline(Fighter_GObj* gobj,
                                                  Fighter_GObj* victim_gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.kb.xE0 = ftCo_800BD9E0(gobj, victim_gobj);
    ftKb_SpecialN_800F1BAC(gobj, fp->fv.kb.xE0, true);
}

void ftKb_SpecialNDrink_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    u8 _pad[24];
    if (fp->cmd_vars[0] != 0) {
        Fighter_GObj* victim_gobj;
        if ((victim_gobj = fp->victim_gobj) != NULL) {
            Fighter* new_fp = fp;
            ftCommon_8007E2F4(new_fp, 0);
            ftCo_800DE2CC(gobj, victim_gobj);
            ftCo_800BE000(victim_gobj, gobj);
            ftKb_SpecialNDrink_Anim_inline(gobj, victim_gobj);
            fp->cmd_vars[0] = 0;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_SpecialNDrink1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    Item_GObj* item_gobj;
    PAD_STACK(16);
    if (fp->cmd_vars[0] != 0 && (item_gobj = fp->target_item_gobj) != NULL) {
        ftCommon_8007E2F4(fp, 0);
        ft_PlaySFX(fp, 0x222F6, 0x7F, 0x40);
        it_802F28C8(item_gobj, 0, 0.0F);
        fp->x1A64 = NULL;
        fp->target_item_gobj = NULL;
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_SpecialAirNDrink_Anim(Fighter_GObj* gobj)
{
    Fighter* fp2;
    Fighter_GObj* victim_gobj;
    Fighter* fp = getFighter(gobj);
    Fighter* new_var;
    if (fp->cmd_vars[0] != 0) {
        if ((victim_gobj = fp->victim_gobj) != NULL) {
            new_var = fp;
            ftCommon_8007E2F4(new_var, 0);
            ftCo_800DE2CC(gobj, victim_gobj);
            ftCo_800BE000(victim_gobj, gobj);
            fp2 = getFighter(gobj);
            fp2->fv.kb.xE0 = ftCo_800BD9E0(gobj, victim_gobj);
            ftKb_SpecialN_800F1BAC(gobj, fp2->fv.kb.xE0, true);
            fp->cmd_vars[0] = 0;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
    PAD_STACK(32);
}

void ftKb_EatTurn_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->facing_dir = -fp->facing_dir;
        fp = GET_FIGHTER(gobj);
        Fighter_ChangeMotionState(gobj, ftKb_MS_EatWait, Ft_MF_SkipModel, 0.0f,
                                  1.0f, 0.0f, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
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

void ftKb_EatJump1_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftKb_DatAttrs* da = fp->dat_attrs;
        PAD_STACK(24);
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_EatJump2, 0x92, 0.0f, 1.0f,
                                  0.0f, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCo_800CB110(gobj, true, da->specialn_jump_height);
    }
}

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

void ftKb_SpecialNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.kb.xE4 != 0) {
        fp->fv.kb.xE4--;
        return;
    }

    if ((fp->input.held_inputs & 0x200) == 0) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialNEnd, 0, 0.0f, 1.0f,
                                  0.0f, NULL);
    }
}

void ftKb_SpecialAirNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.kb.xE4 != 0) {
        fp->fv.kb.xE4--;
        return;
    }

    if ((fp->input.held_inputs & 0x200) == 0) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirNEnd, 0, 0.0f, 1.0f,
                                  0.0f, NULL);
    }
}

void ftKb_EatWait_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    Fighter* fp2;
    enum ftCo_JumpInput jump;
    f32 stickX;
    volatile f32 absX;
    s32 r29;
    s32 r29_2;
    s32 r29_3;
    s32 r29_4;
    s32 r0;
    s32 r0_2;
    PAD_STACK(0x70);

    if (fp->fv.kb.xF4_b0) {
        if (((fp->input.x668 & 0x200) && fp->target_item_gobj != NULL) ||
            ((fp->input.lstick.y <
              -((ftKb_DatAttrs*) fp->dat_attrs)->specialn_y_axis_range_jump) &&
             fp->target_item_gobj != NULL))
        {
            Fighter_ChangeMotionState(gobj, 0x170, 2, 0.0f, 1.0f, 0.0f, NULL);
            r29 = 1;
            fp->x2222_b2 = r29;
            ftKb_SpecialN_800F9070(gobj);
            ftAnim_8006EBA4(gobj);
            ftCommon_8007E2F4(fp, 0x1FF);
        } else {
            r29 = 0;
        }
        if (r29 == 0) {
            fp2 = GET_FIGHTER(gobj);
            if ((fp2->input.x668 & 0x100) && fp2->target_item_gobj != NULL) {
                Fighter_ChangeMotionState(gobj, 0x172, 0x12, 0.0f, 1.0f, 0.0f,
                                          NULL);
                r29_2 = 1;
                fp2->x2222_b2 = r29_2;
                ftKb_SpecialN_800F9070(gobj);
                ftAnim_8006EBA4(gobj);
                ftCommon_8007E2F4(fp2, 0x1FF);
            } else {
                r29_2 = 0;
            }
            if (r29_2 != 0) {
                return;
            }
            goto block_26;
        }
    } else {
        if (((fp->input.x668 & 0x200) && fp->victim_gobj != NULL) ||
            ((fp->input.lstick.y <
              -((ftKb_DatAttrs*) fp->dat_attrs)->specialn_y_axis_range_jump) &&
             fp->victim_gobj != NULL))
        {
            Fighter_ChangeMotionState(gobj, 0x16F, 2, 0.0f, 1.0f, 0.0f, NULL);
            r29_3 = 1;
            fp->x2222_b2 = r29_3;
            ftKb_SpecialN_800F9070(gobj);
            ftAnim_8006EBA4(gobj);
            ftCommon_8007E2F4(fp, 0x1FF);
        } else {
            r29_3 = 0;
        }
        if (r29_3 == 0) {
            fp2 = GET_FIGHTER(gobj);
            if ((fp2->input.x668 & 0x100) && fp2->victim_gobj != NULL) {
                Fighter_ChangeMotionState(gobj, 0x171, 0x12, 0.0f, 1.0f, 0.0f,
                                          NULL);
                r29_4 = 1;
                fp2->x2222_b2 = r29_4;
                ftKb_SpecialN_800F9070(gobj);
                ftAnim_8006EBA4(gobj);
                ftCommon_8007E2F4(fp2, 0x1FF);
            } else {
                r29_4 = 0;
            }
            if (r29_4 == 0) {
            block_26:
                fp2 = GET_FIGHTER(gobj);
                stickX = fp2->input.lstick.x;
                (void) stickX;
                absX = ABS(stickX);
                if (absX < ((ftKb_DatAttrs*) fp2->dat_attrs)
                               ->specialn_x_axis_range_walk)
                {
                    stickX = 0.0f;
                }
                if (((stickX < 0.0f) && (fp2->facing_dir == 1.0f)) ||
                    ((stickX > 0.0f) && (fp2->facing_dir == -1.0f)))
                {
                    Fighter_ChangeMotionState(gobj, 0x16B, 0x92, 0.0f, 1.0f,
                                              0.0f, NULL);
                    ftKb_SpecialN_800F9070(gobj);
                    ftAnim_8006EBA4(gobj);
                    ftCommon_8007E2F4(fp2, 0x1FF);
                    r0 = 1;
                } else {
                    r0 = 0;
                }
                if (r0 == 0) {
                    jump = ftCo_Jump_GetInput(gobj);
                    if (jump != JumpInput_None) {
                        Fighter* fp3 = GET_FIGHTER(gobj);
                        fp3->mv.kb.specialhi.x4 = jump;
                        fp3->mv.kb.specialhi.x0 = 0;
                        Fighter_ChangeMotionState(gobj, 0x16C, 0x92, 0.0f,
                                                  1.0f, 0.0f, NULL);
                        ftKb_SpecialN_800F9070(gobj);
                        ftAnim_8006EBA4(gobj);
                        ftCommon_8007E2F4(fp3, 0x1FF);
                        r0_2 = 1;
                    } else {
                        r0_2 = 0;
                    }
                    if (r0_2 == 0 && ftWalkCommon_800DFC70(gobj)) {
                        Fighter* fp4 = GET_FIGHTER(gobj);
                        ftWalkCommon_800DFCA4(gobj, 0x168, 0x10, 0.0f,
                                              fp4->fv.kb.xE8, fp4->fv.kb.xEC,
                                              fp4->fv.kb.xF0,
                                              fp4->co_attrs.slow_walk_max,
                                              fp4->co_attrs.mid_walk_point,
                                              fp4->co_attrs.fast_walk_min,
                                              ((ftKb_DatAttrs*) fp4->dat_attrs)
                                                  ->specialn_walk_speed);
                        ftCommon_8007E2F4(fp4, 0x1FF);
                    }
                }
            }
        }
    }
}

void ftKb_SpecialAirNCaptureWait_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    Fighter_GObj* gobj2 = gobj;
    Fighter* fp3;
    Fighter* fp2;
    ftKb_DatAttrs* da;
    f32 absX;
    f32 stickX;
    s32 r29;
    s32 r29_2;
    s32 r29_3;
    s32 r29_4;
    s32 r0;
    PAD_STACK(0x50);

    if (fp->fv.kb.xF4_b0) {
        if (((fp->input.x668 & 0x200) && fp->target_item_gobj != NULL) ||
            ((fp->input.lstick.y <
              -((ftKb_DatAttrs*) fp->dat_attrs)->specialn_y_axis_range_jump) &&
             fp->target_item_gobj != NULL))
        {
            Fighter_ChangeMotionState(gobj2, 0x17B, 2, 0.0f, 1.0f, 0.0f, NULL);
            r29 = 1;
            fp->x2222_b2 = r29;
            ftKb_SpecialN_800F9070(gobj2);
            ftAnim_8006EBA4(gobj2);
            ftCommon_8007E2F4(fp, 0x1FF);
        } else {
            r29 = 0;
        }
        if (r29 == 0) {
            fp2 = getFighter(gobj2);
            if ((fp2->input.x668 & 0x100) && fp2->target_item_gobj != NULL) {
                Fighter_ChangeMotionState(gobj2, 0x17D, 0x12, 0.0f, 1.0f, 0.0f,
                                          NULL);
                r29_2 = 1;
                fp2->x2222_b2 = r29_2;
                ftKb_SpecialN_800F9070(gobj2);
                ftAnim_8006EBA4(gobj2);
                ftCommon_8007E2F4(fp2, 0x1FF);
            } else {
                r29_2 = 0;
            }
            if (r29_2 != 0) {
                return;
            }
            goto block_26;
        }
    } else {
        if (((fp->input.x668 & 0x200) && fp->victim_gobj != NULL) ||
            ((fp->input.lstick.y <
              -((ftKb_DatAttrs*) fp->dat_attrs)->specialn_y_axis_range_jump) &&
             fp->victim_gobj != NULL))
        {
            Fighter_ChangeMotionState(gobj2, 0x17A, 2, 0.0f, 1.0f, 0.0f, NULL);
            r29_3 = 1;
            fp->x2222_b2 = r29_3;
            ftKb_SpecialN_800F9070(gobj2);
            ftAnim_8006EBA4(gobj2);
            ftCommon_8007E2F4(fp, 0x1FF);
        } else {
            r29_3 = 0;
        }
        if (r29_3 == 0) {
            fp2 = getFighter(gobj2);
            if ((fp2->input.x668 & 0x100) && fp2->victim_gobj != NULL) {
                Fighter_ChangeMotionState(gobj2, 0x17C, 0x12, 0.0f, 1.0f, 0.0f,
                                          NULL);
                r29_4 = 1;
                fp2->x2222_b2 = r29_4;
                ftKb_SpecialN_800F9070(gobj2);
                ftAnim_8006EBA4(gobj2);
                ftCommon_8007E2F4(fp2, 0x1FF);
            } else {
                r29_4 = 0;
            }
            if (r29_4 == 0) {
            block_26:
                fp3 = getFighter(gobj2);
                stickX = fp3->input.lstick.x;
                (void) stickX;
                da = fp3->dat_attrs;
                if (stickX < 0.0f) {
                    absX = -stickX;
                } else {
                    absX = stickX;
                }
                if (absX < da->specialn_x_axis_range_walk) {
                    stickX = 0.0f;
                }
                if (((stickX < 0.0f) && (fp3->facing_dir == 1.0f)) ||
                    ((stickX > 0.0f) && (fp3->facing_dir == -1.0f)))
                {
                    Fighter_ChangeMotionState(gobj2, 0x17E, 0x92, 0.0f, 1.0f,
                                              0.0f, NULL);
                    ftKb_SpecialN_800F9070(gobj2);
                    ftAnim_8006EBA4(gobj2);
                    ftCommon_8007E2F4(fp3, 0x1FF);
                    r0 = 1;
                } else {
                    r0 = 0;
                }
                if (r0 == 0) {
                    return;
                }
            }
        }
    }
}

void ftKb_EatWalk_IASA(Fighter_GObj* gobj)
{
    ftCo_JumpInput jump_input;
    s32 var;
    PAD_STACK(8);

    jump_input = ftCo_Jump_GetInput(gobj);
    if (jump_input != JumpInput_None) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->mv.kb.specialhi.x4 = jump_input;
        fp->mv.kb.specialhi.x0 = 0;
        Fighter_ChangeMotionState(gobj, ftKb_MS_EatJump1,
                                  Ft_MF_KeepGfx | Ft_MF_SkipModel |
                                      Ft_MF_SkipMatAnim,
                                  0, 1, 0, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
        var = 1;
    } else {
        var = 0;
    }
    if (var == 0) {
        if (ft_8008A1FC(gobj)) {
            Fighter* fp = GET_FIGHTER(gobj);
            Fighter_ChangeMotionState(gobj, ftKb_MS_EatWait, Ft_MF_SkipModel,
                                      0, 1, 0, NULL);
            ftKb_SpecialN_800F9070(gobj);
            ftAnim_8006EBA4(gobj);
            ftCommon_8007E2F4(fp, 0x1FF);
            return;
        }
        ftWalkCommon_800DFEC8(gobj, fn_800F64C8);
    }
}

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
            msid = (new_var = 0x200);
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

static inline void fn_800F9260_DrMario(HSD_GObj* gobj, Fighter* fp, Vec3* pos)
{
    s32 candidates[9];
    s32 count = 0;
    int i;
    s32 pick;
    Fighter* fp2 = GET_FIGHTER(gobj);

    for (i = 0; i < 9; i++) {
        if (i != fp2->fv.kb.x68 && i != fp2->fv.kb.x6C) {
            candidates[count] = i;
            count++;
        }
    }
    pick = candidates[HSD_Randi(count)];
    fp2->fv.kb.x6C = fp2->fv.kb.x68;
    fp2->fv.kb.x68 = pick;
    itDrMarioPill_Spawn(gobj, pos, pick, It_Kind_Kirby_DrMarioVitamin,
                        fp->facing_dir);
}

inline s32 fn_800F9260_inline(HSD_GObj* gobj)
{
    Fighter* fp2;
    s32 candidates[9];
    s32 count;
    s32 i;
    s32 pick;

    fp2 = GET_FIGHTER(gobj);
    for (i = count = 0; i < 9; i++) {
        if (i != fp2->fv.kb.x68 && i != fp2->fv.kb.x6C) {
            candidates[count] = i;
            count++;
        }
    }
    pick = candidates[HSD_Randi(count)];
    fp2->fv.kb.x6C = fp2->fv.kb.x68;
    fp2->fv.kb.x68 = pick;
    return pick;
}

static inline HSD_JObj* fn_800F9260_GetPartJoint(s32 bone, Fighter* fp)
{
    return fp->parts[bone].joint;
}
static inline s32 fn_800F9260_GetLHandBone(Fighter* fp)
{
    return ftParts_GetBoneIndex(fp, FtPart_LHandN);
}
void fn_800F9260(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 found = 0;
    Vec3 sp44;
    s32 bone;
    s32 pick;
    HSD_JObj* joint;

    if (fp->fv.kb.hat.kind != 4) {
        if (fp->throw_flags_b0) {
            fp->throw_flags_b0 = 0;
            found = 1;
        } else {
            found = 0;
        }
        if (found) {
            lb_8000B1CC(
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_LHandN)].joint, NULL,
                &sp44);
            if (fp->fv.kb.hat.kind == FTKIND_MARIO) {
                it_8029B6F8((Item_GObj*) gobj, &sp44, It_Kind_Kirby_MarioFire,
                            fp->facing_dir);
                bone = fn_800F9260_GetLHandBone(fp);
                joint = fn_800F9260_GetPartJoint(bone, fp);
                efSync_Spawn(0x49F, gobj, joint, &fp->facing_dir);
                return;
            }

            pick = fn_800F9260_inline(gobj);

            itDrMarioPill_Spawn((Item_GObj*) gobj, &sp44, pick,
                                It_Kind_Kirby_DrMarioVitamin, fp->facing_dir);
        }
    }
}

void ftKb_SpecialNMr_800F93CC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid = ftKb_MS_MrSpecialAirN;
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

void ftKb_SpecialNLg_800F951C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* fp2;
    s32 motion_id;
    f32 anim_frame;

    ftCommon_8007D5D4(fp);

    fp2 = gobj->user_data;
    motion_id = 0x190;
    anim_frame = fp->cur_anim_frame;

    if (fp2->fv.kb.hat.kind != 0) {
        motion_id = 0x201;
    }

    Fighter_ChangeMotionState(gobj, motion_id, 0x5000, anim_frame, 1.0F, 0.0F,
                              NULL);
    fp->accessory4_cb = fn_800F9260;
}

void ftKb_SpecialNLg_800F9598(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* fp2;
    s32 motion_id;
    f32 anim_frame;

    ftCommon_8007D7FC(fp);

    fp2 = gobj->user_data;
    motion_id = 0x18F;
    anim_frame = fp->cur_anim_frame;

    if (fp2->fv.kb.hat.kind != 0) {
        motion_id = 0x200;
    }

    Fighter_ChangeMotionState(gobj, motion_id, 0x5000, anim_frame, 1.0f, 0.0f,
                              NULL);
    fp->accessory4_cb = fn_800F9260;
}

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

void ftKb_LgSpecialN_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        Fighter* fp = gobj->user_data;
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_LgSpecialAirN, 0x5000,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        fp->accessory4_cb = fn_800F98F4;
    }
}

void ftKb_LgSpecialAirN_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        Fighter* fp = gobj->user_data;
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_LgSpecialN, 0x5000,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        fp->accessory4_cb = fn_800F98F4;
    }
}

void fn_800F98F4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftCheckThrowB0(fp)) {
        Vec3 pos;
        Fighter_Part bone = ftParts_GetBoneIndex(fp, FtPart_LHandN);
        lb_8000B1CC(fp->parts[bone].joint, NULL, &pos);
        it_802C01AC(gobj, &pos, It_Kind_Kirby_LuigiFire, fp->facing_dir);
        efSync_Spawn(0x4B1, gobj,
                     fp->parts[ftParts_GetBoneIndex(fp, FtPart_LHandN)].joint,
                     &fp->facing_dir);
    }
}

void ftKb_SpecialNCa_800F99BC(Fighter_GObj* gobj)
{
    ftKirby_MotionState msid = ftKb_MS_CaSpecialN;
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
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
    PAD_STACK(8);
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
        angle =
            0.017453292f *
            ((range * da2->specialn_ca_angle_difference) /
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
            switch (fp->fv.kb.hat.kind) {
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
            if (fp2->fv.kb.hat.kind != FTKIND_CAPTAIN) {
                msid = ftKb_MS_GnSpecialAirN;
            }
            Fighter_ChangeMotionState(gobj, msid, ftKb_Ca_transition_flags,
                                      anim_frame, 1.0f, 0.0f, NULL);
        }
        fp2->pre_hitlag_cb = efLib_PauseAll;
        fp2->post_hitlag_cb = efLib_ResumeAll;
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
            if (fp2->fv.kb.hat.kind != FTKIND_CAPTAIN) {
                msid = ftKb_MS_GnSpecialN;
            }
            Fighter_ChangeMotionState(gobj, msid, ftKb_Ca_transition_flags,
                                      anim_frame, 1.0f, 0.0f, NULL);
        }
        fp2->pre_hitlag_cb = efLib_PauseAll;
        fp2->post_hitlag_cb = efLib_ResumeAll;
    }
}
