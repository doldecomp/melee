#include "gr/grkongo.h"

#include "grkongo.static.h"

#include "grmaterial.h"
#include "types.h"

#include "ef/efsync.h"
#include "ft/ftdevice.h"
#include "ft/ftlib.h"
#include "ftCommon/ftCo_BarrelWait.h"
#include "gm/gm_unsplit.h"
#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/items/itbox.h"
#include "it/items/itklap.h"
#include "lb/lb_00B0.h"
#include "lb/lbspdisplay.h"

#include "mp/forward.h"

#include "mp/mplib.h"
#include "MSL/math.h"
#include "MSL/math_ppc.h" // IWYU pragma: keep

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/random.h>
#include <baselib/spline.h>

S16Vec3 grKg_803E16E0[6] = {
    { 2, 10, 19 }, { 3, 10, 22 }, { 5, 10, 43 },
    { 6, 10, 44 }, { 0, 1, 0 },   { 1, 2, 2 },
};

StageCallbacks grKg_803E1704[12] = {
    { NULL, NULL, NULL, NULL, 0 },
    { grKongo_801D6074, grKongo_801D6190, grKongo_801D6198, grKongo_801D6378,
      0 },
    { grKongo_801D6074, grKongo_801D6190, grKongo_801D6198, grKongo_801D6378,
      0 },
    { grKongo_801D6038, grKongo_801D6064, grKongo_801D606C, grKongo_801D6070,
      0 },
    { grKongo_801D5FA8, grKongo_801D5FD4, grKongo_801D5FDC, grKongo_801D5FE0,
      0 },
    { grKongo_801D55D8, grKongo_801D5774, grKongo_801D577C, grKongo_801D5FA4,
      0 },
    { grKongo_801D5FE4, grKongo_801D6028, grKongo_801D6030, grKongo_801D6034,
      0 },
    { grKongo_801D637C, grKongo_801D64B4, grKongo_801D64BC, grKongo_801D6518,
      0 },
    { grKongo_801D637C, grKongo_801D64B4, grKongo_801D64BC, grKongo_801D6518,
      0 },
    { grKongo_801D637C, grKongo_801D64B4, grKongo_801D64BC, grKongo_801D6518,
      0 },
    { grKongo_801D5490, grKongo_801D5574, grKongo_801D557C, grKongo_801D55D4,
      0xC0000000 },
    { grKongo_801D651C, grKongo_801D6660, grKongo_801D6668, grKongo_801D69AC,
      0 },
};

char grKg_803E17F4[] = "/GrKg.dat";

typedef struct grKg_StageData {
    StageData stage_data;
    char report_format[0x24];
} grKg_StageData;

grKg_StageData grKg_803E1800 = {
    {
        KONGO,
        grKg_803E1704,
        grKg_803E17F4,
        grKongo_801D523C,
        grKongo_801D5238,
        grKongo_801D52F8,
        grKongo_801D52FC,
        grKongo_801D5338,
        grKongo_801D8444,
        grKongo_801D844C,
        1,
        grKg_803E16E0,
        6,
    },
    "%s:%d: couldn t get gobj(id=%d)\n",
};

char grKg_803E1858[] = "grkongo.c";
char grKg_803E1A00[];
static const lbColl_80008D30_arg1 grKg_803B7FB0 = {
    1, 1, 361, 0, 0, 180, 0, 0, 0,
};
static const f32 grKg_804DAFA0 = 0.0f;
static const f32 grKg_804DAFA4 = 1.0f;
static const f32 grKg_804DAFCC = -99999.0f;
static const f32 grKg_804DAFD0 = 3.4028235e38f;

void grKongo_801D5490(Ground_GObj* arg0)
{
    Ground* temp_r31;
    PAD_STACK(8);

    temp_r31 = arg0->user_data;
    Ground_801C2ED0(arg0->hsd_obj, temp_r31->map_id);
    grAnime_801C8138(arg0, temp_r31->map_id, 0);
    temp_r31->x10_flags.b5 = 1;
    temp_r31->gv.kongo.xE4 = -1;
    temp_r31->gv.kongo.xE6 = -1;
    temp_r31->gv.kongo.xC4 = 0.0f;
    temp_r31->gv.kongo.xC8 = 0.0f;
    temp_r31->gv.kongo3.xCC = Ground_801C3FA4(arg0, 0x13);
    temp_r31->gv.kongo.u.taru.keep = Ground_801C3FA4(arg0, 0xD);
    temp_r31->gv.kongo.xD4 = 0.0f;
    temp_r31->gv.kongo.xD8 = 0.0f;
    temp_r31->gv.kongo.xDC = Ground_801C3FA4(arg0, 0x2B);
    temp_r31->gv.kongo.xE0 = Ground_801C3FA4(arg0, 0x28);
    grKongo_801D69B0(arg0);
    Ground_801C10B8(arg0, fn_801D542C);
    Ground_801C2FE0(arg0);
}

bool grKongo_801D5574(Ground_GObj* arg)
{
    return 0;
}
void grKongo_801D557C(Ground_GObj* arg0)
{
    grKongo_801D7134(arg0, 0);
    grKongo_801D77E0(arg0, 0);
    grKongo_801D7BBC(arg0);
    lb_800115F4();
    Ground_801C2FE0(arg0);
    mpLib_8005667C(4);
}

void grKongo_801D55D4(Ground_GObj* arg)
{
    return;
}

/// @todo Investigate these types of patterns in
/// other files; the Randi check with zero is probably
/// its own thing
static inline s32 random_adder_b(s32 a, s32 b)
{
    s32 c = a - b;
    if (c != 0) {
        c = HSD_Randi(c);
    } else {
        c = 0;
    }
    return b + c;
}

static inline s32 random_adder(s32 temp_f0, s32 temp_f2)
{
    s32 temp_r28_2;
    s32 var_r29;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 var_r3;
    s32 var_r3_2;
#if 0
    if (temp_f2 > temp_f0) {
        return random_adder_b(temp_f2, temp_f0);
    } else if (temp_f2 < temp_f0) {
        return random_adder_b(temp_f0, temp_f2);
    }
#else
    temp_r28_2 = (s32) temp_f0;
    var_r29 = (s32) temp_f2;

    if (temp_f2 > temp_f0) {
        temp_r3 = var_r29 - temp_r28_2;
        if (temp_r3 != 0) {
            var_r3 = HSD_Randi(temp_r3);
        } else {
            var_r3 = 0;
        }
        return temp_r28_2 + var_r3;
    } else if (var_r29 < temp_r28_2) {
        temp_r3_2 = temp_r28_2 - var_r29;
        if (temp_r3_2 != 0) {
            var_r3_2 = HSD_Randi(temp_r3_2);
        } else {
            var_r3_2 = 0;
        }
        return var_r29 + var_r3_2;
    }
    return temp_r28_2;
#endif
}

static inline s32 random_adder_f(f32 a, f32 b)
{
    s32 ia = a;
    s32 ib = b;
    if (ib > ia) {
        return random_adder_b(ib, ia);
    } else if (ib < ia) {
        return random_adder_b(ia, ib);
    }
    return ia;
}

