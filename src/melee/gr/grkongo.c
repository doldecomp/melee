#include "gr/grkongo.h"

#include "grkongo.static.h"

#include "grmaterial.h"
#include "types.h"

#include "gm/gm_unsplit.h"
#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "it/items/itklap.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include "mp/forward.h"

#include "mp/mplib.h"
#include "MSL/math.h"
#include "MSL/math_ppc.h" // IWYU pragma: keep

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/random.h>
#include <baselib/spline.h>

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

// @todo: Investigate these types of patterns in
// other files; the Randi check with zero is probably
// its own thing
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

static inline s32 random_adder_f(f32 temp_f0, f32 temp_f2)
{
#if 1
    s32 temp_r28_2;
    s32 var_r29;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 var_r3;
    s32 var_r3_2;
    temp_r28_2 = (s32) temp_f0;
    var_r29 = (s32) temp_f2;
    if ((s32) temp_f2 > (s32) temp_f0) {
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
#else
    s32 temp_s0 = temp_f0;
    s32 temp_s2 = temp_f2;
    if (temp_s2 > temp_s0) {
        return random_adder_b(temp_s2, temp_s0);
    } else if (temp_s2 < temp_s0) {
        return random_adder_b(temp_s0, temp_s2);
    }
    // return random_adder(temp_f0, temp_f2);
#endif
}

void grKongo_801D55D8(Ground_GObj* arg0)
{
    Vec3 sp14;
    Ground* temp_r31;
    void* temp_r28;

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
        random_adder_f(grKg_804D6980->unk2C, grKg_804D6980->unk30);
    temp_r31->gv.kongo2.xCE =
        random_adder(grKg_804D6980->unk68, grKg_804D6980->unk64);
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

static inline void grKongo_801D577C_inline(Ground* temp_r31, f32 temp_f3_2,
                                           bool sign)
{
    f32 temp_f0 = DegToRad(grKg_804D6980->unk34);
    bool compare = sign ? (temp_f3_2 < temp_f0) : (temp_f3_2 > -temp_f0);
    if (compare) {
        temp_r31->gv.kongo3.xE0 = 0.0f;
        temp_r31->gv.kongo3.xD8 = temp_r31->gv.kongo3.xD4;
    } else {
        temp_r31->gv.kongo3.xE0 = temp_f3_2 - (sign ? temp_f0 : -temp_f0);
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

static inline f32 tau_range(f32 a)
{
    if (a > (f32) M_TAU) {
        return (f64) a - M_TAU;
    } else if (a < (f32) -M_TAU) {
        return (f64) a + M_TAU;
    }
    return 0.0F;
}

void grKongo_801D577C(Ground_GObj* arg0)
{
    Ground* temp_r31 = arg0->user_data;
    HSD_JObj* temp_r30 = Ground_801C3FA4(arg0, 1);
    f32 var_f30;

    f32 temp_f3;
    f32 temp_f31;
    f32 var_f1;
    f32 var_f0;
    HSD_GObj* temp_r3_9;
    Vec3 vec;

    switch (temp_r31->gv.kongo3.xC4) {
    default:
        temp_f3 = temp_r31->gv.kongo3.xE0;
        temp_f31 =
            0.5f * (temp_f3 * (temp_f3 / DegToRad(grKg_804D6980->unk34)));
        if (temp_f3 > 0.0f) {
            var_f30 = temp_r31->gv.kongo3.xD4 - temp_r31->gv.kongo3.xD8;
        } else if (temp_f3 < 0.0f) {
            var_f30 = temp_r31->gv.kongo3.xD8 - temp_r31->gv.kongo3.xD4;
        } else {
            __assert("grkongo.c", 505, "0");
        }
        if (var_f30 < 0.0f) {
            var_f30 = (f32) ((f64) var_f30 + M_TAU);
        }
        if (!(var_f30 < temp_f31)) {
            var_f1 = temp_r31->gv.kongo3.xE0;
            if (var_f1 < 0.0f) {
                var_f1 = -var_f1;
            }
            if (var_f30 < var_f1) {
                // weird
                if ((s16) temp_r31->gv.kongo3.xC4 == 3) {
                    temp_r31->gv.kongo3.xC4 = 0;
                }
            }
            if ((s16) temp_r31->gv.kongo3.xC4 == 2) {
                temp_r31->gv.kongo3.xC4 = 3;
            }
        } else {
            if ((s16) temp_r31->gv.kongo3.xC4 == 3) {
                temp_r31->gv.kongo3.xC4 = 0;
            }
        }
        break;
    case 0:
        if (temp_r31->gv.kongo3.xE0 > 0.0f) {
            grKongo_801D577C_inline(temp_r31, temp_r31->gv.kongo3.xE0, 1);
        } else if (temp_r31->gv.kongo3.xE0 < 0.0f) {
            grKongo_801D577C_inline(temp_r31, temp_r31->gv.kongo3.xE0, 0);
        }
        temp_r31->gv.kongo2.xCC -= 1;
        if ((s16) temp_r31->gv.kongo2.xCC < 0) {
            temp_r31->gv.kongo3.xC4 = 1;
            if (HSD_Randi(2) != 0) {
                var_f0 = DegToRad(grKg_804D6980->unk34);
            } else {
                var_f0 = -DegToRad(grKg_804D6980->unk34);
            }
            temp_r31->gv.kongo3.xDC = var_f0;
            temp_r31->gv.kongo2.xCC =
                random_adder_f(grKg_804D6980->unk3C, grKg_804D6980->unk40);
        }
        break;
    case 1:
        temp_r31->gv.kongo3.xE0 += temp_r31->gv.kongo3.xDC;
        // double_compare(&temp_r31->gv.kongo3.xE0, 0.017453292f *
        // grKg_804D6980->unk38);
        temp_r31->gv.kongo2.xCC -= 1;
        if (temp_r31->gv.kongo2.xCC < 0) {
            temp_r31->gv.kongo3.xC4 = 2;
            temp_r31->gv.kongo2.xCC =
                random_adder_f(grKg_804D6980->unk2C, grKg_804D6980->unk30);
            temp_r31->gv.kongo3.xD4 = grKongo_801D8314();
        }
        break;
    }
    temp_r31->gv.kongo3.xD8 += temp_r31->gv.kongo3.xE0;
    temp_r31->gv.kongo3.xD8 = tau_range(temp_r31->gv.kongo3.xD8);
    HSD_JObjSetRotationZ(temp_r30, temp_r31->gv.kongo.xD8);
    lb_8000B1CC(temp_r30, NULL, &vec);
    Ground_801C4D70(arg0, &vec, temp_r31->gv.kongo3.xD8);
    switch (temp_r31->gv.kongo3.xC8) {
    case 0: {
        s16 val = temp_r31->gv.kongo2.xCE;
        temp_r31->gv.kongo2.xCE -= 1;
        if (val < 0) {
            temp_r31->gv.kongo2.xC8 = 1;
        }
    } break;
    case 1:
        temp_r31->gv.kongo2.xE8 += grKg_804D6980->unk5C;
        if (temp_r31->gv.kongo2.xE8 > grKg_804D6980->unk60) {
            temp_r31->gv.kongo2.xE8 = grKg_804D6980->unk60;
            temp_r31->gv.kongo2.xCE =
                random_adder(grKg_804D6980->unk68, grKg_804D6980->unk64);
            temp_r31->gv.kongo2.xC8 = 2;
        }
        break;
    case 2:
        temp_r31->gv.kongo2.xCE -= 1;
        if (temp_r31->gv.kongo2.xCE < 0) {
            temp_r31->gv.kongo2.xC8 = 3;
        }
        break;
    case 3:
        temp_r31->gv.kongo2.xE8 -= grKg_804D6980->unk5C;
        if (temp_r31->gv.kongo2.xE8 < 0.0f) {
            temp_r31->gv.kongo2.xE8 = 0.0f;
            temp_r31->gv.kongo2.xCE =
                random_adder(grKg_804D6980->unk58, grKg_804D6980->unk54);
            temp_r31->gv.kongo2.xC8 = 0;
        }
        break;
    }
    grAnime_801C7A04(arg0, 0, 7, temp_r31->gv.kongo3.xE8);

    switch (temp_r31->gv.kongo3.xC6) {
    case 0: /* switch 2 */
        temp_r3_9 = grKongo_801D8078(arg0);
        if (temp_r3_9 != NULL) {
            it_802E20D8(temp_r3_9);
            temp_r31->gv.kongo3.xCA =
                ((grKg_804D6980->unk24 - grKg_804D6980->unk20) * HSD_Randf()) +
                grKg_804D6980->unk20;
            temp_r31->gv.kongo.u.taru.keep = temp_r3_9;
            temp_r31->gv.kongo3.xC6 = 1;
            Ground_801C5440(temp_r31, 0, 0x129U);
            grMaterial_801C9604(arg0, grKg_804D6980->unk84, 0);
            return;
        }
        return;
    case 1:
        if (temp_r31->gv.kongo.u.taru.keep == NULL) {
            temp_r31->gv.kongo3.xC6 = 0;
#if 0
            goto block_124;
#endif
        }
        temp_r31->gv.kongo3.xCA -= 1;
        if (temp_r31->gv.kongo3.xCA < 0) {
            temp_r31->gv.kongo3.xC6 = 2;
        case 2: /* switch 2 */
#if 0
block_124:
            sp10 = grKg_803B7FB0.unk0;
            sp14 = grKg_803B7FB0.unk4;
            sp18 = grKg_803B7FB0.unk8;
            sp1C = grKg_803B7FB0.unkC;
            sp20 = grKg_803B7FB0.unk10;
            sp24 = grKg_803B7FB0.unk14;
            sp28 = grKg_803B7FB0.unk18;
            sp2C = grKg_803B7FB0.unk1C;
            sp30 = grKg_803B7FB0.unk20;
            sp10 = 1;
            sp14 = grKg_804D6980->unk6C;
            sp18 = grKg_804D6980->unk70;
            sp1C = grKg_804D6980->unk74;
            sp20 = grKg_804D6980->unk78;
            sp24 = grKg_804D6980->unk7C;
            sp28 = grKg_804D6980->unk80;
            temp_f1_3 = (f32) (1.5707963267948966 + (f64) temp_r31->gv.kongo3.xD8);
            if (temp_f1_3 < 0.0f) {

            } else if (temp_f1_3 > (bitwise f32) M_TAU) {

            }
            temp_r0_4 = temp_r31->gv.kongo3.u.taru.keep->unk2;
            if (temp_r0_4 == 8) {
                ftCo_8009EC70(&sp38, &sp10);
            } else if (temp_r0_4 == 9) {
                it_802E2330(&sp38, &sp10);
            }
            temp_r31->gv.kongo3.xC6 = 3;
            grMaterial_801C95C4(arg0);
            return;
        }
#endif
            break;
        case 3: /* switch 2 */
            if (grKongo_801D8078(arg0) == NULL) {
                temp_r31->gv.kongo3.xC6 = 0;
            }
            break;
        }
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
    if ((enum InternalStageId) temp_r31->map_id == InternalStageID_Unk01) {
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
            if ((enum InternalStageId) temp_r3->map_id ==
                InternalStageID_Unk01)
            {
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
            if ((enum InternalStageId) temp_r3->map_id ==
                InternalStageID_Unk01)
            {
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

static const s32 grKg_803B7FD4[7] = { 7, 4, 8, 5, 9, 6, 0 };

void grKongo_801D651C(Ground_GObj* gobj)
{
    Vec3 sp2C;
    s32 list[6];
    int i;

    Ground* temp_r30 = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;
    list[0] = grKg_803B7FD4[0];
    list[1] = grKg_803B7FD4[1];
    list[2] = grKg_803B7FD4[2];
    list[3] = grKg_803B7FD4[3];
    list[4] = grKg_803B7FD4[4];
    list[5] = grKg_803B7FD4[5];
    i = HSD_Randi(3) * 8;
    temp_r30->gv.kongo2.xC4 = Ground_801C247C(list[i], list[i + 1]);
    temp_r30->gv.kongo2.xC8 = 0.0f;
    temp_r30->gv.kongo2.xD0 = 0.0f;
    temp_r30->gv.kongo.xCC = 0.0f;
    temp_r30->gv.kongo2.xD8 = -99999.0f;
    temp_r30->gv.kongo2.xDC = 3.4028235e38f;
    splArcLengthPoint(&sp2C, temp_r30->gv.kongo2.xC4, temp_r30->gv.kongo.xCC);
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
    f32 sp18;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f3;
    f32 var_f4;
    f64 temp_f1_3;
    f64 temp_f1_4;
    f64 temp_f1_5;
    s32 temp_cr0_eq;
    s32 temp_cr0_eq_2;
    s32 var_r3;
    s32 var_r3_2;
    u32 temp_r4_2;
    u32 temp_r4_3;

    Ground* temp_r4;
    HSD_JObj* temp_r30;
    f32 len;
    Vec3 vec;
    PAD_STACK(8);

    temp_r4 = arg0->user_data;
    temp_r30 = arg0->hsd_obj;

    if ((temp_r4->gv.kongo.xCC + 0.001F) <= 1.0F) {
        splArcLengthPoint(&sp28, temp_r4->gv.kongo2.xC4,
                          temp_r4->gv.kongo.xCC);
        splArcLengthPoint(&sp1C, temp_r4->gv.kongo2.xC4,
                          temp_r4->gv.kongo.xCC + 0.001F);
        len = lbVector_Len_t(lbVector_Diff_t(&sp28, &sp1C, &vec));
        if (len > 0.0F) {
            temp_r4->gv.kongo.xCC += 0.001F * (grKg_804D6980->unk14 / len);
            if (temp_r4->gv.kongo.xCC > 1.0F) {
                temp_r4->gv.kongo.xCC = 1.0F;
            }
        }
#if 0
        temp_f2 = (bitwise f32) sp28 - (bitwise f32) sp1C;
        temp_f1_2 = sp28.y - sp1C.y;
        temp_f3 = sp28.z - sp1C.z;
        var_f4 = (temp_f3 * temp_f3) + ((temp_f2 * temp_f2) + (temp_f1_2 * temp_f1_2));
        if (var_f4 > 0.0F) {
            temp_f1_3 = __frsqrte(var_f4);
            temp_f1_4 = 0.5F * temp_f1_3 * -(((f64) var_f4 * (temp_f1_3 * temp_f1_3)) - 3.0F);
            temp_f1_5 = 0.5F * temp_f1_4 * -(((f64) var_f4 * (temp_f1_4 * temp_f1_4)) - 3.0F);
            sp18 = (f32) ((f64) var_f4 * (0.5F * temp_f1_5 * -(((f64) var_f4 * (temp_f1_5 * temp_f1_5)) - 3.0F)));
            var_f4 = sp18;
        }
#endif
    }
    Ground_801C4B50(temp_r4->gv.kongo2.xC4, &sp5C, &sp50,
                    temp_r4->gv.kongo.xCC);
    HSD_JObjGetTranslation(temp_r30, &sp44);
    HSD_JObjSetTranslate(temp_r30, &sp5C);
    sp34.x = sp50.x;
    sp34.y = sp50.y;
    sp34.z = sp50.z;
    sp34.w = 1.0f;
    HSD_JObjSetRotation(temp_r30, &sp34);
    if (temp_r4->gv.kongo.xD8 < sp50.y) {
        temp_r4->gv.kongo.xD8 = sp50.y;
    }
    if (temp_r4->gv.kongo2.xDC > sp50.z) {
        temp_r4->gv.kongo2.xDC = sp50.z;
    }
    if (((temp_r4->gv.kongo.xD8 - sp44.x) < 5.0f) &&
        ((temp_r4->gv.kongo.xD8 - sp5C.x) > 5.0f))
    {
        Ground_801C5440(temp_r4, 0, 0x5A550U);
        Ground_801C5630(temp_r4, 0, 1.0f - (sp5C.x / temp_r4->gv.kongo2.xDC));
    }
}

void grKongo_801D69AC(Ground_GObj* arg) {}

typedef struct _struct_grKg_803E188C_0x18 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ HSD_JObj* unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} _struct_grKg_803E188C_0x18;

static struct _struct_grKg_803E188C_0x18 grKg_803E188C[0xF] = {
    { 8, NULL, 0.06981317f, 0.0f, 0.0f },
    { 9, NULL, 0.0f, 0.0f, 0.0f },
    { 0xA, NULL, -0.05235988f, 0.0f, 0.0f },
    { 0x17, NULL, -0.10471976f, 0.0f, 0.0f },
    { 0x18, NULL, -0.13962634f, 0.0f, 0.0f },
    { 0x19, NULL, -0.15707964f, 0.0f, 0.0f },
    { 0x1A, NULL, -0.20943952f, 0.0f, 0.0f },
    { 0x1B, NULL, -0.23561944f, 0.0f, 0.0f },
    { 0x1C, NULL, -0.18325958f, 0.0f, 0.0f },
    { 0x1D, NULL, -0.1308997f, 0.0f, 0.0f },
    { 0x1E, NULL, -0.07853982f, 0.0f, 0.0f },
    { 0x1F, NULL, -0.02617994f, 0.0f, 0.0f },
    { 0x20, NULL, 0.0f, 0.0f, 0.0f },
    { 7, NULL, 0.05235988f, 0.0f, 0.0f },
    { 0x2D, NULL, 0.10471976f, 0.0f, 0.0f },
};

struct _struct_grKg_804D6984 {
    HSD_JObj* unk0;
    HSD_JObj* unk4;
};

struct _struct_grKg_804D6984 grKg_804D6984;

void grKongo_801D69B0(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    f32 temp_f31;
    s32 temp_cr0_eq;
    s32 var_r3;
    struct _struct_grKg_803E188C_0x18* var_r30;
    u32 temp_r4;
    u32 var_r28;

    var_r28 = 0U;
    var_r30 = &grKg_803E188C[0];
    do {
        var_r30->unk4 = Ground_801C3FA4(gobj, (s32) var_r30->unk0);
        var_r30->unkC = var_r30->unk8;
        jobj = var_r30->unk4;
        temp_f31 = var_r30->unkC;
        HSD_JObjSetRotationX(jobj, temp_f31);
        var_r28 += 1;
        var_r30 += 0x18;
    } while (var_r28 < 0xFU);
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

void grKongo_801D6AFC(void)
{
    unk_struct_x14 sp44;
    f32 sp8;
    unk_struct_x14* var_r3;
    unk_struct_x14* var_r5;
    _struct_grKg_803E188C_0x18* var_r6;

    s32 var_ctr = 3;
    var_r5 = &sp44;
    var_r3 = var_r5;
    do {
        var_r3->unk0 = 0.0f;
        var_r3->unk4 = 0.0f;
        var_r3->unk8 = 0.0f;
        var_r3->unkC = 0.0f;
        var_r3->unk10 = 0.0f;
        var_r3 += 1;
        var_ctr -= 1;
    } while (var_ctr != 0);
    var_r6 = grKg_803E188C;
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
        s32 var_ctr_3 = 3;
        _struct_grKg_803E188C_0x18* var_r3_3 = grKg_803E188C;
        f32 temp_f0;
        do {
            var_r3_3->unk10 += var_r5->unk0;
            var_r3_3[1].unk10 += var_r5->unk4;
            var_r3_3[2].unk10 += var_r5->unk8;
            var_r3_3[3].unk10 += var_r5->unkC;
            temp_f0 = var_r5->unk10;
            var_r5 += 0x14;
            var_r3_3[4].unk10 += temp_f0;
            var_r3_3 += 0x78;
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
#if 0
    var_r7 = &sp8;
    {
        var_ctr_6 = 3;
        var_r3_6 = var_r7;
        do {
            var_r3_6->unk0 = 0.0f;
            var_r3_6->unk4 = 0.0f;
            var_r3_6->unk8 = 0.0f;
            var_r3_6->unkC = 0.0f;
            var_r3_6->unk10 = 0.0f;
            var_r3_6 += 0x14;
            var_ctr_6 -= 1;
        } while (var_ctr_6 != 0);
    }
    var_ctr_7 = 0xF;
    var_r3_7 = grKg_803E188C;
    var_r4 = var_r7;
    var_r8 = 0;
    do {
        if ((s16) var_r3_7->unk2 == 0) {
            if ((var_r8 != 0) && ((s16) var_r3_7->unk-16 == 0)) {
                rad_compare_c(var_r3_7[1]->unkC - var_r3_7->unkC, grKg_804D6980->unk9C,
                       grKg_804D6980->unkA0, var_r4);
            }
            if (((u32) var_r8 != 0xEU) && ((s16) var_r3_7[1].unk2 == 0)) {
                rad_compare_c(var_r3_7[1]->unkC - var_r3_7->unkC, grKg_804D6980->unk9C,
                       grKg_804D6980->unkA0, var_r4);
            }
        }
        var_r3_7 += 0x18;
        var_r4 += 4;
        var_r8 += 1;
        var_ctr_7 -= 1;
    } while (var_ctr_7 != 0);
    var_ctr_8 = 3;
    do {
        temp_f2_11 = var_r7->unk0;
        if ((bitwise f32) 0.0 != temp_f2_11) {
            var_r6->unkC += temp_f2_11;
        }
        temp_f2_12 = var_r7->unk4;
        temp_r7 = var_r7 + 4;
        temp_r6 = &var_r6[1];
        if ((bitwise f32) 0.0 != temp_f2_12) {
            temp_r6->unkC += temp_f2_12;
        }
        temp_f2_13 = temp_r7->unk4;
        temp_r7_2 = temp_r7 + 4;
        temp_r6_2 = temp_r6 + 0x18;
        if ((bitwise f32) 0.0 != temp_f2_13) {
            temp_r6_2->unkC += temp_f2_13;
        }
        temp_f2_14 = temp_r7_2->unk4;
        temp_r7_3 = temp_r7_2 + 4;
        temp_r6_3 = temp_r6_2 + 0x18;
        if ((bitwise f32) 0.0 != temp_f2_14) {
            temp_r6_3->unkC += temp_f2_14;
        }
        temp_f2_15 = temp_r7_3->unk4;
        temp_r6_4 = temp_r6_3 + 0x18;
        if ((bitwise f32) 0.0 != temp_f2_15) {
            temp_r6_4->unkC += temp_f2_15;
        }
        var_r7 = temp_r7_3 + 4 + 4;
        var_r6 = temp_r6_4 + 0x18;
        var_ctr_8 -= 1;
    } while (var_ctr_8 != 0);
#endif
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

static f64 pi_over_4 = M_PI / 4.0F;

void grKongo_801D7134(HSD_GObj* gobj, s32 arg1)
{
    HSD_JObj** temp_r29_3;
    HSD_JObj* jobj;
    HSD_JObj* jobj_1;
    HSD_JObj* jobj_2;
    HSD_JObj* jobj_3;
    HSD_JObj* jobj_4;
    HSD_JObj* jobj_5;
    HSD_JObj* jobj_6;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f30_3;
    f32 temp_f30_4;
    f32 temp_f30_5;
    f32 temp_f31;
    f32 temp_f3;
    f32 temp_f3_2;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f31;
    f32 var_f31_2;
    s32 temp_cr0_eq;
    s32 temp_cr0_eq_2;
    s32 temp_cr0_eq_3;
    s32 temp_cr0_eq_4;
    s32 temp_cr0_eq_5;
    s32 var_r28;
    s32 var_r29_3;
    s32 var_r3;
    s32 var_r3_2;
    s32 var_r3_3;
    s32 var_r3_4;
    s32 var_r3_5;
    u32 temp_r4;
    u32 temp_r4_2;
    u32 temp_r4_3;
    u32 temp_r4_4;
    u32 temp_r4_5;
    u32 var_r27;
    u32 var_r27_2;
    void* var_r29;
    void* var_r29_2;
    void* var_r30;

#if 0
    Ground *gp = GET_GROUND(gobj);
    grKongo_801D6AFC();
    var_r27 = 0U;
    var_r29 = &grKg_803E16E0 + (0 * 0x18) + 0x1AC;
    do {
        var_r27 += 1;
        var_r29->unk14 = (f32) (37.8 * tanf(-grKg_803E16E0[i + 1]->xC));
        var_r29 += 0x18;
    } while (var_r27 < 0xFU);
    {
        temp_f0 = deg_to_rad * grKg_804D6980->unkAC;
        var_f31 = (f32) (0.7853981633974483 * (0.5 * (f64) (((grKg_803E16E0.unk1F0 - grKg_803E16E0.unk1D8) / 6.0f) + ((grKg_803E16E0.unk208 - grKg_803E16E0.unk1F0) / 6.0f))));
        temp_f30 = grKg_803E16E0.unk1E8 * (((deg_to_rad * grKg_804D6980->unkA8) / (deg_to_rad * grKg_804D6980->unk90)) - 1.0f);
        compare(var_f31, temp_f0, var_f31);
        HSD_JObjSetRotationX(grKg_804D6984.unk0, temp_f30);
        HSD_JObjGetRotationZ(temp_f30_2, grKg_804D6984.unk0);
        HSD_JObjSetRotationZ(grKg_804D6984.unk0, var_f31);
        temp_f3 = var_f31 - temp_f30_2;
        if (ABS(temp_f3) > (deg_to_rad * grKg_804D6980->unkB0)) {
            gp->gv.kongo2.xC8 = -temp_f3;
        }
    }
    temp_f0_3 = deg_to_rad * grKg_804D6980->unkAC;
    var_f31_2 = (f32) (0.7853981633974483 * (0.5 * (f64) (((grKg_803E16E0.unk2E0 - grKg_803E16E0.unk2C8) / 6.0f) + ((grKg_803E16E0.unk2F8 - grKg_803E16E0.unk2E0) / 6.0f))));
    temp_f30_3 = grKg_803E16E0.unk2D8 * (((deg_to_rad * grKg_804D6980->unkA8) / (deg_to_rad * grKg_804D6980->unk90)) - 1.0f);
    if (var_f31_2 > temp_f0_3) {
        var_f31_2 = temp_f0_3;
    } else {
        temp_f0_4 = -temp_f0_3;
        if (var_f31_2 < temp_f0_4) {
            var_f31_2 = temp_f0_4;
        }
    }
    jobj_1 = grKg_804D6984.unk4;
    temp_r29_3 = &grKg_804D6984 + 4;
    HSD_JObjSetRotationX(jobj_1, temp_f30_3);
    jobj_2 = *temp_r29_3;
   HSD_JObjGetRotationZ(temp_f30_4, jobj_2);
    jobj_6 = *temp_r29_3;
    HSD_JObjSetRotationZ(jobj_6, var_f31_2);
    temp_f3_2 = var_f31_2 - temp_f30_4;
    if (temp_f3_2 < 0.0f) {
        var_f2_2 = -temp_f3_2;
    } else {
        var_f2_2 = temp_f3_2;
    }
#endif
#if 0
    if (var_f2_2 > (0.017453292f * grKg_804D6980->unkB0)) {
        gp->gv.kongo.xD8 = -temp_f3_2;
    }
    var_r30 = &grKg_803E16E0 + 0x1AC;
    var_r29_2 = var_r30;
    var_r27_2 = 0U;
    do {
        jobj_3 = var_r29_2->unk4;
        temp_f31 = var_r29_2->unkC;
        HSD_JObjSetRotationX(jobj_3, temp_f31);
        var_r27_2 += 1;
        var_r29_2 += 0x18;
    } while (var_r27_2 < 0xFU);
    mpLib_80057424(4);
    var_r28 = 0;
    var_r29_3 = 0x28;
    do {
        temp_f30_5 = var_r30->unk14;
        mpLib_80056758(var_r29_3, 0, temp_f30_5, 0, temp_f30_5);
        if (var_r28 == 0) {
            mpLib_80056758(var_r29_3 - 1, 0, temp_f30_5, 0, temp_f30_5);
        } else if ((u32) var_r28 == 0xEU) {
            mpLib_80056758(var_r29_3 + 1, 0, temp_f30_5, 0, temp_f30_5);
        }
        var_r28 += 1;
        var_r29_3 += 2;
        var_r30 += 0x18;
    } while ((u32) var_r28 < 0xFU);
#endif
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
                                } else if ((temp_r3_8 - grKg_804D6980->unk52) <
                                           0)
                                {
                                    var_f31 = -3.1415927f;
                                } else {
                                    __assert("grkongo.c", 1753, "0");
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
    Ground_801C2BA4(5);
    // ftCo_800C0764(2, fn_801D8134);
    grZakoGenerator_801CAE04(0);
}

bool grKongo_801D5338(void)
{
    return 0;
}

HSD_GObj* grKongo_801D5340(s32 gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grKg_803E16E0[gobj_id + 1];

    gobj = Ground_801C14D0(gobj_id);

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
            HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grstory.c", 220,
                 gobj_id);
    }
    return gobj;
}

void fn_801D542C(HSD_GObj* arg0)
{
    Ground* temp_r31;
    f32 temp_f2;

    temp_r31 = arg0->user_data;
    mpJointSetCb1(4, temp_r31, fn_801D7700);
    temp_f2 = grKg_804D6980->unk0;
    temp_r31->gv.kongo.xE4 =
        (s16) (((grKg_804D6980->unk4 - temp_f2) * HSD_Randf()) + temp_f2);
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

/// #fn_801D7700

/// #grKongo_801D77E0

/// #grKongo_801D7BBC

void fn_801D7E60(Ground* gp, s32 arg1, CollData* arg2, s32 arg3,
                 mpLib_GroundEnum arg4, float arg8)
{
    if (arg4 == mpLib_GroundEnum_Unk2) {
        gp->gv.kongo3.xC6 = gp->gv.kongo3.xC8 + 1;
    }
}

/// #grKongo_801D7E78

/// #grKongo_801D7F78

void grKongo_801D8058(Ground_GObj* arg)
{
    Ground_801C4A08(arg);
}

/// #grKongo_801D8078

/// #fn_801D8134

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

/// #grKongo_801D844C
