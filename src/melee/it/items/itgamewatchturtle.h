#ifndef GALE01_2C6F40
#define GALE01_2C6F40

#include <melee/it/forward.h>

#include <melee/ft/types.h>
#include <melee/it/items/types.h>
#include <melee/it/types.h>

extern ItemStateTable it_803F7918[];

Item_GObj* it_802C6F40(HSD_GObj* parent, Vec3* pos, Fighter_Part arg2,
                       f32 dir);
void it_2725_Logic75_Destroyed(Item_GObj* item_gobj);
void it_802C7074(Item_GObj* item_gobj);
void it_802C70C0(Item_GObj*);
void it_802C70E0(Item_GObj*);
void it_2725_Logic75_PickedUp(Item_GObj* item_gobj);
void it_802C7158(HSD_GObj* arg0);
bool itGamewatchturtle_UnkMotion1_Anim(Item_GObj* item_gobj);
void it_2725_Logic75_EvtUnk(HSD_GObj*, HSD_GObj*);

#endif
