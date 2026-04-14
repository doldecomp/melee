#include "itmewtwoshadowball.h"

#include "placeholder.h"

#include "db/db.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftKirby/ftKb_Init.h"
#include "ft/chara/ftMewtwo/ftMt_SpecialN.h"
#include "ft/ftlib.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"
#include "MSL/trigf.h"

#include <math.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

extern s32 it_803F7880[];

void it_802C4D10(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* child = HSD_JObjGetChild(gobj->hsd_obj);
    itMewtwoShadowball_DatAttrs* attr =
        ip->xC4_article_data->x4_specialAttributes;

    if (ip->xDD4_itemVar.mewtwoshadowball.x4C > 0) {
        ip->xDD4_itemVar.mewtwoshadowball.x48++;
        if (ip->xDD4_itemVar.mewtwoshadowball.x48 >= attr->x1C[4]) {
            ip->xDD4_itemVar.mewtwoshadowball.x48 = 0;
            ip->xDD4_itemVar.mewtwoshadowball.x3C +=
                ((M_PI / 4) * (2.0f * (HSD_Randf() - 0.5f)));
            ip->xDD4_itemVar.mewtwoshadowball.x44 =
                -ip->xDD4_itemVar.mewtwoshadowball.x40 /
                (ip->xDD4_itemVar.mewtwoshadowball.x48 / 2);
            Item_8026AF0C(ip, it_803F7880[HSD_Randi(3)], 127, 64);
        }
        ip->xDD4_itemVar.mewtwoshadowball.x40 +=
            ip->xDD4_itemVar.mewtwoshadowball.x44;
        ip->xDD4_itemVar.mewtwoshadowball.x30.x = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x30.y +=
            ip->xDD4_itemVar.mewtwoshadowball.x40 *
            ip->xDD4_itemVar.mewtwoshadowball.x50 *
            sinf(ip->xDD4_itemVar.mewtwoshadowball.x3C);
        ip->xDD4_itemVar.mewtwoshadowball.x30.z +=
            ip->xDD4_itemVar.mewtwoshadowball.x40 *
            ip->xDD4_itemVar.mewtwoshadowball.x50 *
            cosf(ip->xDD4_itemVar.mewtwoshadowball.x3C);
    } else {
        ip->xDD4_itemVar.mewtwoshadowball.x30.z = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x30.y = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x30.x = 0.0f;
    }
    HSD_JObjSetTranslate(child, &ip->xDD4_itemVar.mewtwoshadowball.x30);
    ip->xDD4_itemVar.mewtwoshadowball.x4C++;
}

bool it_802C4F50(Item_GObj* gobj, CollData* cd)
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

HSD_GObj* it_802C5000(Item_GObj* parent, Vec3* pos, s32 kind, s32 bone,
                      float facing_dir)
{
    SpawnItem spawn;
    Item_GObj* item_gobj;

    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68(parent, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = parent;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        Item* ip = GET_ITEM(item_gobj);
        itMewtwoShadowball_DatAttrs* attr =
            ip->xC4_article_data->x4_specialAttributes;
        ip->xDB8_itcmd_var3 = 0;
        ip->xDB4_itcmd_var2 = 0;
        ip->xDB0_itcmd_var1 = 0;
        ip->xDAC_itcmd_var0 = 0;
        it_80275158(item_gobj, attr->x0);
        ip->xDD4_itemVar.mewtwoshadowball.x14 = 0;
        ip->xDD4_itemVar.mewtwoshadowball.x4.z = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x28 = 0;
        ip->xDD4_itemVar.mewtwoshadowball.x2C = parent;
        ip->xDD4_itemVar.mewtwoshadowball.x30.z = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x30.y = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x30.x = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x48 = attr->x1C[4];
        ip->xDD4_itemVar.mewtwoshadowball.x3C = (M_TAU * HSD_Randf());
        ip->xDD4_itemVar.mewtwoshadowball.x40 = 2.5f + (HSD_Randf() - 0.5f);
        ip->xDD4_itemVar.mewtwoshadowball.x44 =
            -ip->xDD4_itemVar.mewtwoshadowball.x40 /
            (0.5f * ip->xDD4_itemVar.mewtwoshadowball.x48);
        ip->xDD4_itemVar.mewtwoshadowball.x4C = 0;
        ip->xDD4_itemVar.mewtwoshadowball.x50 = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x54 = ftLib_800869D4(parent);
        ip->xDD4_itemVar.mewtwoshadowball.x58.z = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x58.y = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x58.x = 0.0f;
        Item_8026AB54(item_gobj, parent, bone);
    }
    return item_gobj;
}

