#include "dolphin/types.h"
#include "gm/gm_1A3F.h"
#include "gm/types.h"
#include "if/soundtest.h"

#include "mn/forward.h"

#include "mn/inlines.h"

#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/random.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmresultplayer.h>
#include <melee/gm/types.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/mn/types.h>

struct DebugResultsData {
    u8 x0_0 : 1;
    u8 x0_1 : 1;
    u8 x0_other : 6;
    u8 x1;
    u8 x2;
    u8 x3;
    u8 x4;
    u8 pad_x5[3];
    MatchEnd match_end;
}; /// data used by onEnterResults1

struct DebugMemcardData {
    u32 x0;
    u8 x4;
};

struct enterMenu0_Data {
    UNK_T x0;
    UNK_T x4;
};
ASSERT_SIZE(struct enterMenu0_Data, 0x8);

struct exitIntroData {
    UNK_T x0;
};
ASSERT_SIZE(struct exitIntroData, 0x4);

/* 1B099C */ static void onExitIntro(GameModeState*);
/* 1B09C0 */ static void onEnterMenu0(GameModeState*);
/* 1B09F8 */ static int fn_801B09F8(int);
/* 1B0A34 */ static void onEnterMenu1(GameModeState*);
/* 1B0A8C */ static int fn_801B0A8C(int);
/* 1B0AC8 */ static void onEnterMenu2(GameModeState*);
/* 1B0B00 */ static void onEnterPrize(GameModeState*);
/* 1B0B24 */ static void onExitPrize(GameModeState*);
/* 1B0B48 */ static void onEnterVs(GameModeState*);
/* 1B0B8C */ static void onEnterResults0(GameModeState*);
/* 1B0BF0 */ static void onExitResults0(GameModeState*);
/* 1B0C18 */ static void onEnterIntroEasy(GameModeState*);
/* 1B0C50 */ static void onEnterIntroAllstar(GameModeState*);
/* 1B0C74 */ static void onEnterGameOver(GameModeState*);
/* 1B0CF0 */ static void onEnterApproach(GameModeState*);
/* 1B0DD0 */ static void onEnterResults1(GameModeState*);
/* 1B0F1C */ static void onExitResults1(GameModeState*);
/* 1B0F60 */ static void onEnterMemCard(GameModeState*);
/* 1B0F90 */ static void onExitMemCard(GameModeState*);
/* 480DC8 */ static struct UnkSoundTestData1 intro_easy_enter_data;
/* 480DE8 */ static StartMeleeData vs_enter_data;
/* 480F20 */ static MatchExitInfo vs_exit_data;
/* 4831A8 */ static struct ResultsMatchInfo results0_data;
/* 48542C */ static struct UnkSoundTestData0 prize_enter_data;
/* 485438 */ static struct DebugGameOverData game_over_data;
/* 485454 */ static struct DebugResultsData results1_enter_data;
/* 4D6880 */ static struct exitIntroData intro_easy_exit_data;
/* 4D6884 */ static un_80301C64_t intro_allstar_enter_data;
/* 4D688C */ static struct exitIntroData intro_allstar_exit_data;
/* 4D6890 */ static struct enterMenu0_Data menu_enter_data;
/* 4D6898 */ static struct exitIntroData approach_data;
/* 4D689C */ static struct DebugMemcardData memcard_enter_data;
/* 4D68A4 */ static struct DebugMemcardData memcard_exit_data;

