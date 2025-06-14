#include "gm_1A45.h"

#include "gm_1A36.h"

#include "lb/lb_00F9.h"
#include "lb/lbcardgame.h"
#include "lb/lbdvd.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbaudio_ax.h"
#include "un/un_2FC9.h"

#include <baselib/controller.h>
#include <baselib/sobjlib.h>
#include <baselib/particle.h>
#include <baselib/gobjproc.h>

#include "gm_1A45.static.h"

static u64 gm_803DA888[8] = {
    0,
    0x82FFFA,
    0,
    0x8EFFFA,
    0x800FFA,
    0x808FFA,
    0x800FFA,
    0,
};

bool gm_801A45E8(int bit)
{
    return gm_80479D58.unk_10 & (1ULL << bit);
}

u8 gm_801A4624(void)
{
    return gm_80479D58.unk_10;
}

void gm_801A4634(int bit)
{
    gm_80479D58.unk_10 |= 1ULL << bit;
}

void gm_801A4674(int bit)
{
    gm_80479D58.unk_10 &= ~(1ULL << bit);
}

bool gm_801A46B8(int bit)
{
    return gm_80479D58.unk_12 & (1ULL << bit);
}

bool fn_801A46F4(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        HSD_PadStatus* pad = &HSD_PadMasterStatus[(u8) i];
        if (pad->err == 0 && (pad->trigger & 8) && (pad->button & HSD_PAD_X)) {
            return true;
        }
    }
    return false;
}

bool fn_801A47E4(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        HSD_PadStatus* pad = &HSD_PadMasterStatus[(u8) i];
        if (pad->err == 0 && (pad->trigger & 0x10)) {
            return true;
        }
    }
    return false;
}

u64 gm_801A48A4(u8 arg0)
{
    u32 i;
    u64 result = 0;

    for (i = 0; i < 8; i++) {
        if (arg0 & 1) {
            result |= gm_803DA888[i];
        }
        arg0 >>= 1;
    }

    return result;
}

/// #gm_801A4970

void gm_801A4B08(UNK_T arg0, UNK_T arg1)
{
    gm_80479D58.unk_14 = arg0;
    gm_80479D58.unk_18 = arg1;
}

/// #gm_801A4B1C

void gm_801A4B40(int arg0)
{
    M2C_FIELD(&gm_80479D58, s32*, 0x30) = arg0;
}

void gm_801A4B50(int arg0)
{
    M2C_FIELD(&gm_80479D58, s32*, 0x34) = arg0;
}

void gm_801A4B60(void)
{
    gm_80479D58.unk_C = 1;
}

void gm_801A4B74(void)
{
    gm_80479D58.unk_C = 2;
}

void gm_801A4B88(struct MinorSceneInfo* info)
{
    gm_804D6720 = info;
}

void* gm_801A4B90(void)
{
    return gm_804D6720->unk_struct_0;
}

void* gm_801A4B9C(void)
{
    return gm_804D6720->unk_struct_1;
}

struct gm_80479D58_t* gm_801A4BA8(void)
{
    return gm_80479D58.unk_0;
}

s32 gm_801A4BB8(void)
{
    return gm_80479D58.unk_8;
}

HSD_GObj* gm_801A4BC8(void)
{
    return gm_804D672C;
}

void fn_801A4BD0(HSD_GObj* gobj) {}

void gm_801A4BD4(void)
{
    PAD_STACK(0x18);

    gm_80479D58.unk_14 = fn_801A46F4;
    gm_80479D58.unk_18 = fn_801A47E4;
    gm_80479D58.unk_30 = 0;
    gm_80479D58.unk_34 = 0;

    lb_80019880(1.0F/60 * OS_TIMER_CLOCK);
    HSD_GObj_803912E0(&gm_80479D48);
    gm_80479D48.gproc_pri_max = 0x18;
    HSD_SObjLib_804D7960 = HSD_GObj_803912A8(&gm_80479D48, &HSD_SObjLib_8040C3A4);
    HSD_SObjLib_803A44A4();
    gm_80479D48.unk_2 = &gm_80479D58.unk_28;
    HSD_GObj_80391304(&gm_80479D48);
    hsd_80392474();
    un_802FF78C();
    gm_804D672C = GObj_Create(14, 0, 0);
    if (gm_804D672C != NULL) {
        HSD_GObjProc_8038FD54(gm_804D672C, fn_801A4BD0, 0);
    }
    gm_804D6728 = 0;
    gm_804D6724 = 0;
    gm_801A3E88();
    lbAudioAx_8002835C();
    lb_80014534();
}
