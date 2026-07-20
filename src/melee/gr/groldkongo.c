#include "groldkongo.h"

#include <platform.h>

#include "baselib/debug.h"
#include "cm/camera.h"
#include "ef/efsync.h"

#include "forward.h"

#include "ft/ftdevice.h"
#include "ft/ftlib.h"
#include "ftCommon/ftCo_BarrelWait.h"
#include "gr/granime.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"

#include "lb/forward.h"

#include "lb/lb_00B0.h"
#include "lb/lbspdisplay.h"

#include <math.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

struct grOldKongo_Yaku {
    s16 rframe_bird_wait_a;
    s16 rframe_bird_wait_b;
    f32 rrange_bird_random_offset_y;
    f32 rframe_barrel_shoot_a;
    f32 rframe_barrel_shoot_b;
    f32 rframe_barrel_in;
    f32 rframe_barrel_wait_a;
    f32 rframe_barrel_wait_b;
    f32 rspeed_barrel_rot_accel;
    f32 rspeed_barrel_rot_max;
    f32 rframe_barrel_roll_a;
    f32 rframe_barrel_roll_b;
    s16 rrate_barrel_ld;
    s16 rrate_barrel_l;
    s16 rrate_barrel_lu;
    s16 rrate_barrel_u;
    s16 rrate_barrel_ru;
    s16 rrate_barrel_r;
    s16 rrate_barrel_rd;
    s16 rrate_barrel_d;
    s32 rframe_barrel_interval_a;
    s32 rframe_barrel_interval_b;
    f32 rspeed_barrel_move_accel;
    f32 rspeed_barrel_move_max;
    s32 rframe_barrel_stop_a;
    s32 rframe_barrel_stop_b;
    s32 rpower_barrel_attack;
    s32 rvector_barrel_attack;
    s32 rreff_barrel_attack;
    s32 rrfix_barrel_attack;
    s32 rradd_barrel_attack;
    s32 x68;
    s32 x6C;
};

static struct grOldKongo_Yaku* yaku;

S16Vec3 grOk_803E6580[] = {
    { 0, 3, 1 },
    { 1, 3, 2 },
};

StageCallbacks grOk_803E658C[4] = {
    { grOldKongo_8020F618, grOldKongo_8020F644, grOldKongo_8020F64C,
      grOldKongo_8020F650, 0 },
    { grOldKongo_8020F6E4, grOldKongo_8020F880, grOldKongo_8020F888,
      grOldKongo_80210058, 0 },
    { grOldKongo_8021005C, grOldKongo_802100F4, grOldKongo_802100FC,
      grOldKongo_80210450, 0 },
    { grOldKongo_8020F654, grOldKongo_8020F6B4, grOldKongo_8020F6BC,
      grOldKongo_8020F6E0, 0xC0000000 },
};

char grOk_803E65DC[] = "/GrOk.dat";

typedef struct grOk_StageData {
    StageData stage_data;
    char report_format[0x24];
} grOk_StageData;

grOk_StageData grOk_803E65E8 = {
    {
        OLDKONGO,
        grOk_803E658C,
        grOk_803E65DC,
        grOldKongo_8020F46C,
        grOldKongo_8020F468,
        grOldKongo_8020F4E4,
        grOldKongo_8020F4E8,
        grOldKongo_8020F524,
        grOldKongo_80210780,
        grOldKongo_80210788,
        1,
        (S16Vec3*) grOk_803E6580,
        2,
    },
    "%s:%d: couldn t get gobj(id=%d)\n",
};

void grOldKongo_8020F468(bool arg) {}

