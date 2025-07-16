#include "gm_1A45.h"

#include "gm_1601.h"
#include "gm_1A36.h"

#include "db/db.h"
#include "gm/gmscdata.h"
#include "lb/lb_00F9.h"
#include "lb/lb_0192.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardgame.h"
#include "lb/lbcardnew.h"
#include "lb/lbdvd.h"
#include "lb/lbheap.h"
#include "un/un_2FC9.h"

#include <baselib/controller.h>
#include <baselib/gobjproc.h>
#include <baselib/initialize.h>
#include <baselib/perf.h>
#include <baselib/leak.h>
#include <baselib/particle.h>
#include <baselib/sobjlib.h>

#include <dolphin/os/OSThread.h>

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

u64 gm_803DA8C8[2] = { -1, -1 };

bool gm_801A45E8(int bit)
{
    return gm_80479D58.unk_10 & (1ULL << bit);
}

int gm_801A4624(void)
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

#pragma push
#pragma dont_inline on
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
#pragma pop

void gm_801A4970(int (**arg0)(void))
{
    HSD_PadStatus* temp_r3;
    s8 var_r26;
    s8* temp_r4;
    u64 temp_ret;
    int i;
    PAD_STACK(8);

    var_r26 = 0;
    for (i = 0; i < 4; i++) {
        temp_r3 = &HSD_PadMasterStatus[(u8) i];
        if ((temp_r3->trigger & 2) && (temp_r3->button & 0x400)) {
            lbHeap_80015DF8();
            OSReport("[hsdDumpClassStat] -- Report --\n");
            hsdDumpClassStat(NULL, 0, 1);
            OSReport("\n");
            OSReport("[HSD_ObjDumpStat] -- Report --\n");
            HSD_ObjDumpStat();
            OSReport("\n");
            db_PrintEntityCounts();
            db_PrintThreadInfo();
            HSD_Leak_80387DF8(0);
            if (gm_804D6728 != NULL) {
                gm_801653C8(gm_804D6728);
                gm_804D6728 = NULL;
            } else {
                gm_804D6728 = gm_80165388(0x19, 0x3F, 0, 0xFE);
                if (gm_804D6724 != NULL) {
                    gm_804D6724();
                }
            }
        }
    }

    if (arg0[0] != NULL && arg0[0]() != 0) {
        if (gm_801A45E8(0)) {
            gm_80479D58.unk_10 &= 0xFFFFFFFE;
        } else {
            gm_80479D58.unk_10 |= 1;
        }
    }
    if (gm_801A45E8(0)) {
        if (arg0[1] != NULL && arg0[1]() != 0) {
            gm_80479D58.unk_12 |= 1;
        }
    }
}

void gm_801A4B08(bool (*arg0)(void), bool (*arg1)(void))
{
    gm_80479D58.unk_14 = arg0;
    gm_80479D58.unk_18 = arg1;
}

void gm_801A4B1C(void)
{
    gm_801A4B08(fn_801A46F4, fn_801A47E4);
}

void gm_801A4B40(UNK_T arg0)
{
    gm_80479D58.unk_30 = arg0;
}

void gm_801A4B50(int arg0)
{
    gm_80479D58.unk_34 = arg0;
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

u32 gm_801A4BA8(void)
{
    return gm_80479D58.unk_0;
}

u32 gm_801A4BB8(void)
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

    gm_801A4B08(fn_801A46F4, fn_801A47E4);
    gm_801A4B40(0);
    gm_801A4B50(0);

    lb_80019880(1.0F/60 * OS_TIMER_CLOCK);
    HSD_GObj_803912E0(&gm_80479D48.initdata);
    gm_80479D48.initdata.gproc_pri_max = 0x18;
    HSD_SObjLib_804D7960 = HSD_GObj_803912A8(&gm_80479D48.initdata, &HSD_SObjLib_8040C3A4);
    HSD_SObjLib_803A44A4();
    gm_80479D48.initdata.unk_2 = &gm_80479D58.unk_28;
    HSD_GObj_80391304(&gm_80479D48.initdata);
    hsd_80392474();
    un_802FF78C();
    gm_804D672C = GObj_Create(14, 0, 0);
    if (gm_804D672C != NULL) {
        HSD_GObjProc_8038FD54(gm_804D672C, fn_801A4BD0, 0);
    }
    gm_804D6728 = NULL;
    gm_804D6724 = NULL;
    gm_801A3E88();
    lbAudioAx_8002835C();
    lb_80014534();
}

