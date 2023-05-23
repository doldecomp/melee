#ifndef MELEE_FT_FTDATA_H
#define MELEE_FT_FTDATA_H

#include "ft/forward.h"

#include "ft/fighter.h"

#include <baselib/gobj.h>

typedef struct ftData_UnkModelStruct {
    Fighter_ModelEvent model_events[FTKIND_MAX];
    unk_t (*getter[FTKIND_MAX])(HSD_GObj*);
} ftData_UnkModelStruct;

extern Fighter_UnkMtxEvent ftData_UnkMtxFunc0[FTKIND_MAX];
extern ftData_UnkModelStruct ftData_UnkIntBoolFunc0;

void ftData_800855C8(enum_t id, int slot);
void ftData_8008572C(s32);
void ftData_8008578C(enum_t id, int slot);
void ftData_800857E0(bool);
void ftData_80085820(FighterKind, s32 costume_id);
void ftData_800859A8(Fighter*);
void ftData_80085A14(bool);
void ftData_80085B10(Fighter*);
void ftData_80085CD8(Fighter*, Fighter*, s32 msid);
u32 ftData_80085E50(Fighter*, u32);
void ftData_80085560(s32, bool);

/* 085FD4 */ struct {
    /* +0 */ UNK_T x0;
    /* +4 */ UNK_T x4;
    /* +8 */ UNK_T x8;
}* ftData_80085FD4(Fighter* fp, FtMotionId msid);

extern HSD_GObjEvent
    ftData_OnLoad[FTKIND_MAX]; // One load  callback for every character.
extern HSD_GObjEvent
    ftData_OnDeath[FTKIND_MAX]; // One death callback for every character.
extern HSD_GObjEvent ftData_OnAbsorb[FTKIND_MAX];
extern HSD_GObjEvent
    ftData_UnkMotionStates3[FTKIND_MAX]; // probably ft_OnSomething
extern HSD_GObjEvent ftData_OnUserDataRemove[FTKIND_MAX];
extern Event ftData_Table_Unk1[FTKIND_MAX];
extern Fighter_ItemEvent ftData_OnItemPickupExt[FTKIND_MAX];

#endif
