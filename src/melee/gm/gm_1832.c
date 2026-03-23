#include "gm_1832.h"

#include "gm_unsplit.h"

#include "pl/pl_040D.h"

#include <math_ppc.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/wobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/sislib.h>
#include <sysdolphin/baselib/sobjlib.h>
#include <sysdolphin/baselib/state.h>
#include <sysdolphin/baselib/tobj.h>
#include <sysdolphin/baselib/util.h>
#include <sysdolphin/baselib/random.h>
#include <Runtime/runtime.h>
#include <melee/cm/camera.h>
#include <melee/ef/efasync.h>
#include <melee/ef/eflib.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/ftdemo.h>
#include <melee/ft/ftlib.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gm_1A45.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_1A36.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>

#include "gm_1B03.static.h"
#include <melee/gr/ground.h>
#include <melee/gr/grpushon.h>
#include <melee/gr/stage.h>
#include <melee/if/ifstatus.h>
#include <melee/if/ifall.h>
#include <melee/it/item.h>
#include <melee/it/it_266F.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lb_0192.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lblanguage.h>
#include <melee/mn/types.h>
#include <melee/mn/mnname.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/player.h>
#include <melee/sc/types.h>

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
    int xE4; ///< related to model scale
    int xE8; ///< game type
    u8 xEC;
    u8 xED;
    u8 xEE;    ///< roadmap (IrRdMap) progress
    u8 xEF;    ///< left char amt
    u8 xF0;    ///< right char amt
    u8 xF1[3]; ///< left char ids
    u8 xF4[3]; ///< right char ids
    u8 xF7[3]; ///< left costumes
    u8 xFA[3]; ///< right costumes
    u8 xFD[3]; ///< left metal flags
    u8 x100[3]; ///< right metal flags
    u8 pad_103;
    u8 pad_104[0x54];
} lbl_804735E8;

static HSD_Archive* lbl_804D65F4;
static HSD_Archive* lbl_804D65F8;
static HSD_GObj* lbl_804D65F0;
static SceneDesc* lbl_804D6600;

extern int lbl_804D6608;

typedef struct { s32 v[6]; } ClassicProcArray;

extern ClassicProcArray lbl_803B7C40;
extern ClassicProcArray lbl_803B7C28;

extern DynamicModelDesc** lbl_804D662C;
extern HSD_Archive* lbl_804D6628;
extern u8 lbl_803D9828[];
extern f32 lbl_803B7C68[];

typedef struct {
    /* 0x00 */ f32 vals[3];
} ClassicSlotVals;
STATIC_ASSERT(sizeof(ClassicSlotVals) == 0xC);

typedef struct {
    /* 0x00 */ f32 x00;
    /* 0x04 */ f32 x04;
    /* 0x08 */ Vec3 x08;
    /* 0x14 */ u8 pad_14[0x8];
} ClassicCharLayout;
STATIC_ASSERT(sizeof(ClassicCharLayout) == 0x1C);

typedef struct {
    /* 0x00 */ f32 x00;
    /* 0x04 */ f32 x04;
    /* 0x08 */ f32 x08;
    /* 0x0C */ u8 pad_0C[0x8];
} ClassicTeamEntry;
STATIC_ASSERT(sizeof(ClassicTeamEntry) == 0x14);

typedef struct {
    /* 0x00 */ f32 x00[3];
    /* 0x0C */ f32 x0C[3];
    /* 0x18 */ f32 x18[3];
    /* 0x24 */ f32 x24[3];
} ClassicSplashRow;
STATIC_ASSERT(sizeof(ClassicSplashRow) == 0x30);

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

/// Classic mode stage data table entry (size 0x10)
/// Table has 65 entries: 13 stages × 5 difficulty levels
typedef struct ClassicStageEntry {
    /* 0x00 */ u8 stage_kind;
    /* 0x01 */ u8 pad_1;
    /* 0x02 */ u16 scale0_pct; ///< Divided by 100 to get ratio
    /* 0x04 */ u16 scale1_pct; ///< Divided by 100 to get ratio
    /* 0x06 */ u8 pad_6[0xA];
} ClassicStageEntry;
STATIC_ASSERT(sizeof(ClassicStageEntry) == 0x10);

extern ClassicStageEntry lbl_803D9910[65];

void fn_8018325C(HSD_GObj* arg0, int arg1)
{
    Vec3 pos;
    HSD_JObj* jobj = arg0->hsd_obj;
    HSD_JObj* src = lbl_804735A8.x4[0];
    int i;
    HSD_JObj* arrow;

    HSD_JObjGetTranslation(src, &pos);
    HSD_JObjSetTranslate(jobj, &pos);

    switch (arg1) {
    case 1:
        HSD_JObjAddTranslationZ(jobj, -10.0f);
        if (lbl_804735A8.x38 > 0x50U) {
            arrow = lbl_804735A8.x4[2];
            HSD_JObjSetTranslateX(arrow, -1.0f);
            HSD_JObjSetTranslateY(arrow, 0.0f);
            HSD_JObjSetTranslateZ(arrow, 5.0f);
            HSD_JObjSetScaleX(arrow, 2.8f);
            HSD_JObjSetScaleY(arrow, 2.8f);
        }
        break;
    case 2:
        HSD_JObjAddTranslationZ(jobj, -30.0f);
        if (lbl_804735A8.x38 > 0x5AU) {
            arrow = lbl_804735A8.x4[3];
            HSD_JObjSetTranslateX(arrow, -0.5f);
            HSD_JObjSetTranslateY(arrow, 3.0f);
            HSD_JObjSetTranslateZ(arrow, 5.0f);
            HSD_JObjSetScaleX(arrow, 2.2f);
            HSD_JObjSetScaleY(arrow, 2.2f);
        }
        break;
    }

    if (lbl_804735E8.xE4 == 2) {
        HSD_JObjAddTranslationX(
            jobj, lbl_804D6604->x6A8[lbl_804735E8.xF1[arg1]].x00 -
                      lbl_804D6604->x630[lbl_804735E8.xEF].vals[arg1]);
        HSD_JObjAddTranslationY(
            jobj, lbl_804D6604->x6A8[lbl_804735E8.xF1[arg1]].x04 +
                      lbl_804D6604->x654[lbl_804735E8.xEF].vals[arg1]);

        HSD_JObjSetScaleX(jobj,
                          lbl_804D6604->x6A8[lbl_804735E8.xF1[arg1]].x08.x *
                              lbl_804D6604->x678[lbl_804735E8.xEF].vals[arg1]);
        HSD_JObjSetScaleY(jobj,
                          lbl_804D6604->x6A8[lbl_804735E8.xF1[arg1]].x08.y *
                              lbl_804D6604->x678[lbl_804735E8.xEF].vals[arg1]);
        HSD_JObjSetScaleZ(jobj,
                          lbl_804D6604->x6A8[lbl_804735E8.xF1[arg1]].x08.z *
                              lbl_804D6604->x678[lbl_804735E8.xEF].vals[arg1]);
    } else {
        HSD_JObjAddTranslationX(
            jobj, lbl_804D6604->x6C[lbl_804735E8.xF1[arg1]].x00 -
                      lbl_804D6604->x00[lbl_804735E8.xEF - 1].vals[arg1]);

        HSD_JObjAddTranslationY(
            jobj, lbl_804D6604->x6C[lbl_804735E8.xF1[arg1]].x04 +
                      lbl_804D6604->x18[lbl_804735E8.xEF].vals[arg1]);

        {
            f32 scale_factor = lbl_804D6604->x3C[lbl_804735E8.xEF].vals[arg1];
            HSD_JObjSetScaleX(jobj,
                              lbl_804D6604->x6C[lbl_804735E8.xF1[arg1]].x08.x *
                                  scale_factor);
            HSD_JObjSetScaleY(jobj,
                              lbl_804D6604->x6C[lbl_804735E8.xF1[arg1]].x08.y *
                                  scale_factor);
            HSD_JObjSetScaleZ(jobj,
                              lbl_804D6604->x6C[lbl_804735E8.xF1[arg1]].x08.z *
                                  scale_factor);
        }
    }

    for (i = 0; i < 6; i++) {
        if (Player_GetEntity(i) == arg0) {
            HSD_GObj* entity2 = Player_GetEntityAtIndex(i, 1);
            if (entity2 != NULL) {
                HSD_JObj* jobj2 = entity2->hsd_obj;
                HSD_JObjGetTranslation(jobj, &pos);
                HSD_JObjSetTranslate(jobj2, &pos);
                HSD_JObjGetScale(jobj, &pos);
                HSD_JObjSetScale(jobj2, &pos);
            }
        }
    }
}

