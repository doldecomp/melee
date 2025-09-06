#include "gm_1BFA.h"

#include "gm_unsplit.h"

#include <melee/gm/types.h>

extern UNK_T gm_804D6860[];
extern StartMeleeData gm_80480530;
extern MatchExitInfo gm_80479D98;
extern UNK_T un_804A1F48[];

MinorScene gm_803DFE48_MinorScenes[] = {
    {
        0,
        2,
        0,
        gm_801BFA6C,
        NULL,
        {
            MN_APPROACH,
            gm_804D6860,
            gm_804D6860,
        },
    },
    {
        1,
        2,
        0,
        gm_801BFABC,
        gm_801BFBA8,
        {
            MN_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    {
        2,
        2,
        0,
        gm_801BFCFC,
        gm_801BFF7C,
        {
            MN_PRIZE_INTERFACE,
            un_804A1F48,
            NULL,
        },
    },
    { -1 },
};

/// #gm_801BFA6C

void gm_801BFABC(MinorScene* arg0)
{
    lbl_8046DBD8_t* temp_r31;
    StartMeleeData* temp_r30;
    u8 tmp;

    temp_r30 = gm_801A427C(arg0);
    temp_r31 = gm_801736DC();
    gm_80167A64(&temp_r30->rules);
    gm_80167A14(temp_r30->players);
    temp_r30->rules.x0_6 = false;
    temp_r30->rules.x0_0 = 1;
    temp_r30->rules.x0_3 = 2;
    temp_r30->rules.xE = gm_8016075C(gm_80164024(temp_r31->x4));
    gm_801B0620(&temp_r30->players[0], temp_r31->x0, temp_r31->x1, 1,
                temp_r31->x2);
    gm_801B0664(&temp_r30->players[1], temp_r31->x4, 0, 1, 1);
    tmp = temp_r31->x3;
    temp_r30->players[0].xA = tmp;
    temp_r30->players[1].xA = 0x78;
    temp_r30->players[1].xE = 4;
    temp_r30->players[1].cpu_level = gm_80172CC0(temp_r31->x4, tmp);
    gm_8016F088(temp_r30);
}

/// #gm_801BFBA8

/// #gm_801BFC60

/// #gm_801BFCFC

/// #gm_801BFF7C
