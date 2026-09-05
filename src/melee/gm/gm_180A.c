#include "gmregclear.h"
#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/tobj.h>
#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include <melee/gr/ground.h>
#include <melee/if/iftime.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lblanguage.h>
#include <melee/pl/player.h>
#include <melee/sc/types.h>

struct lbl_80472E48_t {
    /* 0x00 */ u8 b76 : 2, b54 : 2, b32 : 2, b10 : 2;
    /* 0x01 */ char pad_1[3];
    /* 0x04 */ s32 unk_4; /* inferred */
    /* 0x08 */ s32 unk_8; /* inferred */
    /* 0x0C */ u32 xC;
    /* 0x10 */ u8 x10;
    /* 0x11 */ char pad_11[3];
    /* 0x14 */ s32 x14[0x1B];
}; /* size = 0x80 */
ASSERT_SIZE(struct lbl_80472E48_t, 0x80);

static struct lbl_80472E48_t lbl_80472E48;
static s32 lbl_80472EC8[4];

static HSD_Archive* lbl_804D65C8;
static DynamicModelDesc** lbl_804D65CC;
static DynamicModelDesc** lbl_804D65D0;
static s32 lbl_804D65D4;
static s32 lbl_804D65D8;

s32 gm_80180AE4(void)
{
    return lbl_80472EC8[0] * 0xA;
}

Fighter_GObj* gm_80180AF4(void)
{
    return Player_GetEntity(1);
}

void gm_80180B18(void)
{
    int i;

    for (i = 0; i < 0x1B; i++) {
        u8 idx = gm_CKindToSelKind((u8) i);
        lbl_80472E48.x14[gm_CKindToSelKind((u8) i)] =
            (u32) *gmMainLib_8015D06C(idx) / 10;
    }
}

void gm_80180BA0(void)
{
    int i;

    for (i = 0; i < 0x1B; i++) {
        u8 idx = gm_CKindToSelKind((u8) i);
        *gmMainLib_8015D06C(gm_CKindToSelKind((u8) i)) =
            lbl_80472E48.x14[idx] * 0xA;
    }
}

void fn_80180C14(HSD_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;

    if (lbl_80472E48.b10 != 0) {
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        HSD_JObjAnimAll(jobj);
    }
}

