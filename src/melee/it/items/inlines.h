#ifndef MELEE_IT_ITEMS_INLINES_H
#define MELEE_IT_ITEMS_INLINES_H

#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/itmaplib.h"
#include "it/types.h"

static inline void itGamewatch_InitSpawnItem(SpawnItem* spawn,
                                             HSD_GObj* parent, Vec3* pos,
                                             f32 dir)
{
    spawn->prev_pos = *pos;
    spawn->pos = spawn->prev_pos;
    spawn->facing_dir = dir;
    spawn->x3C_damage = 0;
    spawn->vel.x = spawn->vel.y = spawn->vel.z = 0.0F;
    spawn->x0_parent_gobj = parent;
    spawn->x4_parent_gobj2 = spawn->x0_parent_gobj;
    spawn->x44_flag.b0 = true;
    spawn->x40 = 0;
}

static inline void Item_EnterAirStateWithHitlag(Item_GObj* gobj, enum_t msid)
{
    Item* item = GET_ITEM(gobj);
    it_802762BC(item);
    Item_80268E5C(gobj, msid, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
}

static inline void Item_EnterAirStateWithHitlagAndStateDesc(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    it_802762BC(item);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0F);
}

#endif