void fn_80184138(HSD_GObj* arg0, int arg1)
{
    Vec3 pos;
    Vec3 scale;
    HSD_JObj* jobj = arg0->hsd_obj;
    HSD_JObj* src = lbl_804735A8.x4[1];
    f32 scl, xoff, yoff;
    int i;
    PAD_STACK(8);

    HSD_JObjGetTranslation(src, &pos);
    HSD_JObjSetTranslate(jobj, &pos);

    if ((s32) lbl_804735E8.xE4 == 2) {
        scl = lbl_804D6604->x37C[lbl_804735E8.xF4[arg1]].x08;
    } else {
        scl = 1.0f;
    }

    if ((s32) lbl_804735E8.xE4 == 2) {
        xoff = lbl_804D6604->x37C[lbl_804735E8.xF4[arg1]].x00;
    } else {
        xoff = 0.0f;
    }

    if ((s32) lbl_804735E8.xE4 == 2) {
        yoff = lbl_804D6604->x37C[lbl_804735E8.xF4[arg1]].x04;
    } else {
        yoff = 0.0f;
    }

    if (arg1 != 0) {
        HSD_JObjAddTranslationZ(jobj, (f32) (-arg1 * 0x14 + 0xA));
    }

    {
        f32 x_adj =
            xoff + (-lbl_804D6604->x6C[lbl_804735E8.xF4[arg1]].x00 +
                    lbl_804D6604->x00[lbl_804735E8.xF0 - 1].vals[arg1]);
        HSD_JObjAddTranslationX(jobj, x_adj);
    }

    {
        f32 y_adj = yoff + (lbl_804D6604->x6C[lbl_804735E8.xF4[arg1]].x04 +
                            lbl_804D6604->x18[lbl_804735E8.xF0].vals[arg1]);
        HSD_JObjAddTranslationY(jobj, y_adj);
    }

    if ((s32) lbl_804735E8.xE4 == 2) {
        HSD_JObjSetScaleX(
            jobj, lbl_804D6604->x6C[lbl_804735E8.xF4[arg1]].x08.x * scl);
        HSD_JObjSetScaleY(
            jobj, lbl_804D6604->x6C[lbl_804735E8.xF4[arg1]].x08.y * scl);
        HSD_JObjSetScaleZ(
            jobj, lbl_804D6604->x6C[lbl_804735E8.xF4[arg1]].x08.z * scl);
    } else {
        f32 scale_factor = lbl_804D6604->x3C[lbl_804735E8.xF0].vals[arg1];
        HSD_JObjSetScaleX(jobj,
                          lbl_804D6604->x6C[lbl_804735E8.xF4[arg1]].x08.x *
                              scale_factor);
        HSD_JObjSetScaleY(jobj,
                          lbl_804D6604->x6C[lbl_804735E8.xF4[arg1]].x08.y *
                              scale_factor);
        HSD_JObjSetScaleZ(jobj,
                          lbl_804D6604->x6C[lbl_804735E8.xF4[arg1]].x08.z *
                              scale_factor);
    }

    for (i = 0; i < 6; i++) {
        if (Player_GetEntity(i) == arg0) {
            HSD_GObj* entity2 = Player_GetEntityAtIndex(i, 1);
            if (entity2 != NULL) {
                HSD_JObj* jobj2 = entity2->hsd_obj;
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

static char lbl_803D9414[] = {
    0x82, 0x73, 0x82, 0x85, 0x82, 0x81, 0x82, 0x8D, 0, 0, 0, 0
};

static char lbl_804D40A0[] = { 0x8C, 0x52, 0x92, 0x63, 0x00 };

void fn_80184AB8(HSD_GObj* arg0)
{
    HSD_JObj* sp110;
    char sp10[0x100];
    HSD_JObj* jobj;
    s32 i;
    char* name;
    s32 k;

    jobj = arg0->hsd_obj;
    HSD_JObjAnimAll(jobj);

    if ((u16) lbl_804735A8.x38 < 0x8CU) {
        lbl_804735A8.x38 = (u16) (lbl_804735A8.x38 + 1);
        if ((s32) lbl_804735E8.xE4 != 3) {
            if ((u8) lbl_804735E8.xEE < 0xAU) {
                lb_80011E24(jobj, &sp110, 0x12, -1);
                HSD_TObjReqAnimAll(sp110->u.dobj->mobj->tobj,
                                   (f32) (lbl_804735E8.xEE % 10));
                HSD_AObjSetRate(sp110->u.dobj->mobj->tobj->aobj, 0.0f);
                lb_80011E24(jobj, &sp110, 0x13, -1);
                HSD_TObjReqAnimAll(sp110->u.dobj->mobj->tobj, 10.0f);
                HSD_AObjSetRate(sp110->u.dobj->mobj->tobj->aobj, 0.0f);
            } else {
                lb_80011E24(jobj, &sp110, 0x12, -1);
                HSD_TObjReqAnimAll(sp110->u.dobj->mobj->tobj,
                                   (f32) (lbl_804735E8.xEE / 10));
                HSD_AObjSetRate(sp110->u.dobj->mobj->tobj->aobj, 0.0f);
                lb_80011E24(jobj, &sp110, 0x13, -1);
                HSD_TObjReqAnimAll(sp110->u.dobj->mobj->tobj,
                                   (f32) (lbl_804735E8.xEE % 10));
                HSD_AObjSetRate(sp110->u.dobj->mobj->tobj->aobj, 0.0f);
            }

            switch ((s32) lbl_804735A8.x38) {
            case 0xA:
                lbAudioAx_800237A8(0x9C4A, 0x7F, 0x40);
                return;
            case 0x46:
                if ((s32) lbl_804735E8.xE4 == 4 ||
                    (s32) lbl_804735E8.xE4 == 1) {
                    lbl_804D6608 = lbAudioAx_800237A8(0x7C863, 0x7F, 0x40);
                    return;
                }
                if ((s32) lbl_804735E8.xE4 == 2) {
                    lbl_804D6608 = lbAudioAx_800237A8(0x7C837, 0x7F, 0x40);
                    return;
                }
                if ((u8) lbl_804735E8.x100[0] != 0) {
                    lbl_804D6608 = lbAudioAx_800237A8(0x7C847, 0x7F, 0x40);
                    return;
                }
                break;
            case 0x64:
                if ((s32) lbl_804D6608 != -1) {
                    lbAudioAx_800236B8(lbl_804D6608);
                }
                gm_80168C5C((u32) lbl_804735E8.xF4[0]);
                return;
            case 0x5:
                for (i = 0; i < (s32) lbl_804735E8.xEF; i++) {
                    if (i != 0 || (u8) lbl_804735E8.xED == 0x78) {
                        fn_80160DE8(lbl_804735A8.x4[7 + i],
                                    lbl_804735E8.xF1[i], 0, 0,
                                    lbl_804D6604->x57C[lbl_804735E8.xEF].x18[i],
                                    lbl_804D6604->x57C[lbl_804735E8.xEF].x24[i]);
                    } else {
                        name = GetNameText((s32) lbl_804735E8.xED);
                        HSD_SisLib_803A70A0(
                            (HSD_Text*) lbl_804735A8.x4[7 + i], 0, name);
                        HSD_SisLib_803A7548(
                            (HSD_Text*) lbl_804735A8.x4[7 + i], 0, 1.0f, 1.0f);
                    }
                }
                return;
            case 0x6:
                if ((s32) lbl_804735E8.xE4 == 4) {
                    k = 0;
                    name = (char*) gm_80160980(lbl_804735E8.xF4[0]);
                    if (lbLang_IsSavedLanguageUS()) {
                        {
                            char* src = lbl_803D9414;
                            while (*src != 0) {
                                sp10[k] = *src;
                                src++;
                                k++;
                            }
                        }
                        sp10[k] = ' ';
                        k++;
                        while (*name != 0) {
                            sp10[k] = *name;
                            name++;
                            k++;
                        }
                        sp10[k] = 0;
                    } else {
                        {
                            char* src2 = lbl_804D40A0;
                            while (*name != 0) {
                                sp10[k] = *name;
                                name++;
                                k++;
                            }
                            sp10[k] = ' ';
                            k++;
                            while (*src2 != 0) {
                                sp10[k] = *src2;
                                src2++;
                                k++;
                            }
                            sp10[k] = 0;
                        }
                    }
                    HSD_SisLib_803A70A0(
                        (HSD_Text*) lbl_804735A8.x4[10], 0, sp10);
                    HSD_SisLib_803A7548(
                        (HSD_Text*) lbl_804735A8.x4[10], 0,
                        0.8f * (lbl_804D6604->x57C[1].x18[0] *
                                fn_80160F58(lbl_804735E8.xF4[0])),
                        lbl_804D6604->x57C[1].x24[0]);
                    return;
                }
                for (i = 0; i < (s32) lbl_804735E8.xF0; i++) {
                    fn_80160DE8(lbl_804735A8.x4[10 + i],
                                lbl_804735E8.xF4[i], 0, 1,
                                lbl_804D6604->x57C[lbl_804735E8.xF0].x18[i],
                                lbl_804D6604->x57C[lbl_804735E8.xF0].x24[i]);
                }
                break;
            }
        }
    } else {
        lbl_804735A8.x0 = 1;
    }
}

void fn_8018504C(void)
{
    int new_var;
    PAD_STACK(16);
    new_var = 0x32;
    if ((u16) lbl_804735A8.x3A < 0x31U) {
        lbl_804735A8.x3A = (u16) (lbl_804735A8.x3A + 1);
    } else {
        lbl_804735A8.x3A = 0;
    }
    if ((u16) lbl_804735A8.x3C < 0x31U) {
        lbl_804735A8.x3C = (u16) (lbl_804735A8.x3C + 1);
    }
    HSD_JObjReqAnimAll(lbl_804735A8.x4[5],
        (f32) (lbl_804735A8.x3C + ((lbl_804735E8.xEE * 0x32) - new_var)));
    HSD_JObjAnimAll(lbl_804735A8.x4[5]);
    HSD_JObjReqAnimAll(lbl_804735A8.x4[4],
        (f32) (lbl_804735A8.x3A + ((lbl_804735E8.xEE * 0x32) - new_var)));
    HSD_JObjAnimAll(lbl_804735A8.x4[4]);
    if (((u16) lbl_804735A8.x38 == 0x2D) &&
        ((s32) lbl_804735E8.xE4 == 3))
    {
        switch ((s32) lbl_804735E8.xE8) {
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

static f32 lbl_803D9248[] = {
    0.6f, 0.35f, 0.6f, 0.5f, 0.6f, 0.35f, 0.6f, 0.6f, 0.7f, 0.6f,
    0.5f, 0.6f, 0.6f, 0.6f, 0.5f, 0.5f, 0.6f, 0.5f, 0.6f, 0.6f,
    0.5f, 0.6f, 0.6f, 0.6f, 0.6f, 0.5f, 0.5f, 0.5f,
    0.0f, -6.0f, 0.0f,
    0.0f, -3.5f, 0.0f,
    -1.0f, -3.5f, 0.0f,
    0.0f, -3.5f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -3.0f, 0.0f,
    0.0f, -5.0f, 0.0f,
    0.0f, -3.5f, 0.0f,
    0.0f, -3.5f, 0.0f,
    0.0f, -3.5f, 0.0f,
    0.0f, -3.0f, 0.0f,
    -0.5f, -3.5f, 0.0f,
    -2.0f, -6.0f, 0.0f,
    0.0f, -2.5f, 0.0f,
    0.0f, -2.5f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    0.0f, -5.0f, 0.0f,
    0.0f, -3.0f, 0.0f,
    -1.0f, -6.0f, 0.0f,
    -1.0f, -2.5f, 0.0f,
    -1.0f, -3.5f, 0.0f,
    0.0f, -3.5f, 0.0f,
    0.0f, -4.0f, 0.0f,
    -1.0f, -3.5f, 0.0f,
    0.0f, -1.5f, 0.0f,
    0.0f, -4.5f, 0.0f,
    0.0f, -3.5f, 0.0f,
    0.0f, -3.5f, 0.0f,
    3.0f, 4.0f, -5.0f,
};

typedef struct ClassicCharData {
    f32 scale[28];
    Vec3 offset[28];
    Vec3 samus_extra;
} ClassicCharData;

s32 fn_801851C0(void)
{
    u8 pad_stack[8];
    Vec3 pos;
    s32 i;
    s32 result;

    for (i = 0; i < (s32) lbl_804735E8.xE0; i++) {
        ClassicCharData* data = (ClassicCharData*) lbl_803D9248;
        result = i + 1;
        Player_SetPlayerCharacter(result,
            (CharacterKind) lbl_804735E8.xF4[0]);
        Player_SetPlayerId(result, 0);
        Player_SetSlottype(result, Gm_PKind_Demo);
        Player_SetFacingDirection(result, 0.0f);
        Player_SetCostumeId(result, i);
        pos = data->offset[lbl_804735E8.xF4[0]];
        Player_80032768(result, &pos);
        if ((u8) lbl_804735E8.xF4[0] == 0xE) {
            pos.x += data->samus_extra.x;
            pos.y += data->samus_extra.y;
            pos.z += data->samus_extra.z;
            Player_80032828(result, 1, &pos);
        }
        Player_SetModelScale(result,
            data->scale[lbl_804735E8.xF4[0]]);
        Player_SetFlagsBit5(result, lbl_804735E8.x100[0]);
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
}

extern float MSL_TrigF_80400770[];
extern float MSL_TrigF_80400774[];
#pragma dont_inline on
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
#pragma dont_inline reset

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

/// @brief Creates splash screen sprite objects from pre-rendered character images.
/// Distributes 10 image tiles across a grid with random offsets.
void fn_801857C4(HSD_GObj* arg0)
{
    Vec3 pos;
    Vec3 pos_copy;
    HSD_ImageDesc* descs[3];
    HSD_SObj* sobj;
    u64 num_cols;
    s32 row;
    u32 total_tiles;
    u32 delay;
    s32 i;
    u8* img_idx;

    PAD_STACK(0x10);

    if (lbl_804735E8.xE1 != 0) {
        HSD_GObjPLink_80390228(lbl_804D65F0);
        img_idx = lbl_804735E8.xD0;
        delay = 1;
        for (i = 0; i < 10; i++, img_idx++) {
            descs[0] = &lbl_804735E8.x40[*img_idx];
            descs[1] = 0;
            descs[2] = &lbl_804735E8.x88[*img_idx];
            sobj = HSD_SObjLib_803A477C(lbl_804735E8.xDC,
                                        (s32) &descs[0], 0, 0, 0x80, 1);
            total_tiles = 10;
            num_cols = (s32) fn_801855BC(total_tiles);
            row = (u8) i / (u8) num_cols;
            pos.x = (40.0f * HSD_Randf()) +
                    (280.0f +
                     ((290.0f / (f32) (u8) (((u8) num_cols + 9) /
                                            (u8) num_cols)) *
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

s32 fn_80185A0C(void)
{
    HSD_GObj* gobj;
    HSD_GObj* gobj2;
    HSD_GObj* gobj3;
    HSD_GObjProc* proc;
    HSD_ImageDesc* img;
    s32 i, v;
    u8 count;

    PAD_STACK(24);

    gobj = GObj_Create(0x13, 0x14, 0);
    HSD_SObjLib_803A55DC(gobj, 0x280, 0x1E0, 0xB);
    gobj->gxlink_prios = 0x20000;
    HSD_GObjGXLink_8039084C(gobj);
    GObj_SetupGXLinkMax(gobj, (GObj_RenderFunc) fn_8018564C, 0xB);

    gobj2 = GObj_Create(0xE, 0xF, 0);
    HSD_GObjObject_80390A70(gobj2, HSD_SObjLib_804D7960, NULL);
    GObj_SetupGXLink(gobj2, HSD_SObjLib_803A49E0, 0x11, 0);
    proc = HSD_GObj_SetupProc(gobj2, fn_801859C8, 0);
    proc->flags_3 = HSD_GObj_804D783C;

    count = gm_80169238(lbl_804735E8.xF4[0]);
    if ((s32) count > 3) {
        count = 3;
    }
    lbl_804735E8.xE0 = count;

    img = lbl_804735E8.x40;
    lbl_804735E8.xDC = gobj2;
    lbl_804735E8.xE1 = 0;

    for (i = 0; i < (s32) lbl_804735E8.xE0; i++) {
        img->image_ptr = NULL;
        lb_800121FC(img, 0x17C, 0x190, GX_TF_RGB5A3, 0);
        img[3].image_ptr = NULL;
        lb_800121FC(&img[3], 0x17C, 0x190, GX_TF_Z24X8, 0);
        img++;
    }

    for (v = 0; v < 10; v++) {
        if ((v / (s32) lbl_804735E8.xE0) % 2 != 0) {
            lbl_804735E8.xD0[v] =
                (u8) ((lbl_804735E8.xE0 - 1) -
                      (v % (s32) lbl_804735E8.xE0));
        } else {
            lbl_804735E8.xD0[v] =
                (u8) (v % (s32) lbl_804735E8.xE0);
        }
    }

    HSD_GObj_SetupProc(GObj_Create(0x13, 1, 0), fn_801857C4, 0);

    gobj3 = GObj_Create(0x13, 0x14, 0);
    HSD_GObjObject_80390A70(gobj3, HSD_GObj_804D784B,
                            HSD_CObjLoadDesc(lbl_804D6600->cameras->desc));
    GObj_SetupGXLinkMax(gobj3, (GObj_RenderFunc) fn_801852FC, 0);
    gobj3->gxlink_prios = 0x61;
    lbl_804D65F0 = gobj3;
    return fn_801851C0();
}

void fn_80185D64(void)
{
    int i;
    u8* ptr;
    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();

    /// @todo fix pointer arithmetic
    /// is this indicative of an inner struct starting at xE4?
    ptr = (u8*) &lbl_804735E8.xE4;
    for (i = 0; i < lbl_804735E8.xEF; i++) {
        /// how do i access this sanely?
        // its clearly iterating through xF1
        u8 chr = ptr[0x0D];
        if (chr != CHKIND_MAX) {
            Player_80036E20(chr, lbl_804D65F4, 1);
        }
        ptr++;
    }

    ptr = (u8*) &lbl_804735E8.xE4;
    for (i = 0; i < lbl_804735E8.xF0; i++) {
        if (ptr[0x10] == CKIND_GKOOPS) {
            ptr[0x10] = CKIND_KOOPA;
        }
        if (ptr[0x10] != CHKIND_MAX) {
            Player_80036E20(ptr[0x10], lbl_804D65F4, 1);
        }
        ptr++;
    }
}

s32 fn_80185E34(void)
{
    ClassicProcArray local;
    int i;
    int player_slot = 0;
    local = lbl_803B7C28;

    for (i = 0; i < lbl_804735E8.xEF; i++) {
        if (lbl_804735E8.xF1[i] != 0x21) {
            Player_80036CF0(player_slot);
            Player_SetPlayerCharacter(player_slot,
                                      (CharacterKind) lbl_804735E8.xF1[i]);
            Player_SetCostumeId(player_slot, (s32) lbl_804735E8.xF7[i]);
            Player_SetPlayerId(player_slot, 0);
            Player_SetSlottype(player_slot, Gm_PKind_Demo);
            Player_SetFacingDirection(player_slot, 0.0f);
            Player_SetModelScale(player_slot, 1.0f);
            Player_SetFlagsBit5(player_slot, lbl_804735E8.xFD[i]);
            Player_80036F34(player_slot, 5);
            HSD_GObj_SetupProc(
                Player_GetEntity(player_slot),
                (HSD_GObjEvent) local.v[i], 0x16);
            player_slot++;
        }
    }
    return player_slot;
}

void fn_80185F5C(s32 arg0)
{
    ClassicProcArray local;
    int i;
    int player_slot = 0;
    local = lbl_803B7C40;

    for (i = 0; i < lbl_804735E8.xF0; i++) {
        if (lbl_804735E8.xF4[i] != 0x21) {
            Player_80036CF0(player_slot);
            Player_SetPlayerCharacter(player_slot,
                                      (CharacterKind) lbl_804735E8.xF4[i]);
            Player_SetCostumeId(player_slot, (s32) lbl_804735E8.xFA[i]);
            Player_SetPlayerId(player_slot, 0);
            Player_SetSlottype(player_slot, Gm_PKind_Demo);
            Player_SetFacingDirection(player_slot, 0.0f);
            Player_SetModelScale(player_slot, 1.0f);
            Player_SetFlagsBit5(player_slot, lbl_804735E8.x100[i]);
            Player_80036F34(player_slot, 6);
            HSD_GObj_SetupProc(Player_GetEntity(player_slot),
                               (HSD_GObjEvent) local.v[i], 0x16);
            player_slot++;
        }
    }
}

void fn_80186080(void)
{
    s32 temp_r31;

    temp_r31 = HSD_SisLib_803A611C(0, NULL, 9, 0x14, 0, 0xE, 0, 0x12);
    HSD_SisLib_803A62A0(0, "SdIntro.dat", "SIS_IntroData");
    lbl_804735A8.x4[6] = (HSD_JObj*) HSD_SisLib_803A5ACC(
        0, temp_r31, 0.0f, 0.0f, 0.0f, 640.0f, 480.0f);
    if (lbl_804735E8.xE8 == 1) {
        if (lbLang_IsSavedLanguageUS()) {
            HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 5);
            return;
        }
        HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 2);
    } else if (lbl_804735E8.xE8 == 3) {
        if (lbLang_IsSavedLanguageUS()) {
            HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 6);
            return;
        }
        HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 3);
    } else if (lbl_804735E8.xE8 == 2) {
        if (lbLang_IsSavedLanguageUS()) {
            HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 7);
            return;
        }
        HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 4);
    }
}

void fn_801861B8(void)
{
    HSD_Text* text;
    s32 i;

    PAD_STACK(16);

    HSD_SisLib_803A611C(0, NULL, 9, 0x14, 0, 0xE, 0, 0x12);
    HSD_SisLib_803A62A0(0, "SdIntro.dat", "SIS_IntroData");

    for (i = 0; i < (s32) lbl_804735E8.xEF; i++) {
        lbl_804735A8.x4[7 + i] = (HSD_JObj*) HSD_SisLib_803A6754(0, 0);
        ((HSD_Text*) lbl_804735A8.x4[7 + i])->default_kerning = 1;
        text = (HSD_Text*) lbl_804735A8.x4[7 + i];
        text->font_size.x = 1.0f;
        text->font_size.y = 1.0f;
        ((HSD_Text*) lbl_804735A8.x4[7 + i])->default_alignment = 1;
        HSD_SisLib_803A6B98((HSD_Text*) lbl_804735A8.x4[7 + i],
                            lbl_804D6604->x57C[lbl_804735E8.xEF].x00[i],
                            lbl_804D6604->x57C[lbl_804735E8.xEF].x0C[i], " ");
        HSD_SisLib_803A7548((HSD_Text*) lbl_804735A8.x4[7 + i], 0,
                            lbl_804D6604->x57C[lbl_804735E8.xEF].x18[i],
                            lbl_804D6604->x57C[lbl_804735E8.xEF].x24[i]);
    }

    for (i = 0; i < (s32) lbl_804735E8.xF0; i++) {
        lbl_804735A8.x4[10 + i] = (HSD_JObj*) HSD_SisLib_803A6754(0, 0);
        ((HSD_Text*) lbl_804735A8.x4[10 + i])->default_kerning = 1;
        text = (HSD_Text*) lbl_804735A8.x4[10 + i];
        text->font_size.x = 1.0f;
        text->font_size.y = 1.0f;
        ((HSD_Text*) lbl_804735A8.x4[10 + i])->default_alignment = 1;
        if ((s32) lbl_804735E8.xE4 == 4) {
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
                                lbl_804D6604->x57C[lbl_804735E8.xF0].x00[i],
                            lbl_804D6604->x57C[lbl_804735E8.xF0].x0C[i], " ");
        HSD_SisLib_803A7548((HSD_Text*) lbl_804735A8.x4[10 + i], 0,
                            340.0f + lbl_804D6604->x57C[lbl_804735E8.xF0].x18[i],
                            lbl_804D6604->x57C[lbl_804735E8.xF0].x24[i]);
    }
}

static SceneDesc* lbl_804D65FC;

void fn_80186400(void)
{
    HSD_GObj* gobj = GObj_Create(0xE, 0xF, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(lbl_804D65FC->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObj_SetupProc(gobj, fn_80184AB8, 0);
    gm_8016895C(jobj, lbl_804D65FC->models[0], 0);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjAnimAll(jobj);
    if (lbl_804735E8.xE4 != 3) {
        lb_80011E24(jobj, &lbl_804735A8.x4[0], 4, -1);
        lb_80011E24(jobj, &lbl_804735A8.x4[1], 5, -1);
        lb_80011E24(jobj, &lbl_804735A8.x4[2], 0x3A, -1);
        lb_80011E24(jobj, &lbl_804735A8.x4[3], 0x3B, -1);
        HSD_JObjSetTranslateZ(lbl_804735A8.x4[2], 10000.0F);
        HSD_JObjSetTranslateZ(lbl_804735A8.x4[3], 10000.0F);
    }
}

static const char* const lbl_803B7C58[] = {
    "IrAls", "IrEzTarg", "IrEzTuki", "IrEzFigG"
};

static char lbl_804D40B0[] = "IrRdMap";

void fn_80186634(void* arg0)
{
    HSD_GObj* gobj;
    HSD_CObj* cobj1;
    HSD_CObj* cobj2;
    HSD_GObj* gobj2;
    HSD_GObj* gobj3;
    HSD_JObj* jobj;
    HSD_GObj* gobj4;
    const char* names[4];

    lbArchive_80016DBC("GmIntEz.dat", &lbl_804D6604,
                       "gmIntroEasyTable", 0);
    Camera_80028B9C(0xC);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8(InternalStageID_Unk00, NULL);
    Item_80266FA8();
    Item_80266FCC();
    Stage_8022524C();
    efLib_Init();
    efAsync_LoadSync(0);

    names[0] = lbl_803B7C58[0];
    names[1] = lbl_803B7C58[1];
    names[2] = lbl_803B7C58[2];
    names[3] = lbl_803B7C58[3];
    lbl_804D65F4 = lbArchive_80016DBC(
        names[lbl_804735E8.xE8],
        &lbl_804D65FC, "ScItrAllstar_scene_data", 0);
    lbl_804D65F8 = lbArchive_80016DBC(
        lbl_804D40B0, &lbl_804D6600, "ScItrAllstar_scene_data", 0);

    gobj = GObj_Create(0xB, 3, 0);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A,
                            lb_80011AC4(lbl_804D65FC->lights));
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);

    if ((s32) lbl_804735E8.xE4 != 3) {
        lbl_804735E8.xE8 = 0;
    }

    switch ((s32) lbl_804735E8.xE4) {
    case 3:
        gobj2 = GObj_Create(0x13, 0x14, 0);
        cobj1 = HSD_CObjLoadDesc(lbl_804D65FC->cameras[0].desc);
        cobj2 = HSD_CObjLoadDesc(lbl_804D6600->cameras[0].desc);
        HSD_GObjObject_80390A70(gobj2, HSD_GObj_804D784B, cobj1);
        GObj_SetupGXLinkMax(gobj2, HSD_GObj_803910D8, 8);
        gobj2->gxlink_prios = 0x801;
        gobj3 = GObj_Create(0x13, 0x15, 0);
        HSD_GObjObject_80390A70(gobj3, HSD_GObj_804D784B, cobj2);
        if ((s32) lbl_804735E8.xE4 == 4) {
            GObj_SetupGXLinkMax(gobj3, (GObj_RenderFunc) fn_8018569C, 8);
        } else {
            GObj_SetupGXLinkMax(gobj3, (GObj_RenderFunc) fn_8018575C, 8);
        }
        fn_80186400();
        gobj4 = GObj_Create(0xE, 0xF, 0);
        jobj = HSD_JObjLoadJoint(lbl_804D6600->models[0]->joint);
        HSD_GObjObject_80390A70(gobj4, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj4, HSD_GObj_JObjCallback, 0xC, 0);
        HSD_GObj_SetupProc(gobj4, (HSD_GObjEvent) fn_8018504C, 0x11);
        gm_8016895C(jobj, lbl_804D6600->models[0], 0);
        HSD_JObjReqAnimAll(jobj, (f32) ((lbl_804735E8.xEE - 1) * 0x32));
        HSD_JObjAnimAll(jobj);
        lb_80011E24(jobj, &lbl_804735A8.x4[4], 0xE, -1);
        lb_80011E24(jobj, &lbl_804735A8.x4[5], 1, -1);
        gobj = GObj_Create(0xE, 0xF, 0);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848,
                                HSD_FogLoadDesc(lbl_804D65FC->fogs[0].desc));
        GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0xB, 0);
        fn_80186080();
        break;
    default:
        gobj2 = GObj_Create(0x13, 0x14, 0);
        cobj1 = HSD_CObjLoadDesc(lbl_804D65FC->cameras[0].desc);
        cobj2 = HSD_CObjLoadDesc(lbl_804D6600->cameras[0].desc);
        HSD_GObjObject_80390A70(gobj2, HSD_GObj_804D784B, cobj1);
        GObj_SetupGXLinkMax(gobj2, HSD_GObj_803910D8, 8);
        gobj2->gxlink_prios = 0x801;
        gobj3 = GObj_Create(0x13, 0x15, 0);
        HSD_GObjObject_80390A70(gobj3, HSD_GObj_804D784B, cobj2);
        if ((s32) lbl_804735E8.xE4 == 4) {
            GObj_SetupGXLinkMax(gobj3, (GObj_RenderFunc) fn_8018569C, 8);
        } else {
            GObj_SetupGXLinkMax(gobj3, (GObj_RenderFunc) fn_8018575C, 8);
        }
        fn_80186400();
        gobj4 = GObj_Create(0xE, 0xF, 0);
        jobj = HSD_JObjLoadJoint(lbl_804D6600->models[0]->joint);
        HSD_GObjObject_80390A70(gobj4, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj4, HSD_GObj_JObjCallback, 0xC, 0);
        HSD_GObj_SetupProc(gobj4, (HSD_GObjEvent) fn_8018504C, 0x11);
        gm_8016895C(jobj, lbl_804D6600->models[0], 0);
        HSD_JObjReqAnimAll(jobj, (f32) ((lbl_804735E8.xEE - 1) * 0x32));
        HSD_JObjAnimAll(jobj);
        lb_80011E24(jobj, &lbl_804735A8.x4[4], 0xE, -1);
        lb_80011E24(jobj, &lbl_804735A8.x4[5], 1, -1);
        gobj = GObj_Create(0xE, 0xF, 0);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848,
                                HSD_FogLoadDesc(lbl_804D65FC->fogs[0].desc));
        GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0xB, 0);
        fn_801861B8();
        fn_80185D64();
        fn_80185F5C(fn_80185E34());
        break;
    case 4:
        gobj2 = GObj_Create(0x13, 0x14, 0);
        cobj1 = HSD_CObjLoadDesc(lbl_804D65FC->cameras[0].desc);
        cobj2 = HSD_CObjLoadDesc(lbl_804D6600->cameras[0].desc);
        HSD_GObjObject_80390A70(gobj2, HSD_GObj_804D784B, cobj1);
        GObj_SetupGXLinkMax(gobj2, HSD_GObj_803910D8, 8);
        gobj2->gxlink_prios = 0x801;
        gobj3 = GObj_Create(0x13, 0x15, 0);
        HSD_GObjObject_80390A70(gobj3, HSD_GObj_804D784B, cobj2);
        if ((s32) lbl_804735E8.xE4 == 4) {
            GObj_SetupGXLinkMax(gobj3, (GObj_RenderFunc) fn_8018569C, 8);
        } else {
            GObj_SetupGXLinkMax(gobj3, (GObj_RenderFunc) fn_8018575C, 8);
        }
        fn_80186400();
        gobj4 = GObj_Create(0xE, 0xF, 0);
        jobj = HSD_JObjLoadJoint(lbl_804D6600->models[0]->joint);
        HSD_GObjObject_80390A70(gobj4, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj4, HSD_GObj_JObjCallback, 0xC, 0);
        HSD_GObj_SetupProc(gobj4, (HSD_GObjEvent) fn_8018504C, 0x11);
        gm_8016895C(jobj, lbl_804D6600->models[0], 0);
        HSD_JObjReqAnimAll(jobj, (f32) ((lbl_804735E8.xEE - 1) * 0x32));
        HSD_JObjAnimAll(jobj);
        lb_80011E24(jobj, &lbl_804735A8.x4[4], 0xE, -1);
        lb_80011E24(jobj, &lbl_804735A8.x4[5], 1, -1);
        gobj = GObj_Create(0xE, 0xF, 0);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848,
                                HSD_FogLoadDesc(lbl_804D65FC->fogs[0].desc));
        GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0xB, 0);
        fn_801861B8();
        fn_80185D64();
        fn_80185A0C();
        fn_80185E34();
        break;
    }

    lbAudioAx_80023F28(0x2D);
}

void gm_80186DFC_OnFrame(void)
{
    if (lbl_804735A8.x0 != 0) {
        lbAudioAx_800236DC();
        gm_801A4B60();
    }
}

static struct enterdata {
    int x0, x4;
} lbl_804D6618;

static struct {
    int x0, x4;
    HSD_JObj* x8;
    HSD_JObj* xC;
} lbl_804736B0;

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

void gm_80186E30_OnEnter(void* arg0_)
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
    *(ClassicModeEnterData*) &lbl_804735E8.xE4 = *arg0;
    fn_80186634(arg0_);
    lbl_804D6608 = -1;
    gm_80167858((int)(s8) lbl_804735E8.xEC, lbl_804735E8.xED, 0xB, 0x2D);
    gm_80168F88();
}

