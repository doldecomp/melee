#include "ftCo_ItemThrow.h"

#include "ftCo_FallSpecial.h"
#include "ftCo_Lift.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0DF1.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/types.h"

#include "it/forward.h"

#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "pl/plbonuslib.h"

#include <baselib/forward.h>

#include <common_structs.h>
#include <math.h>
#include <MSL/trigf.h>

/* 094D70 */ static bool ftCo_800951D0(Fighter_GObj* gobj);
/* 094E7C */ static bool ftCo_800952DC(Fighter_GObj* gobj);
/* 0952C8 */ static UNK_RET lbl_80095728(UNK_PARAMS);
/* 0952D8 */ static UNK_RET lbl_80095738(UNK_PARAMS);
/* 09549C */ static void ftCo_800958FC(Fighter_GObj* gobj, int);
/* 095540 */ static UNK_RET ftCo_800959A0(UNK_PARAMS);
/* 0955D0 */ static void ftCo_80095A30(Fighter_GObj* gobj);
/* 0958FC */ static void ftCo_80095D5C(Fighter* fp, Vec3* arg1);
/* 095A9C */ static void ftCo_80095EFC(Fighter_GObj* gobj);

/* static */ float const ftCo_804D8590 = 0;
/* static */ double const ftCo_804D8598 = 4503599627370496;
/* static */ double const ftCo_804D85A0 = 4503601774854144;
/* static */ float const ftCo_804D85A8 = 1;
/* static */ float const ftCo_804D85AC = 0.01;
/* static */ float const ftCo_804D85B0 = deg_to_rad;

bool ftCo_80094E54(Fighter* fp)
{
    if (fp->input.x668 & HSD_PAD_A &&
        (fp->input.held_inputs & HSD_PAD_LR || !it_8026B30C(fp->item_gobj)))
    {
        return true;
    }
    return false;
}

int ftCo_80094EA4(HSD_GObj* gobj)
{
    float stick_angle;
    float var_f28;
    float stick_x;
    float stick_y;
    float var_f31;
    Fighter* fp;
    FtMotionId msid;
    int ret;
    PAD_STACK(8);

    fp = gobj->user_data;
    msid = fp->motion_id;

    if (fp->item_gobj != NULL) {
        if (fp->input.x668 & (HSD_PAD_A | HSD_PAD_B)) {
            stick_x = fp->input.lstick.x;
            stick_y = fp->input.lstick.y;
            var_f28 = fp->x673;
            var_f31 = fp->x674;
            stick_angle = ftCo_GetLStickAngle(fp);
            ret = true;
        } else {
            var_f28 = 0.0f;
            stick_x = fp->input.cstick.x;
            var_f31 = 0.0f;
            stick_y = fp->input.cstick.y;
            stick_angle = ftCo_GetCStickAngle(fp);
            ret = false;
        }
    } else {
        return false;
    }
    if (ABS(stick_x) >= p_ftCommonData->x3C &&
        var_f28 < p_ftCommonData->x40 + p_ftCommonData->x44)
    {
        msid = stick_x * fp->facing_dir >= 0.0f ? ftCo_MS_HeavyThrowF4
                                                : ftCo_MS_HeavyThrowB4;
    } else {
        if (stick_y >= p_ftCommonData->xCC &&
            var_f31 < p_ftCommonData->xD0 + fp->co_attrs.jump_startup_time)
        {
            msid = ftCo_MS_HeavyThrowHi4;
        } else {
            if (stick_y <= p_ftCommonData->xD4 &&
                var_f31 < p_ftCommonData->xD8)
            {
                msid = ftCo_MS_HeavyThrowLw4;
            } else {
                if (ABS(stick_x) >= p_ftCommonData->x98) {
                    if (ABS(stick_angle) <= p_ftCommonData->x20_radians) {
                        msid = stick_x * fp->facing_dir >= 0
                                   ? ftCo_MS_HeavyThrowF
                                   : ftCo_MS_HeavyThrowB;
                    } else {
                        goto block_32;
                    }
                } else {
                block_32:
                    if (stick_y >=
                            p_ftCommonData->attackhi3_stick_threshold_y &&
                        stick_angle > p_ftCommonData->x20_radians)
                    {
                        msid = ftCo_MS_HeavyThrowHi;
                    } else {
                        if (stick_y <= p_ftCommonData->xB0 &&
                            (stick_angle < -p_ftCommonData->x20_radians))
                        {
                            msid = ftCo_MS_HeavyThrowLw;
                        } else if (ret != 0) {
                            msid = ftCo_MS_HeavyThrowF;
                        }
                    }
                }
            }
        }
    }
    if (msid != fp->motion_id) {
        ftCo_800958FC(gobj, msid);
        return true;
    }
    return false;
}