void grKongo_801D55D8(Ground_GObj* arg0)
{
    Vec3 sp14;
    Ground* temp_r31;
    void* temp_r28;
    PAD_STACK(8);

    temp_r31 = arg0->user_data;
    temp_r28 = arg0->hsd_obj;
    grAnime_801C8138(arg0, temp_r31->map_id, 0);
    grMaterial_801C94D8(temp_r28);
    temp_r31->gv.kongo3.xE4 = 1.0f;
    temp_r31->gv.kongo.xE8 = 1.0f;
    temp_r31->gv.kongo.xD4 = 0.0f;
    temp_r31->gv.kongo.xD8 = 0.0f;
    temp_r31->gv.kongo3.xC4 = 0;
    temp_r31->gv.kongo3.xC6 = 0;
    temp_r31->gv.kongo3.xC8 = 2;
    temp_r31->gv.kongo.u.taru.keep = NULL;
    temp_r31->gv.kongo3.xDC = 0.0f;
    temp_r31->gv.kongo3.xE0 = 0.0f;
    temp_r31->gv.kongo.xE8 = grKg_804D6980->unk60;
    temp_r31->gv.kongo2.xCC =
        rand_range((s32) grKg_804D6980->unk30, (s32) grKg_804D6980->unk2C);
    temp_r31->gv.kongo2.xCE =
        rand_range(grKg_804D6980->unk68, grKg_804D6980->unk64);
    lb_8000B1CC(Ground_801C3FA4(arg0, 1), NULL, &sp14);
    Ground_801C4D70(arg0, &sp14, temp_r31->gv.kongo.xD8);
#if 0
    temp_r31->unkCC = var_r29;
    var_r29_2 = grKg_804D6980->unk68;
    temp_r28_3 = grKg_804D6980->unk64;
    if (var_r29_2 > temp_r28_3) {
        temp_r3_3 = var_r29_2 - temp_r28_3;
        if (temp_r3_3 != 0) {
            var_r3_3 = HSD_Randi(temp_r3_3);
        } else {
            var_r3_3 = 0;
        }
        var_r29_2 = temp_r28_3 + var_r3_3;
    } else if (var_r29_2 < temp_r28_3) {
        temp_r3_4 = temp_r28_3 - var_r29_2;
        if (temp_r3_4 != 0) {
            var_r3_4 = HSD_Randi(temp_r3_4);
        } else {
            var_r3_4 = 0;
        }
        var_r29_2 += var_r3_4;
    }
#endif
}

bool grKongo_801D5774(Ground_GObj* arg)
{
    return 0;
}

#define DegToRad(a) ((a) * 0.017453292F)
#define M_TAU 6.283185307179586

static inline void grKongo_801D577C_inline(Ground* gp, f32 angular_vel_2,
                                           bool sign)
{
    f32 limit = DegToRad(grKg_804D6980->unk34);
    bool compare = sign ? (angular_vel_2 < limit) : (angular_vel_2 > -limit);
    if (compare) {
        gp->gv.kongo3.xE0 = 0.0f;
        gp->gv.kongo3.xD8 = gp->gv.kongo3.xD4;
    } else {
        gp->gv.kongo3.xE0 = angular_vel_2 - (sign ? limit : -limit);
    }
}

static inline void compare(f32 a, f32 b, f32* c)
{
    if (a > b) {
        *c = b;
    } else {
        b = -b;
        if (a < b) {
            *c = b;
        }
    }
}

static inline void tau_range(f32* a)
{
    f32 temp = *a;
    if (temp > M_TAU) {
        *a = (f64) temp - M_TAU;
    } else if (temp < -M_TAU) {
        *a = (f64) temp + M_TAU;
    }
}

void grKongo_801D577C(Ground_GObj* arg0)
{
    Ground* gp = arg0->user_data;
    HSD_JObj* jobj = Ground_801C3FA4(arg0, 1);
    Vec3 vec;
    lbColl_80008D30_arg1 hit;
    f32 limit_angle;
    f32 angle_delta;

    switch (gp->gv.kongo3.xC4) {
    case 2:
    case 3: {
        f32 angular_vel;
        angular_vel = gp->gv.kongo3.xE0;
        limit_angle = 0.5f * (angular_vel *
                              (angular_vel / DegToRad(grKg_804D6980->unk34)));
        if (angular_vel > 0.0f) {
            angle_delta = gp->gv.kongo3.xD4 - gp->gv.kongo3.xD8;
        } else if (angular_vel < 0.0f) {
            angle_delta = gp->gv.kongo3.xD8 - gp->gv.kongo3.xD4;
        } else {
            __assert(grKg_803E1858, 505, "0");
        }
        if (angle_delta < 0.0f) {
            angle_delta += M_TAU;
        }
        if (!(angle_delta < limit_angle)) {
            f32 abs_vel;
            abs_vel = gp->gv.kongo3.xE0;
            if (abs_vel < 0.0f) {
                abs_vel = -abs_vel;
            }
            if (!(angle_delta < abs_vel)) {
                if ((s16) gp->gv.kongo3.xC4 == 2) {
                    gp->gv.kongo3.xC4 = 3;
                }
                break;
            }
        }
        if ((s16) gp->gv.kongo3.xC4 == 3) {
            gp->gv.kongo3.xC4 = 0;
        }
        break;
    }
    case 0:
        if (gp->gv.kongo3.xE0 > 0.0f) {
            grKongo_801D577C_inline(gp, gp->gv.kongo3.xE0, 1);
        } else if (gp->gv.kongo3.xE0 < 0.0f) {
            grKongo_801D577C_inline(gp, gp->gv.kongo3.xE0, 0);
        }
        gp->gv.kongo2.xCC -= 1;
        if ((s16) gp->gv.kongo2.xCC < 0) {
            f32 spin_step;
            gp->gv.kongo3.xC4 = 1;
            if (HSD_Randi(2) != 0) {
                spin_step = DegToRad(grKg_804D6980->unk34);
            } else {
                spin_step = -DegToRad(grKg_804D6980->unk34);
            }
            gp->gv.kongo3.xDC = spin_step;
            gp->gv.kongo2.xCC =
                random_adder_f(grKg_804D6980->unk3C, grKg_804D6980->unk40);
        }
        break;
    case 1:
        gp->gv.kongo3.xE0 += gp->gv.kongo3.xDC;
        compare(gp->gv.kongo3.xE0, DegToRad(grKg_804D6980->unk38),
                &gp->gv.kongo3.xE0);
        {
            s16 val2 = gp->gv.kongo2.xCC;
            gp->gv.kongo2.xCC = val2 - 1;
            if (val2 < 0) {
                gp->gv.kongo3.xC4 = 2;
                gp->gv.kongo2.xCC =
                    random_adder_f(grKg_804D6980->unk2C, grKg_804D6980->unk30);
                gp->gv.kongo3.xD4 = grKongo_801D8314();
            }
        }
        break;
    }
    gp->gv.kongo3.xD8 += gp->gv.kongo3.xE0;
    tau_range(&gp->gv.kongo3.xD8);
    HSD_JObjSetRotationZ(jobj, gp->gv.kongo.xD8);
    lb_8000B1CC(jobj, NULL, &vec);
    Ground_801C4D70(arg0, &vec, gp->gv.kongo3.xD8);
    switch (gp->gv.kongo3.xC8) {
    case 0: {
        s16 val = gp->gv.kongo2.xCE;
        gp->gv.kongo2.xCE -= 1;
        if (val < 0) {
            gp->gv.kongo3.xC8 = 1;
        }
    } break;
    case 1:
        gp->gv.kongo2.xE8 += grKg_804D6980->unk5C;
        if (gp->gv.kongo2.xE8 > grKg_804D6980->unk60) {
            gp->gv.kongo2.xE8 = grKg_804D6980->unk60;
            gp->gv.kongo2.xCE =
                random_adder(grKg_804D6980->unk68, grKg_804D6980->unk64);
            gp->gv.kongo3.xC8 = 2;
        }
        break;
    case 2: {
        s16 val2 = gp->gv.kongo2.xCE;
        gp->gv.kongo2.xCE = val2 - 1;
        if (val2 < 0) {
            gp->gv.kongo3.xC8 = 3;
        }
    } break;
    case 3:
        gp->gv.kongo2.xE8 -= grKg_804D6980->unk5C;
        if (gp->gv.kongo2.xE8 < 0.0f) {
            gp->gv.kongo2.xE8 = 0.0f;
            gp->gv.kongo2.xCE = random_adder(*(s32*) &grKg_804D6980->unk58,
                                             *(s32*) &grKg_804D6980->unk54);
            gp->gv.kongo3.xC8 = 0;
        }
        break;
    }
    grAnime_801C7A04(arg0, 0, 7, gp->gv.kongo3.xE8);

    switch (gp->gv.kongo3.xC6) {
    case 0: { /* switch 2 */
        HSD_GObj* item_gobj = grKongo_801D8078(arg0);
        if (item_gobj != NULL) {
            it_802E20D8(item_gobj);
            {
                f32 rand_val = HSD_Randf();
                f32 diff = grKg_804D6980->unk24 - grKg_804D6980->unk20;
                gp->gv.kongo3.xCA = (diff * rand_val) + grKg_804D6980->unk20;
            }
            gp->gv.kongo.u.taru.keep = item_gobj;
            gp->gv.kongo3.xC6 = 1;
            Ground_801C5440(gp, 0, 0x129U);
            grMaterial_801C9604(arg0, grKg_804D6980->unk84, 0);
            return;
        }
        return;
    }
    case 1: {
        s16 val2;
        if (gp->gv.kongo.u.taru.keep == NULL) {
            gp->gv.kongo3.xC6 = 0;
            goto block_124;
        }
        val2 = gp->gv.kongo3.xCA;
        gp->gv.kongo3.xCA = val2 - 1;
        if (val2 >= 0) {
            break;
        }
        gp->gv.kongo3.xC6 = 2;
    }
    case 2: { /* switch 2 */
        f32 angle;
        HSD_GObj* kept_gobj;
    block_124:;
        hit = grKg_803B7FB0;
        hit.state = 1;
        hit.damage = *(u32*) &grKg_804D6980->unk6C;
        hit.kb_angle = *(u32*) &grKg_804D6980->unk70;
        hit.unkC = *(u32*) &grKg_804D6980->unk74;
        hit.unk10 = *(u32*) &grKg_804D6980->unk78;
        hit.unk14 = *(u32*) &grKg_804D6980->unk7C;
        hit.element = *(u32*) &grKg_804D6980->unk80;
        angle = (f32) (1.5707963267948966 + (f64) gp->gv.kongo3.xD8);
        if (angle < 0.0f) {
            angle = (f32) ((f64) angle + M_TAU);
        } else if (angle > M_TAU) {
            angle = (f32) ((f64) angle - M_TAU);
        }
        kept_gobj = gp->gv.kongo.u.taru.keep;
        angle = angle * 57.29578f;
        if (kept_gobj->p_link == 8) {
            ftCo_8009EC70((Fighter_GObj*) kept_gobj, &vec, &hit, angle);
        } else if (kept_gobj->p_link == 9) {
            it_802E2330((Item_GObj*) kept_gobj, &vec, &hit, angle);
        }
        gp->gv.kongo3.xC6 = 3;
        Ground_801C5440(gp, 0, 0x12AU);
        grMaterial_801C95C4(arg0);
        return;
    }
    case 3: /* switch 2 */
        if (grKongo_801D8078(arg0) == NULL) {
            gp->gv.kongo3.xC6 = 0;
        }
        break;
    }
}

