#include "ft_0899.h"

#include "math.h"

#include "db/dbsound.h"
#include "ft/fighter.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lbbgflash.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <MSL/math_ppc.h>
#include <MSL/trigf.h>

/* 08998C */ static bool fn_8008998C(Fighter* fp, IKState* ik, Vec3* normal);

static bool fn_8008998C(Fighter* fp, IKState* ik, Vec3* normal)
{
    u8 _[12];
    Vec3 jobj_pos;
    u8 __[4];
    Vec3 sp20;
    f32 floor_y;
    u32 floor_flags;
    u8 ___[4];
    f32 delta_y;
    f32 pos_x;
    f32 delta_x;
    f32 slope;

    Vec3* pos = &ik->pos4;
    HSD_JObjGetTranslation2((HSD_JObj*) fp->gobj->hsd_obj, &jobj_pos);

    normal->z = 0.0f;
    normal->y = 0.0f;
    normal->x = 0.0f;

    if (mpLib_8004DD90_Floor(fp->coll_data.floor.index, pos, &floor_y,
                             &floor_flags, normal) != -1)
    {
        delta_y = (pos->y + floor_y) - jobj_pos.y;
    } else {
        mpFloorGetLeft(fp->coll_data.floor.index, &sp20);
        if (pos->x > sp20.x) {
            mpFloorGetRight(fp->coll_data.floor.index, &sp20);
        }
        delta_y = sp20.y - jobj_pos.y;
    }

    if (ABS(delta_y) < 0.0001f) {
        return 0;
    }

    pos_x = pos->x;
    if (pos_x != jobj_pos.x) {
        delta_x = pos_x - jobj_pos.x;
        slope = delta_x;
        slope = delta_y / slope;
        if (slope > 0.45f) {
            delta_y = 0.45f * delta_x;
        } else if (slope < -0.45f) {
            delta_y = -0.45f * delta_x;
        }
    } else {
        delta_y = 0.0f;
    }

    pos->y += delta_y;
    return 1;
}

