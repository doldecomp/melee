#include "mnstagesel.static.h"

#include "mnstagesel.h"

#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/random.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_1A36.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/types.h>
#include <melee/mn/mn_2295.h>

struct stagelistinfo {
    HSD_JObj* x0;
    int x4;
    u8 x8, x9, xA, xB;
    f32 xC, x10, x14, x18;
} mnStageSel_803F06D0[30] = {
    { 0, 0, 0x2, 0x00, 0x00, 0x04, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x01, 0x0C, 0x0B, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x02, 0x01, 0x05, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x03, 0x0D, 0x0C, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x04, 0x02, 0x0D, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x05, 0x0E, 0x0E, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x08, 0x04, 0x08, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x09, 0x10, 0x10, 2.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0A, 0x05, 0x02, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0B, 0x11, 0x11, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0C, 0x06, 0x07, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0D, 0x12, 0x16, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x06, 0x03, 0x06, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x07, 0x0F, 0x0F, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x12, 0x09, 0x09, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x13, 0x15, 0x12, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x10, 0x08, 0x0A, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x11, 0x14, 0x18, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0E, 0x07, 0x03, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0F, 0x13, 0x17, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x14, 0x0B, 0x13, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x15, 0x16, 0x14, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x16, 0x0A, 0x19, 3.1F, 2.9F, 1.0F, 1.1F },
    { 0, 0, 0x2, 0x17, 0x17, 0x1B, 3.1F, 2.9F, 1.0F, 1.1F },
    { 0, 0, 0x2, 0x18, 0x18, 0x1F, 2.9F, 2.1F, 0.8F, 0.8F },
    { 0, 0, 0x2, 0x19, 0x19, 0x20, 2.9F, 2.1F, 0.8F, 0.8F },
    { 0, 0, 0x2, 0x1A, 0x1A, 0x1C, 2.9F, 2.1F, 0.8F, 0.8F },
    { 0, 0, 0x2, 0x1B, 0x1B, 0x1D, 2.9F, 2.1F, 0.8F, 0.8F },
    { 0, 0, 0x2, 0x1C, 0x1C, 0x1E, 2.9F, 2.1F, 0.8F, 0.8F },
    { 0, 0, 0x2, 0x1D, 0x00, 0x00, 3.6F, 2.7F, 1.2F, 1.0F },
};
static s8 mnStageSel_804D50A0 = -1;

static struct mnStageSel_804D6C90_t {
    u8 x0;
    u8 x1;
    u8 x2;
    s8 x3;
    GXBool x4;
    u32 x8, xC, x10, x14, x18;
    u16 x1C, x1E_stage_id;
}* mnStageSel_804D6C90;
static HSD_Archive* mnStageSel_804D6C94;
static struct {
    u8 _1[0x30];
    UNK_T x30;
    UNK_T x34;
    UNK_T x38;
    UNK_T x3C;
    u8 _2[0xb0 - 0x40];
    HSD_Joint* xB0;
    HSD_AnimJoint* xB4;
    HSD_MatAnimJoint* xB8;
    HSD_ShapeAnimJoint* xBC;
}* mnStageSel_804D6C98;
static HSD_GObj* mnStageSel_804D6C9C;
static u32 mnStageSel_804D6CA0;
static u32 mnStageSel_804D6CA4;
static s32 mnStageSel_804D6CA8;
static s8 mnStageSel_804D6CAC;
static s8 mnStageSel_804D6CAD;
static u8 mnStageSel_804D6CAE;
static u8 mnStageSel_804D6CAF;

STATIC_ASSERT(sizeof(mnStageSel_803F06D0[0]) == 0x1C);

struct StageSelUserData {
    u16 x0;
    u16 x2;
    int x4;
};

#define MAX_ITER 100000
#define NUM_STAGES 29

