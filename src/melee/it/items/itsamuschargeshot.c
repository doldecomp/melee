#include "itsamuschargeshot.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/gobj.h"
#include "baselib/mtx.h"
#include "ef/eflib.h"
#include "ef/efsync.h"

#include "baselib/forward.h"
#include "it/forward.h"
#include "ft/chara/ftSamus/ftSs_SpecialN.h"
#include "ft/chara/ftKirby/ftKb_Init.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lbvector.h"

#include <math.h>
#include <trigf.h>

#define TAU 6.283185307179586
#define PI 3.141592653589793
#define HALF_PI 1.5707963267948966

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

HSD_GObj* it_802B55C8(Fighter_GObj* gobj, Vec3* pos,
                       enum Fighter_Part arg2, s32 arg3,
                       f32 facing_dir)
{
    SpawnItem si;
    HSD_GObj* n;

    si.kind = arg3;
    si.prev_pos = *pos;
    si.prev_pos.z = 0.0f;
    it_8026BB68(gobj, &si.pos);
    si.facing_dir = facing_dir;
    si.x3C_damage = 0;
    si.vel.x = si.vel.y = si.vel.z = 0.0f;
    si.x0_parent_gobj = gobj;
    si.x4_parent_gobj2 = si.x0_parent_gobj;
    si.x44_flag.b0 = true;
    si.x40 = 0;
    n = Item_80268B18(&si);
    if (n != NULL) {
        Item* ip = GET_ITEM(n);
        itSamusChargeShot_Attributes* attr =
            ip->xC4_article_data->x4_specialAttributes;
        ip->xDB8_itcmd_var3 = 0;
        ip->xDB4_itcmd_var2 = 0;
        ip->xDB0_itcmd_var1 = 0;
        ip->xDAC_itcmd_var0 = 0;
        it_80275158(n, attr->lifetime);
        ip->xDD4_itemVar.samuschargeshot.xDE8 = 0;
        ip->xDD4_itemVar.samuschargeshot.xDE0 = 0.0f;
        ip->xDD4_itemVar.samuschargeshot.xDFC = 0.0f;
        ip->xDD4_itemVar.samuschargeshot.xE00 = gobj;
        ip->xDD4_itemVar.samuschargeshot.xE04 =
            ftLib_800869D4((HSD_GObj*) gobj);
        ip->xDD4_itemVar.samuschargeshot.xE2C = 0.0f;
        ip->xDD4_itemVar.samuschargeshot.xE30 = 0.0f;
        ip->xDD4_itemVar.samuschargeshot.xE34 = 0.0f;
        Item_8026AB54(n, gobj, arg2);
    }
    return (HSD_GObj*) n;
}

