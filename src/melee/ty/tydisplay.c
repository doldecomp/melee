#include "tydisplay.h"

#include "gm/gm_1A3F.h"
#include "gm/gm_1A45.h"
#include "if/textlib.h"
#include "ty/toy.h"
#include "ty/tyfigupon.h"
#include "ty/tylist.h"
#include "ty/types.h"

#include <baselib/random.h>

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

/// #un_8031B9DC

/// #un_8031BA78

/// #un_8031BB34

/// #un_8031BB94

/// #un_8031BBF4

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
