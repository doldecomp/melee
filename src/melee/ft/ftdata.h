#ifndef MELEE_FT_FTDATA_H
#define MELEE_FT_FTDATA_H

#include "ft/fighter.h"

#include <baselib/gobj.h>

typedef struct ftData_UnkModelStruct {
    Fighter_ModelEvent model_events[FTKIND_MAX];
    unk_t (*getter[FTKIND_MAX])(HSD_GObj*);
} ftData_UnkModelStruct;

extern Fighter_UnkMtxEvent lbl_803C20CC[FTKIND_MAX];
extern ftData_UnkModelStruct lbl_803C2150;

void func_800855C8(enum_t id, int slot);
void func_8008572C(s32);
void func_8008578C(enum_t id, int slot);
void func_800857E0(bool);
void func_80085820(FighterKind, s32 costume_id);
void func_800859A8(Fighter*);
void func_80085A14(bool);
void func_80085B10(Fighter*);
void func_80085CD8(Fighter*, Fighter*, s32 msid);
u32 func_80085E50(Fighter*, u32);
void func_80085560(s32, bool);

#endif
