#include "gmtrainingmode.h"

#include "gm_1B03.h"

#include "gm/gm_1884.h"
#include "gm/gm_1A3F.h"

#include "lb/forward.h"

#include "melee/gm/gm_unsplit.h"
#include "melee/gm/gmmain_lib.h"
#include "melee/gm/types.h"
#include "melee/lb/lbaudio_ax.h"
#include "melee/lb/lbcardgame.h"
#include "melee/lb/lbcardnew.h"
#include "melee/lb/lbdvd.h"
#include "melee/lb/lbtime.h"
#include "melee/lb/types.h"
#include "melee/mn/types.h"
#include "mn/inlines.h"

/* 1B1B74 */ static void gm_801B1B74(GameModeState*);
/* 1B1C24 */ static void gm_801B1C24(GameModeState*);
/* 1B1EB8 */ static void gm_801B1EB8(GameModeState*);
/* 1B1EEC */ static void gm_801B1EEC(GameModeState*);
/* 1B1F6C */ static void fn_801B1F6C(int);
/* 1B1F70 */ static void gm_801B1F70(GameModeState*);
/* 1B2204 */ static void gm_801B2204(GameModeState*);
/* 4D68C0 */ static u8 gm_804D68C0;
/* 4D68C1 */ static u8 gm_804D68C1;
/* 48E230 */ static CSSData css_data;
/* 48E378 */ static SSSData sss_data;
/* 48E4C0 */ static StartMeleeData training_enter_data;
/* 48E5F8 */ static UNK_T training_exit_data[0x2288 / 4];

GameModeState gm_Mode_Training_States[] = {
    {
        0,
        lbDvdPreload_3,
        0,
        gm_801B1B74,
        gm_801B1C24,
        {
            GS_CSS,
            &css_data,
            &css_data,
        },
    },
    {
        1,
        lbDvdPreload_3,
        0,
        gm_801B1EB8,
        gm_801B1EEC,
        {
            GS_SSS,
            &sss_data,
            &sss_data,
        },
    },
    {
        2,
        lbDvdPreload_3,
        0,
        gm_801B1F70,
        gm_801B2204,
        {
            GS_TRAINING,
            &training_enter_data,
            &training_exit_data,
        },
    },
    { -1 },
};

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void gm_801B1B74(GameModeState* arg0)
{
    VsModeData* vs_data;
    CSSData* css;
    PAD_STACK(8);

    vs_data = &gmMainLib_804D3EE0->unk_D10;
    css = gm_GetGameSceneLoadData(arg0);
    if (gm_804D68C1 != 0) {
        lb_8001C550();
        lb_8001D164(0);
        lb_8001CE00();
    }
    gm_801B06B0(css, 0x17U, vs_data->data.players[0].c_kind, 1,
                vs_data->data.players[0].color, vs_data->data.players[0].xA,
                9U, gm_804D68C0);
    gm_801B07B4(css, vs_data->data.players[1].c_kind, 1,
                vs_data->data.players[1].color, vs_data->data.players[1].xA,
                0U, gm_804D68C0);
    lbDvd_800174BC();
    gm_804D68C1 = lbTime_8000AF74((u32) gm_804D68C1, 1);
}
#ifdef MUST_MATCH
#pragma pop
#endif

static void gm_801B07E8_layer(CSSData* css_data, s8* c_kind, s8* stocks,
                              s8* color, s8* arg4, u8* level)
{
    gm_801B07E8(css_data, c_kind, stocks, color, arg4, level);
}

void gm_801B1C24(GameModeState* arg0)
{
    VsModeData* vs = &gmMainLib_804D3EE0->unk_D10;
    CSSData* css = gm_GetGameSceneLeaveData(arg0);
    s32 i;
    struct GameCache* cache;
    s32 j;
    PAD_STACK(0x10);

    if (css->pending_scene_change == 2) {
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        return;
    }
    gm_80167A14(vs->data.players);
    gm_801B0730(css, &vs->data.players[0].c_kind, NULL,
                &vs->data.players[0].color, &vs->data.players[0].xA, NULL);
    gm_801B07E8_layer(css, &vs->data.players[1].c_kind, NULL,
                      (s8*) &vs->data.players[1].color,
                      (s8*) &vs->data.players[1].xA, NULL);
    j = (i = 2);
    vs->data.players[1].xE = 0;
    for (; i < 4; i++, j++) {
        vs->data.players[i] = vs->data.players[1];
        vs->data.players[i].color = (vs->data.players[i - 1].color + 1) %
                                    gm_80169238(vs->data.players[j].c_kind);
        if (vs->data.players[i].color == vs->data.players[0].color) {
            vs->data.players[i].color =
                (vs->data.players[i].color + 1) %
                gm_80169238(vs->data.players[j].c_kind);
        }
        vs->data.players[i].slot_type = 3;
    }
    if (gm_804D68C0 == 0) {
        vs->data.players[1].slot = 0;
        vs->data.players[2].slot = 0;
        vs->data.players[3].slot = 0;
    } else {
        s32 k = 1;
        for (i = 0; i < 4; i++) {
            if (gm_804D68C0 != i) {
                vs->data.players[k].slot = i + 1;
                k++;
            }
        }
    }
    cache = &lbDvd_GetPreloadCacheScene()->game_cache;
    cache->entries[2].char_id = vs->data.players[2].c_kind;
    cache->entries[2].color = vs->data.players[2].color;
    cache->entries[3].char_id = vs->data.players[3].c_kind;
    cache->entries[3].color = vs->data.players[3].color;
    lbDvd_80018254();
    {
        u64 mask;
        s32 k;
        mask = 0;
        for (k = 0; k < 4; k++) {
            mask |= lbAudioAx_80026E84(vs->data.players[k].c_kind);
        }
        lbAudioAx_80026F2C(20);
        lbAudioAx_8002702C(4, mask);
        lbAudioAx_80027168();
    }
}

