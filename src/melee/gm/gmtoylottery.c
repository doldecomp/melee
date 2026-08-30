#include "gm_unsplit.h"

#include "melee/gm/gm_16F1.h"
#include "melee/gm/gm_unsplit.h"
#include "melee/gm/types.h"
#include "melee/lb/lbcardgame.h"
#include "melee/lb/lbcardnew.h"
#include "melee/lb/types.h"

/* 1BECA8 */ static void onEnter(GameModeState*);
/* 1BECD0 */ static void onExit(GameModeState*);
/* 4D6910 */ static UNK_T exit_data[2];

GameModeState gm_Mode_ToyLottery_States[] = {
    {
        0,
        lbDvdPreload_2,
        0,
        onEnter,
        onExit,
        {
            GS_TOY_LOTTERY,
            NULL,
            &exit_data,
        },
    },
    { -1 },
};

void onEnter(UNUSED GameModeState* state)
{
    lb_8001C550();
    lb_8001D164(0);
}

void onExit(UNUSED GameModeState* state)
{
    gm_80172898(4);
    if (!gm_80173754(1, 0)) {
        gm_SetPendingGameMode(GM_MENU);
        gm_SetNewGameModePending();
    }
}
