#ifndef MELEE_FT_CHARA_FTPURIN_FTPURIN_H
#define MELEE_FT_CHARA_FTPURIN_FTPURIN_H

#include <melee/ft/ftcommon.h>
#include <melee/lb/lbvector.h>

typedef struct _ftPurinAttributes {
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
    u8 data_filler_1[0x100 - 0x30];
} ftPurinAttributes;

/// functions
void func_8013C494(HSD_GObj* fighter_gobj);

void func_8013C614(Fighter* fp, s32 arg1, s32 arg2);
void* func_8013C664(HSD_GObj* fighter_gobj);
void ftPurin_OnLoad(HSD_GObj* fighter_gobj);
void func_8013C2F8(void);
void ftPurin_OnItemPickup(HSD_GObj* fighter_gobj, bool bool);
void ftPurin_OnItemInvisible(HSD_GObj* fighter_gobj);
void ftPurin_OnItemVisible(HSD_GObj* fighter_gobj);
void ftPurin_OnItemDrop(HSD_GObj* fighter_gobj, bool bool1);
void ftPurin_LoadSpecialAttrs(HSD_GObj* fighter_gobj);
void ftPurin_OnKnockbackEnter(HSD_GObj* fighter_gobj);
void ftPurin_OnKnockbackExit(HSD_GObj* fighter_gobj);
void ftPurin_OnDeath(HSD_GObj* fighter_gobj);
void ftPurin_OnUserDataRemove(HSD_GObj* fighter_gobj);
void func_8013C360(HSD_GObj* fighter_gobj);
void func_8013C4F0(HSD_GObj* fighter_gobj, s32 arg1, Mtx vmtx);
void lbl_8013C94C(void);
void ftPurin_SpecialHi_StartAction(HSD_GObj*);

#endif