void gm_801B1EB8(GameModeState* arg0)
{
    SSSData* sss;

    sss = gm_GetGameSceneLoadData(arg0);
    sss->x1 = 0;
    sss->force_stage_id = -1;
    sss->unk_stage = 0;
}

void gm_801B1EEC(GameModeState* arg0)
{
    VsModeData* vs_data;
    SSSData* sss;
    s16 stkind;

    vs_data = &gmMainLib_804D3EE0->unk_D10;
    sss = gm_GetGameSceneLeaveData(arg0);
    if (sss->start_game == 0) {
        gm_SetPendingSceneIndex(0);
        return;
    }
    stkind = sss->data.data.rules.stkind;
    gm_80473814.x6 = stkind;
    vs_data->data.rules.stkind = stkind;
    lbAudioAx_80026F2C(0x18);
    lbAudioAx_8002702C(8, lbAudioAx_80026EBC(vs_data->data.rules.stkind));
    lbAudioAx_80027168();
}

void fn_801B1F6C(int unused) {}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void gm_801B1F70(GameModeState* arg0)
{
    VsModeData* vs;
    StartMeleeData* data;
    int i;

    vs = &gmMainLib_804D3EE0->unk_D10;
    data = gm_GetGameSceneLoadData(arg0);
    gm_80167A64(&data->rules);

    data->rules = vs->data.rules;
    data->rules.on_pause_override = fn_801B1F6C;

    data->rules.x3_6 = true;
    data->rules.x2_5 = false;
    data->rules.x2_1 = true;
    gm_80167A14(data->players);

    for (i = 0; i < 4; i++) {
        data->players[i] = vs->data.players[i];
        data->players[i].xC_b1 = false;
        data->players[i].xD_b2 = true;
    }

    gm_801B0620(&data->players[0], vs->data.players[0].c_kind,
                vs->data.players[0].color, 1, gm_804D68C0);

    for (i = 1; i < 4; i++) {
        PlayerInitData* var_r30 = &data->players[i];
        gm_801B0664(&data->players[i], vs->data.players[i].c_kind,
                    vs->data.players[i].color, 1,
                    vs->data.players[i].slot - 1);
        if (i - 1 != 0) {
            data->players[i].slot_type = Gm_PKind_NA;
        }
    }

    gm_8016F088(data);
    gm_80189CDC(data);
}
#ifdef MUST_MATCH
#pragma pop
#endif

void gm_801B2204(GameModeState* arg0)
{
    MatchExitInfo* temp_r3;

    temp_r3 = gm_GetGameSceneLeaveData(arg0);
    gm_80162968(temp_r3->match_end.frame_count / 60);
    gm_8016247C(temp_r3->match_end.player_standings[0].xE);
    gm_80163298(temp_r3->match_end.player_standings[0].character_kind,
                (u16) gm_80188454(
                    temp_r3->match_end.player_standings[0].character_kind));
    gm_80173BC4(temp_r3->match_end.player_standings[0].character_kind);
    gm_80173EEC();
    if (!gm_80173754(28, gm_804D68C0)) {
        gm_SetPendingSceneIndex(0);
    }
    sfxForward();
}

void gm_Mode_Training_OnInit(void)
{
    VsModeData* temp_r31 = &gmMainLib_804D3EE0->unk_D10;
    int i;

    gm_80167B50(temp_r31);

    for (i = 0; i < 4; i++) {
        temp_r31->data.players[i].color = i;
        temp_r31->data.players[i].xE = 0;
        if (i != 0) {
            temp_r31->data.players[1].c_kind = CHKIND_NONE;
        }
        gm_80473814.players[i] = temp_r31->data.players[i];
    }
}

void gm_Mode_Training_OnLoad(void)
{
    gm_804D68C0 = gm_801677F0();
    gm_804D68C1 = 0;
}