void ft_80089B08(Fighter_GObj* gobj)
{
    u8 _[8];
    IKState ik;
    Vec3 spA4;
    Quaternion rot_save0;
    Quaternion rot_save1;
    Quaternion rot_save2;
    Quaternion rot_save3;
    Quaternion rot_save4;
    Quaternion rot_save5;
    Vec3 sp38;
    Vec3 sp2C;
    volatile f32 line_len_sqrt;
    Vec3 sp1C;

    Fighter* fp = gobj->user_data;
    (void) &line_len_sqrt;

    if (!fp->x2219_b5 && fp->ground_or_air == GA_Ground) {
        if (db_804D4AF8 != 0) {
            f32 scale_y = fp->x34_scale.y;
            ik.len0 = ((ftData_x58_t*) fp->ft_data->x58)->x4 * scale_y;
            ik.len1 = scale_y * (((ftData_x58_t*) fp->ft_data->x58)->xC +
                                 ((ftData_x58_t*) fp->ft_data->x58)->x18);

            if (fp->x221C_u16_y & 2) {
                ik.jobj0 =
                    fp->parts[((ftData_x58_t*) fp->ft_data->x58)->x0].joint;
                ik.jobj1 =
                    fp->parts[((ftData_x58_t*) fp->ft_data->x58)->x8].joint;
                ik.jobj2 =
                    fp->parts[((ftData_x58_t*) fp->ft_data->x58)->x10].joint;
                ik.angle_max = M_PI_2_F;
                ik.angle_limit = 1.2217305f;
                lb_8000B1CC(ik.jobj0, NULL, &ik.pos0);
                lb_8000B1CC(ik.jobj1, NULL, &ik.pos1);
                lb_8000B1CC(ik.jobj2, NULL, &ik.pos2);
                {
                    f32 len;
                    lbVector_Diff(&ik.pos2, &ik.pos1, &ik.pos3);
                    len = ik.len1;
                    lbVector_Normalize(&ik.pos3);
                    ik.pos3.x *= len;
                    ik.pos3.y *= len;
                    ik.pos3.z *= len;
                    lbVector_Add(&ik.pos3, &ik.pos1);
                    ik.pos4 = ik.pos3;
                }
                rot_save0 = ik.jobj0->rotate;
                rot_save1 = ik.jobj1->rotate;
                rot_save2 = ik.jobj2->rotate;
                if (fn_8008998C(fp, &ik, &spA4) != 0) {
                    lbBgFlash_80021410(&ik);
                }
                lbBgFlash_80020E38(ik.jobj2, &spA4, 0.34906584f, 0.34906584f,
                                   -1.0f);
                ik.jobj0->rotate = rot_save0;
                ik.jobj1->rotate = rot_save1;
                ik.jobj2->rotate = rot_save2;
            }
            if (fp->x221C_u16_y & 1) {
                ik.jobj0 =
                    fp->parts[((ftData_x58_t*) fp->ft_data->x58)->x1].joint;
                ik.jobj1 =
                    fp->parts[((ftData_x58_t*) fp->ft_data->x58)->x9].joint;
                ik.jobj2 =
                    fp->parts[((ftData_x58_t*) fp->ft_data->x58)->x11].joint;
                ik.angle_max = M_PI_2_F;
                ik.angle_limit = 1.2217305f;
                lb_8000B1CC(ik.jobj0, NULL, &ik.pos0);
                lb_8000B1CC(ik.jobj1, NULL, &ik.pos1);
                lb_8000B1CC(ik.jobj2, NULL, &ik.pos2);
                {
                    f32 len;
                    lbVector_Diff(&ik.pos2, &ik.pos1, &ik.pos3);
                    len = ik.len1;
                    lbVector_Normalize(&ik.pos3);
                    ik.pos3.x *= len;
                    ik.pos3.y *= len;
                    ik.pos3.z *= len;
                    lbVector_Add(&ik.pos3, &ik.pos1);
                    ik.pos4 = ik.pos3;
                }
                rot_save3 = ik.jobj0->rotate;
                rot_save4 = ik.jobj1->rotate;
                rot_save5 = ik.jobj2->rotate;
                if (fn_8008998C(fp, &ik, &spA4) != 0) {
                    lbBgFlash_80021410(&ik);
                }
                lbBgFlash_80020E38(ik.jobj2, &spA4, 0.34906584f, 0.34906584f,
                                   1.0f);
                ik.jobj0->rotate = rot_save3;
                ik.jobj1->rotate = rot_save4;
                ik.jobj2->rotate = rot_save5;
            }
        }
        if (fp->x221C_u16_y & 4) {
            s32 line_id = fp->coll_data.floor.index;
            f32 angle = fp->facing_dir * atan2f(fp->coll_data.floor.normal.x,
                                                fp->coll_data.floor.normal.y);
            f32 dx, dy, line_len;
            f32 adj_angle;

            mpLineGetV1Pos(line_id, &sp38);
            mpLineGetV0Pos(line_id, &sp2C);
            dy = sp38.y - sp2C.y;
            dx = sp38.x;
            dx -= sp2C.x;
            line_len = dx * dx + dy * dy;
            (void) line_len;
            if (line_len > 0.0f) {
                f64 guess = __frsqrte((f64) line_len);
                guess = 0.5 * guess * (3.0 - guess * guess * line_len);
                guess = 0.5 * guess * (3.0 - guess * guess * line_len);
                guess = 0.5 * guess * (3.0 - guess * guess * line_len);
                ((volatile f32*) &sp1C)[-1] = (f32) ((f64) line_len * guess);
                line_len = ((volatile f32*) &sp1C)[-1];
            }
            if (line_len < 5.0f) {
                adj_angle = 0.0f;
                {
                    s32 next_check = mpLineGetNext(line_id);
                    s32 next_id = next_check;
                    if (next_check != -1 && (mpLineGetKind(next_id) & 1)) {
                        mpLineGetNormal(next_id, &sp1C);
                        adj_angle = fp->facing_dir * atan2f(sp1C.x, sp1C.y);
                    }
                }
                {
                    s32 prev_check = mpLineGetPrev(line_id);
                    s32 prev_id = prev_check;
                    if (prev_check != -1 && (mpLineGetKind(prev_id) & 1)) {
                        mpLineGetNormal(prev_id, &sp1C);
                        adj_angle =
                            0.5f * ((fp->facing_dir * atan2f(sp1C.x, sp1C.y)) +
                                    adj_angle);
                    }
                }
                {
                    f32 diff = adj_angle - angle;
                    diff = ABS(diff);
                    if (diff > 0.17453292f) {
                        angle = adj_angle;
                    }
                }
            }
            {
                f32 max_angle = 0.017453292f * p_ftCommonData->x804;
                if (angle > max_angle) {
                    angle = max_angle;
                } else if (angle < -max_angle) {
                    angle = -max_angle;
                }
            }
            ftPartSetRotX(fp, 0, angle);
        }
    }
    PAD_STACK(16);
}

void ft_8008A1B8(Fighter_GObj* gobj, u32 flags)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x221C_u16_y = flags;
    if (!(flags & (1 << 2))) {
        ftPartSetRotX(fp, 0, 0.0F);
    }
}
