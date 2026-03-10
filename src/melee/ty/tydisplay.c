#include "tydisplay.h"

#include "gm/gm_1A3F.h"
#include "gm/gm_1A45.h"
#include "if/textlib.h"
#include "lb/lblanguage.h"
#include "ty/toy.h"
#include "ty/tyfigupon.h"
#include "ty/tylist.h"
#include "ty/types.h"

#include <baselib/random.h>

extern char un_804D5AC0[];

/// #un_803181BC

void un_803182D4_OnFrame(void)
{
    TyModeState* state = (TyModeState*) un_804A284C;

    if (state->x4 != 0) {
        un_803181BC();
        gm_801A4B60();
    }
}

/// #un_8031830C

/// #un_80318714

/// #un_80318B1C

/// #un_80318CB4

/// #un_80319540

/// #un_80319994

/// #un_80319EF0

/// #fn_8031A4EC

/// #fn_8031A94C

/// #un_8031B1FC

/// #un_8031B328

/// #un_8031B460_OnEnter

/// #un_8031B850

void un_8031B9A4_OnFrame(void)
{
    TyModeState* state = (TyModeState*) un_804A284C;

    if (state->x4 != 0) {
        un_8031B850();
        gm_801A4B60();
    }
}

void* un_8031B9DC(s32 id)
{
    s32* p;
    s32 val;
    bool found = false;

    if (lbLang_IsSettingUS()) {
        p = un_804D6EAC;
        while (val = *p, val != -1) {
            if (val == id) {
                found = true;
                break;
            }
            p = (s32*) ((u8*) p + 0x10);
        }
    }

    if (!found) {
        p = un_804D6EB0;
        while (val = *p, val != -1) {
            if (val == id) {
                break;
            }
            p = (s32*) ((u8*) p + 0x10);
        }
    }

    return p;
}

/// #un_8031BA78

/// #un_8031BB34

char* un_8031BB94(s8 idx)
{
    char* table[] = {
        un_804D5AC0,
        "ToyDspMycharaCmA_Top_matanim_joint",
        "ToyDspMycharaCmB_Top_matanim_joint",
        "ToyDspMycharaCmC_Top_matanim_joint",
        "ToyDspMycharaCmD_Top_matanim_joint",
        "ToyDspMycharaCmE_Top_matanim_joint",
        "ToyDspMycharaR1A_Top_matanim_joint",
        "ToyDspMycharaR1B_Top_matanim_joint",
        "ToyDspMycharaR1C_Top_matanim_joint",
        "ToyDspMycharaR1D_Top_matanim_joint",
        "ToyDspMycharaR1E_Top_matanim_joint",
        "ToyDspMycharaR2A_Top_matanim_joint",
        "ToyDspMycharaR2B_Top_matanim_joint",
        "ToyDspMycharaR2C_Top_matanim_joint",
        "ToyDspMycharaR2D_Top_matanim_joint",
        "ToyDspMycharaR2E_Top_matanim_joint",
        "ToyDspMapA_Top_matanim_joint",
        "ToyDspMapB_Top_matanim_joint",
        "ToyDspMapC_Top_matanim_joint",
        "ToyDspMapD_Top_matanim_joint",
        "ToyDspMapE_Top_matanim_joint",
        "ToyDspFgseriesA_Top_matanim_joint",
        "ToyDspFgseriesB_Top_matanim_joint",
        "ToyDspFgseriesC_Top_matanim_joint",
        "ToyDspFgseriesD_Top_matanim_joint",
        "ToyDspFgseriesE_Top_matanim_joint",
        "ToyDspFgetcA_Top_matanim_joint",
        "ToyDspFgetcB_Top_matanim_joint",
        "ToyDspFgetcC_Top_matanim_joint",
        "ToyDspFgetcD_Top_matanim_joint",
        "ToyDspFgetcE_Top_matanim_joint",
        "ToyDspPokemonA_Top_matanim_joint",
        "ToyDspPokemonB_Top_matanim_joint",
        "ToyDspPokemonC_Top_matanim_joint",
        "ToyDspPokemonD_Top_matanim_joint",
        "ToyDspPokemonE_Top_matanim_joint",
        "ToyDspItemA_Top_matanim_joint",
        "ToyDspItemB_Top_matanim_joint",
        "ToyDspItemC_Top_matanim_joint",
        "ToyDspItemD_Top_matanim_joint",
        "ToyDspItemE_Top_matanim_joint",
        un_804D5AC0,
        un_804D5AC0,
    };

    if (idx == -1) {
        idx = 0;
    }

    return table[idx];
}

s32 un_8031BBF4(s8 arg0)
{
    char* table[] = {
        "TyQuesD.dat",  "TyMycCmA.dat", "TyMycCmB.dat",
        "TyMycCmC.dat", "TyMycCmD.dat", "TyMycCmE.dat",
        "TyMycR1A.dat", "TyMycR1B.dat", "TyMycR1C.dat",
        "TyMycR1D.dat", "TyMycR1E.dat", "TyMycR2A.dat",
        "TyMycR2B.dat", "TyMycR2C.dat", "TyMycR2D.dat",
        "TyMycR2E.dat", "TyMapA.dat",   "TyMapB.dat",
        "TyMapC.dat",   "TyMapD.dat",   "TyMapE.dat",
        "TySeriA.dat",  "TySeriB.dat",  "TySeriC.dat",
        "TySeriD.dat",  "TySeriE.dat",  "TyEtcA.dat",
        "TyEtcB.dat",   "TyEtcC.dat",   "TyEtcD.dat",
        "TyEtcE.dat",  "TyPokeA.dat",  "TyPokeB.dat",
        "TyPokeC.dat",  "TyPokeD.dat",  "TyPokeE.dat",
        "TyItemA.dat",  "TyItemB.dat",  "TyItemC.dat",
        "TyItemD.dat",  "TyItemE.dat",  "TyStandD.dat",
        "TyQuesD.dat",
    };
    if (arg0 == -1) {
        arg0 = 0;
    }
    return (s32) table[arg0];
}

/// #un_8031BC54

/// #un_8031BF34

/// #un_8031C1D0

void tyDisplay_8031C2CC(void)
{
    un_803124BC();
}

s32 tyDisplay_8031C2EC(void)
{
    if (un_80304B0C(5) != 0) {
        if (HSD_Randi(2) == 0) {
            return un_80305058(2, 5, 1, 65.0f);
        }
    }
    return un_80305058(2, 0, 1, 60.0f);
}

/// #un_8031C354

/// #un_8031C454

/// #un_8031C5E4

/// #un_8031C8B8
