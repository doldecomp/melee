#ifndef MELEE_FT_FTPARTS_H
#define MELEE_FT_FTPARTS_H

#include <ctypes.h>

typedef struct _HSD_ObjAllocData HSD_ObjAllocData;
typedef struct _HSD_JObj HSD_JObj;
typedef struct _Fighter Fighter;

unk_t func_8007506C();
extern HSD_ObjAllocData lbl_80459080;
void func_80074B0C(HSD_GObj* fighter_gobj, s32, s32);
void func_80074148(void);
void func_80073758(HSD_JObj* jobj);
void func_80074170(void);
void func_800743E0(HSD_GObj* fighter_gobj);
void func_800749CC(HSD_GObj* fighter_gobj);
void func_80074A4C(HSD_GObj* fighter_gobj, u32, s32);
void func_80074A8C(HSD_GObj* fighter_gobj);
void func_80074E58(Fighter* fp);

#endif
