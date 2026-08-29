#include "gmtoygallery.h"

#include "gm_unsplit.h"

#include "melee/gm/gm_unsplit.h"
#include "melee/gm/types.h"

/* 1BEC80 */ static void gm_801BEC80(GameScene*);
/* 4D6908 */ static UNK_T gm_804D6908[2];

GameScene gm_803DFA18_Scenes[] = {
    {
        0,
        lbDvdPreload_2,
        0,
        NULL,
        gm_801BEC80,
        {
            GS_TOY_GALLERY,
            NULL,
            &gm_804D6908,
        },
    },
    { -1 },
};

void gm_801BEC80(GameScene* arg)
{
    gm_SetPendingGameMode(GM_MENU);
    gm_SetNewGameModePending();
}
