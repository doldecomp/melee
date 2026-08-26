#include "gmboot.h"

#include <melee/gm/gm_unsplit.h>
#include <melee/gm/types.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lblanguage.h>
#include <melee/ty/toy.h>

/* 1BF948 */ static void bootOnLoad(GameScene*);
/* 1BF9A8 */ static void bootOnLeave(GameScene*);
/* 1BFA3C */ static void memcardOnLoad(GameScene*);

/// @todo Move to toy header
enum {
    TROPHY_PIKMIN = 275,
};

struct loadData {
    u32 x0;
    u8 x4;
    u8 mode_id; ///< Copied to ::leaveData::mode_id to set next mode
};

struct leaveData {
    u32 x0;
    u8 mode_id;
};

static struct loadData load_data;
static struct leaveData leave_data;

GameScene gmBoot_BootScenes[] = {
    {
        0,
        1,
        0,
        bootOnLoad,
        bootOnLeave,
        GS_MEMCARD,
        &load_data,
        &leave_data,
    },
    {
        -1,
    },
};

void bootOnLoad(GameScene* scene)
{
    struct loadData* scene_data = gm_GetGameSceneLoadData(scene);
    scene_data->x4 = 0;
    scene_data->x0 = 0;
    scene_data->mode_id = GM_TITLE;
}

void bootOnLeave(GameScene* data)
{
    struct leaveData* scene_data = gm_GetGameSceneLeaveData(data);

    if (!Toy_803048C0(TROPHY_PIKMIN)) {
        if (!lb_8001C2D8(0, "01",
                         lbLang_GetLanguageSetting() == LANG_JP ? "GPIJ"
                                                                : "GPIE",
                         "Pikmin dataFile"))
        {
            Toy_803124BC();
            Toy_SetUnlockState(TROPHY_PIKMIN, true);
        }
    }

    // Set scene exit callback?
    gm_801A4330(lb_8001CE78);

    // Enter mode
    // Gekko "boot to CSS" code changes scene_id to a hardcoded 2
    gm_ChangeGameModeAfterCurrentScene(scene_data->mode_id);
}

GameScene gmBoot_MemCardScenes[] = {
    {
        0,
        3,
        0,
        memcardOnLoad,
        NULL,
        {
            GS_MEMCARD,
            &load_data,
            &leave_data,
        },
    },
    { -1 },
};

void memcardOnLoad(GameScene* scene)
{
    struct loadData* temp_r3 = gm_GetGameSceneLoadData(scene);
    temp_r3->x4 = 0;
    temp_r3->x0 = 1;
}
