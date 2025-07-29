#include "grlast.h"

#include "baselib/psstructs.h"

#include <math.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/random.h>
#include <melee/cm/camera.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gr/granime.h>
#include <melee/gr/grdisplay.h>
#include <melee/gr/grlib.h>
#include <melee/gr/grmaterial.h>
#include <melee/gr/ground.h>
#include <melee/gr/grzakogenerator.h>
#include <melee/gr/inlines.h>
#include <melee/gr/stage.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbvector.h>

const Vec3 grLast_803B8480 = { 1, 1, 1 };
const Vec3 grLast_803B848C = { 0, 1, 0 };
const Vec3 grLast_803B8498 = { 0, 0, 1 };

S16Vec grLast_804D4968[1] = { { 0, 3, 0 } };

static int* grNLa_804D6AD0;

static void grLast_8021A620(int arg0)
{
    Ground_GObj* gobj;
    Ground* gp;

    if (arg0 != 0x1A) {
        return;
    }
    gobj = Ground_801C2BA4(4);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    gobj = Ground_801C2BA4(5);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    gobj = Ground_801C2BA4(6);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    gobj = Ground_801C2BA4(7);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    gobj = Ground_801C2BA4(8);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    gobj = Ground_801C2BA4(9);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    gobj = Ground_801C2BA4(1);
    HSD_ASSERT(0x50, gobj);

    gobj = Ground_801C2BA4(3);
    HSD_ASSERT(0x53, gobj);

    gp = GET_GROUND(gobj);
    HSD_ASSERT(0x54, gp);
    gp->u.map.xC4_b1 = true;
}

static StageCallbacks grLast_803E7EBC[] = {
    {
        // 0 generic anime gobj
        grLast_8021A8E0,
        grLast_8021A90C,
        grLast_8021A914,
        grLast_8021A918,
    },
    {
        // 1 generic anime gobj
        grLast_8021A91C,
        grLast_8021A960,
        grLast_8021A968,
        grLast_8021A96C,
    },
    {
        // 2 generic anime gobj
        grLast_8021A970,
        grLast_8021A99C,
        grLast_8021A9A4,
        grLast_8021A9A8,
    },
    {
        // 3 map type
        grLast_8021A9C4,
        grLast_8021AAA8,
        grLast_8021AAB0,
        grLast_8021AB30,
        0x80000000,
    },
    {
        // 4 generic jobj holder
        grLast_8021AB34,
        grLast_8021AB78,
        grLast_8021AB80,
        grLast_8021AB84,
        0x40000000,
    },
    {
        // 5 generic jobj holder
        grLast_8021AB88,
        grLast_8021ABCC,
        grLast_8021ABD4,
        grLast_8021ABD8,
    },
    {
        // 6 generic jobj holder
        grLast_8021ABDC,
        grLast_8021AC20,
        grLast_8021AC28,
        grLast_8021AC2C,
    },
    {
        // 7, uses UnkGenerator at xE0
        grLast_8021AC30,
        grLast_8021ADC8,
        grLast_8021ADD0,
        grLast_8021B23C,
    },
    {
        // 8 generic jobj holder
        grLast_8021B240,
        grLast_8021B284,
        grLast_8021B28C,
        grLast_8021B290,
    },
    {
        // 9 generic jobj holder
        grLast_8021B294,
        grLast_8021B2D8,
        grLast_8021B2E0,
        grLast_8021B2E4,
    },
};

StageData grNLa_803E7F90 = {
    0x00000025,
    grLast_803E7EBC,
    "/GrNLa.dat",
    grLast_8021A740,
    grLast_8021A620,
    grLast_8021A7C4,
    grLast_8021A7C8,
    grLast_8021A7EC,
    grLast_8021C740,
    grLast_8021C748,
    0x00000001,
    grLast_804D4968,
    ARRAY_SIZE(grLast_804D4968),
};

