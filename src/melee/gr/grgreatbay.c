#include "grgreatbay.h"

#include "placeholder.h"

#include <platform.h>

#include "baselib/psstructs.h"

#include "forward.h"

#include "ft/ft_0877.h"
#include "ft/ftdevice.h"
#include "ft/ftlib.h"
#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "it/it_266F.h"
#include "it/item.h"
#include "it/items/ittincle.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/types.h"
#include "mp/mplib.h"

#include <string.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

S16Vec3 grGb_803E3E60[] = { { 0, 2, 49 }, { 1, 1, 2 },  { 2, 1, 3 },
                            { 4, 1, 34 }, { 3, 1, 38 }, { 5, 10, 0 } };

StageCallbacks grGb_803E3E84[11] = {
    { grGreatBay_801F4404, grGreatBay_801F4430, grGreatBay_801F4438,
      grGreatBay_801F443C, 0 },
    { grGreatBay_801F4694, grGreatBay_801F4994, grGreatBay_801F499C,
      grGreatBay_801F545C, 0 },
    { grGreatBay_801F454C, grGreatBay_801F4650, grGreatBay_801F4658,
      grGreatBay_801F4690, 0xC0000000 },
    { grGreatBay_801F4440, grGreatBay_801F44A0, grGreatBay_801F44A8,
      grGreatBay_801F44AC, 0 },
    { grGreatBay_801F44B0, grGreatBay_801F4510, grGreatBay_801F4518,
      grGreatBay_801F451C, 0 },
    { grGreatBay_801F598C, grGreatBay_801F59F0, grGreatBay_801F59F8,
      grGreatBay_801F59FC, 0 },
    { grGreatBay_801F598C, grGreatBay_801F59F0, grGreatBay_801F59F8,
      grGreatBay_801F59FC, 0 },
    { grGreatBay_801F598C, grGreatBay_801F59F0, grGreatBay_801F59F8,
      grGreatBay_801F59FC, 0 },
    { grGreatBay_801F598C, grGreatBay_801F59F0, grGreatBay_801F59F8,
      grGreatBay_801F59FC, 0 },
    { grGreatBay_801F5A00, grGreatBay_801F5AF0, grGreatBay_801F5AF8,
      grGreatBay_801F5D48, 0 },
    { grGreatBay_801F5460, grGreatBay_801F55F8, grGreatBay_801F5600,
      grGreatBay_801F5988, 0 }
};

StageData grGb_803E3F6C = {
    GREATBAY,
    grGb_803E3E84,
    "/GrGb.dat",
    grGreatBay_801F4240,
    grGreatBay_801F423C,
    grGreatBay_801F42D0,
    grGreatBay_801F42D4,
    grGreatBay_801F42F8,
    grGreatBay_801F680C,
    grGreatBay_801F6814,
    (1 << 0),
    grGb_803E3E60,
    6,
};

typedef struct grGb_StageAttr {
    /* 0x00 */ s16 x0;
    /* 0x02 */ s16 x2;
    /* 0x04 */ f32 x4;
    /* 0x08 */ f32 x8;
    /* 0x0C */ f32 xC;
    /* 0x10 */ f32 x10;
    /* 0x14 */ f32 x14;
    /* 0x18 */ f32 x18;
    /* 0x1C */ f32 x1C;
    /* 0x20 */ f32 x20;
    /* 0x24 */ f32 x24;
    /* 0x28 */ f32 x28;
    /* 0x2C */ f32 x2C;
    /* 0x30 */ f32 x30;
    /* 0x34 */ f32 x34;
    /* 0x38 */ f32 x38;
    /* 0x3C */ f32 x3C;
    /* 0x40 */ f32 x40;
    /* 0x44 */ s16 x44;
    /* 0x46 */ s16 x46;
    /* 0x48 */ s16 x48;
    /* 0x4A */ s16 x4A;
    /* 0x4C */ f32 x4C;
    /* 0x50 */ f32 x50;
    /* 0x54 */ f32 x54;
    /* 0x58 */ f32 x58;
    /* 0x5C */ f32 x5C;
    /* 0x60 */ f32 x60;
    /* 0x64 */ f32 x64;
    /* 0x68 */ f32 x68;
    /* 0x6C */ f32 x6C;
    /* 0x70 */ s16 x70[4];
    /* 0x78 */ f32 x78;
    /* 0x7C */ struct {
        s16 kind;
        s16 weight;
    } x7C[10];
} grGb_StageAttr;

