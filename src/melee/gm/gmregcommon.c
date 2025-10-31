#include "gmregcommon.h"

#include <melee/ft/forward.h>

#include <melee/gm/gm_unsplit.h>
#include <melee/gm/types.h>

#define NUM_OPPONENTS 3

int gm_8017BE84(u32 arg0)
{
    return (arg0 >> 3) & 0x1F;
}

int gm_8017BE8C(s8* opps)
{
    int opp_count = 0;
    int i;
    for (i = 0; i < NUM_OPPONENTS; i++) {
        if (opps[i] != CHKIND_NONE) {
            opp_count++;
        }
    }
    return opp_count;
}

void gmRegSetupEnemyColorTable(s8 ckind, u8 color, s8* ckinds, u8* colors)
{
    u8 ncolors = gm_80169238(ckind);
    int k;
    int j;
    int i;
    bool result;

    for (i = 0; i < NUM_OPPONENTS; i++) {
        if (ckinds[i] != CHKIND_NONE && ckind == ckinds[i] &&
            color == colors[i])
        {
            colors[i] = 0xFF;
        }
    }

    for (i = 0; i < NUM_OPPONENTS; i++) {
        if (ckinds[i] == CHKIND_NONE) {
            continue;
        }
        if (colors[i] != 0xFF) {
            continue;
        }
        for (j = 0; j < ncolors; j++) {
            if (color == j) {
                continue;
            }
            for (k = 0; k < NUM_OPPONENTS; k++) {
                result = true;
                if (i == k || ckinds[k] == CHKIND_NONE) {
                    continue;
                }
                if (j == colors[k]) {
                    result = false;
                    break;
                }
            }
            if (result) {
                colors[i] = j;
                break;
            }
        }
        if (colors[i] == 0xFF) {
            OSReport(
                "Error : not find color in gmRegSetupEnemyColorTable()\n");
            __assert(__FILE__, 0xDA, "0");
        }
    }
}
