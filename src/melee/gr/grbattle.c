#include "granime.h"
#include "grdisplay.h"
#include "grlib.h"
#include "grmaterial.h"
#include "ground.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "stage.h"
#include "types.h"

#include "gm/gm_16AE.h"
#include "lb/lbspdisplay.h"

#include <dolphin/gx/GXEnum.h>
#include <dolphin/mtx.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

/** @var ::grBattle_YakumonoParam::bg_curr_color_overlay
 * @todo ::ColorOverlay_x8_t, from ::grMaterial_801C9604
 * @var ::grBattle_YakumonoParam::bg_prev_color_overlay
 * @copydoc ::grBattle_YakumonoParam::bg_curr_color_overlay
 */
struct grBattle_YakumonoParam {
    int bg_curr_color_overlay;
    int bg_prev_color_overlay;
};

/* 219C98 */ static void grBattle_OnDemoInit(bool);
/* 219CA4 */ static void grBattle_OnInit(void);
/* 219D54 */ static void grBattle_OnLoad(void);
/* 219D58 */ static void grBattle_OnStart(void);
/* 219D7C */ static bool grBattle_80219D7C(void);
/* 219D84 */ static Ground_GObj* grBattle_80219D84(int gobj_id);
/* 219E6C */ static void grBattle_GObj0_Callback0(Ground_GObj* gobj);
/* 21A10C */ static bool grBattle_GObj0_Callback1(Ground_GObj* gobj);
/* 21A114 */ static void grBattle_GObj0_Callback2(Ground_GObj* gobj);
/* 21A118 */ static void grBattle_GObj0_Callback3(Ground_GObj* gobj);
/* 21A11C */ static void grBattle_GObj6_Callback0(Ground_GObj* gobj);
/* 21A16C */ static bool grBattle_GObj6_Callback1(Ground_GObj* gobj);
/* 21A174 */ static void grBattle_GObj6_Callback2(Ground_GObj* gobj);
/* 21A198 */ static void grBattle_GObj6_Callback3(Ground_GObj* gobj);
/* 21A19C */ static void grBattle_GObj5_Callback0(Ground_GObj* gobj);
/* 21A1FC */ static bool grBattle_GObj5_Callback1(Ground_GObj* gobj);
/* 21A204 */ static void grBattle_GObj5_Callback2(Ground_GObj* gobj);
/* 21A208 */ static void grBattle_GObj5_Callback3(Ground_GObj* gobj);
/* 21A20C */ static void grBattle_GObj1_Callback0(Ground_GObj* gobj);
/* 21A264 */ static bool grBattle_GObj1_Callback1(Ground_GObj* gobj);
/* 21A26C */ static void grBattle_GObj1_Callback2(Ground_GObj* gobj);
/* 21A270 */ static void grBattle_GObj1_Callback3(Ground_GObj* gobj);
/* 21A274 */ static void grBattle_GObj2_Callback0(Ground_GObj* gobj);
/* 21A2CC */ static bool grBattle_GObj2_Callback1(Ground_GObj* gobj);
/* 21A2D4 */ static void grBattle_GObj2_Callback2(Ground_GObj* gobj);
/* 21A2D8 */ static void grBattle_GObj2_Callback3(Ground_GObj* gobj);
/* 21A2DC */ static void grBattle_GObj4_Callback0(Ground_GObj* gobj);
/* 21A334 */ static bool grBattle_GObj4_Callback1(Ground_GObj* gobj);
/* 21A33C */ static void grBattle_GObj4_Callback2(Ground_GObj* gobj);
/* 21A340 */ static void grBattle_GObj4_Callback3(Ground_GObj* gobj);
/* 21A344 */ static void grBattle_BG_Callback0(Ground_GObj* gobj);
/* 21A3B4 */ static bool grBattle_BG_Callback1(Ground_GObj* gobj);
/* 21A3BC */ static void grBattle_BG_Callback2(Ground_GObj* gobj);
/* 21A60C */ static void grBattle_BG_Callback3(Ground_GObj* gobj);
/* 21A610 */ static DynamicsDesc* grBattle_OnTouchLine(enum_t);
/* 21A618 */ static bool grBattle_OnCheckShadowRender(Vec3*, int, HSD_JObj*);

/* 4D6AC8 */ static GXBool isDemoFight;
/* 4D6ACC */ static struct grBattle_YakumonoParam* yakumono_param;