static void grLast_8021A740(void)
{
    grNLa_804D6AD0 = Ground_801C49F8();
    stage_info.unk8C.b4 = 1;
    stage_info.unk8C.b5 = 1;
    grLast_8021A7F4(0);
    grLast_8021A7F4(1);
    grLast_8021A7F4(2);
    grLast_8021A7F4(3);
    Ground_801C39C0();
    Ground_801C3BB4();
    Camera_800311DC(1);
    Camera_800311CC(30000);
}

static void grLast_8021A7C4(void) {}

static void grLast_8021A7C8(void)
{
    grZakoGenerator_801CAE04(0);
}

static int grLast_8021A7EC(void)
{
    return FALSE;
}

static Ground_GObj* grLast_8021A7F4(int id)
{
    Ground_GObj* gobj;
    Ground* gp;
    StageCallbacks* cb;

    cb = &grLast_803E7EBC[id];
    gobj = Ground_801C14D0(id);
    if (gobj != NULL) {
        gp = GET_GROUND(gobj);
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (cb->callback3 != NULL) {
            gp->x1C_callback = cb->callback3;
        }
        if (cb->callback0 != NULL) {
            cb->callback0(gobj);
        }
        if (cb->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, cb->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 255, id);
    }
    return gobj;
}

static void grLast_8021A8E0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grLast_8021A90C(Ground_GObj* gobj)
{
    return false;
}

static void grLast_8021A914(Ground_GObj* gobj) {}

static void grLast_8021A918(Ground_GObj* gobj) {}

static void grLast_8021A91C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 1;
}

static bool grLast_8021A960(Ground_GObj* gobj)
{
    return false;
}

static void grLast_8021A968(Ground_GObj* gobj) {}

static void grLast_8021A96C(Ground_GObj* gobj) {}

static void grLast_8021A970(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grLast_8021A99C(Ground_GObj* gobj)
{
    return false;
}

static void grLast_8021A9A4(Ground_GObj* gobj) {}

static void grLast_8021A9A8(Ground_GObj* gobj) {}

static void fn_8021A9AC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    gp->u.map.xC4_b0 = false;
}

static void grLast_8021A9C4(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    u32 i;

    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->u.map.xC4_b0 = true;
    for (i = 0; i < ARRAY_SIZE(gp->u.map.lv_gobj); i++) {
        gp->u.map.lv_gobj[i] = NULL;
    }
    gp->u.map.xC4_b2_25 = 0;
    gp->u.map.xC4_b26 = false;
    gp->u.map.xC4_b27 = true;
    grLast_8021B920(gobj, 1);
    gp->x11_flags.b012 = 1;
    gp->u.map.xC4_b1 = false;
    Ground_801C10B8(gobj, &fn_8021A9AC);
}

static bool grLast_8021AAA8(Ground_GObj* gobj)
{
    return false;
}

static void grLast_8021AAB0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (!gp->u.map.xC4_b1 && !gp->u.map.xC4_b0) {
        grLast_8021B2E8(gobj);
        if (gp->u.map.xC4_b26) {
            int tmp = grLast_8021B5C4(gobj);
            if (tmp != 0) {
                grLast_8021B920(gobj, tmp);
            }
        }
    }
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

static void grLast_8021AB30(Ground_GObj* gobj) {}

static void grLast_8021AB34(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grMaterial_801C94D8(GET_JOBJ(gobj));
    gp->x11_flags.b012 = 2;
}

static bool grLast_8021AB78(Ground_GObj* gobj)
{
    return false;
}

static void grLast_8021AB80(Ground_GObj* gobj) {}

static void grLast_8021AB84(Ground_GObj* gobj) {}

static void grLast_8021AB88(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grMaterial_801C94D8(GET_JOBJ(gobj));
    gp->x11_flags.b012 = 2;
}

static bool grLast_8021ABCC(Ground_GObj* gobj)
{
    return false;
}

static void grLast_8021ABD4(Ground_GObj* gobj) {}

static void grLast_8021ABD8(Ground_GObj* gobj) {}

static void grLast_8021ABDC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grMaterial_801C94D8(GET_JOBJ(gobj));
    gp->x11_flags.b012 = 2;
}

