#include "groldkongo.h"

#include "placeholder.h"

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
#include "lb/forward.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

static struct {
    s16 x0;
    s16 x2;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
    s16 x2C;
    s16 x2E;
    s16 x30;
    s16 x32;
    s16 x34;
    s16 x36;
    s16 x38;
    s16 x3A;
    s32 x3C;
    s32 x40;
    f32 x44;
    f32 x48;
    s32 x4C;
    s32 x50;
    s32 x54;
    s32 x58;
    s32 x5C;
    s32 x60;
    s32 x64;
    s32 x68;
    s32 x6C;
}* grOk_804D6A90;

u8 grOk_803E6580[0xC] = { 0 };

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

char grOk_803E6640[] = "groldkongo.c";

static lbColl_80008D30_arg1 grOk_803B8408;

void grOldKongo_8020F468(bool arg) {}

void grOldKongo_8020F46C(void)
{
    grOk_804D6A90 = Ground_801C49F8();
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
        OSReport((char*) grOk_803E6580 + 0x9C,
                 (char*) grOk_803E6580 + 0xC0, 0xD5, arg0);
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
    gp->gv.oldkongo.xE8 = 1.0f;
    gp->gv.oldkongo.xEC = 1.0f;
    gp->gv.oldkongo.xD8 = 0.0f;
    gp->gv.oldkongo.xDC = 0.0f;
    gp->gv.oldkongo.xC4 = 0;
    gp->gv.oldkongo.xC6 = 0;
    gp->gv.oldkongo.xC8 = 2;
    gp->gv.oldkongo.xD4 = NULL;
    gp->gv.oldkongo.xE0 = 0.0f;
    gp->gv.oldkongo.xE4 = 0.0f;
    gp->gv.oldkongo.xEC = grOk_804D6A90->x48;
    gp->gv.oldkongo.xCC = rand_range(grOk_804D6A90->x18, grOk_804D6A90->x14);
    gp->gv.oldkongo.xCE = rand_range(grOk_804D6A90->x50, grOk_804D6A90->x4C);
    lb_8000B1CC(Ground_801C3FA4(gobj, 1), NULL, &sp14);
    Ground_801C4D70(gobj, &sp14, gp->gv.oldkongo.xDC);
}

bool grOldKongo_8020F880(Ground_GObj* gobj)
{
    return false;
}

#define DegToRad(a) ((a) * 0.017453292F)
#define M_TAU 6.283185307179586

static inline void grOldKongo_8020F888_inline(Ground* gp, f32 vel, bool sign)
{
    f32 step = DegToRad(grOk_804D6A90->x1C);
    bool compare = sign ? (vel < step) : (vel > -step);

    if (compare) {
        gp->gv.oldkongo.xE4 = 0.0f;
        gp->gv.oldkongo.xDC = gp->gv.oldkongo.xD8;
    } else {
        gp->gv.oldkongo.xE4 = vel - (sign ? step : -step);
    }
}

static inline void grOldKongo_8020F888_clamp(f32 a, f32 b, f32* out)
{
    if (a > b) {
        *out = b;
    } else {
        b = -b;
        if (a < b) {
            *out = b;
        }
    }
}

static inline f32 grOldKongo_8020F888_tau_range(f32 a)
{
    if (a > (f32) M_TAU) {
        return (f64) a - M_TAU;
    } else if (a < (f32) -M_TAU) {
        return (f64) a + M_TAU;
    }
    return 0.0f;
}

