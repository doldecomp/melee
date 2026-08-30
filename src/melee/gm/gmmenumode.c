#include "gm/gm_1A3F.h"
#include "if/soundtest.h"

#include "lb/forward.h"

#include "melee/gm/gm_unsplit.h"
#include "melee/gm/gmmain_lib.h"
#include "melee/gm/types.h"
#include "melee/lb/lbcardgame.h"
#include "melee/lb/lbcardnew.h"
#include "melee/lb/lbdvd.h"
#include "melee/lb/lbsnap.h"
#include "melee/mn/mngallery.h"
#include "melee/mn/types.h"
#include "mn/mnsnap.h"

#include <sysdolphin/baselib/memory.h>

struct DebugSoundTestData {
    struct SoundTestData* x0;
    u32 x4;
};

/* 1B0FB8 */ static void onEnterDebug(GameModeState*);
/* 1B0FF8 */ static void onEnter(GameModeState*);
/* 1B138C */ static void onExit(GameModeState*);
/* 4D68B0 */ static struct DebugSoundTestData debug_enter_data;
/* 4D68B8 */ static MenuEnterData* enter_data;
/* 4D68BC */ static MenuExitData* exit_data;

GameModeState gm_Mode_DebugMenu_States[] = {
    {
        0,
        lbDvdPreload_2,
        0,
        onEnterDebug,
        NULL,
        {
            GS_DEBUG_MENU,
            &debug_enter_data,
            NULL,
        },
    },
    { -1 },
};

GameModeState gm_Mode_Menu_States[] = {
    {
        0,
        lbDvdPreload_2,
        0,
        onEnter,
        onExit,
        {
            GS_MENU,
            &enter_data,
            &exit_data,
        },
    },
    { -1 },
};

void onEnterDebug(GameModeState* arg0)
{
    struct DebugSoundTestData* data;

    data = gm_GetGameSceneLoadData(arg0);
    data->x0 = (struct SoundTestData*) &un_803F9FA4;
    data->x4 = 0;
    un_802FF7DC();
    un_802FF884("/audio");
}

