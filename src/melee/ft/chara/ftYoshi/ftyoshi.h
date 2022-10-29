#ifndef MELEE_FT_CHARA_FTYOSHI_FTYOSHI_H
#define MELEE_FT_CHARA_FTYOSHI_FTYOSHI_H

#include <melee/ft/ftcommon.h>
#include <melee/lb/lbvector.h>

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

void func_8012B6E8(Fighter* fp, struct S_UNK_YOSHI1* unk_struct_arg);
void func_8012B804(Fighter* fp, struct S_UNK_YOSHI1* unk_struct_arg, f32 start_frame);
void func_8012C850(HSD_GObj* fighter_gobj);
void func_8012B8A4(HSD_GObj* fighter_gobj);
void func_8012BE3C(HSD_GObj* fighter_gobj);
unk_t func_8012BECC();
unk_t func_8012C1D4();
unk_t func_8012C49C();
unk_t func_8012C600();
unk_t func_8012BDA0();
unk_t func_8012CC1C();
unk_t func_8012CD00();
unk_t func_8012CCE0();
unk_t func_8012CCF0();
unk_t func_8012CCD0();
unk_t func_8012CCC4();
unk_t func_8012CC94();
unk_t func_8012CDD4();
unk_t func_8012CD58();
unk_t func_8012CD40();
unk_t func_8012CD70();
unk_t func_8012CD88();
unk_t func_8012CD28();
unk_t func_8012CD10();

#endif