static inline void grOldKongo_8020F888_update_xC8(HSD_JObj* jobj,
                                                     Ground* gp,
                                                     Ground_GObj* gobj,
                                                     Vec3* pos)
{
    s16 temp_r4_3;
    f32 temp_f1;
    s16 temp_r4_4;

    lb_8000B1CC(jobj, NULL, pos);
    Ground_801C4D70(gobj, pos, gp->gv.arwing.xDC);

    switch (gp->gv.oldkongo.xC8) {
    case 0:
        temp_r4_3 = gp->gv.castle8.plat[0].timer;
        gp->gv.castle8.plat[0].timer = temp_r4_3 - 1;
        if (temp_r4_3 < 0) {
            gp->gv.oldkongo.xC8 = 1;
        }
        break;
    case 1:
        gp->gv.arwing.xEC += grOk_804D6A90->x44;
        temp_f1 = grOk_804D6A90->x48;
        if (gp->gv.arwing.xEC > temp_f1) {
            gp->gv.arwing.xEC = temp_f1;
            {
                s32 var_r28_2;
                s32 temp_r27_2;
                s32 temp_r3_5;
                s32 var_r3_5;
                s32 temp_r3_6;
                s32 var_r3_6;

                var_r28_2 = grOk_804D6A90->x50;
                temp_r27_2 = grOk_804D6A90->x4C;
                if (var_r28_2 > temp_r27_2) {
                    temp_r3_5 = var_r28_2 - temp_r27_2;
                    if (temp_r3_5 != 0) {
                        var_r3_5 = HSD_Randi(temp_r3_5);
                    } else {
                        var_r3_5 = 0;
                    }
                    var_r28_2 = temp_r27_2 + var_r3_5;
                } else if (var_r28_2 < temp_r27_2) {
                    temp_r3_6 = temp_r27_2 - var_r28_2;
                    if (temp_r3_6 != 0) {
                        var_r3_6 = HSD_Randi(temp_r3_6);
                    } else {
                        var_r3_6 = 0;
                    }
                    var_r28_2 += var_r3_6;
                }
                gp->gv.castle8.plat[0].timer = (s16) var_r28_2;
            }
            gp->gv.oldkongo.xC8 = 2;
        }
        break;
    case 2:
        temp_r4_4 = gp->gv.castle8.plat[0].timer;
        gp->gv.castle8.plat[0].timer = temp_r4_4 - 1;
        if (temp_r4_4 < 0) {
            gp->gv.oldkongo.xC8 = 3;
        }
        break;
    case 3:
        gp->gv.arwing.xEC -= grOk_804D6A90->x44;
        if (gp->gv.arwing.xEC < 0.0f) {
            gp->gv.arwing.xEC = 0.0f;
            {
                s32 var_r28_3;
                s32 temp_r27_3;
                s32 temp_r3;
                s32 var_r3;
                s32 temp_r3_2;
                s32 var_r3_2;

                var_r28_3 = grOk_804D6A90->x40;
                temp_r27_3 = grOk_804D6A90->x3C;
                if (var_r28_3 > temp_r27_3) {
                    temp_r3 = var_r28_3 - temp_r27_3;
                    if (temp_r3 != 0) {
                        var_r3 = HSD_Randi(temp_r3);
                    } else {
                        var_r3 = 0;
                    }
                    var_r28_3 = temp_r27_3 + var_r3;
                } else if (var_r28_3 < temp_r27_3) {
                    temp_r3_2 = temp_r27_3 - var_r28_3;
                    if (temp_r3_2 != 0) {
                        var_r3_2 = HSD_Randi(temp_r3_2);
                    } else {
                        var_r3_2 = 0;
                    }
                    var_r28_3 += var_r3_2;
                }
                gp->gv.castle8.plat[0].timer = (s16) var_r28_3;
            }
            gp->gv.oldkongo.xC8 = 0;
        }
        break;
    }
}