static StageCallbacks grNBa_StageCallbacks[] = {
    {
        grBattle_GObj0_Callback0,
        grBattle_GObj0_Callback1,
        grBattle_GObj0_Callback2,
        grBattle_GObj0_Callback3,
        0,
    },
    {
        grBattle_GObj1_Callback0,
        grBattle_GObj1_Callback1,
        grBattle_GObj1_Callback2,
        grBattle_GObj1_Callback3,
        0,
    },
    {
        grBattle_GObj2_Callback0,
        grBattle_GObj2_Callback1,
        grBattle_GObj2_Callback2,
        grBattle_GObj2_Callback3,
        0,
    },
    {
        grBattle_BG_Callback0,
        grBattle_BG_Callback1,
        grBattle_BG_Callback2,
        grBattle_BG_Callback3,
        0,
    },
    {
        grBattle_GObj4_Callback0,
        grBattle_GObj4_Callback1,
        grBattle_GObj4_Callback2,
        grBattle_GObj4_Callback3,
        0,
    },
    {
        grBattle_GObj5_Callback0,
        grBattle_GObj5_Callback1,
        grBattle_GObj5_Callback2,
        grBattle_GObj5_Callback3,
        0,
    },
    {
        grBattle_GObj6_Callback0,
        grBattle_GObj6_Callback1,
        grBattle_GObj6_Callback2,
        grBattle_GObj6_Callback3,
        (1 << 30) | (1 << 31),
    },
};

StageData grNBa_803E7E38 = {
    BATTLE,
    grNBa_StageCallbacks,
    "/GrNBa.dat",
    grBattle_OnInit,
    grBattle_OnDemoInit,
    grBattle_OnLoad,
    grBattle_OnStart,
    grBattle_80219D7C,
    grBattle_OnTouchLine,
    grBattle_OnCheckShadowRender,
    (1 << 0),
    NULL,
    0,
};

void grBattle_OnDemoInit(bool arg0)
{
    isDemoFight = true;
}

void grBattle_OnInit(void)
{
    yakumono_param = Ground_GetYakumonoParam();
    stage_info.unk8C.b4 = 1;
    stage_info.unk8C.b5 = 1;

    grBattle_80219D84(0);
    if (gm_8016B3D8() || Stage_80225194() == 273 || Stage_80225194() == 245) {
        grBattle_80219D84(5);
    } else {
        grBattle_80219D84(3);
        grBattle_80219D84(1);
    }
    grBattle_80219D84(6);
    Ground_801C39C0();
    Ground_801C3BB4();
    grLib_801C9A10();
    isDemoFight = 0;
}

void grBattle_OnLoad(void) {}

void grBattle_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grBattle_80219D7C(void)
{
    return false;
}

Ground_GObj* grBattle_80219D84(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grNBa_StageCallbacks[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
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
            HSD_GObj_SetupProc(gobj, callbacks->callback2, 4);
        }

    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 232, gobj_id);
    }

    return gobj;
}

void grBattle_GObj0_Callback0(Ground_GObj* gobj)
{
    Vec3 v;
    Ground* gp = GET_GROUND(gobj);

    grAnime_801C8138(gobj, gp->map_id, 0);

    if (isDemoFight) {
        grLib_801C9A70(0, &v);
        HSD_JObjSetTranslate(Ground_801C2CF4(0), &v);

        grLib_801C9A70(1, &v);
        HSD_JObjSetTranslate(Ground_801C2CF4(1), &v);

        grLib_801C9A70(2, &v);
        HSD_JObjSetTranslate(Ground_801C2CF4(2), &v);

        grLib_801C9A70(3, &v);
        HSD_JObjSetTranslate(Ground_801C2CF4(3), &v);
    }
}

bool grBattle_GObj0_Callback1(Ground_GObj* arg0)
{
    return false;
}

void grBattle_GObj0_Callback2(Ground_GObj* arg0) {}

void grBattle_GObj0_Callback3(Ground_GObj* arg0) {}

