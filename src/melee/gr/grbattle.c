#include <platform.h>

#include "lb/forward.h"

#include "gr/grbattle.h"

#include "gm/gm_1601.h"
#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/inlines.h"
#include "gr/grzakogenerator.h"
#include "gr/stage.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/debug.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

static void grBattle_80219C98(int);
static void grBattle_80219CA4(void);
static void grBattle_80219D54(void);
static void grBattle_80219D58(void);
static bool grBattle_80219D7C(void);
static HSD_GObj* grBattle_80219D84(int gobj_id);
static void grBattle_80219E6C(HSD_GObj*);
static void grBattle_8021A114(HSD_GObj*);
static void grBattle_8021A118(HSD_GObj*);
static void grBattle_8021A11C(HSD_GObj*);
static bool grBattle_8021A16C(HSD_GObj*);
static void grBattle_8021A174(HSD_GObj*);
static void grBattle_8021A198(HSD_GObj*);
static void grBattle_8021A19C(HSD_GObj*);
static bool grBattle_8021A1FC(HSD_GObj*);
static void grBattle_8021A204(HSD_GObj*);
static void grBattle_8021A208(HSD_GObj*);
static void grBattle_8021A20C(HSD_GObj*);
static bool grBattle_8021A264(HSD_GObj*);
static void grBattle_8021A26C(HSD_GObj*);
static void grBattle_8021A270(HSD_GObj*);
static void grBattle_8021A274(HSD_GObj*);
static bool grBattle_8021A2CC(HSD_GObj*);
static void grBattle_8021A2D4(HSD_GObj*);
static void grBattle_8021A2D8(HSD_GObj*);
static void grBattle_8021A2DC(HSD_GObj*);
static bool grBattle_8021A334(HSD_GObj*);
static void grBattle_8021A33C(HSD_GObj*);
static void grBattle_8021A340(HSD_GObj*);
static void grBattle_8021A344(HSD_GObj*);
static bool grBattle_8021A3B4(HSD_GObj*);
static void grBattle_8021A3BC(HSD_GObj*);
static void grBattle_8021A60C(HSD_GObj*);
static DynamicsDesc* grBattle_8021A610(enum_t);
static bool grBattle_8021A618(Vec3*, int, HSD_JObj*);

extern StageInfo stage_info;

struct {
    int unk0;
    int unk4;
}* grNBa_804D6ACC;

static u8 grNBa_804D6AC8;

static StageCallbacks grNBa_803E7DA0[7] = {
    {
        grBattle_80219E6C,
        grBattle_8021A10C,
        grBattle_8021A114,
        grBattle_8021A118,
        0,
    },
    {
        grBattle_8021A20C,
        grBattle_8021A264,
        grBattle_8021A26C,
        grBattle_8021A270,
        0,
    },
    {
        grBattle_8021A274,
        grBattle_8021A2CC,
        grBattle_8021A2D4,
        grBattle_8021A2D8,
        0,
    },
    {
        grBattle_8021A344,
        grBattle_8021A3B4,
        grBattle_8021A3BC,
        grBattle_8021A60C,
        0,
    },
    {
        grBattle_8021A2DC,
        grBattle_8021A334,
        grBattle_8021A33C,
        grBattle_8021A340,
        0,
    },
    {
        grBattle_8021A19C,
        grBattle_8021A1FC,
        grBattle_8021A204,
        grBattle_8021A208,
        0,
    },
    {
        grBattle_8021A11C,
        grBattle_8021A16C,
        grBattle_8021A174,
        grBattle_8021A198,
        0xC0000000,
    },
};

/// @todo Not ideal @c clang-format behavior.
/// Removing the trailing comma is arguably worse.
StageData grNBa_803E7E38 = {
    0x00000024,
    grNBa_803E7DA0,
    "/GrNBa.dat",
    grBattle_80219CA4,
    grBattle_80219C98,
    grBattle_80219D54,
    grBattle_80219D58,
    grBattle_80219D7C,
    grBattle_8021A610,
    grBattle_8021A618,
    0x00000001,
    NULL,
    0,
};

