
#include "baselib/forward.h"

#include "dolphin/types.h"
#include "gm/types.h"

struct DebugResultsData {
    u8 pad_x0[0x2284];
}; /// data used by gm_801B0DD0

struct DebugMemcardData {
    u32 x0;
    u8 x4;
};

struct DebugSoundTestData {
    struct SoundTestData {
        u32 x0;
        void (*x4)(void);
        char* x8; ///< "Sound Test Menu"
        u8 pad_xC[0x17];
        u8 x23;
        void (*x24)(void);
        char* x28; ///< "Sound Mode "
    }* x0;
    u32 x4;
};

struct TrainingMenuData {
    u8 pad_x0[0x6 - 0x0];
    s16 x6;
    u8 pad_x8[0x14 - 0x8];
    PlayerInitData players[6];
    HSD_GObj* xA4;
    HSD_JObj* xA8[39];
    u32 x144[39];
    u32 x1E0;
    u32 x1E4;
    u32 x1E8;
    u32 x1EC;
    u32 x1F0;
    u32 x1F4;
    u32 x1F8;
    HSD_Text* x1FC;
    u32 x200;
}; /// 80473814

extern struct TrainingMenuData gm_80473814;

extern struct SoundTestData un_803F9FA4;