void grBattle_GObj6_Callback0(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grBattle_GObj6_Callback1(Ground_GObj* arg0)
{
    return false;
}

void grBattle_GObj6_Callback2(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

void grBattle_GObj6_Callback3(Ground_GObj* arg0) {}

void grBattle_GObj5_Callback0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    Ground_JObjInline1(gobj);
    gp->x11_flags.b012 = 2;
}

bool grBattle_GObj5_Callback1(Ground_GObj* gobj)
{
    return false;
}

void grBattle_GObj5_Callback2(Ground_GObj* gobj) {}

void grBattle_GObj5_Callback3(Ground_GObj* gobj) {}

void grBattle_GObj1_Callback0(Ground_GObj* gobj)
{
    /// @todo ::grBattle_GObj5_Callback0
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    grAnime_801C8138(gobj, gp->map_id, 0);
    grMaterial_801C94D8(jobj);
    gp->x11_flags.b012 = 2;
}

bool grBattle_GObj1_Callback1(Ground_GObj* gobj)
{
    return false;
}

void grBattle_GObj1_Callback2(Ground_GObj* gobj) {}

void grBattle_GObj1_Callback3(Ground_GObj* gobj) {}

static void setup_unk_gobj(Ground_GObj* gobj)
{
    HSD_JObj* jobj;
    Ground* gp = GET_GROUND(gobj);
    jobj = GET_JOBJ(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grMaterial_801C94D8(jobj);
    gp->x11_flags.b012 = 2;
}

void grBattle_GObj2_Callback0(Ground_GObj* gobj)
{
    setup_unk_gobj(gobj);
}

bool grBattle_GObj2_Callback1(Ground_GObj* gobj)
{
    return false;
}

void grBattle_GObj2_Callback2(Ground_GObj* gobj) {}

void grBattle_GObj2_Callback3(Ground_GObj* gobj) {}

void grBattle_GObj4_Callback0(Ground_GObj* gobj)
{
    setup_unk_gobj(gobj);
}

bool grBattle_GObj4_Callback1(Ground_GObj* gobj)
{
    return false;
}

void grBattle_GObj4_Callback2(Ground_GObj* gobj) {}

void grBattle_GObj4_Callback3(Ground_GObj* gobj) {}

inline void reset_bg_timer(Ground* gp)
{
    gp->u.battle_bg.timer = HSD_Randi(1200) + 2400;
}

enum grBattle_BG_State {
    BG_Waiting,
    BG_Transitioning,
    BG_Done,
};

void grBattle_BG_Callback0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    PAD_STACK(4 * 4);
    gp->x11_flags.b012 = 2;
    gp->u.battle_bg.state = BG_Waiting;
    reset_bg_timer(gp);
    gp->u.battle_bg.curr = -1;
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
}

bool grBattle_BG_Callback1(Ground_GObj* arg0)
{
    return false;
}

void grBattle_BG_Callback2(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_GObj* bg_gobj;
    int bg_idx;
    s16 indices[] = { 1, 2, 4 };
    size_t const BATTLE_BG_MAX = ARRAY_SIZE(indices);
    PAD_STACK(4 * 5);

    switch (gp->u.battle_bg.state) {
    case BG_Waiting:
        if (gp->u.battle_bg.timer-- < 0) {
            gp->u.battle_bg.state = BG_Transitioning;
            grAnime_801C8138(gobj, gp->map_id, 0);
        }
        break;

    case BG_Transitioning:
        if (HSD_JObjGetFlags(jobj) & JOBJ_HIDDEN) {
            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        }
        if (grAnime_801C83D0(gobj, 0, 7)) {
            if (gp->u.battle_bg.curr == -1) {
                int i;
                for (i = 0; i < BATTLE_BG_MAX; i++) {
                    if (Ground_801C2BA4(indices[i])) {
                        gp->u.battle_bg.curr = indices[i];
                        break;
                    }
                }
                HSD_ASSERT(527, i<BATTLE_BG_MAX);
            }

            // Pick a random different background to transition to
            gp->u.battle_bg.prev = gp->u.battle_bg.curr;
            do {
                bg_idx = indices[HSD_Randi(BATTLE_BG_MAX)];
            } while ((gp->u.battle_bg.curr = bg_idx) == gp->u.battle_bg.prev);

            bg_gobj = Ground_801C2BA4(gp->u.battle_bg.prev);
            HSD_ASSERT(535, bg_gobj);
            grMaterial_801C9604(bg_gobj, yakumono_param->bg_prev_color_overlay,
                                0);

            bg_gobj = grBattle_80219D84(gp->u.battle_bg.curr);
            HSD_ASSERT(539, bg_gobj);
            grMaterial_801C9604(bg_gobj, yakumono_param->bg_curr_color_overlay,
                                0);

            gp->u.battle_bg.state = BG_Done;
        }
        break;

    case BG_Done:
        bg_gobj = Ground_801C2BA4(gp->u.battle_bg.prev);
        HSD_ASSERT(546, bg_gobj);
        if (grLib_801C96E8(bg_gobj)) {
            Ground_801C4A08(bg_gobj);
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
            gp->u.battle_bg.state = BG_Waiting;
            reset_bg_timer(gp);
        }
        break;
    }
}

void grBattle_BG_Callback3(Ground_GObj* gobj) {}

DynamicsDesc* grBattle_OnTouchLine(enum_t arg0)
{
    return NULL;
}

bool grBattle_OnCheckShadowRender(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
