#include "gm_1832.h"

#include "gm_unsplit.h"

#include "cm/camera.h"
#include "dolphin/pad.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/ftdemo.h"
#include "gm/gm_1601.h"
#include "gm/gm_1A36.h"
#include "gm/gm_1A3F.h"
#include "gm/gm_1A45.h"
#include "gm/types.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbbgflash.h"
#include "lb/lblanguage.h"
#include "lb/lbspdisplay.h"
#include "mn/inlines.h"
#include "mn/mnname.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "sc/types.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/dobj.h>
#include <baselib/fog.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/mobj.h>
#include <baselib/random.h>
#include <baselib/sislib.h>
#include <baselib/sobjlib.h>
#include <baselib/state.h>
#include <baselib/tobj.h>
#include <baselib/util.h>
#include <baselib/wobj.h>

static struct {
    int x0;
    HSD_JObj* x4[13];
    u16 x38;
    u16 x3A;
    u16 x3C;
    u16 x3E;
} lbl_804735A8;
/// @brief related to 1p splash screen
static struct {
    HSD_ImageDesc x40[3];
    HSD_ImageDesc x88[3];
    u8 xD0[10]; ///< image descriptor indices for splash effect
    u8 pad_DA[2];
    HSD_GObj* xDC; ///< display GObj for splash screen SObjs
    u8 xE0;
    u8 xE1;
    u8 xE2;
    u8 xE3;
} lbl_804735E8;

static struct gm_1832_8047368C_t {
    /* 0x00 */ s32 model_scale_kind;
    /* 0x04 */ s32 game_type;
    /* 0x08 */ u8 xEC;
    /* 0x09 */ u8 xED;
    /* 0x0A */ u8 xEE;
    /* 0x0B */ u8 xEF;
    /* 0x0C */ u8 xF0;
    /* 0x0D */ u8 xF1[3];
    /* 0x10 */ u8 xF4[3];
    /* 0x13 */ u8 xF7[3];
    /* 0x16 */ u8 xFA[3];
    /* 0x19 */ u8 xFD[3];
    /* 0x1C */ u8 x100[3];
    /* 0x1F */ u8 pad_1F[5];
} lbl_8047368C;
ASSERT_SIZE(struct gm_1832_8047368C_t, 0x24);

static HSD_GObj* lbl_804D65F0;
static HSD_Archive* lbl_804D65F4;
static HSD_Archive* lbl_804D65F8;
static SceneDesc* lbl_804D65FC;
static SceneDesc* lbl_804D6600;

typedef struct {
    HSD_GObjEvent v[6];
} ClassicProcArray;

ClassicProcArray const lbl_803B7C28 = {
    fn_801849E0, fn_80184A04, fn_80184A28,
    fn_80184A4C, fn_80184A70, fn_80184A94,
};

ClassicProcArray const lbl_803B7C40 = {
    fn_801849E0, fn_80184A04, fn_80184A28,
    fn_80184A4C, fn_80184A70, fn_80184A94,
};

typedef struct {
    /* 0x00 */ f32 vals[3];
} ClassicSlotVals;
ASSERT_SIZE(ClassicSlotVals, 0xC);

typedef struct {
    /* 0x00 */ f32 x00;
    /* 0x04 */ f32 x04;
    /* 0x08 */ Vec3 x08;
    /* 0x14 */ u8 pad_14[0x8];
} ClassicCharLayout;
ASSERT_SIZE(ClassicCharLayout, 0x1C);

typedef struct {
    /* 0x00 */ f32 x00;
    /* 0x04 */ f32 x04;
    /* 0x08 */ f32 x08;
    /* 0x0C */ u8 pad_0C[0x8];
} ClassicTeamEntry;
ASSERT_SIZE(ClassicTeamEntry, 0x14);

typedef struct {
    /* 0x00 */ f32 x00[3];
    /* 0x0C */ f32 x0C[3];
    /* 0x18 */ f32 x18[3];
    /* 0x24 */ f32 x24[3];
} ClassicSplashRow;
ASSERT_SIZE(ClassicSplashRow, 0x30);

static struct {
    /* 0x000 */ ClassicSlotVals x00[2];
    /* 0x018 */ ClassicSlotVals x18[3];
    /* 0x03C */ ClassicSlotVals x3C[4];
    /* 0x06C */ ClassicCharLayout x6C[28];
    /* 0x37C */ ClassicTeamEntry x37C[25];
    /* 0x570 */ u8 pad_570[0xC];
    /* 0x57C */ ClassicSplashRow x57C[3];
    /* 0x60C */ u8 pad_60C[0x24];
    /* 0x630 */ ClassicSlotVals x630[3];
    /* 0x654 */ ClassicSlotVals x654[3];
    /* 0x678 */ ClassicSlotVals x678[4];
    /* 0x6A8 */ ClassicCharLayout x6A8[28];
}* lbl_804D6604;

static int lbl_804D6608;