// Random stage selection
// Returns an internal stage ID - 2 (since first 2 internal stage IDs are
// invalid)
int mnStageSel_802599EC(void)
{
    int var_r0;
    int iter;
    bool var_r29 = true;
    int i;

    for (i = 0; i < NUM_STAGES; i++) {
        if (mnStageSel_803F06D0[i].x4 >= 0 &&
            gm_80164330(mnStageSel_803F06D0[i].xA))
        {
            break;
        }
    }
    if (i == NUM_STAGES) {
        for (i = 0; i < NUM_STAGES; i++) {
            mnStageSel_803F06D0[i].x4 = 0;
        }
    }
    while (var_r29) {
        for (i = 0; i < NUM_STAGES; i++) {
            if (mnStageSel_803F06D0[i].x4 > 0) {
                mnStageSel_803F06D0[i].x4--;
            }
        }
        for (i = 0; i < NUM_STAGES; i++) {
            if (mnStageSel_803F06D0[i].x4 == 0 &&
                gm_80164330(mnStageSel_803F06D0[i].xA))
            {
                var_r29 = false;
            }
        }
    }
    for (iter = 0; iter < MAX_ITER; iter++) {
        int tmp = HSD_Randi(NUM_STAGES);
        i = tmp;
        if (mnStageSel_803F06D0[i].x4 == 0) {
            if (gm_80164330(mnStageSel_803F06D0[i].xA)) {
                break;
            }
        }
    }
    if (iter >= MAX_ITER) {
        i = 0;
    }
    mnStageSel_803F06D0[i].x4 = -1;
    if (i < 22) {
        if (i & 1) {
            var_r0 = i - 1;
        } else {
            var_r0 = i + 1;
        }
        if (mnStageSel_803F06D0[var_r0].x4 >= 0) {
            mnStageSel_803F06D0[var_r0].x4 = 3;
        }
    }
    return i;
}

void mnStageSel_80259C28(void)
{
    HSD_JObj* jobj;
    HSD_GObj* gobj;
    u64 _[2];

    if (mnStageSel_804D6CA4 != 0) {
        return;
    }
    switch (mnStageSel_804D6CAE) {
    case 30:
        if (!(mnStageSel_804D6CA0 & 0x1000)) {
            return;
        }
        break;
    case 29:
        if (!(mnStageSel_804D6CA0 & 0x1100)) {
            return;
        }
        break;
    default:
        if (!(mnStageSel_804D6CA0 & 0x1100)) {
            return;
        }
        if (mnStageSel_804D6CAE < 0x1E &&
            mnStageSel_803F06D0[mnStageSel_804D6CAE].x8 >= 2)
        {
            goto skip_randomize;
        }
        lbAudioAx_80024030(3);
        return;
    }
    mnStageSel_804D6CAE = mnStageSel_802599EC();
skip_randomize:

    gobj = GObj_Create(HSD_GOBJ_CLASS_FIGHTER, 5, 0x80);
    jobj = HSD_JObjLoadJoint(mnStageSel_804D6C98->xB0);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x87);
    HSD_GObjProc_8038FD54(gobj, mn_8022EAE0, 0);
    HSD_JObjAddAnimAll(jobj, mnStageSel_804D6C98->xB4,
                       mnStageSel_804D6C98->xB8, mnStageSel_804D6C98->xBC);
    HSD_JObjReqAnimAll(gobj->hsd_obj, 0.0F);
    HSD_JObjAnimAll(gobj->hsd_obj);
    mnStageSel_804D6CAF = 1;
    mnStageSel_804D6CA4 = 0x1E;
    lbAudioAx_80024030(1);
}

