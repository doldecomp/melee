#include "melee/ft/ftcommon.h"
#include "melee/lb/lbvector.h"

#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/mobj.h>

typedef struct _ftYoshiAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    s32 x14;
    f32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    u8 data_filler1[0xEF];
    f32 x120;
    u8 data_filler2[0x14];
} ftYoshiAttributes;

struct S_UNK_YOSHI2 {
    s32 x0;
    s32 x4;
    s32 x8_end_index;
    u8* xC_start_index;
};

struct S_UNK_YOSHI1 {
    s32 x0;
    struct S_UNK_YOSHI2* unk_struct;
};

void func_8012B6E8(Fighter* fighter, struct S_UNK_YOSHI1* unk_struct_arg);
void func_8012B804(Fighter* fighter, struct S_UNK_YOSHI1* unk_struct_arg, f32 start_frame);