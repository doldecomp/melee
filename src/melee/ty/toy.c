#include "toy.h"

#include "inlines.h"

#include "un/un_2FC9.h"

#include "mn/mnsoundtest.h"

#include "baselib/controller.h"

/// #un_80305058

/// #un_803053C4

/// #Trophy_SetUnlockState

/// #un_80305918

s32 un_80305B88(void) {
    int i;
    u32 button;
    PAD_STACK(4);

    for (i = 0; i < 4; i++) {
        if (button = HSD_PadCopyStatus[(u8) i].trigger) {
            gm_801677E8(i);
            break;
        }
    }
    return button;
}

s32 un_80305C44(void) {
    int i = 0;
    u32 button;
    PAD_STACK(4);

    for (i = 0; i < 4; i++) {
        if (button = HSD_PadCopyStatus[(u8) i].button) {
            gm_801677E8(i);
            break;
        }
    }
    return button;
}

/// #un_80305D00

float un_80305DB0(void) {
    float ret = 0.0F;
    int i;

    for (i = 0; i < 4; i++) {
        ret = HSD_PadGetNmlStickY(i);

        if (ABS(ret) > 0.1F) {
            gm_801677E8(i);
            break;
        }
    }

    return ret;
}

/// #un_80305EB4

/// #un_80305FB8

/// #un_803060BC

/// #un_803062BC

/// #un_803062EC

/// #un_803063D4

/// #un_803064B8

/// #un_8030663C

/// #un_803067BC

/// #un_803068E0

/// #un_80306930

/// #un_80306954

/// #un_80306A0C

/// #un_80306A48

/// #un_80306B18

/// #un_80306BB8

/// #un_80306C5C

/// #Toy_RemoveUserData

/// #un_80306D14

/// #un_80306D70

/// #un_80306EEC

/// #un_80307018

/// #un_8030715C

/// #un_80307470

/// #un_803075E8

/// #un_80307828

/// #un_803078E4

/// #un_80307BA0

/// #fn_80307E84

/// #un_80307F64

/// #un_8030813C

/// #un_80308250

/// #un_803082F8

/// #un_80308328

/// #un_80308354

/// #un_803083D8

/// #un_803084A0

/// #un_803087F4

/// #un_80308DC8

/// #un_80308F04

/// #un_80309338

/// #fn_80309404

/// #fn_8030B530

/// #fn_8030E110

/// #un_8030FA50

/// #un_8030FE48

void un_803102C4(s8 arg0)
{
    M2C_FIELD(un_804D6E6C, s8*, 4) = arg0;
}

/// #un_803102D0

/// #un_80310324

/// #un_80310660

/// #un_803109A0

/// #un_80310B48

/// #un_803114E8

/// #un_80311680

/// #un_80311788

/// #un_80311960

/// #un_80311AB0_OnEnter

/// #un_80311F5C

/// #un_80312018_OnFrame

/// #un_80312050

/// #un_803122D0_OnInit

/// #un_8031234C
