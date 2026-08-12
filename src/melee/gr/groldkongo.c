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
#include "lb/lb_00F9.h"

#include <math.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

struct grOldKongo_YakumonoParam {
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

/* 20F468 */ static void grOldKongo_8020F468(bool);
/* 20F46C */ static void grOldKongo_8020F46C(void);
/* 20F4E4 */ static void grOldKongo_8020F4E4(void);
/* 20F4E8 */ static void grOldKongo_8020F4E8(void);
/* 20F524 */ static bool grOldKongo_8020F524(void);
/* 20F52C */ static Ground_GObj* setupStageCallbacks(int gobj_id);
/* 20F618 */ static void stageGObj0_OnInit(Ground_GObj*);
/* 20F644 */ static bool stageGObj0_Callback1(Ground_GObj*);
/* 20F64C */ static void stageGObj0_GObjProc(Ground_GObj*);
/* 20F650 */ static void stageGObj0_Callback3(Ground_GObj*);
/* 20F654 */ static void stageGObj3_OnInit(Ground_GObj*);
/* 20F6B4 */ static bool stageGObj3_Callback1(Ground_GObj*);
/* 20F6BC */ static void stageGObj3_GObjProc(Ground_GObj*);
/* 20F6E0 */ static void stageGObj3_Callback3(Ground_GObj*);
/* 20F6E4 */ static void stageGObj1_OnInit(Ground_GObj*);
/* 20F880 */ static bool stageGObj1_Callback1(Ground_GObj*);
/* 20F888 */ static void stageGObj1_GObjProc(Ground_GObj*);
/* 210058 */ static void stageGObj1_Callback3(Ground_GObj*);
/* 21005C */ static void stageGObj2_OnInit(Ground_GObj*);
/* 2100F4 */ static bool stageGObj2_Callback1(Ground_GObj*);
/* 2100FC */ static void stageGObj2_GObjProc(Ground_GObj*);
/* 210450 */ static void stageGObj2_Callback3(Ground_GObj*);
/* 210454 */ static bool grOldKongo_80210454(Ground_GObj*, Fighter_GObj* keep);
/* 210650 */ static f32 grOldKongo_80210650(void);
/* 210780 */ static DynamicsDesc* grOldKongo_80210780(enum_t);
/* 210788 */ static bool grOldKongo_80210788(Vec3*, int, HSD_JObj*);

static struct grOldKongo_YakumonoParam* yakumono_param;

GrJoint grOk_803E6580[] = {
    { 0, 3, 1 },
    { 1, 3, 2 },
};

static StageCallbacks stage_callbacks[] = {
    {
        stageGObj0_OnInit,
        stageGObj0_Callback1,
        stageGObj0_GObjProc,
        stageGObj0_Callback3,
        0,
    },
    {
        stageGObj1_OnInit,
        stageGObj1_Callback1,
        stageGObj1_GObjProc,
        stageGObj1_Callback3,
        0,
    },
    {
        stageGObj2_OnInit,
        stageGObj2_Callback1,
        stageGObj2_GObjProc,
        stageGObj2_Callback3,
        0,
    },
    {
        stageGObj3_OnInit,
        stageGObj3_Callback1,
        stageGObj3_GObjProc,
        stageGObj3_Callback3,
        (1 << 30) | (1 << 31),
    },
};

StageData grOk_StageData = {
    Gr_Kind_OldKongo,
    stage_callbacks,
    "/GrOk.dat",
    grOldKongo_8020F46C,
    grOldKongo_8020F468,
    grOldKongo_8020F4E4,
    grOldKongo_8020F4E8,
    grOldKongo_8020F524,
    grOldKongo_80210780,
    grOldKongo_80210788,
    (1 << 0),
    grOk_803E6580,
    ARRAY_SIZE(grOk_803E6580),
};

void grOldKongo_8020F468(bool arg) {}

void grOldKongo_8020F46C(void)
{
    yakumono_param = Ground_GetYakumonoParam();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    setupStageCallbacks(0);
    setupStageCallbacks(3);
    setupStageCallbacks(1);
    setupStageCallbacks(2);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grOldKongo_8020F4E4(void) {}

void grOldKongo_8020F4E8(void)
{
    HSD_GObj* gobj;
    gobj = Ground_GetMapGObj(1);
    ftCo_800C0764(gobj, 2, grOldKongo_80210454);
    grZakoGenerator_801CAE04(NULL);
}

bool grOldKongo_8020F524(void)
{
    return false;
}

Ground_GObj* setupStageCallbacks(int gobj_id)
{
    Ground_GObj* gobj;
    StageCallbacks* callbacks = &stage_callbacks[gobj_id];
    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 213, gobj_id);
    }

