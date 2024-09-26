#include <platform.h>

#include <dolphin/card/CARDMount.h>

struct Unk80433380_48 {
    s32 unk0;
    char _4[0x408 - 0x4];
};

struct Unk80433380 {
    char filler0[0x48];
    struct Unk80433380_48* x48;
    int x4C_cardState[2];
    bool x54_stateChanged[3];
};

struct Unk80433380 lb_80433380;

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

/// #lbSnap_8001D338

int lbSnap_8001D350(int i)
{
    struct Unk80433380_48* ptr = &lb_80433380.x48[i];
    if (ptr->unk0 == 0 && lb_80433380.x54_stateChanged[i]) {
        ptr->unk0 = 8;
    }
    return ptr->unk0;
}

/// #lbSnap_8001D394

/// #lbSnap_8001D3B0

/// #lbSnap_8001D3CC

/// #lbSnap_8001D3E8

/// #lbSnap_8001D40C

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

/// #lbSnap_8001E27C

/// #lbSnap_8001E290
