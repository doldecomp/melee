#include "grzebes.h"

#include <platform.h>

#include "forward.h"

#include <dolphin/os.h>

#include "ft/ftdevice.h"
#include "ft/ftlib.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "mp/mplib.h"

#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

/* 1D84A0 */ static void grZebes_801D84A0(bool arg);
/* 1D8528 */ static void grZebes_801D8528(void);
/* 1D852C */ void grZebes_801D852C(void);
/* 1D8550 */ static bool grZebes_801D8550(void);
/* 1D8558 */ static Ground_GObj* grZebes_801D8558(int);
/* 1D8814 */ static bool grZebes_801D8814(Ground_GObj* arg);
/* 1D90FC */ static void grZebes_801D90FC(Ground_GObj* arg);
/* 1D9254 */ static bool grZebes_801D9254(Ground_GObj* arg);
/* 1D93D8 */ static void grZebes_801D93D8(Ground_GObj* arg);
/* 1D93DC */ void grZebes_801D93DC(Ground_GObj* gobj);
/* 1D9408 */ static bool grZebes_801D9408(Ground_GObj* arg);
/* 1D9410 */ static void grZebes_801D9410(Ground_GObj* arg);
/* 1D94EC */ static void grZebes_801D94EC(Ground_GObj* arg);
/* 1D94F0 */ static void fn_801D94F0(Ground_GObj* gobj);
/* 1D95B0 */ static bool grZebes_801D95B0(Ground_GObj* arg);
/* 1D95B8 */ static void grZebes_801D95B8(Ground_GObj* arg);
/* 1D9754 */ static void grZebes_801D9754(Ground_GObj* arg);
/* 1D99D8 */ static bool grZebes_801D99D8(Ground_GObj* arg);
/* 1D9F2C */ static void grZebes_801D9F2C(Ground_GObj* arg);
/* 1D9F7C */ static bool grZebes_801D9F7C(Ground_GObj* arg);
/* 1DA0C0 */ static void grZebes_801DA0C0(Ground_GObj* arg);
/* 1DA3E8 */ static void grZebes_801DA3E8(void);
/* 1DA528 */ static u8 grZebes_801DA528(HSD_GObj*, void*, s32, s32);
/* 1DA9D8 */ static void fn_801DA9D8(Item_GObj* arg0, Ground* gp, Vec3* pos,
                                     HSD_GObj* fobj, f32 slope);
/* 1DA9F0 */ static void fn_801DA9F0(Item_GObj* arg0, Ground* gp, Vec3* pos,
                                     HSD_GObj* fobj, f32 slope);
/* 1DAC90 */ static void fn_801DAC90(Item_GObj*, Ground*, Vec3*, HSD_GObj*,
                                     f32);
/* 1DB3CC */ static void grZebes_801DB3CC(s32 arg);
/* 1DC260 */ static void grZebes_801DC260(void);
/* 1DC744 */ static void grZebes_801DC744(s32, s32, f32);
/* 1DC9DC */ static void grZebes_801DC9DC(s32 arg);
/* 1DCCB8 */ static DynamicsDesc* grZebes_801DCCB8(enum_t arg);
/* 1DCCC0 */ static bool grZebes_801DCCC0(Vec3* arg, int arg0, HSD_JObj* jobj);

static s16 grZe_803E1A10[] = {
    1, 6, 21, 4, 6, 14, 3, 6,
    1, 2, 7, 6, 5, 7, 1, 0,
};

static StageCallbacks grZe_callbacks[] = {
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
};

static u8 grZe_803E1B20[0x0A] = { 0 };
static u8 grZe_803E1B2C[0x58] = { 0 };
static u8 grZe_803E1B84[0x0A] = "grzebes.c";
static u8 grZe_803E1B90[0xF0] = { 0 };
static u8 grZe_803E1C80[0x6C] = { 0 };
static u8 grZe_803E1CEC[0x3C] = { 0 };

/* 4D6990 */ static HSD_GObj* grZe_804D6990;
/* 4D6994 */ static s32 grZe_804D6994;
/* 4D6998 */ static s16 grZe_804D6998;

extern f32 grZe_804DB0B0;

typedef struct grZe_BubbleEntry {
    /* 0x00 */ u8 active;
    /* 0x01 */ u8 pad_01[3];
    /* 0x04 */ u32 unk04;
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 size;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ HSD_GObj* gobj;
} grZe_BubbleEntry;;

/* 8049F140 */ static Vec3 grZe_8049F140[2];
/* 8049F158 */ static Vec3 grZe_8049F158[2];
/* 8049F170 */ static grZe_BubbleEntry grZe_8049F170[20];

