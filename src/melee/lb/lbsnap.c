#include <platform.h>

#include <dolphin/card/CARDMount.h>

struct Unk80433380 {
    char filler0[0x40];
    int unk40[3];
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
