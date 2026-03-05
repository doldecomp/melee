#include "itseakneedleheld.h"

#include "it/it_26B1.h"
#include "it/item.h"
#include "it/inlines.h"

#include "ft/ftlib.h"
#include "ft/chara/ftKirby/ftKb_Init.h"
#include "ft/chara/ftSeak/ftSk_SpecialS.h"

#include <baselib/jobj.h>

void it_802B18B0(Item_GObj* gobj)
{
    HSD_JObj* jobj;
    Item* ip;
    HSD_JObj* child;
    HSD_JObj* needle;
    Fighter_GObj* holder;
    s32 count;
    s32 i;

    jobj = gobj->hsd_obj;
    ip = GET_ITEM(gobj);

    child = (jobj == NULL) ? NULL : jobj->child;
    needle = (child == NULL) ? NULL : child->child;

    holder = ip->xDD4_itemVar.seakneedleheld.xDD4_fighter;

    if (holder == NULL) {
        return;
    }
    if (ip->owner != (HSD_GObj*) holder) {
        return;
    }

    switch (ip->kind) {
    case It_Kind_Seak_NeedleHeld:
        count = ftSk_SpecialS_80111FA0((HSD_GObj*) holder);
        break;
    case It_Kind_Kirby_SeakNeedleHeld:
        count = ftKb_SpecialNSk_80106020((HSD_GObj*) holder);
        break;
    }

    for (i = 0; i < 6; i++) {
        if (i < count) {
            HSD_JObjClearFlagsAll(needle, 0x10);
        } else {
            HSD_JObjSetFlagsAll(needle, 0x10);
        }
        needle = (needle == NULL) ? NULL : needle->next;
    }
}

Item_GObj* it_802B19AC(HSD_GObj* fighter_gobj, Vec3* cur_pos, u32 part,
                       u32 kind, float facing_dir)
{
    SpawnItem spawn;
    Item_GObj* gobj;
    Item* ip;
    PAD_STACK(2 * 4);

    spawn.kind = kind;
    spawn.prev_pos = *cur_pos;
    spawn.prev_pos.z = 0.0f;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.z = spawn.vel.y = spawn.vel.x = 0.0f;
    spawn.x0_parent_gobj = fighter_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;

    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        ip->xDB8_itcmd_var3 = 0;
        ip->xDB4_itcmd_var2 = 0;
        ip->xDB0_itcmd_var1 = 0;
        ip->xDAC_itcmd_var0 = 0;
        ip->xDCC_flag.b3 = false;
        ip->xDD4_itemVar.seakneedleheld.xDD4_fighter =
            (Fighter_GObj*) fighter_gobj;
        Item_8026AB54(gobj, fighter_gobj, part);
    }
    return gobj;
}

void itSeakNeedleHeld_Logic110_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itSeakneedleheld_UnkMotion0_Anim(Item_GObj* gobj)
{
    HSD_JObj* root;
    Item* ip;
    HSD_JObj* jobj;
    Vec3 scale;
    PAD_STACK(4 * 4);

    root = gobj->hsd_obj;
    ip = GET_ITEM(gobj);

    jobj = (root == NULL) ? NULL : root->child;

    if (ip->xDD4_itemVar.seakneedleheld.xDD4_fighter == NULL) {
        goto ret_true;
    }
    if (ip->owner !=
        (HSD_GObj*) ip->xDD4_itemVar.seakneedleheld.xDD4_fighter)
    {
        goto ret_false;
    }

    switch (ip->kind) {
    case It_Kind_Seak_NeedleHeld:
        if (ftSk_SpecialS_80111F70(
                (HSD_GObj*) ip->xDD4_itemVar.seakneedleheld.xDD4_fighter) == 1)
        {
            return true;
        }
        break;
    case It_Kind_Kirby_SeakNeedleHeld:
        if (ftKb_SpecialNSk_80105FF0(
                (HSD_GObj*) ip->xDD4_itemVar.seakneedleheld.xDD4_fighter) == 1)
        {
            return true;
        }
        break;
    }

    it_802B18B0(gobj);

    scale.x = scale.y = scale.z =
        ftLib_800869D4((HSD_GObj*) ip->xDD4_itemVar.seakneedleheld.xDD4_fighter);
    HSD_JObjSetScale(jobj, &scale);
    goto ret_false;

ret_true:
    return true;
ret_false:
    return false;
}

void itSeakneedleheld_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itSeakneedleheld_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

void itSeakNeedleHeld_Logic110_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
