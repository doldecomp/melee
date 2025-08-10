#include "itgamewatchpanic.h"

#include "db/db.h"
#include "ft/chara/ftGameWatch/ftGw_SpecialLw.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/* 2C7FAC */ static bool itGamewatchpanic_UnkMotion1_Anim(Item_GObj*);

ItemStateTable it_803F79A0[] = { { 0, itGamewatchpanic_UnkMotion1_Anim, NULL, NULL },
                                 { 1, itGamewatchpanic_UnkMotion1_Anim, NULL, NULL } };

HSD_GObj* it_802C7D60(Item_GObj* parent, Vec3* pos, Fighter_Part arg2, f32 dir)
{
    SpawnItem spawn_item;
    HSD_GObj* gobj;
    void** attr;

    spawn_item.kind = It_Kind_GameWatch_Panic;
    spawn_item.prev_pos = *pos;
    spawn_item.pos = spawn_item.prev_pos;
    spawn_item.facing_dir = dir;
    spawn_item.x3C_damage = 0;
    spawn_item.vel.x = spawn_item.vel.y = spawn_item.vel.z = 0.0F;
    spawn_item.x0_parent_gobj = parent;

    spawn_item.x4_parent_gobj2 = spawn_item.x0_parent_gobj;
    spawn_item.x44_flag.b0 = true;
    spawn_item.x40 = 0;
    gobj = Item_80268B18(&spawn_item);
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        attr = ip->xC4_article_data->x4_specialAttributes;
        Item_8026AB54(gobj, parent, arg2);
        db_80225DD8(gobj, parent);
        it_8027CE64(gobj, parent, *attr);
        return gobj;
    }
    return NULL;
}

void it_2725_Logic78_Destroyed(Item_GObj* gobj)
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
        it_2725_Logic78_Destroyed(gobj);
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

void it_2725_Logic78_PickedUp(Item_GObj* gobj)
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

void it_2725_Logic78_EvtUnk(Item_GObj* arg0, Item_GObj* arg1)
{
    it_8026B894(arg0, arg1);
}