void grKongo_801D5FA4(Ground_GObj* arg) {}

void grKongo_801D5FA8(Ground_GObj* arg0)
{
    Ground* temp_r3 = arg0->user_data;
    grAnime_801C8138(arg0, temp_r3->map_id, 0);
}

bool grKongo_801D5FD4(Ground_GObj* arg)
{
    return 0;
}

void grKongo_801D5FDC(Ground_GObj* arg) {}

void grKongo_801D5FE0(Ground_GObj* arg) {}

void grKongo_801D5FE4(Ground_GObj* arg0)
{
    Ground* temp_r31;
    PAD_STACK(8);
    temp_r31 = arg0->user_data;
    grAnime_801C8138(arg0, temp_r31->map_id, 0);
    temp_r31->x11_flags.b012 = 1;
}

bool grKongo_801D6028(Ground_GObj* arg)
{
    return 0;
}

void grKongo_801D6030(Ground_GObj* arg) {}

void grKongo_801D6034(Ground_GObj* arg) {}

void grKongo_801D6038(Ground_GObj* arg0)
{
    Ground* temp_r3 = arg0->user_data;
    grAnime_801C8138(arg0, temp_r3->map_id, 0);
}

bool grKongo_801D6064(Ground_GObj* arg)
{
    return 0;
}

void grKongo_801D606C(Ground_GObj* arg) {}

void grKongo_801D6070(Ground_GObj* arg) {}

void grKongo_801D6074(Ground_GObj* arg0)
{
    Ground* temp_r31;
    HSD_JObj* temp_r30;
    PAD_STACK(8);

    temp_r31 = arg0->user_data;
    temp_r30 = arg0->hsd_obj;
    grAnime_801C8138(arg0, temp_r31->map_id, 0);
    temp_r31->gv.kongo3.xC4 = 0;
    temp_r31->gv.kongo3.xC6 = 0;
    temp_r31->gv.kongo3.xC8 = 0;
    temp_r31->gv.kongo3.xCA = 0;
    temp_r31->gv.kongo2.xD0 = -99999.0f;
    temp_r31->gv.kongo2.xD4 = 3.4028235e38f;
    if ((enum InternalStageId) temp_r31->map_id == TEST) {
        temp_r31->gv.kongo.xCC = (f32) ((45.0 * HSD_Randf()) + -15.0);
    } else {
        temp_r31->gv.kongo.xCC = (f32) (9.0 * HSD_Randf());
    }
    HSD_JObjSetTranslateX(temp_r30, temp_r31->gv.kongo.xCC);
}

bool grKongo_801D6190(Ground_GObj* arg)
{
    return 0;
}

void grKongo_801D6198(Ground_GObj* arg0)
{
    Ground* temp_r3;
    PAD_STACK(8);

    temp_r3 = arg0->user_data;
    switch (temp_r3->gv.kongo3.xC4) {
    case 0:
        if (grAnime_801C83D0(arg0, 0, 1) != 0) {
            Ground_801C2ED0((HSD_JObj*) arg0->hsd_obj, temp_r3->map_id);
            Ground_801C2FE0(arg0);
            if ((enum InternalStageId) temp_r3->map_id == TEST) {
                mpJointListAdd(0);
                mpJointSetCb1(0, temp_r3, fn_801D7E60);
            } else {
                mpJointListAdd(1);
                mpJointSetCb1(1, temp_r3, fn_801D7E60);
            }
            temp_r3->gv.kongo3.xC4 = 1;
        }
        return;
    case 1:
        temp_r3->gv.kongo3.xCA += 1;
        if (temp_r3->gv.kongo3.xC8 == temp_r3->gv.kongo3.xC6) {
            temp_r3->gv.kongo3.xC6 = 0;
            temp_r3->gv.kongo3.xC8 = 0;
        } else {
            temp_r3->gv.kongo3.xC8 = temp_r3->gv.kongo3.xC6;
        }
        if ((temp_r3->gv.kongo3.xC6 > grKg_804D6980->unk88) ||
            (temp_r3->gv.kongo3.xCA > grKg_804D6980->unk8C) ||
            (grKongo_801D7F78(arg0) != 0))
        {
            grAnime_801C8138(arg0, temp_r3->map_id, 1);
            if ((enum InternalStageId) temp_r3->map_id == TEST) {
                mpLib_80057BC0(0);
                mpJointClearCb1(0);
            } else {
                mpLib_80057BC0(1);
                mpJointClearCb1(1);
            }
            temp_r3->gv.kongo3.xC4 = 2;
            return;
        }
        break;
    case 2:
        if (grAnime_801C83D0(arg0, 0, 1) != 0) {
            Ground_801C4A08(arg0);
        }
        break;
    }
}

