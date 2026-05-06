#include "groldpupupu.h"

#include "placeholder.h"

#include "baselib/forward.h"

#include "cm/camera.h"

#include "forward.h"

#include "ft/ftdevice.h"
#include "ft/ftlib.h"
#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"

#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

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
    f32 x2C;
    f32 x30;
}* grOp_804D6A98;

static void* grOp_804D6A9C;

static int grOp_804D48A0[1][2] = { { 4, 0 } };
static int grOp_804D48A8[1][2] = { { 5, 1 } };
static int grOp_804D48B0[1][2] = { { 2, 3 } };
static int grOp_804D48C8[1][2] = { { 4, 0 } };
static int grOp_804D48D0[1][2] = { { 5, 1 } };
static int grOp_804D48D8[1][2] = { { 2, 3 } };

static int grOp_804D48E0[1][2] = { { 0, 0 } };

typedef struct grOldPupupuSpawnDesc {
    s8 x0;
    s8 x1;
    s16 x2;
} grOldPupupuSpawnDesc;

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

char grOp_803E673C[] = "/GrOp.dat";

StageData grOp_803E6748 = {
    OLDPUPUPU,
    grOp_803E6688,
    grOp_803E673C,
    grOldPupupu_802107E0,
    grOldPupupu_802107DC,
    grOldPupupu_80210884,
    grOldPupupu_80210888,
    grOldPupupu_802108AC,
    grOldPupupu_80211CA0,
    grOldPupupu_80211CA8,
    1,
    0,
    0,
};

static grOldPupupuSpawnDesc grOp_803E67B0[10] = {
    { -1, 1, 1 }, { 1, 1, 3 },   { 1, 1, 5 },  { -1, 1, 7 },  { -1, 0, 9 },
    { 1, 0, 11 }, { -1, 0, 13 }, { 1, 0, 15 }, { -1, 0, 17 }, { 1, 0, 19 },
};

static int grOp_803E67D8[3] = { 0, 1, 2 };
static Vec3 grOp_803E67E4[2] = { { -1.0F, 0.0F, 0.0F }, { 1.0F, 0.0F, 0.0F } };

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
#pragma push
#pragma dont_inline on
HSD_GObj* grOldPupupu_802108B4_noinline(int arg0);
HSD_GObj* grOldPupupu_802108B4_noinline(int arg0)
{
    return grOldPupupu_802108B4(arg0);
}
#pragma dont_inline reset
#pragma pop

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
    gp->gv.oldpupupu.xC4 = 0;
    gp->gv.oldpupupu.xC8 = 0;
    gp->gv.oldpupupu.xCC = 0;
    gp->gv.oldpupupu.xD0 = 1;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grOldPupupu_80210A1C(Ground_GObj* gobj)
{
    return false;
}