void fn_8018325C(HSD_GObj* arg0, int arg1)
{
    Vec3 pos;
    HSD_JObj* jobj = arg0->hsd_obj;
    HSD_JObj* src = lbl_804735A8.x4[0];
    HSD_JObj* jobj2;
    int i;

    PAD_STACK(4);

    HSD_JObjGetTranslation(src, &pos);
    HSD_JObjSetTranslate(jobj, &pos);

    switch (arg1) {
    case 0:
        break;
    case 1:
        HSD_JObjAddTranslationZ(jobj, -10.0f);
        if (lbl_804735A8.x38 > 0x50U) {
            HSD_JObjSetTranslateX(lbl_804735A8.x4[2], -1.0f);
            HSD_JObjSetTranslateY(lbl_804735A8.x4[2], 0.0f);
            HSD_JObjSetTranslateZ(lbl_804735A8.x4[2], 5.0f);
            HSD_JObjSetScaleX(lbl_804735A8.x4[2], 2.8f);
            HSD_JObjSetScaleY(lbl_804735A8.x4[2], 2.8f);
        }
        break;
    case 2:
        HSD_JObjAddTranslationZ(jobj, -30.0f);
        if (lbl_804735A8.x38 > 0x5AU) {
            HSD_JObjSetTranslateX(lbl_804735A8.x4[3], -0.5f);
            HSD_JObjSetTranslateY(lbl_804735A8.x4[3], 3.0f);
            HSD_JObjSetTranslateZ(lbl_804735A8.x4[3], 5.0f);
            HSD_JObjSetScaleX(lbl_804735A8.x4[3], 2.2f);
            HSD_JObjSetScaleY(lbl_804735A8.x4[3], 2.2f);
        }
        break;
    }

    if (lbl_8047368C.model_scale_kind == 2) {
        HSD_JObjAddTranslationX(
            jobj, lbl_804D6604->x6A8[lbl_8047368C.xF1[arg1]].x00 -
                      lbl_804D6604->x630[lbl_8047368C.xEF].vals[arg1]);
        HSD_JObjAddTranslationY(
            jobj, lbl_804D6604->x6A8[lbl_8047368C.xF1[arg1]].x04 +
                      lbl_804D6604->x654[lbl_8047368C.xEF].vals[arg1]);

        HSD_JObjSetScaleX(jobj,
                          lbl_804D6604->x6A8[lbl_8047368C.xF1[arg1]].x08.x *
                              lbl_804D6604->x678[lbl_8047368C.xEF].vals[arg1]);
        HSD_JObjSetScaleY(jobj,
                          lbl_804D6604->x6A8[lbl_8047368C.xF1[arg1]].x08.y *
                              lbl_804D6604->x678[lbl_8047368C.xEF].vals[arg1]);
        HSD_JObjSetScaleZ(jobj,
                          lbl_804D6604->x6A8[lbl_8047368C.xF1[arg1]].x08.z *
                              lbl_804D6604->x678[lbl_8047368C.xEF].vals[arg1]);
    } else {
        HSD_JObjAddTranslationX(
            jobj, lbl_804D6604->x6C[lbl_8047368C.xF1[arg1]].x00 -
                      lbl_804D6604->x00[lbl_8047368C.xEF - 1].vals[arg1]);

        HSD_JObjAddTranslationY(
            jobj, lbl_804D6604->x6C[lbl_8047368C.xF1[arg1]].x04 +
                      lbl_804D6604->x18[lbl_8047368C.xEF].vals[arg1]);

        HSD_JObjSetScaleX(jobj,
                          lbl_804D6604->x6C[lbl_8047368C.xF1[arg1]].x08.x *
                              lbl_804D6604->x3C[lbl_8047368C.xEF].vals[arg1]);
        HSD_JObjSetScaleY(jobj,
                          lbl_804D6604->x6C[lbl_8047368C.xF1[arg1]].x08.y *
                              lbl_804D6604->x3C[lbl_8047368C.xEF].vals[arg1]);
        HSD_JObjSetScaleZ(jobj,
                          lbl_804D6604->x6C[lbl_8047368C.xF1[arg1]].x08.z *
                              lbl_804D6604->x3C[lbl_8047368C.xEF].vals[arg1]);
    }

    for (i = 0; i < 6; i++) {
        if (Player_GetEntity(i) == arg0) {
            HSD_GObj* entity2 = Player_GetEntityAtIndex(i, 1);
            if (entity2 != NULL) {
                Vec3 scale;
                jobj2 = entity2->hsd_obj;
                HSD_JObjGetTranslation(jobj, &pos);
                HSD_JObjSetTranslate(jobj2, &pos);
                HSD_JObjGetScale(jobj, &scale);
                HSD_JObjSetScale(jobj2, &scale);
            }
        }
    }
}

void fn_80184138(HSD_GObj* arg0, int arg1)
{
    Vec3 pos;
    HSD_JObj* jobj = arg0->hsd_obj;
    HSD_JObj* src = lbl_804735A8.x4[1];
    f32 scl, xoff, yoff;
    HSD_JObj* jobj2;
    int i;

    PAD_STACK(16);

    HSD_JObjGetTranslation(src, &pos);
    HSD_JObjSetTranslate(jobj, &pos);

    if (lbl_8047368C.model_scale_kind == 2) {
        scl = lbl_804D6604->x37C[lbl_8047368C.xF4[arg1]].x08;
    } else {
        scl = 1.0f;
    }

    if (lbl_8047368C.model_scale_kind == 2) {
        xoff = lbl_804D6604->x37C[lbl_8047368C.xF4[arg1]].x00;
    } else {
        xoff = 0.0f;
    }

    if (lbl_8047368C.model_scale_kind == 2) {
        yoff = lbl_804D6604->x37C[lbl_8047368C.xF4[arg1]].x04;
    } else {
        yoff = 0.0f;
    }

    if (arg1 != 0) {
        HSD_JObjAddTranslationZ(jobj, (f32) (-arg1 * 0x14 + 0xA));
    }

    HSD_JObjAddTranslationX(
        jobj, xoff + (-lbl_804D6604->x6C[lbl_8047368C.xF4[arg1]].x00 +
                      lbl_804D6604->x00[lbl_8047368C.xF0 - 1].vals[arg1]));

    HSD_JObjAddTranslationY(
        jobj, yoff + (lbl_804D6604->x6C[lbl_8047368C.xF4[arg1]].x04 +
                      lbl_804D6604->x18[lbl_8047368C.xF0].vals[arg1]));

    if (lbl_8047368C.model_scale_kind == 2) {
        HSD_JObjSetScaleX(
            jobj, lbl_804D6604->x6C[lbl_8047368C.xF4[arg1]].x08.x * scl);
        HSD_JObjSetScaleY(
            jobj, lbl_804D6604->x6C[lbl_8047368C.xF4[arg1]].x08.y * scl);
        HSD_JObjSetScaleZ(
            jobj, lbl_804D6604->x6C[lbl_8047368C.xF4[arg1]].x08.z * scl);
    } else {
        HSD_JObjSetScaleX(jobj,
                          lbl_804D6604->x6C[lbl_8047368C.xF4[arg1]].x08.x *
                              lbl_804D6604->x3C[lbl_8047368C.xF0].vals[arg1]);
        HSD_JObjSetScaleY(jobj,
                          lbl_804D6604->x6C[lbl_8047368C.xF4[arg1]].x08.y *
                              lbl_804D6604->x3C[lbl_8047368C.xF0].vals[arg1]);
        HSD_JObjSetScaleZ(jobj,
                          lbl_804D6604->x6C[lbl_8047368C.xF4[arg1]].x08.z *
                              lbl_804D6604->x3C[lbl_8047368C.xF0].vals[arg1]);
    }

    for (i = 0; i < 6; i++) {
        if (Player_GetEntity(i) == arg0) {
            HSD_GObj* entity2 = Player_GetEntityAtIndex(i, 1);
            if (entity2 != NULL) {
                Vec3 scale;
                jobj2 = entity2->hsd_obj;
                HSD_JObjGetTranslation(jobj, &pos);
                HSD_JObjSetTranslate(jobj2, &pos);
                HSD_JObjGetScale(jobj, &scale);
                HSD_JObjSetScale(jobj2, &scale);
            }
        }
    }
}

