#include "gm_unsplit.h"

#include "melee/gm/gm_unsplit.h"
#include "melee/gm/gmmain_lib.h"
#include "melee/gm/types.h"
#include "melee/lb/types.h"
#include "melee/mn/types.h"

/* 1BEE58 */ static void gm_801BEE58(GameModeState*);
/* 49C030 */ static CSSData gm_8049C030;

GameModeState gm_Mode_HanyuSss_States[] = {
    {
        0,
        lbDvdPreload_2,
        0,
        gm_801BEE58,
        NULL,
        {
            GS_SSS,
            &gm_8049C030,
            NULL,
        },
    },
    { -1 },
};

void gm_801BEE58(GameModeState* arg0)
{
    SSSData* var_r3 = gm_GetGameSceneLoadData(arg0);
    var_r3->data = gmMainLib_804D3EE0->unk_590;
}
