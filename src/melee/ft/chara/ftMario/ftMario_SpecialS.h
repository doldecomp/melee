#ifndef MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALS_H
#define MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALS_H

#include <sysdolphin/baselib/forward.h>
#include <melee/ft/forward.h>
#include <Runtime/platform.h>

void ftMario_SpecialS_ChangeAction(HSD_GObj* gobj, enum_t asid);
void ftMario_SpecialS_SetCall(Fighter* fp);
void ftMario_SpecialS_ReflectThink(HSD_GObj* gobj);
void ftMario_SpecialS_UpdateVarsColl(HSD_GObj* gobj);

#endif
