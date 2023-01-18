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

void func_8012B8A4(HSD_GObj* fighter_gobj);
void func_8012B6E8(Fighter* fp, struct S_UNK_YOSHI1* unk_struct_arg);
void func_8012B804(Fighter* fp, struct S_UNK_YOSHI1* unk_struct_arg,
                   f32 start_frame);

unk_t func_8012BECC(void);
void func_8012C850(HSD_GObj* fighter_gobj);

void func_8012B918(HSD_GObj* fighter_gobj);
void ftYoshi_OnDeath(HSD_GObj* fighter_gobj);
void ftYoshi_OnLoad(HSD_GObj* fighter_gobj);
void ftYoshi_8012BA8C(HSD_GObj* fighter_gobj);
f32 ftYoshi_8012BAC0(Fighter* fp);
void ftYoshi_OnItemPickup(HSD_GObj* fighter_gobj, bool bool);
void ftYoshi_OnItemInvisible(HSD_GObj* fighter_gobj);
void ftYoshi_OnItemVisible(HSD_GObj* fighter_gobj);
void ftYoshi_OnItemDrop(HSD_GObj* fighter_gobj, bool bool1);
void ftYoshi_LoadSpecialAttrs(HSD_GObj* fighter_gobj);
void ftYoshi_OnKnockbackEnter(HSD_GObj* fighter_gobj);
void ftYoshi_OnKnockbackExit(HSD_GObj* fighter_gobj);
unk_t func_8012BDA0(void);
void func_8012BE3C(HSD_GObj* fighter_gobj);

#endif
