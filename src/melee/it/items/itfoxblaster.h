#ifndef GALE01_2ADDD0
#define GALE01_2ADDD0

#include "ft/forward.h"
#include "it/forward.h"

#include "it/items/types.h"

/* 2ADDD0 */ void it_802ADDD0(Item_GObj* item_gobj, s32 visibility);
/* 2ADEF0 */ void it_802ADEF0(HSD_GObj* item_gobj);
/* 2ADF10 */ void it_802ADF10(HSD_GObj* item_gobj);
/* 2AE1D0 */ void it_802AE1D0(Item_GObj* item_gobj);
/* 2AE538 */ void it_802AE538(Item_GObj* item_gobj);
/* 2AE8A8 */ Item_GObj* it_802AE8A8(f32 facing_dir, Fighter_GObj* fighter_gobj,
                                    Vec3* arg2, Fighter_Part ft_part,
                                    ItemKind it_kind);
/* 2AE994 */ Item_GObj* it_802AE994(Fighter_GObj*, Fighter_Part, ItemKind);
/* 2AEAB4 */ void it_802AEAB4(Item_GObj* item_gobj);
/* 2AEB00 */ void itFoxBlaster_Logic96_PickedUp(Item_GObj*);
/* 2AF184 */ void itFoxBlaster_Logic96_EvtUnk(Item_GObj*, HSD_GObj*);
/* 3F6CA8 */ extern ItemStateTable it_803F6CA8[];

#endif
