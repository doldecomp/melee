#include "gmtitlemode.h"

#include "db/db.h"
#include "gm/gm_1A3F.h"
#include "gm/gm_unsplit.h"
#include "gm/types.h"
#include "lb/lbdvd.h"

#include <baselib/controller.h>

struct exitData {
    int buttons;
    UNK_T x4;
};

/* 1B089C */ static void onExit(GameModeState*);
/* 4D6878 */ static struct exitData exit_data;

/* 3DD6A0 */ GameModeState gm_Mode_Title_States[] = {
    {
        0,
        lbDvdPreload_3,
        0,
        gmTitleMode_OnEnter,
        onExit,
        {
            GS_TITLE,
            NULL,
            &exit_data,
        },
    },
    { -1 },
};

void gmTitleMode_OnEnter(UNUSED GameModeState* state)
{
    lbDvd_800174BC();
}

void onExit(GameModeState* scene)
{
    int* buttons = gm_GetGameSceneLeaveData(scene);
    if (DbLevel >= DbLKind_DebugRom) {
        if (*buttons & HSD_PAD_A) {
            gm_SetPendingGameMode(GM_DEBUG_VS);
        } else if (*buttons & HSD_PAD_START) {
            gm_80173EEC();
            gm_80172898(0x100);
            if (!gm_80173754(1, 0)) {
                gm_SetPendingGameMode(GM_MENU);
            }
        } else if (*buttons & HSD_PAD_X) {
            gm_SetPendingGameMode(GM_DEBUG_SOUND_TEST);
        } else if (*buttons & HSD_PAD_Y) {
            gm_SetPendingGameMode(GM_DEBUG);
        } else {
            gm_801BF708(1);
            gm_SetPendingGameMode(GM_OPENING_MV);
        }
    } else if (*buttons & HSD_PAD_START) {
        gm_80173EEC();
        gm_80172898(0x100);
        if (!gm_80173754(1, 0)) {
            gm_SetPendingGameMode(GM_MENU);
        }
    } else {
        gm_801BF708(1);
        gm_SetPendingGameMode(GM_OPENING_MV);
    }
    gm_SetNewGameModePending();
}