void grOldKongo_8020F46C(void)
{
    yaku = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grOldKongo_8020F52C(0);
    grOldKongo_8020F52C(3);
    grOldKongo_8020F52C(1);
    grOldKongo_8020F52C(2);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grOldKongo_8020F4E4(void) {}

void grOldKongo_8020F4E8(void)
{
    HSD_GObj* gobj;
    gobj = Ground_801C2BA4(1);
    ftCo_800C0764(gobj, 2, grOldKongo_80210454);
    grZakoGenerator_801CAE04(NULL);
}

bool grOldKongo_8020F524(void)
{
    return false;
}

HSD_GObj* grOldKongo_8020F52C(int arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grOk_803E658C[arg0];

    gobj = Ground_GetStageGObj(arg0);

    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);

        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }
        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }
        if (callbacks->callback2 != NULL) {
            HSD_GObj_SetupProc(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport((char*) grOk_803E6580 + 0x9C, (char*) grOk_803E6580 + 0xC0,
                 0xD5, arg0);
    }

    return gobj;
}

void grOldKongo_8020F618(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grOldKongo_8020F644(Ground_GObj* gobj)
{
    return false;
}

void grOldKongo_8020F64C(Ground_GObj* arg) {}

void grOldKongo_8020F650(Ground_GObj* arg) {}

void grOldKongo_8020F654(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x10_flags.b5 = 1;
}

bool grOldKongo_8020F6B4(Ground_GObj* gobj)
{
    return false;
}

void grOldKongo_8020F6BC(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

void grOldKongo_8020F6E0(Ground_GObj* arg) {}

void grOldKongo_8020F6E4(Ground_GObj* gobj)
{
    Vec3 sp14;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    grAnime_801C8138(gobj, gp->map_id, 0);
    grMaterial_801C94D8(jobj);
    gp->u.taru.xE8 = 1.0f;
    gp->u.taru.xEC = 1.0f;
    gp->u.taru.xD8 = 0.0f;
    gp->u.taru.xDC = 0.0f;
    gp->u.taru.xC4 = 0;
    gp->u.taru.xC6 = 0;
    gp->u.taru.xC8 = 2;
    gp->u.taru.keep = NULL;
    gp->u.taru.xE0 = 0.0f;
    gp->u.taru.xE4 = 0.0f;
    gp->u.taru.xEC = yaku->rspeed_barrel_move_max;
    gp->u.taru.xCC =
        rand_range(yaku->rframe_barrel_wait_b, yaku->rframe_barrel_wait_a);
    gp->u.taru.xCE =
        rand_range(yaku->rframe_barrel_stop_b, yaku->rframe_barrel_stop_a);
    lb_8000B1CC(Ground_801C3FA4(gobj, 1), NULL, &sp14);
    Ground_801C4D70(gobj, &sp14, gp->u.taru.xDC);
}

bool grOldKongo_8020F880(Ground_GObj* gobj)
{
    return false;
}

static inline void grOldKongo_8020F888_inline(Ground* gp)
{
    f32 vel = gp->u.taru.xE4;

    if (vel > 0.0f) {
        if (vel < yaku->rspeed_barrel_rot_accel * deg_to_rad) {
            gp->u.taru.xE4 = 0.0f;
            gp->u.taru.xDC = gp->u.taru.xD8;
        } else {
            gp->u.taru.xE4 = vel - yaku->rspeed_barrel_rot_accel * deg_to_rad;
        }
    } else if (vel < 0.0f) {
        if (vel > -(yaku->rspeed_barrel_rot_accel * deg_to_rad)) {
            gp->u.taru.xE4 = 0.0f;
            gp->u.taru.xDC = gp->u.taru.xD8;
        } else {
            gp->u.taru.xE4 = vel + yaku->rspeed_barrel_rot_accel * deg_to_rad;
        }
    }
}

void grOldKongo_8020F888(Ground_GObj* gobj)
{
    Vec3 sp3C;
    Ground* gp;
    HSD_JObj* jobj;
    f32 angle_limit;
    f32 x_speed;
    f32 hit_angle;
    f32 angle_delta;
    f32 xec_max;
    PAD_STACK(8);

    gp = GET_GROUND(gobj);
    jobj = Ground_801C3FA4(gobj, 1);
    switch (gp->u.taru.xC4) {
    case 2:
    case 3:
        angle_limit =
            0.5f *
            (gp->u.taru.xE4 *
             (gp->u.taru.xE4 / (yaku->rspeed_barrel_rot_accel * deg_to_rad)));
        if (gp->u.taru.xE4 > 0.0f) {
            angle_delta = gp->u.taru.xD8 - gp->u.taru.xDC;
        } else if (gp->u.taru.xE4 < 0.0f) {
            angle_delta = gp->u.taru.xDC - gp->u.taru.xD8;
        } else {
            HSD_ASSERT(0x18CU, 0);
        }
        if (angle_delta < 0.0f) {
            angle_delta += M_TAU;
        }
        if (angle_delta < angle_limit || angle_delta < ABS(gp->u.taru.xE4)) {
            if (gp->u.taru.xC4 == 3) {
                gp->u.taru.xC4 = 0;
            }
            break;
        }
        if (gp->u.taru.xC4 == 2) {
            gp->u.taru.xC4 = 3;
        }
        break;
    case 0:
        grOldKongo_8020F888_inline(gp);
        gp->u.taru.xCC -= 1;
        if (gp->u.taru.xCC < 0) {
            gp->u.taru.xC4 = 1;
            if (HSD_Randi(2) != 0) {
                x_speed = yaku->rspeed_barrel_rot_accel * deg_to_rad;
            } else {
                x_speed = -(yaku->rspeed_barrel_rot_accel * deg_to_rad);
            }
            gp->u.taru.xE0 = x_speed;
            gp->u.taru.xCC = rand_range(yaku->rframe_barrel_roll_b,
                                        yaku->rframe_barrel_roll_a);
        }
        break;
    case 1:
        gp->u.taru.xE4 += gp->u.taru.xE0;
        Ground_ClampSymmetric(gp->u.taru.xE4,
                              yaku->rspeed_barrel_rot_max * deg_to_rad,
                              &gp->u.taru.xE4);
        if (gp->u.taru.xCC-- < 0) {
            gp->u.taru.xC4 = 2;
            gp->u.taru.xCC = rand_range(yaku->rframe_barrel_wait_b,
                                        yaku->rframe_barrel_wait_a);
            gp->u.taru.xD8 = grOldKongo_80210650();
        }
        break;
    }

    gp->u.taru.xDC += gp->u.taru.xE4;
    Ground_WrapAngle(&gp->u.taru.xDC);
    HSD_JObjSetRotationZ(jobj, gp->u.taru.xDC);
    lb_8000B1CC(jobj, NULL, &sp3C);
    Ground_801C4D70(gobj, &sp3C, gp->u.taru.xDC);

    switch (gp->u.taru.xC8) {
    case 0:
        if (gp->u.taru.xCE-- < 0) {
            gp->u.taru.xC8 = 1;
        }
        break;
    case 1:
        gp->u.taru.xEC += yaku->rspeed_barrel_move_accel;
        xec_max = yaku->rspeed_barrel_move_max;
        if (gp->u.taru.xEC > xec_max) {
            gp->u.taru.xEC = xec_max;
            gp->u.taru.xCE = rand_range(yaku->rframe_barrel_stop_b,
                                        yaku->rframe_barrel_stop_a);
            gp->u.taru.xC8 = 2;
        }
        break;
    case 2:
        if (gp->u.taru.xCE-- < 0) {
            gp->u.taru.xC8 = 3;
        }
        break;
    case 3:
        gp->u.taru.xEC -= yaku->rspeed_barrel_move_accel;
        if (gp->u.taru.xEC < 0.0f) {
            gp->u.taru.xEC = 0.0f;
            gp->u.taru.xCE = rand_range(yaku->rframe_barrel_interval_b,
                                        yaku->rframe_barrel_interval_a);
            gp->u.taru.xC8 = 0;
        }
        break;
    }
    grAnime_801C7A04(gobj, 0, 7U, gp->u.taru.xEC);

    switch (gp->u.taru.xC6) {
    case 1:
        if (gp->u.taru.keep == NULL) {
            gp->u.taru.xC6 = 0;
        } else {
            if (gp->u.taru.xCA-- >= 0) {
                return;
            }
            gp->u.taru.xC6 = 2;
        }
    case 2:
        grAnime_801C7FF8(gobj, 2, 7, 2, 0.0f, 1.0f);
        grMaterial_801C95C4(gobj);
        gp->u.taru.hit_timer = 0;
        gp->u.taru.xC6 = 3;
    case 3:
        if (gp->u.taru.hit_timer++ > 0xA) {
            lbColl_80008D30_arg1 hit = {
                1, 1, 361, 0, 0, 180,
            };
            hit.state = 1;
            hit.damage = yaku->rpower_barrel_attack;
            hit.kb_angle = yaku->rvector_barrel_attack;
            hit.unkC = yaku->rreff_barrel_attack;
            hit.unk10 = yaku->rrfix_barrel_attack;
            hit.unk14 = yaku->rradd_barrel_attack;
            hit.element = yaku->x68;
            hit_angle = 1.5707963267948966 + gp->u.taru.xDC;
            if (hit_angle < 0.0f) {
                hit_angle += M_TAU;
            } else if (hit_angle > M_TAU) {
                hit_angle -= M_TAU;
            }
            hit_angle = 57.29578f * hit_angle;
            {
                Fighter_GObj* fighter_gobj = gp->u.taru.keep;

                if (fighter_gobj->p_link == 8) {
                    ftCo_8009EC70(fighter_gobj, &sp3C, &hit, hit_angle);
                }
            }
            gp->u.taru.xC6 = 4;
            Ground_801C5440(gp, 0, 0x12AU);
        }
        break;
    case 4:
        gp->u.taru.xC6 = 0;
        break;
    case 0:
    default:
        break;
    }
}

void grOldKongo_80210058(Ground_GObj* arg) {}

void grOldKongo_8021005C(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    gp->u.unk.xC4 =
        rand_range(yaku->rframe_bird_wait_b, yaku->rframe_bird_wait_a);
}

bool grOldKongo_802100F4(Ground_GObj* gobj)
{
    return false;
}

void grOldKongo_802100FC(Ground_GObj* arg0)
{
    u32 pad;
    f32 left;
    f32 right;
    f32 center;
    Ground* gp = GET_GROUND(arg0);
    HSD_JObj* jobj = GET_JOBJ(arg0);
    s32 timer = gp->u.unk.xC4;
    u32 pad3;

    if (timer > 0) {
        gp->u.unk.xC4 = timer - 1;
        if (gp->u.unk.xC4 == 0) {
            f32 x;

            grAnime_801C8138(arg0, gp->map_id, 0);
            HSD_JObjSetTranslateY(jobj, (yaku->rrange_bird_random_offset_y *
                                         ((2.0f * (0, HSD_Randf())) - 1.0f)) +
                                            70.0f);
            HSD_JObjSetTranslateZ(jobj, -200.0f);
            Camera_800307D0(&left, &center, &right);
            if (HSD_Randi(2) != 0) {
                if (200.0f < right) {
                    x = right;
                } else {
                    x = 200.0f;
                }
                HSD_JObjSetTranslateX(jobj, x);
                HSD_JObjClearFlagsAll(Ground_801C3FA4(arg0, 3), JOBJ_HIDDEN);
                return;
            }
            if (-200.0f > left) {
                x = left;
            } else {
                x = -200.0f;
            }
            HSD_JObjSetTranslateX(jobj, x);
            HSD_JObjClearFlagsAll(Ground_801C3FA4(arg0, 1), JOBJ_HIDDEN);
        }
    } else if (grAnime_801C83D0(arg0, 0, 7) != 0) {
        s32 min;
        int max;

        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        min = yaku->rframe_bird_wait_b;
        max = yaku->rframe_bird_wait_a;
        if (min > max) {
            s32 range = min - max;

            min = max + (range != 0 ? HSD_Randi(range) : 0);
        } else if (min < max) {
            s32 range = max - min;

            min += (range != 0 ? HSD_Randi(range) : 0);
        }
        gp->u.unk.xC4 = min;
    }
}

void grOldKongo_80210450(Ground_GObj* arg) {}

bool grOldKongo_80210454(Ground_GObj* ground_gobj, Fighter_GObj* keep)
{
    Ground* gp;
    Vec3 pos_gnd;
    Vec3 pos_ft;
    f32 unk;
    f32 rand_val;
    f32 diff;

    gp = GET_GROUND(ground_gobj);

    if (gp->u.taru.xC6 != 0) {
        goto done;
    }

    Ground_801C4DA0(&pos_gnd, &unk);
    ftLib_80086644(keep, &pos_ft);

    if (!((pos_gnd.x - pos_ft.x) * (pos_gnd.x - pos_ft.x) +
              (pos_gnd.y - pos_ft.y) * (pos_gnd.y - pos_ft.y) +
              (pos_gnd.z - pos_ft.z) * (pos_gnd.z - pos_ft.z) <
          yaku->rframe_barrel_in * yaku->rframe_barrel_in))
    {
        goto done;
    }

    rand_val = HSD_Randf();
    diff = yaku->rframe_barrel_shoot_b - yaku->rframe_barrel_shoot_a;
    gp->u.taru.xCA = (s16) (diff * rand_val + yaku->rframe_barrel_shoot_a);
    gp->u.taru.keep = keep;
    gp->u.taru.xC6 = 1;
    Ground_801C5440(gp, 0, 0x129U);
    grAnime_801C7FF8(ground_gobj, 2, 7, 1, 0.0f, 1.0f);
    grMaterial_801C9604(ground_gobj, yaku->x6C, 0);
    efSync_Spawn(0x405, ground_gobj, &pos_ft);
    ftLib_80086C18(keep, 0xD, 0x1E);
    return true;
done:
    return false;
}

void grOldKongo_802105AC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->u.taru.xC6 == 1) {
        gp->u.taru.xC6 = 2;
    }
}