Item_GObj* it_802C519C(Item_GObj* parent, Vec3* pos, s32 kind, s32 max_charge,
                       float facing_dir, float angle)
{
    SpawnItem spawn;
    Item_GObj* item_gobj;

    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68(parent, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = parent;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        Item* ip = GET_ITEM(item_gobj);
        itMewtwoShadowball_DatAttrs* attr =
            ip->xC4_article_data->x4_specialAttributes;
        f32 timer;

        Item_80268E5C(item_gobj, 9, ITEM_ANIM_UPDATE);
        ip->xDB8_itcmd_var3 = 0;
        ip->xDB4_itcmd_var2 = 0;
        ip->xDB0_itcmd_var1 = 0;
        ip->xDAC_itcmd_var0 = 0;
        timer = attr->x0;
        ip->xDD4_itemVar.mewtwoshadowball.x0 = (s32) timer;
        it_80275158(item_gobj, timer);
        ip->xDD4_itemVar.mewtwoshadowball.x14 = 1;
        ip->xDD4_itemVar.mewtwoshadowball.x4.z = 1.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x28 = 0;
        ip->xDD4_itemVar.mewtwoshadowball.x2C = parent;
        ip->xDD4_itemVar.mewtwoshadowball.x30.z = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x30.y = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x30.x = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x48 = attr->x1C[4];
        ip->xDD4_itemVar.mewtwoshadowball.x4.x = angle;
        ip->xDD4_itemVar.mewtwoshadowball.x3C = angle;
        {
            f32 speed = attr->x1C[8];
            ip->xDD4_itemVar.mewtwoshadowball.x4.y = speed;
            ip->xDD4_itemVar.mewtwoshadowball.x40 = speed;
        }
        ip->xDD4_itemVar.mewtwoshadowball.x44 = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x4C = 0;
        ip->xDD4_itemVar.mewtwoshadowball.x50 = 1.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x54 = ftLib_800869D4(parent);
        ip->xDD4_itemVar.mewtwoshadowball.x58.z = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x58.y = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x58.x = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x30.z = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x30.y = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x30.x = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x18 = 0;
        ip->xDD4_itemVar.mewtwoshadowball.x1C = max_charge;
        ip->xDD4_itemVar.mewtwoshadowball.x20 = 0;
        {
            f32 base = attr->x18;
            ip->xDD4_itemVar.mewtwoshadowball.x10 =
                (ip->xDD4_itemVar.mewtwoshadowball.x18 *
                 ((attr->x1C[0] - base) /
                  ip->xDD4_itemVar.mewtwoshadowball.x1C)) +
                base;
        }
        {
            f32 base = attr->x10;
            ip->xDD4_itemVar.mewtwoshadowball.x24 =
                ((ip->xDD4_itemVar.mewtwoshadowball.x18 *
                  ((attr->x14 - base) /
                   ip->xDD4_itemVar.mewtwoshadowball.x1C)) +
                 base);
        }
        ip->x40_vel.x = ip->xDD4_itemVar.mewtwoshadowball.x4.y *
                        cosf(ip->xDD4_itemVar.mewtwoshadowball.x4.x);
        ip->x40_vel.y = ip->xDD4_itemVar.mewtwoshadowball.x4.y *
                        sinf(ip->xDD4_itemVar.mewtwoshadowball.x4.x);
        ip->x40_vel.z = 0.0f;
        it_8026B3A8(item_gobj);
    }
    return item_gobj;
}

