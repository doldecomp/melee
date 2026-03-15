#include "itnessbat.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/chara/ftNess/ftNs_AttackS4.h"
#include "ft/ft_0BF0.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <baselib/jobj.h>

static inline void itNessbat_ClearOwnerRef(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (gobj != NULL && ip != NULL) {
        HSD_GObj* x0 = ip->xDD4_itemVar.nessbat.x0;
        if (x0 != NULL && ip->owner == x0) {
            ftNs_AttackS4_ItemNessBatSetNULL(x0);
        }
        ip->xDD4_itemVar.nessbat.x0 = NULL;
        ip->owner = NULL;
    }
}

static inline bool itNessbat_RemoveItem(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        ip->xDD4_itemVar.nessbat.x0 = NULL;
        ip->owner = NULL;
        return true;
    }
    return false;
}

HSD_GObj* it_802AD478(Item_GObj* gobj, Vec3* pos, Fighter_Part part,
                      f32 facing_dir)
{
    SpawnItem spawn;
    Item_GObj* bat;
    PAD_STACK(4);

    if (gobj != NULL) {
        spawn.kind = It_Kind_Ness_Bat;
        spawn.prev_pos = *pos;
        spawn.prev_pos.z = 0.0f;
        spawn.pos = spawn.prev_pos;
        spawn.facing_dir = facing_dir;
        spawn.x3C_damage = 0;
        spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
        spawn.x0_parent_gobj = gobj;
        spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
        spawn.x44_flag.b0 = false;
        spawn.x40 = 0;

        bat = Item_80268B18(&spawn);
        if (bat != NULL) {
            Item* ip = GET_ITEM(bat);
            ip->xDB8_itcmd_var3 = 0;
            ip->xDB4_itcmd_var2 = 0;
            ip->xDB0_itcmd_var1 = 0;
            ip->xDAC_itcmd_var0 = 0;
            ip->xDCC_flag.b3 = false;
            ip->xDD4_itemVar.nessbat.x0 = gobj;
            it_80275158(bat, 1200.0f);
            Item_8026AB54(bat, gobj, part);
        }
    } else {
        bat = NULL;
    }
    return bat;
}

Item_GObj* it_802AD590(Fighter_GObj* gobj, Fighter_Part part)
{
    SpawnItem spawn;
    Item_GObj* bat;
    Vec3 pos;
    PAD_STACK(4);

    if (gobj != NULL) {
        spawn.kind = It_Kind_Ness_Bat;
        ftLib_80086644(gobj, &pos);
        spawn.prev_pos = pos;
        spawn.prev_pos.z = 0.0f;
        spawn.pos = spawn.prev_pos;
        spawn.facing_dir = ftLib_800865C0(gobj);
        spawn.x3C_damage = 0;
        spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
        spawn.x0_parent_gobj = gobj;
        spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
        spawn.x44_flag.b0 = false;
        spawn.x40 = 0;

        bat = Item_80268B18(&spawn);
        if (bat != NULL) {
            Item* ip = GET_ITEM(bat);
            ip->xDB8_itcmd_var3 = 1;
            ip->xDB4_itcmd_var2 = 1;
            ip->xDB0_itcmd_var1 = 1;
            ip->xDAC_itcmd_var0 = 1;
            ip->xDCC_flag.b3 = false;
            ip->xDD4_itemVar.nessbat.x0 = gobj;
            Item_8026AB54(bat, gobj, part);
        }
    } else {
        bat = NULL;
    }
    return bat;
}

void it_802AD6B8(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        ip->xDD4_itemVar.nessbat.x0 = 0;
        ip->owner = NULL;
        Item_8026A8EC(gobj);
    }
}

void it_2725_Logic58_PickedUp(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if ((ip->xDAC_itcmd_var0 | ip->xDB0_itcmd_var1 | ip->xDB4_itcmd_var2 |
         ip->xDB8_itcmd_var3) != 0)
    {
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    } else {
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    }
    Item_802694CC(gobj);
}

bool itNessbat_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child = HSD_JObjGetChild(jobj);
    PAD_STACK(24);

    if (ip->xDAC_itcmd_var0 == 0) {
        HSD_JObjClearFlagsAll(child, 0x10);
    } else {
        HSD_JObjSetFlagsAll(child, 0x10);
    }

    if (ip->xDD4_itemVar.nessbat.x0 != NULL) {
        if (ftNs_AttackS4_CheckNessBatRemove(ip->xDD4_itemVar.nessbat.x0) ==
            true)
        {
            itNessbat_ClearOwnerRef(gobj);
            if (itNessbat_RemoveItem(gobj)) {
                return true;
            }
        }
    } else {
        itNessbat_ClearOwnerRef(gobj);
        if (itNessbat_RemoveItem(gobj)) {
            return true;
        }
    }
    return false;
}

void itNessbat_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itNessbat_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

static inline void copy_jobj_scale(HSD_JObj* dst, HSD_JObj* src, Vec3* scale)
{
    scale->x = scale->y = scale->z = HSD_JObjGetScaleY(src);
    HSD_JObjSetScale(dst, scale);
}

bool itNessbat_UnkMotion1_Anim(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        if (ip != NULL) {
            if (ip->xDD4_itemVar.nessbat.x0 != NULL) {
                if (ftCo_800BF228(ip->xDD4_itemVar.nessbat.x0) == true) {
                    Vec3 scale;
                    HSD_GObj* owner = ip->xDD4_itemVar.nessbat.x0;
                    copy_jobj_scale(GET_JOBJ(gobj), GET_JOBJ(owner), &scale);
                }
            }
        }
    }
    return false;
}

void itNessbat_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itNessbat_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void itNessBat_Logic58_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
