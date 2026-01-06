#include "if_2F72.h"

#include "if/ifall.h"
#include "lb/lb_00B0.h"
#include "lb/lbarchive.h"

#include <baselib/gobj.h>
#include <baselib/gobjplink.h>

static void* lbl_804A1340[13];

void if_802F7E24(void)
{
    memzero(lbl_804A1340, 0x34);
    lbArchive_LoadSections(*ifAll_802F3690(), lbl_804A1340,
                           "ifPrize_scene_data", 0);
}

void if_802F7E7C(void)
{
    HSD_GObj** data = (HSD_GObj**) lbl_804A1340;
    s32 i = 0;
    HSD_GObj** base = (HSD_GObj**) lbl_804A1340;

    do {
        if (data[1] != NULL) {
            HSD_GObjPLink_80390228(data[1]);
        }
        if (data[2] != NULL) {
            HSD_GObjPLink_80390228(data[2]);
        }
        i++;
        data += 2;
    } while (i < 6);
    memzero(base, 0x34);
}
