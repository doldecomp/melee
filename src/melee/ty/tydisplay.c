#include "tydisplay.h"

<<<<<<< HEAD
=======
#include "gm/gm_1A3F.h"
#include "gm/gm_1A45.h"
>>>>>>> 8c8cc9bff (Fix build: add missing includes and prototypes for ty module)
#include "if/textlib.h"
#include "ty/toy.h"
#include "ty/tyfigupon.h"
#include "ty/tylist.h"

#include <baselib/random.h>

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