/* 3DD6D0 */ GameModeState gm_Mode_Debug_States[] = {
    {
        0,
        lbDvdPreload_2,
        0,
        onEnterMenu0,
        NULL,
        {
            GS_DEBUG_MENU,
            &menu_enter_data,
            NULL,
        },
    },
    {
        1,
        lbDvdPreload_2,
        0,
        onEnterMenu1,
        NULL,
        {
            GS_DEBUG_MENU,
            &menu_enter_data,
            NULL,
        },
    },
    {
        2,
        lbDvdPreload_2,
        0,
        onEnterMenu2,
        NULL,
        {
            GS_DEBUG_MENU,
            &menu_enter_data,
            NULL,
        },
    },
    {
        3,
        lbDvdPreload_2,
        0,
        onEnterPrize,
        onExitPrize,
        {
            GS_PRIZE_INTERFACE,
            &prize_enter_data,
            NULL,
        },
    },
    {
        4,
        lbDvdPreload_2,
        0,
        onEnterVs,
        NULL,
        {
            GS_VS,
            &vs_enter_data,
            &vs_exit_data,
        },
    },
    {
        5,
        lbDvdPreload_2,
        0,
        onEnterResults0,
        onExitResults0,
        {
            GS_RESULTS,
            &results0_data,
            &results0_data,
        },
    },
    {
        6,
        lbDvdPreload_2,
        0,
        onEnterIntroEasy,
        onExitIntro,
        {
            GS_INTRO_EASY,
            &intro_easy_enter_data,
            &intro_easy_exit_data,
        },
    },
    {
        7,
        lbDvdPreload_2,
        0,
        onEnterIntroAllstar,
        onExitIntro,
        {
            GS_INTRO_ALLSTAR,
            &intro_allstar_enter_data,
            &intro_allstar_exit_data,
        },
    },
    {
        8,
        lbDvdPreload_2,
        0,
        NULL,
        onExitIntro,
        {
            GS_COMING_SOON,
            NULL,
            NULL,
        },
    },
    {
        9,
        lbDvdPreload_2,
        0,
        onEnterGameOver,
        onExitIntro,
        {
            GS_GAMEOVER,
            &game_over_data,
            &game_over_data,
        },
    },
    {
        10,
        lbDvdPreload_2,
        0,
        onEnterApproach,
        onExitIntro,
        {
            GS_APPROACH,
            &approach_data,
            &approach_data,
        },
    },
    {
        11,
        lbDvdPreload_2,
        0,
        onEnterResults1,
        onExitResults1,
        {
            GS_RESULTS,
            &results1_enter_data,
            NULL,
        },
    },
    {
        12,
        lbDvdPreload_2,
        0,
        NULL,
        onExitIntro,
        {
            GS_MOVIE_OPENING,
            NULL,
            NULL,
        },
    },
    {
        13,
        lbDvdPreload_2,
        0,
        onEnterMemCard,
        onExitMemCard,
        {
            GS_MEMCARD,
            &memcard_enter_data,
            &memcard_exit_data,
        },
    },
    {
        14,
        lbDvdPreload_2,
        0,
        NULL,
        NULL,
        {
            GS_STAFFROLL,
            NULL,
            NULL,
        },
    },
    { -1 },
};

void onExitIntro(GameModeState* unused)
{
    gm_SetPendingSceneIndex(0); // onEnterMenu0
}

void onEnterMenu0(GameModeState* arg0)
{
    struct enterMenu0_Data* temp_r3 = gm_GetGameSceneLoadData(arg0);
    temp_r3->x0 = un_803FA4E0;
    temp_r3->x4 = fn_801B09F8;
}

int fn_801B09F8(int arg0)
{
    if (arg0 == 0) {
        sfxBack();
        gm_ChangeGameModeAfterCurrentScene(GM_TITLE);
        gm_801A4B60();
    }
    return 0;
}

void onEnterMenu1(GameModeState* arg0)
{
    struct enterMenu0_Data* temp_r3 = gm_GetGameSceneLoadData(arg0);
    temp_r3->x0 = un_803FA790;
    temp_r3->x4 = fn_801B0A8C;
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 0x20);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

int fn_801B0A8C(int arg0)
{
    if (arg0 == 0) {
        sfxBack();
        gm_SetPendingSceneIndex(0);
        gm_801A4B60();
    }
    return 0;
}

void onEnterMenu2(GameModeState* arg0)
{
    struct enterMenu0_Data* temp_r3 = gm_GetGameSceneLoadData(arg0);
    temp_r3->x0 = un_803FC4CC;
    temp_r3->x4 = fn_801B0A8C;
}

void onEnterPrize(GameModeState* arg0)
{
    un_802FFEE0(gm_GetGameSceneLoadData(arg0));
}

void onExitPrize(GameModeState* arg0)
{
    gm_SetPendingSceneIndex(2);
}

void onEnterVs(GameModeState* arg0)
{
    un_802FFF2C(gm_GetGameSceneLoadData(arg0));
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 0x20);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void onEnterResults0(GameModeState* arg0)
{
    struct ResultsMatchInfo* temp_r3 = gm_GetGameSceneLoadData(arg0);
    gm_80177724(temp_r3);
    temp_r3->match_end = vs_exit_data.match_end;
}