void fn_80180C60(HSD_GObj* gobj)
{
    typedef struct fn_80180C60_state {
        struct lbl_80472E48_t e48;
        s32 ec8[4];
    } fn_80180C60_state;
    fn_80180C60_state* state = (fn_80180C60_state*) &lbl_80472E48;
    s32 d;
    s32* max_dist;
    s32 dist;
    s32 disp;
    HSD_JObj* jobj;
    u32 b76;

    dist = (s32) (0.1f * Ground_801C57F0(0));
    jobj = gobj->hsd_obj;
    if (dist < 0) {
        dist = 0;
    }

    state->ec8[0] = dist;
    b76 = state->e48.b76;

    if (b76 != 0 && state->e48.b54) {
        ifTime_HideTimers();
        if (state->ec8[0] == state->ec8[1]) {
            state->ec8[3] = state->ec8[3] + 1;
        } else {
            state->ec8[3] = 0;
        }
        if (state->ec8[3] > 0x3C) {
            state->e48.b32 = 1;
            if (dist == 0 && !state->e48.b10) {
                state->e48.b10 = 1;
            }
        }
    } else {
        if (b76 != 0) {
            ifTime_HideTimers();
            if (state->ec8[0] == state->ec8[1]) {
                state->ec8[3] = state->ec8[3] + 1;
            } else {
                state->ec8[3] = 0;
            }
            if (state->ec8[3] > 0x78) {
                state->e48.b32 = 1;
                if (!state->e48.b10) {
                    state->e48.b10 = 1;
                }
            }
        } else if (gm_8016AEEC() == 0 && gm_8016AEFC() == 0x3B) {
            state->e48.b76 = 1;
            ifTime_HideTimers();
            Player_80031790(0);
        }
        if (Ground_801C1DC0() != 0) {
            if (!state->e48.b76) {
                state->e48.b76 = 1;
                ifTime_HideTimers();
                Player_80031790(0);
            }
            if (!state->e48.b54) {
                state->e48.b54 = 1;
                Player_80031790(0);
            }
            state->ec8[3] = 0;
        }
    }

    if (!state->e48.b32) {
        HSD_JObjReqAnimAll(jobj, 0.0f);
    } else if (state->e48.b10) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    } else if (dist > state->e48.x14[gm_CKindToSelKind((u8) state->e48.unk_4)])
    {
        if (lbl_804D65D4 == 0) {
            lbAudioAx_800237A8(0x9C40, 0x7F, 0x40);
            lbAudioAx_800237A8(0x144, 0x7F, 0x40);
            gm_80167858((s32) (s8) state->e48.x10,
                        (s32) Player_GetNametagSlotID(0), 0xD, 0x5A);
            lbl_804D65D4 = 1;
        }
        HSD_JObjClearFlagsAll(
            HSD_JObjGetNext(HSD_JObjGetChild(HSD_JObjGetChild(jobj))),
            JOBJ_HIDDEN);
    }

    d = lbLang_IsSavedLanguageUS() != 0 ? (s32) ((f64) (f32) dist / 0.304788)
                                        : dist;
    disp = d;
    if (d > 0x1869F) {
        disp = 0x1869F;
    }

    /* ones digit */
    HSD_JObjReqAnimAll(HSD_JObjGetNext(HSD_JObjGetNext(
                           HSD_JObjGetChild(HSD_JObjGetChild(jobj)))),
                       (f32) (disp % 10));

    /* tens digit */
    HSD_JObjReqAnimAll(HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                           HSD_JObjGetChild(HSD_JObjGetChild(jobj))))),
                       (f32) ((disp / 10) % 10));

    /* hundreds digit */
    d = disp / 100;
    if (d != 0) {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                HSD_JObjGetNext(HSD_JObjGetChild(HSD_JObjGetChild(jobj)))))),
            (f32) (d % 10));
    } else {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                HSD_JObjGetNext(HSD_JObjGetChild(HSD_JObjGetChild(jobj)))))),
            10.0f);
    }

    /* thousands digit */
    d = disp / 1000;
    if (d != 0) {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                HSD_JObjGetNext(HSD_JObjGetChild(HSD_JObjGetChild(jobj))))))),
            (f32) (d % 10));
    } else {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                HSD_JObjGetNext(HSD_JObjGetChild(HSD_JObjGetChild(jobj))))))),
            10.0f);
    }

    /* ten-thousands digit */
    d = disp / 10000;
    if (d != 0) {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                    HSD_JObjGetChild(HSD_JObjGetChild(jobj)))))))),
            (f32) (d % 10));
    } else {
        HSD_JObjReqAnimAll(
            HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetNext(
                    HSD_JObjGetChild(HSD_JObjGetChild(jobj)))))))),
            10.0f);
    }

    HSD_JObjAnimAll(jobj);
    state->ec8[1] = state->ec8[0];
    max_dist = &state->ec8[2];
    if (state->ec8[0] > *max_dist + 0xA) {
        *max_dist = state->ec8[0];
        lbAudioAx_80023870(0xBB, 0x7F, 0x40, 0x8A);
    }
}

