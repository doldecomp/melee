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