int ftCo_8009515C(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL && fp->input.x668 & HSD_PAD_A) {
        if (fp->mv.co.itemthrow.x20 != 0) {
            ftCo_800957F4(gobj, ftCo_MS_LightThrowDash);
        } else {
            ftCo_80095A30(gobj);
        }
        return true;
    }
    if (fp->mv.co.itemthrow.x20 != 0) {
        --fp->mv.co.itemthrow.x20;
    }
    return false;
}

bool ftCo_800951D0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL && ftCo_80094E54(fp)) {
        ftCo_80095A30(gobj);
        return true;
    }
    return false;
}

bool ftCo_80095254(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL && ftCo_80094E54(fp)) {
        ftCo_800957F4(gobj, ftCo_MS_LightThrowDash);
        return true;
    }
    return false;
}

bool ftCo_800952DC(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL && fp->input.held_inputs & HSD_PAD_LR) {
        ftCo_800957F4(gobj, ftCo_MS_LightThrowDash);
        return true;
    }
    return false;
}

/// @todo A lot of shared code with #ftCo_80094EA4.
bool ftCo_80095328(Fighter_GObj* gobj, bool* arg1)
{
    float angle;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    int msid;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if (fp->item_gobj != NULL && ftCo_800DF50C(fp)) {
        var_f31 = fp->input.cstick.x;
        var_f28 = fp->input.cstick.y;
        var_f29 = 0.0f;
        var_f30 = 0.0f;
        angle = ftCo_GetCStickAngle(fp);
    } else if (fp->item_gobj != NULL && ftCo_80094E54(fp)) {
        var_f31 = fp->input.lstick.x;
        var_f28 = fp->input.lstick.y;
        var_f30 = fp->x673;
        var_f29 = fp->x674;
        angle = ftCo_GetLStickAngle(fp);
    } else {
        return false;
    }

    if (ABS(var_f31) < p_ftCommonData->xDC &&
        ABS(var_f28) < p_ftCommonData->xE0)
    {
        if (it_8026B30C(fp->item_gobj) == 0 &&
            !(fp->input.held_inputs & HSD_PAD_LR))
        {
            ftCo_800957F4(gobj, 0x64);
            if (arg1 != NULL) {
                *arg1 = true;
            }
            return true;
        } else {
            ftCo_80095744(gobj, arg1);
            fp->x2224_b1 = true;
            return true;
        }
    }
    if (angle > p_ftCommonData->x20_radians) {
        msid = var_f29 < p_ftCommonData->x3FC ? 0x72 : 0x66;
    } else if (angle < -p_ftCommonData->x20_radians) {
        msid = var_f29 < p_ftCommonData->x3FC ? 0x73 : 0x67;
    } else if (var_f31 * fp->facing_dir >= 0.0F) {
        msid = var_f30 < p_ftCommonData->x3FC ? 0x70 : 0x64;
    } else {
        msid = var_f30 < p_ftCommonData->x3FC ? 0x71 : 0x65;
    }
    ftCo_800957F4(gobj, msid);
    if (arg1 != NULL) {
        *arg1 = true;
    }
    return true;
}

bool ftCo_8009563C(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL && ftCo_80094E54(fp) &&
        fp->mv.co.itemthrow4.unk_timer != 0)
    {
        ftCo_800957F4(gobj, fp->motion_id == ftCo_MS_EscapeF
                                ? ftCo_MS_LightThrowF4
                                : ftCo_MS_LightThrowB4);
        return true;
    }
    if (fp->mv.co.itemthrow4.unk_timer != 0) {
        --fp->mv.co.itemthrow4.unk_timer;
    }
    return false;
}