void fn_801849E0(HSD_GObj* gobj)
{
    fn_8018325C(gobj, 0);
}

void fn_80184A04(HSD_GObj* gobj)
{
    fn_8018325C(gobj, 1);
}

void fn_80184A28(HSD_GObj* gobj)
{
    fn_8018325C(gobj, 2);
}

void fn_80184A4C(HSD_GObj* gobj)
{
    fn_80184138(gobj, 0);
}

void fn_80184A70(HSD_GObj* gobj)
{
    fn_80184138(gobj, 1);
}

void fn_80184A94(HSD_GObj* gobj)
{
    fn_80184138(gobj, 2);
}

typedef struct ClassicCharData {
    /* 0x000 */ f32 scale[28];
    /* 0x070 */ Vec3 offset[28];
    /* 0x1C0 */ Vec3 samus_extra;
} ClassicCharData;

static ClassicCharData lbl_803D9248 = {
    { 0.6f, 0.35f, 0.6f, 0.5f, 0.6f, 0.35f, 0.6f, 0.6f, 0.7f, 0.6f,
      0.5f, 0.6f,  0.6f, 0.6f, 0.5f, 0.5f,  0.6f, 0.5f, 0.6f, 0.6f,
      0.5f, 0.6f,  0.6f, 0.6f, 0.6f, 0.5f,  0.5f, 0.5f },
    { { 0.0f, -6.0f, 0.0f },  { 0.0f, -3.5f, 0.0f },  { -1.0f, -3.5f, 0.0f },
      { 0.0f, -3.5f, 0.0f },  { 0.0f, -1.0f, 0.0f },  { 0.0f, -3.0f, 0.0f },
      { 0.0f, -5.0f, 0.0f },  { 0.0f, -3.5f, 0.0f },  { 0.0f, -3.5f, 0.0f },
      { 0.0f, -3.5f, 0.0f },  { 0.0f, -3.0f, 0.0f },  { -0.5f, -3.5f, 0.0f },
      { -2.0f, -6.0f, 0.0f }, { 0.0f, -2.5f, 0.0f },  { 0.0f, -2.5f, 0.0f },
      { -1.0f, -1.0f, 0.0f }, { 0.0f, -5.0f, 0.0f },  { 0.0f, -3.0f, 0.0f },
      { -1.0f, -6.0f, 0.0f }, { -1.0f, -2.5f, 0.0f }, { -1.0f, -3.5f, 0.0f },
      { 0.0f, -3.5f, 0.0f },  { 0.0f, -4.0f, 0.0f },  { -1.0f, -3.5f, 0.0f },
      { 0.0f, -1.5f, 0.0f },  { 0.0f, -4.5f, 0.0f },  { 0.0f, -3.5f, 0.0f },
      { 0.0f, -3.5f, 0.0f } },
    { 3.0f, 4.0f, -5.0f },
};

static char lbl_803D9414[] = { 0x82, 0x73, 0x82, 0x85, 0x82, 0x81,
                               0x82, 0x8D, 0,    0,    0,    0 };

static char lbl_804D40A0[] = { 0x8C, 0x52, 0x92, 0x63, 0x00 };

static const char* const lbl_803B7C58[] = { "IrAls", "IrEzTarg", "IrEzTuki",
                                            "IrEzFigG" };

static char lbl_803D9444[] = "ScItrAllstar_scene_data";