MinorSceneHandler* gm_801A4CE0(u8 id)
{
    MinorSceneHandler* cur;
    for (cur = gm_801A50A0(); cur->class_id != 0x2D; cur++) {
        if (cur->class_id == id) {
            return cur;
        }
    }
    return NULL;
}

inline u64 maybe_gm_801A48A4(u8 i)
{
    u64 temp_ret = gm_801A48A4(i);
    if (gm_80479D58.unk_38_0) {
        return temp_ret;
    } else {
        return -1ULL;
    }
}

void gm_801A4D34(void (*arg0)(void), MinorSceneInfo* arg1)
{
    int temp_r3;
    int i;
    struct gm_80479D58_t* temp_r25;

    PAD_STACK(28);

    temp_r25 = &gm_80479D58;
    gm_801677C0(&temp_r25->unk_10);
    gm_80479D58.unk_0 = 0;
    gm_80479D58.unk_4 = 0;
    gm_80479D58.unk_8 = 0;
    gm_80479D58.unk_C = 0;
    HSD_PadFlushQueue(HSD_PAD_FLUSH_QUEUE_LEAVE1);
    lb_8001CF18();

    while (temp_r25->unk_C == 0) {
        hsd_80392E80();
        gmMainLib_8046B0F0.xC = 0;

        while ((temp_r3 = lb_80019894()) == 0) {
            lb_800195D0();
        }
        lb_800195D0();

        if (HSD_PadGetResetSwitch()) {
            gmMainLib_8046B0F0.x4 = true;
            break;
        }

        for (i = 0; i < temp_r3; i++) {
            HSD_PerfSetStartTime();
            lb_800198E0();
            if (g_debugLevel >= 3) {
                gm_801A4970((void*) &temp_r25->unk_14);
            }
            if (gm_801A46B8(0) || !gm_801A45E8(0)) {
                temp_r25->unk_38_0 = true;
            } else {
                temp_r25->unk_38_0 = false;
            }
            if (gm_80479D58.unk_38_0) {
                lb_80019900();
                if (lb_80019A30(0)) {
                    gm_801A3A74();
                }
                if (lb_80019A30(0) && (arg0 != NULL)) {
                    arg0();
                }
            }
            if (gm_80479D58.unk_10 != gm_80479D58.unk_11 ||
                    temp_r25->unk_12 != temp_r25->unk_13) {
                temp_r25->unk_20 = maybe_gm_801A48A4(temp_r25->unk_10);
                temp_r25->unk_11 = temp_r25->unk_10;
                temp_r25->unk_13 = temp_r25->unk_12;
                temp_r25->unk_12 = 0;
            }
            temp_r25->unk_28 = temp_r25->unk_20;
            if (lb_80019A30(0) == 0) {
                temp_r25->unk_28 |= gm_803DA8C8[temp_r25->unk_34];
            }
            if (lb_80019A30(1) == 0) {
                temp_r25->unk_28 |= ~gm_803DA8C8[temp_r25->unk_34];
            }
            if (g_debugLevel >= 3) {
                db_CheckScreenshot();
            }
            lbAudioAx_80027DF8();
            if (temp_r25->unk_30 != NULL) {
                temp_r25->unk_30();
            }
            HSD_GObj_80390CFC();
            if (temp_r25->unk_0 != -2) {
                temp_r25->unk_0++;
            }
            if (gm_80479D58.unk_38_0 && (lb_80019A30(0) != 0)) {
                if (temp_r25->unk_8 != -2) {
                    temp_r25->unk_8++;
                }
            }
            HSD_PerfSetCPUTime();
            if (g_debugLevel >= 3) {
                OSCheckActiveThreads();
            }
            gmMainLib_8046B0F0.xC = 0;
            if (temp_r25->unk_C != 0) {
                break;
            }
        }
        if (temp_r25->unk_C == 2) {
            break;
        }

        lb_800195D0();
        GXInvalidateVtxCache();
        GXInvalidateTexAll();
        HSD_StartRender(HSD_RP_SCREEN);
        HSD_GObj_80390FC0();
        HSD_Init_803755A8();
        HSD_PerfSetDrawTime();
        HSD_VICopyXFBAsync(HSD_RP_SCREEN);
        if (temp_r25->unk_4 != -2U) {
            temp_r25->unk_4++;
        }
        db_TakeScreenshotIfPending();
        HSD_PerfSetTotalTime();
        HSD_PerfInitStat();
    }
    HSD_VIWaitXFBFlush();
}

