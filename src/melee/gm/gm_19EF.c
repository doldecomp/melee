#include "gm_19EF.h"

#include "gm_1601.h"
#include "gm_1A36.h"
#include "gm_1A3F.h"
#include "gm_1A45.h"
#include "gm_unsplit.h"

#include "it/inlines.h"

#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbspdisplay.h>
#include <melee/sc/types.h>
#include <melee/ty/toy.h>
#include <melee/ty/tylist.h>

static HSD_Archive* lbl_804D6698;
static SceneDesc* lbl_804D669C;
static SceneDesc* lbl_804D66A0;
static SceneDesc* lbl_804D66A4;
static SceneDesc* lbl_804D66A8;
static HSD_Joint* lbl_804D66AC;
static struct {
    HSD_JObj* x0;
    s32 x4;
} lbl_804D66B0;
static HSD_JObj* lbl_804D66B8;
static struct {
    HSD_JObj* x0;
    s32 x4;
} lbl_804D66C0;
static struct {
    HSD_JObj* x0;
    s32 x4;
} lbl_804D66C8;
static struct {
    HSD_JObj* x0;
    s32 x4;
} lbl_804D66D0;
static HSD_JObj* lbl_804D66D8;
static struct {
    HSD_JObj* x0;
    s32 x4;
} lbl_804D66E0;
static HSD_JObj* lbl_804D66E8;
static HSD_Archive* lbl_804D66F0;
static HSD_JObj* lbl_804D66F4;
static u32 lbl_804D66F8;

static struct {
    u8 x0;
    u8 pad_01[0x3];
    s32 x4;
    int x8;
    s32 xC;
    u32 x10;
    u8 x14;
    u8 x15;
    u8 x16;
    u8 pad_17;
    int x18;
    u16 x1C;
    u16 x1E;
    u8 x20;
    u8 pad_21;
    u16 x22;
    HSD_Text* x24;
    HSD_GObj* x28;
    HSD_JObj* x2C[10];
    HSD_JObj* x54;
    HSD_JObj* x58;
    HSD_JObj* x5C;
    u8 x60;
    u8 pad_61[3];
    s32 x64;
    s32 x68;
    s32 x6C;
    s32 x70;
    u8 pad_74[0x78 - 0x74];
} lbl_80479A98;

static void fn_8019F2D4(u32 arg0);

static void fn_8019EFC4(HSD_PadStatus* pad)
{
    HSD_JObj* child_next;
    HSD_JObj* jobj;

    jobj = lbl_80479A98.x28->hsd_obj;
    if ((u8) lbl_80479A98.x60 != 0) {
        if (jobj == NULL) {
            jobj = NULL;
        } else {
            jobj = jobj->child;
        }
        if (jobj == NULL) {
            jobj = NULL;
        } else {
            jobj = jobj->next;
        }
        child_next = jobj;
        if (lbl_80479A98.x70 != 0) {
            lbl_80479A98.x64++;
            if ((lbl_80479A98.x64 % 5 == 0) && lbl_80479A98.x70 != 0) {
                lbl_80479A98.x70--;
            }
            if (lbl_80479A98.x64 > 0 && lbl_80479A98.x64 <= 5) {
                lbl_80479A98.x68 =
                    lbl_80479A98.x64 + (lbl_80479A98.x68 / 5 * 5);
                if (lbl_80479A98.x68 > 0 && lbl_80479A98.x68 <= 5) {
                    lbl_80479A98.x6C =
                        lbl_80479A98.x68 + (lbl_80479A98.x6C / 5 * 5);
                }
            } else if (lbl_80479A98.x64 == 0x32) {
                lbl_80479A98.x64 = 0;
            }
        }
        HSD_JObjReqAnimAll(lbl_80479A98.x54, (f32) lbl_80479A98.x64);
        HSD_JObjReqAnimAll(lbl_80479A98.x58, (f32) lbl_80479A98.x68);
        HSD_JObjReqAnimAll(lbl_80479A98.x5C, (f32) lbl_80479A98.x6C);
        {
            s32 i;
            for (i = 10; i > 0; i--) {
                if (i > lbl_80479A98.x70) {
                    HSD_JObjSetFlags(lbl_80479A98.x2C[i - 1], JOBJ_HIDDEN);
                } else {
                    HSD_JObjClearFlags(lbl_80479A98.x2C[i - 1], JOBJ_HIDDEN);
                }
            }
        }
        HSD_JObjAnimAll(child_next);
    }
}

