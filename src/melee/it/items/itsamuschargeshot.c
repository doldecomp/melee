#include "itsamuschargeshot.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "baselib/gobj.h"
#include "baselib/mtx.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftKirby/ftKb_Init.h"
#include "ft/chara/ftSamus/ftSs_SpecialN.h"
#include "ft/ftlib.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lbvector.h"

#include <math.h>
#include <trigf.h>

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

HSD_GObj* it_802B55C8(Fighter_GObj* gobj, Vec3* pos, enum Fighter_Part arg2,
                      s32 arg3, f32 facing_dir)
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

void it_802B56E4(Item_GObj* gobj, Vec3* vec, f32 farg0, f32 farg1, f32 farg2)
{
    Item* ip = GET_ITEM(gobj);
    itSamusChargeShot_Attributes* attr =
        ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);

    ip->xDD4_itemVar.samuschargeshot.xDD8 = farg0;
    it_80275158(gobj, attr->lifetime);
    if (farg1 < 0.0f) {
        farg1 = 0.0f;
    }
    if (farg1 > farg2) {
        farg1 = farg2;
    }
    ip->xDD4_itemVar.samuschargeshot.xDEC = farg1;
    ip->xDD4_itemVar.samuschargeshot.xDF0 = farg2;
    {
        if (ip->xDD4_itemVar.samuschargeshot.xE00 != NULL &&
            ip->owner == ip->xDD4_itemVar.samuschargeshot.xE00)
        {
            it_802B5CBC(gobj);
            {
                Vec3 sp2C;
                Vec3 sp20;

                HSD_MtxGetRotation(
                    ftLib_80086630(ip->xDD4_itemVar.samuschargeshot.xE00,
                                   ip->xDC4)
                        ->mtx,
                    &sp2C);
                sp20.x = sp20.y = sp20.z = 0.0f;
                it_8027429C(gobj, &sp20);
            }
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
            ip->x40_vel.x = ip->xDD4_itemVar.samuschargeshot.xDDC *
                            cosf(ip->xDD4_itemVar.samuschargeshot.xDD8);
            ip->x40_vel.y = ip->xDD4_itemVar.samuschargeshot.xDDC *
                            sinf(ip->xDD4_itemVar.samuschargeshot.xDD8);
            ip->x40_vel.z = 0.0f;
            ip->xDD4_itemVar.samuschargeshot.xDE8 = 1;
        }
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
            if ((ip->xDD4_itemVar.samuschargeshot.xE00 != NULL) &&
                (ip->owner == ip->xDD4_itemVar.samuschargeshot.xE00))
            {
                temp_r0 = ip->kind;
                switch (temp_r0) {
                case It_Kind_Samus_Charge:
                    ftSs_SpecialN_801291F0(
                        ip->xDD4_itemVar.samuschargeshot.xE00);
                    break;
                case It_Kind_Kirby_SamusCharge:
                    ftKb_SpecialNSs_800FCD04(
                        ip->xDD4_itemVar.samuschargeshot.xE00);
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
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* grandchild = itGetJObjGrandchild(gobj);

    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    switch (ip->kind) {
    case It_Kind_Samus_Charge:
        efSync_Spawn(0x47F, (HSD_GObj*) gobj, grandchild);
        ip->xDD4_itemVar.samuschargeshot.xDFC = 1;
        return;
    case It_Kind_Kirby_SamusCharge:
        efSync_Spawn(0x4A1, (HSD_GObj*) gobj, grandchild);
        ip->xDD4_itemVar.samuschargeshot.xDFC = 1;
        return;
    }
}

bool itSamuschargeshot_UnkMotion8_Anim(Item_GObj* gobj)
{
    Vec3 scale;
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* grandchild = itGetJObjGrandchild(gobj);

    scale.x = scale.y = scale.z = ip->xDD4_itemVar.samuschargeshot.xDE4;

    HSD_JObjSetScale(grandchild, &scale);
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
    itSamusChargeShot_Attributes* attr =
        ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(4);

    it_80275158(gobj, attr->lifetime);
    efLib_DestroyAll(gobj);
    ip->xDD4_itemVar.samuschargeshot.xDFC = 0.0f;

    if (ip->xDD4_itemVar.samuschargeshot.xDEC < 0) {
        ip->xDD4_itemVar.samuschargeshot.xDEC = 0;
    }
    if (ip->xDD4_itemVar.samuschargeshot.xDEC >= 8) {
        ip->xDD4_itemVar.samuschargeshot.xDEC = 7;
    }
    Item_80268E5C(gobj, ip->xDD4_itemVar.samuschargeshot.xDEC + 1,
                  ITEM_ANIM_UPDATE);
    ip->on_accessory = it_802B5EDC;
}

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
    pi_over_two_x_facing_dir = (f32) (M_PI_2 * (f64) ip->facing_dir);
    HSD_JObjSetRotationY(jobj, pi_over_two_x_facing_dir);

    ip->xDD4_itemVar.samuschargeshot.xDD8 += M_PI;
    while (ip->xDD4_itemVar.samuschargeshot.xDD8 < 0.0f) {
        ip->xDD4_itemVar.samuschargeshot.xDD8 += M_TAU;
    }
    while (ip->xDD4_itemVar.samuschargeshot.xDD8 > M_TAU) {
        ip->xDD4_itemVar.samuschargeshot.xDD8 -= M_TAU;
    }
    return false;
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
    ip->xDD4_itemVar.samuschargeshot.xDD8 =
        atan2f(ip->x40_vel.y, ip->x40_vel.x);
    while (ip->xDD4_itemVar.samuschargeshot.xDD8 < 0.0f) {
        ip->xDD4_itemVar.samuschargeshot.xDD8 += M_TAU;
    }
    while (ip->xDD4_itemVar.samuschargeshot.xDD8 > M_TAU) {
        ip->xDD4_itemVar.samuschargeshot.xDD8 -= M_TAU;
    }

    ip->facing_dir = (ip->x40_vel.x >= 0.0f) ? 1.0f : -1.0f;
    pi_over_two_x_facing_dir = (f32) (M_PI_2 * (f64) ip->facing_dir);
    HSD_JObjSetRotationY(jobj, pi_over_two_x_facing_dir);
    return false;
}

void itSamusChargeshot_Logic108_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
