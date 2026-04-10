#include "itclimbersstring.h"

#include "placeholder.h"

#include "ft/chara/ftPopo/ftPp_SpecialS.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/itCharItems.h"
#include "it/item.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobjplink.h>
#include <baselib/jobj.h>

/* 2C248C */ static void it_802C248C(Item* ip, HSD_JObj* jobj);
/* 2C28DC */ static void fn_802C28DC(Item_GObj* gobj);
/* 2C29E8 */ static void fn_802C29E8(Item_GObj* gobj);
/* 2C2AF4 */ static void fn_802C2AF4(HSD_GObj* gobj);
/* 2C33B8 */ static void it_802C33B8(Item* item);

void it_802C2750(Item_GObj* gobj)
{
    int unused[2];
    Item* ip = GET_ITEM(gobj);
    if (ip != NULL) {
        if (gobj != NULL) {
            if (ip->owner != NULL) {
                ftPp_SpecialS_8012114C(ip->owner);
            }
            ip->owner = NULL;
            ip->xDD4_itemVar.climbersstring.xC = NULL;
            {
                ItemLink* cur;
                for (cur = ip->xDD4_itemVar.climbersstring.x4; cur != NULL;) {
                    HSD_GObj* cur_gobj = cur->gobj;
                    cur = cur->next;
                    HSD_GObjPLink_80390228(cur_gobj);
                }
            }
        }
        Item_8026A8EC(gobj);
    }
}

Item_GObj* it_802C27D4(Fighter_GObj* owner, Vec3* pos, int msid, float dir)
{
    Fighter* fp = owner->user_data;
    SpawnItem spawn;
    Item_GObj* item_gobj;
    PAD_STACK(20);

    spawn.kind = 0x71;
    spawn.prev_pos = *pos;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = owner;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = false;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        Item* ip = GET_ITEM(item_gobj);
        ip->xDD4_itemVar.climbersstring.xC = owner;
        it_802C248C(ip, fp->parts[FtPart_L4thNb].joint);
        Item_8026AB54(item_gobj, owner, FtPart_L4thNb);
    }
    return item_gobj;
}

void fn_802C28B8(Item_GObj* gobj)
{
    it_802C33B8(GET_ITEM(gobj));
}

void it_2725_Logic70_EvtUnk(Item_GObj* arg0, Item_GObj* arg1)
{
    Item* ip = GET_ITEM((HSD_GObj*) arg0);
    it_8026B894(arg0, (HSD_GObj*) arg1);
    if (ip->xDD4_itemVar.climbersstring.xC == arg1) {
        ip->xDD4_itemVar.climbersstring.xC = NULL;
    }
}

void it_802C3810(Item_GObj* gobj)
{
    Item* item;
    int unused[2];

    item = gobj->user_data;
    Item_80268E5C(gobj, 2, 2);
    it_8026BB20(gobj);
    item->on_accessory = fn_802C29E8;
}

void it_802C3864(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    u8 _pad[16];
    ItemLink* link = ip->xDD4_itemVar.climbersstring.x8;
    Mtx mtx;
    PAD_STACK(8);

    PSMTXIdentity(mtx);
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.0f;

    {
        Item* ip2 = ip;
        HSD_JObjSetupMatrix(link->jobj);
        PSMTXConcat(link->jobj->mtx, mtx, mtx);
        ip2->xDD4_itemVar.climbersstring.x0 = 2.25f;
    }
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    it_8026BB20(gobj);
    ip->on_accessory = fn_802C2AF4;
}

void it_802C3950(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemLink* link = ip->xDD4_itemVar.climbersstring.x4;
    Vec3 result;
    u8 _pad[8];
    Mtx mtx;
    PAD_STACK(8);

    PSMTXIdentity(mtx);
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.0f;
    HSD_JObjSetupMatrix(link->jobj);
    PSMTXConcat(link->jobj->mtx, mtx, mtx);
    result.x = mtx[0][3];
    result.y = mtx[1][3];
    result.z = mtx[2][3];
    link->pos = result;
    link->coll_data.cur_pos = link->pos;
    link->coll_data.last_pos = link->coll_data.cur_pos;
    link->x2C_b0 = 1;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_8026BB20(gobj);
    ip->on_accessory = fn_802C28DC;
}

void it_2725_Logic70_PickedUp(Item_GObj* gobj)
{
    short pad;
    void (*new_var)(Item_GObj* gobj);
    Item* ip = gobj->user_data;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_8026BB44(gobj);
    new_var = &fn_802C28B8;
    ip->on_accessory = *new_var;
}
