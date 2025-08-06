#include "gmomake15.h"

#include "gm_unsplit.h"
#include "gmopening.h"

#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/sobjlib.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbmthp.h>

static HSD_GObj* gm_804D6858;

void gm_801ACE94_OnEnter(void* unused)
{
    HSD_GObj* gobj;
    HSD_SObj_803A477C_t* temp_r3_2;

    gobj = GObj_Create(0x13, 0x14, 0);
    gm_801A9DD0(gobj, 0x280, 0x1E0, 8, 0);
    gobj->gxlink_prios = 0x800;

    gobj = GObj_Create(0xE, 0xF, 0);
    gm_804D6858 = gobj;
    HSD_GObjObject_80390A70(gobj, HSD_SObjLib_804D7960, NULL);
    GObj_SetupGXLink(gobj, lbMthp_8001F67C, 0xB, 0);
    temp_r3_2 = lbMthp_8001F624(gobj, 0x1C0, 0x150);
    temp_r3_2->x10 = 96.0f;
    temp_r3_2->x14 = 72.0f;
    lbAudioAx_80023F28(0x52);
    lbAudioAx_80024E50(1);
    lbMthp_8001F410("MvOmake15.mth", NULL, 0, 0, 0);
    lbAudioAx_80024E50(0);
    gm_804D6724 = fn_801AA0E8;
}

void gm_801ACF8C_OnFrame(void)
{
    bool var_r31 = false;
    PAD_STACK(4);

    lbMthp_8001F578();
    lbMthp_8001F5C4();
    if (gmMainLib_8046B0F0.xC != 0 && lbMthp_8001F604() == 0) {
        var_r31 = true;
    }
    if (lbMthp_8001F604() != 0 || (gm_801A36A0(4) & 0x1100) || var_r31) {
        lbAudioAx_800236DC();
        if (var_r31 != 0) {
            gm_801A4B74();
        } else {
            gm_801A4B60();
        }
        gmMainLib_8015DB0C(0);
        if ((gm_801A36A0(4) & 0x1100) || var_r31) {
            if (var_r31 == 0) {
                lbAudioAx_80024030(1);
            }
            gm_801A42E8(0);
            gm_801A42D4();
        }
    }
}
