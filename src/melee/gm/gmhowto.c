#include "gmhowto.h"

#include "gm_unsplit.h"
#include "gmopening.h"

#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/sobjlib.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbmthp.h>

static int gm_803DD2C0[] = {
    1,  19, 856, 1,  1,   85, 279, 1,  1,   59,  17,  1,  1,     59, 19,
    1,  1,  59,  35, 1,   1,  27,  37, 1,   1,   59,  43, 1,     1,  59,
    39, 1,  1,   59, 499, 1,  1,   67, 892, 1,   240, 2,  63,    1,  1,
    77, 67, 1,   1,  67,  23, 1,   1,  71,  51,  1,   1,  59,    25, 1,
    1,  87, 53,  1,  1,   95, 59,  1,  1,   101, 117, 1,  65536, 1,
};

UNK_T gm_801ACC94(void)
{
    return &gm_803DD2C0;
}

static HSD_GObj* gm_804D6850;

void gm_801ACCA0_OnEnter(void* unused)
{
    HSD_GObj* gobj;
    PAD_STACK(8);

    gobj = GObj_Create(0x13, 0x14, 0);
    gm_801A9DD0(gobj, 0x280, 0x1E0, 8, 0);
    gobj->gxlink_prios = 1 << 0xB;

    gobj = GObj_Create(0xE, 0xF, 0);
    gm_804D6850 = gobj;
    HSD_GObjObject_80390A70(gobj, HSD_SObjLib_804D7960, NULL);
    GObj_SetupGXLink(gobj, lbMthp_8001F67C, 0xB, 0);
    lbMthp_8001F624(gobj, 0x280, 0x1E0);
    lbAudioAx_80023F28(0x24);
    lbAudioAx_80024E50(1);
    lbMthp_8001F410("MvHowto.mth", gm_803DD2C0, 0, 0, 0);
    lbAudioAx_80024E50(0);
    gm_804D6724 = fn_801AA0E8;
}

void gm_801ACD8C_OnFrame(void)
{
    bool var_r31 = false;
    PAD_STACK(4);

    lbMthp_8001F578();
    lbMthp_8001F5C4();
    if (gmMainLib_8046B0F0.xC && lbMthp_8001F604() == 0) {
        var_r31 = true;
    }
    if (lbMthp_8001F604() != 0 || (gm_801A36A0(4) & 0x1100) || var_r31) {
        lbAudioAx_800236DC();
        lbAudioAx_80023694();
        if (var_r31 != 0) {
            gm_801A4B74();
        } else {
            gm_801A4B60();
        }
        if (gm_801A36A0(4) & 0x1100) {
            lbAudioAx_80024030(1);
            gm_801A42E8(MJ_TITLE);
            gm_801A42D4();
        } else if (gmMainLib_8015DB00() != 5) {
            gmMainLib_8015DB18();
            gm_SetScenePendingMinor(0);
        }
    }
}
