#include "gm_1A36.h"

#include "db/db_2253.h"
#include "gm/gm_1601.h"
#include "gm/gmmain_lib.h"
#include "lb/lbarq.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbdvd.h"
#include "lb/lbheap.h"
#include "lb/lblanguage.h"
#include "lb/lbmemory.h"
#include "lb/lbmthp.h"
#include "lb/lbsnap.h"
#include "lb/lbtime.h"
#include "lb/lbunknown_005.h"

#include <placeholder.h>
#include <dolphin/card/CARDBios.h>
#include <dolphin/dvd/dvd.h>
#include <dolphin/gx/GXInit.h>
#include <dolphin/gx/GXMisc.h>
#include <dolphin/os/os.h>
#include <dolphin/os/OSInit.h>
#include <dolphin/os/OSMemory.h>
#include <dolphin/pad/Pad.h>
#include <dolphin/vi/vi.h>
#include <baselib/baselib_unknown_002.h>
#include <baselib/controller.h>
#include <baselib/debug.h>
#include <baselib/initialize.h>
#include <baselib/rumble.h>
#include <baselib/sislib.h>
#include <baselib/video.h>

extern bool lbl_804D6B20;
extern u16 lbl_804D6B30; // debug flags

extern GXRenderModeObj GXNtsc480IntDf;
extern PadLibData HSD_PadLibData;
extern char lbl_803EA6C8[]; // build timestamp string
extern s32* seed_ptr;

enum {
    DbLKind_Master = 0,
    DbLKind_NoDebugRom = 1,
    DbLKind_DebugDevelop = 2,
    DbLKind_DebugRom = 3,
    DbLKind_Develop = 4,
};

static u32 arena_size;
static bool lbl_804D6594;

static u8 lbl_8046B108[0xF0];
static HSD_PadRumbleListData lbl_8046B1F8[12];

static void gmMain_8015FD24(void)
{
    PADSetSpec(5);
    HSD_PadInit(5, lbl_8046B108, 12, lbl_8046B1F8);
    HSD_PadLibData.clamp_stickType = 0;
    HSD_PadLibData.clamp_stickShift = 1;
    HSD_PadLibData.clamp_stickMax = 80;
    HSD_PadLibData.clamp_stickMin = 0;
    HSD_PadLibData.scale_stick = 80;
    HSD_PadLibData.clamp_analogLRShift = 1;
    HSD_PadLibData.clamp_analogLRMax = 140;
    HSD_PadLibData.clamp_analogLRMin = 0;
    HSD_PadLibData.scale_analogLR = 140;
}

static void gmMain_8015FDA0(void) {}

// set debug level
static void gmMain_8015FDA4(void)
{
    if (DVDConvertPathToEntrynum("/develop.ini") != -1) {
        lbl_804D6B20 = true;
        if (lbl_804D6B30 & 0x400) {
            int level = g_debugLevel;
            switch (level) {
            case DbLKind_NoDebugRom:
                level = DbLKind_DebugRom;
                break;
            case DbLKind_DebugDevelop:
                level = DbLKind_Develop;
                break;
            case DbLKind_DebugRom:
                level = DbLKind_NoDebugRom;
                break;
            case DbLKind_Develop:
                level = DbLKind_DebugDevelop;
                break;
            default:
                level = DbLKind_DebugDevelop;
                break;
            }
            g_debugLevel = level;
        } else if (lbl_804D6B30 & 0x800) {
            int level = g_debugLevel;
            switch (level) {
            case DbLKind_NoDebugRom:
                level = DbLKind_DebugRom;
                break;
            case DbLKind_DebugDevelop:
                level = DbLKind_Develop;
                break;
            }
            g_debugLevel = level;
            lbl_804D6B20 = false;
        }
    } else {
        if (g_debugLevel != DbLKind_NoDebugRom) {
            __assert(__FILE__, 0xD2, "DbLevel == DbLKind_NoDebugRom");
        }
        g_debugLevel = 0;
    }
}

#ifdef MWERKS_GEKKO

