#ifndef MELEE_FT_FTDATA_H
#define MELEE_FT_FTDATA_H

#include <melee/ft/fighter.h>
#include <sysdolphin/baselib/gobj.h>

extern void (*lbl_803C20CC[FTKIND_MAX])(HSD_GObj*, s32, void*);
extern void (*lbl_803C2150[FTKIND_MAX])(HSD_GObj*, s32, BOOL);

void func_800855C8(void);
void func_8008572C(u32);
void func_8008578C(void);
void func_800857E0(u32);
void func_80085820(void);
void func_800859A8(void);
void func_80085A14(u32);
void func_80085B10(void);
void func_80085CD8(void);
u32 func_80085E50(struct _Fighter*, u32);

#endif
