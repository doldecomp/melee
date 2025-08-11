#include "gm_1BF9.h"

#include "un/un_3028.h"

#include <melee/gm/gm_unsplit.h>
#include <melee/gm/types.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lblanguage.h>
#include <melee/ty/toy.h>
#include <melee/ty/tylist.h>
#include <melee/un/un_2FC9.h>

typedef struct {
    u32 x0;
    u8 x4;
    u8 x5;
} unk_struct_0_t;

static unk_struct_0_t gm_804D6940;
static u32 gm_804D6948[2];

MinorScene gm_803DFDD8_MinorScenes[] = {
    {
        0,
        1,
        0,
        gm_801BF948,
        gm_801BF9A8,
        42,
        &gm_804D6940,
        gm_804D6948,
    },
    {
        -1,
    },
};

void gm_801BF948(MinorScene* scene)
{
    unk_struct_0_t* temp_r3 = gm_801A427C(scene);
    temp_r3->x4 = 0;
    temp_r3->x0 = 0;
    if (gmMainLib_8046B0F0.x0 == 1) {
        temp_r3->x5 = 0;
        return;
    }
    gm_801BF708(0);
    temp_r3->x5 = 24;
}

enum {
    TROPHY_PIKMIN = 0x113,
};

enum {
    LANG_JP = 0,
};

void gm_801BF9A8(MinorScene* data)
{
    struct sceneData* scene_data = gm_801A4284(data);

    if (!un_803048C0(TROPHY_PIKMIN)) {
        if (!lb_8001C2D8(0, "01",
                         lbLang_GetLanguageSetting() == LANG_JP ? "GPIJ"
                                                                : "GPIE",
                         "Pikmin dataFile"))
        {
            un_803124BC();
            Trophy_SetUnlockState(TROPHY_PIKMIN, true);
        }
    }

    // Set scene exit callback?
    gm_801A4330(lb_8001CE78);

    // Enter major scene
    // Gekko "boot to CSS" code changes scene_id to a hardcoded 2
    gm_801A42F8(scene_data->scene_id);
}

MinorScene gm_803DFE18_MinorScenes[] = {
    {
        0,
        3,
        0,
        gm_801BFA3C,
        0,
        42,
        &gm_804D6940,
        gm_804D6948,
    },
    {
        -1,
    },
};

void gm_801BFA3C(MinorScene* scene)
{
    unk_struct_0_t* temp_r3 = gm_801A427C(scene);
    temp_r3->x4 = 0;
    temp_r3->x0 = 1;
}