void fn_80186EFC(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    PAD_STACK(8);
    HSD_JObjReqAnimAll(lbl_804736B0.xC, 0.0F);
    HSD_JObjAnimAll(jobj);
    if (lbl_804736B0.x4 < 0x8C) {
        lbl_804736B0.x4++;
    } else {
        lbl_804736B0.x0 = 1;
    }
}

static struct {
    /* 0x00 */ f32 x0;
    /* 0x04 */ f32 x4;
    /* 0x08 */ f32 x8;
    /* 0x0C */ f32 xC;
    /* 0x10 */ f32 x10;
    /* 0x14 */ f32 x14;
} lbl_803D9498[] = {
    { 0.0f, -4.5f, 0.0f, 1.0f, 1.0f, 1.0f },
    { 0.0f, 1.5f, 0.0f, 0.6f, 0.6f, 0.6f },
    { 0.0f, -5.3f, 0.0f, 1.3f, 1.3f, 1.3f },
    { 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { 0.0f, 5.5f, 0.0f, 0.75f, 0.75f, 0.75f },
    { -1.1f, -2.0f, 0.0f, 0.5f, 0.5f, 0.5f },
    { -1.0f, -3.5f, 0.0f, 1.3f, 1.3f, 1.3f },
    { -1.0f, -0.5f, 0.0f, 1.35f, 1.35f, 1.35f },
    { -1.0f, -2.0f, 0.0f, 1.4f, 1.4f, 1.4f },
    { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { 0.0f, -6.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { -1.0f, -0.5f, 0.0f, 1.1f, 1.1f, 1.1f },
    { -2.0f, -6.5f, 0.0f, 1.3f, 1.3f, 1.3f },
    { -0.5f, 2.5f, 0.0f, 1.0f, 1.0f, 1.0f },
    { -0.8f, 5.0f, 0.0f, 0.7f, 0.7f, 0.7f },
    { -1.0f, 4.0f, 0.0f, 0.8f, 0.8f, 0.8f },
    { 0.0f, -5.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { 0.0f, 2.0f, 0.0f, 0.9f, 0.9f, 0.9f },
    { -1.0f, -12.5f, 0.0f, 1.8f, 1.8f, 1.8f },
    { -3.5f, 0.0f, 0.0f, 1.8f, 1.8f, 1.8f },
    { 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { 0.0f, -2.5f, 0.0f, 1.1f, 1.1f, 1.1f },
    { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { 0.0f, 5.5f, 0.0f, 0.4f, 0.4f, 0.4f },
    { 1.0f, -11.0f, 0.0f, 1.3f, 1.3f, 1.3f },
    { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { -1.1f, 2.5f, 0.0f, 0.4f, 0.4f, 0.4f },
};

void fn_80186F6C(HSD_GObj* arg0)
{
    Vec3 pos;
    HSD_JObj* jobj = arg0->hsd_obj;
    HSD_JObj* child = lbl_804736B0.x8;
    PAD_STACK(4);

    HSD_JObjGetTranslation(child, &pos);

    pos.x -= 7.0f;
    pos.x += lbl_803D9498[lbl_804D6618.x0].x0;
    pos.y += lbl_803D9498[lbl_804D6618.x0].x4;
    pos.z += lbl_803D9498[lbl_804D6618.x0].x8;

    HSD_JObjSetTranslate(jobj, &pos);

    HSD_JObjSetScaleX(jobj, lbl_803D9498[lbl_804D6618.x0].xC);
    HSD_JObjSetScaleY(jobj, lbl_803D9498[lbl_804D6618.x0].x10);
    HSD_JObjSetScaleZ(jobj, lbl_803D9498[lbl_804D6618.x0].x14);

    {
        HSD_GObj* entity2 = Player_GetEntityAtIndex(0, 1);
        if (entity2 != NULL) {
            HSD_JObj* jobj2 = entity2->hsd_obj;

            HSD_JObjGetTranslation(jobj, &pos);
            pos.x += 3.0f;
            pos.z -= 5.0f;
            pos.y += 4.0f;
            HSD_JObjSetTranslate(jobj2, &pos);

            HSD_JObjGetScale(jobj, &pos);
            HSD_JObjSetScale(jobj2, &pos);
        }
    }
}

extern HSD_Archive* lbl_804D6610;

#pragma push
#pragma dont_inline on
HSD_GObjProc* fn_801873F0(void)
{
    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();
    Player_80036E20(lbl_804D6618.x0, lbl_804D6610, 1);
    Player_SetPlayerCharacter(0, lbl_804D6618.x0);
    Player_SetCostumeId(0, lbl_804D6618.x4);
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, Gm_PKind_Demo);
    Player_SetFacingDirection(0, 0.0f);
    Player_SetModelScale(0, 1.0f);
    Player_80036F34(0, 6);
    return HSD_GObj_SetupProc(Player_GetEntity(0), fn_80186F6C, 0x16U);
}
#pragma pop

void fn_80187494(HSD_GObj* gobj, int arg1)
{
    int temp_ret = HSD_CObjSetCurrent(gobj->hsd_obj);
    PAD_STACK(4);
    if (temp_ret != 0) {
        Camera_800313E0(gobj, 1);
        gobj->gxlink_prios = 0x801;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

static SceneDesc* lbl_804D6614;

void fn_801874FC(void)
{
    HSD_JObj* sp8;
    HSD_GObj* gobj;
    HSD_JObj* jobj;

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(lbl_804D6614->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObj_SetupProc(gobj, fn_80186EFC, 0);
    gm_8016895C(jobj, lbl_804D6614->models[0], 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    lb_80011E24(jobj, &sp8, 0x3A, -1);
    HSD_JObjSetTranslateZ(sp8, 10000.0F);
    lb_80011E24(jobj, &sp8, 0x3B, -1);
    HSD_JObjSetTranslateZ(sp8, 10000.0F);
    lb_80011E24(jobj, &lbl_804736B0.x8, 5, -1);
    lb_80011E24(jobj, &lbl_804736B0.xC, 6, -1);
}

/// #fn_801874FC

#pragma push
#pragma dont_inline on
void fn_80187714(void)
{
    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(64);
    Stage_802251E8(0, NULL);
    Stage_8022524C();
    Item_80266FA8();
    Item_80266FCC();
    efLib_Init();
    efAsync_LoadSync(0);
}
#pragma pop

extern HSD_Archive* lbl_804D6610;

void gm_8018776C_OnFrame(void)
{
    if (lbl_804736B0.x0 != 0) {
        lbArchive_80016EFC(lbl_804D6610);
        lbAudioAx_800236DC();
        gm_801A4B60();
    }
}

#pragma push
#pragma dont_inline on
void gm_801877A8_OnEnter(void* arg0_)
{
    struct enterdata* arg0 = arg0_;
    HSD_GObj* temp_r30;
    HSD_GObj* temp_r30_2;
    HSD_GObj* temp_r30_3;
    HSD_LObj* lobj;
    HSD_CObj* cobj;
    HSD_Fog* fog;
    PAD_STACK(8);

    lbl_804736B0.x0 = 0;
    lbl_804736B0.x4 = 0;

    lbl_804D6618 = *arg0;
    fn_80187714();
    lbl_804D6610 = lbArchive_80016DBC("IrAls", &lbl_804D6614,
                                      "ScItrAllstar_scene_data", 0);

    temp_r30 = GObj_Create(0x13, 0x14, 0);
    cobj = HSD_CObjLoadDesc(lbl_804D6614->cameras[0].desc);
    HSD_GObjObject_80390A70(temp_r30, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(temp_r30, fn_80187494, 8);
    temp_r30->gxlink_prios = 0x801;

    temp_r30_2 = GObj_Create(0xB, 3, 0);
    lobj = lb_80011AC4(lbl_804D6614->lights);
    HSD_GObjObject_80390A70(temp_r30_2, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(temp_r30_2, HSD_GObj_LObjCallback, 0, 0);
    fn_801874FC();

    temp_r30_3 = GObj_Create(0xE, 0xF, 0);
    fog = HSD_FogLoadDesc(lbl_804D6614->fogs[0].desc);
    HSD_GObjObject_80390A70(temp_r30_3, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(temp_r30_3, HSD_GObj_FogCallback, 0xB, 0);
    fn_801873F0();
    lbAudioAx_80023F28(0x2D);
}
#pragma pop

static struct {
    DynamicModelDesc*** x0;
    HSD_CameraAnim** x4;
    HSD_GObj* x8;
    u8 pad_C[0x28];
    u16 x34;
    struct {
        u8 stage_index : 5;
        u8 done : 1;
        u8 flash : 1;
        u8 active : 1;
    } x36;
    struct {
        u8 frame_counter : 4;
        u8 anim_state : 2;
        u8 state2 : 2;
    } x37;
    u8 x38;
} lbl_804736C0;

void fn_80187910(HSD_GObj* arg0)
{
    Vec3 sp10;
    HSD_CObj* cobj;
    s32 frame;
    f32 scale;

    PAD_STACK(8);
    cobj = arg0->hsd_obj;
    if (gm_801A36A0(lbl_804736C0.x38) & 0x100) {
        lbl_804736C0.x37.frame_counter =
            (s32) cobj->eyepos->aobj->curr_frame / 300;
        lbl_804736C0.x37.frame_counter++;
        if (lbl_804736C0.x37.frame_counter >= 8U) {
            lbl_804736C0.x37.frame_counter = 0;
        }
        frame = lbl_804736C0.x37.frame_counter * 0x12C;
        HSD_CObjRemoveAnim(cobj);
        HSD_CObjAddAnim(cobj, *(HSD_CameraAnim**) lbl_804736C0.x4[1]);
        HSD_CObjReqAnim(cobj, (f32) frame);
    }
    HSD_CObjAnim(cobj);
    HSD_CObjGetInterest(cobj, &sp10);
    scale = Ground_801C0498();
    sp10.x *= scale;
    sp10.y *= scale;
    sp10.z *= scale;
    HSD_CObjSetInterest(cobj, &sp10);
    HSD_CObjGetEyePosition(cobj, &sp10);
    scale = Ground_801C0498();
    sp10.x *= scale;
    sp10.y *= scale;
    sp10.z *= scale;
    HSD_CObjSetEyePosition(cobj, &sp10);
}

typedef struct {
    u8 pad_hi : 4;
    u8 state : 2;
    u8 pad_lo : 2;
} x37_state_bits;

typedef struct {
    u8 b7 : 1, b6 : 1, b5 : 1, b4 : 1, b3 : 1, b2 : 1, b1 : 1, b0 : 1;
} u8_bits;

void fn_80187AB4(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    int state = lbl_804736C0.x37.anim_state;
    DynamicModelDesc* desc;
    int anim_state;

    switch (state) {
    case 0:
        if (lb_8000B09C(jobj) == 0) {
            lbl_804736C0.x37.anim_state = 1;
            desc = (*lbl_804736C0.x0)[11 - lbl_804736C0.x36.stage_index];
            if (desc->anims != NULL) {
                anim_state = lbl_804736C0.x37.anim_state;
                if (desc->anims[anim_state] != NULL) {
                    lb_8000C0E8(jobj, anim_state, desc);
                    HSD_JObjReqAnimAll(jobj, 0.0f);
                    HSD_JObjAnimAll(jobj);
                }
            }
            lbl_804736C0.x34 = 0x960;
        }
        break;
    case 1:
        if ((u32) lbl_804736C0.x36.active == 1U) {
            lbl_804736C0.x36.flash = 1;
        }
        if (lbl_804736C0.x36.flash) {
            lbl_804736C0.x37.anim_state = 2;
            lbl_804736C0.x36.done = 1;
            lbBgFlash_8002063C(1);
        }
        if (lb_8000B09C(jobj) == 0) {
            desc = (*lbl_804736C0.x0)[11 - lbl_804736C0.x36.stage_index];
            if (desc->anims != NULL) {
                anim_state = lbl_804736C0.x37.anim_state;
                if (desc->anims[anim_state] != NULL) {
                    lb_8000C0E8(jobj, anim_state, desc);
                    HSD_JObjReqAnimAll(jobj, 0.0f);
                    HSD_JObjAnimAll(jobj);
                }
            }
        }
        break;
    case 2:
        if (lb_8000B09C(jobj) == 0) {
            lbl_804736C0.x36.done = 1;
            HSD_GObjPLink_80390228(gobj);
        }
        break;
    }
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void fn_80187C9C(HSD_GObj* gobj, int arg1)
{
    GXSetZMode(0, GX_NEVER, 0);
    HSD_GObj_JObjCallback(gobj, arg1);
    HSD_StateInvalidate(0x40);
}

void fn_80187CF4(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    int state = lbl_804736C0.x37.state2;
    DynamicModelDesc* desc;
    int anim_state;

    switch (state) {
    case 0:
        if (lb_8000B09C(jobj) == 0) {
            lbl_804736C0.x37.state2 = 1;
            anim_state = lbl_804736C0.x37.state2;
            desc = (*lbl_804736C0.x0)[12];
            if (desc->anims[anim_state] != NULL) {
                lb_8000C0E8(jobj, anim_state, desc);
                HSD_JObjReqAnimAll(jobj, 0.0f);
                HSD_JObjAnimAll(jobj);
            }
        }
        break;
    case 1:
        if (lb_8000B09C(jobj) == 0) {
            lbl_804736C0.x37.state2 = 2;
            anim_state = lbl_804736C0.x37.state2;
            desc = (*lbl_804736C0.x0)[12];
            if (desc->anims[anim_state] != NULL) {
                lb_8000C0E8(jobj, anim_state, desc);
                HSD_JObjReqAnimAll(jobj, 0.0f);
                HSD_JObjAnimAll(jobj);
            }
        }
        break;
    case 2:
        if (gm_801A36A0(lbl_804736C0.x38) & 0x1000) {
            lbAudioAx_80024030(1);
            lbl_804736C0.x36.active = 1;
            lbl_804736C0.x37.state2 = 3;
            anim_state = lbl_804736C0.x37.state2;
            desc = (*lbl_804736C0.x0)[12];
            if (desc->anims[anim_state] != NULL) {
                lb_8000C0E8(jobj, anim_state, desc);
                HSD_JObjReqAnimAll(jobj, 0.0f);
                HSD_JObjAnimAll(jobj);
            }
        } else if (lb_8000B09C(jobj) == 0) {
            anim_state = lbl_804736C0.x37.state2;
            desc = (*lbl_804736C0.x0)[12];
            if (desc->anims[anim_state] != NULL) {
                lb_8000C0E8(jobj, anim_state, desc);
                HSD_JObjReqAnimAll(jobj, 0.0f);
                HSD_JObjAnimAll(jobj);
            }
        }
        break;
    case 3:
        if (lb_8000B09C(jobj) == 0) {
            HSD_GObjPLink_80390228(gobj);
        }
        break;
    }
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

static char lbl_804D4138[] = "IrNml";

static char* lbl_803D9750[] = {
    "mc01", "mc02", "mc03", "mc04", "mc05", "mc06",
    "mc07", "mc08", "mc09", "mc10", "mc11", "mc12",
    (char*) 0x1C, (char*) 0x1C, (char*) 0x1C, (char*) 0x1C,
    (char*) 0x1C, (char*) 0x1C, (char*) 0x1C, (char*) 0x1C,
    (char*) 0x1C, (char*) 0x14, (char*) 0x14, (char*) 0x1C,
    (char*) 0x20000,    (char*) 0x10000000, (char*) 0x20,       (char*) 0x100,
    (char*) 0x20000,    (char*) 0x10000,    (char*) 0x100,      (char*) 0x04000000,
    (char*) 0x802,      (char*) 0x4000,     (char*) 8,          (char*) 0xC00,
    (char*) 0x10000,    (char*) 0x01000000, (char*) 0x20000,    (char*) 0x40,
    (char*) 0x80,       (char*) 0x200000,   NULL,               (char*) 0x2000,
    NULL,               (char*) 0x60000,    (char*) 0x200000,   (char*) 0x9000,
    (char*) 0x53634974, (char*) 0x724E6F72, (char*) 0x6D616C5F, (char*) 0x7363656E,
    (char*) 0x655F6461, (char*) 0x74610000,
};

static HSD_Archive* lbl_804D6620;

void gm_80187F48_OnEnter(void* arg0_)
{
    u8* arg0 = arg0_;
    u8 stage_index;
    HSD_GObj* cam_gobj;
    HSD_CObj* cobj;
    HSD_GObj* gobj2;
    HSD_GObj* gobj3;
    HSD_GObj* gobj4;
    HSD_GObj* gobj5;
    HSD_JObj* jobj;
    HSD_JObj* jobj2;
    DynamicModelDesc* desc;
    int anim_idx;

    lbl_804736C0.x38 = arg0[0];
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8(*(u16*) (arg0 + 2), NULL);
    Item_80266F70();
    Item_80266FCC();
    efLib_Init();
    efAsync_LoadSync(0);
    efAsync_LoadSync(0x1F);
    Stage_8022524C();
    Player_InitAllPlayers();
    lbBgFlash_800209F4();

    lbl_804736C0.x37.anim_state = 0;
    lbl_804736C0.x37.frame_counter = 0;
    lbl_804736C0.x34 = 0;
    lbl_804736C0.x36.done = 0;
    lbl_804736C0.x36.flash = 0;
    lbl_804736C0.x36.stage_index = arg0[1];
    lbl_804736C0.x37.state2 = 0;
    lbl_804736C0.x36.active = 0;

    stage_index = arg0[1];
    lbl_804D6620 = lbArchive_80016DBC(
        lbl_804D4138, &lbl_804736C0.x0,
        (char*) &lbl_803D9750[48],
        &lbl_804736C0.x4, lbl_803D9750[stage_index], NULL);

    lbAudioAx_80026F2C((s32) lbl_803D9750[stage_index + 12]);
    {
        u64 ret = lbAudioAx_80026E84(Player_GetPlayerCharacter(0));
        lbAudioAx_8002702C((s32) lbl_803D9750[stage_index + 12],
                           ret | *(u64*) &lbl_803D9750[stage_index * 2 + 24]);
    }
    lbAudioAx_80027168();
    lbAudioAx_80027648();

    cam_gobj = GObj_Create(0x13, 0x14, 0);
    lbl_804736C0.x8 = cam_gobj;
    cobj = HSD_CObjLoadDesc((HSD_CObjDesc*) *lbl_804736C0.x4);
    HSD_GObjObject_80390A70(cam_gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(cam_gobj, (void*) Camera_800304E0, 8);
    HSD_GObj_SetupProc(cam_gobj, fn_80187910, 0);
    HSD_CObjAddAnim(cobj, *(HSD_CameraAnim**) lbl_804736C0.x4[1]);
    HSD_CObjReqAnim(cobj, 0.0f);

    gobj2 = GObj_Create(0x13, 0x14, 0);
    HSD_GObjObject_80390A70(gobj2, HSD_GObj_804D784B,
        HSD_CObjLoadDesc(((SceneDesc*) lbl_804736C0.x0)->cameras[0].desc));
    GObj_SetupGXLinkMax(gobj2, HSD_GObj_803910D8, 8);
    gobj2->gxlink_prios = 0xC00;

    gobj3 = GObj_Create(0xB, 3, 0);
    HSD_GObjObject_80390A70(gobj3, HSD_GObj_804D784A,
        lb_80011AC4(((SceneDesc*) lbl_804736C0.x0)->lights));
    GObj_SetupGXLink(gobj3, HSD_GObj_LObjCallback, 0xA, 0);

    gobj4 = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(
        (*lbl_804736C0.x0)[11 - lbl_804736C0.x36.stage_index]->joint);
    lb_80011C18(jobj, 0x08000000);
    HSD_GObjObject_80390A70(gobj4, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj4, fn_80187C9C, 0xB, 0xB);

    desc = (*lbl_804736C0.x0)[11 - lbl_804736C0.x36.stage_index];
    if (desc->anims != NULL) {
        anim_idx = lbl_804736C0.x37.anim_state;
        if (desc->anims[anim_idx] != NULL) {
            lb_8000C0E8(jobj, anim_idx, desc);
            HSD_JObjReqAnimAll(jobj, 0.0f);
            HSD_JObjAnimAll(jobj);
        }
    }
    HSD_GObj_SetupProc(gobj4, fn_80187AB4, 0);

    gobj5 = GObj_Create(0xE, 0xF, 0);
    jobj2 = HSD_JObjLoadJoint((*lbl_804736C0.x0)[12]->joint);
    lb_80011C18(jobj2, 0x08000000);
    HSD_GObjObject_80390A70(gobj5, HSD_GObj_804D7849, jobj2);
    GObj_SetupGXLink(gobj5, fn_80187C9C, 0xB, 0xB);

    anim_idx = lbl_804736C0.x37.state2;
    desc = (*lbl_804736C0.x0)[12];
    if (desc->anims[anim_idx] != NULL) {
        lb_8000C0E8(jobj2, anim_idx, desc);
        HSD_JObjReqAnimAll(jobj2, 0.0f);
        HSD_JObjAnimAll(jobj2);
    }

    HSD_JObjReqAnimAll(jobj2, 0.0f);
    HSD_JObjAnimAll(jobj2);
    HSD_GObj_SetupProc(gobj5, fn_80187CF4, 0);
    lbAudioAx_80023F28(0x2E);
}

void gm_80188364_OnLeave(void* arg0)
{
    HSD_Archive** var = &lbl_804D6620;
    lbArchive_80016EFC(*var);
}

void gm_8018838C_OnFrame(void)
{
    if (lbl_804736C0.x36.done) {
        gm_801A4B60();
    }
}

extern f32 lbl_804DA5E8;

f32 gm_801883C0(void)
{
    HSD_GObj* gobj;
    HSD_CObj* cobj;
    HSD_AObj* aobj;

    gobj = lbl_804736C0.x8;
    if (gobj == NULL) {
        goto return_default;
    }

    cobj = gobj->hsd_obj;
    goto check_cobj;

return_default:
    return lbl_804DA5E8;

check_cobj:
    aobj = cobj->eyepos->aobj;
    if (aobj != NULL) {
        return aobj->curr_frame;
    }

    aobj = cobj->interest->aobj;
    if (aobj != NULL) {
        return aobj->curr_frame;
    }

    return lbl_804DA5E8;
}

bool gm_8018841C(void)
{
    if (gm_801A4310() == MJ_TRAINING) {
        return true;
    }
    return false;
}

static TrainingModeState lbl_80473700;

int gm_80188454(int idx)
{
    return lbl_80473700.char_data[idx];
}

int fn_8018846C(void)
{
    int result;
    int* ptr = (int*) &lbl_80473700;
    int* p;

    result = pl_8004134C(0);
    p = ptr + Player_GetPlayerCharacter(0) + 2;
    if (*p < result) {
        *p = result;
    }
    if (result != 0) {
        ptr[67] = result;
        ptr[68] = 1;
    }
    if (ptr[68] != 0) {
        return ptr[67];
    }
    return result;
}

inline int fn_801884F8_inline(void)
{
    int result;

    result = pl_80041300(0);
    if (result != 0) {
        lbl_80473700.result_cache[0] = result;
        lbl_80473700.result_cache[1] = 1;
    }
    if (lbl_80473700.result_cache[1] != 0) {
        result = lbl_80473700.result_cache[0];
    }
    return result;
}

#pragma push
#pragma dont_inline on
int fn_801884F8(void)
{
    int result;

    result = pl_80041300(0);
    if (result != 0) {
        lbl_80473700.result_cache[0] = result;
        lbl_80473700.result_cache[1] = 1;
    }
    if (lbl_80473700.result_cache[1] != 0) {
        result = lbl_80473700.result_cache[0];
    }
    return result;
}
#pragma pop
void fn_80188550(int arg0)
{
    int current = lbl_80473700.count;

    if (arg0 != current) {
        if (arg0 > lbl_80473700.count) {
            int i = 0;
            int skip = lbl_80473700.count;
            int remaining = arg0 - current;

            for (i = 0; i < 4; i++) {
                if (i != 0) {
                    if (skip == 0) {
                        if (i != 0) {
                            lbl_80473700.players[i].slot_type = 1;
                        } else {
                            lbl_80473700.players[i].slot_type = 0;
                        }
                        gm_8016EDDC(i, &lbl_80473700.players[i]);
                        if (--remaining == 0) {
                            break;
                        }
                    } else {
                        skip--;
                    }
                }
            }
        } else {
            int to_remove = current - arg0;
            int j;
            for (j = 3; j >= 0; j--) {
                if (j != 0 && to_remove != 0) {
                    if (current != 3) {
                        fn_8016EF98(to_remove + 1);
                    } else {
                        fn_8016EF98(j);
                    }
                    if (--to_remove == 0) {
                        break;
                    }
                }
            }
        }
        lbl_80473700.count = arg0;
    }
}

void fn_80188644()
{
    int i;
    Vec3 sp10;
    int saved_count;

    PAD_STACK(8);

    saved_count = lbl_80473700.count;
    lbl_80473700.count = 1;
    Player_SetFacingDirection(0, 1.0f);
    Player_SetHUDDamage(0, 0);
    Stage_80224E64(0, &sp10);
    Player_800328D4(0, &sp10);
    ifStatus_802F6508(0);

    i = 0;
    do {
        if (i != 0 && i <= saved_count) {
            fn_8016EF98(i);
            if (i == 1) {
                if (i != 0) {
                    lbl_80473700.players[i].slot_type = 1;
                } else {
                    lbl_80473700.players[i].slot_type = 0;
                }
                gm_8016EDDC(i, &lbl_80473700.players[i]);
            }
        }
        i++;
    } while (i < 4);

    lbl_80473700.css.menu_values[0] = 0;
    lbl_80473700.css.menu_values[1] = 0;
    lbl_80473700.css.menu_values[2] = 0;
    lbl_80473700.css.menu_values[3] = 0;
    saved_count = 0;
    lbl_80473700.css.menu_values[4] = saved_count;
    lbl_80473700.css.menu_values[5] = saved_count;
    lbl_80473700.css.menu_values[6] = saved_count;
    lbl_80473700.css.menu_values[saved_count] = 2;
}

void fn_80188738(HSD_JObj* arg0)
{
    HSD_JObj* jobjs[3];
    int i;
    int val;

    if (pl_800412D0(0) > 999) {
        val = 999;
    } else {
        val = pl_800412D0(0);
    }

    jobjs[2] = arg0;
    jobjs[1] = (jobjs[2] == NULL) ? NULL : jobjs[2]->next;
    jobjs[0] = (jobjs[1] == NULL) ? NULL : jobjs[1]->next;

    if ((val / 100) != 0) {
        HSD_JObjReqAnimAll(jobjs[0], (f32) (val / 100));
    } else {
        HSD_JObjReqAnimAll(jobjs[0], 10.0f);
    }

    if ((val / 10) != 0) {
        HSD_JObjReqAnimAll(jobjs[1], (f32) ((val % 100) / 10));
    } else {
        HSD_JObjReqAnimAll(jobjs[1], 10.0f);
    }

    HSD_JObjReqAnimAll(jobjs[2], (f32) (val % 10));

    for (i = 0; i < 3; i++) {
        HSD_JObjAnimAll(jobjs[i]);
    }
}

int fn_8018846C_noInline(void);
int fn_8018846C_noInline()
{
    return fn_8018846C();
}

void fn_80188910(HSD_JObj* arg0)
{
    HSD_JObj* jobjs[3];
    int i;
    int val;

    if (fn_8018846C() > 999) {
        val = 999;
    } else {
        val = fn_8018846C_noInline();
    }

    jobjs[2] = arg0;
    jobjs[1] = (jobjs[2] == NULL) ? NULL : jobjs[2]->next;
    jobjs[0] = (jobjs[1] == NULL) ? NULL : jobjs[1]->next;

    if ((val / 100) != 0) {
        HSD_JObjReqAnimAll(jobjs[0], (f32) (val / 100));
    } else {
        HSD_JObjReqAnimAll(jobjs[0], 10.0f);
    }
    if ((val / 10) != 0) {
        HSD_JObjReqAnimAll(jobjs[1], (f32) ((val % 100) / 10));
    } else {
        HSD_JObjReqAnimAll(jobjs[1], 10.0f);
    }
    HSD_JObjReqAnimAll(jobjs[2], (f32) (val % 10));

    for (i = 0; i < 3; i++) {
        HSD_JObjAnimAll(jobjs[i]);
    }
}

void fn_80188B3C(HSD_JObj* arg0)
{
    HSD_JObj* jobjs[3];
    int i;
    int val;

    if (fn_801884F8_inline() > 999) {
        val = 999;
    } else {
        val = fn_801884F8();
    }

    jobjs[2] = arg0;
    jobjs[1] = (jobjs[2] == NULL) ? NULL : jobjs[2]->next;
    jobjs[0] = (jobjs[1] == NULL) ? NULL : jobjs[1]->next;

    if ((val / 100) != 0) {
        HSD_JObjReqAnimAll(jobjs[0], (f32) (val / 100));
    } else {
        HSD_JObjReqAnimAll(jobjs[0], 10.0f);
    }
    if ((val / 10) != 0) {
        HSD_JObjReqAnimAll(jobjs[1], (f32) ((val % 100) / 10));
    } else {
        HSD_JObjReqAnimAll(jobjs[1], 10.0f);
    }
    HSD_JObjReqAnimAll(jobjs[2], (f32) (val % 10));

    for (i = 0; i < 3; i++) {
        HSD_JObjAnimAll(jobjs[i]);
    }
}

void fn_80188D3C(HSD_JObj* arg0)
{
    HSD_JObj* jobjs[3];
    int i;
    int val;
    int hundreds;

    val = gm_80473814.x144[0x19];

    jobjs[2] = (arg0 == NULL) ? NULL : arg0->child;
    jobjs[1] = (jobjs[2] == NULL) ? NULL : jobjs[2]->next;
    jobjs[0] = (jobjs[1] == NULL) ? NULL : jobjs[1]->next;

    hundreds = val / 100;
    if (hundreds != 0) {
        HSD_JObjReqAnimAll(jobjs[0], (f32) hundreds);
    } else {
        HSD_JObjReqAnimAll(jobjs[0], 10.0f);
    }

    if ((val / 10) != 0) {
        HSD_JObjReqAnimAll(jobjs[1], (f32) ((val - (hundreds * 100)) / 10));
    } else {
        HSD_JObjReqAnimAll(jobjs[1], 10.0f);
    }

    HSD_JObjReqAnimAll(jobjs[2], (f32) (val % 10));

    for (i = 0; i < 3; i++) {
        HSD_JObjAnimAll(jobjs[i]);
    }
}

void fn_80188EE8(HSD_GObj* gobj)
{
    CssSubStruct* sub = &lbl_80473700.css;
    HSD_JObj* jobj;
    s32 val;

    PAD_STACK(16);

    if (gm_801A45E8(2) != 0) {
        HSD_SisLib_803A6368(sub->text, 0x1E);
        HSD_JObjSetFlagsAll(sub->jobjs[3], 0x10);
    } else {
        HSD_JObjClearFlagsAll(sub->jobjs[3], 0x10);
    }

    {
        u32 counter = sub->anim_frames[22];
        if (counter < 10 || (counter >= 20 && counter < 30)) {
            sub->anim_frames[22] = counter + 1;
            sub->anim_frames[1] = sub->anim_frames[22];
        }
    }

    HSD_JObjReqAnimAll(sub->jobjs[22], (f32) sub->anim_frames[22]);
    HSD_JObjAnimAll(sub->jobjs[22]);
    HSD_JObjReqAnimAll(sub->jobjs[1], (f32) sub->anim_frames[1]);
    HSD_JObjAnimAll(sub->jobjs[1]);

    sub->text->pos_x =
        (12.0f * (9.798828f + HSD_JObjGetTranslationX(sub->jobjs[1]))) + 50.0f;
    sub->text->pos_y = 150.0f;

    fn_80188738(sub->jobjs[9]);
    fn_80188910(sub->jobjs[5]);
    fn_80188B3C(sub->jobjs[19]);

    jobj = sub->jobjs[12];
    HSD_JObjReqAnimAll(jobj, (f32) sub->x03);
    HSD_JObjAnimAll(jobj);

    jobj = sub->jobjs[13];
    HSD_JObjReqAnimAll(jobj, (f32) sub->menu_values[0]);
    HSD_JObjAnimAll(jobj);

    jobj = sub->jobjs[23];
    HSD_JObjReqAnimAll(jobj, (f32) sub->x00);
    HSD_JObjAnimAll(jobj);

    jobj = sub->jobjs[34];
    HSD_JObjReqAnimAll(jobj, (f32) sub->menu_values[0]);
    HSD_JObjAnimAll(jobj);

    val = sub->menu_values[1];
    if (lbLang_IsSettingUS() != 0 && val == 0x13) {
        HSD_SisLib_803A6368(sub->text, 0x17);
    } else {
        HSD_SisLib_803A6368(sub->text,
                            (s32) * (s16*) &lbl_803D9828[val * 4 + 2]);
    }

    jobj = sub->jobjs[32];
    HSD_JObjReqAnimAll(jobj, (f32) (sub->menu_values[2] + 1));
    HSD_JObjAnimAll(jobj);

    jobj = sub->jobjs[31];
    HSD_JObjReqAnimAll(jobj, (f32) sub->menu_values[3]);
    HSD_JObjAnimAll(jobj);

    fn_80188D3C(sub->jobjs[27]);

    HSD_JObjSetFlags(sub->jobjs[25], 0x10);

    val = sub->menu_values[6];
    jobj = sub->jobjs[26];
    if (val == 2 && lbl_80473700.mode == 3) {
        val = 3;
    }
    HSD_JObjReqAnimAll(jobj, (f32) val);
    HSD_JObjAnimAll(jobj);
}

#pragma dont_inline on
void fn_801891F4(void)
{
    CssSubStruct* sub = &lbl_80473700.css;
    u64 buttons;
    int i;
    int count;

    buttons = gm_801A36C0((u8) lbl_80473700.mode);

    if (gm_801A45E8(2) != 0) {
        if (sub->x01 == 0) {
            fn_801651FC(0, 0);
            count = lbl_80473700.count;
            sub->x03 = 0;
            for (i = 0; i < 4; i++) {
                if (i != 0 && count != 0) {
                    Player_SetPlayerAndEntityCpuType(i, 0);
                    count--;
                    if (count == 0) break;
                }
            }
            sub->anim_frames[22] = 0;
        }
        sub->x01 = 1;

        if (buttons & 0x1000000000ULL) {
            lbAudioAx_80024030(2);
            if ((u8) sub->x00 != 0) {
                sub->x00--;
                if (sub->x00 == 5) {
                    sub->x00 = 4;
                }
            } else {
                sub->x00 = 8;
            }
        }

        if (buttons & 0x2000000000ULL) {
            lbAudioAx_80024030(2);
            if ((u8) sub->x00 < 8) {
                sub->x00++;
                if (sub->x00 == 5) {
                    sub->x00 = 6;
                }
            } else {
                sub->x00 = 0;
            }
        }

        switch (sub->x00) {
        case 0:
            if (buttons & 0x4000000000ULL) {
                lbAudioAx_80024030(2);
                if (sub->menu_values[sub->x00] != 0) {
                    sub->menu_values[sub->x00]--;
                    return;
                }
                sub->menu_values[sub->x00] = 5;
                return;
            }
            if (buttons & 0x8000000000ULL) {
                lbAudioAx_80024030(2);
                if ((u32) sub->menu_values[sub->x00] < 5) {
                    sub->menu_values[sub->x00]++;
                    return;
                }
                sub->menu_values[sub->x00] = 0;
                return;
            }
            break;
        case 1:
            if (buttons & 0x4000000000ULL) {
                lbAudioAx_80024030(2);
                if (sub->menu_values[sub->x00] != 0) {
                    sub->menu_values[sub->x00]--;
                } else {
                    sub->menu_values[sub->x00] = 0x1D;
                }
            } else if (buttons & 0x8000000000ULL) {
                lbAudioAx_80024030(2);
                if ((u32) sub->menu_values[sub->x00] < 0x1D) {
                    sub->menu_values[sub->x00]++;
                } else {
                    sub->menu_values[sub->x00] = 0;
                }
            }
            if (buttons & 0x100ULL) {
                Vec3 pos;
                s16 item;
                HSD_JObj* jobj;
                lbAudioAx_80024030(8);
                item = *(s16*) &((s32*) lbl_803D9828)[sub->menu_values[1]];
                jobj = Player_GetEntity(0)->hsd_obj;
                HSD_ASSERT(979, jobj);
                pos = jobj->translate;
                pos.y += 10.0f;
                it_8026D258(&pos, (ItemKind) item);
                return;
            }
            break;
        case 2:
            if (buttons & 0x4000000000ULL) {
                lbAudioAx_80024030(2);
                if (sub->menu_values[sub->x00] != 0) {
                    sub->menu_values[sub->x00]--;
                    return;
                }
                sub->menu_values[sub->x00] = 2;
                return;
            }
            if (buttons & 0x8000000000ULL) {
                lbAudioAx_80024030(2);
                if ((u32) sub->menu_values[sub->x00] < 2) {
                    sub->menu_values[sub->x00]++;
                    return;
                }
                sub->menu_values[sub->x00] = 0;
                return;
            }
            break;
        case 3:
            if (buttons & 0x4000000000ULL) {
                lbAudioAx_80024030(2);
                if (sub->menu_values[sub->x00] != 0) {
                    sub->menu_values[sub->x00]--;
                    return;
                }
                sub->menu_values[sub->x00] = 5;
                return;
            }
            if (buttons & 0x8000000000ULL) {
                lbAudioAx_80024030(2);
                if ((u32) sub->menu_values[sub->x00] < 5) {
                    sub->menu_values[sub->x00]++;
                    return;
                }
                sub->menu_values[sub->x00] = 0;
                return;
            }
            break;
        case 4:
            if (buttons & 0x4000000000ULL) {
                lbAudioAx_80024030(2);
                if (sub->menu_values[sub->x00] != 0) {
                    sub->menu_values[sub->x00]--;
                    if (sub->menu_values[sub->x00] == 0) {
                        gm_801A36E0(0, 0x19);
                        return;
                    }
                } else {
                    sub->menu_values[sub->x00] = 0x3E7;
                    return;
                }
            } else if (buttons & 0x8000000000ULL) {
                lbAudioAx_80024030(2);
                if ((u32) sub->menu_values[sub->x00] < 0x3E7) {
                    sub->menu_values[sub->x00]++;
                    if (sub->menu_values[sub->x00] == 0x3E7) {
                        gm_801A36E0(0, 0x19);
                        return;
                    }
                } else {
                    sub->menu_values[sub->x00] = 0;
                    return;
                }
            }
            break;
        case 5:
            if (buttons & 0x4000000000ULL) {
                lbAudioAx_80024030(2);
                sub->menu_values[sub->x00] = 0;
                return;
            }
            if (buttons & 0x8000000000ULL) {
                lbAudioAx_80024030(2);
                sub->menu_values[sub->x00] = 1;
                return;
            }
            break;
        case 6:
            if (buttons & 0x4000000000ULL) {
                lbAudioAx_80024030(2);
                if (sub->menu_values[sub->x00] != 0) {
                    sub->menu_values[sub->x00]--;
                } else {
                    sub->menu_values[sub->x00] = 2;
                }
                switch (sub->menu_values[sub->x00]) {
                case 0:
                    fn_801650E8();
                    return;
                case 1:
                    fn_80165190(0, 5);
                    return;
                case 2:
                    if (lbl_80473700.mode == 3) {
                        fn_801652B0(0, 0);
                        return;
                    }
                    fn_801652B0(0, 3);
                    return;
                }
            } else if (buttons & 0x8000000000ULL) {
                lbAudioAx_80024030(2);
                if ((u32) sub->menu_values[sub->x00] < 2) {
                    sub->menu_values[sub->x00]++;
                } else {
                    sub->menu_values[sub->x00] = 0;
                }
                switch (sub->menu_values[sub->x00]) {
                case 0:
                    fn_801650E8();
                    return;
                case 1:
                    fn_80165190(0, 5);
                    return;
                case 2:
                    if (lbl_80473700.mode == 3) {
                        fn_801652B0(0, 0);
                        return;
                    }
                    fn_801652B0(0, 3);
                    return;
                }
            }
            break;
        case 7:
            if (buttons & 0x100ULL) {
                lbAudioAx_80024030(1);
                fn_80188644();
                return;
            }
            break;
        case 8:
            if (buttons & 0x100ULL) {
                gm_8016B328();
                return;
            }
            break;
        }
    } else {
        if (sub->x01 == 1) {
            ClassicProcArray speeds;
            int cpu_type;
            int damage;
            PAD_STACK(40);

            speeds = *(ClassicProcArray*) lbl_803B7C68;

            lbAudioAx_80024030(0);
            sub->anim_frames[22] = 0x14;
            lb_80019880(__cvt_dbl_usll(
                (f64) (0.016666668f / ((f32*) speeds.v)[sub->menu_values[0]] *
                       (f32) (*(u32*) 0x800000F8 >> 2))));

            fn_80188550(sub->menu_values[2] + 1);

            cpu_type = sub->menu_values[3];
            count = lbl_80473700.count;
            sub->x03 = (u8) cpu_type;
            for (i = 0; i < 4; i++) {
                if (i != 0 && count != 0) {
                    Player_SetPlayerAndEntityCpuType(i, cpu_type);
                    count--;
                    if (count == 0) break;
                }
            }

            damage = sub->menu_values[4];
            count = lbl_80473700.count;
            for (i = 0; i < 4; i++) {
                if (i != 0 && count != 0) {
                    Player_SetHUDDamage(i, damage);
                    count--;
                    if (count == 0) break;
                }
            }

            for (i = 1; i < 4; i++) {
                fn_8016B388(i, sub->menu_values[4]);
            }

            switch (sub->menu_values[6]) {
            case 0:
                fn_801650E8();
                break;
            case 1:
                fn_80165190(0, 5);
                break;
            case 2:
                if (lbl_80473700.mode == 3) {
                    fn_801652B0(0, 0);
                } else {
                    fn_801652B0(0, 3);
                }
                break;
            }
        }
        sub->x01 = 0;
    }
}
#pragma dont_inline off

s32 fn_80189B88(void)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    CssSubStruct* sub;
    int i;
    PAD_STACK(8);

    sub = &lbl_80473700.css;
    sub->x00 = 0;
    sub->x01 = 0;
    HSD_GObj_SetupProc(GObj_Create(0xE, 2, 0),
                       (HSD_GObjEvent) fn_801891F4, 0x15);
    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint((*lbl_804D662C)->joint);
    sub->gobj = gobj;
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObj_SetupProc(gobj, (HSD_GObjEvent) fn_80188EE8, 0x11);
    gm_8016895C(jobj, *lbl_804D662C, 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    for (i = 0; i < 0x27; i++) {
        sub->anim_frames[i] = 0;
        lb_80011E24(jobj, &sub->jobjs[i], i, -1);
    }
    sub->anim_frames[22] = 0x1E;
    sub->anim_frames[1] = 0x1E;
    sub->menu_values[0] = 0;
    sub->menu_values[1] = 0;
    sub->menu_values[2] = 0;
    sub->menu_values[3] = 0;
    sub->menu_values[4] = 0;
    sub->menu_values[5] = 0;
    sub->menu_values[6] = 0;
    sub->menu_values[0] = 2;
    return 0;
}

TrainingModeState* gm_80189CDC(StartMeleeData* arg0)
{
    s32 i;

    arg0->rules.x0_0 = 0;
    arg0->rules.is_teams = 1;
    arg0->rules.xB = -1;
    arg0->rules.x20 = 0xFFFFFFFFFFFFFFFFULL;
    arg0->rules.x5_0 = 1;

    for (i = 0; i < 4; i++) {
        lbl_80473700.css.saved_players[i] = arg0->players[i];
        lbl_80473700.players[i] = lbl_80473700.css.saved_players[i];
    }

    lbl_80473700.mode = (s32) (arg0->players[0].slot - 1);
    lbl_80473700.count = 1;

    for (i = 0; i < 25; i++) {
        lbl_80473700.char_data[i] = 0;
    }

    return &lbl_80473700;
}

inline void resetText(HSD_Text* text)
{
    text->pos_x = 0xf;
    text->pos_y = 0.6f;
}

HSD_Text* fn_8018A000(void)
{
    u8* data;
    HSD_Text* text;
    CssSubStruct* sub;

    PAD_STACK(0x10);
    data = lbl_803D9828;
    memzero(lbl_80473700.result_cache, 0x10);
    lbl_804D6628 = lbArchive_80016DBC("GmTrain",
        &lbl_804D662C, &data[0xA0], 0);
    fn_80189B88();
    ifAll_802F3404();
    HSD_SisLib_803A611C(0, NULL, 9, 0x14, 0, 0xE, 0, 0x12);
    sub = &lbl_80473700.css;
    if (lbLang_IsSavedLanguageUS()) {
        HSD_SisLib_803A62A0(0, (char*) &data[0xBC],
                            (char*) &data[0xC8]);
    } else {
        HSD_SisLib_803A62A0(0, (char*) &data[0xDC],
                            (char*) &data[0xC8]);
    }

    sub->text = HSD_SisLib_803A5ACC(
        0, 0,
        (12.0f * (HSD_JObjGetTranslationX(sub->jobjs[1]) + 9.798828f)) + 50.0f,
        150.0f, 0.1f, 167.0f, 16.0f);
    text = sub->text;
    lbLang_IsSettingUS();
    HSD_SisLib_803A6368(text, (s32) *(s16*) &data[2]);
    sub->text->default_fitting = 1;
    resetText(sub->text);
    text = sub->text;
    sub->text->default_alignment = 2;
    return text;
}

u8 gm_8018A160(u8 difficulty, u8 stage_slot)
{
    return lbl_803D9910[stage_slot + (difficulty * 5)].stage_kind;
}

f32 gm_8018A188(u8 difficulty, u8 stage_slot)
{
    return (f32) lbl_803D9910[stage_slot + (difficulty * 5)].scale0_pct /
           100.0F;
}

f32 gm_8018A1D8(u8 difficulty, u8 stage_slot)
{
    return (f32) lbl_803D9910[stage_slot + (difficulty * 5)].scale1_pct /
           100.0F;
}

u8 gm_8018A228(u8 difficulty, u8 stage_slot, u8 idx)
{
    return lbl_803D9910[stage_slot + (difficulty * 5)].pad_6[idx * 3];
}

u8 gm_8018A25C(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D9910[stage_slot + difficulty * 5].pad_6[arg2 * 3 + 1];
}

u8 gm_8018A290(u8 difficulty, u8 stage_slot, u8 idx)
{
    return lbl_803D9910[stage_slot + (difficulty * 5)].pad_6[2 + idx * 3];
}

f32 gm_8018A2C4(u8 difficulty, u8 stage_slot)
{
    return (f32) lbl_803D9910[stage_slot + (difficulty * 5)].scale0_pct /
           100.0F;
}

f32 gm_8018A314(u8 difficulty, u8 stage_slot)
{
    return (f32) lbl_803D9910[stage_slot + (difficulty * 5)].scale1_pct /
           100.0F;
}

void fn_8018A364(int arg0_int)
{
    MatchEnd* arg0 = (MatchEnd*) arg0_int;
    struct StartMeleeRules* rules;
    gmm_x0_528_t* main_data;
    UnkAllstarData* data;
    u32 total_time;

    rules = gm_8016AE50();
    data = &gm_80473A18;

    if (fn_8017E318() > 0) {
        ((u8_bits*)&arg0->_x448[2])->b3 = 1;
    }

    if (rules->x4_5) {
        main_data = gmMainLib_8015CDE0();
        total_time = data->x0.xC.x20 + gm_8016AEDC();
        ((u8_bits*)&arg0->_x448[0])->b5 = 1;

        if ((u8) data->x0.cpu_level == 4) {
            ((u8_bits*)&arg0->_x448[0])->b2 = 1;
        }

        if (total_time < 0x6270U) {
            ((u8_bits*)&arg0->_x448[2])->b6 = 1;
        } else if (total_time < 0x9AB0U) {
            ((u8_bits*)&arg0->_x448[2])->b7 = 1;
        }

        if ((u32) data->x0.xC.x1C == 0U && arg0->player_standings[0].x44 == 0) {
            ((u8_bits*)&arg0->_x448[1])->b1 = 1;
        }

        if ((u8) data->x0.xC.xE != 0) {
            ((u8_bits*)&arg0->_x448[2])->b5 = 1;
        }

        if ((u8) data->x0.xC.xF != 0) {
            ((u8_bits*)&arg0->_x448[2])->b4 = 1;
        }

        if ((u32)(data->x0.xC.x1C + arg0->player_standings[0].x44) == (u32) Player_GetDamage(0)) {
            ((u8_bits*)&arg0->_x448[0])->b1 = 1;
        }

        if ((u8) data->x0.xC.xD != 0) {
            ((u8_bits*)&arg0->_x448[1])->b0 = 1;
            return;
        }

        if (arg0->player_standings[0].stocks == main_data->stocks) {
            ((u8_bits*)&arg0->_x448[1])->b2 = 1;
        }
    }
}