void grOldKongo_8020F888(Ground_GObj* arg0)
{
    Vec3 sp3C;
    u8 pad[8];
    lbColl_80008D30_arg1 hit;
    Ground* temp_r31;
    Ground_GObj* temp_r29;
    HSD_JObj* temp_r30;
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f3;
    f32 temp_f31;
    f32 var_f0;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f30;
    s16 temp_r3_9;
    s16 temp_r4;
    s16 temp_r4_5;
    s32 temp_r28;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 var_r27;
    s32 var_r3_3;
    s32 var_r3_4;
    temp_r29 = arg0;
    temp_r31 = GET_GROUND(temp_r29);
    temp_r30 = Ground_801C3FA4(temp_r29, 1);
    switch (temp_r31->gv.oldkongo.xC4) {
    case 2:
    case 3:
        temp_f3 = temp_r31->gv.arwing.xE0.y;
        temp_f31 = 0.5f * (temp_f3 * (temp_f3 / DegToRad(grOk_804D6A90->x1C)));
        if (temp_f3 > 0.0f) {
            var_f30 = temp_r31->gv.oldkongo.xD8 - temp_r31->gv.arwing.xDC;
        } else if (temp_f3 < 0.0f) {
            var_f30 = temp_r31->gv.arwing.xDC - temp_r31->gv.oldkongo.xD8;
        } else {
            HSD_ASSERT(0x18CU, NULL);
        }
        if (var_f30 < 0.0f) {
            var_f30 += M_TAU;
        }
        if (var_f30 < temp_f31) {
            goto block_16;
        }
        var_f1 = temp_r31->gv.arwing.xE0.y;
        if (var_f1 < 0.0f) {
            var_f1 = -var_f1;
        }
        if (!(var_f30 < var_f1)) {
            goto block_17;
        }
    block_16:
        if ((s16) temp_r31->gv.oldkongo.xC4 == 3) {
            temp_r31->gv.oldkongo.xC4 = 0;
        }
        break;
    block_17:
        if ((s16) temp_r31->gv.oldkongo.xC4 == 2) {
            temp_r31->gv.oldkongo.xC4 = 3;
        }
        break;
    case 0:
        temp_f3 = temp_r31->gv.arwing.xE0.y;
        if (temp_f3 > 0.0f) {
            temp_f0 = DegToRad(grOk_804D6A90->x1C);
            if (temp_f3 < temp_f0) {
                temp_r31->gv.arwing.xE0.y = 0.0f;
                temp_r31->gv.arwing.xDC = temp_r31->gv.oldkongo.xD8;
            } else {
                temp_r31->gv.arwing.xE0.y = temp_f3 - temp_f0;
            }
        } else if (temp_f3 < 0.0f) {
            temp_f1 = DegToRad(grOk_804D6A90->x1C);
            if (temp_f3 > -temp_f1) {
                temp_r31->gv.arwing.xE0.y = 0.0f;
                temp_r31->gv.arwing.xDC = temp_r31->gv.oldkongo.xD8;
            } else {
                temp_r31->gv.arwing.xE0.y = temp_f3 + temp_f1;
            }
        }
        temp_r31->gv.castle8.plat[0].state -= 1;
        if ((s16) temp_r31->gv.castle8.plat[0].state < 0) {
            temp_r31->gv.oldkongo.xC4 = 1;
            if (HSD_Randi(2) != 0) {
                var_f0 = DegToRad(grOk_804D6A90->x1C);
            } else {
                var_f0 = -DegToRad(grOk_804D6A90->x1C);
            }
            temp_r31->gv.arwing.xE0.x = var_f0;
            {
                s32 temp_r27;
                s32 var_r28;
                s32 temp_r3;
                s32 var_r3;
                s32 temp_r3_2;
                s32 var_r3_2;

                temp_f0 = grOk_804D6A90->x24;
                temp_f2 = grOk_804D6A90->x28;
                temp_r27 = (s32) temp_f0;
                var_r28 = (s32) temp_f2;
                if ((s32) temp_f2 > (s32) temp_f0) {
                    temp_r3 = var_r28 - temp_r27;
                    if (temp_r3 != 0) {
                        var_r3 = HSD_Randi(temp_r3);
                    } else {
                        var_r3 = 0;
                    }
                    var_r28 = temp_r27 + var_r3;
                } else if (var_r28 < temp_r27) {
                    temp_r3_2 = temp_r27 - var_r28;
                    if (temp_r3_2 != 0) {
                        var_r3_2 = HSD_Randi(temp_r3_2);
                    } else {
                        var_r3_2 = 0;
                    }
                    var_r28 += var_r3_2;
                }
                temp_r31->gv.castle8.plat[0].state = (s16) var_r28;
            }
        }
        break;
    case 1:
        temp_r31->gv.arwing.xE0.y += temp_r31->gv.arwing.xE0.x;
        temp_f2 = temp_r31->gv.arwing.xE0.y;
        temp_f0 = DegToRad(grOk_804D6A90->x20);
        if (temp_f2 > temp_f0) {
            temp_r31->gv.arwing.xE0.y = temp_f0;
        } else {
            temp_f0 = -temp_f0;
            if (temp_f2 < temp_f0) {
                temp_r31->gv.arwing.xE0.y = temp_f0;
            }
        }
        temp_r4 = temp_r31->gv.castle8.plat[0].state;
        temp_r31->gv.castle8.plat[0].state = temp_r4 - 1;
        if (temp_r4 < 0) {
            temp_r31->gv.oldkongo.xC4 = 2;
            temp_f0 = grOk_804D6A90->x14;
            temp_f2 = grOk_804D6A90->x18;
            temp_r28 = (s32) temp_f0;
            var_r27 = (s32) temp_f2;
            if ((s32) temp_f2 > (s32) temp_f0) {
                temp_r3_3 = var_r27 - temp_r28;
                if (temp_r3_3 != 0) {
                    var_r3_3 = HSD_Randi(temp_r3_3);
                } else {
                    var_r3_3 = 0;
                }
                var_r27 = temp_r28 + var_r3_3;
            } else if (var_r27 < temp_r28) {
                temp_r3_4 = temp_r28 - var_r27;
                if (temp_r3_4 != 0) {
                    var_r3_4 = HSD_Randi(temp_r3_4);
                } else {
                    var_r3_4 = 0;
                }
                var_r27 += var_r3_4;
            }
            temp_r31->gv.castle8.plat[0].state = (s16) var_r27;
            temp_r31->gv.oldkongo.xD8 = grOldKongo_80210650();
        }
        break;
    }

    temp_r31->gv.arwing.xDC += temp_r31->gv.arwing.xE0.y;
    temp_f2 = temp_r31->gv.arwing.xDC;
    if (temp_f2 > M_TAU) {
        temp_r31->gv.arwing.xDC = (f32) ((f64) temp_f2 - M_TAU);
    } else if (temp_f2 < -M_TAU) {
        temp_f2 += M_TAU;
        temp_r31->gv.arwing.xDC = temp_f2;
    }
    temp_f31 = temp_r31->gv.arwing.xDC;
    HSD_JObjSetRotationZ(temp_r30, temp_f31);
    grOldKongo_8020F888_update_xC8(temp_r30, temp_r31, temp_r29, &sp3C);
    grAnime_801C7A04(temp_r29, 0, 7U, temp_r31->gv.arwing.xEC);

    switch (temp_r31->gv.oldkongo.xC6) {
    case 1:
        if ((u32) temp_r31->gv.arwing.xD4 == 0U) {
            temp_r31->gv.oldkongo.xC6 = 0;
            goto block_123;
        }
        temp_r4_5 = temp_r31->gv.castle11.xCA;
        temp_r31->gv.castle11.xCA = temp_r4_5 - 1;
        if (temp_r4_5 >= 0) {
            return;
        }
        temp_r31->gv.oldkongo.xC6 = 2;
    case 2:
    block_123:
        grAnime_801C7FF8(temp_r29, 2, 7, 2, 0.0f, 1.0f);
        grMaterial_801C95C4(temp_r29);
        temp_r31->gv.castle2.xD0 = 0;
        temp_r31->gv.oldkongo.xC6 = 3;
    case 3:
        temp_r3_9 = temp_r31->gv.castle2.xD0;
        temp_r31->gv.castle2.xD0 = temp_r3_9 + 1;
        if (temp_r3_9 > 0xA) {
            hit = grOk_803B8408;
            hit.state = 1;
            hit.damage = grOk_804D6A90->x54;
            hit.kb_angle = grOk_804D6A90->x58;
            hit.unkC = grOk_804D6A90->x5C;
            hit.unk10 = grOk_804D6A90->x60;
            hit.unk14 = grOk_804D6A90->x64;
            hit.element = grOk_804D6A90->x68;
            var_f1_2 =
                (f32) (1.5707963267948966 + (f64) temp_r31->gv.arwing.xDC);
            if (var_f1_2 < 0.0f) {
                var_f1_2 += M_TAU;
            } else if (var_f1_2 > M_TAU) {
                var_f1_2 = (f32) ((f64) var_f1_2 - M_TAU);
            }
            var_f1_2 = 57.29578f * var_f1_2;
            if (((HSD_GObj*) temp_r31->gv.arwing.xD4)->p_link == 8) {
                ftCo_8009EC70((Fighter_GObj*) temp_r31->gv.arwing.xD4, &sp3C,
                              &hit, var_f1_2);
            }
            temp_r31->gv.oldkongo.xC6 = 4;
            Ground_801C5440(temp_r31, 0, 0x12AU);
            return;
        }
        return;
    case 4:
        temp_r31->gv.oldkongo.xC6 = 0;
        break;
    case 0:
    default:
        return;
    }
}