void fn_80184AB8(HSD_GObj* arg0)
{
    HSD_JObj* sp110;
    char sp10[0x100];
    HSD_JObj* jobj;
    s32 i;
    const char* name;

    PAD_STACK(4);

    jobj = arg0->hsd_obj;
    HSD_JObjAnimAll(jobj);

    if (lbl_804735A8.x38 < 0x8CU) {
        lbl_804735A8.x38 = (u16) (lbl_804735A8.x38 + 1);
    } else {
        lbl_804735A8.x0 = 1;
        return;
    }

    if (lbl_8047368C.model_scale_kind != 3) {
        if (lbl_8047368C.xEE < 0xAU) {
            lb_80011E24(jobj, &sp110, 0x12, -1);
            HSD_TObjReqAnimAll(sp110->u.dobj->mobj->tobj,
                               (f32) (lbl_8047368C.xEE % 10));
            HSD_AObjSetRate(sp110->u.dobj->mobj->tobj->aobj, 0.0f);
            lb_80011E24(jobj, &sp110, 0x13, -1);
            HSD_TObjReqAnimAll(sp110->u.dobj->mobj->tobj, 10.0f);
            HSD_AObjSetRate(sp110->u.dobj->mobj->tobj->aobj, 0.0f);
        } else {
            lb_80011E24(jobj, &sp110, 0x12, -1);
            HSD_TObjReqAnimAll(sp110->u.dobj->mobj->tobj,
                               (f32) (lbl_8047368C.xEE / 10));
            HSD_AObjSetRate(sp110->u.dobj->mobj->tobj->aobj, 0.0f);
            lb_80011E24(jobj, &sp110, 0x13, -1);
            HSD_TObjReqAnimAll(sp110->u.dobj->mobj->tobj,
                               (f32) (lbl_8047368C.xEE % 10));
            HSD_AObjSetRate(sp110->u.dobj->mobj->tobj->aobj, 0.0f);
        }

        switch ((s32) lbl_804735A8.x38) {
        case 0xA:
            lbAudioAx_800237A8(0x9C4A, 0x7F, 0x40);
            return;
        case 0x2D:
            break;
        case 0x46:
            if (lbl_8047368C.model_scale_kind == 4 ||
                lbl_8047368C.model_scale_kind == 1)
            {
                lbl_804D6608 = lbAudioAx_800237A8(0x7C863, 0x7F, 0x40);
                return;
            }
            if (lbl_8047368C.model_scale_kind == 2) {
                lbl_804D6608 = lbAudioAx_800237A8(0x7C837, 0x7F, 0x40);
                return;
            }
            if (lbl_8047368C.x100[0] != 0) {
                lbl_804D6608 = lbAudioAx_800237A8(0x7C847, 0x7F, 0x40);
                return;
            }
            break;
        case 0x64:
            if ((s32) lbl_804D6608 != -1) {
                lbAudioAx_800236B8(lbl_804D6608);
            }
            gm_80168C5C((u32) lbl_8047368C.xF4[0]);
            return;
        case 0x5:
            for (i = 0; i < (s32) lbl_8047368C.xEF; i++) {
                if (i != 0 || lbl_8047368C.xED == 0x78) {
                    fn_80160DE8(lbl_804735A8.x4[7 + i], lbl_8047368C.xF1[i], 0,
                                0, lbl_804D6604->x57C[lbl_8047368C.xEF].x18[i],
                                lbl_804D6604->x57C[lbl_8047368C.xEF].x24[i]);
                } else {
                    HSD_SisLib_803A70A0((HSD_Text*) lbl_804735A8.x4[7 + i], 0,
                                        GetNameText((s32) lbl_8047368C.xED));
                    HSD_SisLib_803A7548((HSD_Text*) lbl_804735A8.x4[7 + i], 0,
                                        1.0f, 1.0f);
                }
            }
            return;
        case 0x6:
            if (lbl_8047368C.model_scale_kind == 4) {
                i = 0;
                name = gm_80160980(lbl_8047368C.xF4[0]);
                if (lbLang_IsSavedLanguageUS()) {
                    {
                        char* src = lbl_803D9414;
                        while (*src != 0) {
                            sp10[i++] = *src++;
                        }
                    }
                    sp10[i] = ' ';
                    i++;
                    while (*name != 0) {
                        sp10[i++] = *name++;
                    }
                    sp10[i] = 0;
                } else {
                    {
                        char* src2 = lbl_804D40A0;
                        while (*name != 0) {
                            sp10[i++] = *name++;
                        }
                        sp10[i] = ' ';
                        i++;
                        while (*src2 != 0) {
                            sp10[i++] = *src2++;
                        }
                        sp10[i] = 0;
                    }
                }
                HSD_SisLib_803A70A0((HSD_Text*) lbl_804735A8.x4[10], 0, sp10);
                HSD_SisLib_803A7548((HSD_Text*) lbl_804735A8.x4[10], 0,
                                    0.8f * (lbl_804D6604->x57C[1].x18[0] *
                                            fn_80160F58(lbl_8047368C.xF4[0])),
                                    lbl_804D6604->x57C[1].x24[0]);
                return;
            }
            for (i = 0; i < (s32) lbl_8047368C.xF0; i++) {
                fn_80160DE8(lbl_804735A8.x4[10 + i], lbl_8047368C.xF4[i], 0, 1,
                            lbl_804D6604->x57C[lbl_8047368C.xF0].x18[i],
                            lbl_804D6604->x57C[lbl_8047368C.xF0].x24[i]);
            }
            break;
        }
    }
}

void fn_8018504C(void)
{
    int new_var;
    PAD_STACK(16);
    new_var = 0x32;
    if (lbl_804735A8.x3A < 0x31U) {
        lbl_804735A8.x3A = (u16) (lbl_804735A8.x3A + 1);
    } else {
        lbl_804735A8.x3A = 0;
    }
    if (lbl_804735A8.x3C < 0x31U) {
        lbl_804735A8.x3C = (u16) (lbl_804735A8.x3C + 1);
    }
    HSD_JObjReqAnimAll(
        lbl_804735A8.x4[5],
        (f32) (lbl_804735A8.x3C + ((lbl_8047368C.xEE * 0x32) - new_var)));
    HSD_JObjAnimAll(lbl_804735A8.x4[5]);
    HSD_JObjReqAnimAll(
        lbl_804735A8.x4[4],
        (f32) (lbl_804735A8.x3A + ((lbl_8047368C.xEE * 0x32) - new_var)));
    HSD_JObjAnimAll(lbl_804735A8.x4[4]);
    if ((lbl_804735A8.x38 == 0x2D) && (lbl_8047368C.model_scale_kind == 3)) {
        switch (lbl_8047368C.game_type) {
        case 1:
            lbAudioAx_800237A8(0x7C864, 0x7F, 0x40);
            return;
        case 2:
            lbAudioAx_800237A8(0x9C49, 0x7F, 0x40);
            return;
        case 3:
            lbAudioAx_800237A8(0x9C47, 0x7F, 0x40);
            break;
        }
    }
}

s32 fn_801851C0(void)
{
    u8 pad_stack[8];
    Vec3 pos;
    s32 i;
    s32 result;

    for (i = 0; i < (s32) lbl_804735E8.xE0; i++) {
        ClassicCharData* data = &lbl_803D9248;
        result = i + 1;
        Player_SetPlayerCharacter(result, (CharacterKind) lbl_8047368C.xF4[0]);
        Player_SetPlayerId(result, 0);
        Player_SetSlottype(result, Gm_PKind_Demo);
        Player_SetFacingDirection(result, 0.0f);
        Player_SetCostumeId(result, i);
        pos = data->offset[lbl_8047368C.xF4[0]];
        Player_80032768(result, &pos);
        if (lbl_8047368C.xF4[0] == 0xE) {
            pos.x += data->samus_extra.x;
            pos.y += data->samus_extra.y;
            pos.z += data->samus_extra.z;
            Player_80032828(result, 1, &pos);
        }
        Player_SetModelScale(result, data->scale[lbl_8047368C.xF4[0]]);
        Player_SetFlagsBit5(result, lbl_8047368C.x100[0]);
        Player_80037054(result, 6);
    }

    return result;
}

