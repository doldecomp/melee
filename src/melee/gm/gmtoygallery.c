#include "gmtoygallery.h"

#include "gm_unsplit.h"

#include "gm_unsplit.h"
#include "types.h"

/* 1BEC80 */ static void onExit(GameModeState*);
/* 4D6908 */ static UNK_T exit_data[2];
/* 4D6910 */ static UNK_T toy_lottery_exit_data[2];
/* 4D6918 */ UNK_T toy_collection_exit_data[2];

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