typedef struct grZe_BubbleConfig {
    f32 scales[7];
    Vec3 positions[4];
} grZe_BubbleConfig;

void grZebes_801D84A0(bool arg) {}

void grZebes_801D84A4(void)
{
    grZe_804D6990 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grZebes_801D8558(0);
    grZebes_801D8558(1);
    grZebes_801D8558(6);
    grZebes_801D8558(4);
    grZebes_801D8558(8);
    Ground_801C39C0();
    Ground_801C3BB4();
    grZebes_801DA3E8();
}
void grZebes_801D8528(void) {}

void grZebes_801D852C(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grZebes_801D8550(void)
{
    return false;
}

Ground_GObj* grZebes_801D8558(int id)
{
    Ground_GObj* gobj;
    StageCallbacks* cbs = &grZe_callbacks[id];
    gobj = Ground_801C14D0(id);
    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (cbs->callback3 != NULL) {
            gp->x1C_callback = cbs->callback3;
        }
        if (cbs->callback0 != NULL) {
            cbs->callback0(gobj);
        }
        if (cbs->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, cbs->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 256, id);
    }
    return gobj;
}

static const Vec3 grZe_803B7FF0 = { 0.0f, 0.0f, 0.0f };

void grZebes_801D8644(HSD_GObj* gobj)
{
    Vec3 pos;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child_jobj;
    Item_GObj* mat_gobj;
    Item_GObj* mat_gobj2;

    gp->gv.zebes5.xF0 = (u32) grZebes_801D8558(7);
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    child_jobj = Ground_801C3FA4(gobj, 0x1E);
    mat_gobj = grMaterial_801C8CFC(7, 0, gp, child_jobj, NULL, fn_801DA9D8,
                                   NULL);
    grMaterial_801C8DE0(mat_gobj, 0.0f, -7.0f, 0.0f, 0.0f, 7.0f, 0.0f,
                        3.0f);
    grMaterial_801C8E08(mat_gobj);
    gp->gv.zebes5.xC4 = 0;
    gp->gv.zebes5.xC7 = 0xFF;
    gp->gv.zebes5.xC8 = 0;
    gp->gv.zebes5.xCA = 0;
    gp->gv.zebes5.xCC = HSD_JObjGetTranslationX(child_jobj);
    gp->gv.zebes5.xD0 = 0.0f;
    gp->gv.zebes5.xD4 = 0.0f;
    gp->gv.zebes5.xD8 = 0.0f;
    gp->gv.zebes5.xDC = (u32) child_jobj;
    gp->gv.zebes5.xE0 = (u32) Ground_801C3FA4(gobj, 0x20);
    gp->gv.zebes5.xE4 = (u32) mat_gobj;
    gp->gv.zebes5.xE8 = 0x1C;
    gp->gv.zebes5.xEC = 0;
    gp->gv.zebes5.xF4 = 0;
    pos = grZe_803B7FF0;
    mat_gobj2 = grMaterial_801C8D44(0, 0, gp, &pos, 0, NULL, fn_801DAC90,
                                    NULL);
    grMaterial_801C8E08(mat_gobj2);
    gp->gv.zebes5.xFC = (u32) mat_gobj2;
    grZebes_801DC9DC((s32) gobj);
    gp->gv.zebes5.xF8 = (u32) grZakoGenerator_801CA394(
        (UNK_T) &grZe_803E1B90, 0xA, (UNK_T) grZebes_801DCB64, 1.0f);
    mpJointSetB10(0);
    Ground_801C2FE0((Ground_GObj*) gobj);
}

bool grZebes_801D8814(Ground_GObj* arg)
{
    return false;
}

/// #grZebes_801D881C

void grZebes_801D90FC(Ground_GObj* arg) {}