void fn_801852FC(HSD_GObj* gobj)
{
    int i;
    int j;

    PAD_STACK(0x18);

    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        for (i = 0; i < lbl_804735E8.xE0; i++) {
            for (j = 0; j < lbl_804735E8.xE0 + 1; j++) {
                if (j == 0 || i + 1 != j) {
                    Player_800366DC(j, 0);
                } else {
                    Player_800366DC(j, 1);
                }
            }
            Camera_800313E0(gobj, 1);
            HSD_StateInvalidate(-1);
            HSD_ImageDescCopyFromEFB(&lbl_804735E8.x40[i], 0x82, 0, 0, 0);
            HSD_ImageDescCopyFromEFB(&lbl_804735E8.x88[i], 0x82, 0, 1, 1);
        }
        HSD_CObjEndCurrent();
    }
    lbl_804735E8.xE1 = 1;
}

/// @todo .sdata2 order hack
static inline void gm_1832_sdata2_order(int unused)
{
    (void) unused;
    (void) 280.0f;
    (void) 290.0f;
    (void) 40.0f;
    (void) -60.0f;
    (void) 160.0f;
    (void) U32_TO_F32;
    (void) 0.0;
    (void) 0.5;
    (void) 3.0;
    (void) 200.0f;
    (void) 340.0f;
    (void) 10000.0f;
}

