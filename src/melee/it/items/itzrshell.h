#ifndef _itzrshell_h_
#define _itzrshell_h_

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

void it_802E02E8(Item_GObj*);
void it_2725_Logic12_PickedUp(Item_GObj*);
void it_2725_Logic12_Thrown(Item_GObj*);
void it_2725_Logic12_Dropped(Item_GObj*);
void it_2725_Logic12_EnteredAir(Item_GObj*);
void it_2725_Logic12_Destroyed(Item_GObj*);
bool it_2725_Logic12_DmgDealt(Item_GObj*);
bool it_2725_Logic12_DmgReceived(Item_GObj*);
bool it_2725_Logic12_Reflected(Item_GObj*);
bool it_2725_Logic12_HitShield(Item_GObj*);
bool it_2725_Logic12_ShieldBounced(Item_GObj*);
void it_802E0468(Item_GObj*, HSD_GObj*);
Item_GObj* it_802E0488(s32, Vec3*, s32);
extern ItemStateTable it_803F87F0[];

#endif