/// seems to handle "Go!" animations, based on .dat filenames

static void fn_8019F1D0(void)
{
    char sp8[28];
    u32 value;
    char* ptr;
    u32 rem;
    u8 count;

    count = 0;
    value = lbl_80479A98.x8;
    HSD_SisLib_803A7664(lbl_80479A98.x24);
    if (value != 0) {
        while (value != 0) {
            value /= 10;
            count++;
        }
        rem = lbl_80479A98.x8;
        ptr = &sp8[count];
        *ptr = '\0';
        while (count != 0) {
            *((&sp8[count]) - 1) = (char) ((rem % 10) + 0x30);
            rem /= 10;
            ptr--;
            count--;
        }
    } else {
        sp8[0] = 0x30;
        sp8[1] = 0;
    }
    HSD_SisLib_803A6B98(lbl_80479A98.x24, 240.0f, 176.0f, sp8);
}

static void fn_8019F2D4(u32 arg0)
{
    if (lbl_804D66C8.x4 == 0xA) {
        gm_80167858((s8) lbl_80479A98.x15, lbl_80479A98.x16, 0xD, 0xA);
    }
    if (lbl_804D66C8.x4 == 0x19) {
        gm_80167858((s8) lbl_80479A98.x15, lbl_80479A98.x16, 0xD, 0x14);
    }
    if ((u8) lbl_80479A98.x0 == 0) {
        HSD_JObj* jobj;
        HSD_MObj* mobj;

        if (lbl_804D66C8.x4 < 0x50) {
            lbl_804D66C8.x4++;
        } else {
            lbl_80479A98.x0 = 1;
        }
        lbl_804D66C0.x4 = lbl_804D66C8.x4;
        jobj = lbl_804D66C8.x0;
        HSD_JObjReqAnimAll(jobj, (f32) lbl_804D66C8.x4);
        HSD_JObjAnimAll(jobj);
        jobj = lbl_804D66C0.x0;
        HSD_JObjReqAnimAll(jobj, (f32) lbl_804D66C0.x4);
        HSD_JObjAnimAll(jobj);
        mobj = lbl_804D66C8.x0->u.dobj->mobj;
        HSD_MObjReqAnim(mobj, 0.0f);
        HSD_MObjAnim(mobj);
        mobj = lbl_804D66C0.x0->u.dobj->mobj;
        HSD_MObjReqAnim(mobj, 1.0f);
        HSD_MObjAnim(mobj);
        return;
    } else if ((u8) lbl_80479A98.x0 == 1) {
        HSD_JObj* jobj;
        HSD_MObj* mobj;

        if ((u8) lbl_80479A98.x14 != 0) {
            mobj = lbl_804D66C8.x0->u.dobj->mobj;
            HSD_MObjReqAnim(mobj, 0.0f);
            HSD_MObjAnim(mobj);
            mobj = lbl_804D66C0.x0->u.dobj->mobj;
            HSD_MObjReqAnim(mobj, 1.0f);
            HSD_MObjAnim(mobj);
        } else {
            mobj = lbl_804D66C8.x0->u.dobj->mobj;
            HSD_MObjReqAnim(mobj, 1.0f);
            HSD_MObjAnim(mobj);
            mobj = lbl_804D66C0.x0->u.dobj->mobj;
            HSD_MObjReqAnim(mobj, 0.0f);
            HSD_MObjAnim(mobj);
        }
        if (arg0 & 0x1100) {
            if ((u8) lbl_80479A98.x14 != 0) {
                if ((u16) lbl_80479A98.x1E >= (u16) lbl_80479A98.x1C) {
                    lbl_80479A98.x0 = 8;
                    lbAudioAx_80024030(1);
                    lbl_80479A98.x60 = 1;
                    lbl_80479A98.x22 =
                        lbl_80479A98.x22 - (lbl_80479A98.x1C * 0xA);
                    lbl_80479A98.x1E = lbl_80479A98.x1E - lbl_80479A98.x1C;
                    lbl_804D66C8.x4 = 0x5A;
                    lbl_804D66C0.x4 = 0x64;
                    return;
                }
                lbAudioAx_80024030(3);
                return;
            }
            lbl_80479A98.x0 = 8;
            lbAudioAx_80024030(1);
            lbAudioAx_80023F28(0x20);
            lbAudioAx_800237A8(0x9C43, 0x7F, 0x40);
            lbl_804D66C8.x4 = 0x6E;
            lbl_804D66C0.x4 = 0x78;
            return;
        }
        if ((arg0 & 0x40000) && ((u8) lbl_80479A98.x14 == 0)) {
            lbAudioAx_80024030(2);
            lbl_80479A98.x14 = 1;
        }
        if ((arg0 & 0x80000) && ((u8) lbl_80479A98.x14 == 1)) {
            lbAudioAx_80024030(2);
            lbl_80479A98.x14 = 0;
            return;
        }
    } else if ((u8) lbl_80479A98.x0 == 8) {
        HSD_JObj* jobj;
        HSD_MObj* mobj;

        jobj = lbl_804D66C0.x0;
        HSD_JObjReqAnimAll(jobj, (f32) lbl_804D66C8.x4);
        HSD_JObjAnimAll(jobj);
        jobj = lbl_804D66C8.x0;
        HSD_JObjReqAnimAll(jobj, (f32) lbl_804D66C8.x4);
        HSD_JObjAnimAll(jobj);
        if (lbl_804D66C8.x4 < lbl_804D66C0.x4) {
            lbl_804D66C8.x4++;
        } else if ((u8) lbl_80479A98.x14 != 0) {
            lbl_80479A98.x0 = 9;
            lbl_804D66E0.x4 = 0x3C;
        } else {
            lbl_80479A98.x0 = 0xA;
        }
        if ((u8) lbl_80479A98.x14 != 0) {
            mobj = lbl_804D66C0.x0->u.dobj->mobj;
            HSD_MObjReqAnim(mobj, 2.0f);
            HSD_MObjAnim(mobj);
            return;
        }
        mobj = lbl_804D66C8.x0->u.dobj->mobj;
        HSD_MObjReqAnim(mobj, 2.0f);
        HSD_MObjAnim(mobj);
    }
}