void grZebes_801D9100(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child_jobj;
    Item_GObj* mat_gobj;

    grAnime_801C8138(gobj, gp->map_id, 0);
    Ground_801C2ED0(jobj, gp->map_id);
    child_jobj = Ground_801C3FA4(gobj, 0xF);
    mat_gobj = grMaterial_801C8CFC(7, 0, gp, child_jobj, NULL, fn_801DA9F0,
                                   NULL);
    grMaterial_801C8DE0(mat_gobj, 0.0f, -5.0f, 0.0f, 0.0f, 5.0f, 0.0f,
                        2.0f);
    grMaterial_801C8E08(mat_gobj);
    gp->gv.zebes4.xC4 = 0xFF;
    gp->gv.zebes4.xC5 = 0;
    gp->gv.zebes4.xC6 = 0;
    gp->gv.zebes4.xC8 = HSD_JObjGetTranslationX(child_jobj);
    gp->gv.zebes4.xCC = 0.0f;
    gp->gv.zebes4.xD0 = 0.0f;
    gp->gv.zebes4.xD4 = 0.0f;
    gp->gv.zebes4.xD8 = (u32) child_jobj;
    gp->gv.zebes4.xDC = (u32) Ground_801C3FA4(gobj, 0x11);
    gp->gv.zebes4.xE0 = (u32) mat_gobj;
    gp->gv.zebes4.xE4 = 0xD;
    gp->gv.zebes4.xE8 = 0;
    gp->gv.zebes4.xEC =
        (u32) grZakoGenerator_801CA394((UNK_T) &grZe_803E1C80, 4,
                                       (UNK_T) grZebes_801DCBB0, 1.0f);
    Ground_801C2FE0((Ground_GObj*) gobj);
}

bool grZebes_801D9254(Ground_GObj* arg)
{
    return false;
}

static const Vec3 grZe_803B802C = { 24.1f, -4.6f, 0.0f };
static const Vec3 grZe_803B8038 = { 24.05f, 2.2f, 0.0f };

void grZebes_801D925C(HSD_GObj* gobj)
{
    Vec3 pos1;
    Vec3 pos2;
    f32 slope, intercept;
    HSD_JObj* jobj;
    Ground* gp = GET_GROUND(gobj);
    s32 result = grZebes_801DA528(gobj, &gp->gv.zebes4, 1, 2);

    if (gp->gv.zebes4.xE8 != result) {
        gp->gv.zebes4.xE8 = result;
        if (result == 1) {
            grAnime_801C7FF8(gobj, 6, 1, 1, 30.0f, 1.0f);
            grAnime_801C78FC(gobj, 6, 1U);
        } else if (result == 3) {
            grAnime_801C7FF8(gobj, 6, 1, 2, 0.0f, 1.0f);
            grAnime_801C78FC(gobj, 6, 1U);
        }
    }

    pos1 = grZe_803B802C;
    pos2 = grZe_803B8038;

    jobj = Ground_801C3FA4(gobj, 1);
    if (jobj != NULL) {
        lb_8000B1CC(jobj, &pos1, &grZe_8049F158[1]);
        lb_8000B1CC(jobj, &pos2, &grZe_8049F140[1]);
    }

    Ground_801C4368(&slope, &intercept);
    grZakoGenerator_801CA43C((void*) gp->gv.zebes4.xEC,
                             Ground_801C3FA4(gobj, 1), slope);
    Ground_801C2FE0((Ground_GObj*) gobj);
}

void grZebes_801D93D8(Ground_GObj* arg) {}

void grZebes_801D93DC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grZebes_801D9408(Ground_GObj* arg)
{
    return false;
}

void grZebes_801D9410(Ground_GObj* gobj)
{
    f32 slope, intercept;
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C4368(&slope, &intercept);
    HSD_JObjSetTranslateY(jobj, slope);
    if (grAnime_801C83D0(gobj, 0, 7) != 0) {
        grZebes_801DA4FC(gobj);
    }
}

void grZebes_801D94EC(Ground_GObj* arg) {}

void fn_801D94F0(Ground_GObj* gobj)
{
    GET_GROUND(gobj)->gv.zebes.x0_b0 = false;
}

void grZebes_801D9508(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_GObj* map_a_gobj = Ground_801C2BA4(6);
    HSD_ASSERT(909, map_a_gobj);
    gp->gv.zebes.x4 = (u32) Ground_801C3FA4(map_a_gobj, 14);
    gp->gv.zebes.x8 = 1;
    gp->gv.zebes.xA = (s16) (HSD_Randi(600) + 3000);
    gp->gv.zebes.x0_b0 = true;
    Ground_801C10B8(gobj, fn_801D94F0);
}

bool grZebes_801D95B0(Ground_GObj* arg)
{
    return false;
}

void grZebes_801D95B8(Ground_GObj* gobj)
{
    Vec3 pos;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* stored_jobj = (HSD_JObj*) gp->gv.zebes.x4;

    if (stored_jobj != NULL) {
        HSD_JObjGetTranslation2(stored_jobj, &pos);
        HSD_JObjSetTranslate(jobj, &pos);
    }
    if (!gp->gv.zebes.x0_b0) {
        if (gp->gv.zebes.xA > 0) {
            gp->gv.zebes.xA--;
            if (gp->gv.zebes.xA == 0) {
                if (gp->gv.zebes.x8 > 0) {
                    grAnime_801C8138(gobj, gp->map_id, 0);
                    gp->gv.zebes.x8 = -1;
                    return;
                }
                grAnime_801C8138(gobj, gp->map_id, 1);
                gp->gv.zebes.x8 = 1;
            }
        } else if (grAnime_801C83D0(gobj, 0, 7) != 0) {
            gp->gv.zebes.xA = (s16) (HSD_Randi(600) + 3000);
        }
    }
}

