#include "gmstamina.h"

#include "gm_1B03.static.h"

#include "gm_unsplit.h"
#include "gmvsdata.h"

#include <placeholder.h>

#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/random.h>
#include <melee/db/db.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmcamera.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmresult.h>
#include <melee/gm/gmresultplayer.h>
#include <melee/gm/gmtou.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/types.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/lbmthp.h>
#include <melee/lb/lbsnap.h>
#include <melee/lb/lbtime.h>
#include <melee/lb/types.h>
#include <melee/mn/mngallery.h>
#include <melee/mn/types.h>
#include <melee/pl/player.h>
#include <melee/un/un_2FC9.h>
#include <melee/vi/types.h>
#include <melee/vi/vi0102.h>
#include <melee/vi/vi0402.h>
#include <melee/vi/vi0501.h>
#include <melee/vi/vi1101.h>
#include <melee/vi/vi1201v1.h>

MinorScene gm_803DF138_MinorScenes[] = {
    {
        0,
        3,
        0,
        gm_801B91C8,
        gm_801B922C,
        {
            MN_CSS,
            &gm_804807B0,
            &gm_804807B0,
        },
    },
    {
        1,
        3,
        0,
        gm_801B9254,
        gm_801B927C,
        {
            MN_SSS,
            &gm_80480668,
            &gm_80480668,
        },
    },
    {
        2,
        3,
        0,
        gm_801B931C,
        gm_801B9560,
        {
            MN_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    { -1 },
};

static struct {
    u16 done_counter;     ///< Ticks up to 100 when match is done
    bool eliminated[4];   ///< True if this slot been eliminated
    u16 slomo_counter[4]; ///< Ticks up to 100 when player is eliminated
} gm_804975F8;

extern MatchExitInfo gm_80479D98;

void gm_801B91C8(MinorScene* arg0)
{
    VsModeData* vs = &gmMainLib_804D3EE0->unk_10D0;
    CSSData* css = gm_801A427C(arg0);
    css->match_type = 2;
    css->ko_star_counts = 0;
    css->data = *vs;
    lbDvd_800174BC();
}

void gm_801B922C(MinorScene* scene)
{
    gm_801A5680(scene, &gmMainLib_804D3EE0->unk_10D0);
}

void gm_801B9254(MinorScene* scene)
{
    gm_801A5754(scene, &gmMainLib_804D3EE0->unk_10D0);
}

void gm_801B927C(MinorScene* arg0)
{
    VsModeData* vs = &gmMainLib_804D3EE0->unk_10D0;
    SSSData* sss = gm_801A4284(arg0);
    if (sss->start_game != 0) {
        *vs = sss->data;

        lbAudioAx_80026F2C(0x18);
        lbAudioAx_8002702C(
            8, lbAudioAx_80026EBC((enum InternalStageId) sss->force_stage_id));
        lbAudioAx_80027168();
        return;
    }
    gm_SetScenePendingMinor(0);
}

void gm_801B931C(MinorScene* arg0)
{
    VsModeData* vs = &gmMainLib_804D3EE0->unk_10D0;
    StartMeleeData* start = gm_801A427C(arg0);
    int i;

    gm_80167BC8(vs);

    start->rules = vs->data.rules;

    start->rules.x2_5 = false;
    start->rules.x0_6 = false;
    start->rules.x0_0 = 1;
    start->rules.x44 = fn_801B9850;
    start->rules.x3_0 = false;
    gm_80167A14(start->players);

    for (i = 0; i < 4; i++) {
        start->players[i] = vs->data.players[i];
        start->players[i].xC_b7 = true;
        start->players[i].stocks = 1;
        start->players[i].hp = 150;
    }

    gm_801B0348(start);
    gm_8016F088(start);
    gm_80168FC4();
}

void gm_801B9560(MinorScene* scene)
{
    VsModeData* vs = &gmMainLib_804D3EE0->unk_10D0;
    gm_80168710(&gm_80479D98.match_end, vs);
    gm_801A5AF0(scene, 0, 0);
}

void gm_801B95B0_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_10D0);
}

void gm_801B95D8_OnLoad(void)
{
    gm_SetGameSpeed(1.0F);
    gm_801A55C4();
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
            if (gmMainLib_804D3EE0->unk_10D0.data.rules.x8) {
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
    HSD_GObjProc_8038FD54(GObj_Create(0xF, 0x11, 0), fn_801B96E8, 0x15);
}
