#include "gmtoygallery.h"

#include "gm_unsplit.h"

#include "melee/gm/gm_unsplit.h"
#include "melee/gm/types.h"

/* 1BEC80 */ static void onExit(GameModeState*);
/* 4D6908 */ static UNK_T exit_data[2];

GameModeState gm_Mode_ToyGallery_States[] = {
    {
        0,
        lbDvdPreload_2,
        0,
        NULL,
        onExit,
        {
            GS_TOY_GALLERY,
            NULL,
            &exit_data,
        },
    },
    { -1 },
};

void onExit(UNUSED GameModeState* state)
{
    gm_SetPendingGameMode(GM_MENU);
    gm_SetNewGameModePending();
}
