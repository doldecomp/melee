#include <dolphin/types.h>
#include <dolphin/gx/gxtypes.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/initialize.h>
#include <functions.h>

extern s32 g_debugLevel; // debug level
extern BOOL lbl_804D6B20;
extern u16 lbl_804D6B30; // debug flags

extern GXRenderModeObj lbl_80401168;
extern PadLibData HSD_PadLibData;
extern char lbl_803EA6C8[]; // build timestamp string
extern s32* seed_ptr;
extern void lbl_8015FD24();
extern void lbl_803762C4();
extern void func_801692E8(int, struct datetime* datetime);

enum {
    DbLKind_Master = 0,
    DbLKind_NoDebugRom = 1,
    DbLKind_DebugDevelop = 2,
    DbLKind_DebugRom = 3,
    DbLKind_Develop = 4,
};

struct datetime {
    u16 year;
    u8 month, day, hour, minute, second;
};

static u32 arena_size;
static BOOL lbl_804D6594;

static u8 lbl_8046B108[0xF0];
static HSD_PadRumbleListData lbl_8046B1F8[12];

static void lbl_8015FD24(void)
{
    PADSetSpec(5);
    func_80377D98(5, lbl_8046B108, 12, lbl_8046B1F8);
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

static void lbl_8015FDA0(void)
{
}

// set debug level
static void func_8015FDA4(void)
{
    if (DVDConvertPathToEntrynum("/develop.ini") != -1) {
        lbl_804D6B20 = TRUE;
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
            lbl_804D6B20 = FALSE;
        }
    } else {
        if (g_debugLevel != DbLKind_NoDebugRom) {
            __assert(__FILE__, 0xD2, "DbLevel == DbLKind_NoDebugRom");
        }
        g_debugLevel = 0;
    }
}

inline void init_spr_unk()
{
    #define MTSPR(spr, val) \
        asm { li r3, val } \
        asm { oris r3, r3, val } \
        asm { mtspr spr, r3 } \

    MTSPR(0x392, 4);
    MTSPR(0x393, 5);
    MTSPR(0x394, 6);
    MTSPR(0x395, 7);
}

void main(void)
{
    char* unused_format_string = "Data %lx\n";
    u32 unused[2];

    OSInit();
    func_8034EE9C();
    DVDInit();
    PADInit();
    CARDInit();
    OSInitAlarm();
    func_80225374();
    func_8015FDA4();
    if (OSGetConsoleSimulatedMemSize() / (1024 * 1024) == 48) {
        OSAllocFromArenaHi(0x01800000, 4);
    }
    arena_size = OSGetArenaHi() - OSGetArenaLo();
    HSD_SetInitParameter(HSD_INIT_XFB_MAX_NUM, 2);
    HSD_SetInitParameter(HSD_INIT_RENDER_MODE_OBJ, &lbl_80401168);
    HSD_SetInitParameter(HSD_INIT_FIFO_SIZE, 0x40000);
    HSD_SetInitParameter(HSD_INIT_HEAP_MAX_NUM, 4);
    func_80228C4C();
    HSD_AllocateXFB(2, &lbl_80401168);
    HSD_GXSetFifoObj(GXInit(HSD_AllocateFIFO(0x40000), 0x40000));
    HSD_InitComponent();
    GXSetMisc(1, 8);
    *seed_ptr = OSGetTick();
    func_8002838C();
    func_80019AAC(&lbl_8015FD24);
    func_80375934(&lbl_8015FDA0);
    func_8037598C(&lbl_803762C4);
    func_803767A0(0);
    func_8001564C();
    func_80015F3C();
    func_80018F68();
    func_80014D2C();
    func_8001C5BC();
    func_8001D21C();
    func_8001E290();
    func_8015FCC0();
    func_8001F87C();
    func_803A6048(0xC000);
    func_8015FBA4();
    if (g_debugLevel != DbLKind_Master && lbl_804D6B30 & 0x20 && func_803931A4(-1)) {
        func_80393A54(1);
        while (!func_80393A04()) {
            OSReport("please setup server for USB\n");
            func_80392E80();
        }
    }
    func_8022886C();
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
        OSReport("# ARAM Free Size %d MB\n", (free_aram_end - free_aram_start) / (1024 * 1024));
    }
    OSReport("# %s\n", lbl_803EA6C8);
    {
        struct datetime dt;
        func_801692E8(func_8000AFBC(), &dt);
        OSReport("# GC Calendar Year %d Month %d Day %d\n",
            dt.year, dt.month, dt.day);
        OSReport("#             Hour %d Min %d Sec %d \n",
            dt.hour, dt.minute, dt.second);
    }
    OSReport("#\n\n");
    lbl_804D6594 = FALSE;
    if (lbl_804D6594) {
        func_80225D2C();
    } else {
        func_80225D40();
    }

    init_spr_unk();

    func_80228A64();
    func_801A4510();
}
