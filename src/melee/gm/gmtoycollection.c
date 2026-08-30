#include "gm_unsplit.h"

#include "melee/gm/gm_unsplit.h"
#include "melee/gm/types.h"
#include "melee/lb/types.h"

/* 1BED14 */ static void gm_801BED14(GameModeState*);
/* 4D6910 */ static UNK_T gm_804D6918[2];

GameModeState gm_Mode_ToyCollection_States[] = {
    {
        0,
        lbDvdPreload_2,
        0,
        NULL,
        gm_801BED14,
        {
            GS_TOY_COLLECTION,
            NULL,
            &gm_804D6918,
        },
    },
    { -1 },
};

void gm_801BED14(GameModeState* arg)
{
    gm_SetPendingGameMode(GM_MENU);
    gm_SetNewGameModePending();
}
