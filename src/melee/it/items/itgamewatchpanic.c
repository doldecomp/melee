#include "itgamewatchpanic.h"

#include "inlines.h"

#include "db/db.h"
#include "ft/chara/ftGameWatch/ftGw_SpecialLw.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include "it/itzako.h"

/* 2C7FAC */ static bool itGamewatchpanic_UnkMotion1_Anim(Item_GObj*);

ItemStateTable it_803F79A0[] = {
    { 0, itGamewatchpanic_UnkMotion1_Anim, NULL, NULL },
    { 1, itGamewatchpanic_UnkMotion1_Anim, NULL, NULL }
};

HSD_GObj* it_802C7D60(Item_GObj* parent, Vec3* pos, Fighter_Part arg2, f32 dir)
{
    SpawnItem spawn;
    Item_GObj* result;

    spawn.kind = It_Kind_GameWatch_Panic;
    Item_InitSpawn(&spawn, parent, pos, dir);
    result = Item_80268B18(&spawn);
    if (result != NULL) {
        Item* item = GET_ITEM(result);
        void** attr = item->xC4_article_data->x4_specialAttributes;
        Item_AttachGameWatchArticle(parent, arg2, result, attr);
        return result;
    }
    return NULL;
}

void itGameWatchPanic_Logic78_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->owner != NULL) {
        ftGw_SpecialLw_ItemPanicSetFlag(ip->owner);
    }
}

void it_802C7E94(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip != NULL) {
        itGameWatchPanic_Logic78_Destroyed(gobj);
        Item_8026A8EC(gobj);
    }
}

void it_802C7EE0(Item_GObj* gobj)
{
    it_8026B724(gobj);
}

void it_802C7F00(Item_GObj* gobj)
{
    it_8026B73C(gobj);
}

void itGameWatchPanic_Logic78_PickedUp(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDB0_itcmd_var1 = 0;
    ip->xDAC_itcmd_var0 = 0;
    if (ip->owner != NULL) {
        ip->ground_or_air = ftLib_800865CC(ip->owner);
        if (ip->ground_or_air == GA_Ground) {
            Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
        } else {
            Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        }
        Item_802694CC(gobj);
    }
}

bool itGamewatchpanic_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip->owner != NULL ? ftGw_SpecialLw_ItemCheckPanicRemove(ip->owner)
                          : true)
    {
        Item* ip = GET_ITEM(gobj);
        if (ip->owner != NULL) {
            ftGw_SpecialLw_ItemPanicSetFlag(ip->owner);
        }
        return true;
    }
    return false;
}

void itGameWatchPanic_Logic78_EvtUnk(Item_GObj* arg0, Item_GObj* arg1)
{
    it_8026B894(arg0, arg1);
}