static void ftCo_80095700(Fighter_GObj* gobj, enum_t arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (arg1) {
    case 95:
    case 101:
    case 105:
    case 109:
    case 113:
    case 117:
        fp->mv.co.itemthrow.facing_dir = -fp->facing_dir;
        return;
    default:
        fp->mv.co.itemthrow.facing_dir = fp->facing_dir;
        return;
    }
}

void ftCo_80095744(Fighter_GObj* gobj, int* arg1)
{
    Vec3 vec;
    Fighter* fp = gobj->user_data;
    vec.x = vec.y = vec.z = 0;
    PAD_STACK(4);

    if (ftGetParasolStatus(gobj) != -1) {
        if (fp->motion_id == ftCo_MS_ItemParasolFallSpecial) {
            ftCo_800968C8(gobj);
        } else {
            ftCo_Fall_Enter(gobj);
        }
        if (arg1 != NULL) {
            *arg1 = 1;
        }
    } else if (arg1 != NULL) {
        *arg1 = 0;
    }
    Item_8026ABD8(fp->item_gobj, &vec, 1);
}

inline float getAnimSpeed(Fighter_GObj* gobj, int msid)
{
    Fighter* fp;
    float speed = 1;
    fp = GET_FIGHTER(gobj);
    if (msid >= ftCo_MS_LightThrowF4) {
        speed *= p_ftCommonData->x400;
    }
    speed *= (1 / it_8026B334(fp->item_gobj));
    return speed;
}

void ftCo_800957F4(Fighter_GObj* gobj, int msid)
{
    float anim_spd;
    Fighter* fp = GET_FIGHTER(gobj);

    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    fp->throw_flags = 0;

    fp->mv.co.itemthrow4.anim_spd = anim_spd = getAnimSpeed(gobj, msid);
    ftCo_80095700(gobj, msid);
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, anim_spd, 0, NULL);

    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = ftCo_80095EFC;
    ftCo_80095EFC((HSD_GObj*) gobj);
}

/// @todo Mostly just an inline of #ftCo_800957F4.
void ftCo_800958FC(HSD_GObj* gobj, FtMotionId msid)
{
    Fighter* temp_r4;
    Fighter* fp;
    float temp_f2;

    fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    fp->throw_flags = 0;

    temp_f2 = getAnimSpeed(gobj, msid);
    temp_r4 = GET_FIGHTER(gobj);
    switch (msid) {
    case 0x5F:
    case 0x65:
    case 0x69:
    case 0x6D:
    case 0x71:
    case 0x75:
        temp_r4->mv.co.itemthrow.facing_dir = -temp_r4->facing_dir;
        break;
    default:
        temp_r4->mv.co.itemthrow.facing_dir = temp_r4->facing_dir;
        break;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0F, temp_f2, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);

    fp->accessory4_cb = ftCo_80095EFC;
    fp->take_dmg_cb = ftCo_800974C4;
    if (fp->x2222_b0) {
        fp->phys_cb = ftCo_800961D0;
        fp->coll_cb = ftCo_80096498;
    }
    ftCo_80095EFC(gobj);
}

