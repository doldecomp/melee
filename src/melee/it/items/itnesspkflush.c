#include "itnesspkflush.h"

#include <placeholder.h>
#include <platform.h>

#include "db/db.h"
#include "ft/chara/ftKirby/ftKb_Init.h"
#include "ft/chara/ftNess/ftNs_SpecialN.h"
#include "ft/ftlib.h"

#include "ft/chara/ftKirby/ftKb_Init.h"
#include "ft/chara/ftNess/ftNs_SpecialN.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itnesspkflushexplode.h"
#include "MSL/trigf.h"

#include <math.h>
#include <baselib/jobj.h>

/* 2AB29C */ static bool itNesspkflush_UnkMotion1_Coll(Item_GObj* gobj);
/* 2AB2A4 */ static bool itNesspkflush_UnkMotion2_Coll(Item_GObj* gobj);

static inline void itNesspkflush_SetScale(HSD_JObj* jobj, Item* ip,
                                          itFlashAttributes* attr)
{
    Vec3 scale;
    scale.x = scale.y = scale.z = (ip->xDD4_itemVar.pkflush.xDD8_PKFlash *
                                   ((attr->xC_FLASH_GRAPHIC_SIZE_GROWTH_MUL -
                                     attr->x8_FLASH_GRAPHIC_SIZE_INIT_MUL) /
                                    attr->x4_FLASH_HITBOX_SIZE_MUL)) +
                                  attr->x8_FLASH_GRAPHIC_SIZE_INIT_MUL;
    HSD_JObjSetScale(jobj, &scale);
}

Fighter_GObj* it_802AA7E4(Item_GObj* gobj)
{
    return GET_ITEM(gobj)->owner;
}

bool it_802AA7F0(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    if (it->msid == 0x2) {
        return 1;
    }
    return 0;
}

bool it_802AA810(Item_GObj* gobj, CollData* cd)
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

HSD_GObj* it_802AA8C0(Item_GObj* gobj, Vec3* pos, ItemKind kind,
                      f32 facing_dir)
{
    SpawnItem spawn;
    Item_GObj* flash;
    PAD_STACK(4);

    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0F;
    it_8026BB68(gobj, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
    spawn.x0_parent_gobj = gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;

    flash = Item_80268B18(&spawn);
    if (flash != NULL) {
        Item* ip = GET_ITEM(flash);
        itFlashAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
        ip->xDB8_itcmd_var3 = 0;
        ip->xDB4_itcmd_var2 = 0;
        ip->xDB0_itcmd_var1 = 0;
        ip->xDAC_itcmd_var0 = 0;
        it_80275158(flash, attr->x0_FLASH_LIFETIMER);
        ip->xDD4_itemVar.pkflush.xDD8_PKFlash = 0.0F;
        ip->xDD4_itemVar.pkflush.xDDC_PKFlash = 0;
        ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner = gobj;
        ip->xDD4_itemVar.pkflush.xDE4_PKFlash = 0;
        it_802AAA80(flash);
    }
    return flash;
}

void it_2725_Logic102_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802725D4(gobj);

    if (ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner != NULL) {
        if (ip->owner == ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner) {
            switch (ip->kind) {
            case It_Kind_Ness_PKFlush:
                ftNs_SpecialN_SetNULL(
                    ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner);
                break;
            case It_Kind_Kirby_NessPKFlush:
                ftKb_SpecialNNs_800FECBC(
                    ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner);
                break;
            }
        }
        ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner = NULL;
    }
    ip->xDC8_word.flags.x13 = 0;
}

void it_802AAA50(Item_GObj* gobj)
{
    Item* ip;

    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        if (ip != NULL) {
            ip->owner = NULL;
            ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner = NULL;
            ip->xDC8_word.flags.x13 = 0;
        }
    }
}

void it_802AAA80(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFlashAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    f32 angle;
    PAD_STACK(8);

    it_8026B3A8(gobj);
    ip->xDC8_word.flags.x13 = 0;
    it_80272940(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_80275158(gobj, attr->x0_FLASH_LIFETIMER);
    ip->xDD4_itemVar.pkflush.xDD8_PKFlash = 0.0f;
    ip->xDD4_itemVar.pkflush.xDDC_PKFlash = 0;
    angle =
        (0.017453292f * attr->x10_FLASH_UNK1 * ip->facing_dir) + (f32) M_PI_2;
    ip->x40_vel.x = -attr->x14_FLASH_PEAK_RISE_HEIGHT * cosf(angle);
    ip->x40_vel.y = attr->x14_FLASH_PEAK_RISE_HEIGHT * sinf(angle);
    ip->x40_vel.z = 0.0f;
    db_80225DD8(gobj, ip->owner);
}

bool itNesspkflush_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFlashAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    bool holding;

    if (it_80272C6C(gobj) == false) {
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    }

    if (ip->xDD4_itemVar.pkflush.xDDC_PKFlash == 0) {
        ip->xDD4_itemVar.pkflush.xDD8_PKFlash += 1.0f;
        if (ip->xDD4_itemVar.pkflush.xDD8_PKFlash >=
            attr->x4_FLASH_HITBOX_SIZE_MUL)
        {
            ip->xDD4_itemVar.pkflush.xDD8_PKFlash =
                attr->x4_FLASH_HITBOX_SIZE_MUL;
        }

        if (ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner != NULL &&
            ip->owner == ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner)
        {
            switch (ip->kind) {
            case It_Kind_Ness_PKFlush:
                holding = ftNs_SpecialN_CheckSpecialNHold(
                    ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner);
                break;
            case It_Kind_Kirby_NessPKFlush:
                holding = ftKb_SpecialNNs_800FEC78(
                    ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner);
                break;
            }
            if (holding != true) {
                Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
                ip->xD44_lifeTimer = attr->x28_FLASH_EXPLOSION_DELAY;
                ip->xDAC_itcmd_var0 = 0;
            }
        }
    }

    if (it_80273130(gobj) == true) {
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        ip->xD44_lifeTimer = attr->x28_FLASH_EXPLOSION_DELAY;
        ip->xDAC_itcmd_var0 = 0;
    }

    itNesspkflush_SetScale(jobj, ip, attr);
    return false;
}