static void fn_8019F6EC(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);

    HSD_JObjReqAnimAll(jobj, (f32) lbl_804D66E0.x4);
    if (lbl_80479A98.x0 == 0) {
        if (lbl_804D66E0.x4 < 0x32) {
            lbl_804D66E0.x4 += 1;
        } else if (lbl_80479A98.x20 != 0) {
            lbAudioAx_800237A8(0x9C43, 0x7F, 0x40);
            lbAudioAx_80023F28(0x20);
            lbl_80479A98.x0 = 0xAU;
        }
    } else if (lbl_80479A98.x0 == 9) {
        if (lbl_804D66E0.x4 < 0x50) {
            lbl_804D66E0.x4 += 1;
        } else if ((u32) lbl_80479A98.x8 == (u32) lbl_80479A98.xC &&
                   lbl_80479A98.x70 == 0)
        {
            gm_801A4B60();
            lbl_80479A98.x18 = 1;
        }
    }
    HSD_JObjAnimAll(jobj);
    HSD_JObjAnimAll(lbl_804D66B8);
    HSD_JObjAnimAll(lbl_804D66E8);
}

static void fn_8019F810(void)
{
    u32 trigger;
    PAD_STACK(16);

    trigger = HSD_PadCopyStatus[lbl_80479A98.x15].trigger;
    fn_8019EFC4(&HSD_PadCopyStatus[lbl_80479A98.x15]);
    if (lbl_80479A98.x0 < 8U) {
        lbl_804D66B0.x4 += 1;
        if (lbl_804D66B0.x4 > 0x31F) {
            lbl_804D66B0.x4 = 0x190;
        }
        HSD_JObjReqAnimAll(lbl_804D66B0.x0, (f32) lbl_804D66B0.x4);
        HSD_JObjAnimAll(lbl_804D66B0.x0);
    } else {
        HSD_JObjSetFlagsAll(lbl_804D66B0.x0, JOBJ_HIDDEN);
    }
    if (lbl_80479A98.x0 == 9) {
        if ((u32) lbl_80479A98.x8 == (u32) lbl_80479A98.xC) {
            switch (lbl_80479A98.x4) {
            case 0:
            case 1:
            case 2:
                lbl_80479A98.x18 = 1;
            }
        } else {
            fn_80168F2C(0);
            lbl_80479A98.x8 =
                ((lbl_80479A98.x8 - lbl_80479A98.x10) < (lbl_80479A98.xC))
                    ? (lbl_80479A98.xC)
                    : (lbl_80479A98.x8 - lbl_80479A98.x10);
        }
    }
    if (lbl_80479A98.x0 == 0xA) {
        HSD_JObjReqAnimAll(lbl_804D66D0.x0, (f32) lbl_804D66D0.x4);
        HSD_JObjAnimAll(lbl_804D66D0.x0);
        if (lbl_804D66D0.x4 < 0x2B2) {
            lbl_804D66D0.x4 += 1;
        } else {
            gm_801A4B60();
            lbl_80479A98.x18 = 0;
        }
    }
    fn_8019F2D4(trigger);
    fn_8019F1D0();
}