void ftCo_80095A30(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float var_f1_2;
    float var_f1_3;
    int var_r0;
    int var_r0_2;
    int var_r0_3;
    int var_r29;
    float var_f1;

    PAD_STACK(0x8);

    var_f1 = fp->input.lstick.x;
    if (var_f1 < 0.0f) {
        var_f1 = -var_f1;
    }
    if (var_f1 >= p_ftCommonData->x3C &&
        fp->x673 < p_ftCommonData->x40 + p_ftCommonData->x44)
    {
        if (fp->input.lstick.x * fp->facing_dir >= 0.0f) {
            var_r0 = 0x6C;
        } else {
            var_r0 = 0x6D;
        }
        var_r29 = var_r0;
    } else {
        if (fp->input.lstick.y >= p_ftCommonData->xCC &&
            fp->x674 < p_ftCommonData->xD0 + fp->co_attrs.jump_startup_time)
        {
            var_r29 = 0x6E;
        } else {
            if (fp->input.lstick.y <= p_ftCommonData->xD4 &&
                fp->x674 < p_ftCommonData->xD8)
            {
                var_r29 = 0x6F;
            } else {
                var_f1_2 = fp->input.lstick.x;
                if (var_f1_2 < 0.0f) {
                    var_f1_2 = -var_f1_2;
                }
                if (var_f1_2 >= p_ftCommonData->x98) {
                    if (ftCo_GetLStickAngle(fp) < 0.0f) {
                        var_f1_3 = -ftCo_GetLStickAngle(fp);
                    } else {
                        var_f1_3 = ftCo_GetLStickAngle(fp);
                    }
                    if (var_f1_3 <= p_ftCommonData->x20_radians) {
                        if (fp->input.lstick.x * fp->facing_dir >= 0.0f) {
                            var_r0_2 = 0x5E;
                        } else {
                            var_r0_2 = 0x5F;
                        }
                        var_r29 = var_r0_2;
                    } else {
                        goto block_25;
                    }
                } else {
                block_25:
                    if (fp->input.lstick.y >=
                            p_ftCommonData->attackhi3_stick_threshold_y &&
                        ftCo_GetLStickAngle(fp) > p_ftCommonData->x20_radians)
                    {
                        var_r29 = 0x60;
                    } else {
                        if (fp->input.lstick.y <= p_ftCommonData->xB0 &&
                            ftCo_GetLStickAngle(fp) <
                                -p_ftCommonData->x20_radians)
                        {
                            var_r29 = 0x61;
                        } else {
                            if (it_8026B30C(fp->item_gobj) == 0) {
                                var_r0_3 = 0x5E;
                            } else {
                                var_r0_3 = 0x63;
                            }
                            var_r29 = var_r0_3;
                        }
                    }
                }
            }
        }
    }
    ftCo_800957F4(gobj, var_r29);
}

void ftCo_80095D5C(Fighter* fp, Vec3* arg1)
{
    float vel;
    float angle;
    void* array_element;
    u32 cmd_var0 = fp->cmd_vars[0];
    float vel_mul = 1;
    ftCo_DatAttrs* co_attrs = &fp->co_attrs;
    if (cmd_var0 != 0) {
        vel_mul = 0.01f * ((cmd_var0 >> 12) & 0x3FF);
    }
    array_element = Fighter_804D6550 + (fp->motion_id * 3);
    vel = vel_mul * (co_attrs->item_throw_velocity_multiplier *
                     M2C_FIELD(array_element, float*, -0x468));
    if (cmd_var0 != 0) {
        u32 s16_var1 = ((s16*) &fp->cmd_vars)[1];
        int int_angle = s16_var1 << 20;
        int_angle = int_angle >> 20;
        if (int_angle == 361) {
            angle = M2C_FIELD(array_element, float*, -0x464);
        } else {
            angle = deg_to_rad * int_angle;
        }
        fp->cmd_vars[0] = 0;
    } else {
        angle = M2C_FIELD(array_element, float*, -0x464);
    }
    arg1->x = fp->mv.co.itemthrow.facing_dir * (vel * cosf(angle));
    arg1->y = vel * sinf(angle);
    arg1->z = 0;
}