void grZebes_801D9754(Ground_GObj* arg) {}

void grZebes_801D9758(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    ftCo_800C07F8(gobj, 3, grZebes_801DCBFC);
    gp->gv.zebes.x4 = 1;
}

/// #grZebes_801D9798

bool grZebes_801D99D8(Ground_GObj* arg)
{
    return false;
}

/// #grZebes_801D99E0

void grZebes_801D9F2C(Ground_GObj* arg) {}

void grZebes_801D9F30(Ground_GObj* gobj)
{
    Ground* gp;

    gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->gv.zebes2.xC4 = 0;
    gp->x11_flags.b012 = 1;
}

bool grZebes_801D9F7C(Ground_GObj* arg)
{
    return false;
}

void grZebes_801D9F84(Ground_GObj* gobj)
{
    f32 slope;
    f32 intercept;
    Ground* gp = GET_GROUND(gobj);

    switch (gp->gv.zebes2.xC4) {
    case 0:
        Ground_801C4368(&slope, &intercept);
        if (slope > 5.0f) {
            grAnime_801C7FF8(gobj, 3, 7, 2, 0.0f, 1.0f);
            grAnime_801C78FC(gobj, 3, 7);
            gp->gv.zebes2.xC4 = 1;
            Ground_801C53EC(0x61A85);
            return;
        }
        if (slope > -20.0f) {
            grAnime_801C7FF8(gobj, 3, 7, 1, 0.0f, 1.0f);
            grAnime_801C78FC(gobj, 3, 7);
            gp->gv.zebes2.xC4 = 1;
            Ground_801C53EC(0x61A85);
            return;
        }
        return;
    case 1:
        if (grAnime_801C83D0(gobj, 3, 7) != 0) {
            grAnime_801C7FF8(gobj, 3, 7, 0, 0.0f, 1.0f);
            gp->gv.zebes2.xC4 = 0;
        }
        break;
    }
}

void grZebes_801DA0C0(Ground_GObj* arg) {}

/// #grZebes_801DA0C4

/// #grZebes_801DA254

void grZebes_801DA3E8(void)
{
    grZe_804D6998 = 0;
}

void grZebes_801DA3F4(Vec3* pos)
{
    Ground_GObj* gobj;
    HSD_JObj* jobj;

    if (grZe_804D6998 < 10 &&
        (gobj = grZebes_801D8558(5)) != NULL)
    {
        jobj = GET_JOBJ(gobj);
        if (jobj != NULL) {
            HSD_JObjSetTranslate(jobj, pos);
            grZe_804D6998 += 1;
            return;
        }
        Ground_801C4A08(gobj);
    }
}

void grZebes_801DA4FC(Ground_GObj* gobj)
{
    grZe_804D6998 -= 1;
    Ground_801C4A08(gobj);
}

/// #grZebes_801DA528

void fn_801DA9D8(Item_GObj* arg0, Ground* gp, Vec3* pos, HSD_GObj* fobj,
                 f32 slope)
{
    gp->gv.zebes.xC.z += slope;
    gp->gv.zebes.xC.y = pos->x;
}

void fn_801DA9F0(Item_GObj* arg0, Ground* gp, Vec3* pos, HSD_GObj* fobj,
                 f32 slope)
{
    gp->gv.zebes.xC.y += slope;
    gp->gv.zebes.xC.x = pos->x;
}

/// #grZebes_801DAA08

void fn_801DAC90(Item_GObj* arg0, Ground* arg1, Vec3* arg2, HSD_GObj* arg3,
                 f32 arg4)
{
    s32 found = -1;
    s32 i;

    for (i = 0; i < 20; i++) {
        if (grZe_8049F170[i].active == 1 && i != 0 && i != 6) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        grZe_8049F170[found].active = 2;
        grZe_804D6994 = 0x78;
        grZe_8049F170[found].unk1C = 0.001f;
    }
}