static bool grLast_8021AC20(Ground_GObj* gobj)
{
    return false;
}

static void grLast_8021AC28(Ground_GObj* gobj) {}

static void grLast_8021AC2C(Ground_GObj* gobj) {}

static void grLast_8021AC30(Ground_GObj* gobj)
{
    const float grLast_804DBB80 = (M_PI / 180) / 250;
    const float grLast_804DBB7C = (M_PI / 180) / 1000;

    Ground* gp = GET_GROUND(gobj);

    grMaterial_801C94D8(GET_JOBJ(gobj));
    gp->u.last.xC4 = 0;
    gp->u.last.xC8 = 0;
    gp->u.last.xCC = 0;
    gp->u.last.xD0 = 0;
    gp->u.last.xD4 = HSD_Randf() * grLast_804DBB80 + grLast_804DBB7C;
    gp->u.last.xD4 *= HSD_Randi(2) ? +1.0F : -1.0F;
    gp->u.last.xD8 = HSD_Randf() * grLast_804DBB80 + grLast_804DBB7C;
    gp->u.last.xD8 *= HSD_Randi(2) ? +1.0F : -1.0F;
    gp->u.last.xDC = 0;
    gp->u.last.xE0 = 0;

    {
        HSD_JObj* jobj = Ground_801C3FA4(gobj, 5);
        Vec3 sp10 = grLast_803B8480;
        HSD_JObjSetScale(jobj, &sp10);
        gp->x11_flags.b012 = 2;
    }
}

static bool grLast_8021ADC8(Ground_GObj* gobj)
{
    return false;
}

static void grLast_8021ADD0(Ground_GObj* gobj)
{
    Vec3 sp38;
    Vec3 sp2C;
    Vec3 sp20;
    Vec3 sp14;
    const float grLast_804DBB80 = (M_PI / 180) / 250;
    const float grLast_804DBB7C = (M_PI / 180) / 1000;
    const float grLast_804DBB8C = +(M_PI / 180) / 20;
    const float grLast_804DBB90 = -(M_PI / 180) / 20;
    const float grLast_804DBB94 = +(M_PI / 180) * 15;
    const float grLast_804DBB98 = -(M_PI / 180) * 15;
    const float grLast_804DBB9C = +(M_PI / 180) * 10;
    const float grLast_804DBBA0 = -(M_PI / 180) * 10;

    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    gp->u.last.xCC += gp->u.last.xD4;
    gp->u.last.xCC *= 0.99F;
    if (gp->u.last.xCC > grLast_804DBB8C) {
        gp->u.last.xCC = grLast_804DBB8C;
    } else if (gp->u.last.xCC < grLast_804DBB90) {
        gp->u.last.xCC = grLast_804DBB90;
    }
    gp->u.last.xD0 += gp->u.last.xD8;
    gp->u.last.xD0 *= 0.99F;
    if (gp->u.last.xD0 > grLast_804DBB8C) {
        gp->u.last.xD0 = grLast_804DBB8C;
    } else if (gp->u.last.xD0 < grLast_804DBB90) {
        gp->u.last.xD0 = grLast_804DBB90;
    }
    gp->u.last.xC4 += gp->u.last.xCC;
    if (gp->u.last.xC4 > grLast_804DBB94) {
        float randf;
        gp->u.last.xC4 = grLast_804DBB94;
        gp->u.last.xCC = -ABS(gp->u.last.xCC);
        randf = HSD_Randf();
        gp->u.last.xD4 = grLast_804DBB80 * -randf - grLast_804DBB7C;
    } else if (gp->u.last.xC4 < grLast_804DBB98) {
        float randf;
        gp->u.last.xC4 = grLast_804DBB98;
        gp->u.last.xCC = ABS(gp->u.last.xCC);
        gp->u.last.xD4 = grLast_804DBB80 * HSD_Randf() + grLast_804DBB7C;
    }
    HSD_JObjSetRotationX(jobj, gp->u.last.xC4 * gp->u.last.xDC);
    gp->u.last.xC8 += gp->u.last.xD0;
    if (gp->u.last.xC8 > grLast_804DBB9C) {
        float randf;
        gp->u.last.xC8 = grLast_804DBB9C;
        gp->u.last.xD0 = -ABS(gp->u.last.xD0);
        randf = HSD_Randf();
        gp->u.last.xD8 = grLast_804DBB80 * -randf - grLast_804DBB7C;
    } else if (gp->u.last.xC8 < grLast_804DBBA0) {
        gp->u.last.xC8 = grLast_804DBBA0;
        gp->u.last.xD0 = ABS(gp->u.last.xD0);
        gp->u.last.xD8 = grLast_804DBB80 * HSD_Randf() + grLast_804DBB7C;
    }
    HSD_JObjSetRotationY(jobj, gp->u.last.xC8 * gp->u.last.xDC);
    if (gp->u.last.xE0 != NULL && gp->u.last.xE0->appsrt != NULL) {
        sp20 = grLast_803B848C;
        sp14 = grLast_803B8498;

        jobj = Ground_801C3FA4(gobj, 5);
        lb_8000B1CC(jobj, NULL, &sp38);
        lb_8000B1CC(jobj, &sp20, &sp20);
        lbVector_Sub(&sp20, &sp38);
        lbVector_Normalize(&sp20);
        lb_8000B1CC(jobj, &sp14, &sp14);
        lbVector_Sub(&sp14, &sp38);
        lbVector_Normalize(&sp14);
        lbVector_EulerAnglesFromPartialONB(&sp2C, &sp14, &sp20);
        gp->u.last.xE0->appsrt->translate = sp38;
        gp->u.last.xE0->appsrt->rot.x = sp2C.x;
        gp->u.last.xE0->appsrt->rot.y = sp2C.y;
        gp->u.last.xE0->appsrt->rot.z = sp2C.z;
        gp->u.last.xE0->appsrt->status = 0;
    }
}

