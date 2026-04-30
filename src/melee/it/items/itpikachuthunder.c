#include "itpikachuthunder.h"

#include <placeholder.h>

#include "db/db.h"
#include "ft/chara/ftPikachu/ftPk_SpecialLw.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCharItems.h"
#include "it/item.h"

#include "it/items/forward.h"

#include "it/types.h"
#include "MSL/math.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

ItemStateTable it_803F70C8[] = {
    {
        -1,
        itPikachuthunder_UnkMotion0_Anim,
        NULL,
        NULL,
    },
    {
        0,
        itPikachuthunder_UnkMotion1_Anim,
        NULL,
        itPikachuthunder_UnkMotion1_Coll,
    },
    {
        0,
        itPikachuthunder_UnkMotion2_Anim,
        NULL,
        NULL,
    },
};

s32 it_802B1DEC(Item_GObj* arg0)
{
    return GET_ITEM(arg0)->xDD4_itemVar.pikachuthunder.x4;
}

Item_GObj* it_802B1DF8(Item_GObj* owner, Vec3* pos, Vec3* vel, s32 count,
                       s32 delay, s32 kind)
{
    int i;
    Item* ip;
    itPikachuthunderAttributes* attrs;
    SpawnItem spawn;
    u8 _pad[4];
    u32 x40 = Item_8026AE60();
    s32 cur_delay = 0;
    Item_GObj* prev = NULL;
    Item_GObj* first;

    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    spawn.pos = spawn.prev_pos;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.facing_dir = -1.0f;
    spawn.x3C_damage = 0;
    spawn.x0_parent_gobj = owner;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = x40;

    for (i = 0; i < count; i++) {
        Item_GObj* item_gobj = Item_80268B18(&spawn);
        if (i == 0) {
            first = item_gobj;
        }
        if (item_gobj != NULL) {
            ip = GET_ITEM(item_gobj);
            attrs = ip->xC4_article_data->x4_specialAttributes;
            if (prev != NULL) {
                GET_ITEM(prev)->xDD4_itemVar.pikachuthunder.x34 = item_gobj;
            }
            it_802756D0(item_gobj);
            ip->xDC8_word.flags.xD = 0;
            db_80225DD8(item_gobj, owner);
            it_802B2080(item_gobj);
            ip->xDCC_flag.b3 = 0;
            ip->xDCC_flag.b4567 = 14;
            ip->xDD4_itemVar.pikachuthunder.x0 = i;
            ip->xDD4_itemVar.pikachuthunder.x38 = owner;
            ip->xDD4_itemVar.pikachuthunder.x8 = cur_delay;
            ip->xDD4_itemVar.pikachuthunder.x14 = ABS(attrs->x4 / vel->y);
            ip->xDD4_itemVar.pikachuthunder.x1C = *vel;
            ip->xDD4_itemVar.pikachuthunder.x34 = NULL;
            ip->xDD4_itemVar.pikachuthunder.x4 = 0;
            ip->xDD4_itemVar.pikachuthunder.xC = attrs->x4;
            ip->xDD4_itemVar.pikachuthunder.x18 = 1.0f;
        }
        prev = item_gobj;
        cur_delay += delay;
    }
    return first;
}

void it_802B1FC8(Item_GObj* gobj)
{
    it_802B22B8(gobj);
}

void it_802B1FE8(Item_GObj* gobj, Vec3* pos)
{
    Item* ip = GET_ITEM(gobj);
    itPikachuthunderAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    f32 scale = ip->xDD4_itemVar.pikachuthunder.x18;
    f32 offset = -attrs->x8;

    offset *= scale;
    *pos = ip->pos;
    pos->y += offset;
}

void it_2725_Logic39_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachuthunder.x0 == 0 &&
        ip->xDD4_itemVar.pikachuthunder.x38 != NULL &&
        !ftPk_SpecialLw_CheckProperty(ip->xDD4_itemVar.pikachuthunder.x38))
    {
        ftPk_SpecialLw_SetState_Unk0(ip->xDD4_itemVar.pikachuthunder.x38);
    }
}

void it_802B2080(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itPikachuthunderAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_80275158(gobj, attrs->x0);
    it_8026BB44(gobj);
}

bool itPikachuthunder_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachuthunder.x8 <= 0) {
        it_802B211C(gobj);
    } else {
        ip->xDD4_itemVar.pikachuthunder.x8--;
    }
    return false;
}