void fn_80185408(int x, float arg8, float arg9, float argA, float argB)
{
    u8 _[0x30];
    Mtx sp1C;
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE,
                  GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetZMode(1, GX_LEQUAL, 1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                  GX_COLOR_NULL);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetCullMode(GX_CULL_NONE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetColorUpdate(0);
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXLoadPosMtxImm(HSD_identityMtx, 0);
    GXSetCurrentMtx(0);
    MTXOrtho(sp1C, 0.0F, 480.0F, 0.0F, 640.0F, 0.0F, 5000.0F);
    GXSetProjection(sp1C, GX_ORTHOGRAPHIC);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXWGFifo.f32 = argA;
    GXWGFifo.f32 = arg8;
    GXWGFifo.f32 = -4932.0F;
    GXWGFifo.f32 = argB;
    GXWGFifo.f32 = arg8;
    GXWGFifo.f32 = -4932.0F;
    GXWGFifo.f32 = argB;
    GXWGFifo.f32 = arg9;
    GXWGFifo.f32 = -4932.0F;
    GXWGFifo.f32 = argA;
    GXWGFifo.f32 = arg9;
    GXWGFifo.f32 = -4932.0F;
    GXSetColorUpdate(1);
    HSD_StateInvalidate(-1);
    gm_1832_sdata2_order(0);
}

extern float MSL_TrigF_80400770[];
extern float MSL_TrigF_80400774[];

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
double fn_801855BC(double arg8)
{
    f64 temp_f2;
    f64 temp_f2_2;
    f64 temp_f2_3;
    f64 temp_f2_4;

    if (arg8 > 0.0) {
        temp_f2_2 = __frsqrte(arg8);
        temp_f2_3 =
            0.5 * temp_f2_2 * -(((f64) arg8 * (temp_f2_2 * temp_f2_2)) - 3.0);
        temp_f2_4 =
            0.5 * temp_f2_3 * -(((f64) arg8 * (temp_f2_3 * temp_f2_3)) - 3.0);
        temp_f2 =
            0.5 * temp_f2_4 * -(((f64) arg8 * (temp_f2_4 * temp_f2_4)) - 3.0);
        return arg8 *
               (0.5 * temp_f2 * -(((f64) arg8 * (temp_f2 * temp_f2)) - 3.0));
    }
    if (0.0 == arg8) {
        return 0.0;
    }
    if (arg8) {
        return MSL_TrigF_80400770[0];
    }
    return MSL_TrigF_80400774[0];
}
#ifdef MUST_MATCH
#pragma pop
#endif

void fn_8018564C(HSD_GObj* gobj)
{
    fn_80185408(0xFC8000, 0.0F, 480.0F, 200.0F, 640.0F);
    HSD_SObjLib_803A54EC(gobj, 7);
}

void fn_8018569C(HSD_GObj* gobj)
{
    int i;
    PAD_STACK(8);
    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        for (i = 0; i < lbl_804735E8.xE0 + 1; i++) {
            if (i == 0) {
                Player_800366DC(i, 1);
            } else {
                Player_800366DC(i, 0);
            }
        }
        Camera_800313E0(gobj, 1);
        gobj->gxlink_prios = 0x1001;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void fn_8018575C(HSD_GObj* gobj)
{
    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        Camera_800313E0(gobj, 1);
        gobj->gxlink_prios = 0x1001;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

/// @brief Creates splash screen sprite objects from pre-rendered character
/// images. Distributes 10 image tiles across a grid with random offsets.
void fn_801857C4(HSD_GObj* arg0)
{
    HSD_SObjDesc2 desc;
    UNUSED u8 pad_b[8];
    Vec3 pos_copy;
    UNUSED u8 pad_a[8];
    Vec3 pos;
    HSD_SObj* sobj;
    u64 num_cols;
    s32 row;
    u32 total_tiles;
    u8* img_idx;
    u32 delay;
    s32 i;

    if (lbl_804735E8.xE1 != 0) {
        HSD_GObjPLink_80390228(lbl_804D65F0);
        img_idx = (u8*) lbl_804735E8.x40;
        i = 0;
        delay = 1;
        for (; i < 10; i++, img_idx++) {
            desc.desc.image = &lbl_804735E8.x40[img_idx[0x90]];
            desc.desc.tlut = NULL;
            desc.image2 = &lbl_804735E8.x88[img_idx[0x90]];
            sobj = HSD_SObjLib_803A477C(lbl_804735E8.xDC, &desc.desc, 0, 0,
                                        0x80, 1);
            total_tiles = 10;
            num_cols = (s32) fn_801855BC(total_tiles);
            row = (u8) i / (u8) num_cols;
            pos.x =
                (40.0f * HSD_Randf()) +
                (280.0f +
                 ((290.0f / (f32) (u8) (((u8) num_cols + 9) / (u8) num_cols)) *
                  (f32) ((u8) i % (u8) num_cols)));
            pos.y = (40.0f * HSD_Randf()) +
                    (((160.0f / (f32) (u8) num_cols) * (f32) row) + -60.0f);
            pos_copy = pos;
            sobj->x10 = pos_copy.x;
            sobj->x14 = pos_copy.y;
            sobj->x48 = delay;
            delay += 8;
            sobj->x40 |= 9;
        }
        HSD_GObjPLink_80390228(arg0);
    }
}

void fn_801859C8(HSD_GObj* gobj)
{
    HSD_SObj* sobj = gobj->hsd_obj;

    while (sobj != NULL) {
        if (sobj->x48 != 0) {
            sobj->x48--;
            if (sobj->x48 == 0) {
                sobj->x40 &= ~1;
            }
        }
        sobj = sobj->next;
    }
}

static inline void fn_80185A0C_Tail(const u8* count_ptr, u8** img_idx, s32* i)
{
    s32 k;
    HSD_ImageDesc* img;
    HSD_CObj* cobj;
    HSD_GObj* gobj3;

    img = lbl_804735E8.x40;
    lbl_804735E8.xE1 = 0;
    for (*i = 0; *i < (s32) *count_ptr; (*i)++) {
        img->image_ptr = NULL;
        lb_800121FC(img, 0x17C, 0x190, GX_TF_RGB5A3, 0);
        img[3].image_ptr = NULL;
        lb_800121FC(&img[3], 0x17C, 0x190, GX_TF_Z24X8, 0);
        img++;
    }

    for (k = 0; k < 10; (*img_idx)++, k++) {
        if ((k / (s32) *count_ptr) % 2 != 0) {
            (*img_idx)[0x90] =
                (u8) ((*count_ptr - 1) - (k % (s32) *count_ptr));
        } else {
            (*img_idx)[0x90] = (u8) (k % (s32) *count_ptr);
        }
    }

    HSD_GObj_SetupProc(GObj_Create(0x13, 1, 0), fn_801857C4, 0);

    gobj3 = GObj_Create(0x13, 0x14, 0);
    cobj = HSD_CObjLoadDesc(lbl_804D6600->cameras->desc);
    HSD_GObjObject_80390A70(gobj3, HSD_GObj_CameraKind, cobj);
    GObj_SetupGXLinkMax(gobj3, (GObj_RenderFunc) (Event) fn_801852FC, 0);
    gobj3->gxlink_prios = 0x61;
    lbl_804D65F0 = gobj3;
}

s32 fn_80185A0C(void)
{
    u8* count_ptr;
    u8* img_idx;
    HSD_GObj* gobj2;
    HSD_GObj* gobj;
    HSD_GObjProc* proc;
    s32 i;
    u8 count;

    PAD_STACK(24);

    gobj = GObj_Create(0x13, 0x14, 0);
    HSD_SObjLib_803A55DC(gobj, 0x280, 0x1E0, 0xB);
    gobj->gxlink_prios = 0x20000;
    HSD_GObjGXLink_8039084C(gobj);
    GObj_SetupGXLinkMax(gobj, (GObj_RenderFunc) (Event) fn_8018564C, 0xB);

    gobj2 = GObj_Create(0xE, 0xF, 0);
    HSD_GObjObject_80390A70(gobj2, HSD_SObjLib_804D7960, NULL);
    GObj_SetupGXLink(gobj2, HSD_SObjLib_803A49E0, 0x11, 0);
    proc = HSD_GObj_SetupProc(gobj2, fn_801859C8, 0);
    proc->flags_3 = HSD_GObj_804D783C;

    count = gm_80169238(lbl_8047368C.xF4[0]);
    lbl_804735E8.xE0 = (s32) count > 3 ? 3 : count;

    img_idx = lbl_804735E8.xD0 - 0x90;
    lbl_804735E8.xDC = gobj2;
    count_ptr = &lbl_804735E8.xE0;
    fn_80185A0C_Tail(count_ptr, &img_idx, &i);
    return fn_801851C0();
}

void fn_80185D64(void)
{
    int i;
    u8 chr;
    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();

    for (i = 0; i < lbl_8047368C.xEF; i++) {
        chr = lbl_8047368C.xF1[i];
        if (chr != CHKIND_MAX) {
            Player_80036E20(chr, lbl_804D65F4, 1);
        }
    }

    for (i = 0; i < lbl_8047368C.xF0; i++) {
        if (lbl_8047368C.xF4[i] == CKIND_GKOOPS) {
            lbl_8047368C.xF4[i] = CKIND_KOOPA;
        }
        chr = lbl_8047368C.xF4[i];
        if (chr != CHKIND_MAX) {
            Player_80036E20(chr, lbl_804D65F4, 1);
        }
    }
}

s32 fn_80185E34(void)
{
    ClassicProcArray local;
    int i;
    int player_slot = 0;
    local = lbl_803B7C28;

    for (i = 0; i < lbl_8047368C.xEF; i++) {
        if (lbl_8047368C.xF1[i] != 0x21) {
            Player_80036CF0(player_slot);
            Player_SetPlayerCharacter(player_slot,
                                      (CharacterKind) lbl_8047368C.xF1[i]);
            Player_SetCostumeId(player_slot, (s32) lbl_8047368C.xF7[i]);
            Player_SetPlayerId(player_slot, 0);
            Player_SetSlottype(player_slot, Gm_PKind_Demo);
            Player_SetFacingDirection(player_slot, 0.0f);
            Player_SetModelScale(player_slot, 1.0f);
            Player_SetFlagsBit5(player_slot, lbl_8047368C.xFD[i]);
            Player_80036F34(player_slot, 5);
            HSD_GObj_SetupProc(Player_GetEntity(player_slot),
                               (HSD_GObjEvent) (Event) local.v[i], 0x16);
            player_slot++;
        }
    }
    return player_slot;
}

void fn_80185F5C(s32 arg0)
{
    ClassicProcArray local;
    int i = 0;
    local = lbl_803B7C40;

    while (i < lbl_8047368C.xF0) {
        if (lbl_8047368C.xF1[i] != 0x21) {
            Player_80036CF0(arg0);
            Player_SetPlayerCharacter(arg0,
                                      (CharacterKind) lbl_8047368C.xF4[i]);
            Player_SetCostumeId(arg0, (s32) lbl_8047368C.xFA[i]);
            Player_SetPlayerId(arg0, 0);
            Player_SetSlottype(arg0, Gm_PKind_Demo);
            Player_SetFacingDirection(arg0, 0.0f);
            Player_SetModelScale(arg0, 1.0f);
            Player_SetFlagsBit5(arg0, lbl_8047368C.x100[i]);
            Player_80036F34(arg0, 6);
            HSD_GObj_SetupProc(Player_GetEntity(arg0),
                               (HSD_GObjEvent) (Event) local.v[i + 3], 0x16);
            arg0++;
        }
        i++;
    }
}

void fn_80186080(void)
{
    s32 temp_r31;

    temp_r31 = HSD_SisLib_803A611C(0, NULL, 9, 0x14, 0, 0xE, 0, 0x12);
    HSD_SisLib_803A62A0(0, "SdIntro.dat", "SIS_IntroData");
    lbl_804735A8.x4[6] = (HSD_JObj*) HSD_SisLib_803A5ACC(
        0, temp_r31, 0.0f, 0.0f, 0.0f, 640.0f, 480.0f);
    if (lbl_8047368C.game_type == 1) {
        if (lbLang_IsSavedLanguageUS()) {
            HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 5);
            return;
        }
        HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 2);
    } else if (lbl_8047368C.game_type == 3) {
        if (lbLang_IsSavedLanguageUS()) {
            HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 6);
            return;
        }
        HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 3);
    } else if (lbl_8047368C.game_type == 2) {
        if (lbLang_IsSavedLanguageUS()) {
            HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 7);
            return;
        }
        HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 4);
    }
}