static void grLast_8021B23C(Ground_GObj* gobj) {}

static void grLast_8021B240(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grMaterial_801C94D8(GET_JOBJ(gobj));
    gp->x11_flags.b012 = 2;
}

static bool grLast_8021B284(Ground_GObj* gobj)
{
    return false;
}

static void grLast_8021B28C(Ground_GObj* gobj) {}

static void grLast_8021B290(Ground_GObj* gobj) {}

static void grLast_8021B294(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grMaterial_801C94D8(GET_JOBJ(gobj));
    gp->x11_flags.b012 = 2;
}

static bool grLast_8021B2D8(Ground_GObj* gobj)
{
    return false;
}

static void grLast_8021B2E0(Ground_GObj* gobj) {}

static void grLast_8021B2E4(Ground_GObj* gobj) {}

static s16 grNLa_803E8010[][4] = {
    { 4, 1, 2, 0 }, { 5, 1, 2, 4 },  { 6, 1, 2, 6 },
    { 7, 1, 2, 8 }, { 8, 1, 2, 10 }, { 9, 0, -1, 0 },
};

static void grLast_8021B2E8(Ground_GObj* gobj)
{
    GXColor sp30;
    GXColor sp2C;
    Ground* gp;
    float temp_f1;
    Ground* temp_gp;

    gp = GET_GROUND(gobj);
    if (Stage_80225194() == 0xB0 || // Boss fight vs Master Hand
        Stage_80225194() == 0xFB)
    { // Event match #50
        temp_f1 = gm_8016ECE8();
        switch (gp->u.map.xC4_b2_25) {
        case 1:
            if (temp_f1 < 0.7F) {
                gp->u.map.xC4_b26 = true;
            }
            break;
        case 3:
            if (temp_f1 < 0.6F) {
                gp->u.map.xC4_b26 = true;
            }
            break;
        case 5:
            if (temp_f1 < 0.5F) {
                gp->u.map.xC4_b26 = true;
            }
            break;
        case 7:
            if (temp_f1 < 0.4F) {
                gp->u.map.xC4_b26 = true;
            }
            break;
        case 9:
            if (temp_f1 < 0.3F) {
                gp->u.map.xC4_b26 = true;
            }
            break;
        case 12:
            if (temp_f1 < 0.2F) {
                gp->u.map.xC4_b26 = true;
            }
            break;
        case 15:
            break;
        }
    } else if (gp->u.map.xC8 > 1800.0F) {
        gp->u.map.xC4_b26 = true;
    }
    gp->u.map.xC8 += 1.0F;
    switch (gp->u.map.xC4_b2_25) {
    case 9:
        temp_gp = GET_GROUND(gp->u.map.lv_gobj[3]);
        temp_gp->u.last.xDC += 1.0F / 180;
        if (temp_gp->u.last.xDC > 1) {
            temp_gp->u.last.xDC = 1;
        }
        break;
    case 10:
        temp_gp = GET_GROUND(gp->u.map.lv_gobj[3]);
        temp_gp->u.last.xDC -= 1.0F / 58;
        if (temp_gp->u.last.xDC < 0) {
            temp_gp->u.last.xDC = 0;
        }
        Camera_80030E44(1, 0);
        break;
    case 11:
        Camera_80030E44(1, 0);
        break;
    case 15:
        if (gp->u.map.xC4_b27) {
            int tmp;
            Ground_801C2090(&sp2C);
            do {
                sp30.r = HSD_Randi(2) * 0x1E;
                sp30.g = HSD_Randi(2) * 0x1E;
                sp30.b = HSD_Randi(2) * 0x1E;
            } while (
                (sp30.r == 0x1E && sp30.g == 0x1E && sp30.b == 0x1E) ||
                (sp30.r == sp2C.r && sp30.g == sp2C.g && sp30.g == sp2C.g));
            tmp = HSD_Randi(0x3C);
            tmp += 0x3C;
            grLast_8021C40C(gobj, sp30, tmp);
        }
        break;
    }
    grLast_8021C500(gobj);
}