void grKongo_801D6378(Ground_GObj* arg)
{
    return;
}

void grKongo_801D828C(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    if (gp->gv.kongo3.xC6 != 1) {
        return;
    }
    HSD_ASSERT(1719, gp->gv.kongo.u.taru.keep);
    if (((u8*) gp->gv.kongo.u.taru.keep)[2] == 8) {
        gp->gv.kongo3.xC6 = 0;
        gp->gv.kongo.u.taru.keep = NULL;
        grMaterial_801C95C4(gobj);
    }
}

void grKongo_801D637C(Ground_GObj* arg0)
{
    Ground* temp_r31;
    HSD_JObj* temp_r30;
    PAD_STACK(8);

    temp_r31 = arg0->user_data;
    temp_r30 = arg0->hsd_obj;
    grAnime_801C8138(arg0, temp_r31->map_id, 0);
    grAnime_801C78FC(arg0, 0, 7);
    if (temp_r31->map_id == SHRINE) {
        temp_r31->gv.kongo.xCC = (f32) ((45.0 * HSD_Randf()) + -15.0);
    } else if (temp_r31->map_id == ZEBES) {
        temp_r31->gv.kongo.xCC = (f32) ((20.0 * HSD_Randf()) + -10.0);
    } else {
        temp_r31->gv.kongo.xCC = (f32) (9.0 * HSD_Randf());
    }
    HSD_JObjSetTranslateX(temp_r30, temp_r31->gv.kongo.xCC);
}

bool grKongo_801D64B4(Ground_GObj* arg)
{
    return 0;
}

void grKongo_801D64BC(Ground_GObj* arg0)
{
    if ((grAnime_801C83D0(arg0, 0, 1) != 0) ||
        (grAnime_801C84A4(arg0, 0, 1) != 0))
    {
        Ground_801C4A08(arg0);
    }
}

void grKongo_801D6518(Ground_GObj* arg)
{
    return;
}

typedef struct grKg_801D651C_pair {
    s32 a;
    s32 b;
} grKg_801D651C_pair;

typedef struct grKg_801D651C_pair_list {
    grKg_801D651C_pair pairs[3];
    s32 terminator;
} grKg_801D651C_pair_list;

static const grKg_801D651C_pair_list grKg_803B7FD4 = {
    {
        { 7, 4 },
        { 8, 5 },
        { 9, 6 },
    },
    0,
};

void grKongo_801D651C(Ground_GObj* gobj)
{
    Ground* gp;
    HSD_JObj* jobj;
    Vec3 sp2C;
    grKg_801D651C_pair list[3];
    int i;
    PAD_STACK(8);

    gp = gobj->user_data;
    jobj = gobj->hsd_obj;
    list[0] = grKg_803B7FD4.pairs[0];
    list[1] = grKg_803B7FD4.pairs[1];
    list[2] = grKg_803B7FD4.pairs[2];
    i = HSD_Randi(3);
    gp->gv.kongo2.xC4 = Ground_801C247C(list[i].a, list[i].b);
    gp->gv.kongo2.xC8 = grKg_804DAFA0;
    gp->gv.kongo2.xD0 = grKg_804DAFA0;
    gp->gv.kongo.xCC = grKg_804DAFA0;
    gp->gv.kongo2.xD8 = grKg_804DAFCC;
    gp->gv.kongo2.xDC = grKg_804DAFD0;
    splArcLengthPoint(&sp2C, gp->gv.kongo2.xC4, gp->gv.kongo.xCC);
    HSD_JObjSetTranslate(jobj, &sp2C);
}

bool grKongo_801D6660(Ground_GObj* arg)
{
    return 0;
}

static inline Vec3* lbVector_Diff_t(Vec3* a, Vec3* b, Vec3* result)
{
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
    return result;
}

static inline float lbVector_Len_t(Vec3* vec)
{
    return sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

void grKongo_801D6668(Ground_GObj* arg0)
{
    Vec3 sp5C;
    Vec3 sp50;
    Vec3 sp44;
    Quaternion sp34;
    Vec3 sp28;
    Vec3 sp1C;
    volatile f32 length;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;

    Ground* gp;
    HSD_JObj* jobj;
    f32 step;
    PAD_STACK(12);

    gp = arg0->user_data;
    step = 0.001F;
    jobj = arg0->hsd_obj;

    if ((gp->gv.kongo.xCC + step) <= 1.0) {
        splArcLengthPoint(&sp28, gp->gv.kongo2.xC4, gp->gv.kongo.xCC);
        splArcLengthPoint(&sp1C, gp->gv.kongo2.xC4, gp->gv.kongo.xCC + step);
        dx = sp28.x - sp1C.x;
        dz = sp28.z;
        dz -= sp1C.z;
        dy = sp28.y - sp1C.y;
        dx *= dx;
        dy *= dy;
        dz *= dz;
        dist = dx + dy;
        dist = dz + dist;
        if (dist > 0.0F) {
            f64 guess = __frsqrte(dist);
            guess = 0.5 * guess * (3.0 - (guess * guess * dist));
            guess = 0.5 * guess * (3.0 - (guess * guess * dist));
            guess = 0.5 * guess * (3.0 - (guess * guess * dist));
            length = (f32) ((f64) dist * guess);
            dist = length;
        }
        if (dist > 0.0) {
            step *= grKg_804D6980->unk14 / dist;
            gp->gv.kongo.xCC += step;
            if (gp->gv.kongo.xCC > 1.0) {
                gp->gv.kongo.xCC = 1.0F;
            }
        }
    }
    dx = gp->gv.kongo.xCC;
    Ground_801C4B50(gp->gv.kongo2.xC4, &sp5C, &sp50, dx);
    HSD_JObjGetTranslation(jobj, &sp44);
    HSD_JObjSetTranslate(jobj, &sp5C);
    sp34.x = sp50.x;
    sp34.y = sp50.y;
    sp34.z = sp50.z;
    sp34.w = 1.0f;
    HSD_JObjSetRotation(jobj, &sp34);
    if (gp->gv.kongo.xD8 < sp5C.y) {
        gp->gv.kongo.xD8 = sp5C.y;
    }
    if (gp->gv.kongo2.xDC > sp5C.z) {
        gp->gv.kongo2.xDC = sp5C.z;
    }
    if (((gp->gv.kongo.xD8 - sp44.y) < 5.0f) &&
        ((gp->gv.kongo.xD8 - sp5C.y) > 5.0f))
    {
        Ground_801C5440(gp, 0, 0x5A550U);
        Ground_801C5630(gp, 0, 1.0f - (sp5C.z / gp->gv.kongo2.xDC));
    }
}

void grKongo_801D69AC(Ground_GObj* arg) {}

typedef struct _struct_grKg_803E188C_0x18 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ HSD_JObj* unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} _struct_grKg_803E188C_0x18;