static inline s32 fn_8019F9C4_GetCharIdx(CharacterKind arg0)
{
    switch (gm_801A4310()) {
    case 3:
        return gm_80160474(arg0, GM_CLASSIC);
    case 4:
        return gm_80160474(arg0, GM_ADVENTURE);
    default:
        return gm_80160474(arg0, GM_ALLSTAR);
    }
}

void fn_8019F9C4(u32 arg0)
{
    HSD_CObj* cobj;
    HSD_GObj* gobj;
    HSD_GObj* cam_gobj;
    HSD_JObj* jobj;
    HSD_JObj* child;
    HSD_JObj* next;
    HSD_JObj* node;
    HSD_JObj** ptr;
    s32 char_idx;
    s32 i;
    f32 f;
    f32 scale;
    PAD_STACK(8);

    char_idx = fn_8019F9C4_GetCharIdx(arg0);
    arg0 = (char_idx == -1) ? 8 : arg0;
    fn_80168F7C();
    lbl_804D6698 = lbArchive_80016DBC("GmGover.dat", &lbl_804D669C,
                                      "ScGamRegGover_scene_data", 0);
    lbArchive_80016DBC("GmGoCoin.dat", &lbl_804D66A0,
                       "ScGamRegGover_scene_data", 0);
    Toy_803124BC();
    Toy_803102D0();
    {
        u8 game_mode = gm_801A4310();
        char* model_name = gm_80160564(arg0, game_mode);
        char* scene_name = gm_801604DC(arg0, game_mode);
        lbArchive_LoadSymbols(scene_name, &lbl_804D66AC, model_name, 0);
        lbArchive_LoadSymbols("GmGoAnim.dat", &lbl_804D66A4,
                              "ScGamRegGover_scene_data", 0);
        lbArchive_LoadSymbols("GmRgStnd.dat", &lbl_804D66A8, "standScene", 0);
    }
    cobj = HSD_CObjLoadDesc(lbl_804D669C->cameras->desc);
    cam_gobj = GObj_Create(0x13, 0x14, 0);
    HSD_GObjObject_80390A70(cam_gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(cam_gobj, HSD_GObj_803910D8, 0);
    cam_gobj->gxlink_prios = 0x801;

    gobj = GObj_Create(0xB, 0xF, 0);
    {
        HSD_LObj* lobj = lb_80011AC4(lbl_804D669C->lights);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    }
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(lbl_804D669C->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObj_SetupProc(gobj, (void (*)(HSD_GObj*)) fn_8019F810, 0);
    gm_8016895C(jobj, lbl_804D669C->models[0], 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    lbl_80479A98.x14 = 1;
    lbl_80479A98.x0 = 0;
    lbl_804D66B0.x4 = 0;
    lbl_804D66C0.x4 = 0;
    lbl_804D66C8.x4 = 0;
    lbl_804D66E0.x4 = 0;
    lbl_804D66D0.x4 = 0x24E;
    lb_80011E24(jobj, &lbl_804D66B0.x0, 0x38, -1);
    lb_80011E24(jobj, &lbl_804D66D8, 1, -1);
    lb_80011E24(jobj, &lbl_804D66D0.x0, 2, -1);
    lb_80011E24(jobj, &lbl_804D66C8.x0, 0x35, -1);
    lb_80011E24(jobj, &lbl_804D66C0.x0, 0x37, -1);
    if ((u8) lbl_80479A98.x20 != 0) {
        HSD_JObjSetFlagsAll(lbl_804D66B0.x0, JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(lbl_804D66C8.x0, JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(lbl_804D66C0.x0, JOBJ_HIDDEN);
    }

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(lbl_804D66A0->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    gm_8016895C(jobj, lbl_804D66A0->models[0], 0);
    lbl_80479A98.x28 = gobj;

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }
    if (child == NULL) {
        node = NULL;
    } else {
        node = child->child;
    }

    for (i = 0; i < 10; i++) {
        lbl_80479A98.x2C[i] = node;
        if (node->next != NULL) {
            node = node->next;
        }
    }

    lbl_80479A98.x70 = lbl_80479A98.x1C;

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }
    if (child == NULL) {
        next = NULL;
    } else {
        next = child->next;
    }

    if (next == NULL) {
        child = NULL;
    } else {
        child = next->child;
    }
    lbl_80479A98.x54 = child;

    if (lbl_80479A98.x54 == NULL) {
        child = NULL;
    } else {
        child = lbl_80479A98.x54->next;
    }
    lbl_80479A98.x58 = child;

    if (lbl_80479A98.x58 == NULL) {
        child = NULL;
    } else {
        child = lbl_80479A98.x58->next;
    }
    lbl_80479A98.x5C = child;

    {
        u16 val = lbl_80479A98.x1E;
        lbl_80479A98.x6C = ((0xA - ((val / 100) % 10)) * 5) % 50;
        lbl_80479A98.x68 = ((0xA - ((val / 10) % 10)) * 5) % 50;
        lbl_80479A98.x64 = ((0xA - (val % 10)) * 5) % 50;
    }
    HSD_JObjReqAnimAll(lbl_80479A98.x5C, (f32) lbl_80479A98.x6C);
    HSD_JObjReqAnimAll(lbl_80479A98.x58, (f32) lbl_80479A98.x68);
    HSD_JObjReqAnimAll(lbl_80479A98.x54, (f32) lbl_80479A98.x64);
    for (i = 10; i > 0; i--) {
        if (i > lbl_80479A98.x70) {
            HSD_JObjSetFlags(lbl_80479A98.x2C[i - 1], JOBJ_HIDDEN);
        } else {
            HSD_JObjClearFlags(lbl_80479A98.x2C[i - 1], JOBJ_HIDDEN);
        }
    }
    HSD_JObjAnimAll(jobj);

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(lbl_804D66A4->models[0]->joint);
    lbl_804D66E0.x0 = jobj;
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObj_SetupProc(gobj, fn_8019F6EC, 0);
    gm_8016895C(jobj, lbl_804D66A4->models[0], 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(lbl_804D66A8->models[0]->joint);
    lbl_804D66E8 = jobj;
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_JObjSetScaleX(jobj, 2.0f);
    HSD_JObjSetScaleY(jobj, 2.0f);
    HSD_JObjSetScaleZ(jobj, 2.0f);

    if (lbl_804D66E0.x0 == NULL) {
        child = NULL;
    } else {
        child = lbl_804D66E0.x0->child;
    }
    if (child == NULL) {
        next = NULL;
    } else {
        next = child->child;
    }
    if (next == NULL) {
        node = NULL;
    } else {
        node = next->child;
    }
    lb_8000C1C0(jobj, node);

    if (lbl_804D66E0.x0 == NULL) {
        child = NULL;
    } else {
        child = lbl_804D66E0.x0->child;
    }
    if (child == NULL) {
        next = NULL;
    } else {
        next = child->child;
    }
    if (next == NULL) {
        node = NULL;
    } else {
        node = next->child;
    }
    lb_8000C290(jobj, node);

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(lbl_804D66AC);
    lbl_804D66B8 = jobj;
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);

    char_idx = fn_8019F9C4_GetCharIdx(arg0);

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    HSD_JObjSetTranslateX(child, Toy_803060BC(char_idx, 0));
    HSD_JObjSetTranslateY(child, Toy_803060BC(char_idx, 1));
    HSD_JObjSetTranslateZ(child, Toy_803060BC(char_idx, 2));
    HSD_JObjSetRotationY(child, 0.017453292f * Toy_803060BC(char_idx, 5));
    f = Toy_803060BC(char_idx, 4);
    scale = Toy_803060BC(char_idx, 3) / f;
    HSD_JObjSetScaleX(child, scale);
    HSD_JObjSetScaleY(child, scale);
    HSD_JObjSetScaleZ(child, scale);
    HSD_JObjSetScaleX(jobj, 2.0f);
    HSD_JObjSetScaleY(jobj, 2.0f);
    HSD_JObjSetScaleZ(jobj, 2.0f);

    lb_8000C1C0(jobj, lbl_804D66E8);
    lb_8000C290(jobj, lbl_804D66E8);

    HSD_SisLib_803A611C(0, cam_gobj, 9, 0x12, 0, 0xB, 0, 0x13);
    HSD_SisLib_803A62A0(0, "SdIntro.dat", "SIS_IntroData");
    lbl_80479A98.x24 = HSD_SisLib_803A6754(0, 0);
    lbl_80479A98.x24->font_size.x = 0.1f;
    lbl_80479A98.x24->font_size.y = 0.1f;
    lbl_80479A98.x24->default_alignment = 2;
    HSD_SisLib_803A6B98(lbl_80479A98.x24, 240.0f, 176.0f, " ");
    if ((u8) lbl_80479A98.x20 == 0) {
        lbAudioAx_800237A8(0x9C42, 0x7F, 0x40);
        lbAudioAx_80023F28(5);
    }
}

void gm_801A0A10_OnEnter(void* arg0_)
{
    DebugGameOverData* arg0 = arg0_;

    lbl_80479A98.x60 = 0;
    lbl_80479A98.x22 = arg0->x18;
    lbl_80479A98.x1E = (u16) (arg0->x18 / 10);
    if (lbl_80479A98.x1E > 0x3E7U) {
        lbl_80479A98.x1E = 0x3E7U;
    }
    lbl_80479A98.x1C = arg0->x16;
    if (lbl_80479A98.x1E >= lbl_80479A98.x1C) {
        lbl_80479A98.x20 = 0;
    } else {
        lbl_80479A98.x20 = 1;
    }
    lbl_80479A98.x16 = (u8) arg0->x15;
    lbl_80479A98.x4 = (s32) arg0->x8;
    lbl_80479A98.x8 = (s32) arg0->x0;
    lbl_80479A98.xC = (s32) ((s32) arg0->x0 / 2);
    lbl_80479A98.x10 = (u32) (lbl_80479A98.x8 - lbl_80479A98.xC) / 120;
    if (lbl_80479A98.x10 == 0) {
        lbl_80479A98.x10 = 1U;
    }
    lbl_80479A98.x15 = arg0->slot;
    fn_8019F9C4(arg0->ckind);
}

void gm_801A0B18_OnLeave(void* arg0_)
{
    DebugGameOverData* arg0 = arg0_;
    arg0->x4 = lbl_80479A98.x8;
    arg0->xC = lbl_80479A98.x18;
    arg0->x18 = lbl_80479A98.x22;
    lbAudioAx_800236DC();
    lbArchive_80016EFC(lbl_804D6698);
}

static void fn_801A0B60(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObjReqAnimAll(jobj, lbl_804D66F8);
    HSD_JObjAnimAll(jobj);
    if (lbl_804D66F8 == 0xBD) {
        if (((u32) gm_801A36A0(4) & 0x1000) || ((u32) gm_801A36A0(4) & 0x100))
        {
            lbl_804D66F8 += 1;
        }
    } else {
        lbl_804D66F8 += 1;
    }
    if ((int) HSD_AObjGetCurrFrame(lbl_804D66F4->aobj) >=
        (int) HSD_AObjGetEndFrame(lbl_804D66F4->aobj))
    {
        gm_801A4B60();
    }
}

void gm_801A0C6C_OnEnter(void* unused)
{
    SceneDesc* sp10;
    HSD_GObj* temp_r30;
    HSD_GObj* temp_r30_2;
    HSD_GObj* temp_r30_3;
    HSD_JObj* temp_r3;
    HSD_CObj* cobj;
    HSD_LObj* lobj;
    PAD_STACK(4);

    lbl_804D66F8 = 0;
    lbl_804D66F0 =
        lbArchive_80016DBC("IfComSn.dat", &sp10, "ScComSoon_scene_data", 0);

    temp_r30 = GObj_Create(0x13, 0x14, 0);
    cobj = HSD_CObjLoadDesc(sp10->cameras[0].desc);
    HSD_GObjObject_80390A70(temp_r30, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(temp_r30, HSD_GObj_803910D8, 0);
    temp_r30->gxlink_prios = 0x801;

    temp_r30_2 = GObj_Create(0xB, 0xF, 0);
    lobj = lb_80011AC4(sp10->lights);
    HSD_GObjObject_80390A70(temp_r30_2, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(temp_r30_2, HSD_GObj_LObjCallback, 0, 0);
    temp_r30_3 = GObj_Create(0xE, 0xF, 0);
    temp_r3 = HSD_JObjLoadJoint(sp10->models[0]->joint);
    HSD_GObjObject_80390A70(temp_r30_3, HSD_GObj_804D7849, temp_r3);
    GObj_SetupGXLink(temp_r30_3, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObj_SetupProc(temp_r30_3, fn_801A0B60, 0);
    gm_8016895C(temp_r3, sp10->models[0], 0);
    HSD_JObjReqAnimAll(temp_r3, 0.0f);
    HSD_JObjAnimAll(temp_r3);
    lb_80011E24(temp_r3, &lbl_804D66F4, 1, -1);
}

extern HSD_Archive* lbl_804D66F0;

void gm_801A0E0C_OnLeave(void* unused)
{
    lbArchive_80016EFC(lbl_804D66F0);
    lbAudioAx_800236DC();
}