    return gobj;
}

void stageGObj0_OnInit(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool stageGObj0_Callback1(Ground_GObj* gobj)
{
    return false;
}

void stageGObj0_GObjProc(Ground_GObj* arg) {}

void stageGObj0_Callback3(Ground_GObj* arg) {}

void stageGObj3_OnInit(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    Ground_JObjInline1(gobj);
    gp->x10_flags.b5 = 1;
}

bool stageGObj3_Callback1(Ground_GObj* gobj)
{
    return false;
}

void stageGObj3_GObjProc(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

void stageGObj3_Callback3(Ground_GObj* arg) {}

void stageGObj1_OnInit(Ground_GObj* gobj)
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
    gp->u.taru.xEC = yakumono_param->rspeed_barrel_move_max;
    gp->u.taru.xCC = rand_range(yakumono_param->rframe_barrel_wait_b,
                                yakumono_param->rframe_barrel_wait_a);
    gp->u.taru.xCE = rand_range(yakumono_param->rframe_barrel_stop_b,
                                yakumono_param->rframe_barrel_stop_a);
    lb_8000B1CC(Ground_801C3FA4(gobj, 1), NULL, &sp14);
    Ground_801C4D70(gobj, &sp14, gp->u.taru.xDC);
}

bool stageGObj1_Callback1(Ground_GObj* gobj)
{
    return false;
}

static inline void grOldKongo_8020F888_inline(Ground* gp)
{
    f32 vel = gp->u.taru.xE4;

    if (vel > 0.0f) {
        if (vel < yakumono_param->rspeed_barrel_rot_accel * deg_to_rad) {
            gp->u.taru.xE4 = 0.0f;
            gp->u.taru.xDC = gp->u.taru.xD8;
        } else {
            gp->u.taru.xE4 =
                vel - yakumono_param->rspeed_barrel_rot_accel * deg_to_rad;
        }
    } else if (vel < 0.0f) {
        if (vel > -(yakumono_param->rspeed_barrel_rot_accel * deg_to_rad)) {
            gp->u.taru.xE4 = 0.0f;
            gp->u.taru.xDC = gp->u.taru.xD8;
        } else {
            gp->u.taru.xE4 =
                vel + yakumono_param->rspeed_barrel_rot_accel * deg_to_rad;
        }
    }
}

void stageGObj1_GObjProc(Ground_GObj* gobj)
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
            0.5f * (gp->u.taru.xE4 *
                    (gp->u.taru.xE4 /
                     (yakumono_param->rspeed_barrel_rot_accel * deg_to_rad)));
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
                x_speed = yakumono_param->rspeed_barrel_rot_accel * deg_to_rad;
            } else {
                x_speed =
                    -(yakumono_param->rspeed_barrel_rot_accel * deg_to_rad);
            }
            gp->u.taru.xE0 = x_speed;
            gp->u.taru.xCC = rand_range(yakumono_param->rframe_barrel_roll_b,
                                        yakumono_param->rframe_barrel_roll_a);
        }
        break;
    case 1:
        gp->u.taru.xE4 += gp->u.taru.xE0;
        Ground_ClampSymmetric(
            gp->u.taru.xE4, yakumono_param->rspeed_barrel_rot_max * deg_to_rad,
            &gp->u.taru.xE4);
        if (gp->u.taru.xCC-- < 0) {
            gp->u.taru.xC4 = 2;
            gp->u.taru.xCC = rand_range(yakumono_param->rframe_barrel_wait_b,
                                        yakumono_param->rframe_barrel_wait_a);
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
        gp->u.taru.xEC += yakumono_param->rspeed_barrel_move_accel;
        xec_max = yakumono_param->rspeed_barrel_move_max;
        if (gp->u.taru.xEC > xec_max) {
            gp->u.taru.xEC = xec_max;
            gp->u.taru.xCE = rand_range(yakumono_param->rframe_barrel_stop_b,
                                        yakumono_param->rframe_barrel_stop_a);
            gp->u.taru.xC8 = 2;
        }
        break;
    case 2:
        if (gp->u.taru.xCE-- < 0) {
            gp->u.taru.xC8 = 3;
        }
        break;
    case 3:
        gp->u.taru.xEC -= yakumono_param->rspeed_barrel_move_accel;
        if (gp->u.taru.xEC < 0.0f) {
            gp->u.taru.xEC = 0.0f;
            gp->u.taru.xCE =
                rand_range(yakumono_param->rframe_barrel_interval_b,
                           yakumono_param->rframe_barrel_interval_a);
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
            hit.state = HitCapsule_Enabled;
            hit.damage = yakumono_param->rpower_barrel_attack;
            hit.kb_angle = yakumono_param->rvector_barrel_attack;
            hit.unkC = yakumono_param->rreff_barrel_attack;
            hit.unk10 = yakumono_param->rrfix_barrel_attack;
            hit.unk14 = yakumono_param->rradd_barrel_attack;
            hit.element = yakumono_param->x68;
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

void stageGObj1_Callback3(Ground_GObj* arg) {}

void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    gp->u.unk.xC4 = rand_range(yakumono_param->rframe_bird_wait_b,
                               yakumono_param->rframe_bird_wait_a);
}

bool stageGObj2_Callback1(Ground_GObj* gobj)
{
    return false;
}

void stageGObj2_GObjProc(Ground_GObj* arg0)
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
            HSD_JObjSetTranslateY(
                jobj, (yakumono_param->rrange_bird_random_offset_y *
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
        min = yakumono_param->rframe_bird_wait_b;
        max = yakumono_param->rframe_bird_wait_a;
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

void stageGObj2_Callback3(Ground_GObj* arg) {}

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
          yakumono_param->rframe_barrel_in * yakumono_param->rframe_barrel_in))
    {
        goto done;
    }

    rand_val = HSD_Randf();
    diff = yakumono_param->rframe_barrel_shoot_b -
           yakumono_param->rframe_barrel_shoot_a;
    gp->u.taru.xCA =
        (s16) (diff * rand_val + yakumono_param->rframe_barrel_shoot_a);
    gp->u.taru.keep = keep;
    gp->u.taru.xC6 = 1;
    Ground_801C5440(gp, 0, 0x129U);
    grAnime_801C7FF8(ground_gobj, 2, 7, 1, 0.0f, 1.0f);
    grMaterial_801C9604(ground_gobj, yakumono_param->x6C, 0);
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

    total = yakumono_param->rrate_barrel_ld + yakumono_param->rrate_barrel_l +
            yakumono_param->rrate_barrel_lu + yakumono_param->rrate_barrel_u +
            yakumono_param->rrate_barrel_ru + yakumono_param->rrate_barrel_r +
            yakumono_param->rrate_barrel_rd + yakumono_param->rrate_barrel_d;

    if (total != 0) {
        r = HSD_Randi(total);
    } else {
        r = 0;
    }

    if ((r -= yakumono_param->rrate_barrel_ld) < 0) {
        result = 2.3561945;
    } else if ((r -= yakumono_param->rrate_barrel_l) < 0) {
        result = 1.5707964;
    } else if ((r -= yakumono_param->rrate_barrel_lu) < 0) {
        result = 0.7853982;
    } else if ((r -= yakumono_param->rrate_barrel_u) < 0) {
        result = 0;
    } else if ((r -= yakumono_param->rrate_barrel_ru) < 0) {
        result = -0.7853982;
    } else if ((r -= yakumono_param->rrate_barrel_r) < 0) {
        result = -1.5707964;
    } else if ((r -= yakumono_param->rrate_barrel_rd) < 0) {
        result = -2.3561945;
    } else if ((r -= yakumono_param->rrate_barrel_d) < 0) {
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
