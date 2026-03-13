#include "itclinkmilk.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"

typedef struct itClinkmilkVars {
    /* +00 ip+DD4 */ HSD_GObj* x0;
} itClinkmilkVars;

typedef struct itClinkmilkLink {
    /* +000 */ u8 pad_0[0x518];
    /* +518 */ HSD_GObj* x518;
} itClinkmilkLink;

HSD_GObj* it_802C8B28(Item_GObj* parent_gobj, Vec3* pos, u32 kind, f32 facing)
{
    SpawnItem spawn;
    Item_GObj* gobj;
    u8 _[4];

    if (parent_gobj != NULL) {
        spawn.kind = 0x7B;
        spawn.prev_pos = *pos;
        spawn.prev_pos.z = it_804DD310;
        spawn.pos = spawn.prev_pos;
        spawn.facing_dir = facing;
        spawn.x3C_damage = 0;
        spawn.vel.z = it_804DD310;
        spawn.vel.y = it_804DD310;
        spawn.vel.x = it_804DD310;
        spawn.x0_parent_gobj = parent_gobj;
        spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
        spawn.x44_flag.b0 = false;
        spawn.x40 = 0;
        gobj = Item_80268B18(&spawn);
        if (gobj != NULL) {
            Item* ip = GET_ITEM(gobj);

            ip->xDB8_itcmd_var3 = 0;
            ip->xDB4_itcmd_var2 = 0;
            ip->xDB0_itcmd_var1 = 0;
            ip->xDAC_itcmd_var0 = 0;
            ip->xDCC_flag.b3 = false;
            ((itClinkmilkVars*) &ip->xDD4_itemVar)->x0 = parent_gobj;
            Item_8026AB54(gobj, parent_gobj, kind);
        }
    } else {
        gobj = NULL;
    }
    return gobj;
}

void it_802C8C34(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);

        if (ip != NULL) {
            ((itClinkmilkVars*) &ip->xDD4_itemVar)->x0 = NULL;
            ((itClinkmilkLink*) ip)->x518 = NULL;
            Item_8026A8EC(gobj);
        }
    }
}

void it_2725_Logic80_PickedUp(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->facing_dir == -1.0f) {
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    } else {
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    }
    Item_802694CC(gobj);
}

/// #itClinkmilk_UnkMotion1_Anim

void itClinkmilk_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itClinkmilk_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void itCLinkMilk_Logic80_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