static inline bool animate_all(Ground* gp)
{
    int i;
    for (i = 0; i < 5; i++) {
        if (!grAnime_801C83D0(gp->u.map.lv_gobj[i], grNLa_803E8010[i][1], 7)) {
            return false;
        }
    }
    return true;
}

static int grLast_8021B5C4(Ground_GObj* gobj)
{
    Ground* gp;
    int i;
    int result;
    int unused[4];
    HSD_AObj* aobj = NULL;

    result = 0;
    gp = GET_GROUND(gobj);
    switch (gp->u.map.xC4_b2_25) {
    case 1:
        result = 2;
        break;
    case 2:
        if (animate_all(gp)) {
            result = 3;
        }
        break;
    case 3:
        result = 4;
        break;
    case 4:
        if (animate_all(gp)) {
            result = 5;
        }
        break;
    case 5:
        result = 6;
        break;
    case 6:
        if (animate_all(gp)) {
            result = 7;
        }
        break;
    case 7:
        result = 8;
        break;
    case 8:
        if (animate_all(gp)) {
            result = 9;
        }
        break;
    case 9:
        aobj = grAnime_801C8318(gp->u.map.lv_gobj[3], grNLa_803E8010[3][2], 7);
        HSD_ASSERT(0x3F4, aobj);
        if (aobj->curr_frame == 100) {
            result = 10;
        }
        break;
    case 10:
        if (grAnime_801C84A4(gp->u.map.lv_gobj[3], grNLa_803E8010[3][2], 7)) {
            result = 11;
        }
        break;
    case 11:
        if (animate_all(gp)) {
            result = 12;
        }
        break;
    case 12:
        result = 13;
        break;
    case 13:
        if (gp->u.map.xC4_b27 && grLib_801C96E8(gp->u.map.lv_gobj[4])) {
            result = 14;
        }
        break;
    case 14:
        if (grLib_801C96E8(gp->u.map.lv_gobj[5])) {
            result = 15;
        }
        break;
    case 15:
        result = 16;
        break;
    case 16:
        if (gp->u.map.xC4_b27 && grLib_801C96E8(gp->u.map.lv_gobj[5])) {
            result = 17;
        }
        break;
    case 17:
        if (grLib_801C96E8(gp->u.map.lv_gobj[0])) {
            result = 1;
        }
        break;
    }
    return result;
}

