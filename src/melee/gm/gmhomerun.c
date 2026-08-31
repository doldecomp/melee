#include "gmhomerun.h"

#include "gm_unsplit.h"

#include "gm/forward.h"

#include "gm/gmvsmelee.h"

#include <melee/pl/forward.h>

#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/lbtime.h>
#include <melee/lb/types.h>
#include <melee/mn/types.h>

GameModeState gm_Mode_Homerun_States[] = {
    {
        0,
        3,
        0,
        gm_801B98E8,
        gm_801B999C,
        {
            GS_CSS,
            &gmVsMelee_CssData,
            &gmVsMelee_CssData,
        },
    },
    {
        1,
        3,
        0,
        gm_801B9A3C,
        gm_801B9DD8,
        {
            GS_VS,
            &gmVsMelee_StartData,
            &gmVsMelee_VsExitInfo,
        },
    },
    { -1 },
};

VsModeData gm_80497618;
static u8 gm_804D68F8;
static u8 gm_804D68F9;

void gm_801B98E8(GameModeState* scene)
{
    CSSData* css;
    struct GameCache* game_cache;
    VsModeData* vs = &gm_80497618;

    css = gm_GetGameModeStateEnterData(scene);
    if (gm_804D68F9 != 0) {
        lb_8001C550();
        lb_8001D164(0);
        lb_8001CE00();
    }
    gm_801B06B0(css, 0x10, vs->start.players[0].ckind, 1,
                vs->start.players[0].color, vs->start.players[0].nametag, 0,
                gm_804D68F8);
    game_cache = &lbDvd_GetPreloadCacheScene()->game_cache;
    lbDvd_SetupVsPreloadCache();
    game_cache->entries[1].char_id = CHKIND_SANDBAG;
    game_cache->entries[1].color = 0;
    game_cache->stkind = 0x54;
    lbDvd_80018254();
    gm_804D68F9 = lbTime_8000AF74(gm_804D68F9, 1);
}

void gm_801B999C(GameModeState* scene)
{
    VsModeData* vs = &gm_80497618;
    CSSData* temp_r3;

    temp_r3 = gm_GetGameModeStateExitData(scene);
    if (temp_r3->pending_scene_change == 2) {
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        return;
    }
    gm_SetupAllPlayerDefaults(vs->start.players);
    gm_801B0730(temp_r3, &vs->start.players[0].ckind, NULL,
                &vs->start.players[0].color, &vs->start.players[0].nametag,
                NULL);
    vs->start.players[1].ckind = CHKIND_SANDBAG;
    vs->start.players[1].xE = 0xF;
    vs->start.players[1].x1C = 1.0f;
    vs->start.players[1].slot_type = Gm_PKind_Cpu;
    vs->start.players[1].stocks = 1;
    vs->start.players[1].team = 1;
}

void gm_801B9A3C(GameModeState* arg0)
{
    StartMeleeData* start;
    VsModeData* vs = &gm_80497618;
    int i;

    start = gm_GetGameModeStateEnterData(arg0);
    gm_SetupRulesDefaults(&start->rules);

    start->rules = vs->start.rules;

    start->rules.stkind = St_Kind_Unk84;
    start->rules.match_kind = 1;
    start->rules.x0_6 = true;
    start->rules.x1_0 = true;
    start->rules.x4_2 = false;
    start->rules.x4_4 = false;

    start->rules.is_teams = false;
    start->rules.xB = -1;
    start->rules.time_limit = 10;
    start->rules.x34 = 1.0f;
    start->rules.x30 = 1.0f;

    start->rules.x5_0 = true;
    start->rules.x1_3 = true;
    start->rules.x44 = gm_80181998;

    start->rules.x3_3 = true;
    start->rules.x3_2 = true;
    start->rules.x7 = 9;

    for (i = 0; i < GM_MAX_PLAYERS; i++) {
        start->players[i] = vs->start.players[i];
        start->players[i].xC_b1 = false;
        start->players[i].xD_b3 = true;
    }

    gm_801B0620(&start->players[0], vs->start.players[0].ckind,
                vs->start.players[0].color, 1, gm_804D68F8);
    start->players[0].xD_b2 = true;
    gm_LoadRumbleEnabled(start);
    gm_80181A00(start->players[0].ckind, start->players[0].nametag);
    gm_80180B18();
}

void gm_801B9DD8(GameModeState* arg0)
{
    u32 temp_r31;
    s32* temp_r3_2;
    u8 selkind;
    MatchExitInfo* temp_r3;
    u16 tmp;

    temp_r3 = gm_GetGameModeStateExitData(arg0);
    gm_80162968(temp_r3->match_end.frame_count / 60);
    gm_8016247C(temp_r3->match_end.player_standings[0].xE);
    gm_80180BA0();
    if (temp_r3->match_end.result == OUTCOME_RETRY) {
        gm_SetNextGameModeStateId(1);
        return;
    }
    selkind = gm_CKindToSelKind(temp_r3->match_end.player_standings[0].ckind);
    temp_r31 = gm_80180AE4();
    if ((tmp = gm_801734D0(temp_r31)) != 0x148) {
        gm_80164504(tmp);
    }
    temp_r3_2 = gmMainLib_8015D084(selkind);
    if (temp_r31 > *temp_r3_2) {
        *temp_r3_2 = temp_r31;
    }
    gm_80173B30(temp_r31);
    gm_80173EEC();
    gm_80172898(8);
    if (gm_80173754(0x20, gm_804D68F8) == 0) {
        gm_SetNextGameModeStateId(0);
    }
}

void gm_Mode_Homerun_OnInit(void)
{
    VsModeData* data = &gm_80497618;
    gm_InitVsMode(data);
}

void gm_Mode_Homerun_OnLoad(void)
{
    gm_804D68F8 = gm_801677F0();
    gm_804D68F9 = 0;
}
