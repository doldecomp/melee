#include <platform.h>

#include "gmmain_lib.h"

#include "db/db_2253.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardgame.h"
#include "lb/lbdvd.h"
#include "lb/lblanguage.h"
#include "lb/lbmthp.h"
#include "ty/toy.h"
#include "un/un_2FC9.h"

#include <placeholder.h>
#include <dolphin/dvd/dvd.h>
#include <dolphin/os/OSRtc.h>
#include <dolphin/vi/vi.h>
#include <baselib/controller.h>
#include <baselib/devcom.h>
#include <baselib/video.h>

typedef struct MinorScene MinorScene;

struct MinorScene {
    u8 idx;
    u8 preload;
    u16 flags;

    void (*Prep)(MinorScene*);
    void (*Decide)(MinorScene*);

    u8 class_id;

    void* unk_struct_0;
    void* unk_struct_1;
};

typedef struct {
    u8 preload;
    u8 idx;

    void (*Load)(void);
    void (*Unload)(void);
    void (*Init)(void);

    MinorScene* minor_scenes;
} MajorScene; // 803DACA4

void gm_801A4014(MajorScene* scene);

typedef struct _MinorSceneHandler {
    u8 class_id;

    void (*OnFrame)(void);
    void (*OnLoad)(u32);
    void (*OnLeave)(u32);
    void (*unk_func)(void);
} MinorSceneHandler; // 803DA920

extern struct {
    int x0, x4, x8;
} gmMainLib_8046B0F0;

typedef struct {
    u8 curr_major;
    u8 pending_major;
    u8 prev_major;
    u8 curr_minor;
    u8 prev_minor;
    u8 pending_minor;
} SceneNums;

typedef struct {
    SceneNums nums;
    SceneNums nums2;
    u8 pending;
    u8 x0D;
    u8 x0E;
    u8 x0F;
    void* data;
} GameState; // 80479D30
STATIC_ASSERT(sizeof(GameState) == 0x14);

/* 1A3EF4 */ static void gm_801A3EF4(void);
/* 1A3F48 */ static void gm_801A3F48(MinorScene*);
/* 1A4284 */ static UNK_T gm_801A4284(UNK_T);
/* 1A42F8 */ static void gm_801A42F8(int);
/* 1A4310 */ static UNK_RET gm_800A4310(UNK_PARAMS);
/* 1A4330 */ void gm_801A4330(void*);
/* 1A4B88 */ static void gm_801A4B88(void*);
/* 1A4BD4 */ static void gm_801A4BD4(void);
/* 1A4CE0 */ static MinorSceneHandler* gm_801A4CE0(u8);
/* 1A4D34 */ static void gm_801A4D34(void*);
/* 1A50AC */ static MajorScene* gm_801A50AC(void);

static GameState gm_80479D30;

inline u8 matchMinor(MinorScene* scenes)
{
    u8 i;
    for (i = 0; i != 255; i++) {
        if (scenes[i].idx > gm_80479D30.nums.curr_minor) {
            return scenes[i].idx;
        }
    }
    return 0;
}

void gm_801A4014(MajorScene* scene)
{
    MinorScene* temp_r5;
    MinorScene* var_r27;
    MinorScene* var_r6;
    int var_ctr;
    int var_r3;
    int* temp_r30;
    int temp_r0;
    u8 var_r3_3;
    int var_r4;
    struct {
        u32 x0, x4, x8;
    }* temp_r25;
    MinorSceneHandler* temp_r26;
    u32 unused;

    var_r4 = gm_80479D30.nums.curr_minor;
#if 0
    gm_80479D30.nums.curr_minor = matchMinor(scene->minor_scenes);
#else
    temp_r5 = scene->minor_scenes;
    var_ctr = 0xFF - var_r4;
    if (var_r4 < 0xFF) {
    loop_1:
        var_r6 = temp_r5;
        var_r3 = 0;
        while (var_r3 < 0xFF) {
            if (var_r6->idx == 0xFF) {
                var_r4 += 1;
                goto loop_1;
            }
            if (var_r4 == var_r6->idx) {
                var_r27 = &temp_r5[var_r3];
                goto good;
            }
            var_r6 += 1;
            var_r3 += 1;
        }
    }
    var_r27 = NULL;
good:
    gm_80479D30.nums.curr_minor = (u8) var_r27->idx;
#endif
    gm_801A3F48(var_r27);
    if (var_r27->Prep != NULL) {
        var_r27->Prep(var_r27);
    }
    temp_r25 = (void*) var_r27;
    temp_r26 = gm_801A4CE0(var_r27->class_id);
    gm_801A4BD4();
    gm_801A4B88(temp_r25);
    if (temp_r26->OnLoad != NULL) {
        temp_r26->OnLoad(temp_r25->x4);
    }
    gm_801A4D34(temp_r26->OnFrame);
    temp_r30 = &gmMainLib_8046B0F0.x4;
    if (*temp_r30 == 0 && temp_r26->OnLeave != NULL) {
        temp_r26->OnLeave(temp_r25->x8);
    }
    if (*temp_r30 == 0) {
        if (var_r27->Decide != NULL) {
            var_r27->Decide(var_r27);
        }
        gm_80479D30.nums.prev_minor = gm_80479D30.nums.curr_minor;
        if (gm_80479D30.nums.pending_minor) {
            gm_80479D30.nums.curr_minor = gm_80479D30.nums.pending_minor - 1;
            gm_80479D30.nums.pending_minor = 0;
        } else {
            gm_80479D30.nums.curr_minor = matchMinor(scene->minor_scenes);
        }
    }
    lb_8001CDB4();
    lb_8001B760(0xB);
    lbMthp_8001F800();
    if (*temp_r30 != 0) {
        lbAudioAx_80027DBC();
        HSD_PadReset();
        while (lb_8001B6F8() == 0xB)
            ;
        if (DVDCheckDisk() == 0) {
            OSResetSystem(1, 0, 0);
        }
        lbMthp_8001F800();
        while (HSD_DevComIsBusy(1) != 0)
            ;
        gmMainLib_8015FBA4();
        gm_801A50AC();
        lb_8000C160(&gm_80479D30, 0x14);
        gm_801A3EF4();
        gmMainLib_8046B0F0.x0 = 1;
        gm_801A42F8(0x28);
        HSD_VISetBlack(0);
    }
}

