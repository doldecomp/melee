#include "gmstamina.h"

#include "gm_unsplit.h"

#include <placeholder.h>

#include "gm/gm_1A3F.h"

#include <sysdolphin/baselib/gobjproc.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/types.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbdvd.h>
#include <melee/mn/types.h>
#include <melee/pl/player.h>

GameModeState gm_Mode_StaminaVs_States[] = {
    {
        0,
        lbDvdPreload_3,
        0,
        gm_801B91C8,
        gm_801B922C,
        {
            GS_CSS,
            &gmVsMelee_CssData,
            &gmVsMelee_CssData,
        },
    },
    {
        1,
        lbDvdPreload_3,
        0,
        gm_801B9254,
        gm_801B927C,
        {
            GS_SSS,
            &gmVsMelee_SssData,
            &gmVsMelee_SssData,
        },
    },
    {
        2,
        lbDvdPreload_3,
        0,
        gm_801B931C,
        gm_801B9560,
        {
            GS_VS,
            &gmVsMelee_StartData,
            &gmVsMelee_VsExitInfo,
        },
    },
    { -1 },
};

static struct {
    u16 done_counter;     ///< Ticks up to 100 when match is done
    bool eliminated[4];   ///< True if this slot been eliminated
    u16 slomo_counter[4]; ///< Ticks up to 100 when player is eliminated
} gm_804975F8;

void gm_801B91C8(GameModeState* state)
{
    VsModeData* vs = &gmMainLib_804D3EE0->modes.vs_stamina;
    CSSData* css = gm_GetGameModeStateEnterData(state);
    css->match_type = 2;
    css->ko_counts = 0;
    css->vs = *vs;
    lbDvd_SetupVsPreloadCache();
}

void gm_801B922C(GameModeState* scene)
{
    gmVsMelee_ExitCss(scene, &gmMainLib_804D3EE0->modes.vs_stamina);
}

void gm_801B9254(GameModeState* scene)
{
    gmVsMelee_EnterSss(scene, &gmMainLib_804D3EE0->modes.vs_stamina);
}

void gm_801B927C(GameModeState* state)
{
    VsModeData* vs = &gmMainLib_804D3EE0->modes.vs_stamina;
    SSSData* sss = gm_GetGameModeStateExitData(state);
    if (sss->start_game != 0) {
        *vs = sss->vs;

        lbAudioAx_80026F2C(0x18);
        lbAudioAx_8002702C(8, lbAudioAx_80026EBC(sss->force_stage_id));
        lbAudioAx_80027168();
        return;
    }
    gm_SetNextGameModeStateId(0);
}

void gm_801B931C(GameModeState* state)
{
    VsModeData* vs = &gmMainLib_804D3EE0->modes.vs_stamina;
    StartMeleeData* start = gm_GetGameModeStateEnterData(state);
    int i;

    gm_80167BC8(vs);

    start->rules = vs->start.rules;

    start->rules.x2_5 = false;
    start->rules.x0_6 = false;
    start->rules.match_kind = 1;
    start->rules.x44 = fn_801B9850;
    start->rules.x3_0 = false;
    gm_SetupAllPlayerDefaults(start->players);

    for (i = 0; i < PAD_MAX_CONTROLLERS; i++) {
        start->players[i] = vs->start.players[i];
        start->players[i].xC_b7 = true;
        start->players[i].stocks = 1;
        start->players[i].hp = 150;
    }

    gm_SetupSubColors(start);
    gm_LoadRumbleEnabled(start);
    gm_LoadAnnouncer();
}

void gm_801B9560(GameModeState* scene)
{
    VsModeData* vs = &gmMainLib_804D3EE0->modes.vs_stamina;
    gm_80168710(&gmVsMelee_VsExitInfo.match_end, vs);
    gmVsMelee_ExitVs(scene, 0, 0);
}

void gm_Mode_StaminaVs_OnInit(void)
{
    gm_InitVsMode(&gmMainLib_804D3EE0->modes.vs_stamina);
}

void gm_Mode_StaminaVs_OnLoad(void)
{
    gm_SetGameSpeed(1.0F);
    gmVsMelee_ResetKOCounts();
}

/// Number of players / teams remaining
int gm_801B9600(void)
{
    int i;
    int j;
    int count = 0;
    PAD_STACK(4);

    for (i = 0; i < 4; i++) {
        if (Player_GetPlayerSlotType(i) != Gm_PKind_NA &&
            Player_GetStocks(i) == 0)
        {
            gm_804975F8.eliminated[i] = true;
        }
        if (!gm_804975F8.eliminated[i]) {
            if (gmMainLib_804D3EE0->modes.vs_stamina.start.rules.is_teams) {
                for (j = 0; j < i; j++) {
                    if (!gm_804975F8.eliminated[j] &&
                        Player_GetTeam(i) == Player_GetTeam(j))
                    {
                        break;
                    }
                }
                if (i == j) {
                    count++;
                }
            } else {
                count++;
            }
        }
    }
    return count;
}

/// Handles player elimination and game end
static void fn_801B96E8(HSD_GObj* unused)
{
    int i;
    PAD_STACK(4);

    for (i = 0; i < 4; i++) {
        if (Player_GetPlayerSlotType(i) != Gm_PKind_NA) {
            if (gm_804975F8.slomo_counter[i] > 0 &&
                gm_804975F8.slomo_counter[i] < 100)
            {
                gm_804975F8.slomo_counter[i]++;
            } else if (gm_804975F8.slomo_counter[i] == 100) {
                gm_804975F8.slomo_counter[i] = 0;
                gm_SetGameSpeed(1.0F);
            }
        }
    }

    // If 1 or fewer players/teams remain, count to 100 and end the game
    if (gm_801B9600() <= 1) {
        gm_804975F8.done_counter++;
        if (gm_804975F8.done_counter > 100) {
            gm_SetGameSpeed(1.0F);
            gm_8016B33C(5);
            gm_8016B328();
        }
    }
}

void gm_801B97C4(int slot, bool cond)
{
    if (slot < 4 && cond == 0) {
        if (!gm_804975F8.eliminated[slot]) {
            Player_UpdateMatchFrameCount(slot, cond);
            gm_804975F8.slomo_counter[slot] = 1;
            gm_SetGameSpeed(0.4F);
        }
        gm_804975F8.eliminated[slot] = true;
    }
}

void fn_801B9850(void)
{
    int i;
    gm_804975F8.done_counter = 0;
    for (i = 0; i < 4; i++) {
        if (Player_GetPlayerSlotType(i) == Gm_PKind_NA) {
            gm_804975F8.eliminated[i] = true;
        } else {
            gm_804975F8.eliminated[i] = false;
        }
        gm_804975F8.slomo_counter[i] = 0;
    }
    HSD_GObj_SetupProc(GObj_Create(0xF, 0x11, 0), fn_801B96E8, 0x15);
}