void grOldPupupu_80210A24(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    if ((int) grOp_804D6A9C == 0 && gp->gv.oldpupupu.xD0 == 1) {
        gp->gv.oldpupupu.xD0 = 0;
        switch (gp->gv.oldpupupu.xC8) {
        case 0:
            grAnime_801C8138(
                gobj, gp->map_id,
                grOp_804D48A0[gp->gv.oldpupupu.xCC][gp->gv.oldpupupu.xD4]);
            break;
        case 1:
            grAnime_801C8138(
                gobj, gp->map_id,
                grOp_804D48B0[gp->gv.oldpupupu.xCC][gp->gv.oldpupupu.xD4]);
            break;
        case 2:
            grAnime_801C8138(
                gobj, gp->map_id,
                grOp_804D48A8[gp->gv.oldpupupu.xCC][gp->gv.oldpupupu.xD4]);
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
    gp->gv.oldpupupu2.xC4 =
        x2 > x0   ? x0 + (x2 - x0 != 0 ? HSD_Randi(x2 - x0) : 0)
        : x2 < x0 ? x2 + (x0 - x2 != 0 ? HSD_Randi(x0 - x2) : 0)
                  : x2;
}

bool grOldPupupu_80210D08(Ground_GObj* gobj)
{
    return false;
}

void grOldPupupu_80210D10(Ground_GObj* gobj)
{
    f32 cam_left;
    f32 cam_right;
    f32 cam_center;
    Ground* gp;
    HSD_GObj* spawn;
    HSD_JObj* jobj;
    f32 direction;
    f32 y;
    f32 x;
    f32 step;
    s16 timer;
    s16 min_respawn;
    s16 respawn;
    s32 count;
    s32 i;
    s32 index;

    PAD_STACK(0x10);
    gp = GET_GROUND(gobj);
    timer = gp->gv.oldpupupu2.xC4;
    gp->gv.oldpupupu2.xC4 = timer - 1;
    if (timer < 0) {
        direction = Ground_801C0498();
        index = HSD_Randi(10);
        if (grOp_803E67B0[index].x1 != 0 && HSD_Randi(5) == 0) {
            count = 3;
        } else {
            count = 1;
        }
        Camera_800307D0(&cam_left, &cam_center, &cam_right);
        if (grOp_803E67B0[index].x0 == 1) {
            step = -10.0F;
            if (cam_right < 200.0F) {
                cam_right = 200.0F;
            }
            x = -(((f32) count * -10.0F) - (50.0F + cam_right));
        } else {
            step = 10.0F;
            if (cam_left > -200.0F) {
                cam_left = -200.0F;
            }
            x = -(((f32) count * 10.0F) - (cam_left - 50.0F));
        }
        y = direction *
            (((f32) grOp_804D6A98->x4 * ((2.0F * HSD_Randf()) - 1.0F)) +
             20.0F);
        for (i = 0; i < count; i++) {
            spawn = grOldPupupu_802108B4_noinline(2);
            if (spawn != NULL) {
                jobj = spawn->hsd_obj;
                HSD_ASSERT(0x216, jobj);
                HSD_JObjSetTranslateX(jobj, direction * x);
                HSD_JObjSetTranslateY(jobj, y);
                HSD_JObjSetTranslateZ(jobj, -150.0F * direction);
                grAnime_801C7FF8(spawn, 0, 7, 0, 40.0F * (f32) i, 1.0F);
                HSD_JObjClearFlagsAll(
                    Ground_801C3FA4(spawn, grOp_803E67B0[index].x2),
                    JOBJ_HIDDEN);
            }
            x += step;
        }

        respawn = grOp_804D6A98->x2;
        min_respawn = grOp_804D6A98->x0;
        if (respawn > min_respawn) {
            s32 range = respawn - min_respawn;

            if (range != 0) {
                respawn = min_respawn + HSD_Randi(range);
            } else {
                respawn = min_respawn;
            }
        } else if (respawn < min_respawn) {
            s32 range = min_respawn - respawn;

            if (range != 0) {
                respawn += HSD_Randi(range);
            }
        }
        gp->gv.oldpupupu2.xC4 = respawn;
    }
}

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
    gp->gv.oldpupupu.xC4 = 0;
    gp->gv.oldpupupu.xC8 = 0;
    gp->gv.oldpupupu.xCC = 0;

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

    gp->gv.oldpupupu.xD0 = max;
    gp->gv.oldpupupu.xD4 = 1;
    gp->gv.oldpupupu.xE0 = 0;
    gp->gv.oldpupupu.xD8 = 1;
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
    Vec3 pos;
    Ground* gp;

    ftLib_80086644(fighter_gobj, &pos);
    vel->y = 0.0F;
    vel->z = 0.0F;

    gp = GET_GROUND(gobj);
    switch (gp->gv.oldpupupu.xDC) {
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

void grOldPupupu_802113E0(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    if (grOp_804D6A9C == 0) {
        gp->gv.oldpupupu.xE0 += 1;
        gp->gv.oldpupupu.xDC = 0;

        switch (gp->gv.oldpupupu.xC8) {
        case 0:
            if (gp->gv.oldpupupu.xD4 != 0) {
                Ground* other_gp;

                gp->gv.oldpupupu.xD4 = 0;
                gp->gv.oldpupupu.xCC = 0;
                gp->gv.oldpupupu.xD0 =
                    rand_range(grOp_804D6A98->xC, grOp_804D6A98->x8);
                grAnime_801C8138(
                    gobj, gp->map_id,
                    grOp_804D48C8[gp->gv.oldpupupu.xCC][gp->gv.oldpupupu.xD8]);
                other_gp = Ground_801C2BA4(1)->user_data;
                other_gp->gv.oldpupupu.xC4 = gp->gv.oldpupupu.xC4;
                other_gp->gv.oldpupupu.xC8 = gp->gv.oldpupupu.xC8;
                other_gp->gv.oldpupupu.xCC = 0;
                other_gp->gv.oldpupupu.xD4 = gp->gv.oldpupupu.xD8;
                other_gp->gv.oldpupupu.xD0 = 1;
                gp->gv.oldpupupu.xCC = rand_range((s32) grOp_804D6A98->x2C,
                                                  (s32) grOp_804D6A98->x30);
            }

            gp->gv.oldpupupu.xD0 -= 1;
            if (grAnime_801C83D0(gobj, 0, 7) != 0) {
                if (gp->gv.oldpupupu.xD0 > 0) {
                    Ground* other_gp;

                    gp->gv.oldpupupu.xCC -= 1;
                    if (gp->gv.oldpupupu.xCC <= 0) {
                        gp->gv.oldpupupu.xCC = 0;
                        grAnime_801C8138(gobj, gp->map_id,
                                         grOp_804D48C8[gp->gv.oldpupupu.xCC]
                                                      [gp->gv.oldpupupu.xD8]);
                        gp->gv.oldpupupu.xCC =
                            rand_range((s32) grOp_804D6A98->x2C,
                                       (s32) grOp_804D6A98->x30);
                    }
                    other_gp = Ground_801C2BA4(1)->user_data;
                    other_gp->gv.oldpupupu.xC4 = gp->gv.oldpupupu.xC4;
                    other_gp->gv.oldpupupu.xC8 = gp->gv.oldpupupu.xC8;
                    other_gp->gv.oldpupupu.xCC = 0;
                    other_gp->gv.oldpupupu.xD4 = gp->gv.oldpupupu.xD8;
                    other_gp->gv.oldpupupu.xD0 = 1;
                    return;
                }

                {
                    Ground* other_gp;

                    gp->gv.oldpupupu.xC4 += 1;
                    if (gp->gv.oldpupupu.xC4 >= 3) {
                        gp->gv.oldpupupu.xC4 = 0;
                    }
                    gp->gv.oldpupupu.xC8 = grOp_803E67D8[gp->gv.oldpupupu.xC4];
                    gp->gv.oldpupupu.xD4 = 1;
                    other_gp = Ground_801C2BA4(1)->user_data;
                    other_gp->gv.oldpupupu.xC4 = gp->gv.oldpupupu.xC4;
                    other_gp->gv.oldpupupu.xC8 = gp->gv.oldpupupu.xC8;
                    other_gp->gv.oldpupupu.xCC = 0;
                    other_gp->gv.oldpupupu.xD4 = gp->gv.oldpupupu.xD8;
                    other_gp->gv.oldpupupu.xD0 = 1;
                    return;
                }
            }
            break;

        case 1:
            if (gp->gv.oldpupupu.xD4 != 0) {
                Vec3 pos;
                s32 side;
                Ground* other_gp;

                gp->gv.oldpupupu.xCC = 0;
                HSD_JObjGetTranslation(gobj->hsd_obj, &pos);
                side = ftLib_800864A8(&pos, NULL) == 1.0F;
                if ((f32) gp->gv.oldpupupu.xD8 == (f32) side) {
                    gp->gv.oldpupupu.xC8 = 2;
                    gp->gv.oldpupupu.xD4 = 0;
                    gp->gv.oldpupupu.xCC = 0;
                    gp->gv.oldpupupu.xD0 = 0;
                    grAnime_801C8138(gobj, gp->map_id,
                                     grOp_804D48D0[gp->gv.oldpupupu.xCC]
                                                  [gp->gv.oldpupupu.xD8]);
                    gp->gv.oldpupupu.xC4 += 1;
                    if (gp->gv.oldpupupu.xC4 >= 3) {
                        gp->gv.oldpupupu.xC4 = 0;
                    }
                    gp->gv.oldpupupu.xC8 = grOp_803E67D8[gp->gv.oldpupupu.xC4];
                    gp->gv.oldpupupu.xD4 = 1;
                    other_gp = Ground_801C2BA4(1)->user_data;
                    other_gp->gv.oldpupupu.xC4 = gp->gv.oldpupupu.xC4;
                    other_gp->gv.oldpupupu.xC8 = gp->gv.oldpupupu.xC8;
                    other_gp->gv.oldpupupu.xCC = 0;
                    other_gp->gv.oldpupupu.xD4 = gp->gv.oldpupupu.xD8;
                    other_gp->gv.oldpupupu.xD0 = 1;
                } else {
                    other_gp = Ground_801C2BA4(1)->user_data;
                    gp->gv.oldpupupu.xD8 = side;
                    gp->gv.oldpupupu.xD4 = 0;
                    gp->gv.oldpupupu.xCC = 0;
                    gp->gv.oldpupupu.xD0 = 0;
                    grAnime_801C8138(gobj, gp->map_id,
                                     grOp_804D48D8[gp->gv.oldpupupu.xCC]
                                                  [gp->gv.oldpupupu.xD8]);
                    other_gp->gv.oldpupupu.xC4 = gp->gv.oldpupupu.xC4;
                    other_gp->gv.oldpupupu.xC8 = gp->gv.oldpupupu.xC8;
                    other_gp->gv.oldpupupu.xCC = 0;
                    other_gp->gv.oldpupupu.xD4 = gp->gv.oldpupupu.xD8;
                    other_gp->gv.oldpupupu.xD0 = 1;
                }
            }

            if (gp->gv.oldpupupu.xC8 == 1 && grAnime_801C83D0(gobj, 0, 7) != 0)
            {
                Ground* other_gp;

                gp->gv.oldpupupu.xC4 += 1;
                if (gp->gv.oldpupupu.xC4 >= 3) {
                    gp->gv.oldpupupu.xC4 = 0;
                }
                gp->gv.oldpupupu.xC8 = grOp_803E67D8[gp->gv.oldpupupu.xC4];
                gp->gv.oldpupupu.xD4 = 1;
                other_gp = Ground_801C2BA4(1)->user_data;
                other_gp->gv.oldpupupu.xC4 = gp->gv.oldpupupu.xC4;
                other_gp->gv.oldpupupu.xC8 = gp->gv.oldpupupu.xC8;
                other_gp->gv.oldpupupu.xCC = 0;
                other_gp->gv.oldpupupu.xD4 = gp->gv.oldpupupu.xD8;
                other_gp->gv.oldpupupu.xD0 = 1;
                return;
            }
            break;

        case 2:
            if (gp->gv.oldpupupu.xD4 != 0) {
                Ground* other_gp;

                gp->gv.oldpupupu.xD4 = 0;
                gp->gv.oldpupupu.xCC = 0;
                gp->gv.oldpupupu.xD0 = 0;
                grAnime_801C8138(
                    gobj, gp->map_id,
                    grOp_804D48D0[gp->gv.oldpupupu.xCC][gp->gv.oldpupupu.xD8]);
                other_gp = Ground_801C2BA4(1)->user_data;
                other_gp->gv.oldpupupu.xC4 = gp->gv.oldpupupu.xC4;
                other_gp->gv.oldpupupu.xC8 = gp->gv.oldpupupu.xC8;
                other_gp->gv.oldpupupu.xCC = 0;
                other_gp->gv.oldpupupu.xD4 = gp->gv.oldpupupu.xD8;
                other_gp->gv.oldpupupu.xD0 = 1;
            }

            if (grAnime_801C83D0(gobj, 0, 7) == 0) {
                gp->gv.oldpupupu.xD0 += 1;
                if (gp->gv.oldpupupu.xD0 == 0x2D) {
                    lbAudioAx_800237A8(gp->gv.oldpupupu.xD8 == 0 ? 0x72BF0
                                                                 : 0x72BF1,
                                       0x7F, 0x40);
                }
                if (gp->gv.oldpupupu.xD0 > 0x2D &&
                    gp->gv.oldpupupu.xD0 < 0x140)
                {
                    Camera_80030E44(1, NULL);
                    gp->gv.oldpupupu.xDC = gp->gv.oldpupupu.xD8 + 1;
                    if ((gp->gv.oldpupupu.xD0 % 10) == 0) {
                        if (gp->gv.oldpupupu.xD8 == 0) {
                            lb_80011A50(&grOp_803E67E4[0], 0xF, 0.5F, 0.0F,
                                        0.0F, grOp_804D6A98->x20,
                                        grOp_804D6A98->x24, grOp_804D6A98->x1C,
                                        grOp_804D6A98->x28);
                        } else {
                            lb_80011A50(&grOp_803E67E4[1], 0xF, 0.5F, 0.0F,
                                        0.0F, grOp_804D6A98->x14,
                                        grOp_804D6A98->x24, grOp_804D6A98->x18,
                                        grOp_804D6A98->x28);
                        }
                        return;
                    }
                }
            } else {
                Ground* other_gp;

                gp->gv.oldpupupu.xC4 += 1;
                if (gp->gv.oldpupupu.xC4 >= 3) {
                    gp->gv.oldpupupu.xC4 = 0;
                }
                gp->gv.oldpupupu.xC8 = grOp_803E67D8[gp->gv.oldpupupu.xC4];
                gp->gv.oldpupupu.xD4 = 1;
                other_gp = Ground_801C2BA4(1)->user_data;
                other_gp->gv.oldpupupu.xC4 = gp->gv.oldpupupu.xC4;
                other_gp->gv.oldpupupu.xC8 = gp->gv.oldpupupu.xC8;
                other_gp->gv.oldpupupu.xCC = 0;
                other_gp->gv.oldpupupu.xD4 = gp->gv.oldpupupu.xD8;
                other_gp->gv.oldpupupu.xD0 = 1;
            }
            break;
        }
    }
}

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

    if (other_gp->gv.oldpupupu.xC8 == 2 && other_gp->gv.oldpupupu.xD4 != 0) {
        grAnime_801C8138(gobj, gp->map_id,
                         grOp_804D48E0[other_gp->gv.oldpupupu.xCC]
                                      [other_gp->gv.oldpupupu.xD8]);
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