void grZebes_801DAE70(s32 arg0, u8 arg1, f32 x, f32 y, f32 scale)
{
    grZe_BubbleEntry* entry = &grZe_8049F170[arg0];

    if (entry->active == 0) {
        if (entry->gobj == NULL) {
            Ground_GObj* gobj;

            entry->x = x;
            entry->y = y;
            entry->unk10 = 0.0f;
            entry->unk14 = 0.0f;
            entry->unk1C = scale;
            entry->size = scale;

            if (arg0 == 0 || arg0 == 6) {
                gobj = NULL;
            } else {
                gobj = grZebes_801D8558(3);
                if (gobj != NULL) {
                    HSD_JObj* jobj = GET_JOBJ(gobj);
                    Ground* gp = GET_GROUND(gobj);
                    Vec3 pos;

                    pos.x = x;
                    pos.y = y;
                    pos.z = 0.0f;
                    HSD_JObjSetTranslate(jobj, &pos);

                    pos.x = scale;
                    pos.y = scale;
                    pos.z = 0.001f;
                    HSD_JObjSetScale(jobj, &pos);

                    gp->gv.zebes3.xC4 = 0;
                    gp->gv.zebes3.xC8 = arg0;
                }
            }

            entry->active = arg1;
            entry->gobj = (HSD_GObj*) gobj;
            grZe_8049F170[arg0].unk04 = 0;
        }
    }
}

/// #grZebes_801DB088

/// #grZebes_801DB3CC

/// #grZebes_801DBB60

void grZebes_801DC260(void)
{
    int i;
    grZe_BubbleEntry* entry = grZe_8049F170;

    for (i = 0; i < 20; i++, entry++) {
        if (entry->active != 0) {
            HSD_GObj* gobj = entry->gobj;
            if (gobj != NULL) {
                Vec3 v;
                HSD_JObj* jobj = GET_JOBJ(gobj);

                v.x = entry->x;
                v.y = entry->y;
                v.z = 0.0f;
                HSD_JObjSetTranslate(jobj, &v);

                v.x = entry->size;
                v.y = entry->size;
                v.z = entry->size;
                HSD_JObjSetScale(jobj, &v);
            }
        }
    }
}

/// #grZebes_801DC408

/// #grZebes_801DC744

/// #grZebes_801DC9DC

static const grZe_BubbleConfig grZe_803B8044 = {
    { 1.0f, 1.1f, 1.0f, 1.2f, 1.1f, 1.0f, 1.0f },
    {
        { 7.59f, 2.5f, 0.0f },
        { 24.05f, 2.2f, 0.0f },
        { 8.2f, -4.55f, 0.0f },
        { 24.1f, -4.6f, 0.0f },
    },
};

void grZebes_801DC9DC(s32 arg0)
{
    int i;

    grZe_804D6994 = 0;

    for (i = 0; i < 20; i++) {
        grZe_8049F170[i].active = 0;
        grZe_8049F170[i].gobj = NULL;
    }

    grZe_8049F158[0] = grZe_803B8044.positions[2];
    grZe_8049F158[1] = grZe_803B8044.positions[3];
    grZe_8049F140[0] = grZe_803B8044.positions[0];
    grZe_8049F140[1] = grZe_803B8044.positions[1];

    grZebes_801DC744(3, 1, grZe_803B8044.positions[1].x);

    i = 0;
    do {
        grZebes_801DB3CC(arg0);
        i++;
    } while (i < 100);
}

bool grZebes_801DCB64(Vec3* vec, int val)
{
    if (val < 9) {
        grLib_801C96F8(0xBA, 0, vec);
    } else {
        grLib_801C96F8(0xBB, 0, vec);
    }
    return false;
}

bool grZebes_801DCBB0(Vec3* vec, int val)
{
    if (val < 3) {
        grLib_801C96F8(0xBA, 0, vec);
    } else {
        grLib_801C96F8(0xBB, 0, vec);
    }
    return false;
}

bool grZebes_801DCBFC(Ground_GObj* gobj, HSD_GObj* fobj, void* arg)
{
    Vec3 pos;
    Vec3 prev;
    f32 slope, intercept;

    Ground_801C4368(&slope, &intercept);
    ftLib_80086644(fobj, &pos);
    ftLib_80086684(fobj, &prev);
    prev.y += intercept;
    if (pos.y < slope) {
        *(void**) arg = grZe_804D6990->user_data;
        if (prev.y > slope) {
            Ground_801C43A4(&pos);
            Ground_801C53EC(0x61A82);
            Ground_801C53EC(0x66);
        }
        return true;
    }
    return false;
}

DynamicsDesc* grZebes_801DCCB8(enum_t arg)
{
    return false;
}

bool grZebes_801DCCC0(Vec3* arg, int arg0, HSD_JObj* jobj)
{
    return true;
}

f32 grZebes_801DCCC8(void)
{
    f32 slope, intercept;
    Ground_801C4368(&slope, &intercept);
    return grZe_804DB0B0 + slope;
}