void it_802B56E4(Item_GObj* gobj, Vec3* vec, f32 farg0,
                 f32 farg1, f32 farg2)
{
    Vec3 sp2C;
    Vec3 sp20;
    Item* ip = GET_ITEM(gobj);
    itSamusChargeShot_Attributes* attr =
        ip->xC4_article_data->x4_specialAttributes;

    PAD_STACK(0X8);

    ip->xDD4_itemVar.samuschargeshot.xDD8 = farg0;
    it_80275158(gobj, attr->lifetime);
    if (farg1 < 0.0f) {
        farg1 = 0.0f;
    }
    if (farg1 > farg2) {
        farg1 = farg2;
    }
    ip->xDD4_itemVar.samuschargeshot.xDEC = (s32) farg1;
    ip->xDD4_itemVar.samuschargeshot.xDF0 = (s32) farg2;
    if ((ip->xDD4_itemVar.samuschargeshot.xE00 != NULL) &&
        (ip->owner == ip->xDD4_itemVar.samuschargeshot.xE00))
    {
        it_802B5CBC(gobj);
        HSD_MtxGetRotation(
            ftLib_80086630(ip->xDD4_itemVar.samuschargeshot.xE00,
                           (enum Fighter_Part) ip->xDC4)
                ->mtx,
            &sp2C);
        sp20.z = 0.0f;
        sp20.y = 0.0f;
        sp20.x = 0.0f;
        it_8027429C(gobj, &sp20);
        ip->xDC8_word.flags.x14 = 0;
        it_8026B3A8(gobj);
        ip->xDD4_itemVar.samuschargeshot.xDDC =
            (farg1 * ((attr->xC - attr->x8) / farg2)) + attr->x8;
        ip->xDD4_itemVar.samuschargeshot.xDF8 =
            (u32) ((farg1 * ((attr->x14 - attr->x10) / farg2)) +
                   attr->x10);
        ip->xDD4_itemVar.samuschargeshot.xDE0 = 0.0f;
        ip->xDD4_itemVar.samuschargeshot.xDE4 =
            (ip->xDD4_itemVar.samuschargeshot.xDEC *
             ((attr->x1C - attr->x18) /
             ip->xDD4_itemVar.samuschargeshot.xDF0)) +
            attr->x18;
        ip->xDD4_itemVar.samuschargeshot.xDF4 = 0;
        ip->facing_dir =
            ftLib_800865C0(ip->xDD4_itemVar.samuschargeshot.xE00);
        ip->pos = *vec;
        ip->xDD4_itemVar.samuschargeshot.xDFC = 0;
        ip->x40_vel.x =
            ip->xDD4_itemVar.samuschargeshot.xDDC *
            cosf(ip->xDD4_itemVar.samuschargeshot.xDD8);
        ip->x40_vel.y =
            ip->xDD4_itemVar.samuschargeshot.xDDC *
            sinf(ip->xDD4_itemVar.samuschargeshot.xDD8);
        ip->x40_vel.z = 0.0f;
        ip->xDD4_itemVar.samuschargeshot.xDE8 = 1;
    }
}

void it_2725_Logic108_Destroyed(Item_GObj* gobj)
{
    Item* ip;
    enum ItemKind temp_r0;

    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        efLib_DestroyAll((HSD_GObj*) gobj);
        if (ip->xDD4_itemVar.samuschargeshot.xDE8 == 0) {
            if ((ip->xDD4_itemVar.samuschargeshot.xE00 != NULL) && (ip->owner == ip->xDD4_itemVar.samuschargeshot.xE00)) {
                temp_r0 = ip->kind;
                switch (temp_r0) {
                    case It_Kind_Samus_Charge:
                        ftSs_SpecialN_801291F0(ip->xDD4_itemVar.samuschargeshot.xE00);
                        break;
                    case It_Kind_Kirby_SamusCharge:
                        ftKb_SpecialNSs_800FCD04(ip->xDD4_itemVar.samuschargeshot.xE00);
                        break;
                }
            }
            ip->xDD4_itemVar.samuschargeshot.xE00 = 0;
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
        ip->xDD4_itemVar.samuschargeshot.xDFC = 0;
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
            ip->xDD4_itemVar.samuschargeshot.xDFC = 1;
            return;
        case It_Kind_Kirby_SamusCharge:
            efSync_Spawn(0x4A1, (HSD_GObj* ) gobj, child);
            ip->xDD4_itemVar.samuschargeshot.xDFC = 1;
            return;
    }
}


bool itSamuschargeshot_UnkMotion8_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* grandchild = itGetJObjGrandchild(gobj);

    f32 temp = *(f32*) &ip->xDD4_itemVar.samuschargeshot.xDE4;
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
    ip->xDD4_itemVar.samuschargeshot.xDFC = 0.0f;

    if (ip->xDD4_itemVar.samuschargeshot.xDEC < 0) {
        ip->xDD4_itemVar.samuschargeshot.xDEC = 0;
    }
    if (ip->xDD4_itemVar.samuschargeshot.xDEC >= 8) {
        ip->xDD4_itemVar.samuschargeshot.xDEC = 7;
    }
    Item_80268E5C(gobj, ip->xDD4_itemVar.samuschargeshot.xDEC + 1, ITEM_ANIM_UPDATE);
    ip->on_accessory = it_802B5EDC;
}

/// #itSamuschargeshot_UnkMotion8_Anim