void fn_80181598(void)
{
    typedef struct {
        struct lbl_80472E48_t x0;
        int x80[4];
    } lbl_80472E48_with_ec8;
    lbl_80472E48_with_ec8* state = (lbl_80472E48_with_ec8*) &lbl_80472E48;
    s32* unk_4;
    s32 val;
    s32 idx;
    u32 mode;

    PAD_STACK(0x20);

    if (gm_801A4624() != 0) {
        return;
    }

    mode = state->x0.b10;

    if (mode != 0) {
        if (mode == 1) {
            lbAudioAx_800237A8(0xC0, 0x7F, 0x40);
            lbAudioAx_800237A8(0x148, 0x7F, 0x40);
            state->x0.b10 = 2;
        }
        lbl_804D65D8 += 1;
        if (lbl_804D65D8 >= 0xF0 ||
            (lbl_804D65D8 > 0x3C &&
             (HSD_PadCopyStatus[state->x0.x10].trigger & HSD_PAD_A)))
        {
            gm_8016B328();
            return;
        }
    }

    if (state->x0.b32 != 0 && ((mode = state->x0.b10, mode == 0) || mode == 3))
    {
        state->x0.xC += 1;
        if (state->x0.xC > 0x3C &&
            (state->x0.xC >= 0xF0 ||
             (HSD_PadCopyStatus[state->x0.x10].trigger & HSD_PAD_A)))
        {
            unk_4 = &state->x0.unk_4;
            idx = gm_CKindToSelKind((u8) *unk_4);
            val = state->x80[0];
            idx = (u8) idx << 2;
            state = (lbl_80472E48_with_ec8*) state->x0.x14;
            if (val > *(s32*) ((unsigned char*) state + idx)) {
                *(s32*) ((unsigned char*) state +
                         (gm_CKindToSelKind((u8) *unk_4) << 2)) = val;
            }
            gm_8016B328();
        }
    }
}

void fn_80181708(void)
{
    HSD_GObj* new_var;
    typedef struct {
        struct lbl_80472E48_t x0;
        int x80[4];
    } lbl_80472E48_with_ec8;
    HSD_JObj* jobj;
    HSD_GObj* gobj;
    lbl_80472E48_with_ec8* state = (lbl_80472E48_with_ec8*) &lbl_80472E48;

    state->x80[0] = 0;
    state->x80[1] = 0;
    state->x80[2] = 0;
    state->x80[3] = 0;
    state->x0.b76 = 0;
    state->x0.b54 = 0;
    state->x0.b32 = 0;
    state->x0.b10 = 0;
    state->x0.xC = 0;
    state->x0.x10 = (s8) Player_GetPlayerId(0);
    lbl_804D65D4 = 0;
    lbl_804D65D8 = 0;

    HSD_GObj_SetupProc(GObj_Create(0xEU, 0x11U, 0U),
                       (void (*)(HSD_GObj*)) fn_80181598, 0x15U);

    gobj = GObj_Create(0xEU, 0xFU, 0U);
    jobj = HSD_JObjLoadJoint((*lbl_804D65CC)->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xBU, 0U);
    HSD_GObj_SetupProc(gobj, fn_80180C14, 0x15U);
    gm_8016895C(jobj, *lbl_804D65CC, 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);

    gobj = (new_var = GObj_Create(0xEU, 0xFU, 0U));
    jobj = HSD_JObjLoadJoint((*lbl_804D65D0)->joint);
    HSD_GObjObject_80390A70(new_var, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(new_var, HSD_GObj_JObjCallback, 0xBU, 0U);
    HSD_GObj_SetupProc(new_var, fn_80180C60, 0x15U);
    gm_8016895C(jobj, *lbl_804D65D0, 0);
    HSD_JObjReqAnimAll(jobj, 10.0f);
    HSD_JObjAnimAll(jobj);
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    HSD_JObjSetFlagsAll(
        HSD_JObjGetNext(HSD_JObjGetChild(HSD_JObjGetChild(jobj))),
        JOBJ_HIDDEN);
    HSD_JObjClearFlagsAll(HSD_JObjGetNext(HSD_JObjGetNext(
                              HSD_JObjGetChild(HSD_JObjGetChild(jobj)))),
                          JOBJ_HIDDEN);

    gm_80168F88();
}

void gm_80181998(void)
{
    lbl_804D65C8 = lbArchive_80016DBC("IfHrNoCn", &lbl_804D65CC,
                                      "ScInfCnt_scene_models", 0);
    lbl_804D65C8 = lbArchive_80016DBC("IfHrReco", &lbl_804D65D0,
                                      "ScInfCnt_scene_models", 0);
    fn_80181708();
}

void gm_80181A00(s32 arg0, s32 arg1)
{
    lbl_80472E48.unk_4 = arg0;
    lbl_80472E48.unk_8 = arg1;
}