u8 gm_801A4310(void)
{
    return ((u8*) &gm_80479D30)[0];
}

inline MajorScene* findSceneMatching(u8 idx)
{
    MajorScene* cur;
    for (cur = gm_801A50AC(); cur->idx != 45; cur++) {
        if (cur->idx == idx) {
            return cur;
        }
    }
    return NULL;
}

u8 gm_801A43A0(u8 arg0)
{
    u8 temp_r3;
    MajorScene* var_r30;
    MajorScene* var_r3_2;
    GameState* gamestate = &gm_80479D30;
    u64 unused;

    var_r30 = findSceneMatching(arg0);

    gm_80479D30.pending = 0;
    gm_80479D30.nums.curr_minor = 0;
    gm_80479D30.nums.prev_minor = 0;
    gm_80479D30.nums.pending_minor = 0;
    lbDvd_80018F58(var_r30->preload);
    if (var_r30->Load != NULL) {
        var_r30->Load();
    }
    while (!gamestate->pending) {
        if (gm_80479D30.data != NULL &&
            (temp_r3 = (*(u8(*)(void)) gm_80479D30.data)(), temp_r3 != 45))
        {
            gm_80479D30.nums2 = gm_80479D30.nums;
            gamestate->pending = 0;
            gamestate->nums.curr_minor = 0;
            gamestate->nums.prev_minor = 0;
            gamestate->nums.pending_minor = 0;

            var_r3_2 = findSceneMatching(temp_r3);

            gm_801A4014(var_r3_2);
            if (gmMainLib_8046B0F0.x4 == 0) {
                gm_80479D30.nums = gm_80479D30.nums2;
            }
        } else {
            gm_801A4014(var_r30);
        }
    }
    if (gmMainLib_8046B0F0.x4 == 0 && var_r30->Unload != NULL) {
        var_r30->Unload();
    }
    return gm_80479D30.nums.pending_major;
}

// UnclePunch: Scene_Main
void gm_801A4510(void)
{
    u32 unused;
    MajorScene* major_scenes;
    GameState* gamestate = &gm_80479D30;
    int i;

    gm_801A50AC();
    lb_8000C160(&gm_80479D30, sizeof(GameState));
    major_scenes = gm_801A50AC();
    for (i = 0; major_scenes[i].idx != 0x2D; i++) {
        if (major_scenes[i].Init != NULL) {
            major_scenes[i].Init();
        }
    }
    if (VIGetDTVStatus() != NULL &&
        (db_804D6B30 & 0x200 || OSGetProgressiveMode() == 1))
    {
        gm_80479D30.nums.curr_major = 0x27;
    } else {
        gm_80479D30.nums.curr_major = 0x28;
    }
    gm_80479D30.nums.prev_major = 0x2D;

    while (true) {
        u8 major = gm_801A43A0(gm_80479D30.nums.curr_major);
        if (gmMainLib_8046B0F0.x4 != 0) {
            gmMainLib_8046B0F0.x4 = 0;
        }
        gamestate->nums.prev_major = gamestate->nums.curr_major;
        gamestate->nums.curr_major = major;
    }
}

enum {
    TROPHY_PIKMIN = 0x113,
};

enum {
    LANG_JP = 0,
};

void gm_801BF9A8(void* data)
{
    struct {
        u32 a;
        u8 scene_id;
    }* scene_data;

    scene_data = gm_801A4284(data);

    if (!un_803048C0(TROPHY_PIKMIN)) {
        if (!lb_8001C2D8(0, "01",
                         lbLang_GetLanguageSetting() == LANG_JP ? "GPIJ"
                                                                : "GPIE",
                         "Pikmin dataFile"))
        {
            un_803124BC();
            Trophy_SetUnlockState(TROPHY_PIKMIN, true);
        }
    }

    // Set scene exit callback?
    gm_801A4330(&lb_8001CE78);

    // Enter major scene
    // Gekko "boot to CSS" code changes scene_id to a hardcoded 2
    gm_801A42F8(scene_data->scene_id);
}
