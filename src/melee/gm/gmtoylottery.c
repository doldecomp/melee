#include "gm_unsplit.h"

#include "melee/gm/gm_16F1.h"
#include "melee/gm/gm_unsplit.h"
#include "melee/gm/types.h"
#include "melee/lb/lbcardgame.h"
#include "melee/lb/lbcardnew.h"
#include "melee/lb/types.h"

/* 1BECA8 */ static void gm_801BECA8(GameScene*);
/* 1BECD0 */ static void gm_801BECD0(GameScene*);
/* 4D6910 */ static UNK_T gm_804D6910[2];

GameScene gm_803DFA48_Scenes[] = {
    {
        0,
        lbDvdPreload_2,
        0,
        gm_801BECA8,
        gm_801BECD0,
        {
            GS_TOY_LOTTERY,
            NULL,
            &gm_804D6910,
        },
    },
    { -1 },
};

void gm_801BECA8(GameScene* arg)
{
    lb_8001C550();
    lb_8001D164(0);
}

void gm_801BECD0(GameScene* arg)
{
    gm_80172898(4);
    if (!gm_80173754(1, 0)) {
        gm_SetPendingGameMode(GM_MENU);
        gm_SetNewGameModePending();
    }
}