static inline void do_anime(Ground_GObj* gobj, int i, int n)
{
    if (grNLa_803E8010[i][2] != -1) {
        grAnime_801C8098(gobj, grNLa_803E8010[i][1], 7, n, 0, 1);
        grAnime_801C7980(gobj, grNLa_803E8010[i][1], 7);
    } else {
        grAnime_801C7FF8(gobj, grNLa_803E8010[i][1], 7, n, 0, 1);
    }
}

static const GXColor grNLa_804DBBD4 = { 0xAA, 0xCA, 0xFF, 0x00 };
static const GXColor grNLa_804DBBD8 = { 0xC8, 0xC8, 0xC8, 0xFF };
static const GXColor grNLa_804DBBDC = { 0 };
static const GXColor grNLa_804DBBE0 = { 0 };

static inline void grlib_inline(Ground* gp)
{
    grLib_801C9834(gp->u.last.xE0);
    gp->u.last.xE0 = NULL;
}

static void grLast_8021B920(Ground_GObj* gobj_, int arg1)
{
    Ground_GObj* gobj = gobj_;
    Vec3 sp40;
    u8 _[0x0C];
    Ground* gp;
    int i;
    Ground* temp_r28_10;

    gp = gobj->user_data;

    gp->u.map.xC8 = 0.0F;
    gp->u.map.xC4_b2_25 = arg1;
    switch (gp->u.map.xC4_b2_25) {
    case 1:
        for (i = 0; i < 5; i++) {
            if (gp->u.map.lv_gobj[i] == NULL) {
                gp->u.map.lv_gobj[i] = grLast_8021A7F4(grNLa_803E8010[i][0]);
                HSD_ASSERT(0x44B, gp->u.map.lv_gobj[i]);
                HSD_GObjGXLink_803909D8(gp->u.map.lv_gobj[i], gobj_);
                if (grNLa_803E8010[i][2] != -1) {
                    grAnime_801C7FF8(gp->u.map.lv_gobj[i],
                                     grNLa_803E8010[i][2], 7,
                                     grNLa_803E8010[i][3], 0.0F, 1.0F);
                }
                do_anime(gp->u.map.lv_gobj[i], i, 0);
            }
        }
        grAnime_801C8098(Ground_801C2BA4(4), 0x10, 7, 0, 0.0F, 1.0F);
        gp->u.map.xC4_b26 = false;
        grLast_8021C640();
        break;
    case 2:
        i = 0;
        for (i = 0; i < 5; i++) {
            do_anime(gp->u.map.lv_gobj[i], i, 1);
        }
        grAnime_801C7A94(Ground_801C2BA4(4), 0x10, 7, 0.0F);
        grLib_801C9854(GET_JOBJ(Ground_801C2BA4(4)));
        gp->u.map.xC4_b26 = true;
        break;
    case 3:
        for (i = 0; i < 5; i++) {
            do_anime(gp->u.map.lv_gobj[i], i, 2);
        }
        gp->u.map.xC4_b26 = true;
        break;
    case 4:
        for (i = 0; i < 5; i++) {
            do_anime(gp->u.map.lv_gobj[i], i, 3);
        }
        gp->u.map.xC4_b26 = true;
        break;
    case 5:
        for (i = 0; i < 5; i++) {
            do_anime(gp->u.map.lv_gobj[i], i, 4);
        }
        gp->u.map.xC4_b26 = false;
        break;
    case 6:
        for (i = 0; i < 5; i++) {
            do_anime(gp->u.map.lv_gobj[i], i, 5);
        }
        gp->u.map.xC4_b26 = true;
        break;
    case 7:
        for (i = 0; i < 5; i++) {
            do_anime(gp->u.map.lv_gobj[i], i, 6);
        }
        gp->u.map.xC4_b26 = false;
        break;
    case 8:
        for (i = 0; i < 5; i++) {
            do_anime(gp->u.map.lv_gobj[i], i, 7);
        }
        gp->u.map.xC4_b26 = true;
        break;
    case 9:
        for (i = 0; i < 5; i++) {
            do_anime(gp->u.map.lv_gobj[i], i, 8);
        }

        temp_r28_10 = GET_GROUND(Ground_801C2BA4(7));
        lb_8000B1CC(Ground_801C3FA4(Ground_801C2BA4(7), 5), NULL, &sp40);
        temp_r28_10->u.last.xE0 = grLib_801C96F8(0x7531, 0x1E, &sp40);

        gp->u.map.xC4_b26 = false;
        break;
    case 10:
        grLast_8021C40C(gobj, grNLa_804DBBD4, 120.0F);
        grAnime_801C7A94(Ground_801C2BA4(7), 5, 7, 0.0F);

        grlib_inline(GET_GROUND(Ground_801C2BA4(7)));

        gp->u.map.xC4_b26 = true;
        grLast_8021C6AC();
        break;
    case 11:
        for (i = 0; i < 5; i++) {
            do_anime(gp->u.map.lv_gobj[i], i, 9);
        }
        gp->u.map.xC4_b26 = true;
        break;
    case 12:
        for (i = 0; i < 5; i++) {
            do_anime(gp->u.map.lv_gobj[i], i, 10);
        }
        gp->u.map.xC4_b26 = false;
        break;
    case 13:
        grLast_8021C40C(gobj, grNLa_804DBBD8, 120.0F);
        for (i = 0; i < 5; i++) {
            grMaterial_801C9604(gp->u.map.lv_gobj[i], grNLa_804D6AD0[0], 0);
            grMaterial_801C9698(gp->u.map.lv_gobj[i]);
        }
        gp->u.map.xC4_b26 = true;
        break;
    case 14:
        grLast_8021C40C(gobj, grNLa_804DBBDC, 60.0F);
        for (i = 0; i < 5; i++) {
            Ground_801C4A08(gp->u.map.lv_gobj[i]);
            gp->u.map.lv_gobj[i] = NULL;
        }
        gp->u.map.lv_gobj[5] = grLast_8021A7F4(grNLa_803E8010[5][0]);
        HSD_ASSERT(0x4D2, gp->u.map.lv_gobj[5]);
        HSD_GObjGXLink_803909D8(gp->u.map.lv_gobj[5], gobj);
        do_anime(gp->u.map.lv_gobj[5], 5, 0);
        grMaterial_801C9604(gp->u.map.lv_gobj[5], grNLa_804D6AD0[1], 0);
        grMaterial_801C9698(gp->u.map.lv_gobj[5]);
        Ground_801C1E00(0);
        gp->u.map.xC4_b26 = true;
        grLast_8021C640();
        break;
    case 15:
        gp->u.map.xC4_b26 = false;
        break;
    case 16:
        grLast_8021C40C(gobj, grNLa_804DBBE0, 60.0F);
        grMaterial_801C9604(gp->u.map.lv_gobj[5], grNLa_804D6AD0[2], 0);
        grMaterial_801C9698(gp->u.map.lv_gobj[5]);
        gp->u.map.xC4_b26 = true;
        break;
    case 17:
        for (i = 0; i < 5; i++) {
            gp->u.map.lv_gobj[i] = grLast_8021A7F4(grNLa_803E8010[i][0]);
            HSD_ASSERT(0x4F0, gp->u.map.lv_gobj[i]);
            HSD_GObjGXLink_803909D8(gp->u.map.lv_gobj[i], gobj);
            if (grNLa_803E8010[i][2] != -1) {
                grAnime_801C7FF8(gp->u.map.lv_gobj[i], grNLa_803E8010[i][2], 7,
                                 grNLa_803E8010[i][3], 0.0F, 1.0F);
            }
            do_anime(gp->u.map.lv_gobj[i], i, 0);
            grMaterial_801C9604(gp->u.map.lv_gobj[i], grNLa_804D6AD0[3], 0);
            grMaterial_801C9698(gp->u.map.lv_gobj[i]);
        }

        Ground_801C4A08(gp->u.map.lv_gobj[5]);
        gp->u.map.lv_gobj[5] = NULL;
        Ground_801C1E00(1);
        gp->u.map.xC4_b26 = true;
        break;
    }
}

