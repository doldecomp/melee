#include "dolphin/types.h"
#include "gm/types.h"

struct DebugResultsData {
    u8 x0_0 : 1;
    u8 x0_1 : 1;
    u8 x0_other : 6;
    u8 x1;
    u8 x2;
    u8 x3;
    u8 x4;
    u8 pad_x5[3];
    MatchEnd match_end;
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

/* 3F9FA4 */ extern struct SoundTestData un_803F9FA4;