void onEnter(GameModeState* scene)
{
    GameRules* rules;
    MenuEnterData* data;
    GameModeKind previous_mode;

    data = scene->info.enter_data;
    lb_8001C550();
    lb_8001D164(0);
    lbSnap_8001E218(HSD_MemAlloc(lbSnap_8001E204()),
                    HSD_MemAlloc(lbSnap_8001E210()));
    {
        ssize_t i;
        for (i = 0; i < (signed) ARRAY_SIZE(mnSnap_804A0B90); i++) {
            mnSnap_804A0B90[i] =
                HSD_MemAlloc(sizeof(struct mnSnap_804A0B90_t));
        }
    }
    lbDvd_80018C6C();
    lbDvd_8001823C();
    lbDvd_80018254();
    mnGallery_80258940();
    rules = gmMainLib_GetGameRules();
    if (rules->force_main_menu != 0) {
        rules->force_main_menu = 0;
        data->menu_kind = MENU_KIND_MAIN;
        data->hovered_selection = SEL_MAIN_1P;
        data->load_assets = 1;
        return;
    }
    data->load_assets = 1;
    previous_mode = gm_GetPreviousGameMode();
    if (previous_mode == GM_CHALLENGER_APPROACH) {
        previous_mode = gm_801737D8();
    }
    switch (previous_mode) {
    case GM_CLASSIC:
        data->menu_kind = MENU_KIND_REG;
        data->hovered_selection = SEL_REG_CLASSIC;
        return;
    case GM_ADVENTURE:
        data->menu_kind = MENU_KIND_REG;
        data->hovered_selection = SEL_REG_ADVENTURE;
        return;
    case GM_ALLSTAR:
        data->menu_kind = MENU_KIND_REG;
        data->hovered_selection = SEL_REG_ALLSTAR;
        return;
    case GM_CLASSIC_GOVER:
        data->menu_kind = MENU_KIND_REG;
        data->hovered_selection = SEL_REG_CLASSIC;
        return;
    case GM_ADVENTURE_GOVER:
        data->menu_kind = MENU_KIND_REG;
        data->hovered_selection = SEL_REG_ADVENTURE;
        return;
    case GM_ALLSTAR_GOVER:
        data->menu_kind = MENU_KIND_REG;
        data->hovered_selection = SEL_REG_ALLSTAR;
        return;
    case GM_EVENT:
        data->menu_kind = MENU_KIND_EVENT;
        data->hovered_selection = 0;
        return;
    case GM_TARGET_TEST:
        data->menu_kind = MENU_KIND_STADIUM;
        data->hovered_selection = SEL_STADIUM_TARGET;
        return;
    case GM_10MAN_VS:
        data->menu_kind = MENU_KIND_MULTI_VS;
        data->hovered_selection = SEL_MULTI_VS_10MAN;
        return;
    case GM_100MAN_VS:
        data->menu_kind = MENU_KIND_MULTI_VS;
        data->hovered_selection = SEL_MULTI_VS_100MAN;
        return;
    case GM_3MIN_VS:
        data->menu_kind = MENU_KIND_MULTI_VS;
        data->hovered_selection = SEL_MULTI_VS_3MIN;
        return;
    case GM_15MIN_VS:
        data->menu_kind = MENU_KIND_MULTI_VS;
        data->hovered_selection = SEL_MULTI_VS_15MIN;
        return;
    case GM_ENDLESS_VS:
        data->menu_kind = MENU_KIND_MULTI_VS;
        data->hovered_selection = SEL_MULTI_VS_ENDLESS;
        return;
    case GM_CRUEL_VS:
        data->menu_kind = MENU_KIND_MULTI_VS;
        data->hovered_selection = SEL_MULTI_VS_CRUEL;
        return;
    case GM_HOME_RUN_CONTEST:
        data->menu_kind = MENU_KIND_STADIUM;
        data->hovered_selection = SEL_STADIUM_HOMERUN;
        return;
    case GM_TRAINING:
        data->menu_kind = MENU_KIND_1P;
        data->hovered_selection = SEL_1P_TRAINING;
        return;
    case GM_VS:
        data->menu_kind = MENU_KIND_VS;
        data->hovered_selection = SEL_VS_MELEE;
        return;
    case GM_TOURNAMENT:
        data->menu_kind = MENU_KIND_VS;
        data->hovered_selection = SEL_VS_TOURNAMENT;
        return;
    case GM_CAMERA_MODE:
        data->menu_kind = MENU_KIND_SPECIAL;
        data->hovered_selection = SEL_SPECIAL_VS_CAMERA;
        return;
    case GM_STAMINA_VS:
        data->menu_kind = MENU_KIND_SPECIAL;
        data->hovered_selection = SEL_SPECIAL_VS_STAMINA;
        return;
    case GM_SUPER_SUDDEN_DEATH_VS:
        data->menu_kind = MENU_KIND_SPECIAL;
        data->hovered_selection = SEL_SPECIAL_VS_SUDDEN_DEATH;
        return;
    case GM_GIANT_VS:
        data->menu_kind = MENU_KIND_SPECIAL;
        data->hovered_selection = SEL_SPECIAL_VS_GIANT;
        return;
    case GM_TINY_VS:
        data->menu_kind = MENU_KIND_SPECIAL;
        data->hovered_selection = SEL_SPECIAL_VS_TINY;
        return;
    case GM_INVISIBLE_VS:
        data->menu_kind = MENU_KIND_SPECIAL;
        data->hovered_selection = SEL_SPECIAL_VS_INVISIBLE;
        return;
    case GM_SLOMO_VS:
        data->menu_kind = MENU_KIND_SPECIAL;
        data->hovered_selection = SEL_SPECIAL_VS_SLOMO;
        return;
    case GM_LIGHTNING_VS:
        data->menu_kind = MENU_KIND_SPECIAL;
        data->hovered_selection = SEL_SPECIAL_VS_LIGHTNING;
        return;
    case GM_CAMERA_VS:
        data->menu_kind = MENU_KIND_SPECIAL;
        data->hovered_selection = SEL_SPECIAL_VS_FIXED_CAMERA;
        return;
    case GM_SINGLE_BUTTON_VS:
        data->menu_kind = MENU_KIND_SPECIAL;
        data->hovered_selection = SEL_SPECIAL_VS_SINGLE_BUTTON;
        return;
    case GM_TOY_GALLERY:
        data->menu_kind = MENU_KIND_TOY;
        data->hovered_selection = SEL_TOY_GALLERY;
        return;
    case GM_TOY_LOTTERY:
        data->menu_kind = MENU_KIND_TOY;
        data->hovered_selection = SEL_TOY_LOTTERY;
        return;
    case GM_TOY_COLLECTION:
        data->menu_kind = MENU_KIND_TOY;
        data->hovered_selection = SEL_TOY_COLLECTION;
        return;
    case GM_MENU:
        data->menu_kind = MENU_KIND_SETTINGS;
        data->hovered_selection = SEL_SETTINGS_LANG;
        return;
    default:
        data->menu_kind = MENU_KIND_MAIN;
        data->hovered_selection = SEL_MAIN_1P;
        return;
    }
}

void onExit(GameModeState* arg0)
{
    MenuExitData* data = arg0->info.exit_data;

    gm_SetPendingGameMode(data->pending_mode);
    gm_SetNewGameModePending();
}