void it_802C53F0(Item_GObj* gobj, Vec3* pos, float angle, float charge,
                 float max_charge)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        itMewtwoShadowball_DatAttrs* attr =
            ip->xC4_article_data->x4_specialAttributes;
        HSD_JObj* child = HSD_JObjGetChild(gobj->hsd_obj);

        ip->xDD4_itemVar.mewtwoshadowball.x4.x = angle;
        ip->xDD4_itemVar.mewtwoshadowball.x18 = (s32) charge;
        {
            f32 base = attr->x8;
            ip->xDD4_itemVar.mewtwoshadowball.x4.y =
                (charge * ((attr->xC - base) / max_charge)) + base;
        }
        {
            f32 base = attr->x10;
            ip->xDD4_itemVar.mewtwoshadowball.x24 =
                ((charge * ((attr->x14 - base) / max_charge)) + base);
        }
        ip->xDD4_itemVar.mewtwoshadowball.x4.z = 0.0f;
        {
            f32 base = attr->x18;
            ip->xDD4_itemVar.mewtwoshadowball.x10 =
                (ip->xDD4_itemVar.mewtwoshadowball.x18 *
                 ((attr->x1C[0] - base) /
                  ip->xDD4_itemVar.mewtwoshadowball.x1C)) +
                base;
        }
        ip->xDD4_itemVar.mewtwoshadowball.x20 = 0;
        ip->facing_dir = ftLib_800865C0(ip->xDD4_itemVar.mewtwoshadowball.x2C);
        ip->pos = *pos;
        ip->xDD4_itemVar.mewtwoshadowball.x28 = 0;
        ip->x40_vel.x = ip->xDD4_itemVar.mewtwoshadowball.x4.y *
                        ip->xDD4_itemVar.mewtwoshadowball.x50 *
                        cosf(ip->xDD4_itemVar.mewtwoshadowball.x4.x);
        ip->x40_vel.y = ip->xDD4_itemVar.mewtwoshadowball.x4.y *
                        ip->xDD4_itemVar.mewtwoshadowball.x50 *
                        sinf(ip->xDD4_itemVar.mewtwoshadowball.x4.x);
        ip->x40_vel.z = 0.0f;
        ip->xDD4_itemVar.mewtwoshadowball.x14 = 1;
        ip->xDD4_itemVar.mewtwoshadowball.x4C = 0;
        {
            Vec3 scale = { 1.0f, 1.0f, 1.0f };
            HSD_JObjSetScale(child, &scale);
        }
    }
}

void it_2725_Logic101_Destroyed(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = gobj->user_data;
        efLib_DestroyAll(gobj);
        if (ip->xDD4_itemVar.mewtwoshadowball.x14 == 0) {
            if (ip->xDD4_itemVar.mewtwoshadowball.x2C != NULL &&
                ip->owner == ip->xDD4_itemVar.mewtwoshadowball.x2C)
            {
                switch (ip->kind) {
                case It_Kind_Mewtwo_ShadowBall:
                    ftMt_SpecialN_SetNULL(
                        ip->xDD4_itemVar.mewtwoshadowball.x2C);
                    break;
                case It_Kind_Kirby_MewtwoShadowBall:
                    ftKb_SpecialNMt_80107040(
                        ip->xDD4_itemVar.mewtwoshadowball.x2C);
                    break;
                }
            }
            ip->xDD4_itemVar.mewtwoshadowball.x2C = NULL;
        }
        ip->owner = NULL;
        ip->xDC8_word.flags.x13 = 0;
    }
}

void it_802C573C(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = gobj->user_data;
        efLib_DestroyAll(gobj);
        ip->xDD4_itemVar.mewtwoshadowball.x28 = 0;
        Item_8026A8EC(gobj);
    }
}

void it_2725_Logic101_PickedUp(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    PAD_STACK(0x18);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->xDD4_itemVar.mewtwoshadowball.x50 = 0.0F;
}

