#ifndef MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALS_H
#define MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALS_H

#include <melee/ft/forward.h>
#include <Runtime/platform.h>
#include <sysdolphin/baselib/forward.h>

void ftMario_SpecialS_ChangeAction(HSD_GObj* gobj, s32 new_action_state_index);
void ftMario_SpecialS_SetCall(Fighter* fp);
void ftMario_SpecialS_ReflectThink(HSD_GObj* gobj);
void ftMario_SpecialS_UpdateVarsColl(HSD_GObj* gobj);

#endif
