#include "itzeldadinfire.h"

#include "baselib/forward.h"

#include "baselib/jobj.h"
#include "db/db.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftZelda/ftZd_SpecialLw.h"
#include "ft/ftlib.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itzeldadinfireexplode.h"

#include <MSL/math.h>

/* 2C4434 */ static bool itZeldadinfire_UnkMotion1_Coll(Item_GObj* gobj);

ItemStateTable ItemStateTable_ZeldaDinFire[] = {
    { 0, itZeldadinfire_UnkMotion0_Anim, itZeldadinfire_UnkMotion0_Phys,
      itZeldadinfire_UnkMotion0_Coll },
    { 1, itZeldadinfire_UnkMotion1_Anim, itZeldadinfire_UnkMotion1_Phys,
      itZeldadinfire_UnkMotion1_Coll },
};

typedef struct {
    float x0;
    float x4;
    float x8;
    float xC;
    float x10;
    float x14;
    float x18;
    float x1C;
    float x20;
    float x24;
    float x28;
    float x2C;
} ItZeldaDinFire_ItemVars;

Fighter_GObj* it_802C3AF0(Item_GObj* gobj)
{
    return GET_ITEM(gobj)->owner;
}

bool it_802C3AFC(Item_GObj* gobj, CollData* cd)
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

Item_GObj* it_802C3BAC(Item_GObj* gobj, Vec* vec, float facing_dir, float arg3)
{
    SpawnItem si;
    Item_GObj* n;
    si.kind = It_Kind_Zelda_DinFire;
    si.prev_pos = *vec;
    si.prev_pos.z = 0.0f;
    it_8026BB68(gobj, &si.pos);
    si.facing_dir = facing_dir;
    si.x3C_damage = 0;
    si.vel.x = si.vel.y = si.vel.z = 0.0f;
    si.x0_parent_gobj = gobj;
    si.x4_parent_gobj2 = si.x0_parent_gobj;
    si.x44_flag.b0 = 1;
    si.x40 = 0;
    n = Item_80268B18(&si);
    if (n != NULL) {
        Item* i = GET_ITEM(n);
        ItZeldaDinFire_ItemVars* attrs =
            i->xC4_article_data->x4_specialAttributes;
        i->xDAC_itcmd_var0 = i->xDB0_itcmd_var1 = i->xDB4_itcmd_var2 =
            i->xDB8_itcmd_var3 = 0;
        it_80275158(n, attrs->x0);
        i->xDD4_itemVar.zeldadinfire.xDD8 = 0.0f;
        i->xDD4_itemVar.zeldadinfire.xDDC = 0;
        i->xDD4_itemVar.zeldadinfire.xDE0 = gobj;
        i->xDD4_itemVar.zeldadinfire.xDE4 = 0;
        it_802C3D74(n);
    }
    return n;
}

void it_2725_Logic65_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802725D4(gobj);
    if (ip->xDD4_itemVar.zeldadinfire.xDE0) {
        if (ip->owner == ip->xDD4_itemVar.zeldadinfire.xDE0) {
            ftZd_SpecialLw_8013B5C4(ip->xDD4_itemVar.zeldadinfire.xDE0);
        }
        ip->xDD4_itemVar.zeldadinfire.xDE0 = NULL;
    }
    if (ip->xDD4_itemVar.zeldadinfire.xDF4) {
        efLib_DestroyAll(gobj);
        ip->xDD4_itemVar.zeldadinfire.xDF4 = 0;
    }
    ip->xDC8_word.flags.x13 = 0;
}

void it_802C3D44(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        if (ip != NULL) {
            ip->owner = NULL;
            ip->xDD4_itemVar.zeldadinfire.xDE0 = 0;
            ip->xDC8_word.flags.x13 = 0;
        }
    }
}

void it_802C3D74(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItZeldaDinFire_ItemVars* attrs;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    double rot;
    attrs = ip->xC4_article_data->x4_specialAttributes;
    it_8026B3A8(gobj);
    ip->xDC8_word.flags.x13 = 0;
    it_80272940(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_80275158(gobj, attrs->x0);
    ip->xDD4_itemVar.zeldadinfire.xDD8 = 0.0f;
    ip->xDD4_itemVar.zeldadinfire.xDDC = 0;
    ip->xDD4_itemVar.zeldadinfire.xDE8 = attrs->x10 * ip->facing_dir;
    if (1.0f == ip->facing_dir) {
        rot = 0.0;
    } else {
        rot = M_PI;
    }
    ip->xDD4_itemVar.zeldadinfire.xDEC = rot;
    ip->xDD4_itemVar.zeldadinfire.xDF0 = attrs->x14;
    efSync_Spawn(1272, gobj, jobj);
    ip->xDD4_itemVar.zeldadinfire.xDF4 = 1;
    ip->x40_vel.x = ip->xDD4_itemVar.zeldadinfire.xDF0 *
                    cosf(ip->xDD4_itemVar.zeldadinfire.xDEC +
                         ip->xDD4_itemVar.zeldadinfire.xDE8);
    ip->x40_vel.y = ip->xDD4_itemVar.zeldadinfire.xDF0 *
                    sinf(ip->xDD4_itemVar.zeldadinfire.xDEC +
                         ip->xDD4_itemVar.zeldadinfire.xDE8);
    ip->x40_vel.z = 0.0f;
    db_80225DD8(gobj, ip->owner);
}

static inline void itZeldadinfire_UnkMotion0_Anim_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItZeldaDinFire_ItemVars* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if (ip->xDD4_itemVar.zeldadinfire.xDF4) {
        efLib_DestroyAll(gobj);
        ip->xDD4_itemVar.zeldadinfire.xDF4 = 0;
    }
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    efSync_Spawn(1273, gobj, jobj);
    ip->xDD4_itemVar.zeldadinfire.xDF4 = 1;
    ip->xD44_lifeTimer = attrs->x2C;
}