void fn_80259D84(HSD_GObj* gobj)
{
    struct StageSelUserData* temp_r31 = HSD_GObjGetUserData(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    switch (temp_r31->x2) {
    case 0:
        if (mnStageSel_804D6CAF == 0) {
            mnStageSel_80259C28();
        }
        if (++temp_r31->x4 >= 9U) {
            HSD_ForeachAnim(jobj, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
            temp_r31->x2 = 1;
        }
        break;
    case 1:
        if (mnStageSel_804D6CAF == 0) {
            mnStageSel_80259C28();
        }
        if (temp_r31->x0 != mnStageSel_804D6CAE) {
            if (temp_r31->x0 < 0x1E &&
                mnStageSel_803F06D0[temp_r31->x0].x8 >= 2)
            {
                HSD_JObjReqAnimAllByFlags(jobj, 1, 10.0F);
            }
            lbAudioAx_80024030(2);
            temp_r31->x4 = 0;
            temp_r31->x2 = 2;
            mnStageSel_80259ED8(mnStageSel_804D6CAE);
        }
        break;
    case 2:
        if (++temp_r31->x4 > 0xAU) {
            HSD_GObjPLink_80390228(gobj);
            temp_r31->x2++;
        }
        break;
    }
}

void mnStageSel_80259ED8(int id)
{
    HSD_GObj* gobj;
    int temp_r29_2;
    HSD_JObj* jobj;
    struct StageSelUserData* temp_r3_2;
    u8 _[4];

    gobj = GObj_Create(HSD_GOBJ_CLASS_FIGHTER, 5, 0x80);
    jobj = HSD_JObjLoadJoint(mnStageSel_804D6C98->x30);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x84);
    HSD_GObjProc_8038FD54(gobj, mn_8022EAE0, 1);
    HSD_JObjAddAnimAll(jobj, mnStageSel_804D6C98->x34,
                       mnStageSel_804D6C98->x38, mnStageSel_804D6C98->x3C);
    jobj = GET_JOBJ(gobj);
    temp_r3_2 = HSD_MemAlloc(sizeof(struct StageSelUserData));
    GObj_InitUserData(gobj, 4, HSD_Free, temp_r3_2);
    HSD_GObjProc_8038FD54(gobj, fn_80259D84, 1);
    temp_r3_2->x0 = id;
    temp_r3_2->x4 = 0;
    temp_r3_2->x2 = 0;
    if (id < 0x1E) {
        if (mnStageSel_803F06D0[id].x8 >= 2) {
            temp_r29_2 = 20.0F * mnStageSel_803F06D0[id].x9;
            HSD_JObjReqAnimAll(jobj, 0.0F);
            HSD_JObjReqAnimAllByFlags(jobj, 0x10, temp_r29_2);
            HSD_JObjAnimAll(jobj);
            HSD_ForeachAnim(jobj, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
        }
    }
}

void fn_8025A090(HSD_GObj* gobj)
{
    u32 var_r3;
    struct {
        u32 x0;
        u32 x4;
    }* temp_r30;
    HSD_JObj* jobj;

    jobj = GET_JOBJ(gobj);
    temp_r30 = HSD_GObjGetUserData(gobj);
    var_r3 = mnStageSel_804D6CAE;
    if (mnStageSel_803F06D0[mnStageSel_804D6CAE].x8 < 2) {
        var_r3 = 0x1E;
    }
    if (temp_r30->x0 != var_r3) {
        temp_r30->x0 = var_r3;
        temp_r30->x4 = 0;
        if ((s32) var_r3 < 0x1D) {
            HSD_JObjReqAnimAll(jobj, 50.0F * mnStageSel_803F06D0[var_r3].x9);
            HSD_JObjAnimAll(jobj);
            HSD_ForeachAnim(jobj, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
            HSD_JObjSetTranslateX(jobj, 0.0F);
        } else {
            HSD_JObjSetTranslateX(jobj, 100.0F);
        }
    }
    if (temp_r30->x4 < 0x5A) {
        temp_r30->x4++;
        if (temp_r30->x4 == 0x14) {
            HSD_JObjReqAnimAll(jobj,
                               50.0F * mnStageSel_803F06D0[temp_r30->x0].x9);
        }
        if (temp_r30->x4 == 0x45) {
            HSD_ForeachAnim(jobj, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
        }
    } else if (mnStageSel_804D6CAF) {
        mnStageSel_804D6CAF = 2;
    }
}

void fn_8025A310(HSD_GObj* gobj)
{
    Vec3 sp1C;
    Vec3 sp10;
    f32 temp_f1;
    f32 temp_f2;
    int i;
    HSD_JObj* jobj;
    u32 unused;

    jobj = gobj->hsd_obj;
    if (mnStageSel_804D6CAF != 0) {
        HSD_JObjSetFlags(jobj, 0x10);
        return;
    }
    HSD_JObjGetTranslation(jobj, &sp1C);
    sp1C.x = 0.03f * mnStageSel_804D6CAC + sp1C.x;
    if (-27.0F > sp1C.x) {
        sp1C.x = -27.0F;
    }
    if (27.0F < sp1C.x) {
        sp1C.x = 27.0F;
    }
    sp1C.y = 0.03f * mnStageSel_804D6CAD + sp1C.y;
    if (-19.0F > sp1C.y) {
        sp1C.y = -19.0F;
    }
    if (19.0F < sp1C.y) {
        sp1C.y = 19.0F;
    }

    HSD_JObjSetTranslate(jobj, &sp1C);
    lb_8000B1CC(jobj, NULL, &sp1C);
    for (i = 0; i < 0x1E; i++) {
        if (mnStageSel_803F06D0[i].x8 != 0) {
            lb_8000B1CC(mnStageSel_803F06D0[i].x0, NULL, &sp10);
            temp_f2 = sp10.x;
            temp_f1 = mnStageSel_803F06D0[i].xC;
            if (temp_f2 - temp_f1 < sp1C.x && temp_f2 + temp_f1 > sp1C.x) {
                if (sp10.y - mnStageSel_803F06D0[i].x10 < sp1C.y &&
                    sp10.y + mnStageSel_803F06D0[i].x10 > sp1C.y)
                {
                    mnStageSel_804D6CAE = i;
                    return;
                }
            }
        }
    }
}

void fn_8025A560(HSD_GObj* gobj)
{
    struct StageSelUserData {
        int x0;
    }* temp_r30;
    Vec3 sp10;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    temp_r30 = HSD_GObjGetUserData(gobj);

    if (mnStageSel_804D6CAE < 0x16 && (mnStageSel_804D6CAE & 1) &&
        mnStageSel_803F06D0[mnStageSel_804D6CAE].x8 == 0)
    {
        HSD_JObjSetTranslateX(jobj, 100.0F);
    } else if (mnStageSel_804D6CAE < 0x1E) {
        lb_8000B1CC(mnStageSel_803F06D0[mnStageSel_804D6CAE].x0, NULL, &sp10);
        HSD_JObjSetTranslateX(jobj, sp10.x);
        HSD_JObjSetTranslateY(jobj, sp10.y);
        HSD_JObjSetScaleX(jobj, mnStageSel_803F06D0[mnStageSel_804D6CAE].x14);
        HSD_JObjSetScaleY(jobj, mnStageSel_803F06D0[mnStageSel_804D6CAE].x18);
    } else {
        HSD_JObjSetTranslateX(jobj, 100.0F);
    }
    if (mnStageSel_804D6CAF != 0) {
        HSD_JObjReqAnimAll(jobj, 0.0F);
        HSD_JObjAnimAll(jobj);
        return;
    }
    if (++temp_r30->x0 >= 10) {
        temp_r30->x0 = 0;
        HSD_JObjReqAnimAll(jobj, 0.0F);
        HSD_JObjAnimAll(jobj);
    }
}

void fn_8025A91C(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if (++mnStageSel_804D6CA8 >= 0xFA) {
        mnStageSel_804D6CA8 = 0;
        HSD_JObjReqAnimAll(jobj, 0.0F);
        HSD_JObjAnimAll(jobj);
    }
}

void fn_8025A974(HSD_GObj* gobj, u32 unused)
{
    HSD_FogSet(gobj->hsd_obj);
}

// OnLoad
/// #mnStageSel_8025A998_OnEnter

static inline HSD_PadStatus* get_pad(u8 i)
{
    return &HSD_PadCopyStatus[i];
}

// OnFrame
void mnStageSel_8025B850_OnFrame(void)
{
    if (mnStageSel_804D6C90->x3 >= 0) {
        mnStageSel_804D6CAF = 2;
        mnStageSel_804D6C90->x1E_stage_id = mnStageSel_804D6C90->x3;
        gm_801A4B60();
        return;
    }
    if (mnStageSel_804D6C90->x2 == 0 && mn_8022F218()) {
        lbAudioAx_80024030(0);
        lb_800145F4();
        HSD_GObjPLink_80390228(mnStageSel_804D6C9C);
        mn_8022F268();
        gm_801A42F8(1);
        gm_801A4B60();
        return;
    }
    if (mnStageSel_804D50A0 < 0) {
        mnStageSel_804D6CA0 = 0;
        mnStageSel_804D6CA0 |= HSD_PadCopyStatus[0].trigger;
        mnStageSel_804D6CA0 |= HSD_PadCopyStatus[1].trigger;
        mnStageSel_804D6CA0 |= HSD_PadCopyStatus[2].trigger;
        mnStageSel_804D6CA0 |= HSD_PadCopyStatus[3].trigger;
        {
            int i;
            for (i = 0; i < 4; i++) {
                mnStageSel_804D6CAC = get_pad(i)->stickX;
                mnStageSel_804D6CAD = get_pad(i)->stickY;
                if (get_pad(i)->stickX < -0x1E || get_pad(i)->stickX > +0x1E ||
                    get_pad(i)->stickY < -0x1E || get_pad(i)->stickY > +0x1E)
                {
                    break;
                }
            }
        }
    } else {
        mnStageSel_804D6CA0 = get_pad(mnStageSel_804D50A0)->trigger;
        mnStageSel_804D6CAC = get_pad(mnStageSel_804D50A0)->stickX;
        mnStageSel_804D6CAD = get_pad(mnStageSel_804D50A0)->stickY;
    }
    if (mnStageSel_804D6CAC < -0x1E) {
        mnStageSel_804D6CAC += 0x1E;
    } else if (mnStageSel_804D6CAC > 0x1E) {
        mnStageSel_804D6CAC -= 0x1E;
    } else {
        mnStageSel_804D6CAC = 0;
    }
    if (mnStageSel_804D6CAD < -0x1E) {
        mnStageSel_804D6CAD += 0x1E;
    } else if (mnStageSel_804D6CAD > 0x1E) {
        mnStageSel_804D6CAD -= 0x1E;
    } else {
        mnStageSel_804D6CAD = 0;
    }
    if (mnStageSel_804D6CA4 != 0) {
        mnStageSel_804D6CA4 -= 1;
        return;
    }
    if (mnStageSel_804D6C90->x1 == 0 && (mnStageSel_804D6CA0 & 0x200) &&
        mnStageSel_804D6CAF == 0)
    {
        lbAudioAx_80024030(0);
        gm_801A4B60();
    }
    if (mnStageSel_804D6CAF == 2) {
        mnStageSel_804D6C90->x1E_stage_id =
            mnStageSel_803F06D0[mnStageSel_804D6CAE].xB;
        gm_801A4B60();
    }
}

void mnStageSel_8025BB5C_OnLeave(UNK_T unused)
{
    struct mnStageSel_804D6C90_t* tmp;

    if (mnStageSel_804D6C94 != NULL) {
        lbArchive_80016EFC(mnStageSel_804D6C94);
        mnStageSel_804D6C94 = NULL;
    }
    tmp = mnStageSel_804D6C90;
    tmp->x4 = mnStageSel_804D6CAF == 2 ? true : false;
    if (tmp->x4) {
        PreloadCacheScene* cache = lbDvd_8001822C();
        cache->stage_id = tmp->x1E_stage_id;
        lbDvd_80018254();
    }
}

u8 mnStageSel_8025BBD4(void)
{
    return mnStageSel_803F06D0[mnStageSel_802599EC()].xB;
}

u8 mnStageSel_8025BC08(int idx)
{
    return mnStageSel_803F06D0[idx].xB;
}