static void grLast_8021C40C(Ground_GObj* gobj, GXColor color, float arg2)
{
    GXColor sp18;
    Ground* gp = GET_GROUND(gobj);
    Ground_801C2090(&sp18);
    gp->u.map.xE4 = color.r;
    gp->u.map.xE8 = color.g;
    gp->u.map.xEC = color.b;
    gp->u.map.xF4 = sp18.r;
    gp->u.map.xF8 = sp18.g;
    gp->u.map.xFC = sp18.b;
    gp->u.map.x104 = arg2;
    gp->u.map.xC4_b27 = false;
}

static void grLast_8021C500(Ground_GObj* gobj)
{
    GXColor sp10;
    Ground* gp = GET_GROUND(gobj);

    if (!gp->u.map.xC4_b27) {
        gp->u.map.x104 -= 1.0F;
        if (gp->u.map.x104 > 0.0F) {
            gp->u.map.xF4 += (gp->u.map.xE4 - gp->u.map.xF4) / gp->u.map.x104;
            gp->u.map.xF8 += (gp->u.map.xE8 - gp->u.map.xF8) / gp->u.map.x104;
            gp->u.map.xFC +=
                ((gp->u.map.xEC - gp->u.map.xFC) / gp->u.map.x104);
            sp10.r = gp->u.map.xF4;
            sp10.g = gp->u.map.xF8;
            sp10.b = gp->u.map.xFC;
        } else {
            sp10.r = gp->u.map.xE4;
            sp10.g = gp->u.map.xE8;
            sp10.b = gp->u.map.xEC;
            gp->u.map.xC4_b27 = true;
        }
        Ground_801C205C(&sp10);
        Camera_SetBackgroundColor(sp10.r, sp10.g, sp10.b);
    }
}