bool itNesspkflush_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    itFlashAttributes* attr = ip->xC4_article_data->x4_specialAttributes;

    ip->xDAC_itcmd_var0++;

    if (ip->xDD4_itemVar.pkflush.xDDC_PKFlash == 0) {
        if (ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner != NULL) {
            Item_GObj* owner = ip->owner;
            if ((owner == ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner) &&
                (ip->xDAC_itcmd_var0 >=
                 ((s32) attr->x28_FLASH_EXPLOSION_DELAY) - 2))
            {
                switch (ip->kind) {
                case It_Kind_Ness_PKFlush:
                    it_802AF940(owner, gobj, &ip->pos,
                                It_Kind_Ness_PKFlush_Explode, ip->facing_dir,
                                ip->xDD4_itemVar.pkflush.xDD8_PKFlash);
                    break;
                case It_Kind_Kirby_NessPKFlush:
                    it_802AF940(owner, gobj, &ip->pos,
                                It_Kind_Kirby_NessPKFlush_Explode,
                                ip->facing_dir,
                                ip->xDD4_itemVar.pkflush.xDD8_PKFlash);
                    break;
                }
                return true;
            }
        }
    }

    itNesspkflush_SetScale(jobj, ip, attr);
    return it_80273130(gobj);
}

bool itNesspkflush_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    itFlashAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    itNesspkflush_SetScale(jobj, ip, attr);
    return it_80273130(gobj);
}

void itNesspkflush_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFlashAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);

    if (ip->xDD4_itemVar.pkflush.xDDC_PKFlash == 0) {
        if (ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner != NULL &&
            ip->owner == ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner)
        {
            bool holding;
            switch (ip->kind) {
            case It_Kind_Ness_PKFlush:
                holding = ftNs_SpecialN_CheckSpecialNHold(
                    ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner);
                break;
            case It_Kind_Kirby_NessPKFlush:
                holding = ftKb_SpecialNNs_800FEC78(
                    ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner);
                break;
            }
            if (holding == true) {
                f32 stick_y;
                f32 stick_x;
                ftLib_800865D8(ip->xDD4_itemVar.pkflush.xDE0_PKFlash_Owner,
                               &stick_x, &stick_y);
                if (ABS(stick_x) > 0.2f) {
                    ip->x40_vel.x += stick_x * attr->x18_FLASH_CONTROL;
                    if (ABS(ip->x40_vel.x) > attr->x20_FLASH_UNK2) {
                        ip->x40_vel.x = (ip->x40_vel.x > 0.0f)
                                            ? attr->x20_FLASH_UNK2
                                            : -attr->x20_FLASH_UNK2;
                    }
                }
            }
        }
    }

    ip->x40_vel.y -= attr->x1C_FLASH_GRAVITY;
    if (ip->x40_vel.y < -attr->x24_FLASH_UNK3) {
        ip->x40_vel.y = -attr->x24_FLASH_UNK3;
    }
    ip->x40_vel.z = 0.0f;
}

void itNesspkflush_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

void itNesspkflush_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

bool itNesspkflush_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFlashAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = GET_JOBJ(gobj);

    if (it_802AA810(gobj, &ip->x378_itemColl) != 0) {
        Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
        ip->xD44_lifeTimer = attr->x28_FLASH_EXPLOSION_DELAY;
        Item_8026B074(ip);
        Item_8026AE84(ip, 0x86, 0x7F, 0x40);
    }

    itNesspkflush_SetScale(jobj, ip, attr);
    return false;
}

bool itNesspkflush_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

bool itNesspkflush_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

bool itNessPKFlush_Logic102_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    ip->xDD4_itemVar.pkflush.xDDC_PKFlash = 1;
    ip->facing_dir = -(ip->facing_dir);
    HSD_JObjSetRotationY(jobj, M_PI_2 * ip->facing_dir);
    ip->x40_vel.x = -(ip->x40_vel.x);
    ip->x40_vel.y = -(ip->x40_vel.y);
    ip->x40_vel.z = 0.0f;
    return false;
}

bool itNessPKFlush_Logic102_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itNessPKFlush_Logic102_Absorbed(Item_GObj* arg0)
{
    return true;
}

void itNessPKFlush_Logic102_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
