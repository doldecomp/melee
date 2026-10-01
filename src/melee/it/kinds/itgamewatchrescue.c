#include "itgamewatchrescue.h"

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include "inlines.h"
#include <melee/ft/kinds/ftGameWatch/ftgamewatchspecialhi.h>
#include <melee/it/inlines.h>
#include <melee/it/it_26B1.h>
#include <melee/it/item.h>
#include <melee/it/itzako.h>

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
        Item_InitSpawnPosition(&spawn, arg1, true);
        Item_InitSpawnCommonFields(&spawn, parent, farg0, false);
        result = Item_80268B18(&spawn);
        if (result != NULL) {
            temp_r6 = result->user_data;
            tmp = (void**) temp_r6->xC4_article_data->x4_specialAttributes;
            Item_ClearCmdVars(temp_r6);
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

static inline void clearRescue(Item_GObj* item_gobj)
{
    if (item_gobj != NULL) {
        Item* ip = GET_ITEM(item_gobj);
        ip->xDD4_itemVar.gamewatchrescue.xDD8 = NULL;
        ip->owner = NULL;
    }
}

bool itGamewatchrescue_UnkMotion1_Anim(Item_GObj* item_gobj)
{
    Item* ip = GET_ITEM(item_gobj);
    HSD_GObj* rescue_gobj = ip->xDD4_itemVar.gamewatchrescue.xDD8;
    PAD_STACK(8);

    if (rescue_gobj != NULL) {
        if (ftGw_SpecialHi_ItemCheckRescueRemove(rescue_gobj) == true) {
            it_802C8158(item_gobj);
            clearRescue(item_gobj);
            return true;
        }
    } else {
        it_802C8158(item_gobj);
        clearRescue(item_gobj);
        return true;
    }
    return false;
}

void itGamewatchrescue_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itGamewatchrescue_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void itGameWatchRescue_Logic81_EvtUnk(Item_GObj* item_gobj1,
                                      Item_GObj* item_gobj2)
{
    it_8026B894(item_gobj1, item_gobj2);
}