static void grLast_8021C640(void)
{
    GXColor sp8 = { 0x0C, 0x06, 0x28, 0xFF };
    Ground_801C052C(&sp8);
    Ground_801C05D4(&sp8);
    Ground_801C0544(&sp8);
    Ground_801C058C(&sp8);
    Ground_801C05EC(&sp8);
    Ground_801C05A4(&sp8);
    Ground_801C055C(&sp8);
    Ground_801C05BC(&sp8);
    Ground_801C0574(&sp8);
}

static void grLast_8021C6AC(void)
{
    GXColor sp1C = { 0x8C, 0xB4, 0xBE, 0xFF };
    GXColor sp18 = { 0x96, 0xB4, 0xBE, 0xFF };
    GXColor sp14 = { 0x6E, 0x78, 0x8C, 0xFF };
    GXColor sp10 = { 0x00, 0x00, 0x00, 0xFF };
    GXColor spC = { 0x73, 0xA0, 0x91, 0xFF };
    GXColor sp8 = { 0x87, 0xA5, 0xA0, 0xFF };
    Ground_801C052C(&sp1C);
    Ground_801C05D4(&sp18);
    Ground_801C0544(&sp1C);
    Ground_801C058C(&sp14);
    Ground_801C05EC(&sp10);
    Ground_801C05A4(&sp14);
    Ground_801C055C(&spC);
    Ground_801C05BC(&sp8);
    Ground_801C0574(&spC);
}

static DynamicsDesc* grLast_8021C740(int arg0)
{
    return NULL;
}

static bool grLast_8021C748(Vec3* v, int i, HSD_JObj* jobj)
{
    return true;
}
