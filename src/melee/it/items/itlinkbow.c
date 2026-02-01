#include "it/items/itlinkbow.h"

#include "ft/chara/ftKirby/ftKb_Init.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"

#include <baselib/gobj.h>

/* 2AF32C */ static void it_802AF32C(HSD_GObj*);
/* 2AF64C */ static bool itLinkbow_UnkMotion5_Anim(Item_GObj* gobj);
/* 2AF844 */ static void itLinkbow_UnkMotion5_Phys(HSD_GObj*);
/* 2AF848 */ static bool itLinkbow_UnkMotion5_Coll(Item_GObj* gobj);
/* 2AF90C */ static bool itLinkbow_UnkMotion6_Anim(Item_GObj* gobj);
/* 2AF914 */ static void itLinkbow_UnkMotion6_Phys(HSD_GObj*);
/* 2AF918 */ static bool itLinkbow_UnkMotion6_Coll(Item_GObj* gobj);

ItemStateTable it_803F6E98[] = {
    { 0, itLinkbow_UnkMotion5_Anim, itLinkbow_UnkMotion5_Phys,
      itLinkbow_UnkMotion5_Coll },
    { 1, itLinkbow_UnkMotion5_Anim, itLinkbow_UnkMotion5_Phys,
      itLinkbow_UnkMotion5_Coll },
    { 2, itLinkbow_UnkMotion5_Anim, itLinkbow_UnkMotion5_Phys,
      itLinkbow_UnkMotion5_Coll },
    { 3, itLinkbow_UnkMotion5_Anim, itLinkbow_UnkMotion5_Phys,
      itLinkbow_UnkMotion5_Coll },
    { 4, itLinkbow_UnkMotion5_Anim, itLinkbow_UnkMotion5_Phys,
      itLinkbow_UnkMotion5_Coll },
    { 5, itLinkbow_UnkMotion5_Anim, itLinkbow_UnkMotion5_Phys,
      itLinkbow_UnkMotion5_Coll },
    { -1, itLinkbow_UnkMotion6_Anim, itLinkbow_UnkMotion6_Phys,
      itLinkbow_UnkMotion6_Coll }
};

static s32 it_803F6F08[7] = { 0, 1, 2, 3, 4, 5, 6 };
static s32 it_803F6F24[7] = { 3, 4, 5, 0, 1, 2, 6 };

HSD_GObj* it_802AF1A4(f32 facing_dir, Fighter_GObj* owner_gobj, Vec3* vec,
                      Fighter_Part arg3, int arg4)
{
    Item_GObj* gobj;
    Item* item;
    SpawnItem spawn;
    f32 pad[1];

    spawn.kind = arg4;
    spawn.prev_pos = *vec;
    spawn.prev_pos.z = 0.0F;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0.0F;
    spawn.vel.y = 0.0F;
    spawn.vel.x = 0.0F;
    spawn.x0_parent_gobj = (HSD_GObj*) owner_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0.0F;

    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        item = GET_ITEM((HSD_GObj*) gobj);
        item->xDB8_itcmd_var3 = 0;
        item->xDB4_itcmd_var2 = 0;
        item->xDB0_itcmd_var1 = 0;
        item->xDAC_itcmd_var0 = 0;
        item->xDCC_flag.b3 = false;
        item->xDD4_itemVar.linkbow.x0 = ftLib_800869D4(item->owner);
        item->xDD4_itemVar.linkbow.x4 = owner_gobj;
        Item_8026AB54((HSD_GObj*) gobj, (HSD_GObj*) owner_gobj, arg3);
    }
    return (HSD_GObj*) gobj;
}

void itLinkBow_Logic100_Destroyed(Item_GObj* arg0)
{
    Item* item;
    if (arg0 != NULL) {
        item = GET_ITEM((HSD_GObj*) arg0);
        if (item->owner != NULL) {
            switch (item->kind) {
            case It_Kind_Link_Bow:
            case It_Kind_CLink_Bow:
                ftLk_SpecialN_UnsetFv14(item->owner);
                break;
            case It_Kind_Kirby_CLinkBow:
            case It_Kind_Kirby_LinkBow:
                ftKb_SpecialNLk800FB444(item->owner);
                break;
            }
        }
    }
}

void it_802AF304(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item_8026A8EC(gobj);
    }
}

void it_802AF32C(HSD_GObj* arg0)
{
    f32 temp_f31;
    Item* item;
    enum ftLk_SpecialNIndex arg1;

    item = GET_ITEM((HSD_GObj*) arg0);

    if (item->xDD4_itemVar.linkbow.x4 != NULL) {
        if (item->owner == item->xDD4_itemVar.linkbow.x4) {
            switch (item->kind) {
            case It_Kind_Link_Bow:
            case It_Kind_CLink_Bow:
                arg1 = ftLk_SpecialN_GetIndex(item->owner);
                break;
            case It_Kind_Kirby_CLinkBow:
            case It_Kind_Kirby_LinkBow:
                arg1 = ftKb_SpecialNLk800FB394(item->owner);
                break;
            }
            if (item->msid != it_803F6F08[arg1]) {
                if (item->msid == it_803F6F24[arg1]) {
                    temp_f31 = item->x5CC_currentAnimFrame;
                    Item_80268E5C(arg0, arg1, ITEM_ANIM_UPDATE);
                    Item_802694CC(arg0);
                    Item_80268DD4(arg0, temp_f31);
                    return;
                }
                Item_80268E5C(arg0, arg1, ITEM_ANIM_UPDATE);
                Item_802694CC(arg0);
            }
        }
    }
}