void grOldKongo_802105C8(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    if (gp->u.taru.xC6 != 1) {
        return;
    }

    HSD_ASSERT(751, gp->u.taru.keep);

    if (((u8*) gp->u.taru.keep)[2] == 8) {
        gp->u.taru.xC6 = 0;
        gp->u.taru.keep = NULL;
        grMaterial_801C95C4(gobj);
    }
}

f32 grOldKongo_80210650(void)
{
    f32 result;
    s32 total;
    s32 r;

    total = yaku->rrate_barrel_ld + yaku->rrate_barrel_l +
            yaku->rrate_barrel_lu + yaku->rrate_barrel_u +
            yaku->rrate_barrel_ru + yaku->rrate_barrel_r +
            yaku->rrate_barrel_rd + yaku->rrate_barrel_d;

    if (total != 0) {
        r = HSD_Randi(total);
    } else {
        r = 0;
    }

    if ((r -= yaku->rrate_barrel_ld) < 0) {
        result = 2.3561945;
    } else if ((r -= yaku->rrate_barrel_l) < 0) {
        result = 1.5707964;
    } else if ((r -= yaku->rrate_barrel_lu) < 0) {
        result = 0.7853982;
    } else if ((r -= yaku->rrate_barrel_u) < 0) {
        result = 0;
    } else if ((r -= yaku->rrate_barrel_ru) < 0) {
        result = -0.7853982;
    } else if ((r -= yaku->rrate_barrel_r) < 0) {
        result = -1.5707964;
    } else if ((r -= yaku->rrate_barrel_rd) < 0) {
        result = -2.3561945;
    } else if ((r -= yaku->rrate_barrel_d) < 0) {
        result = -3.1415927;
    } else {
        HSD_ASSERT(786, 0);
    }

    return result;
}

DynamicsDesc* grOldKongo_80210780(enum_t gobj)
{
    return false;
}

bool grOldKongo_80210788(Vec3* a, int arg, HSD_JObj* joint)
{
    Vec3 b;

    lb_8000B1CC(joint, NULL, &b);

    if (a->y > b.y) {
        return true;
    } else {
        return false;
    }
}