void itSamuschargeshot_UnkMotion8_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.x = ip->xDD4_itemVar.samuschargeshot.xDDC *
                    cosf(ip->xDD4_itemVar.samuschargeshot.xDD8);
    ip->x40_vel.y = ip->xDD4_itemVar.samuschargeshot.xDDC *
                    sinf(ip->xDD4_itemVar.samuschargeshot.xDD8);
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

    if ((ip->xDD4_itemVar.samuschargeshot.xDEC ==
         ip->xDD4_itemVar.samuschargeshot.xDF0) &&
        (ip->xDD4_itemVar.samuschargeshot.xDF4 == 0))
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
    ip->xDD4_itemVar.samuschargeshot.xDF4 =
        ip->xDD4_itemVar.samuschargeshot.xDF4 + 1;
    ip->xDD4_itemVar.samuschargeshot.xDF4 =
        ip->xDD4_itemVar.samuschargeshot.xDF4 % 3;
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

bool it_2725_Logic108_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 pi_over_two_x_facing_dir;

    ip->facing_dir = -ip->facing_dir;
    pi_over_two_x_facing_dir = (f32) (HALF_PI * (f64) ip->facing_dir);
    if (jobj == NULL) {
        __assert("jobj.h", 0x294U, "jobj");
    }
    if (jobj->flags & 0x20000) {
        __assert("jobj.h", 0x295U, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    }
    jobj->rotate.y = pi_over_two_x_facing_dir;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != NULL) {
            if (jobj == NULL) {
                __assert("jobj.h", 0x234U, "jobj");
            }
            {
                s32 c = 0;
                u32 flags = jobj->flags;
                if (!(flags & 0x800000) && (flags & 0x40)) {
                    c = 1;
                }
                if (c == 0) {
                    HSD_JObjSetMtxDirtySub(jobj);
                }
            }
        }
    }
    ip->xDD4_itemVar.samuschargeshot.xDD8 = (f32) ((f64) ip->xDD4_itemVar.samuschargeshot.xDD8 + PI);
    while (ip->xDD4_itemVar.samuschargeshot.xDD8 < 0.0f) {
        ip->xDD4_itemVar.samuschargeshot.xDD8 = (f32) ((f64) ip->xDD4_itemVar.samuschargeshot.xDD8 + TAU);
    }
    while (ip->xDD4_itemVar.samuschargeshot.xDD8 > TAU) {
        ip->xDD4_itemVar.samuschargeshot.xDD8 = (f32) ((f64) ip->xDD4_itemVar.samuschargeshot.xDD8 - TAU);
    }
    return 0;
}


bool itSamusChargeshot_Logic108_HitShield(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic108_ShieldBounced(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 pi_over_two_x_facing_dir;

    lbVector_Mirror(&ip->x40_vel, &ip->xC58);
    ip->xDD4_itemVar.samuschargeshot.xDD8 = atan2f(ip->x40_vel.y, ip->x40_vel.x);
    while (ip->xDD4_itemVar.samuschargeshot.xDD8 < 0.0f) {
        ip->xDD4_itemVar.samuschargeshot.xDD8 = (f32) ((f64) ip->xDD4_itemVar.samuschargeshot.xDD8 + TAU);
    }
    while (ip->xDD4_itemVar.samuschargeshot.xDD8 > TAU) {
        ip->xDD4_itemVar.samuschargeshot.xDD8 = (f32) ((f64) ip->xDD4_itemVar.samuschargeshot.xDD8 - TAU);
    }

    ip->facing_dir = (ip->x40_vel.x >= 0.0f) ? 1.0f : -1.0f;
    pi_over_two_x_facing_dir = (f32) (1.5707963267948966 * (f64) ip->facing_dir);
    if (jobj == NULL) {
        __assert("jobj.h", 0x294U, "jobj");
    }
    if (jobj->flags & 0x20000) {
        __assert("jobj.h", 0x295U, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    }
    jobj->rotate.y = pi_over_two_x_facing_dir;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != NULL) {
            if (jobj == NULL) {
                __assert("jobj.h", 0x234U, "jobj");
            }
            {
                s32 c;
                u32 flags;
                flags = jobj->flags;
                c = 0;
                if (!(flags & 0x800000) && (flags & 0x40)) {
                    c = 1;
                }
                if (c == 0) {
                    HSD_JObjSetMtxDirtySub(jobj);
                }
            }
        }
    }
    return 0;
}

void itSamusChargeshot_Logic108_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