bool itMewtwoshadowball_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* grandchild = itGetJObjGrandchild(gobj);
    itMewtwoShadowball_DatAttrs* attr =
        ip->xC4_article_data->x4_specialAttributes;
    HSD_GObj* parent = ip->xDD4_itemVar.mewtwoshadowball.x2C;
    Vec3 scale;
    Vec3 trans;

    if (parent != NULL && ip->owner == parent) {
        switch (ip->kind) {
        case It_Kind_Mewtwo_ShadowBall:
            if (ftMt_SpecialN_CheckShadowBallRemove(parent)) {
                return true;
            }
            if (ftMt_SpecialN_CheckShadowBallCancel(
                    ip->xDD4_itemVar.mewtwoshadowball.x2C))
            {
                return true;
            }
            if (ftMt_SpecialN_GetChargeLevel(
                    ip->xDD4_itemVar.mewtwoshadowball.x2C,
                    &ip->xDD4_itemVar.mewtwoshadowball.x18,
                    &ip->xDD4_itemVar.mewtwoshadowball.x1C) == -1)
            {
                return true;
            }
            break;
        case It_Kind_Kirby_MewtwoShadowBall:
            if (ftKb_SpecialNMt_80106F9C(parent)) {
                return true;
            }
            if (ftKb_SpecialNMt_80106FEC(
                    ip->xDD4_itemVar.mewtwoshadowball.x2C))
            {
                return true;
            }
            if (ftKb_SpecialNMt_80106F44(
                    ip->xDD4_itemVar.mewtwoshadowball.x2C,
                    &ip->xDD4_itemVar.mewtwoshadowball.x18,
                    &ip->xDD4_itemVar.mewtwoshadowball.x1C) == -1)
            {
                return true;
            }
            break;
        default:
            return false;
        }
    }
    scale.x = scale.y = scale.z = (ip->xDD4_itemVar.mewtwoshadowball.x18 *
                                   ((attr->x1C[0] - attr->x18) /
                                    ip->xDD4_itemVar.mewtwoshadowball.x1C)) +
                                  attr->x18;
    HSD_JObjSetScale(grandchild, &scale);
    if (ip->xDD4_itemVar.mewtwoshadowball.x58.x == 0.0f &&
        ip->xDD4_itemVar.mewtwoshadowball.x58.y == 0.0f &&
        ip->xDD4_itemVar.mewtwoshadowball.x58.z == 0.0f)
    {
        HSD_JObjGetTranslation(grandchild,
                               &ip->xDD4_itemVar.mewtwoshadowball.x58);
    }
    trans.x = -ip->xDD4_itemVar.mewtwoshadowball.x58.x *
              ip->xDD4_itemVar.mewtwoshadowball.x54;
    trans.y = -ip->xDD4_itemVar.mewtwoshadowball.x58.y *
              ip->xDD4_itemVar.mewtwoshadowball.x54;
    trans.z = -ip->xDD4_itemVar.mewtwoshadowball.x58.z *
              ip->xDD4_itemVar.mewtwoshadowball.x54;
    HSD_JObjSetTranslate(grandchild, &trans);
    return false;
}

void itMewtwoshadowball_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itMewtwoshadowball_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802C5B18(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    itMewtwoShadowball_DatAttrs* attr =
        ip->xC4_article_data->x4_specialAttributes;
    it_80275158(gobj, attr->x0);
    efLib_DestroyAll(gobj);
    ip->xDD4_itemVar.mewtwoshadowball.x28 = 0;
    if (ip->xDD4_itemVar.mewtwoshadowball.x18 < 0) {
        ip->xDD4_itemVar.mewtwoshadowball.x18 = 0;
    }
    if (ip->xDD4_itemVar.mewtwoshadowball.x18 >=
        ip->xDD4_itemVar.mewtwoshadowball.x1C)
    {
        ip->xDD4_itemVar.mewtwoshadowball.x18 =
            ip->xDD4_itemVar.mewtwoshadowball.x1C;
    }
    Item_80268E5C(gobj, ip->xDD4_itemVar.mewtwoshadowball.x18 + 1,
                  ITEM_ANIM_UPDATE);
    ip->on_accessory = fn_802C5E18;
    ip->xDD4_itemVar.mewtwoshadowball.x50 =
        0.5F * ((f32) ip->xDD4_itemVar.mewtwoshadowball.x18 /
                ip->xDD4_itemVar.mewtwoshadowball.x1C) +
        0.5F;
    PAD_STACK(8);
}

bool itMewtwoshadowball_UnkMotion8_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    HSD_JObj* jobj = itGetJObjGrandchild(gobj);
    Vec3 scale;
    scale.x = scale.y = scale.z = ip->xDD4_itemVar.mewtwoshadowball.x10;
    HSD_JObjSetScale(jobj, &scale);
    return it_80273130(gobj);
}

void itMewtwoshadowball_UnkMotion8_Phys(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    if (ip->xDD4_itemVar.mewtwoshadowball.x4C > 0) {
        ip->x40_vel.x = ip->xDD4_itemVar.mewtwoshadowball.x4.y *
                        cosf(ip->xDD4_itemVar.mewtwoshadowball.x4.x);
        ip->x40_vel.y = ip->xDD4_itemVar.mewtwoshadowball.x4.y *
                        sinf(ip->xDD4_itemVar.mewtwoshadowball.x4.x);
    }
    it_802C4D10(gobj);
}

bool itMewtwoshadowball_UnkMotion8_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (it_802C4F50(gobj, &ip->x378_itemColl)) {
        it_802C5E5C(gobj);
    }
    return false;
}