void itLinkBow_Logic100_PickedUp(Item_GObj* arg0)
{
    HSD_JObj* jobj;
    Item* item;
    Vec3 scale;
    enum ftLk_SpecialNIndex idx;

    item = GET_ITEM((HSD_GObj*) arg0);
    jobj = HSD_GObjGetHSDObj((HSD_GObj*) arg0);

    if (item->xDD4_itemVar.linkbow.x4 != NULL) {
        if (item->owner == item->xDD4_itemVar.linkbow.x4) {
            switch (item->kind) {
            case It_Kind_Link_Bow:
            case It_Kind_CLink_Bow:
                idx = ftLk_SpecialN_GetIndex(item->owner);
                break;
            case It_Kind_Kirby_CLinkBow:
            case It_Kind_Kirby_LinkBow:
                idx = ftKb_SpecialNLk800FB394(item->owner);
                break;
            }

            switch (idx) {
            case ftLk_SpecialNIndex_Start:
                Item_80268E5C((HSD_GObj*) arg0, ftLk_SpecialNIndex_Start,
                              ITEM_ANIM_UPDATE);
                Item_802694CC((HSD_GObj*) arg0);
                scale.x = scale.y = scale.z = item->xDD4_itemVar.linkbow.x0;
                HSD_JObjSetScale(jobj, &scale);
                break;
            case ftLk_SpecialNIndex_AirStart:
            case ftLk_SpecialNIndex_None:
                Item_80268E5C((HSD_GObj*) arg0, ftLk_SpecialNIndex_AirStart,
                              ITEM_ANIM_UPDATE);
                Item_802694CC((HSD_GObj*) arg0);
                scale.x = scale.y = scale.z = item->xDD4_itemVar.linkbow.x0;
                HSD_JObjSetScale(jobj, &scale);
                break;
            default:
                break;
            }
        }
    }
}

bool itLinkbow_UnkMotion5_Anim(Item_GObj* arg0)
{
    Item* item;
    HSD_JObj* jobj;
    Vec3 scale;

    item = GET_ITEM((HSD_GObj*) arg0);
    jobj = HSD_GObjGetHSDObj(arg0);

    scale.x = scale.y = scale.z = item->xDD4_itemVar.linkbow.x0;
    HSD_JObjSetScale(jobj, &scale);

    switch (item->msid) {
    case 5:
    case 2:
        if ((item->x5CC_currentAnimFrame == 0.0f) ||
            ((item->x5CC_currentAnimFrame >= 24.0f)))
        {
            itLinkBow_Logic100_Destroyed((Item_GObj*) arg0);
            return 1;
        }
        break;
    default:
        it_802AF32C(arg0);
        break;
    }

    if (item->xDD4_itemVar.linkbow.x4 == NULL) {
        return 1;
    }
    if (item->owner != item->xDD4_itemVar.linkbow.x4) {
        return 1;
    }
    if (item->owner != NULL) {
        switch (item->kind) {
        case It_Kind_Link_Bow:
        case It_Kind_CLink_Bow:
            if (ftLk_SpecialN_IsActiveAnd2071b6(item->owner) != 0) {
                return 1;
            }
            break;
        case It_Kind_Kirby_CLinkBow:
        case It_Kind_Kirby_LinkBow:
            if (ftKb_SpecialNLk800FB470(item->owner) != 0) {
                return 1;
            }
            break;
        default:
            break;
        }
    }

    return 0;
}

void itLinkbow_UnkMotion5_Phys(HSD_GObj* arg0)
{
    return;
}

bool itLinkbow_UnkMotion5_Coll(Item_GObj* arg0)
{
    Item* item;
    HSD_JObj* jobj;
    Vec3 scale;

    item = GET_ITEM(arg0);
    jobj = HSD_GObjGetHSDObj(arg0);
    scale.x = scale.y = scale.z = item->xDD4_itemVar.linkbow.x0;
    HSD_JObjSetScale(jobj, &scale);
    return 0;
}

bool itLinkbow_UnkMotion6_Anim(Item_GObj* arg0)
{
    return 1;
}

void itLinkbow_UnkMotion6_Phys(HSD_GObj* arg0)
{
    return;
}

bool itLinkbow_UnkMotion6_Coll(Item_GObj* arg0)
{
    return 1;
}

void itLinkBow_Logic100_EvtUnk(Item_GObj* arg0, Item_GObj* arg1)
{
    it_8026B894(arg0, (HSD_GObj*) arg1);
}