void onExitResults0(GameModeState* arg0)
{
    gm_GetGameSceneLeaveData(arg0);
    gm_SetPendingSceneIndex(0);
}

void onEnterIntroEasy(GameModeState* arg0)
{
    struct UnkSoundTestData1* temp_r31 = gm_GetGameSceneLoadData(arg0);
    gm_80168F88();
    un_80301BA8(temp_r31);
}

void onEnterIntroAllstar(GameModeState* arg0)
{
    un_80301C64(gm_GetGameSceneLoadData(arg0));
}

extern int un_803FA258[];

void onEnterGameOver(GameModeState* arg0)
{
    struct DebugGameOverData* data;

    data = gm_GetGameSceneLoadData(arg0);
    data->x0 = 0x1869F;
    data->x8 = 1;
    data->ckind = un_803FA258[0x4D];
    data->slot = 0;
    data->x15 = 0x78;
    data->x18 = HSD_Randi(0x3E8);
    data->x16 = (HSD_Randi(0xA) + 1);
}

void onEnterApproach(GameModeState* arg0)
{
    u8* temp_r3 = gm_GetGameSceneLoadData(arg0);
    temp_r3[1] = 0;

    switch (un_803FA258[0x50]) {
    default:
    case 12:
        temp_r3[0] = 0x19;
        break;
    case 1:
        temp_r3[0] = 3;
        break;
    case 2:
        temp_r3[0] = 7;
        break;
    case 3:
        temp_r3[0] = 9;
        break;
    case 4:
        temp_r3[0] = 0xA;
        break;
    case 5:
        temp_r3[0] = 0xF;
        break;
    case 6:
        temp_r3[0] = 0x14;
        break;
    case 7:
        temp_r3[0] = 0x15;
        break;
    case 8:
        temp_r3[0] = 0x16;
        break;
    case 9:
        temp_r3[0] = 0x17;
        break;
    case 10:
        temp_r3[0] = 0x18;
        break;
    case 11:
        temp_r3[0] = 0x19;
        break;
    }
}

void onEnterResults1(GameModeState* arg0)
{
    u64 sfx_result = 0;
    int i;
    struct DebugResultsData* data = gm_GetGameSceneLoadData(arg0);
    MatchEnd* match_end = &data->match_end;

    data->x0_0 = un_803FA258[0x5E];
    data->x0_1 = un_803FA258[0x5F];
    data->x1 = un_803FA258[0x5A];
    data->x2 = un_803FA258[0x5B];
    data->x3 = un_803FA258[0x5C];
    data->x4 = un_803FA258[0x5D];

    gm_80166A98(match_end, un_803FA258[0x60] & 0xFF, (s8) un_803FA258[0x51],
                un_803FA258[0x56] - 1, (s8) un_803FA258[0x52],
                un_803FA258[0x57] - 1, (s8) un_803FA258[0x53],
                un_803FA258[0x58] - 1, (s8) un_803FA258[0x54],
                un_803FA258[0x59] - 1);

    for (i = 0; i < 4; i++) {
        if (match_end->player_standings[i].slot_type != 3 &&
            match_end->player_standings[i].is_big_loser == 0)
        {
            sfx_result |= lbAudioAx_80026E84(
                match_end->player_standings[i].character_kind);
        }
    }

    lbAudioAx_80026F2C(0x14);
    lbAudioAx_8002702C(0x4, sfx_result);
    gm_80168FC4();
    gm_801701A0();
    PAD_STACK(8);
}

void onExitResults1(GameModeState* arg0)
{
    lbAudioAx_800236DC();
    if (HSD_PadCopyStatus->button & HSD_PAD_L) {
        gm_SetPendingSceneIndex(11); // onEnterResults1
    } else {
        gm_SetPendingSceneIndex(0); // onEnterMenu0
    }
}

void onEnterMemCard(GameModeState* arg0)
{
    struct DebugMemcardData* data = gm_GetGameSceneLoadData(arg0);
    data->x0 = 1;
    data->x4 = 0;
}

void onExitMemCard(GameModeState* arg0)
{
    UNUSED struct DebugMemcardData* data = gm_GetGameSceneLeaveData(arg0);
    gm_SetPendingSceneIndex(0);
}
