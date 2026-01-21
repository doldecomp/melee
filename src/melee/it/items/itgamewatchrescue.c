#include "itgamewatchrescue.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include <melee/ft/chara/ftGameWatch/ftGw_SpecialHi.h>
#include <melee/it/inlines.h>
#include <melee/it/it_26B1.h>
#include <melee/it/it_2725.h>
#include <melee/it/item.h>

ItemStateTable it_803F79C0[] = { {
                                     0,
                                     itGamewatchrescue_UnkMotion1_Anim,
                                     itGamewatchrescue_UnkMotion1_Phys,
                                     itGamewatchrescue_UnkMotion1_Coll,
                                 },
                                 {
                                     0,
                                     itGamewatchrescue_UnkMotion1_Anim,
                                     itGamewatchrescue_UnkMotion1_Phys,
                                     itGamewatchrescue_UnkMotion1_Coll,
                                 } };

Item_GObj* it_802C8038(Item_GObj* parent, Vec3* arg1, s32 arg2, s32 arg3,
                       f32 farg0, f32 farg1)
{
    void** tmp;
    Item* temp_r6;
    SpawnItem spawn;
    Item_GObj* result;

    if (parent != NULL) {
        spawn.kind = It_Kind_GameWatch_Rescue;
        spawn.prev_pos = *arg1;
        spawn.prev_pos.z = 0.0F;
        spawn.pos = spawn.prev_pos;
        spawn.facing_dir = farg0;
        spawn.x3C_damage = 0;
        spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
        spawn.x0_parent_gobj = parent;
        spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
        spawn.x44_flag.b0 = false;
        spawn.x40 = 0;
        result = Item_80268B18(&spawn);
        if (result != NULL) {
            temp_r6 = result->user_data;
            tmp = temp_r6->xC4_article_data->x4_specialAttributes;
            temp_r6->xDB8_itcmd_var3 = 0;
            temp_r6->xDB4_itcmd_var2 = 0;
            temp_r6->xDB0_itcmd_var1 = 0;
            temp_r6->xDAC_itcmd_var0 = 0;
            temp_r6->xDCC_flag.b3 = false;
            temp_r6->xDD4_itemVar.gamewatchrescue.xDD8 = parent;
            it_8027CE64(result, parent, *tmp);
            it_802C8208(result, arg3);
        }
    } else {
        result = NULL;
    }
    return result;
}

void it_802C8158(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    HSD_GObj* temp_r3;

    if ((item_gobj != NULL) && (item != NULL)) {
        if ((temp_r3 = item->xDD4_itemVar.gamewatchrescue.xDD8) != NULL &&
            item->owner == temp_r3)
        {
            ftGw_SpecialHi_ItemRescueSetNULL(temp_r3);
        }
        item->xDD4_itemVar.gamewatchrescue.xDD8 = NULL;
        item->owner = NULL;
        Item_8026A8EC(item_gobj);
    }
}

void it_802C81C8(Item_GObj* item_gobj)
{
    it_8026B724(item_gobj);
}

void it_802C81E8(Item_GObj* item_gobj)
{
    it_8026B73C(item_gobj);
}

void it_802C8208(HSD_GObj* hsd_gobj, enum_t msid)
{
    Item_80268E5C(hsd_gobj, msid, ITEM_ANIM_UPDATE);
    Item_802694CC(hsd_gobj);
}

/// #itGamewatchrescue_UnkMotion1_Anim
bool itGamewatchrescue_UnkMotion1_Anim(Item_GObj* item_gobj)
{
    Item* item1;
    Item* item2;
    // All of these items are unused, but the stack needs padding for a match
    // so...
    Item* item3;
    Item* item4;
    Item* item5;
    Item* item6;
    Item* item7;

    Item* temp_r3_3;
    Item* temp_r3_4;
    HSD_GObj* temp_r3;
    HSD_GObj* temp_r3_2;

    item1 = GET_ITEM(item_gobj);
    if ((temp_r3 = item1->xDD4_itemVar.gamewatchrescue.xDD8) != NULL) {
        if (ftGw_SpecialHi_ItemCheckRescueRemove(temp_r3) == true) {
            item2 = GET_ITEM(item_gobj);
            if (item_gobj != NULL && item2 != NULL) {
                if ((temp_r3_2 = item2->xDD4_itemVar.gamewatchrescue.xDD8) !=
                        NULL &&
                    item2->owner == temp_r3_2)
                {
                    ftGw_SpecialHi_ItemRescueSetNULL(temp_r3_2);
                }
                item2->xDD4_itemVar.gamewatchrescue.xDD8 = NULL;
                item2->owner = NULL;
                Item_8026A8EC(item_gobj);
            }
            if (item_gobj != NULL) {
                temp_r3_3 = GET_ITEM(item_gobj);
                temp_r3_3->xDD4_itemVar.gamewatchrescue.xDD8 = NULL;
                temp_r3_3->owner = NULL;
            }
            return true;
        }
        goto end;
    }
    if (item_gobj != NULL && item1 != NULL) {
        if (temp_r3 != NULL && item1->owner == temp_r3) {
            ftGw_SpecialHi_ItemRescueSetNULL(temp_r3);
        }
        item1->xDD4_itemVar.gamewatchrescue.xDD8 = NULL;
        item1->owner = NULL;
        Item_8026A8EC(item_gobj);
    }
    if (item_gobj != NULL) {
        temp_r3_4 = GET_ITEM(item_gobj);
        temp_r3_4->xDD4_itemVar.gamewatchrescue.xDD8 = NULL;
        temp_r3_4->owner = NULL;
    }
    return true;
end:
    return false;
}

void itGamewatchrescue_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itGamewatchrescue_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void it_2725_Logic81_EvtUnk(Item_GObj* item_gobj1, Item_GObj* item_gobj2)
{
    it_8026B894(item_gobj1, item_gobj2);
}
