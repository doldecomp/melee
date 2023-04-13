#ifndef MELEE_FT_FTDATA_H
#define MELEE_FT_FTDATA_H

#include <melee/ft/fighter.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct ftData_UnkModelStruct {
    Fighter_ModelEvent model_events[FTKIND_MAX];
    unk_t (*getter[FTKIND_MAX])(HSD_GObj*);
} ftData_UnkModelStruct;

extern Fighter_UnkMtxEvent lbl_803C20CC[FTKIND_MAX];
extern ftData_UnkModelStruct lbl_803C2150;

void ftData_800855C8(enum_t id, int slot);
void ftData_8008572C(s32);
void ftData_8008578C(enum_t id, int slot);
void ftData_800857E0(bool);
void ftData_80085820(FighterKind, s32 costume_id);
void ftData_800859A8(Fighter*);
void ftData_80085A14(bool);
void ftData_80085B10(Fighter*);
void ftData_80085CD8(Fighter*, Fighter*, s32 asid);
u32 ftData_80085E50(Fighter*, u32);
void ftData_80085560(s32, bool);

#endif