bool itZeldadinfire_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    ItZeldaDinFire_ItemVars* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    Vec v;
    if (ip->xDD4_itemVar.zeldadinfire.xDDC == 0) {
        ip->xDD4_itemVar.zeldadinfire.xDD8 += 1.0f;
        if (ip->xDD4_itemVar.zeldadinfire.xDD8 >= attrs->x4) {
            ip->xDD4_itemVar.zeldadinfire.xDD8 = attrs->x4;
        }
        if (ip->xDD4_itemVar.zeldadinfire.xDE0 != 0 &&
            ip->owner == ip->xDD4_itemVar.zeldadinfire.xDE0 &&
            ftZd_SpecialLw_8013B574(ip->xDD4_itemVar.zeldadinfire.xDE0) == 1)
        {
            itZeldadinfire_UnkMotion0_Anim_inline(gobj);
        }
    }
    v.x = v.y = v.z = ip->xDD4_itemVar.zeldadinfire.xDD8 *
                          ((attrs->xC - attrs->x8) / attrs->x4) +
                      attrs->x8;
    HSD_JObjSetScale(jobj, &v);
    if (it_80273130(gobj) == 1) {
        itZeldadinfire_UnkMotion0_Anim_inline(gobj);
    }
    return false;
}

bool itZeldadinfire_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    ItZeldaDinFire_ItemVars* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    Vec v;
    v.x = v.y = v.z = ip->xDD4_itemVar.zeldadinfire.xDD8 *
                          ((attrs->xC - attrs->x8) / attrs->x4) +
                      attrs->x8;
    HSD_JObjSetScale(jobj, &v);
    if (it_80273130(gobj) == 1) {
        if (ip->xDD4_itemVar.zeldadinfire.xDF4 != 0) {
            efLib_DestroyAll(gobj);
            ip->xDD4_itemVar.zeldadinfire.xDF4 = 0;
        }
        if (ip->xDD4_itemVar.zeldadinfire.xDE0 != 0 &&
            ip->xDD4_itemVar.zeldadinfire.xDE0 == ip->owner)
        {
            it_802C4580(ip->owner, gobj, &ip->pos, ip->facing_dir,
                        ip->xDD4_itemVar.zeldadinfire.xDD8);
            ftZd_SpecialLw_8013B5C4(ip->xDD4_itemVar.zeldadinfire.xDE0);
        }
        return true;
    }
    return false;
}

void itZeldadinfire_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItZeldaDinFire_ItemVars* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    int pad;
    float f1;
    float f2;
    if (ip->xDD4_itemVar.zeldadinfire.xDDC == 0) {
        if (ip->xDD4_itemVar.zeldadinfire.xDE0 != 0 &&
            ip->owner == ip->xDD4_itemVar.zeldadinfire.xDE0 &&
            ftZd_SpecialLw_8013B540(ip->xDD4_itemVar.zeldadinfire.xDE0) == 1)
        {
            float *f3, *f4;
            f3 = &f1;
            f4 = &f2;
            ftLib_800865D8(ip->xDD4_itemVar.zeldadinfire.xDE0, f4, f3);
            if (ABS(f1) > attrs->x20) {
                ip->xDD4_itemVar.zeldadinfire.xDE8 =
                    ip->facing_dir * (attrs->x24 * f1) +
                    ip->xDD4_itemVar.zeldadinfire.xDE8;
                if (ABS(ip->xDD4_itemVar.zeldadinfire.xDE8) > attrs->x28) {
                    ip->xDD4_itemVar.zeldadinfire.xDE8 =
                        ip->xDD4_itemVar.zeldadinfire.xDE8 > 0.0f
                            ? attrs->x28
                            : -(attrs->x28);
                }
            }
            ip->xDD4_itemVar.zeldadinfire.xDF0 += attrs->x18;
            if (ip->xDD4_itemVar.zeldadinfire.xDF0 > attrs->x1C) {
                ip->xDD4_itemVar.zeldadinfire.xDF0 = attrs->x1C;
            }
            ip->x40_vel.x = ip->xDD4_itemVar.zeldadinfire.xDF0 *
                            cosf(ip->xDD4_itemVar.zeldadinfire.xDEC +
                                 ip->xDD4_itemVar.zeldadinfire.xDE8);
            ip->x40_vel.y = ip->xDD4_itemVar.zeldadinfire.xDF0 *
                            sinf(ip->xDD4_itemVar.zeldadinfire.xDEC +
                                 ip->xDD4_itemVar.zeldadinfire.xDE8);
            ip->x40_vel.z = 0.0f;
        }
    }
}

void itZeldadinfire_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

bool itZeldadinfire_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (it_802C3AFC(gobj, &ip->x378_itemColl)) {
        itZeldadinfire_UnkMotion0_Anim_inline(gobj);
    }
    return false;
}

bool itZeldadinfire_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

bool it_2725_Logic65_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    ip->xDD4_itemVar.zeldadinfire.xDDC = 1;
    ip->facing_dir = -(ip->facing_dir);
    HSD_JObjSetRotationY(jobj, M_PI_2 * ip->facing_dir);
    ip->x40_vel.x = -(ip->x40_vel.x);
    ip->x40_vel.y = -(ip->x40_vel.y);
    ip->x40_vel.z = 0.0f;
    return false;
}

bool it_2725_Logic65_Clanked(Item_GObj* gobj)
{
    return true;
}

bool it_2725_Logic65_Absorbed(Item_GObj* gobj)
{
    return true;
}

void it_2725_Logic65_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