void grOldKongo_80210058(Ground_GObj* arg) {}

void grOldKongo_8021005C(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    gp->gv.unk.xC4 = rand_range(grOk_804D6A90->x2, grOk_804D6A90->x0);
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
    s32 timer = gp->gv.unk.xC4;
    u32 pad3;

    if (timer > 0) {
        gp->gv.unk.xC4 = timer - 1;
        if (gp->gv.unk.xC4 == 0) {
            f32 x;

            grAnime_801C8138(arg0, gp->map_id, 0);
            HSD_JObjSetTranslateY(jobj, (grOk_804D6A90->x4 *
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
        min = grOk_804D6A90->x2;
        max = grOk_804D6A90->x0;
        if (min > max) {
            s32 range = min - max;

            min = max + (range != 0 ? HSD_Randi(range) : 0);
        } else if (min < max) {
            s32 range = max - min;

            min += (range != 0 ? HSD_Randi(range) : 0);
        }
        gp->gv.unk.xC4 = min;
    }
}

void grOldKongo_80210450(Ground_GObj* arg) {}

s32 grOldKongo_80210454(HSD_GObj* arg0, HSD_GObj* arg1)
{
    Ground* gp;
    Vec3 pos_gnd;
    Vec3 pos_ft;
    f32 unk;
    f32 rand_val;
    f32 diff;

    gp = GET_GROUND(arg0);

    if (gp->gv.oldkongo.xC6 != 0) {
        goto done;
    }

    Ground_801C4DA0(&pos_gnd, &unk);
    ftLib_80086644(arg1, &pos_ft);

    if (!((pos_gnd.x - pos_ft.x) * (pos_gnd.x - pos_ft.x) +
              (pos_gnd.y - pos_ft.y) * (pos_gnd.y - pos_ft.y) +
              (pos_gnd.z - pos_ft.z) * (pos_gnd.z - pos_ft.z) <
          grOk_804D6A90->x10 * grOk_804D6A90->x10))
    {
        goto done;
    }

    rand_val = HSD_Randf();
    diff = grOk_804D6A90->xC - grOk_804D6A90->x8;
    gp->gv.oldkongo.xCA = (s16) (diff * rand_val + grOk_804D6A90->x8);
    gp->gv.oldkongo.xD4 = arg1;
    gp->gv.oldkongo.xC6 = 1;
    Ground_801C5440(gp, 0, 0x129U);
    grAnime_801C7FF8(arg0, 2, 7, 1, 0.0f, 1.0f);
    grMaterial_801C9604(arg0, grOk_804D6A90->x6C, 0);
    efSync_Spawn(0x405, arg0, &pos_ft);
    ftLib_80086C18(arg1, 0xD, 0x1E);
    return 1;
done:
    return 0;
}

void grOldKongo_802105AC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->gv.oldkongo.xC6 == 1) {
        gp->gv.oldkongo.xC6 = 2;
    }
}

void grOldKongo_802105C8(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    if (gp->gv.oldkongo.xC6 != 1) {
        return;
    }
    if (gp->gv.oldkongo.xD4 == NULL) {
        __assert(grOk_803E6640, 751, "gp->u.taru.keep");
    }
    if (((u8*) gp->gv.oldkongo.xD4)[2] == 8) {
        gp->gv.oldkongo.xC6 = 0;
        gp->gv.oldkongo.xD4 = NULL;
        grMaterial_801C95C4(gobj);
    }
}

extern f32 grOk_804DB9CC;
extern f32 grOk_804DBA04;
extern f32 grOk_804DBA08;
extern f32 grOk_804DBA0C;
extern f32 grOk_804DBA10;
extern f32 grOk_804DBA14;
extern f32 grOk_804DBA18;
extern f32 grOk_804DBA1C;

f32 grOldKongo_80210650(void)
{
    f32 result;
    s32 total;
    s32 r;

    total = grOk_804D6A90->x2C + grOk_804D6A90->x2E + grOk_804D6A90->x30 +
            grOk_804D6A90->x32 + grOk_804D6A90->x34 + grOk_804D6A90->x36 +
            grOk_804D6A90->x38 + grOk_804D6A90->x3A;

    if (total != 0) {
        r = HSD_Randi(total);
    } else {
        r = 0;
    }

    if ((r -= grOk_804D6A90->x2C) < 0) {
        result = grOk_804DBA04;
    } else if ((r -= grOk_804D6A90->x2E) < 0) {
        result = grOk_804DBA08;
    } else if ((r -= grOk_804D6A90->x30) < 0) {
        result = grOk_804DBA0C;
    } else if ((r -= grOk_804D6A90->x32) < 0) {
        result = grOk_804DB9CC;
    } else if ((r -= grOk_804D6A90->x34) < 0) {
        result = grOk_804DBA10;
    } else if ((r -= grOk_804D6A90->x36) < 0) {
        result = grOk_804DBA14;
    } else if ((r -= grOk_804D6A90->x38) < 0) {
        result = grOk_804DBA18;
    } else if ((r -= grOk_804D6A90->x3A) < 0) {
        result = grOk_804DBA1C;
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
