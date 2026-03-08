#include "itseakneedleheld.h"

#include "ft/chara/ftKirby/ftKb_Init.h"
#include "ft/chara/ftSeak/ftSk_SpecialS.h"

#include "ft/forward.h"

#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"

#include <baselib/jobj.h>

ItemStateTable it_803F70A8[] = {
    {
        -1,
        itSeakneedleheld_UnkMotion0_Anim,
        itSeakneedleheld_UnkMotion0_Phys,
        itSeakneedleheld_UnkMotion0_Coll,
    },
};

void it_802B18B0(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* child = HSD_JObjGetChild(jobj);
    HSD_JObj* needle = HSD_JObjGetChild(child);
    Fighter_GObj* owner = ip->xDD4_itemVar.seakneedleheld.owner;
    int count;
    int i;

    if (owner == NULL) {
        return;
    }
    if (ip->owner != owner) {
        return;
    }

    switch (ip->kind) {
    case It_Kind_Seak_NeedleHeld:
        count = ftSk_SpecialS_80111FA0(owner);
        break;
    case It_Kind_Kirby_SeakNeedleHeld:
        count = ftKb_SpecialNSk_80106020(owner);
        break;
    default:
        break;
    }

    for (i = 0; i < 6; i++) {
        if (i < count) {
            HSD_JObjClearFlagsAll(needle, JOBJ_HIDDEN);
        } else {
            HSD_JObjSetFlagsAll(needle, JOBJ_HIDDEN);
        }
        needle = HSD_JObjGetNext(needle);
    }
}

Item_GObj* it_802B19AC(Fighter_GObj* parent_gobj, Vec3* cur_pos,
                       Fighter_Part part, ItemKind kind, float facing_dir)
{
    SpawnItem spawn;

    spawn.kind = kind;
    spawn.prev_pos = *cur_pos;
    spawn.prev_pos.z = 0.0f;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = parent_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;

    {
        Item_GObj* gobj = Item_80268B18(&spawn);
        if (gobj != NULL) {
            Item* ip = GET_ITEM(gobj);
            PAD_STACK(2 * 4);
            ip->xDAC_itcmd_var0 = ip->xDB0_itcmd_var1 = ip->xDB4_itcmd_var2 =
                ip->xDB8_itcmd_var3 = 0;
            ip->xDCC_flag.b3 = false;
            ip->xDD4_itemVar.seakneedleheld.owner = parent_gobj;
            Item_8026AB54(gobj, parent_gobj, part);
        }
        return gobj;
    }
}

void itSeakNeedleHeld_Logic110_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itSeakneedleheld_UnkMotion0_Anim(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* needle = HSD_JObjGetChild(jobj);
    Vec3 scale;
    PAD_STACK(3 * 4);

    if (ip->xDD4_itemVar.seakneedleheld.owner == NULL) {
        goto ret_true;
    }
    if (ip->owner != ip->xDD4_itemVar.seakneedleheld.owner) {
        goto ret_false;
    }

    switch (ip->kind) {
    case It_Kind_Seak_NeedleHeld:
        if (ftSk_SpecialS_80111F70(ip->xDD4_itemVar.seakneedleheld.owner) == 1)
        {
            return true;
        }
        break;
    case It_Kind_Kirby_SeakNeedleHeld:
        if (ftKb_SpecialNSk_80105FF0(ip->xDD4_itemVar.seakneedleheld.owner) ==
            1)
        {
            return true;
        }
        break;
    default:
        break;
    }

    it_802B18B0(gobj);

    scale.x = scale.y = scale.z =
        ftLib_800869D4(ip->xDD4_itemVar.seakneedleheld.owner);
    HSD_JObjSetScale(needle, &scale);
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