static void grBattle_80219C98(int arg0)
{
    grNBa_804D6AC8 = 1;
}

static void grBattle_80219CA4(void)
{
    grNBa_804D6ACC = Ground_801C49F8();
    stage_info.unk8C.b4 = 1;
    stage_info.unk8C.b5 = 1;

    grBattle_80219D84(0);
    if (gm_8016B3D8() || Stage_80225194() == 0x111 || Stage_80225194() == 0xF5)
    {
        grBattle_80219D84(5);
    } else {
        grBattle_80219D84(3);
        grBattle_80219D84(1);
    }
    grBattle_80219D84(6);
    Ground_801C39C0();
    Ground_801C3BB4();
    grLib_801C9A10();
    grNBa_804D6AC8 = 0;
}

static void grBattle_80219D54(void) {}

static void grBattle_80219D58(void)
{
    grZakoGenerator_801CAE04(false);
}

static bool grBattle_80219D7C(void)
{
    return false;
}

static HSD_GObj* grBattle_80219D84(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grNBa_803E7DA0[gobj_id];

    gobj = Ground_801C14D0(gobj_id);

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
            HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 4);
        }

    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 232, gobj_id);
    }

    return gobj;
}

static void grBattle_80219E6C(HSD_GObj* gobj)
{
    Vec3 v;
    Ground* gp = gobj->user_data;
    enum_t id = gp->map_id;

    grAnime_801C8138(gobj, id, 0);

    if (grNBa_804D6AC8 == 0) {
        return;
    }

    grLib_801C9A70(0, &v);
    HSD_JObjSetTranslate(Ground_801C2CF4(0), &v);

    grLib_801C9A70(1, &v);
    HSD_JObjSetTranslate(Ground_801C2CF4(1), &v);

    grLib_801C9A70(2, &v);
    HSD_JObjSetTranslate(Ground_801C2CF4(2), &v);

    grLib_801C9A70(3, &v);
    HSD_JObjSetTranslate(Ground_801C2CF4(3), &v);
}

bool grBattle_8021A10C(HSD_GObj* arg0)
{
    return false;
}

static void grBattle_8021A114(HSD_GObj* arg0) {}

static void grBattle_8021A118(HSD_GObj* arg0) {}

