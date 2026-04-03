#include "groldpupupu.h"

#include "baselib/forward.h"
#include "forward.h"

#include "ft/ftlib.h"
#include "gr/granime.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/random.h>
#include "ft/ftdevice.h"

static struct {
    s16 x0;
    s16 x2;
    int x4;
    int x8;
    int xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
}* grOp_804D6A98;

static void* grOp_804D6A9C;

static int grOp_804D48A0[1][2] = { { 4, 0 } };
static int grOp_804D48A8[1][2] = { { 5, 1 } };
static int grOp_804D48B0[1][2] = { { 2, 3 } };

static int grOp_804D48E0[1][2] = { { 0, 0 } };

StageCallbacks grOp_803E6688[9] = {
    { grOldPupupu_8021099C, grOldPupupu_802109C8, grOldPupupu_802109D0,
      grOldPupupu_802109D4, 0 },
    { grOldPupupu_802109D8, grOldPupupu_80210A1C, grOldPupupu_80210A24,
      grOldPupupu_80210B00, 0 },
    { grOldPupupu_80210BE4, grOldPupupu_80210C2C, grOldPupupu_80210C34,
      grOldPupupu_80210C78, 0 },
    { grOldPupupu_80211110, grOldPupupu_8021118C, grOldPupupu_80211194,
      grOldPupupu_80211198, 0 },
    { grOldPupupu_80210B04, grOldPupupu_80210B48, grOldPupupu_80210B50,
      grOldPupupu_80210B54, 0 },
    { grOldPupupu_80210B58, grOldPupupu_80210BB8, grOldPupupu_80210BC0,
      grOldPupupu_80210BE0, 0xC0000000 },
    { grOldPupupu_80211C10, grOldPupupu_80211C14, grOldPupupu_80211C1C,
      grOldPupupu_80211C9C, 0 },
    { grOldPupupu_8021119C, grOldPupupu_80211284, grOldPupupu_802113E0,
      grOldPupupu_80211C0C, 0 },
    { grOldPupupu_80210C7C, grOldPupupu_80210D08, grOldPupupu_80210D10,
      grOldPupupu_8021110C, 0 },
};

void grOldPupupu_802107DC(bool arg) {}

void grOldPupupu_802107E0(void)
{
    PAD_STACK(8);

    grOp_804D6A98 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grOldPupupu_802108B4(0);
    grOldPupupu_802108B4(3);
    grOldPupupu_802108B4(7);
    grOldPupupu_802108B4(5);
    grOldPupupu_802108B4(4);
    grOldPupupu_802108B4(6);
    grOldPupupu_802108B4(1);
    grOldPupupu_802108B4(8);
    Ground_801C39C0();
    Ground_801C3BB4();
    grOp_804D6A9C = NULL;
}

void grOldPupupu_80210884(void) {}

void grOldPupupu_80210888(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grOldPupupu_802108AC(void)
{
    return false;
}

HSD_GObj* grOldPupupu_802108B4(int arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grOp_803E6688[arg0];

    gobj = Ground_GetStageGObj(arg0);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "groldpupupu.c", 0xD9,
                 arg0);
    }

    return gobj;
}

void grOldPupupu_8021099C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grOldPupupu_802109C8(Ground_GObj* gobj)
{
    return false;
}

void grOldPupupu_802109D0(Ground_GObj* arg) {}

void grOldPupupu_802109D4(Ground_GObj* arg) {}

void grOldPupupu_802109D8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    gp->gv.unk.xC4 = 0;
    gp->gv.unk.xC8 = 0;
    gp->gv.unk.xCC = 0;
    gp->gv.unk.xD0 = 1;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grOldPupupu_80210A1C(Ground_GObj* gobj)
{
    return false;
}

void grOldPupupu_80210A24(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    if ((int) grOp_804D6A9C == 0 && gp->gv.unk.xD0 == 1) {
        gp->gv.unk.xD0 = 0;
        switch (gp->gv.unk.xC8) {
        case 0:
            grAnime_801C8138(
                gobj, gp->map_id,
                grOp_804D48A0[gp->gv.unk.xCC][gp->gv.unk.xD4]);
            break;
        case 1:
            grAnime_801C8138(
                gobj, gp->map_id,
                grOp_804D48B0[gp->gv.unk.xCC][gp->gv.unk.xD4]);
            break;
        case 2:
            grAnime_801C8138(
                gobj, gp->map_id,
                grOp_804D48A8[gp->gv.unk.xCC][gp->gv.unk.xD4]);
            break;
        }
    }
}

void grOldPupupu_80210B00(Ground_GObj* arg) {}

void grOldPupupu_80210B04(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x10_flags.b5 = 1;
}

bool grOldPupupu_80210B48(Ground_GObj* gobj)
{
    return false;
}

void grOldPupupu_80210B50(Ground_GObj* arg) {}

void grOldPupupu_80210B54(Ground_GObj* arg) {}

void grOldPupupu_80210B58(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 1;
}

bool grOldPupupu_80210BB8(Ground_GObj* gobj)
{
    return false;
}

void grOldPupupu_80210BC0(Ground_GObj* gobj)
{
    lb_800115F4();
}

void grOldPupupu_80210BE0(Ground_GObj* arg) {}

void grOldPupupu_80210BE4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObjSetFlagsAll(GET_JOBJ(gobj), JOBJ_HIDDEN);
    gp->x11_flags.b012 = 2;
}

