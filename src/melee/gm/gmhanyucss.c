#include "gm_unsplit.h"

#include "melee/gm/gm_1601.h"
#include "melee/gm/gm_unsplit.h"
#include "melee/gm/gmvsmelee.h"
#include "melee/gm/types.h"
#include "melee/mn/types.h"

/* 1BED3C */ static void gm_801BED3C(GameModeState*);
/* 1BEDA8 */ static void gm_801BEDA8(GameModeState*);
/* 49BEE8 */ static CSSData gm_8049BEE8;

GameModeState gm_Mode_HanyuCss_States[] = {
    {
        0,
        lbDvdPreload_2,
        0,
        gm_801BED3C,
        gm_801BEDA8,
        {
            GS_CSS,
            &gm_8049BEE8,
            NULL,
        },
    },
    { -1 },
};

void gm_801BED3C(GameModeState* arg0)
{
    CSSData* temp_r31 = gm_GetGameSceneLoadData(arg0);
    temp_r31->data = *gm_801A5244();

    gm_80164F18();
    if (temp_r31->match_type & 1) {
        gm_80164A0C(7);
    }
}

void gm_801BEDA8(GameModeState* arg0)
{
    CSSData* css = gm_GetGameSceneLoadData(arg0);
    VsModeData* vs = gm_801A5244();

    if (css->pending_scene_change == 2) {
        if (css->match_type != 0) {
            css->match_type--;
        } else {
            css->match_type = 0x17;
        }
    } else {
        css->match_type = (css->match_type + 1) % 24;
    }

    *vs = css->data;
}