static struct _struct_grKg_803E188C_0x18 grKg_803E188C[0xF] = {
    { 8, 0, NULL, 0.06981317f, 0.0f, 0.0f },
    { 9, 0, NULL, 0.0f, 0.0f, 0.0f },
    { 0xA, 0, NULL, -0.05235988f, 0.0f, 0.0f },
    { 0x17, 0, NULL, -0.10471976f, 0.0f, 0.0f },
    { 0x18, 0, NULL, -0.13962634f, 0.0f, 0.0f },
    { 0x19, 0, NULL, -0.15707964f, 0.0f, 0.0f },
    { 0x1A, 0, NULL, -0.20943952f, 0.0f, 0.0f },
    { 0x1B, 0, NULL, -0.23561944f, 0.0f, 0.0f },
    { 0x1C, 0, NULL, -0.18325958f, 0.0f, 0.0f },
    { 0x1D, 0, NULL, -0.1308997f, 0.0f, 0.0f },
    { 0x1E, 0, NULL, -0.07853982f, 0.0f, 0.0f },
    { 0x1F, 0, NULL, -0.02617994f, 0.0f, 0.0f },
    { 0x20, 0, NULL, 0.0f, 0.0f, 0.0f },
    { 7, 0, NULL, 0.05235988f, 0.0f, 0.0f },
    { 0x2D, 0, NULL, 0.10471976f, 0.0f, 0.0f },
};

char grKg_803E1A00[] = "gp->u.taru.keep";

struct _struct_grKg_804D6984 {
    HSD_JObj* unk0;
    HSD_JObj* unk4;
};

struct _struct_grKg_804D6984 grKg_804D6984;

void grKongo_801D69B0(HSD_GObj* gobj)
{
    f32 rot_x;
    struct _struct_grKg_803E188C_0x18* entry;
    u32 i;

    for (entry = &grKg_803E188C[i = 0U]; i < 0xFU; i += 1, entry += 1) {
        entry->unk4 = Ground_801C3FA4(gobj, (s32) entry->unk0);
        entry->unkC = entry->unk8;
        rot_x = entry->unkC;
        HSD_JObjSetRotationX(entry->unk4, rot_x);
    }
    grKg_804D6984.unk0 = Ground_801C3FA4(gobj, 0xB);
    grKg_804D6984.unk4 = Ground_801C3FA4(gobj, 0x21);
    grKongo_801D7134(gobj, 1);
    grKongo_801D77E0(gobj, 1);
    mpJointSetB10(4);
}

static inline void rad_compare(f32 a, f32 b, f32* ret)
{
    f32 c = deg_to_rad * b;
    if (a > c) {
        *ret = c;
    } else {
        c = -c;
        if (a < c) {
            *ret = c;
        }
    }
}

static inline void rad_compare_b(f32 a, f32 b, f32* ret)
{
    f32 c = deg_to_rad * b;
    if (a > c) {
        c = -c;
    } else if (a < -c) {
    } else {
        c = 0.0F;
    }
    *ret = (f32) (0.99 * (f64) (c + *ret));
}

static inline void rad_compare_c(f32 a, f32 b, f32 d, f32* ret)
{
    f32 c = deg_to_rad * b;
    if (a > c) {
        *ret += d * (a - c);
    } else if (a < -c) {
        *ret += d * (a + c);
    }
}

typedef struct unk_struct_x14 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} unk_struct_x14;

static inline void grKongo_801D6AFC_apply(f32* deltas,
                                          _struct_grKg_803E188C_0x18* entries)
{
    int i;

    for (i = 0; i < 0xF; i++) {
        f32 delta = deltas[i];
        if (delta != 0.0) {
            entries[i].unkC += delta;
        }
    }
}

void grKongo_801D6AFC(void)
{
    f32 sp44[15];
    f32 sp8[15];
    f32* var_r5;
    f32* deltas;
    _struct_grKg_803E188C_0x18* entries;

    s32 var_ctr = 3;
    var_r5 = sp44;
    do {
        var_r5[0] = 0.0f;
        var_r5[1] = 0.0f;
        var_r5[2] = 0.0f;
        var_r5[3] = 0.0f;
        var_r5[4] = 0.0f;
        var_r5 += 5;
        var_ctr -= 1;
    } while (var_ctr != 0);
    var_r5 = sp44;
    entries = grKg_803E188C;
    {
        s32 var_ctr_2 = 5;
        _struct_grKg_803E188C_0x18* var_r3_2 = grKg_803E188C;
        do {
            int i;
            for (i = 0; i < 3; i++) {
                rad_compare_b(var_r3_2->unkC - var_r3_2->unk8,
                              grKg_804D6980->unk94, &var_r3_2->unk10);
                var_r3_2++;
            }
            var_ctr_2 -= 1;
        } while (var_ctr_2 != 0);
    }
    {
        volatile s32 var_ctr_3 = 3;
        _struct_grKg_803E188C_0x18* var_r3_3 = grKg_803E188C;
        f32 temp_f0;
        do {
            var_r3_3->unk10 += var_r5[0];
            var_r3_3[1].unk10 += var_r5[1];
            var_r3_3[2].unk10 += var_r5[2];
            var_r3_3[3].unk10 += var_r5[3];
            temp_f0 = var_r5[4];
            var_r5 += 5;
            var_r3_3[4].unk10 += temp_f0;
            var_r3_3 += 5;
            var_ctr_3 -= 1;
        } while (var_ctr_3 != 0);
    }
    {
        s32 var_ctr_4 = 3;
        _struct_grKg_803E188C_0x18* var_r3_4 = grKg_803E188C;
        do {
            int i;
            for (i = 0; i < 5; i++) {
                rad_compare(var_r3_4->unk10, grKg_804D6980->unk98,
                            &var_r3_4->unk10);
                var_r3_4++;
            }
            var_ctr_4 -= 1;
        } while (var_ctr_4 != 0);
    }
    deltas = sp8;
    {
        s32 var_ctr_5 = 3;
        _struct_grKg_803E188C_0x18* var_r3_5 = grKg_803E188C;
        do {
            int i;
            for (i = 0; i < 5; i++) {
                var_r3_5->unkC += var_r3_5->unk10;
                rad_compare(var_r3_5->unkC, grKg_804D6980->unk90,
                            &var_r3_5->unkC);
                var_r3_5++;
            }
            var_ctr_5 -= 1;
        } while (var_ctr_5 != 0);
    }
    {
        s32 var_ctr_6 = 3;
        f32* delta_init = deltas;
        do {
            delta_init[0] = 0.0f;
            delta_init[1] = 0.0f;
            delta_init[2] = 0.0f;
            delta_init[3] = 0.0f;
            delta_init[4] = 0.0f;
            delta_init += 5;
            var_ctr_6 -= 1;
        } while (var_ctr_6 != 0);
    }
    {
        s32 var_ctr_7 = 0xF;
        _struct_grKg_803E188C_0x18* entry = grKg_803E188C;
        f32* delta_ptr = deltas;
        s32 i = 0;
        do {
            if (entry->unk2 == 0) {
                if ((i != 0) && (entry[-1].unk2 == 0)) {
                    {
                        volatile f32 stiffness = grKg_804D6980->unkA0;
                        rad_compare_c(entry[-1].unkC - entry->unkC,
                                      grKg_804D6980->unk9C, stiffness,
                                      delta_ptr);
                    }
                }
                if (((u32) i != 0xEU) && (entry[1].unk2 == 0)) {
                    {
                        volatile f32 stiffness = grKg_804D6980->unkA0;
                        rad_compare_c(entry[1].unkC - entry->unkC,
                                      grKg_804D6980->unk9C, stiffness,
                                      delta_ptr);
                    }
                }
            }
            entry += 1;
            delta_ptr += 1;
            i += 1;
            var_ctr_7 -= 1;
        } while (var_ctr_7 != 0);
    }
    grKongo_801D6AFC_apply(deltas, entries);
}

#if 0

