#include "itgamewatchparachute.h"

#include "ftGameWatch/ftGw_AttackAir.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include "db/db.h"
#include "it/it_2725.h"

HSD_GObj* it_802C6C38(Item_GObj* parent, Vec3* pos, enum_t part,
                       float facing_dir)
{
    Item_GObj* gobj;
    SpawnItem spawn;
    PAD_STACK(4);

    spawn.kind = 0x75;
    spawn.prev_pos = *pos;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0.0f;
    spawn.vel.y = 0.0f;
    spawn.vel.x = 0.0f;
    spawn.x0_parent_gobj = parent;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        itGamewatchparachuteAttributes* attrs =
            GET_ITEM(gobj)->xC4_article_data->x4_specialAttributes;
        Item_8026AB54(gobj, parent, part);
        db_80225DD8(gobj, parent);
        it_8027CE64(gobj, parent, attrs->x0);
        return gobj;
    }
    return NULL;
}

void it_802C6D6C(Item_GObj* item_gobj)
{
    int pad[1];
    Item* item = GET_ITEM(item_gobj);

    if (item != NULL) {
        if (item->owner != NULL) {
            ftGw_AttackAirN_ItemParachuteSetFlag(item->owner);
        }
        Item_8026A8EC(item_gobj);
    }
}

void itGameWatchParachute_Logic74_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802C6DB8(Item_GObj* gobj)
{
    it_8026B724(gobj);
}

void it_802C6DD8(Item_GObj* gobj)
{
    it_8026B73C(gobj);
}

void itGameWatchParachute_Logic74_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->owner != NULL) {
        ftGw_AttackAirN_ItemParachuteSetFlag(ip->owner);
    }
}

void itGameWatchParachute_Logic74_PickedUp(Item_GObj* item_gobj)
{
    Item* temp_r3;

    temp_r3 = item_gobj->user_data;
    temp_r3->xDAC_itcmd_var0 = 0;
    if ((HSD_GObj*) temp_r3->owner != NULL) {
        Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
        Item_802694CC(item_gobj);
    }
}

void it_802C6E50(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026BB44(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itGamewatchparachute_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    bool remove;
    PAD_STACK(8);

    if (ip->x5CC_currentAnimFrame == 30.0f) {
        if (ip->owner != NULL) {
            ftGw_AttackAirN_ItemParachuteSetFlag(ip->owner);
        }
        return true;
    }

    if (ip->owner != NULL) {
        remove = ftGw_AttackAirN_ItemCheckParachuteRemove(ip->owner);
    } else {
        remove = true;
    }

    if (remove) {
        if (GET_ITEM(gobj)->owner != NULL) {
            ftGw_AttackAirN_ItemParachuteSetFlag(GET_ITEM(gobj)->owner);
        }
        return true;
    }

    return false;
}