static void grBattle_8021A11C(HSD_GObj* gobj)
{
    u8 _[8];

    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grBattle_8021A16C(HSD_GObj* arg0)
{
    return false;
}

static void grBattle_8021A174(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

static void grBattle_8021A198(HSD_GObj* arg0) {}

static void grBattle_8021A19C(HSD_GObj* gobj)
{
    u8 _[8];

    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

static bool grBattle_8021A1FC(HSD_GObj* arg0)
{
    return false;
}

static void grBattle_8021A204(HSD_GObj* arg0) {}

static void grBattle_8021A208(HSD_GObj* arg0) {}

static void grBattle_8021A20C(HSD_GObj* gobj)
{
    u8 _[8];

    Ground* gp = gobj->user_data;

    /// @todo Missing cast
    UNK_T hsd_obj = gobj->hsd_obj;

    grAnime_801C8138(gobj, gp->map_id, 0);
    grMaterial_801C94D8(hsd_obj);
    gp->x11_flags.b012 = 2;
}

static bool grBattle_8021A264(HSD_GObj* arg0)
{
    return false;
}

static void grBattle_8021A26C(HSD_GObj* arg0) {}

static void grBattle_8021A270(HSD_GObj* arg0) {}

static void grBattle_8021A274(HSD_GObj* gobj)
{
    u8 _[8];

    Ground* gp = gobj->user_data;
    void* hsd_obj = gobj->hsd_obj;
    grAnime_801C8138(gobj, gp->map_id, 0);
    grMaterial_801C94D8(hsd_obj);
    gp->x11_flags.b012 = 2;
}

static bool grBattle_8021A2CC(HSD_GObj* arg0)
{
    return false;
}

static void grBattle_8021A2D4(HSD_GObj* arg0) {}

static void grBattle_8021A2D8(HSD_GObj* arg0) {}

static void grBattle_8021A2DC(HSD_GObj* gobj)
{
    u8 _[8];

    Ground* gp = gobj->user_data;
    void* hsd_obj = gobj->hsd_obj;
    grAnime_801C8138(gobj, gp->map_id, 0);
    grMaterial_801C94D8(hsd_obj);
    gobj;
    gp->x11_flags.b012 = 2;
}

static bool grBattle_8021A334(HSD_GObj* arg0)
{
    return false;
}

static void grBattle_8021A33C(HSD_GObj* arg0) {}

static void grBattle_8021A340(HSD_GObj* arg0) {}

static inline void reset_bg_timer(Ground* gp)
{
    gp->u.battle.bg_timer = HSD_Randi(1200) + 2400;
}

enum {
    BG_Waiting,
    BG_Transitioning,
    BG_Done,
};

static void grBattle_8021A344(HSD_GObj* gobj)
{
    u8 _[16];

    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    gp->x11_flags.b012 = 2;
    gp->u.battle.bg_state = BG_Waiting;
    reset_bg_timer(gp);
    gp->u.battle.curr_bg = -1;
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
}

static bool grBattle_8021A3B4(HSD_GObj* arg0)
{
    return false;
}

static void grBattle_8021A3BC(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_GObj* bg_gobj;
    int bg_idx;
    s16 sp28[] = { 1, 2, 4 };

#define BATTLE_BG_MAX ARRAY_SIZE(sp28)

    u8 _[20];

    switch (gp->u.battle.bg_state) {

    case BG_Waiting:
        if (gp->u.battle.bg_timer-- < 0) {
            gp->u.battle.bg_state = BG_Transitioning;
            grAnime_801C8138(gobj, gp->map_id, 0);
        }
        break;

    case BG_Transitioning:
        if (HSD_JObjGetFlags(jobj) & JOBJ_HIDDEN) {
            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        }
        if (grAnime_801C83D0(gobj, 0, 7)) {
            if (gp->u.battle.curr_bg == -1) {
                int i;
                for (i = 0; i < BATTLE_BG_MAX; i++) {
                    if (Ground_801C2BA4(sp28[i])) {
                        gp->u.battle.curr_bg = sp28[i];
                        break;
                    }
                }
                HSD_ASSERT(527, i<BATTLE_BG_MAX);
            }

            // Pick a random different background to transition to
            gp->u.battle.prev_bg = gp->u.battle.curr_bg;
            do {
                bg_idx = sp28[HSD_Randi(BATTLE_BG_MAX)];
            } while ((gp->u.battle.curr_bg = bg_idx) == gp->u.battle.prev_bg);

            bg_gobj = Ground_801C2BA4(gp->u.battle.prev_bg);
            HSD_ASSERT(535, bg_gobj);
            grMaterial_801C9604(bg_gobj, grNBa_804D6ACC->unk4, 0);

            bg_gobj = grBattle_80219D84(gp->u.battle.curr_bg);
            HSD_ASSERT(539, bg_gobj);
            grMaterial_801C9604(bg_gobj, grNBa_804D6ACC->unk0, 0);

            gp->u.battle.bg_state = BG_Done;
        }
        break;

    case BG_Done:
        bg_gobj = Ground_801C2BA4(gp->u.battle.prev_bg);
        HSD_ASSERT(546, bg_gobj);
        if (grLib_801C96E8(bg_gobj)) {
            Ground_801C4A08(bg_gobj);
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
            gp->u.battle.bg_state = BG_Waiting;
            reset_bg_timer(gp);
        }
        break;
    }
}

static void grBattle_8021A60C(HSD_GObj* arg0) {}

static DynamicsDesc* grBattle_8021A610(enum_t arg0)
{
    return NULL;
}

static bool grBattle_8021A618(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
