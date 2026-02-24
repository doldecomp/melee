#include "itmariocape.h"

#include "db/db.h"
#include "ef/efasync.h"
#include "ft/chara/ftMario/ftMr_SpecialS.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

Item_GObj* it_802B2560(Fighter_GObj* parent_gobj, float facing_dir, Vec3* pos,
                       Fighter_Part part, ItemKind kind)
{
    SpawnItem spawn;
    Item_GObj* gobj;

    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0;
    spawn.x0_parent_gobj = parent_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;

    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        Item_8026AB54(gobj, parent_gobj, part);
        db_80225DD8(gobj, parent_gobj);
        return gobj;
    }
    return NULL;
}

void it_802B2674(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(4);

    if (ip != NULL) {
        if (ip->owner != NULL) {
            ftMr_SpecialS_Reset(ip->owner);
        }
        Item_8026A8EC(gobj);
    }
}

void it_802B26C0(Item_GObj* gobj)
{
    it_8026B724(gobj);
}

void it_802B26E0(Item_GObj* gobj)
{
    it_8026B73C(gobj);
}

void it_2725_Logic41_PickedUp(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDAC_itcmd_var0 = ip->xDB0_itcmd_var1 = 0;
    if (ip->owner != NULL) {
        if (ftLib_800865CC(gobj) != 1) {
            Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
        } else {
            Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        }
        Item_802694CC(gobj);
        it_80274574(gobj);
    }
}

static void inlineA0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    bool removed;
    PAD_STACK(8);

    if (ip->xDAC_itcmd_var0 != 0) {
        ip->xDAC_itcmd_var0 = 0;
        efAsync_Spawn(gobj, &GET_ITEM(gobj)->xBC0, 0, 1149,
                      ip->xBBC_dynamicBoneTable->bones[16]);
    }
    if (ip->xDB0_itcmd_var1 != 0) {
        ip->xDB0_itcmd_var1 = 0;
        efAsync_Spawn(gobj, &GET_ITEM(gobj)->xBC0, 0, 1150,
                      ip->xBBC_dynamicBoneTable->bones[6]);
    }
}

inline void reset(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->owner != NULL) {
        ftMr_SpecialS_Reset(ip->owner);
    }
}

bool itMariocape_UnkMotion1_Anim(Item_GObj* gobj)
{
    inlineA0(gobj);
    PAD_STACK(4);
    {
        Item* ip = GET_ITEM(gobj);
        bool removed;
        if (ip->owner != NULL) {
            removed = ftMr_SpecialS_CheckItemCapeRemove(ip->owner);
        } else {
            removed = true;
        }
        if (removed) {
            reset(gobj);
            return true;
        }
        return false;
    }
}

void it_802B2870(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void itMarioCape_Logic41_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->owner != NULL) {
        ftMr_SpecialS_Reset(ip->owner);
    }
}