static inline void init_spr_unk(void)
{
#define MTSPR(spr, val)                                                       \
    asm { li r3, val }                                                        \
    asm                                                                       \
    {                                                                         \
        oris r3, r3, val                                                      \
    }                                                                         \
    asm { mtspr spr, r3 }

    MTSPR(0x392, 4);
    MTSPR(0x393, 5);
    MTSPR(0x394, 6);
    MTSPR(0x395, 7);
}
#else

/// @remarks Might not do anything relevant to a port, but should still
///          understand its purpose before ignoring it.
static inline void init_spr_unk(void)
{
    NOT_IMPLEMENTED;
}

#endif

int main(void)
{
#ifdef MUST_MATCH
    char* unused_format_string = "Data %lx\n";
    u32 _[2];
#endif

    OSInit();
    VIInit();
    DVDInit();
    PADInit();
    CARDInit();
    OSInitAlarm();
    db_80225374();
    gmMain_8015FDA4();
    if (OSGetConsoleSimulatedMemSize() / (1024 * 1024) == 48) {
        OSAllocFromArenaHi(0x01800000, 4);
    }
    arena_size = (intptr_t) OSGetArenaHi() - (intptr_t) OSGetArenaLo();
    HSD_SetInitParameter(HSD_INIT_XFB_MAX_NUM, 2);
    HSD_SetInitParameter(HSD_INIT_RENDER_MODE_OBJ, &GXNtsc480IntDf);
    HSD_SetInitParameter(HSD_INIT_FIFO_SIZE, 0x40000);
    HSD_SetInitParameter(HSD_INIT_HEAP_MAX_NUM, 4);
    db_80228C4C();
    HSD_AllocateXFB(2, &GXNtsc480IntDf);
    HSD_GXSetFifoObj(GXInit(HSD_AllocateFifo(0x40000), 0x40000));
    HSD_InitComponent();
    GXSetMisc(1, 8);
    *seed_ptr = OSGetTick();
    func_8002838C();
    func_80019AAC(&gmMain_8015FD24);
    HSD_VISetUserPostRetraceCallback(&gmMain_8015FDA0);
    HSD_VISetUserGXDrawDoneCallback(&lbl_803762C4);
    HSD_VISetBlack(0);
    func_8001564C();
    func_80015F3C();
    func_80018F68();
    func_80014D2C();
    func_8001C5BC();
    func_8001D21C();
    func_8001E290();
    gmMainLib_8015FCC0();
    func_8001F87C();
    func_803A6048(0xC000);
    gmMainLib_8015FBA4();

    if (g_debugLevel != DbLKind_Master && lbl_804D6B30 & 0x20 &&
        func_803931A4(-1))
    {
        func_80393A54(1);
        while (!func_80393A04()) {
            OSReport("please setup server for USB\n");
            func_80392E80();
        }
    }

    db_8022886C();
    OSReport("# ---------------------------------------------\n");
    OSReport("#    Super Smash Bros. Melee\n");
    OSReport("#\n");
    OSReport("# Distribution %d\n", lbLang_GetLanguageSetting());
    OSReport("# Language %d\n", lbLang_GetSavedLanguage());
    OSReport("# DbLevel %d\n", g_debugLevel);
    OSReport("# Arena Size %d MB\n", arena_size / (1024 * 1024));
    {
        u32 free_aram_start;
        u32 free_aram_end;
        func_800154BC(&free_aram_start, &free_aram_end);
        OSReport("# ARAM Free Size %d MB\n",
                 (free_aram_end - free_aram_start) / (1024 * 1024));
    }
    OSReport("# %s\n", lbl_803EA6C8);
    {
        struct datetime dt;
        gm_801692E8(func_8000AFBC(), &dt);
        OSReport("# GC Calendar Year %d Month %d Day %d\n", dt.year, dt.month,
                 dt.day);
        OSReport("#             Hour %d Min %d Sec %d \n", dt.hour, dt.minute,
                 dt.second);
    }
    OSReport("#\n\n");
    lbl_804D6594 = false;
    if (lbl_804D6594) {
        db_80225D2C();
    } else {
        db_80225D40();
    }

    init_spr_unk();

    db_80228A64();
    gm_801A4510();
}
