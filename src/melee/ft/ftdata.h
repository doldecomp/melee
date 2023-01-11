#ifndef MELEE_FT_FTDATA_H
#define MELEE_FT_FTDATA_H

#include <melee/ft/fighter.h>
#include <sysdolphin/baselib/gobj.h>

extern void (*lbl_803C20CC[FTKIND_MAX])(HSD_GObj*, s32, void*);
extern void (*lbl_803C2150[FTKIND_MAX])(HSD_GObj*, s32, BOOL);

void func_800855C8(void);
void func_8008572C(s32);
void func_8008578C(void);
void func_800857E0(BOOL);
void func_80085820(FighterKind, s32 costume_id);
void func_800859A8(Fighter*);
void func_80085A14(BOOL);
void func_80085B10(Fighter*);
void func_80085CD8(Fighter*, Fighter*, s32 asid);
u32 func_80085E50(struct _Fighter*, u32);
void func_80085560(s32, BOOL);

#endif