bool grOldPupupu_80210C2C(Ground_GObj* gobj)
{
    return false;
}

void grOldPupupu_80210C34(Ground_GObj* gobj)
{
    PAD_STACK(8);
    if (grAnime_801C83D0(gobj, 0, 7) != 0) {
        Ground_801C4A08(gobj);
    }
}

void grOldPupupu_80210C78(Ground_GObj* arg) {}

void grOldPupupu_80210C7C(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    s16 x2, x0;

    x2 = grOp_804D6A98->x2;
    x0 = grOp_804D6A98->x0;
    *(s16*) &gp->gv.unk.xC4 =
        x2 > x0
            ? x0 + (x2 - x0 != 0 ? HSD_Randi(x2 - x0) : 0)
        : x2 < x0
            ? x2 + (x0 - x2 != 0 ? HSD_Randi(x0 - x2) : 0)
            : x2;
}

bool grOldPupupu_80210D08(Ground_GObj* gobj)
{
    return false;
}

/// #grOldPupupu_80210D10

void grOldPupupu_8021110C(Ground_GObj* arg) {}

void grOldPupupu_80211110(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(16);
    grAnime_801C8138(gobj, gp->map_id, 0);
    ((Ground*) gobj->user_data)->x10_flags.b2 = 0;
    grMaterial_801C8858(jobj, 0x28000000U);
    gp->x11_flags.b012 = 2;
}

bool grOldPupupu_8021118C(Ground_GObj* gobj)
{
    return false;
}

void grOldPupupu_80211194(Ground_GObj* arg) {}

void grOldPupupu_80211198(Ground_GObj* arg) {}

void grOldPupupu_8021119C(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    s32 max;
    s32 min;

    ftCo_800C06E8(gobj, 0xA, fn_802112F4);
    gp->gv.unk.xC4 = 0;
    gp->gv.unk.xC8 = 0;
    gp->gv.unk.xCC = 0;

    max = grOp_804D6A98->xC;
    min = grOp_804D6A98->x8;

    if (max > min) {
        s32 range = max - min;
        if (range != 0) {
            max = min + HSD_Randi(range);
        } else {
            max = min;
        }
    } else if (max < min) {
        s32 range = min - max;
        if (range != 0) {
            max += HSD_Randi(range);
        }
    }

    gp->gv.unk.xD0 = max;
    gp->gv.unk.xD4 = 1;
    gp->gv.unk.xE0 = 0;
    gp->gv.unk.xD8 = 1;
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 1;
}

bool grOldPupupu_80211284(Ground_GObj* gobj)
{
    return false;
}

bool grOldPupupu_8021128C(Vec* vec, f32 maxX, f32 minX, f32 maxY, f32 minY)
{
    float maxY_actual;
    float maxX_actual;
    if (maxX > minX) {
        maxX_actual = maxX;
    } else {
        maxX_actual = minX;
        minX = maxX;
    }
    if (maxY > minY) {
        maxY_actual = maxY;
    } else {
        maxY_actual = minY;
        minY = maxY;
    }
    if (minX < vec->x && vec->x < maxX_actual) {
        if (minY < vec->y && vec->y < maxY_actual) {
            return true;
        }
    }
    return false;
}

bool fn_802112F4(Ground_GObj* gobj, HSD_GObj* fighter_gobj, Vec3* vel)
{
    Ground* gp;
    Vec3 pos;
    PAD_STACK(8);

    ftLib_80086644(fighter_gobj, &pos);
    vel->y = 0.0F;
    vel->z = 0.0F;

    gp = gobj->user_data;
    switch (gp->gv.unk.xDC) {
    case 1:
        if (grOldPupupu_8021128C(&pos, grOp_804D6A98->x1C, grOp_804D6A98->x20,
                                 grOp_804D6A98->x24,
                                 grOp_804D6A98->x28) == true)
        {
            vel->x = -grOp_804D6A98->x10;
            return true;
        }
        break;
    case 2:
        if (grOldPupupu_8021128C(&pos, grOp_804D6A98->x18, grOp_804D6A98->x14,
                                 grOp_804D6A98->x24,
                                 grOp_804D6A98->x28) == true)
        {
            vel->x = grOp_804D6A98->x10;
            return true;
        }
        break;
    }

    vel->x = 0.0F;
    return false;
}

/// #grOldPupupu_802113E0

void grOldPupupu_80211C0C(Ground_GObj* arg) {}

void grOldPupupu_80211C10(Ground_GObj* arg) {}

bool grOldPupupu_80211C14(Ground_GObj* gobj)
{
    return false;
}

void grOldPupupu_80211C1C(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    Ground* other_gp = Ground_801C2BA4(7)->user_data;
    PAD_STACK(8);

    if (other_gp->gv.unk.xC8 == 2 && other_gp->gv.unk.xD4 != 0) {
        grAnime_801C8138(
            gobj, gp->map_id,
            grOp_804D48E0[other_gp->gv.unk.xCC][other_gp->gv.unk.xD8]);
    }
}

void grOldPupupu_80211C9C(Ground_GObj* arg) {}

DynamicsDesc* grOldPupupu_80211CA0(enum_t gobj)
{
    return false;
}

bool grOldPupupu_80211CA8(Vec3* a, int arg, HSD_JObj* joint)
{
    Vec3 b;

    lb_8000B1CC(joint, NULL, &b);

    if (a->y > b.y) {
        return true;
    } else {
        return false;
    }
}
