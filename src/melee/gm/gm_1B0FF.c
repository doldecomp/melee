#include "gm_1B03.h"

#include "gm_1B03.static.h"

#include "gm/gm_1A3F.h"
#include "melee/gm/gm_unsplit.h"
#include "melee/gm/gmmain_lib.h"
#include "melee/gm/types.h"
#include "melee/lb/lbcardgame.h"
#include "melee/lb/lbcardnew.h"
#include "melee/lb/lbdvd.h"
#include "melee/lb/lbsnap.h"
#include "melee/mn/mngallery.h"
#include "melee/mn/mnsnap.h"
#include "melee/mn/types.h"

#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/random.h>

/* 1B0FF8 */ static void gm_801B0FF8(GameScene*);
/* 1B138C */ static void gm_801B138C(GameScene*);
/* 4D68BC */ MenuExitData* gm_804D68BC;
/* 4D68B8 */ MenuEnterData* gm_804D68B8;
/* 4D68B0 */ UNK_T gm_804D68B0[0x8 / 4];

GameScene gm_803DD8B8_Scenes[] = {
    {
        0,
        2,
        0,
        gm_801B0FF8,
        gm_801B138C,
        {
            GS_MENU,
            &gm_804D68B8,
            &gm_804D68BC,
        },
    },
    { -1 },
};

void gm_801B0FF8(GameScene* scene)
{
    GameRules* rules;
    MenuEnterData* data;
    GameModeKind var_r0;

    data = scene->info.load_data;
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
    rules = gmMainLib_8015CC34();
    if (rules->force_main_menu != 0) {
        rules->force_main_menu = 0;
        data->menu_kind = MENU_KIND_MAIN;
        data->hovered_selection = SEL_MAIN_1P;
        data->load_assets = 1;
        return;
    }
    data->load_assets = 1;
    var_r0 = gm_801A4320();
    if (var_r0 == GM_CHALLENGER_APPROACH) {
        var_r0 = gm_801737D8();
    }
    switch (var_r0) {
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
    case GM_FIXED_CAMERA_VS:
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

void gm_801B138C(GameScene* arg0)
{
    MenuExitData* data = arg0->info.leave_data;

    gm_801A42E8(data->pending_mode);
    gm_801A42D4();
}

void gm_801B13B8(GameScene* arg0)
{
    StartMeleeData* temp_r28 = gm_801A427C(arg0);
    int i;

    gm_80167A64(&temp_r28->rules);
    temp_r28->rules.xE = 0x20;
    temp_r28->rules.xB = -1;
    temp_r28->rules.xC = -1;
    temp_r28->rules.x0_0 = 0;

    for (i = 0; i < 6; i++) {
        gm_8016795C(&temp_r28->players[i]);
        temp_r28->players[i].stocks = 0;
        temp_r28->players[i].xE = 4;
    }

    temp_r28->players[0].c_kind = 6;
    temp_r28->players[1].c_kind = 8;
    temp_r28->players[2].c_kind = 6;
    temp_r28->players[3].c_kind = 6;

    temp_r28->players[0].slot_type = Gm_PKind_Human;
    temp_r28->players[1].slot_type = Gm_PKind_Human;
    temp_r28->players[2].slot_type = Gm_PKind_NA;
    temp_r28->players[3].slot_type = Gm_PKind_NA;

    temp_r28->players[0].xC_b0 = false;
    temp_r28->players[1].xC_b0 = false;
    temp_r28->players[2].xC_b0 = false;
    temp_r28->players[3].xC_b0 = false;

    gm_80168FC4();
}