void ftCo_ItemThrow_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftCheckThrowB4(fp)) {
        fp->facing_dir = -fp->facing_dir;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCo_80095EFC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Item_GObj* item_gobj = fp->item_gobj;
    Vec3 vec0;
    Vec3 vec1;
    Vec3 vec2;

    PAD_STACK(0x8);

    if (item_gobj != NULL) {
        lb_8000B1CC(it_80272C90(item_gobj), NULL, &vec0);
        if (ftCheckThrowB3(fp)) {
            ftCo_80095D5C(fp, &vec1);
            {
                u32 cmd_var1 = fp->cmd_vars[1];
                float var_f4 = 1;
                if (cmd_var1 != 0) {
                    fp->cmd_vars[1] = 0;
                    var_f4 = 0.01f * (cmd_var1 & 0x3FFFFF);
                }
                {
                    float vec0_x = vec0.x;
                    float fsm = -fp->cmd_timer / fp->frame_speed_mul;
                    float cd_xB4 = M2C_FIELD(fp + 0x110, float*, 0xB4);
                    float temp_f2 =
                        cd_xB4 *
                        M2C_FIELD((Fighter_804D6550 + (fp->motion_id * 3)),
                                  float*, -0x460);
                    float temp_f4 = var_f4 * temp_f2;
                    {
                        vec2.x = fsm * (fp->mv.co.itemthrow4.x8.x - vec0_x) +
                                 vec0_x;
                        {
                            float vec1_y =
                                fsm * (fp->mv.co.itemthrow4.x8.y - vec0.y) +
                                vec0.y;
                            vec2.y = vec1_y;
                            vec2.z = 0;
                            pl_8003E978(fp->player_id, fp->x221F_b4,
                                        fp->item_gobj, vec1_y, temp_f2, cd_xB4,
                                        temp_f4, vec0_x, vec0.y, fsm);
                        }
                        {
                            FtMoveId msid = fp->motion_id;
                            if (msid == ftCo_MS_LightThrowDrop) {
                                Item_8026AC74(fp->item_gobj, &vec2, &vec1,
                                              temp_f4);
                            } else if (msid >= ftCo_MS_LightThrowF4) {
                                if (it_8026B2B4(fp->item_gobj) == 1) {
                                    ftCommon_8007EBAC(fp, 29, 0);
                                } else {
                                    ftCommon_8007EBAC(fp, 27, 0);
                                }
                                Item_8026AD20(fp->item_gobj, &vec2, &vec1,
                                              temp_f4);
                            } else {
                                if (it_8026B2B4(fp->item_gobj) == 1) {
                                    ftCommon_8007EBAC(fp, 28, 0);
                                } else {
                                    ftCommon_8007EBAC(fp, 26, 0);
                                }
                                Item_8026AD20(fp->item_gobj, &vec2, &vec1,
                                              temp_f4);
                            }
                        }
                    }
                }
            }
        } else {
            fp->mv.co.itemthrow4.x8 = vec0;
        }
    }
}

void ftCo_ItemThrow_IASA(Fighter_GObj* gobj) {}

void ftCo_ItemThrow_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_LightThrowDash_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommonData* cd = p_ftCommonData;
    if (fp->cur_anim_frame <= cd->x408) {
        ft_80085030(gobj, cd->x40C * (cd->x404 * fp->co_attrs.gr_friction),
                    fp->facing_dir);
    } else {
        ft_80085030(gobj, p_ftCommonData->x404 * fp->co_attrs.gr_friction,
                    fp->facing_dir);
    }
}

void ftCo_LightThrowAir_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_800961D0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        ft_80084DB0(gobj);
    } else {
        ft_80084F3C(gobj);
    }
}

void ftCo_LightThrowDashDrop_Coll(Fighter_GObj* gobj)
{
    ft_80084104(gobj);
}

void ftCo_LightThrow_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, ftCo_80096250);
}

static inline void inlineA0(Fighter_GObj* gobj, FtMotionId msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float facing_dir = fp->facing_dir;
    if (facing_dir != fp->facing_dir1) {
        fp->facing_dir = fp->facing_dir1;
    }
    Fighter_ChangeMotionState(
        gobj, msid,
        Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |
            Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
            Ft_MF_SkipModelFlags | Ft_MF_Unk27,
        fp->cur_anim_frame, fp->mv.co.itemthrow4.anim_spd, 0, NULL);
    fp->facing_dir = facing_dir;
    fp->accessory4_cb = ftCo_80095EFC;
    ftCo_80095EFC(gobj);
}

void ftCo_80096250(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    if (fp->motion_id >= ftCo_MS_LightThrowF4) {
        inlineA0(gobj, fp->motion_id + 4);
    } else {
        inlineA0(gobj, fp->motion_id + 6);
    }
}

void ftCo_LightThrowAir_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, ftCo_80096374);
}

void ftCo_80096374(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    {
        if (fp->motion_id >= ftCo_MS_LightThrowF4) {
            inlineA0(gobj, fp->motion_id - 4);
        } else {
            inlineA0(gobj, fp->motion_id - 6);
        }
    }
}

void ftCo_HeavyThrow_Coll(Fighter_GObj* gobj)
{
    ft_800841B8(gobj, ftCo_80096E68);
}

void ftCo_80096498(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Ground) {
        if (ft_80082708(gobj) == GA_Ground) {
            ftCommon_8007D5D4(fp);
        }
    } else if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
    }
}
