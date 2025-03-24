#include "vi.h"

#include "cm/camera.h"
#include "gm/gm_1601.h"
#include "gm/gm_1A36.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"

char* un_803FFFA8[26] = {
    "PlCaDViWaitAJ.dat", "PlDkDViWaitAJ.dat", "PlFxDViWaitAJ.dat",
    "PlGwDViWaitAJ.dat", "PlKbDViWaitAJ.dat", "PlKpDViWaitAJ.dat",
    "PlLkDViWaitAJ.dat", "PlLgDViWaitAJ.dat", "PlMrDViWaitAJ.dat",
    "PlMsDViWaitAj.dat", "PlMtDViWaitAJ.dat", "PlNsDViWaitAJ.dat",
    "PlPeDViWaitAJ.dat", "PlPkDViWaitAJ.dat", "PlPpDViWaitAJ.dat",
    "PlPrDViWaitAJ.dat", "PlSsDViWaitAJ.dat", "PlYsDViWaitAJ.dat",
    "PlZdDViWaitAJ.dat", "PlSkDViWaitAJ.dat", "PlFcDViWaitAJ.dat",
    "PlClDViWaitAJ.dat", "PlDrDViWaitAJ.dat", "PlFeDViWaitAJ.dat",
    "PlPcDViWaitAJ.dat", "PlGnDViWaitAJ.dat"
};

char* un_8031C99C(s32 index)
{
    return un_803FFFA8[index];
}

void un_8031C9B4(s32 arg0, s32 arg1)
{
    u8 r3 = gm_8017E440();
    if (r3 != 4) {
        gm_801678F8(r3, arg0, arg1);
    }
}

void un_8031CA04(HSD_GObj* arg0)
{
    Camera_800310A0(2U);
    arg0->gxlink_prios = 9;
    HSD_GObj_80390ED0(arg0, 7);
    Camera_800310A0(1U);
    arg0->gxlink_prios = 8;
    HSD_GObj_80390ED0(arg0, 7);
    Camera_800310A0(0U);
    arg0->gxlink_prios = 8;
    HSD_GObj_80390ED0(arg0, 7);
    Camera_800313E0(arg0, 1);
}

void un_8031CAAC(void)
{
    u64 temp_ret;
    temp_ret = gm_801A36A0(gm_8017E430());
    if ((temp_ret & 0x1000) != 0) {
        lbAudioAx_800236DC();
        lbAudioAx_80023694();
        lb_800145F4();
        gm_801A4B60();
    }
}
