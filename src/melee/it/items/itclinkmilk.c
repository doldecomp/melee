#include "itclinkmilk.h"

#include "ft/chara/ftCLink/ftCl_Init.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"

ItemStateTable it_803F7A28[] = {
    { 0, itClinkmilk_UnkMotion1_Anim, itClinkmilk_UnkMotion1_Phys,
      itClinkmilk_UnkMotion1_Coll },
    { 1, itClinkmilk_UnkMotion1_Anim, itClinkmilk_UnkMotion1_Phys,
      itClinkmilk_UnkMotion1_Coll },
};

HSD_GObj* it_802C8B28(Item_GObj* parent, Vec3* pos, u32 bone, float facing_dir)
{
    Item_GObj* item_gobj;
    SpawnItem spawn;
    PAD_STACK(4);
    if (parent != NULL) {
        spawn.kind = 0x7B;
        spawn.prev_pos = *pos;
        spawn.prev_pos.z = 0.0f;
        spawn.pos = spawn.prev_pos;
        spawn.facing_dir = facing_dir;
        spawn.x3C_damage = 0;
        spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
        spawn.x0_parent_gobj = parent;
        spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
        spawn.x44_flag.b0 = false;
        spawn.x40 = 0;
        item_gobj = Item_80268B18(&spawn);
        if (item_gobj != NULL) {
            Item* ip = GET_ITEM(item_gobj);
            ip->xDB8_itcmd_var3 = 0;
            ip->xDB4_itcmd_var2 = 0;
            ip->xDB0_itcmd_var1 = 0;
            ip->xDAC_itcmd_var0 = 0;
            ip->xDCC_flag.b3 = false;
            ip->xDD4_itemVar.clinkmilk.x0 = parent;
            Item_8026AB54(item_gobj, parent, bone);
        }
    } else {
        item_gobj = NULL;
    }
    return item_gobj;
}

void it_802C8C34(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = gobj->user_data;
        if (ip != NULL) {
            ip->xDD4_itemVar.clinkmilk.x0 = NULL;
            ip->owner = NULL;
            Item_8026A8EC(gobj);
        }
    }
}

void it_2725_Logic80_PickedUp(Item_GObj* gobj)
{
    Item* ip = GET_ITEM((HSD_GObj*) gobj);
    if (ip->facing_dir == 1.0f) {
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    } else {
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    }
    Item_802694CC(gobj);
}

static inline void itCLinkMilk_NotifyParent(Item_GObj* gobj)
{
    Item* ip2;
    if (gobj) {
        Item* ip = GET_ITEM(gobj);
        if (gobj && ip) {
            // permuterslop
            Fighter_GObj* parent = (ip2 = ip)->xDD4_itemVar.clinkmilk.x0;
            if (parent != NULL && ip->owner == parent) {
                ftCl_Init_801492C4(parent);
            }
            ip->xDD4_itemVar.clinkmilk.x0 = NULL;
            ip->owner = NULL;
        }
    }
}

static inline bool itCLinkMilk_Destroy(Item_GObj* gobj)
{
    if (gobj) {
        Item* ip = GET_ITEM(gobj);
        if (ip != NULL) {
            ip->xDD4_itemVar.clinkmilk.x0 = NULL;
            ip->owner = NULL;
            return true;
        }
    }
    return false;
}

bool itClinkmilk_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* child = HSD_JObjGetChild(gobj->hsd_obj);
    HSD_JObj* grandchild = HSD_JObjGetChild(gobj->hsd_obj);
    u8 _pad[4];
    Vec3 sv;
    PAD_STACK(12);

    if (ip->xDAC_itcmd_var0 == 1) {
        HSD_JObjClearFlags(grandchild, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlags(grandchild, JOBJ_HIDDEN);
    }

    if (ip->xDD4_itemVar.clinkmilk.x0 != NULL) {
        if (ftCl_Init_8014920C(ip->xDD4_itemVar.clinkmilk.x0) == true) {
            itCLinkMilk_NotifyParent(gobj);
            if (itCLinkMilk_Destroy(gobj)) {
                return true;
            }
        } else {
            ip->xDAC_itcmd_var0 =
                ftCl_Init_801492F4(ip->xDD4_itemVar.clinkmilk.x0);
            sv.x = sv.y = sv.z = ftLib_800869D4(ip->xDD4_itemVar.clinkmilk.x0);
            HSD_JObjSetScale(child, &sv);
        }
    } else {
        itCLinkMilk_NotifyParent(gobj);
        if (itCLinkMilk_Destroy(gobj)) {
            return true;
        }
    }
    return false;
}

void itClinkmilk_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itClinkmilk_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void itCLinkMilk_Logic80_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