bool itMewtwoshadowball_UnkMotion9_Anim(Item_GObj* gobj)
{
    return it_80273130(gobj);
}

void itMewtwoshadowball_UnkMotion9_Phys(Item_GObj* gobj) {}

bool itMewtwoshadowball_UnkMotion9_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (it_802C4F50(gobj, &ip->x378_itemColl)) {
        it_802C5E5C(gobj);
    }
    return false;
}

void fn_802C5E18(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.mewtwoshadowball.x20++;
    ip->xDD4_itemVar.mewtwoshadowball.x20 =
        ip->xDD4_itemVar.mewtwoshadowball.x20 % 3;
}

void it_802C5E5C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    itMewtwoShadowball_DatAttrs* attr =
        ip->xC4_article_data->x4_specialAttributes;
    Vec3 pos;

    HSD_JObjSetFlagsAll(gobj->hsd_obj, JOBJ_HIDDEN);
    it_80275158(gobj, attr->x1C[3]);
    efLib_DestroyAll(gobj);
    ip->xDD4_itemVar.mewtwoshadowball.x28 = 0;
    if (ip->xDD4_itemVar.mewtwoshadowball.x18 < 0) {
        ip->xDD4_itemVar.mewtwoshadowball.x18 = 0;
    }
    if (ip->xDD4_itemVar.mewtwoshadowball.x18 >=
        ip->xDD4_itemVar.mewtwoshadowball.x1C)
    {
        ip->xDD4_itemVar.mewtwoshadowball.x18 =
            ip->xDD4_itemVar.mewtwoshadowball.x1C;
    }
    Item_80268E5C(gobj, ip->xDD4_itemVar.mewtwoshadowball.x18 + 0xA,
                  ITEM_ANIM_UPDATE);
    ip->on_accessory = NULL;
    ip->xDD4_itemVar.mewtwoshadowball.x64 =
        ip->x5D4_hitboxes[0].hit.scale * attr->x1C[2];
    lb_8000B1CC(HSD_JObjGetChild(HSD_JObjGetChild(jobj)), NULL, &pos);
    efSync_Spawn(0x40E, gobj, &pos);
    Item_8026AE84(ip, 0x74, 127, 64);
}

bool itMewtwoshadowball_UnkMotion17_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    u8 _pad[8];
    Vec3 scale;
    HSD_JObj* grandchild = itGetJObjGrandchild(gobj);

    scale.x = scale.y = scale.z = ip->xDD4_itemVar.mewtwoshadowball.x10;
    HSD_JObjSetScale(grandchild, &scale);
    if (ip->x5D4_hitboxes[0].hit.state != HitCapsule_Disabled) {
        ip->x5D4_hitboxes[0].hit.scale = ip->xDD4_itemVar.mewtwoshadowball.x64;
    }
    return it_80273130(gobj);
}

void itMewtwoshadowball_UnkMotion17_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

bool itMewtwoshadowball_UnkMotion17_Coll(Item_GObj* gobj)
{
    return false;
}

bool itMewtwoShadowball_Logic101_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool itMewtwoShadowball_Logic101_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itMewtwoShadowball_Logic101_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic101_Reflected(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ip->xDD4_itemVar.mewtwoshadowball.x4.x += M_PI;
    while (ip->xDD4_itemVar.mewtwoshadowball.x4.x < 0.0f) {
        ip->xDD4_itemVar.mewtwoshadowball.x4.x += M_TAU;
    }
    while (ip->xDD4_itemVar.mewtwoshadowball.x4.x > M_TAU) {
        ip->xDD4_itemVar.mewtwoshadowball.x4.x -= M_TAU;
    }
    return false;
}

bool itMewtwoShadowball_Logic101_HitShield(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic101_ShieldBounced(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    PAD_STACK(8);
    lbVector_Mirror(&ip->x40_vel, &ip->xC58);
    ip->xDD4_itemVar.mewtwoshadowball.x4.x =
        atan2f(ip->x40_vel.y, ip->x40_vel.x);
    while (ip->xDD4_itemVar.mewtwoshadowball.x4.x < 0.0f) {
        ip->xDD4_itemVar.mewtwoshadowball.x4.x += M_TAU;
    }
    while (ip->xDD4_itemVar.mewtwoshadowball.x4.x > M_TAU) {
        ip->xDD4_itemVar.mewtwoshadowball.x4.x -= M_TAU;
    }
    return false;
}

void itMewtwoShadowball_Logic101_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
