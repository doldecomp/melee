#include "lbsnap.static.h"

#include "lbcardgame.h"

#include <dolphin/card/CARDMount.h>

void lbSnap_8001D2BC(void)
{
    int i;
    for (i = 0; i < (signed) ARRAY_SIZE(lb_80433380.x4C_cardState); i++) {
        int prev = lb_80433380.x4C_cardState[i];
        lb_80433380.x4C_cardState[i] = CARDProbe(i);
        if (lb_80433380.x4C_cardState[i] != prev) {
            lb_80433380.x54_stateChanged[i] = true;
        }
    }
}

int lbSnap_8001D338(int arg0)
{
    return lb_80433380.x54_stateChanged[arg0];
}

int lbSnap_8001D350(int i)
{
    struct Unk80433380_48* ptr = &lb_80433380.x48[i];
    if (ptr->unk0 == 0 && lb_80433380.x54_stateChanged[i]) {
        ptr->unk0 = 8;
    }
    return ptr->unk0;
}

int lbSnap_8001D394(int arg0)
{
    return lb_80433380.x48[arg0].unk4;
}

int lbSnap_8001D3B0(int arg0)
{
    return lb_80433380.x48[arg0].unk8;
}

int lbSnap_8001D3CC(int arg0)
{
    return lb_80433380.x48[arg0].unkC;
}

int lbSnap_8001D3E8(int arg0, int arg1)
{
    return lb_80433380.x48[arg0].unk16[arg1].unk0;
}

int lbSnap_8001D40C(int arg0)
{
    struct Unk80433380_48* ptr = &lb_80433380.x48[arg0];
    lb_80433380.x54_stateChanged[arg0] = 0;
    ptr->unk0 = lb_8001BFD8(arg0, &ptr->unk10, &ptr->unk8, &ptr->unkC);
    if (ptr->unk0 == 0) {
        int i;
        int j = 0;
        struct Unk80433380_48* ptr2 = ptr;
        for (i = 0; i < 0x7F; i++) {
            if (ptr2->unk14 == -1) {
                break;
            }
            ptr2 += 2;
            j++;
        }
        ptr->unk4 = j;
    }
    return ptr->unk0;
}

/// #lbSnap_8001D4A4

/// #lbSnap_8001D5FC

/// #lbSnap_8001D7B0

/// #lbSnap_8001DA5C

/// #lbSnap_8001DC0C

/// #lbSnap_8001DE8C

/// #lbSnap_8001DF20

/// #lbSnap_8001DF6C

/// #lbSnap_8001E058

s32 lbSnap_8001E204(void)
{
    return 0x3E840;
}

s32 lbSnap_8001E210(void)
{
    return 0x840;
}

/// #lbSnap_8001E218

void lbSnap_8001E27C(void)
{
    lb_80433380.unk_0 = 0;
    lb_80433380.x48 = NULL;
}

/// #lbSnap_8001E290