static char lbl_804D40B0[] = "IrRdMap";

void fn_801861B8(void)
{
    HSD_Text* text;
    s32 i;

    PAD_STACK(16);

    HSD_SisLib_803A611C(0, NULL, 9, 0x14, 0, 0xE, 0, 0x12);
    HSD_SisLib_803A62A0(0, "SdIntro.dat", "SIS_IntroData");

    for (i = 0; i < (s32) lbl_8047368C.xEF; i++) {
        lbl_804735A8.x4[7 + i] = (HSD_JObj*) HSD_SisLib_803A6754(0, 0);
        ((HSD_Text*) lbl_804735A8.x4[7 + i])->default_kerning = 1;
        text = (HSD_Text*) lbl_804735A8.x4[7 + i];
        text->font_size.x = 1.0f;
        text->font_size.y = 1.0f;
        ((HSD_Text*) lbl_804735A8.x4[7 + i])->default_alignment = 1;
        HSD_SisLib_803A6B98((HSD_Text*) lbl_804735A8.x4[7 + i],
                            lbl_804D6604->x57C[lbl_8047368C.xEF].x00[i],
                            lbl_804D6604->x57C[lbl_8047368C.xEF].x0C[i], " ");
        HSD_SisLib_803A7548((HSD_Text*) lbl_804735A8.x4[7 + i], 0,
                            lbl_804D6604->x57C[lbl_8047368C.xEF].x18[i],
                            lbl_804D6604->x57C[lbl_8047368C.xEF].x24[i]);
    }

    for (i = 0; i < (s32) lbl_8047368C.xF0; i++) {
        lbl_804735A8.x4[10 + i] = (HSD_JObj*) HSD_SisLib_803A6754(0, 0);
        ((HSD_Text*) lbl_804735A8.x4[10 + i])->default_kerning = 1;
        text = (HSD_Text*) lbl_804735A8.x4[10 + i];
        text->font_size.x = 1.0f;
        text->font_size.y = 1.0f;
        ((HSD_Text*) lbl_804735A8.x4[10 + i])->default_alignment = 1;
        if (lbl_8047368C.model_scale_kind == 4) {
            HSD_SisLib_803A6B98((HSD_Text*) lbl_804735A8.x4[10 + i],
                                340.0f + lbl_804D6604->x57C[1].x00[0],
                                lbl_804D6604->x57C[1].x0C[0], " ");
            HSD_SisLib_803A7548((HSD_Text*) lbl_804735A8.x4[10 + i], 0,
                                340.0f + lbl_804D6604->x57C[1].x18[0],
                                lbl_804D6604->x57C[1].x24[0]);
            return;
        }
        HSD_SisLib_803A6B98((HSD_Text*) lbl_804735A8.x4[10 + i],
                            340.0f +
                                lbl_804D6604->x57C[lbl_8047368C.xF0].x00[i],
                            lbl_804D6604->x57C[lbl_8047368C.xF0].x0C[i], " ");
        HSD_SisLib_803A7548((HSD_Text*) lbl_804735A8.x4[10 + i], 0,
                            340.0f +
                                lbl_804D6604->x57C[lbl_8047368C.xF0].x18[i],
                            lbl_804D6604->x57C[lbl_8047368C.xF0].x24[i]);
    }
}

void fn_80186400(void)
{
    HSD_GObj* gobj = GObj_Create(0xE, 0xF, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(lbl_804D65FC->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObj_SetupProc(gobj, fn_80184AB8, 0);
    gm_8016895C(jobj, lbl_804D65FC->models[0], 0);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjAnimAll(jobj);
    if (lbl_8047368C.model_scale_kind != 3) {
        lb_80011E24(jobj, &lbl_804735A8.x4[0], 4, -1);
        lb_80011E24(jobj, &lbl_804735A8.x4[1], 5, -1);
        lb_80011E24(jobj, &lbl_804735A8.x4[2], 0x3A, -1);
        lb_80011E24(jobj, &lbl_804735A8.x4[3], 0x3B, -1);
        HSD_JObjSetTranslateZ(lbl_804735A8.x4[2], 10000.0F);
        HSD_JObjSetTranslateZ(lbl_804735A8.x4[3], 10000.0F);
    }
}

typedef struct ClassicArchiveNameArray {
    const char* v[4];
} ClassicArchiveNameArray;

typedef struct ClassicArchiveNameLocal {
    ClassicArchiveNameArray names;
    u32 pad;
} ClassicArchiveNameLocal;

static inline void* gm_80186634_LoadLightList(void)
{
    return lb_80011AC4(lbl_804D65FC->lights);
}

static inline void gm_80186634_SetupLight(void)
{
    HSD_GObj* gobj;

    gobj = GObj_Create(0xB, 3, 0);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_LightKind,
                            gm_80186634_LoadLightList());
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);
}