void grKongo_801D69B0(HSD_GObj *arg0) {
    HSD_JObj *temp_r29;
    f32 temp_f31;
    s32 temp_cr0_eq;
    s32 var_r3;
    struct _struct_grKg_803E188C_0x18 *var_r30;
    u32 temp_r4;
    u32 var_r28;

    var_r28 = 0U;
    var_r30 = &grKg_803E188C[0];
    do {
        var_r30->unk4 = Ground_801C3FA4(arg0, (s32) var_r30->unk0);
        var_r30->unkC = var_r30->unk8;
        temp_r29 = var_r30->unk4;
        temp_f31 = var_r30->unkC;
        temp_r29->rotate.x = temp_f31;
        HSD_JObjSetRotationX(temp_r30, &temp_f31);
        var_r28 += 1;
        var_r30 += 0x18;
    } while (var_r28 < 0xFU);
    grKg_804D6984.unk0 = Ground_801C3FA4(arg0, 0xB);
    grKg_804D6984.unk4 = Ground_801C3FA4(arg0, 0x21);
    grKongo_801D7134(arg0, 1);
    grKongo_801D77E0(arg0, 1);
    mpJointSetB10(4);
}
#endif

#if 0


? ftCo_8009EC70(Vec3 *, s32 *);                     /* extern */
u32 it_802E18B4(HSD_GObj *);                        /* extern */
? it_802E2330(Vec3 *, s32 *);                       /* extern */
? mpLib_8005667C(?);                                /* extern */
? mpVtxGetPos(?, f32 *, ? *);                    /* extern */
? mpLib_80056758(s32, ?, f32, ?, f32);              /* extern */
? ftCo_800C0764(?, s32 (*)(HSD_GObj *, HSD_GObj *)); /* extern */
extern ? grKg_804D6984;
static ? grKg_803B7FB0;                             /* unable to generate initializer: unknown type; const */
#endif

void grKongo_801D7134(HSD_GObj* gobj, s32 arg1)
{
    s32 line_id;
    Ground* gp;
    _struct_grKg_803E188C_0x18* table;
    _struct_grKg_803E188C_0x18* entry;
    HSD_JObj* jobj;
    f32 angle;
    f32 old_angle;
    f32 angular_vel;
    f32 temp;
    f32 displacement;
    u32 i;
    PAD_STACK(0x18);

    gp = gobj->user_data;
    grKongo_801D6AFC();

    for (i = 0U; i < 15U; i++) {
        grKg_803E188C[i].unk14 = (f32) (37.8 * tanf(-grKg_803E188C[i].unkC));
    }

    displacement =
        grKg_803E188C[2].unkC * (((deg_to_rad * grKg_804D6980->unkA8) /
                                  (deg_to_rad * grKg_804D6980->unk90)) -
                                 1.0f);
    angle = (f32) (0.7853981633974483 *
                   (0.5 *
                    (f64) (((grKg_803E188C[2].unk14 - grKg_803E188C[1].unk14) /
                            6.0f) +
                           ((grKg_803E188C[3].unk14 - grKg_803E188C[2].unk14) /
                            6.0f))));
    if (angle > (deg_to_rad * grKg_804D6980->unkAC)) {
        angle = deg_to_rad * grKg_804D6980->unkAC;
    } else if (angle < -(deg_to_rad * grKg_804D6980->unkAC)) {
        angle = -(deg_to_rad * grKg_804D6980->unkAC);
    }
    HSD_JObjSetRotationX(grKg_804D6984.unk0, displacement);
    old_angle = HSD_JObjGetRotationZ(grKg_804D6984.unk0);
    HSD_JObjSetRotationZ(grKg_804D6984.unk0, angle);
    angular_vel = angle - old_angle;
    if (ABS(angular_vel) > (deg_to_rad * grKg_804D6980->unkB0)) {
        gp->gv.kongo.xC8 = -angular_vel;
    }

    displacement =
        grKg_803E188C[12].unkC * (((deg_to_rad * grKg_804D6980->unkA8) /
                                   (deg_to_rad * grKg_804D6980->unk90)) -
                                  1.0f);
    angle =
        (f32) (0.7853981633974483 *
               (0.5 *
                (f64) (((grKg_803E188C[12].unk14 - grKg_803E188C[11].unk14) /
                        6.0f) +
                       ((grKg_803E188C[13].unk14 - grKg_803E188C[12].unk14) /
                        6.0f))));
    if (angle > (deg_to_rad * grKg_804D6980->unkAC)) {
        angle = deg_to_rad * grKg_804D6980->unkAC;
    } else if (angle < -(deg_to_rad * grKg_804D6980->unkAC)) {
        angle = -(deg_to_rad * grKg_804D6980->unkAC);
    }
    HSD_JObjSetRotationX(grKg_804D6984.unk4, displacement);
    old_angle = HSD_JObjGetRotationZ(grKg_804D6984.unk4);
    HSD_JObjSetRotationZ(grKg_804D6984.unk4, angle);
    angular_vel = angle - old_angle;
    if (ABS(angular_vel) > (deg_to_rad * grKg_804D6980->unkB0)) {
        gp->gv.kongo.xD8 = -angular_vel;
    }

    entry = (_struct_grKg_803E188C_0x18*) ((u8*) grKg_803E16E0 + 0x1AC);
    for (i = 0; i < 15; i++) {
        HSD_JObjSetRotationX(entry->unk4, entry->unkC);
        entry++;
    }

    mpLib_80057424(4);
    entry = (_struct_grKg_803E188C_0x18*) ((u8*) grKg_803E16E0 + 0x1AC);
    line_id = 0x28;
    for (i = 0; i < 15; i++) {
        temp = entry->unk14;
        mpLib_80056758(line_id, 0.0f, temp, 0.0f, temp);
        if ((s32) i == 0) {
            mpLib_80056758(line_id - 1, 0.0f, temp, 0.0f, temp);
        } else if (i == 14) {
            mpLib_80056758(line_id + 1, 0.0f, temp, 0.0f, temp);
        }
        line_id += 2;
        entry++;
    }
}

