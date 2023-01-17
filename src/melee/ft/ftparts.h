#ifndef MELEE_FT_FTPARTS_H
#define MELEE_FT_FTPARTS_H

#include <dolphin/mtx/types.h>
#include <melee/ft/fighter.h>

void func_80074B0C(struct _HSD_GObj*, s32, s32);
void func_80073758(struct _HSD_JObj*);
void func_80074148(void);
void func_80074170(void);
void func_800743E0(void);
void func_800749CC(struct _HSD_GObj*);
void func_80074A4C(struct _HSD_GObj*, u32, s32);
void func_80074A8C(struct _HSD_GObj*);
void func_80074E58(struct _Fighter*);

/// @returns A bone index.
s32 func_8007500C(struct _Fighter*, s32);

void Fighter_JObjSetRotation(struct _HSD_JObj*, Quaternion*);
void func_8007592C(struct _Fighter*, s32, f32);
void func_80075AF0(struct _Fighter*, s32, f32);
void func_80075CB4(struct _Fighter*, s32, f32);
s32 func_8007500C(struct _Fighter*, s32);
void func_800753D4(struct _Fighter*, s32, unk_t);
f32 func_80075F48(Fighter*, s32);
s32 func_80074A74(HSD_GObj*, s32);
void func_80075650(HSD_GObj* fighter_gobj, HSD_JObj*, u32*);
void func_8007487C(unk_t item, u32*, u8 costume_id, u32*, u32*);
void func_80074CA0(u32*, s32, u32*);
void func_80074D7C(u32*, s32, u32*);
void Fighter_SetupParts(HSD_GObj* fighter_obj);

/// @returns Blend frames.
f32 func_80075E78(Fighter*, bool);

void Fighter_JObjMakePositionMtx(HSD_JObj* jobj, Mtx mtx, Mtx rmtx);
void func_8007462C(void);
void func_8007482C(void);
s32 Fighter_IntpJObjLoad(HSD_JObj* jobj, HSD_Joint* joint, HSD_JObj* parent);
void func_80074B6C(void);
void func_80073830(void);
void func_80075028(void);
void func_800750C8(void);
void func_80075240(void);
void func_80075304(void);
void func_800755E8(void);
void func_800739B8(void);
void func_80073CA8(void);

#endif