static inline void gm_80186634_SetupCamera(void)
{
    HSD_GObj* gobj2;
    HSD_GObj* gobj;
    HSD_CObj* cobj;
    HSD_CObj* cobj2;

    gobj = GObj_Create(0x13, 0x14, 0);
    cobj = HSD_CObjLoadDesc(lbl_804D65FC->cameras[0].desc);
    cobj2 = HSD_CObjLoadDesc(lbl_804D6600->cameras[0].desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_CameraKind, cobj);
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 8);
    gobj->gxlink_prios = 0x801;
    gobj2 = GObj_Create(0x13, 0x15, 0);
    HSD_GObjObject_80390A70(gobj2, HSD_GObj_CameraKind, cobj2);
    if (lbl_8047368C.model_scale_kind == 4) {
        GObj_SetupGXLinkMax(gobj2, (GObj_RenderFunc) (Event) fn_8018569C, 8);
    } else {
        GObj_SetupGXLinkMax(gobj2, (GObj_RenderFunc) (Event) fn_8018575C, 8);
    }
}

static inline void gm_80186634_SetupModel(void)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(lbl_804D6600->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xC, 0);
    HSD_GObj_SetupProc(gobj, (HSD_GObjEvent) (Event) fn_8018504C, 0x11);
    gm_8016895C(jobj, lbl_804D6600->models[0], 0);
    HSD_JObjReqAnimAll(jobj, (f32) ((lbl_8047368C.xEE - 1) * 0x32));
    HSD_JObjAnimAll(jobj);
    lb_80011E24(jobj, &lbl_804735A8.x4[4], 0xE, -1);
    lb_80011E24(jobj, &lbl_804735A8.x4[5], 1, -1);
}

static inline void gm_80186634_SetupFog(void)
{
    HSD_GObj* gobj;
    HSD_Fog* fog;

    gobj = GObj_Create(0xE, 0xF, 0);
    fog = HSD_FogLoadDesc(lbl_804D65FC->fogs[0].desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_FogKind, fog);
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0xB, 0);
}

void fn_80186634(void* arg0)
{
    ClassicArchiveNameLocal local;
    PAD_STACK(12);

    lbArchive_80016DBC("GmIntEz.dat", &lbl_804D6604, "gmIntroEasyTable", 0);
    Camera_80028B9C(0xC);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8(St_Kind_Dummy, NULL);
    Item_80266FA8();
    Item_80266FCC();
    Stage_8022524C();
    efLib_Init();
    efAsync_LoadSync(0);

    local.names = *(const ClassicArchiveNameArray*) lbl_803B7C58;
    lbl_804D65F4 = lbArchive_80016DBC(local.names.v[lbl_8047368C.game_type],
                                      &lbl_804D65FC, lbl_803D9444, 0);
    lbl_804D65F8 =
        lbArchive_80016DBC(lbl_804D40B0, &lbl_804D6600, lbl_803D9444, 0);

    gm_80186634_SetupLight();

    if (lbl_8047368C.model_scale_kind != 3) {
        lbl_8047368C.game_type = 0;
    }

    switch (lbl_8047368C.model_scale_kind) {
    case 3:
        gm_80186634_SetupCamera();
        fn_80186400();
        gm_80186634_SetupModel();
        gm_80186634_SetupFog();
        fn_80186080();
        break;
    case 0:
    case 1:
    case 2:
        gm_80186634_SetupCamera();
        fn_80186400();
        gm_80186634_SetupModel();
        gm_80186634_SetupFog();
        fn_801861B8();
        fn_80185D64();
        fn_80185F5C(fn_80185E34());
        break;
    case 4:
        gm_80186634_SetupCamera();
        fn_80186400();
        gm_80186634_SetupModel();
        gm_80186634_SetupFog();
        fn_801861B8();
        fn_80185D64();
        fn_80185A0C();
        fn_80185E34();
        break;
    }

    lbAudioAx_80023F28(0x2D);
}

void gm_Scene_IntroEasy_OnFrame(void)
{
    if (lbl_804735A8.x0 != 0) {
        lbAudioAx_800236DC();
        gm_801A4B60();
    }
}
/// Classic Mode intro scene enter data (0x20 bytes)
typedef struct ClassicModeEnterData {
    /* 0x00 */ int x0;
    /* 0x04 */ int x4;
    /* 0x08 */ int x8;
    /* 0x0C */ int xC;
    /* 0x10 */ union {
        int x10_int;
        struct {
            u8 x10;
            u8 x11;
        };
    };
    /* 0x14 */ int x14;
    /* 0x18 */ int x18;
    /* 0x1C */ int x1C;
} ClassicModeEnterData;

void gm_Scene_IntroEasy_OnEnter(void* arg0_)
{
    ClassicModeEnterData* arg0 = arg0_;

    if (arg0->x10 == 0x1A || arg0->x11 == 0x1A) {
        lbl_804735A8.x0 = 1;
        return;
    }

    lbl_804735A8.x0 = 0;
    lbl_804735A8.x38 = 0;
    lbl_804735A8.x3A = 0;
    lbl_804735A8.x3C = 0;
    *(ClassicModeEnterData*) &lbl_8047368C.model_scale_kind = *arg0;
    fn_80186634(arg0_);
    lbl_804D6608 = -1;
    gm_80167858((int) (s8) lbl_8047368C.xEC, lbl_8047368C.xED, 0xB, 0x2D);
    gm_80168F88();
}