void it_802B211C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itPikachuthunderAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_80275158(gobj, attrs->x0);
    ip->x40_vel = ip->xDD4_itemVar.pikachuthunder.x1C;
    ip->xDCC_flag.b3 = 1;
    it_8026BB20(gobj);
}

bool itPikachuthunder_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ip->xD44_lifeTimer--;
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

bool itPikachuthunder_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachuthunder.x0 == 0) {
        if (it_8026DA70(gobj)) {
            Item* ip = gobj->user_data;
            itPikachuthunderAttributes* attrs =
                ip->xC4_article_data->x4_specialAttributes;
            Vec3 pos;
            pos.z = 0.0f;
            pos.x = 0.0f;
            pos.y = -attrs->x8;
            it_80272AC4(gobj, &pos);
            it_802B22B8(gobj);
            if (ip->xDD4_itemVar.pikachuthunder.x38 != NULL) {
                if (!ftPk_SpecialLw_CheckProperty(
                        ip->xDD4_itemVar.pikachuthunder.x38))
                {
                    ftPk_SpecialLw_80127608(
                        ip->xDD4_itemVar.pikachuthunder.x38);
                }
            }
        }
    } else {
        Item* ip = gobj->user_data;
        if (ip->xDD4_itemVar.pikachuthunder.x4 != 0) {
            if (ip->pos.y <= ip->xDD4_itemVar.pikachuthunder.x28.y) {
                it_802B22B8(gobj);
            }
        }
    }
    return false;
}

static inline void it_802B22B8_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachuthunder.x34 != NULL) {
        Item* child_ip = GET_ITEM(ip->xDD4_itemVar.pikachuthunder.x34);
        if (child_ip != NULL) {
            child_ip->xDD4_itemVar.pikachuthunder.x28 = ip->pos;
            child_ip->xDD4_itemVar.pikachuthunder.x4 = 1;
        }
    }
}

void it_802B22B8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 2, ITEM_UNK_0x1 | ITEM_HIT_PRESERVE);
    ip->xD44_lifeTimer = ip->xDD4_itemVar.pikachuthunder.x14;
    ip->xDD4_itemVar.pikachuthunder.x4 = 1;
    it_802B22B8_inline(gobj);
}

static inline f32 pika_scale(f32 a, f32 b)
{
    f32 f = 10000.0f * a / b;
    f = ((s32) (f + 1)) / 10000.0f;
    return f;
}

static inline void itPikachuthunder_UnkMotion2_ScaleCall(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_80275594(gobj, 0,
                pika_scale(ip->xDD4_itemVar.pikachuthunder.x10,
                           ip->xDD4_itemVar.pikachuthunder.xC));
}

static inline void itPikachuthunder_UnkMotion2_UpdateScale(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itPikachuthunderAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.pikachuthunder.x10 =
        ip->xDD4_itemVar.pikachuthunder.xC +
        ip->xDD4_itemVar.pikachuthunder.x1C.y;
    if (ip->xDD4_itemVar.pikachuthunder.x10 > 0.0f) {
        ip->xDD4_itemVar.pikachuthunder.x18 =
            pika_scale(ip->xDD4_itemVar.pikachuthunder.x10, attrs->x4);
        if (ip->xDD4_itemVar.pikachuthunder.x18 <= 0.0f) {
            ip->xDD4_itemVar.pikachuthunder.x18 = 0.01f;
        }
        itPikachuthunder_UnkMotion2_ScaleCall(gobj);
        ip->xDD4_itemVar.pikachuthunder.xC =
            ip->xDD4_itemVar.pikachuthunder.x10;
    }
}

bool itPikachuthunder_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    PAD_STACK(12);

    ip->xD44_lifeTimer--;
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    itPikachuthunder_UnkMotion2_UpdateScale(gobj);
    HSD_JObjSetScaleY(jobj, ip->xDD4_itemVar.pikachuthunder.x18);
    return false;
}

bool itPikachuThunder_Logic39_DmgDealt(Item_GObj* arg0)
{
    return false;
}

bool itPikachuThunder_Logic39_HitShield(Item_GObj* arg0)
{
    return false;
}

bool itPikachuThunder_Logic39_Clanked(Item_GObj* arg0)
{
    return false;
}

bool itPikachuThunder_Logic39_Absorbed(Item_GObj* arg0)
{
    return false;
}

void itPikachuThunder_Logic39_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachuthunder.x38 == ref_gobj) {
        ip->xDD4_itemVar.pikachuthunder.x38 = NULL;
    }
    it_8026B894(gobj, ref_gobj);
}