typedef struct grGb_804D69E0_t {
    grGb_StageAttr* x0;
} grGb_804D69E0_t;
grGb_804D69E0_t grGb_804D69E0;

void grGreatBay_801F423C(bool unused)
{
    return;
}

void grGreatBay_801F4240(void)
{
    grGb_804D69E0.x0 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grGreatBay_801F4300(0);
    grGreatBay_801F4300(3);
    grGreatBay_801F4300(4);
    grGreatBay_801F4300(2);
    grGreatBay_801F4300(1);
    grGreatBay_801F4300(9);
    grGreatBay_801F4300(10);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grGreatBay_801F42D0(void) {}

void grGreatBay_801F42D4(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grGreatBay_801F42F8(void)
{
    return false;
}

HSD_GObj* grGreatBay_801F4300(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grGb_803E3E84[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
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
            if (gobj_id == 10) {
                HSD_GObj_SetupProc(gobj, callbacks->callback2, 5);
            } else {
                HSD_GObj_SetupProc(gobj, callbacks->callback2, 4);
            }
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 247, gobj_id);
    }

    return gobj;
}

void grGreatBay_801F4404(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grGreatBay_801F4430(Ground_GObj* gobj)
{
    return false;
}

void grGreatBay_801F4438(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F443C(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F4440(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C77FC(gobj, 0, 7);
    gp->x11_flags.b012 = 1;
}

bool grGreatBay_801F44A0(Ground_GObj* gobj)
{
    return false;
}

void grGreatBay_801F44A8(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F44AC(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F44B0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C77FC(gobj, 0, 7);
    gp->x11_flags.b012 = 3;
}

bool grGreatBay_801F4510(Ground_GObj* gobj)
{
    return false;
}

void grGreatBay_801F4518(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F451C(Ground_GObj* gobj)
{
    return;
}

void fn_801F4520(HSD_GObj* gobj)
{
    ftCo_800C07F8(gobj, 6, grGreatBay_801F6708);
}

void grGreatBay_801F454C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->x11_flags.b012 = 1;
    gp->xC_callback = NULL;
    gp->x10_flags.b5 = 1;

    Ground_801C4E70(Ground_801C3FA4(gobj, 4), Ground_801C3FA4(gobj, 1),
                    Ground_801C3FA4(gobj, 3), Ground_801C3FA4(gobj, 2),
                    Ground_801C3FA4(gobj, 6), Ground_801C3FA4(gobj, 5));
    mpLib_80057BC0(1);
    grGreatBay_801F5D4C(gobj);
    Ground_801C10B8(gobj, fn_801F4520);
}

bool grGreatBay_801F4650(Ground_GObj* gobj)
{
    return false;
}

void grGreatBay_801F4658(Ground_GObj* gobj)
{
    grGreatBay_801F5E28(gobj);
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

void grGreatBay_801F4690(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F4694(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Vec3 scale;
    s16 max_val, min_val;
    f32 factor;

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);

    HSD_JObjGetScale(jobj, &scale);
    factor = grGb_804D69E0.x0->x68;
    scale.x *= factor;
    scale.y *= factor;
    scale.z *= factor;
    HSD_JObjSetScale(jobj, &scale);

    HSD_JObjSetTranslateX(jobj, grGb_804D69E0.x0->x4C + grGb_804D69E0.x0->x54);
    HSD_JObjSetTranslateY(jobj, grGb_804D69E0.x0->x50);

    gp->gv.greatbay.xCC = HSD_JObjGetTranslationY(Ground_801C3FA4(gobj, 2));

    gp->gv.greatbay.xC4 = 0;
    gp->gv.greatbay.xC5.b0123456 = 0;

    max_val = grGb_804D69E0.x0->x46;
    min_val = grGb_804D69E0.x0->x44;
    gp->gv.greatbay.xC6 = rand_range(max_val, min_val);

    gp->gv.greatbay.xC5.b7 = 1;
    gp->gv.greatbay.xC8 = NULL;
    gp->x10_flags.b5 = 1;
    gp->x11_flags.b012 = 1;
}

bool grGreatBay_801F4994(Ground_GObj* gobj)
{
    return false;
}

void grGreatBay_801F499C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* jobj2 = Ground_801C3FA4(gobj, 2);
    HSD_JObj* jobj3 = Ground_801C3FA4(gobj, 3);
    Vec3 pos;

    HSD_ASSERT(529, jobj);
    HSD_ASSERT(530, jobj2);

    switch (gp->gv.greatbay.xC4) {
    case 0: {
        if (gp->gv.greatbay.xC6 < 0) {
            if (grAnime_801C84A4(gobj, 0, 7)) {
                gp->gv.greatbay.xC4 = 1;
                grAnime_801C8138(gobj, gp->map_id, 1);
                gp->gv.greatbay.xC6 = 0;
                mpLib_80058044(2);
                mpLib_80058044(3);
                mpLib_80058044(4);
                mpLib_80058044(1);
            }
        } else {
            gp->gv.greatbay.xC6--;
        }
        break;
    }
    case 1: {
        s16 timer = gp->gv.greatbay.xC6;
        gp->gv.greatbay.xC6 = timer + 1;
        if (timer == 90) {
            Ground_801C53EC(0x57E42);
            lb_8000B1CC(jobj, NULL, &pos);
            gp->gv.greatbay.xC8 = grLib_801C96F8(0x7531, 0x1E, &pos);
        }
        if (grAnime_801C83D0(gobj, 0, 7)) {
            gp->gv.greatbay.xC4 = 3;
            gp->gv.greatbay.xC6 =
                rand_range(grGb_804D69E0.x0->x4A, grGb_804D69E0.x0->x48);
            grAnime_801C7A04(gobj, 0, 7, 0.0f);
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
            if (gp->gv.greatbay.xC8 != NULL) {
                grLib_801C9874(gp->gv.greatbay.xC8);
                gp->gv.greatbay.xC8 = NULL;
            }
        }
        break;
    }
    case 2: {
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        gp->gv.greatbay.xC6++;
        if (gp->gv.greatbay.xC6 == 60) {
            Ground_801C53EC(0x57E41);
            lb_8000B1CC(jobj, NULL, &pos);
            gp->gv.greatbay.xC8 = grLib_801C96F8(0x7531, 0x1E, &pos);
        }
        {
            if (gp->gv.greatbay.xC6 == 60 || gp->gv.greatbay.xC6 == 120) {
                HSD_JObj* j = Ground_801C3FA4(gobj, 34);
                if (j != NULL) {
                    grLib_801C97DC(0x7533, 0x1E, j);
                }
            }
        }
        {
            if (gp->gv.greatbay.xC6 == 90 || gp->gv.greatbay.xC6 == 150) {
                HSD_JObj* j = Ground_801C3FA4(gobj, 38);
                if (j != NULL) {
                    grLib_801C97DC(0x7533, 0x1E, j);
                }
            }
        }
        if (grAnime_801C83D0(gobj, 0, 7)) {
            gp->gv.greatbay.xC4 = 0;
            gp->gv.greatbay.xC6 =
                rand_range(grGb_804D69E0.x0->x46, grGb_804D69E0.x0->x44);
            grAnime_801C8138(gobj, gp->map_id, 0);
            mpLib_80057FDC(2);
            mpLib_80057FDC(3);
            mpLib_80057FDC(4);
            mpLib_80057FDC(1);
            if (gp->gv.greatbay.xC8 != NULL) {
                grLib_801C9874(gp->gv.greatbay.xC8);
                gp->gv.greatbay.xC8 = NULL;
            }
        }
        break;
    }
    case 3: {
        s16 timer = gp->gv.greatbay.xC6;
        gp->gv.greatbay.xC6 = timer - 1;
        if (timer < 0) {
            gp->gv.greatbay.xC4 = 2;
            grAnime_801C8138(gobj, gp->map_id, 2);
            gp->gv.greatbay.xC6 = 0;
            gp->gv.greatbay.xC5.b7 = 0;
            gp->gv.greatbay.xC5.b0123456 =
                grGreatBay_801F62F8(gp->gv.greatbay.xC5.b0123456);
            switch (gp->gv.greatbay.xC5.b0123456) {
            case 1: {
                s32 max_x =
                    rand_range(grGb_804D69E0.x0->x64, grGb_804D69E0.x0->x60);
                HSD_JObjSetTranslateX(jobj, grGb_804D69E0.x0->x4C + max_x);
                mpLib_80057BC0(2);
                mpLib_80057BC0(3);
                mpLib_80057BC0(4);
                mpJointListAdd(1);
                break;
            }
            case 2:
                HSD_ASSERT(652, 0);
                break;
            case 0: {
                s32 max_x =
                    rand_range(grGb_804D69E0.x0->x5C, grGb_804D69E0.x0->x58);
                HSD_JObjSetTranslateX(jobj, grGb_804D69E0.x0->x4C + max_x);
                mpJointListAdd(2);
                mpJointListAdd(3);
                mpJointListAdd(4);
                mpLib_80057BC0(1);
                break;
            }
            case 3: {
                s32 max_x =
                    rand_range(grGb_804D69E0.x0->x64, grGb_804D69E0.x0->x60);
                HSD_JObjSetTranslateX(jobj, grGb_804D69E0.x0->x4C + max_x);
                mpLib_80057BC0(2);
                mpLib_80057BC0(3);
                mpLib_80057BC0(4);
                mpJointListAdd(1);
                break;
            }
            }
        }
        break;
    }
    }

    {
        f32 y = HSD_JObjGetTranslationY(jobj2);
        if (gp->gv.greatbay.xCC != y) {
            y *= grGb_804D69E0.x0->x6C;
            HSD_JObjSetTranslateY(jobj2, y);
            gp->gv.greatbay.xCC = y;
        }
    }

    switch (gp->gv.greatbay.xC5.b0123456) {
    case 1:
        HSD_JObjSetRotationY(jobj3, 1.5707964f);
        break;
    case 2:
        HSD_ASSERT(692, 0);
        break;
    case 0:
        HSD_JObjSetRotationY(jobj2, 0.0f);
        break;
    case 3:
        HSD_JObjSetRotationY(jobj3, -1.5707964f);
        break;
    }

    Ground_801C2FE0(gobj);
    grGreatBay_801F660C(gobj);
    mpLib_80055E24(2);

    if (gp->gv.greatbay.xC4 == 2 && !gp->gv.greatbay.xC5.b7) {
        gp->gv.greatbay.xC5.b7 = grGreatBay_801F63F4(gobj);
    }
}

void grGreatBay_801F545C(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F5460(Ground_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    Ground* gp = GET_GROUND(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    gp->xC_callback = NULL;
    mpJointSetCb1(5, gp, grGreatBay_801F5914);
    mpJointListAdd(5);
    HSD_JObjSetTranslateX(jobj, 1000.0f);
    HSD_JObjSetTranslateY(jobj, 1000.0f);
    Ground_801C2FE0(gobj);
    mpLib_80057424(5);
    gp->gv.greatbay4.xF0 = it_802ECA70(gobj);
    gp->gv.greatbay4.xC4 = 0;
    gp->gv.greatbay4.xC8 = 0;
    gp->gv.greatbay4.xD0 = 0;
    gp->gv.greatbay4.xCC = 0;
    gp->gv.greatbay4.xD8 = 0;
    gp->gv.greatbay4.xDC = 0;
    gp->gv.greatbay4.xE0 = 0.0f;
}

bool grGreatBay_801F55F8(Ground_GObj* gobj)
{
    return false;
}

void grGreatBay_801F5600(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    Vec3 pos;

    it_802ECCA4(gp->gv.greatbay4.xF0, &gp->gv.greatbay4.xC4,
                &gp->gv.greatbay4.xE4);
    if (gp->gv.greatbay4.xE4.y < -50.0f) {
        it_802EC830(gp->gv.greatbay4.xF0);
        mpLib_80057424(5);
        gp->gv.greatbay4.xF0 = it_802ECA70(gobj);
        gp->gv.greatbay4.xC4 = 0;
        gp->gv.greatbay4.xC8 = 0;
        gp->gv.greatbay4.xD0 = 0;
        gp->gv.greatbay4.xCC = 0;
        gp->gv.greatbay4.xD8 = 0;
        gp->gv.greatbay4.xDC = 0;
        gp->gv.greatbay4.xE0 = 0.0f;
        return;
    }
    it_802ECC98(gp->gv.greatbay4.xF0, gp->gv.greatbay4.xE0);
    switch (gp->gv.greatbay4.xC4) {
    case 1:
        mpJointListAdd(5);
        Ground_801C2FE0(gobj);
        break;
    case 2:
    case 5:
        if (gp->gv.greatbay4.xD8 != 0 && gp->gv.greatbay4.xD4 == 0) {
            it_802EBD14(gp->gv.greatbay4.xF0);
        }
        break;
    case 4:
        if (gp->gv.greatbay4.xD8 == 0) {
            it_802EBFAC(gp->gv.greatbay4.xF0);
        } else if (gp->gv.greatbay4.xDC != gp->gv.greatbay4.xD8) {
            it_802EBD14(gp->gv.greatbay4.xF0);
        }
        break;
    case 6:
    case 7:
        if (gp->gv.greatbay4.xCC == 0 &&
            it_802ECC8C(gp->gv.greatbay4.xF0) == 0)
        {
            pos = gp->gv.greatbay4.xE4;
            pos.y += 10.0f;
            grLib_801C96F8(0x7534, 0x1E, &pos);
            Ground_801C53EC(0x57E4A);
            gp->gv.greatbay4.xCC = 1;
        }
        mpLib_80057BC0(5);
        break;
    case 8:
        if (gp->gv.greatbay4.xD0 == 0 && gp->gv.greatbay4.xE4.y <= 0.0f) {
            gp->gv.greatbay4.xD0 = 1;
            grLib_801C96F8(0x7537, 0x1E, &gp->gv.greatbay4.xE4);
            Ground_801C53EC(0x57E48);
        }
        break;
    case 9:
        if (gp->gv.greatbay4.xC8 != gp->gv.greatbay4.xC4) {
            Ground_801C53EC(0x57E47);
        }
        break;
    case 12:
        if (gp->gv.greatbay4.xC8 != gp->gv.greatbay4.xC4) {
            gp->gv.greatbay4.xCC = 0;
            mpJointListAdd(5);
        }
        if (gp->gv.greatbay4.xD8 != 0) {
            it_802EBD14(gp->gv.greatbay4.xF0);
        }
        break;
    }
    gp->gv.greatbay4.xC8 = gp->gv.greatbay4.xC4;
    HSD_JObjSetTranslate(jobj, &gp->gv.greatbay4.xE4);
    Ground_801C2FE0(gobj);
    gp->gv.greatbay4.xDC = gp->gv.greatbay4.xD8;
    gp->gv.greatbay4.xD8 = 0;
    gp->gv.greatbay4.xE0 = 0.0f;
    Ground_801C2FE0(gobj);
}

void grGreatBay_801F5914(Ground* arg0, s32 arg1, CollData* arg2, s32 arg3,
                         enum mpLib_GroundEnum arg4, f32 farg0)
{
    s32 temp_r0;
    PAD_STACK(12);

    temp_r0 = arg2->x34_flags.b1234;
    if (temp_r0 == 1 || (s32) temp_r0 == 2 || temp_r0 == 3) {
        arg0->gv.greatbay.xD4 =
            ((u32) arg2->env_flags & Collide_LedgeGrabMask);
        arg0->gv.greatbay.xD8 += 1;
        arg0->gv.greatbay.xE0 += arg3 / 100.0f;
    }
}

void grGreatBay_801F5988(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F598C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C7A04(gobj, 0, 7, 0.0f);
    gp->x11_flags.b012 = 2;
}

bool grGreatBay_801F59F0(Ground_GObj* gobj)
{
    return false;
}

void grGreatBay_801F59F8(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F59FC(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F5A00(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    s16 max_val, min_val;

    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C7A04(gobj, 0, 7, 0.0f);
    gp->gv.greatbay2.gobjs[0] = grGreatBay_801F4300(5);
    gp->gv.greatbay2.gobjs[1] = grGreatBay_801F4300(6);
    gp->gv.greatbay2.gobjs[2] = grGreatBay_801F4300(7);
    gp->gv.greatbay2.gobjs[3] = grGreatBay_801F4300(8);

    max_val = grGb_804D69E0.x0->x2;
    min_val = grGb_804D69E0.x0->x0;
    gp->gv.greatbay2.x10 = rand_range(max_val, min_val);

    gp->x11_flags.b012 = 2;
}

bool grGreatBay_801F5AF0(Ground_GObj* gobj)
{
    return false;
}

void grGreatBay_801F5AF8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    s32 i;
    PAD_STACK(8);

    if (gp->gv.greatbay2.x10 > 0) {
        gp->gv.greatbay2.x10 = gp->gv.greatbay2.x10 - 1;
        if (gp->gv.greatbay2.x10 == 0) {
            grAnime_801C8138(gobj, gp->map_id, 0);
            grAnime_801C7A04(gobj, 0, 7, 1.0f);
            for (i = 0; i < 4; i++) {
                HSD_GObj* g = gp->gv.greatbay2.gobjs[i];
                if (g != NULL) {
                    Ground* child_gp = GET_GROUND(g);
                    if (child_gp != NULL) {
                        grAnime_801C8138(gp->gv.greatbay2.gobjs[i],
                                         child_gp->map_id, 0);
                        grAnime_801C7A04(gp->gv.greatbay2.gobjs[i], 0, 7,
                                         1.0f);
                    }
                }
            }
            gp->gv.greatbay2.x12.b0 = 0;
            gp->gv.greatbay2.x12.b1 = 0;
            gp->gv.greatbay2.x12.b2 = 0;
            gp->gv.greatbay2.x12.b3 = 0;
        }
    } else {
        f32 frame = Ground_801C3F20(jobj);
        if (!gp->gv.greatbay2.x12.b0 && frame > 0.0f) {
            gp->gv.greatbay2.x12.b0 = 1;
        }
        if (!gp->gv.greatbay2.x12.b1 && frame > 0.0f) {
            gp->gv.greatbay2.x12.b1 = 1;
        }
        if (!gp->gv.greatbay2.x12.b2 && frame > 0.0f) {
            gp->gv.greatbay2.x12.b2 = 1;
        }
        if (!gp->gv.greatbay2.x12.b3 && frame > 0.0f) {
            gp->gv.greatbay2.x12.b3 = 1;
        }
        if (lb_8000B134(GET_JOBJ(gobj))) {
            grAnime_801C7A04(gobj, 0, 7, 0.0f);
            for (i = 0; i < 4; i++) {
                if (gp->gv.greatbay2.gobjs[i] != NULL) {
                    grAnime_801C7A04(gp->gv.greatbay2.gobjs[i], 0, 7, 0.0f);
                }
            };
            gp->gv.greatbay2.x10 =
                rand_range(grGb_804D69E0.x0->x2, grGb_804D69E0.x0->x0);
        }
    }
}

void grGreatBay_801F5D48(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F5D4C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj;
    PAD_STACK(16);

    mpJointSetCb1(0, gp, grGreatBay_801F60C4);
    jobj = Ground_801C3FA4(gobj, 49);
    gp->gv.greatbay3.jobj = jobj;
    if (jobj != NULL) {
        gp->gv.greatbay3.translation.x =
            HSD_JObjGetTranslationX(gp->gv.greatbay3.jobj);
        gp->gv.greatbay3.translation.y =
            HSD_JObjGetTranslationY(gp->gv.greatbay3.jobj);
    } else {
        HSD_ASSERT(1132, 0);
    }
    gp->gv.greatbay3.translation.z = 0.0f;
    gp->gv.greatbay3.xD0 = 0.0f;
    gp->gv.greatbay3.xD4 = 0.0f;
    gp->gv.greatbay3.xD8 = 0.0f;
    gp->gv.greatbay3.xDC = 0.0f;
    gp->gv.greatbay3.xE0 = 0.0f;
}

void grGreatBay_801F5E28(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = gp->gv.greatbay3.jobj;
    PAD_STACK(8);

    if (jobj != NULL) {
        f32 delta, factor;

        delta = gp->gv.greatbay3.translation.z - gp->gv.greatbay3.xD8;
        if (-gp->gv.greatbay3.xD8 * delta < 0.0f) {
            factor = grGb_804D69E0.x0->x14;
        } else {
            factor = grGb_804D69E0.x0->x18;
        }
        gp->gv.greatbay3.xD8 += delta * factor;

        delta = gp->gv.greatbay3.xD0 - gp->gv.greatbay3.xDC;
        if (-gp->gv.greatbay3.xDC * delta < 0.0f) {
            factor = grGb_804D69E0.x0->x28;
        } else {
            factor = grGb_804D69E0.x0->x2C;
        }
        gp->gv.greatbay3.xDC += delta * factor;

        delta = gp->gv.greatbay3.xD4 - gp->gv.greatbay3.xE0;
        if (delta < 0.0f) {
            factor = grGb_804D69E0.x0->x40;
        } else {
            factor = grGb_804D69E0.x0->x3C;
        }
        gp->gv.greatbay3.xE0 += delta * factor;

        HSD_JObjSetRotationZ(jobj, gp->gv.greatbay3.xD8);
        HSD_JObjSetTranslateX(jobj, gp->gv.greatbay3.translation.x +
                                        gp->gv.greatbay3.xDC);
        HSD_JObjSetTranslateY(jobj, gp->gv.greatbay3.translation.y +
                                        gp->gv.greatbay3.xE0);

        gp->gv.greatbay3.translation.z = 0.0f;
        gp->gv.greatbay3.xD0 = 0.0f;
        gp->gv.greatbay3.xD4 = 0.0f;
    }
}

void grGreatBay_801F60C4(Ground* gp, s32 arg1, CollData* arg2, s32 arg3,
                         enum mpLib_GroundEnum arg4, f32 farg0)
{
    Vec3 pos;
    s32 damage = arg3;
    s32 temp_r0;
    PAD_STACK(12);

    temp_r0 = arg2->x34_flags.b1234;
    if (temp_r0 == 1 || temp_r0 == 3) {
        HSD_JObj* jobj;
        if (arg4 == 1) {
            damage = (s32) ((f32) damage * grGb_804D69E0.x0->x4);
        }
        jobj = gp->gv.greatbay3.jobj;
        if (jobj != NULL) {
            f32 dx, abs_dx, t, rot_amount, disp_amount, y_amount;
            lb_8000B1CC(jobj, NULL, &pos);
            dx = arg2->cur_pos.x - pos.x;
            t = ABS(dx) / 15.0f;
            if (t > 1.0f) {
                t = 1.0f;
            }
            rot_amount = t * (0.017453292f * (damage * grGb_804D69E0.x0->x8 +
                                              grGb_804D69E0.x0->xC));
            disp_amount =
                t * (damage * grGb_804D69E0.x0->x1C + grGb_804D69E0.x0->x20);
            y_amount = damage * grGb_804D69E0.x0->x30 + grGb_804D69E0.x0->x34;
            if (dx < 0.0f) {
                gp->gv.greatbay3.translation.z += rot_amount;
                {
                    f32 max = grGb_804D69E0.x0->x10;
                    if (gp->gv.greatbay3.translation.z > max) {
                        gp->gv.greatbay3.translation.z = max;
                    }
                }
                gp->gv.greatbay3.xD0 += disp_amount;
                {
                    f32 max = grGb_804D69E0.x0->x24;
                    if (gp->gv.greatbay3.xD0 > max) {
                        gp->gv.greatbay3.xD0 = max;
                    }
                }
            } else {
                gp->gv.greatbay3.translation.z -= rot_amount;
                {
                    f32 min = -grGb_804D69E0.x0->x10;
                    if (gp->gv.greatbay3.translation.z < min) {
                        gp->gv.greatbay3.translation.z = min;
                    }
                }
                gp->gv.greatbay3.xD0 -= disp_amount;
                {
                    f32 min = -grGb_804D69E0.x0->x24;
                    if (gp->gv.greatbay3.xD0 < min) {
                        gp->gv.greatbay3.xD0 = min;
                    }
                }
            }
            gp->gv.greatbay3.xD4 -= y_amount;
            {
                f32 min = -grGb_804D69E0.x0->x38;
                if (gp->gv.greatbay3.xD4 < min) {
                    gp->gv.greatbay3.xD4 = min;
                }
            }
        }
    }
}

s32 grGreatBay_801F62F8(s32 current)
{
    s32 result;
    s32 i = 0;
    grGb_StageAttr* attr;
    s32 total;
    s32 rand;

    do {
        current += 0;
        attr = grGb_804D69E0.x0;
        total = attr->x70[0] + attr->x70[1] + attr->x70[3] + attr->x70[2];
        rand = ZRANDI(total);

        attr = grGb_804D69E0.x0;
        if ((rand -= attr->x70[2]) < 0) {
            result = 1;
        } else if (0 > (rand -= attr->x70[1])) {
            result = 2;
        } else if ((rand -= attr->x70[0]) < 0) {
            result = 0;
        } else if ((rand = rand - attr->x70[3]) < 0) {
            result = 3;
        } else {
            HSD_ASSERT(1277, 0);
        }

        if (current != result) {
            goto done;
        }
    } while (i++ <= 1000);
    result = 0;

done:
    return result;
}

extern Vec3 grGb_803B81C8;
extern SpawnItem grGb_803B81D4;

bool grGreatBay_801F63F4(Ground_GObj* gobj)
{
    Vec3 rot;
    Vec3 pos;
    SpawnItem spawn;
    HSD_JObj* jobj;
    s32 total, rand, i, offset;
    s32 selected;
    PAD_STACK(8);

    rot = grGb_803B81C8;
    jobj = Ground_801C3FA4(gobj, 2);
    if (jobj == NULL) {
        return false;
    }
    lb_8000B1CC(jobj, &rot, &pos);
    pos.z = 0.0f;
    if (pos.y <= Stage_GetBlastZoneBottomOffset()) {
        return false;
    }
    if (HSD_Randf() > grGb_804D69E0.x0->x78) {
        return true;
    }

    total = 0;
    offset = 0;
    for (i = 0; i < 10; i++) {
        s16 item_id = grGb_804D69E0.x0->x7C[offset / 4].kind;
        if (item_id != -1 && it_8026D324(item_id)) {
            total += grGb_804D69E0.x0->x7C[offset / 4].weight;
        }
        offset += 4;
    }

    if (total == 0) {
        return true;
    }

    selected = -1;
    rand = ZRANDI(total);

    offset = 0;
    for (i = 0; i < 10; i++) {
        s16 item_id = grGb_804D69E0.x0->x7C[offset / 4].kind;
        if (item_id != -1 && it_8026D324(item_id)) {
            rand -= grGb_804D69E0.x0->x7C[offset / 4].weight;
            if (rand < 0) {
                selected = grGb_804D69E0.x0->x7C[i].kind;
                break;
            }
        }
        offset += 4;
    }
    if (selected == -1) {
        return true;
    }

    spawn = grGb_803B81D4;
    spawn.kind = selected;
    spawn.prev_pos = pos;
    spawn.pos = spawn.prev_pos;
    Item_80268B18(&spawn);
    return true;
}

s16 grGb_803E4048[][2] = {
    { 32, 20 }, { 23, 18 }, { 22, 15 }, { 29, 16 },
    { 28, 17 }, { 27, 19 }, { 39, 21 }, { 0, 0 },
};

void grGreatBay_801F660C(Ground_GObj* gobj)
{
    u32 i;
    HSD_JObj* jobj;
    Vec3 pos;

    for (i = 0; i < 7; i++) {
        jobj = Ground_801C3FA4(gobj, grGb_803E4048[i][1]);
        HSD_ASSERT(1398, jobj);
        lb_8000B1CC(jobj, NULL, &pos);
        mpVtxSetPos(grGb_803E4048[i][0], pos.x, pos.y);
    }
}

bool grGreatBay_801F66A4(void)
{
    HSD_GObj* gobj;
    Ground* gp;

    if (stage_info.internal_stage_id == GREATBAY) {
        gobj = Ground_801C2BA4(1);
        if (gobj != NULL) {
            gp = GET_GROUND(gobj);
            if (gp != NULL) {
                if (gp->gv.greatbay.xC4 != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool grGreatBay_801F6708(u32 unk, HSD_GObj* gobj)
{
    Vec3 current;
    Vec3 previous;
    f32 arg;
    PAD_STACK(8);

    ftLib_80086644(gobj, &current);
    ftLib_80086684(gobj, &previous);
    if (ft_80087838(gobj) == false) {
        if (current.y < -5.0f) {
            if (previous.y > -5.0f) {
                arg = ftLib_80086B80(gobj) / 10.0f;
                current.y = -5.0f;
                grGreatBay_801F67A4(&current, arg);
                Ground_801C53EC(0x57E40);
            }
        }
    }

    return false;
}

void grGreatBay_801F67A4(Vec3* vec, f32 arg8)
{
    HSD_psAppSRT* temp_r3_2;
    HSD_Generator* temp_r3;

    temp_r3 = grLib_801C96F8(0x7537, 0x1E, vec);
    if (temp_r3 != NULL) {
        temp_r3_2 = temp_r3->appsrt;
        temp_r3_2->scale.x *= arg8;
        temp_r3_2->scale.y *= arg8;
        temp_r3_2->scale.z *= arg8;
    }
}

DynamicsDesc* grGreatBay_801F680C(enum_t unused)
{
    return NULL;
}

bool grGreatBay_801F6814(Vec3* a, int _, HSD_JObj* joint)
{
    Vec3 b;
    lb_8000B1CC(joint, NULL, &b);

    if (a->y > b.y) {
        return true;
    } else {
        return false;
    }
}
