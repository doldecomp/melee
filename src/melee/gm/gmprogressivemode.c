#include "gmprogressivemode.h"

#include "gm/gm_1A3F.h"

/* 1BF8F8 */ static void gm_801BF8F8(GameModeState*);
/* 1BF920 */ static void gm_801BF920(GameModeState*);
/* 4D6938 */ static UNK_T gm_804D6938;
/* 4D693C */ static UNK_T gm_804D693C;

GameModeState gm_Mode_ProgScan_States[] = {
    {
        0,
        lbDvdPreload_2,
        0,
        gm_801BF8F8,
        gm_801BF920,
        {
            GS_PROG_SCAN,
            &gm_804D6938,
            &gm_804D693C,
        },
    },
    { -1 },
};

void gm_801BF8F8(GameModeState* arg0)
{
    int* val = gm_GetGameSceneLoadData(arg0);
    *val = 1;
}

void gm_801BF920(GameModeState* arg0)
{
    gm_GetGameSceneLeaveData(arg0);
    gm_ChangeGameModeAfterCurrentScene(GM_BOOT);
}
