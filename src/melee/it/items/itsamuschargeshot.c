#include "itsamuschargeshot.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/gobj.h"
#include "ef/eflib.h"
#include "ef/efsync.h"

#include "baselib/forward.h"
#include "it/forward.h"
#include "ft/chara/ftSamus/ftSs_SpecialN.h"
#include "ft/chara/ftKirby/ftKb_Init.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <math.h>

bool it_802B5518(Item_GObj* gobj, CollData* cd)
{
    Item* ip = GET_ITEM(gobj);
    bool ret = false;
    it_8026DA08(gobj);
    if (ip->x40_vel.y > 0.0f) {
        if (cd->env_flags & Collide_CeilingMask) {
            ret = true;
        }
    } else if (cd->env_flags & Collide_FloorMask) {
        ret = true;
    }
    if (ip->x40_vel.x > 0.0f) {
        if (cd->env_flags & Collide_LeftWallMask) {
            ret = true;
        }
    } else if (cd->env_flags & Collide_RightWallMask) {
        ret = true;
    }
    return ret;
}

/// #it_802B55C8

/// #it_802B56E4

void it_2725_Logic108_Destroyed(Item_GObj* gobj)
{
    Item* ip;
    enum ItemKind temp_r0;

    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        efLib_DestroyAll((HSD_GObj*) gobj);
        if (ip->xDD4_itemVar.samuschargeshot.x14 == 0) {
            if ((ip->xDD4_itemVar.samuschargeshot.x2C != NULL) && (ip->owner == ip->xDD4_itemVar.samuschargeshot.x2C)) {
                temp_r0 = ip->kind;
                switch (temp_r0) {
                    case It_Kind_Samus_Charge:
                        ftSs_SpecialN_801291F0(ip->xDD4_itemVar.samuschargeshot.x2C);
                        break;
                    case It_Kind_Kirby_SamusCharge:
                        ftKb_SpecialNSs_800FCD04(ip->xDD4_itemVar.samuschargeshot.x2C);
                        break;
                }
            }
            ip->xDD4_itemVar.samuschargeshot.x2C = 0;
        }
        ip->owner = NULL;
        ip->xDC8_word.flags.x13 = 0;
    }
}


void it_802B5974(Item_GObj* gobj)
{
    Item* ip;

    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        efLib_DestroyAll((HSD_GObj*) gobj);
        ip->xDD4_itemVar.samuschargeshot.x28 = 0;
        Item_8026A8EC(gobj);
    }
}

void it_2725_Logic108_PickedUp(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child;
    Item* ip = GET_ITEM(gobj);
    enum ItemKind kind;

    if (!jobj) {
        child = NULL;
    } else {
        child = jobj->child;
    }
    if (!child) {
        child = NULL;
    } else {
        child = child->child;
    }

    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    switch (ip->kind) {
        case It_Kind_Samus_Charge:
            efSync_Spawn(0x47F, (HSD_GObj* ) gobj, child);
            ip->xDD4_itemVar.samuschargeshot.x28 = 1;
            return;
        case It_Kind_Kirby_SamusCharge:
            efSync_Spawn(0x4A1, (HSD_GObj* ) gobj, child);
            ip->xDD4_itemVar.samuschargeshot.x28 = 1;
            return;
    }
}


bool itSamuschargeshot_UnkMotion8_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* grandchild = itGetJObjGrandchild(gobj);

    f32 temp = *(f32*) &ip->xDD4_itemVar.samuschargeshot.x10;
    Vec3 scale;
    scale.z = temp;
    scale.y = temp;
    scale.x = temp;

    if (grandchild == NULL) {
        __assert("jobj.h", 0x2F8U, "jobj");
    }

    grandchild->scale = scale;

    if (!(grandchild->flags & 0x02000000)) {
        if (grandchild != NULL) {
            if (grandchild == NULL) {
                __assert("jobj.h", 0x234U, "jobj");
            }
            {
                u32 flags = grandchild->flags;
                s32 c2 = 0;
                if (!(flags & 0x800000) && (flags & 0x40)) {
                    c2 = 1;
                }
                if (c2 == 0) {
                    HSD_JObjSetMtxDirtySub(grandchild);
                }
            }
        }
    }
    return it_80273130(gobj);
}

void itSamuschargeshot_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itSamuschargeshot_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802B5CBC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSamusChargeShot_Attributes* attr = ip->xC4_article_data->x4_specialAttributes;
    HSD_GObjEvent event;

    it_80275158(gobj, attr->lifetime);
    efLib_DestroyAll(gobj);
    ip->xDD4_itemVar.samuschargeshot.x28 = 0.0f;

    if (ip->xDD4_itemVar.samuschargeshot.x18 < 0) {
        ip->xDD4_itemVar.samuschargeshot.x18 = 0;
    }
    if (ip->xDD4_itemVar.samuschargeshot.x18 >= 8) {
        ip->xDD4_itemVar.samuschargeshot.x18 = 7;
    }
    Item_80268E5C(gobj, ip->xDD4_itemVar.samuschargeshot.x18 + 1, ITEM_ANIM_UPDATE);
    ip->on_accessory = it_802B5EDC;
}

/// #itSamuschargeshot_UnkMotion8_Anim

void itSamuschargeshot_UnkMotion8_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.x = ip->xDD4_itemVar.samuschargeshot.x8 *
                    cosf(ip->xDD4_itemVar.samuschargeshot.x4);
    ip->x40_vel.y = ip->xDD4_itemVar.samuschargeshot.x8 *
                    sinf(ip->xDD4_itemVar.samuschargeshot.x4);
}

bool itSamuschargeshot_UnkMotion8_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (it_802B5518(gobj, &ip->x378_itemColl)) {
        return true;
    }
    return false;
}

void it_802B5EDC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    if ((ip->xDD4_itemVar.samuschargeshot.x18 ==
         ip->xDD4_itemVar.samuschargeshot.x1C) &&
        (ip->xDD4_itemVar.samuschargeshot.x20 == 0))
    {
        switch (ip->kind) {
            case It_Kind_Samus_Charge:
                efSync_Spawn(0x480, gobj, jobj);
                efSync_Spawn(0x481, gobj, jobj);
                break;
            case It_Kind_Kirby_SamusCharge:
                efSync_Spawn(0x4A2, gobj, jobj);
                efSync_Spawn(0x4A3, gobj, jobj);
                break;
        }
    }
    ip->xDD4_itemVar.samuschargeshot.x20 =
        ip->xDD4_itemVar.samuschargeshot.x20 + 1;
    ip->xDD4_itemVar.samuschargeshot.x20 =
        ip->xDD4_itemVar.samuschargeshot.x20 % 3;
}

bool itSamusChargeshot_Logic108_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool itSamusChargeshot_Logic108_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itSamusChargeshot_Logic108_Absorbed(Item_GObj* arg0)
{
    return true;
}

/// #it_2725_Logic108_Reflected

bool itSamusChargeshot_Logic108_HitShield(Item_GObj* arg0)
{
    return true;
}

/// #it_2725_Logic108_ShieldBounced

void itSamusChargeshot_Logic108_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
