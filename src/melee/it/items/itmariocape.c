#include "itmariocape.h"

#include "db/db.h"
#include "ef/efasync.h"
#include "ft/chara/ftMario/ftMr_SpecialS.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

HSD_GObj* it_802B2560(Item_GObj* arg0, f32 farg0, Vec3* arg1,
                      enum Fighter_Part arg2, u32 arg3)
{
    SpawnItem spawn;
    Item_GObj* temp_r3;
    spawn.kind = arg3;
    spawn.prev_pos = *arg1;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = farg0;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0;
    spawn.vel.y = 0;
    spawn.vel.x = 0;
    spawn.x0_parent_gobj = arg0;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    temp_r3 = Item_80268B18(&spawn);
    if (temp_r3 != NULL) {
        Item_8026AB54(temp_r3, arg0, arg2);
        db_80225DD8(temp_r3, arg0);
        return temp_r3;
    }
    return NULL;
}

void it_802B2674(Item_GObj* item_gobj)
{
    int pad[1];
    Item* item = GET_ITEM(item_gobj);

    if (item != NULL) {
        if (item->owner != NULL) {
            ftMr_SpecialS_Reset(item->owner);
        }
        Item_8026A8EC(item_gobj);
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
    Item* item = GET_ITEM(gobj);
    item->xDB0_itcmd_var1 = 0;
    item->xDAC_itcmd_var0 = 0;
    if (item->owner != NULL) {
        if (ftLib_800865CC(gobj) != 1) {
            Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
        } else {
            Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        }
        Item_802694CC(gobj);
        it_80274574(gobj);
    }
}

bool itMariocape_UnkMotion1_Anim(HSD_GObj* gobj)
{
    Item* ip;
    Item* item = GET_ITEM(gobj);
    bool BoolVar;
    PAD_STACK(8);
    if (item->xDAC_itcmd_var0 != 0) {
        item->xDAC_itcmd_var0 = 0;
        efAsync_Spawn(gobj, &GET_ITEM(gobj)->xBC0, 0, 0x47d,
                      item->xBBC_dynamicBoneTable->bones[16]);
    }
    if (item->xDB0_itcmd_var1 != 0) {
        item->xDB0_itcmd_var1 = 0;
        efAsync_Spawn(gobj, &GET_ITEM(gobj)->xBC0, 0, 0x47e,
                      item->xBBC_dynamicBoneTable->bones[6]);
    }
    ip = GET_ITEM(gobj);
    if (ip->owner != 0) {
        BoolVar = ftMr_SpecialS_CheckItemCapeRemove(ip->owner);
    } else {
        BoolVar = true;
    }
    if (BoolVar != 0) {
        ip = GET_ITEM(gobj);
        if (ip->owner != 0) {
            ftMr_SpecialS_Reset(ip->owner);
        }
        return true;
    }
    return false;
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
