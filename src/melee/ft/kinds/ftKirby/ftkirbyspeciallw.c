#include "ftkirby.h"
#include "types.h"

#include <placeholder.h>

#include "baselib/forward.h"

#include "cm/camera.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_084E.h"
#include "ft/ft_0877.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/kinds/ftCommon/ftCo_FallSpecial.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"

#include "ftKirby/forward.h"

#include "ftKirby/inlines.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"

#include <math.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>

struct ftKb_Init_803CB490_layout {
    char pad[0x74];
    Vec3 vec;
};

struct ftKb_Init_803CB4EC_t {
    int ints[6];
    Vec3 vec;
};

bool ftKb_Init_803CB490[] = {
    false, true,  false, false, false, false, true,  true,
    false, false, false, true,  true,  true,  false, false,
    true,  true,  true,  true,  false, true,  true,
};

struct ftKb_Init_803CB4EC_t ftKb_Init_803CB4EC = {
    { 0, 2, 3, 4, 5, 6 },
    { 0.0F, 1.0F, 0.0F },
};

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
            fp->x221E_b4 = true;
            fp->x2225_b2 = true;
        } else {
            ftParts_80074B0C(
                gobj, 0, ftKb_Init_803CB4EC.ints[fp->mv.kb.specialhi.x10.i]);
            ftParts_80074B0C(gobj, 1, -1);
            ftCommon_8007F5CC(gobj, 0);
            fp->x221E_b4 = false;
            fp->x2225_b2 = false;
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
            fp->u.kb.hat.x4 = fp->mv.kb.specialhi.x10.i =
                ((fp->u.kb.hat.x4 + HSD_Randi(4)) % 5) + new_var;
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
    f32 pos;
    f32 slide_speed;
    f32 pos_x_alias;
    f32 top_y;
    f32 bottom_y;
    f32 floor_normal_x_sign;
    f32 normal_y_slide;
    Fighter* fp = GET_FIGHTER(gobj);
    struct ftKb_Init_803CB490_layout* p =
        (struct ftKb_Init_803CB490_layout*) ftKb_Init_803CB490;
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    {
        UNUSED u8 pad2[12];
    }

    fp->mv.kb.specialhi.x18 = fp->coll_data.floor.normal;
    fp->mv.kb.specialhi.xC4 =
        fp->facing_dir *
        atan2f(fp->mv.kb.specialhi.x18.x, fp->mv.kb.specialhi.x18.y);
    if (0.0f != fp->mv.kb.specialhi.x18.x) {
        pos = fp->cur_pos.y;
        pos_x_alias = fp->cur_pos.x;
        slide_speed = dat_attr->speciallw_slide_max_speed;
        top_y = pos;
        top_y = top_y + slide_speed;
        floor_normal_x_sign = fp->mv.kb.specialhi.x18.x > 0.0f ? 1.0f : -1.0f;
        bottom_y = pos - slide_speed;
        pos = fp->cur_pos.x;
        normal_y_slide = fp->mv.kb.specialhi.x18.y * slide_speed;
        if (mpCheckAllRemap(NULL, 0, NULL, &sp1C, -1, -1, pos, top_y,
                            (normal_y_slide * floor_normal_x_sign) +
                                pos_x_alias,
                            bottom_y) == 0)
        {
            sp1C = p->vec;
        }
        if (fp->mv.kb.specialhi.x18.x > 0.0f) {
            if (sp1C.x < 0.0f) {
                fp->mv.kb.specialhi.x18 = p->vec;
                fp->xE4_ground_accel_1 = (fp->mv.kb.specialhi.xC4 = 0.0f);
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
    fp->mv.kb.speciallw.x24[0] = p->vec;
    fp->mv.kb.speciallw.x54[0] = fp->mv.kb.speciallw.x24[0];
    fp->mv.kb.speciallw.x88[0] = 0.0f;
    fp->mv.kb.speciallw.x88[4] = 0.0f;
    fp->mv.kb.speciallw.x24[1] = p->vec;
    fp->mv.kb.speciallw.x54[1] = fp->mv.kb.speciallw.x24[1];
    fp->mv.kb.speciallw.x88[1] = 0.0f;
    fp->mv.kb.speciallw.x88[5] = 0.0f;
    fp->mv.kb.speciallw.x24[2] = p->vec;
    fp->mv.kb.speciallw.x54[2] = fp->mv.kb.speciallw.x24[2];
    fp->mv.kb.speciallw.x88[2] = 0.0f;
    fp->mv.kb.speciallw.x88[6] = 0.0f;
    fp->mv.kb.speciallw.x24[3] = p->vec;
    fp->mv.kb.speciallw.x54[3] = fp->mv.kb.speciallw.x24[3];
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
    for (i = 3; i > 0; i--) {
        fp->mv.kb.speciallw.x24[i] = fp->mv.kb.speciallw.x24[i - 1];
        fp->mv.kb.speciallw.x54[i] = fp->mv.kb.speciallw.x54[i - 1];
        fp->mv.kb.speciallw.x88[i] = fp->mv.kb.speciallw.x88[i - 1];
        fp->mv.kb.speciallw.x88[i + 4] = fp->mv.kb.speciallw.x88[i + 3];
    }
    fp->mv.kb.speciallw.x24[0] = fp->mv.kb.speciallw.x18;
    fp->mv.kb.speciallw.x88[0] = fp->mv.kb.speciallw.x84;
    fp->mv.kb.speciallw.x54[0].z = 0.0f;
    fp->mv.kb.speciallw.x54[0].y = 0.0f;
    fp->mv.kb.speciallw.x54[0].x = 0.0f;
    fp->mv.kb.speciallw.x88[4] = 0.0f;
    fp->mv.kb.speciallw.x54[0].x += fp->mv.kb.speciallw.x24[0].x;
    fp->mv.kb.speciallw.x54[0].y += fp->mv.kb.speciallw.x24[0].y;
    fp->mv.kb.speciallw.x54[0].z += fp->mv.kb.speciallw.x24[0].z;
    fp->mv.kb.speciallw.x88[4] += fp->mv.kb.speciallw.x88[0];
    fp->mv.kb.speciallw.x54[0].x += fp->mv.kb.speciallw.x24[1].x;
    fp->mv.kb.speciallw.x54[0].y += fp->mv.kb.speciallw.x24[1].y;
    fp->mv.kb.speciallw.x54[0].z += fp->mv.kb.speciallw.x24[1].z;
    fp->mv.kb.speciallw.x88[4] += fp->mv.kb.speciallw.x88[1];
    fp->mv.kb.speciallw.x54[0].x += fp->mv.kb.speciallw.x24[2].x;
    fp->mv.kb.speciallw.x54[0].y += fp->mv.kb.speciallw.x24[2].y;
    fp->mv.kb.speciallw.x54[0].z += fp->mv.kb.speciallw.x24[2].z;
    fp->mv.kb.speciallw.x88[4] += fp->mv.kb.speciallw.x88[2];
    fp->mv.kb.speciallw.x54[0].x += fp->mv.kb.speciallw.x24[3].x;
    fp->mv.kb.speciallw.x54[0].y += fp->mv.kb.speciallw.x24[3].y;
    fp->mv.kb.speciallw.x54[0].z += fp->mv.kb.speciallw.x24[3].z;
    fp->mv.kb.speciallw.x88[4] += fp->mv.kb.speciallw.x88[3];
    lbVector_Normalize(&fp->mv.kb.speciallw.x54[0]);
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
            temp_f1 * (fp->mv.co.common.x58.x * fp->co_attrs.ground_friction);
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

static inline void ftKbUnkInline(Fighter_GObj* gobj, int val)
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
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirLwEnd, 0x04440012U,
                                  0.0f, 1.0f, 0.0f, NULL);
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
        fp2->mv.kb.speciallw.x24[0] = p->vec;
        fp2->mv.kb.speciallw.x54[0] = fp2->mv.kb.speciallw.x24[0];
        fp2->mv.kb.speciallw.x88[0] = 0.0f;
        fp2->mv.kb.speciallw.x88[4] = 0.0f;
        fp2->mv.kb.speciallw.x24[1] = p->vec;
        fp2->mv.kb.speciallw.x54[1] = fp2->mv.kb.speciallw.x24[1];
        fp2->mv.kb.speciallw.x88[1] = 0.0f;
        fp2->mv.kb.speciallw.x88[5] = 0.0f;
        fp2->mv.kb.speciallw.x24[2] = p->vec;
        fp2->mv.kb.speciallw.x54[2] = fp2->mv.kb.speciallw.x24[2];
        fp2->mv.kb.speciallw.x88[2] = 0.0f;
        fp2->mv.kb.speciallw.x88[6] = 0.0f;
        fp2->mv.kb.speciallw.x24[3] = p->vec;
        fp2->mv.kb.speciallw.x54[3] = fp2->mv.kb.speciallw.x24[3];
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
        fp2->mv.kb.speciallw.x24[0] = p->vec;
        fp2->mv.kb.speciallw.x54[0] = fp2->mv.kb.speciallw.x24[0];
        fp2->mv.kb.speciallw.x88[0] = 0.0f;
        fp2->mv.kb.speciallw.x88[4] = 0.0f;
        fp2->mv.kb.speciallw.x24[1] = p->vec;
        fp2->mv.kb.speciallw.x54[1] = fp2->mv.kb.speciallw.x24[1];
        fp2->mv.kb.speciallw.x88[1] = 0.0f;
        fp2->mv.kb.speciallw.x88[5] = 0.0f;
        fp2->mv.kb.speciallw.x24[2] = p->vec;
        fp2->mv.kb.speciallw.x54[2] = fp2->mv.kb.speciallw.x24[2];
        fp2->mv.kb.speciallw.x88[2] = 0.0f;
        fp2->mv.kb.speciallw.x88[6] = 0.0f;
        fp2->mv.kb.speciallw.x24[3] = p->vec;
        fp2->mv.kb.speciallw.x54[3] = fp2->mv.kb.speciallw.x24[3];
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
    fp2->mv.kb.speciallw.x24[0] = p->vec;
    fp2->mv.kb.speciallw.x54[0] = fp2->mv.kb.speciallw.x24[0];
    fp2->mv.kb.speciallw.x88[0] = 0.0f;
    fp2->mv.kb.speciallw.x88[4] = 0.0f;
    fp2->mv.kb.speciallw.x24[1] = p->vec;
    fp2->mv.kb.speciallw.x54[1] = fp2->mv.kb.speciallw.x24[1];
    fp2->mv.kb.speciallw.x88[1] = 0.0f;
    fp2->mv.kb.speciallw.x88[5] = 0.0f;
    fp2->mv.kb.speciallw.x24[2] = p->vec;
    fp2->mv.kb.speciallw.x54[2] = fp2->mv.kb.speciallw.x24[2];
    fp2->mv.kb.speciallw.x88[2] = 0.0f;
    fp2->mv.kb.speciallw.x88[6] = 0.0f;
    fp2->mv.kb.speciallw.x24[3] = p->vec;
    fp2->mv.kb.speciallw.x54[3] = fp2->mv.kb.speciallw.x24[3];
    fp2->mv.kb.speciallw.x88[3] = 0.0f;
    fp2->mv.kb.speciallw.x88[7] = 0.0f;
    fp2->mv.kb.speciallw.x18 = p->vec;
    fp2->mv.kb.speciallw.x84 = 0.0f;
    ftPartSetRotX(fp, 0, 0.0f);
}

static inline void ftKb_SpecialLw_SetStoneVecs(Fighter_GObj* gobj, Fighter* fp,
                                               ftKb_DatAttrs* da)
{
    Fighter* fp3;
    f32 angle;
    fp3 = GET_FIGHTER(gobj);
    angle = fp->mv.kb.specialhi.xC4;
    fp3->mv.kb.speciallw.x54[0].x = fp3->mv.kb.speciallw.x24[0].x =
        fp->mv.kb.speciallw.x18.x;
    fp3->mv.kb.speciallw.x54[0].y = fp3->mv.kb.speciallw.x24[0].y =
        fp->mv.kb.speciallw.x18.y;
    fp3->mv.kb.speciallw.x54[0].z = fp3->mv.kb.speciallw.x24[0].z =
        fp->mv.kb.speciallw.x18.z;
    fp3->mv.kb.speciallw.x88[4] = fp3->mv.kb.speciallw.x88[0] = angle;
    {
        s32 i;
        for (i = 1; i < 4; i++) {
            fp3->mv.kb.speciallw.x54[i].x = fp3->mv.kb.speciallw.x24[i].x =
                fp->mv.kb.speciallw.x18.x;
            fp3->mv.kb.speciallw.x54[i].y = fp3->mv.kb.speciallw.x24[i].y =
                fp->mv.kb.speciallw.x18.y;
            fp3->mv.kb.speciallw.x54[i].z = fp3->mv.kb.speciallw.x24[i].z =
                fp->mv.kb.speciallw.x18.z;
            fp3->mv.kb.speciallw.x88[i + 4] = fp3->mv.kb.speciallw.x88[i] =
                angle;
        }
    }
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
}

void ftKb_SpecialAirLwStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* fp2;
    s32 temp;
    ftKb_DatAttrs* da = fp->dat_attrs;
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
        ftKb_SpecialLw_SetStoneVecs(gobj, fp, da);
    } else {
        fp2 = GET_FIGHTER(gobj);
        fp2->mv.kb.speciallw.x24[0] = p->vec;
        fp2->mv.kb.speciallw.x54[0] = fp2->mv.kb.speciallw.x24[0];
        fp2->mv.kb.speciallw.x88[0] = 0.0f;
        fp2->mv.kb.speciallw.x88[4] = 0.0f;
        fp2->mv.kb.speciallw.x24[1] = p->vec;
        fp2->mv.kb.speciallw.x54[1] = fp2->mv.kb.speciallw.x24[1];
        fp2->mv.kb.speciallw.x88[1] = 0.0f;
        fp2->mv.kb.speciallw.x88[5] = 0.0f;
        fp2->mv.kb.speciallw.x24[2] = p->vec;
        fp2->mv.kb.speciallw.x54[2] = fp2->mv.kb.speciallw.x24[2];
        fp2->mv.kb.speciallw.x88[2] = 0.0f;
        fp2->mv.kb.speciallw.x88[6] = 0.0f;
        fp2->mv.kb.speciallw.x24[3] = p->vec;
        fp2->mv.kb.speciallw.x54[3] = fp2->mv.kb.speciallw.x24[3];
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
    s32 temp;
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
        ftKb_SpecialLw_SetStoneVecs(gobj, fp, da);
    } else {
        fp2 = GET_FIGHTER(gobj);
        fp2->mv.kb.speciallw.x24[0] = p->vec;
        fp2->mv.kb.speciallw.x54[0] = fp2->mv.kb.speciallw.x24[0];
        fp2->mv.kb.speciallw.x88[0] = 0.0f;
        fp2->mv.kb.speciallw.x88[4] = 0.0f;
        fp2->mv.kb.speciallw.x24[1] = p->vec;
        fp2->mv.kb.speciallw.x54[1] = fp2->mv.kb.speciallw.x24[1];
        fp2->mv.kb.speciallw.x88[1] = 0.0f;
        fp2->mv.kb.speciallw.x88[5] = 0.0f;
        fp2->mv.kb.speciallw.x24[2] = p->vec;
        fp2->mv.kb.speciallw.x54[2] = fp2->mv.kb.speciallw.x24[2];
        fp2->mv.kb.speciallw.x88[2] = 0.0f;
        fp2->mv.kb.speciallw.x88[6] = 0.0f;
        fp2->mv.kb.speciallw.x24[3] = p->vec;
        fp2->mv.kb.speciallw.x54[3] = fp2->mv.kb.speciallw.x24[3];
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
    fp2->mv.kb.speciallw.x24[0] = p->vec;
    fp2->mv.kb.speciallw.x54[0] = fp2->mv.kb.speciallw.x24[0];
    fp2->mv.kb.speciallw.x88[0] = 0.0f;
    fp2->mv.kb.speciallw.x88[4] = 0.0f;
    fp2->mv.kb.speciallw.x24[1] = p->vec;
    fp2->mv.kb.speciallw.x54[1] = fp2->mv.kb.speciallw.x24[1];
    fp2->mv.kb.speciallw.x88[1] = 0.0f;
    fp2->mv.kb.speciallw.x88[5] = 0.0f;
    fp2->mv.kb.speciallw.x24[2] = p->vec;
    fp2->mv.kb.speciallw.x54[2] = fp2->mv.kb.speciallw.x24[2];
    fp2->mv.kb.speciallw.x88[2] = 0.0f;
    fp2->mv.kb.speciallw.x88[6] = 0.0f;
    fp2->mv.kb.speciallw.x24[3] = p->vec;
    fp2->mv.kb.speciallw.x54[3] = fp2->mv.kb.speciallw.x24[3];
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