f32 grKongo_801D8314(void)
{
    s32 var_r3;
    f32 var_f31;
    s32 temp_r3 = grKg_804D6980->unk44 + grKg_804D6980->unk46 +
                  grKg_804D6980->unk48 + grKg_804D6980->unk4A +
                  grKg_804D6980->unk4C + grKg_804D6980->unk4E +
                  grKg_804D6980->unk50 + grKg_804D6980->unk52;
    if (temp_r3 != 0) {
        var_r3 = HSD_Randi(temp_r3);
    } else {
        var_r3 = 0;
    }
    {
        s32 temp_r3_2 = var_r3 - grKg_804D6980->unk44;
        if (temp_r3_2 < 0) {
            var_f31 = 2.3561945f;
        } else {
            s32 temp_r3_3 = temp_r3_2 - grKg_804D6980->unk46;
            if (temp_r3_3 < 0) {
                var_f31 = 1.5707964f;
            } else {
                s32 temp_r3_4 = temp_r3_3 - grKg_804D6980->unk48;
                if (temp_r3_4 < 0) {
                    var_f31 = 0.7853982f;
                } else {
                    s32 temp_r3_5 = temp_r3_4 - grKg_804D6980->unk4A;
                    if (temp_r3_5 < 0) {
                        var_f31 = 0.0f;
                    } else {
                        s32 temp_r3_6 = temp_r3_5 - grKg_804D6980->unk4C;
                        if (temp_r3_6 < 0) {
                            var_f31 = -0.7853982f;
                        } else {
                            s32 temp_r3_7 = temp_r3_6 - grKg_804D6980->unk4E;
                            if (temp_r3_7 < 0) {
                                var_f31 = -1.5707964f;
                            } else {
                                s32 temp_r3_8 =
                                    temp_r3_7 - grKg_804D6980->unk50;
                                if (temp_r3_8 < 0) {
                                    var_f31 = -2.3561945f;
                                } else {
                                    temp_r3_8 -= grKg_804D6980->unk52;
                                    if (temp_r3_8 < 0) {
                                        var_f31 = -3.1415927f;
                                    } else {
                                        HSD_ASSERT(1753, 0);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return var_f31;
}

void grKongo_801D5238(bool arg) {}

void grKongo_801D523C(void)
{
    u8* temp_r5;

    grKg_804D6980 = Ground_801C49F8();
    temp_r5 = (u8*) &stage_info.unk8C;
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grKongo_801D5340(0);
    grKongo_801D5340(10);
    grKongo_801D5340(5);
    grKongo_801D5340(3);
    grKongo_801D5340(6);
    grKongo_801D5340(4);
    Ground_801C39C0();
    Ground_801C3BB4();
    mpLib_80057BC0(0);
    mpLib_80057BC0(1);
    if ((Stage_80225194() != 0x3D) && (gm_8016B238() == 0)) {
        Ground_801C53EC(0x5A551U);
    }
}

void grKongo_801D52F8(void) {}

void grKongo_801D52FC(void)
{
    HSD_GObj* gobj = Ground_801C2BA4(5);
    ftCo_800C0764(gobj, 2, fn_801D8134);
    grZakoGenerator_801CAE04(NULL);
}

bool grKongo_801D5338(void)
{
    return 0;
}

HSD_GObj* grKongo_801D5340(s32 gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grKg_803E1704[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }
        // 0x80
        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }
        // 0x94
        if (callbacks->callback2 != NULL) {
            HSD_GObj_SetupProc(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport((char*) grKg_803E16E0 + 0x154, grKg_803E1858, 0x10E, gobj_id);
    }
    return gobj;
}

void fn_801D542C(HSD_GObj* arg0)
{
    Ground* gp;
    f32 range;
    f32 rand;
    f32 min;

    gp = arg0->user_data;
    mpJointSetCb1(4, gp, fn_801D7700);
    rand = HSD_Randf();
    min = grKg_804D6980->unk0;
    range = grKg_804D6980->unk4 - min;
    gp->gv.kongo.xE4 = (s16) ((range * rand) + min);
}

/// #grKongo_801D5490

/// #grKongo_801D5574

/// #grKongo_801D557C

/// #grKongo_801D55D4

/// #grKongo_801D55D8

/// #grKongo_801D5774

/// #grKongo_801D577C

/// #grKongo_801D5FA4

/// #grKongo_801D5FA8

/// #grKongo_801D5FD4

/// #grKongo_801D5FDC

/// #grKongo_801D5FE0

/// #grKongo_801D5FE4

/// #grKongo_801D6028

/// #grKongo_801D6030

/// #grKongo_801D6034

/// #grKongo_801D6038

/// #grKongo_801D6064

/// #grKongo_801D606C

/// #grKongo_801D6070

/// #grKongo_801D6074

/// #grKongo_801D6190

/// #grKongo_801D6198

/// #grKongo_801D6378

/// #grKongo_801D637C

/// #grKongo_801D64B4

/// #grKongo_801D64BC

/// #grKongo_801D6518

/// #grKongo_801D651C

/// #grKongo_801D6660

/// #grKongo_801D6668

/// #grKongo_801D69AC

/// #grKongo_801D69B0

/// #grKongo_801D6AFC

/// #grKongo_801D7134

static void fn_801D7700(Ground* gp, s32 arg1, CollData* cd, s32 arg3,
                        mpLib_GroundEnum arg4, float arg8)
{
    s32 idx;
    s32 idx2;
    f32 ratio;
    Vec3* cur = &cd->cur_pos;
    s32 type = cd->x34_flags.b1234;
    f32 segment_size;
    f32 x1;
    f32 y1;
    f32 x2;
    f32 y2;

    if (type == 1 || type == 3) {
        if (arg4 == mpLib_GroundEnum_Unk1) {
            mpVtxGetPos(0x1D, &x1, &y1);
            mpVtxGetPos(0x1A, &x2, &y2);

            {
                segment_size = (x2 - x1) / 15.0F;
                ratio = (cur->x - x1) / segment_size;
                idx2 = (s32) ratio;
                idx = (s32) ratio;

                if (idx < 0) {
                    idx2 = 0;
                } else if ((u32) idx2 >= 15) {
                    idx2 = 14;
                }

                grKg_803E188C[idx2].unk10 +=
                    0.017453292F * grKg_804D6980->unkA4;
            }
        }
    }
}

void grKongo_801D77E0(HSD_GObj* gobj, s32 arg1)
{
    Ground* gp = gobj->user_data;
    s32 i;
    f32 v;
    f32 limit;
    f32 step;

    if (arg1 != 0) {
        gp->gv.kongo.xC4 = 0.0f;
        gp->gv.kongo.xC8 = 0.0f;
        gp->gv.kongo.xD4 = 0.0f;
        gp->gv.kongo.xD8 = 0.0f;
    } else {
        Ground* q = gp;
        for (i = 2; i != 0; i--) {
            if (q->gv.kongo.xC4 > 0.0f) {
                if (q->gv.kongo.xC8 > 0.0f) {
                    step = 0.017453292f * grKg_804D6980->unkB4;
                } else {
                    step = 0.017453292f * grKg_804D6980->unkB4 * 0.5f;
                }
                q->gv.kongo.xC8 -= step;
            } else if (q->gv.kongo.xC4 < 0.0f) {
                if (q->gv.kongo.xC8 < 0.0f) {
                    step = 0.017453292f * grKg_804D6980->unkB4;
                } else {
                    step = 0.017453292f * grKg_804D6980->unkB4 * 0.5f;
                }
                q->gv.kongo.xC8 += step;
            }
            q->gv.kongo.xC4 += q->gv.kongo.xC8;
            v = q->gv.kongo.xC4;
            limit = 0.017453292f * (grKg_804D6980->unkB8 -
                                    0.017453292f * grKg_804D6980->unkAC);
            if (v > limit) {
                q->gv.kongo.xC4 = limit;
                q->gv.kongo.xC8 = 0.0f;
            } else if (v < -limit) {
                q->gv.kongo.xC4 = -limit;
                q->gv.kongo.xC8 = 0.0f;
            } else {
                f32 av = (v < 0.0f) ? -v : v;
                if (av < 0.017453292f * grKg_804D6980->unkB4) {
                    f32 av2 = (q->gv.kongo.xC8 < 0.0f) ? -q->gv.kongo.xC8
                                                       : q->gv.kongo.xC8;
                    if (av2 < 0.017453292f * grKg_804D6980->unkB4) {
                        q->gv.kongo.xC4 = 0.0f;
                        q->gv.kongo.xC8 = 0.0f;
                    }
                }
            }
            q = (Ground*) ((u8*) q + 0x10);
        }
    }
    HSD_JObjSetRotationZ(gp->gv.kongo3.xCC, gp->gv.kongo.xC4);
    HSD_JObjSetRotationZ(gp->gv.kongo3.xD0, gp->gv.kongo.xC4);
    HSD_JObjSetRotationZ(gp->gv.kongo.xDC, gp->gv.kongo.xD4);
    HSD_JObjSetRotationZ(gp->gv.kongo.xE0, gp->gv.kongo.xD4);
}

void grKongo_801D7BBC(HSD_GObj* gobj)
{
    HSD_GObj* obj;
    s32 item_kind;
    s32 event_kind;
    Ground* gp;
    f32 roll;
    f32 box_weight;
    s32 rand_kind;

    gp = gobj->user_data;

    if (gp->gv.kongo.xE4 > 0) {
        gp->gv.kongo.xE4 -= 1;
    }
    if (gp->gv.kongo.xE4 == -1) {
        return;
    }
    if (gp->gv.kongo.xE4 != 0) {
        return;
    }

    event_kind = gm_8016B238() == 0 && it_8026D324(It_Kind_Box) != 0;
    if (event_kind != 0) {
        roll = grKg_804D6980->unkC;
    } else {
        roll = grKg_804DAFA0;
    }
    {
        f32 rand = HSD_Randf();
        roll = rand *
               (grKg_804D6980->unk10 * (grKg_804DAFA4 - grKg_804D6980->unk18) +
                (grKg_804D6980->unk10 * grKg_804D6980->unk18 +
                 (grKg_804D6980->unk8 + roll)));
    }
    {
        f32 r = HSD_Randf();
        f32 delta = grKg_804D6980->unk4 - grKg_804D6980->unk0;
        gp->gv.kongo.xE4 = (s16) (delta * r + grKg_804D6980->unk0);
    }
    roll -= grKg_804D6980->unk8;
    if (roll < grKg_804DAFA0) {
        event_kind = 1;
    } else {
        s32 flag = 0;
        if (gm_8016B238() == 0 && it_8026D324(It_Kind_Box) != 0) {
            flag = 1;
        }
        if (flag != 0) {
            box_weight = grKg_804D6980->unkC;
        } else {
            box_weight = grKg_804DAFA0;
        }
        roll -= box_weight;
        {
            f32 zero = grKg_804DAFA0;
            if (roll < zero) {
                event_kind = 2;
            } else {
                f32 base_weight = grKg_804D6980->unk10;
                f32 box_rate = grKg_804D6980->unk18;
                f32 prod = base_weight * box_rate;
                roll -= prod;
                if (roll < zero) {
                    if (HSD_Randi(2) != 0) {
                        item_kind = 1;
                    } else {
                        item_kind = 2;
                    }
                    event_kind = 3;
                } else {
                    roll -= base_weight * (grKg_804DAFA4 - box_rate);
                    if (roll < zero) {
                        rand_kind = HSD_Randi(3);
                        if (rand_kind == 0) {
                            item_kind = 7;
                        } else if (rand_kind == 1) {
                            item_kind = 8;
                        } else {
                            item_kind = 9;
                        }
                        event_kind = 3;
                    } else {
                        return;
                    }
                }
            }
        }
    }

    if (gp->gv.kongo.xE6 == event_kind && HSD_Randf() > grKg_804D6980->unk1C) {
        return;
    }
    gp->gv.kongo.xE6 = event_kind;
    switch (event_kind) {
    case 1:
        obj = grKongo_801D5340(0xB);
        if (obj != NULL && it_802E18B4((Item_GObj*) obj) == NULL) {
            Ground_801C4A08(obj);
        }
        break;
    case 2:
        obj = grKongo_801D5340(0xB);
        if (obj != NULL && it_80286088((Item_GObj*) obj) == NULL) {
            Ground_801C4A08(obj);
        }
        break;
    case 3:
        grKongo_801D5340(item_kind);
        break;
    }
}

void fn_801D7E60(Ground* gp, s32 arg1, CollData* arg2, s32 arg3,
                 mpLib_GroundEnum arg4, float arg8)
{
    if (arg4 == mpLib_GroundEnum_Unk2) {
        gp->gv.kongo3.xC6 = gp->gv.kongo3.xC8 + 1;
    }
}

Vec3* grKongo_801D7E78(HSD_GObj* gobj, Vec3* pos)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj;
    PAD_STACK(8);

    if (gp != NULL) {
        if (gp->map_id == TEST || gp->map_id == CASTLE ||
            gp->map_id == SHRINE || gp->map_id == ZEBES || gp->map_id == KRAID)
        {
            jobj = Ground_801C3FA4(gobj, 2);
            if (jobj != NULL) {
                lb_8000B1CC(jobj, NULL, pos);
                goto done;
            }
            return NULL;
        }
        if (gp->map_id == YORSTER) {
            jobj = gobj->hsd_obj;
            if (jobj != NULL) {
                HSD_JObjGetTranslation(jobj, pos);
                goto done;
            }
            return NULL;
        }
        return NULL;
    }
    return NULL;

done:
    return pos;
}

bool grKongo_801D7F78(HSD_GObj* gobj)
{
    double _pre;
    Vec3 pos1;
    Vec3 pos2;
    HSD_GObj* cur;
    PAD_STACK(12);

    if (grKongo_801D7E78(gobj, &pos1) == NULL) {
        return false;
    }

    for (cur = HSD_GObj_Entities->x14; cur != NULL; cur = cur->next) {
        if (cur == gobj) {
            continue;
        }
        if (grKongo_801D7E78(cur, &pos2) == NULL) {
            continue;
        }
        {
            f32 dz = pos2.z - pos1.z;
            if (dz < -100.0F) {
                if (dz > -150.0F) {
                    f32 dx = pos2.x - pos1.x;
                    if (dx * dx < 6400.0F) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void grKongo_801D8058(Ground_GObj* arg)
{
    Ground_801C4A08(arg);
}

HSD_GObj* grKongo_801D8078(HSD_GObj* gobj)
{
    s32 unused1;
    Vec3 pos;
    f32 unk;
    Vec3 item_pos;
    HSD_GObj* cur;
    Ground_801C4DA0(&pos, &unk);

    for (cur = HSD_GObj_Entities->items; cur != NULL; cur = cur->next) {
        if (itGetKind(cur) == 0xDA) {
            f32 dx, dy, dz, dx2, dy2, dz2, r;

            it_8026B294(cur, &item_pos);

            dx = pos.x - item_pos.x;
            dz = pos.z - ((0, item_pos.z));
            dy = pos.y - item_pos.y;
            dx2 = dx * dx;
            dy2 = dy * dy;
            dz2 = dz * dz;
            r = grKg_804D6980->unk28;

            if (dx2 + dy2 + dz2 < r * r) {
                return cur;
            }
        }
    }

    return NULL;
}

static int fn_801D8134(HSD_GObj* arg0, HSD_GObj* arg1)
{
    Ground* gp;
    Vec3 pos_gnd;
    Vec3 pos_ft;
    f32 unk;
    f32 rand_val;
    f32 diff;

    gp = GET_GROUND(arg0);

    if (gp->gv.kongo3.xC6 != 0) {
        goto done;
    }

    Ground_801C4DA0(&pos_gnd, &unk);
    ftLib_80086644(arg1, &pos_ft);

    if (!((pos_gnd.x - pos_ft.x) * (pos_gnd.x - pos_ft.x) +
              (pos_gnd.y - pos_ft.y) * (pos_gnd.y - pos_ft.y) +
              (pos_gnd.z - pos_ft.z) * (pos_gnd.z - pos_ft.z) <
          grKg_804D6980->unk28 * grKg_804D6980->unk28))
    {
        goto done;
    }

    rand_val = HSD_Randf();
    diff = grKg_804D6980->unk24 - grKg_804D6980->unk20;
    gp->gv.kongo3.xCA = (s16) (diff * rand_val + grKg_804D6980->unk20);
    gp->gv.kongo3.xD0 = (HSD_JObj*) arg1;
    gp->gv.kongo3.xC6 = 1;
    Ground_801C5440(gp, 0, 0x129U);
    grMaterial_801C9604(arg0, grKg_804D6980->unk84, 0);
    efSync_Spawn(0x405, arg0, &pos_ft);
    ftLib_80086C18(arg1, 0xD, 0x1E);
    return 1;
done:
    return 0;
}

void grKongo_801D8270(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->gv.inishie2.xC6 == 1) {
        gp->gv.inishie2.xC6 = 2;
    }
}

/// #grKongo_801D828C

/// #grKongo_801D8314

DynamicsDesc* grKongo_801D8444(enum_t arg)
{
    return false;
}

bool grKongo_801D844C(Vec3* a, int b, HSD_JObj* jobj)
{
    Vec3 vec;
    lb_8000B1CC(jobj, NULL, &vec);
    if (a->y > vec.y) {
        return true;
    } else {
        return false;
    }
}
