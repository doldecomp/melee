#include "itnesspkthunderball.h"

#include <placeholder.h>

#include "db/db.h"
#include "dolphin/pad.h"
#include "ft/chara/ftNess/ftNs_SpecialHi.h"
#include "ft/ftlib.h"
#include "gr/stage.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itnesspkthundertrail.h"
#include "lb/lbvector.h"
#include "MSL/math.h"

#include <string.h>
#include <trigf.h>

/* 2AC000 */ static bool itNesspkthunderball_UnkMotion0_Coll(Item_GObj* gobj);

static inline void normalizeAngle(f32* angle)
{
    while (*angle < 0.0F) {
        *angle += M_TAU;
    }
    while (*angle > M_TAU) {
        *angle -= M_TAU;
    }
}

void it_802AB3F0(Item_GObj* gobj, Vec3* out, s32 idx)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        if (ip != NULL) {
            if (out != NULL) {
                *out = ip->xDD4_itemVar.pkthunder.positions[idx * 2];
            }
        } else if (out != NULL) {
            out->x = out->y = out->z = 0.0f;
        }
    } else if (out != NULL) {
        out->x = out->y = out->z = 0.0f;
    }
}

void it_802AB468(Item_GObj* gobj, f32* out, s32 unused)
{
    Item* ip;

    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        if (ip != NULL) {
            if (out == NULL) {
                return;
            }
            *out = *(f32*) &ip->xDD4_itemVar.pkthunder.xEEC;
            return;
        }
        if (out == NULL) {
            return;
        }
        *out = 0.0f;
        return;
    }
    if (out == NULL) {
        return;
    }
    *out = 0.0f;
}

bool it_802AB4B8(Item_GObj* gobj, CollData* cd)
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

HSD_GObj* it_802AB568(Item_GObj* gobj)
{
    Item* ip;

    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        if (ip != NULL) {
            return ip->owner;
        }
    }
    return NULL;
}

HSD_GObj* it_802AB58C(Item_GObj* owner, Vec3* pos, f32 facing_dir)
{
    Item_GObj* ball;
    int i;
    SpawnItem spawn;

    spawn.kind = It_Kind_Ness_PKThunder;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68(owner, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = owner;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = Item_8026AE60();

    ball = Item_80268B18(&spawn);
    if (ball != NULL) {
        Item* ip = GET_ITEM(ball);
        itPKThunderAttributes* attr =
            ip->xC4_article_data->x4_specialAttributes;

        ip->xDB8_itcmd_var3 = 0;
        ip->xDB4_itcmd_var2 = 0;
        ip->xDB0_itcmd_var1 = 0;
        ip->xDAC_itcmd_var0 = 0;
        it_80275158(ball, attr->x0_PKTHUNDER_LIFETIME);
        ip->xDD4_itemVar.pkthunder.xEF4 = NULL;
        for (i = 0; i < 16; i++) {
            ip->xDD4_itemVar.pkthunder.positions[i] = *pos;
        }
        for (i = 0; i < 16; i++) {
            ip->xDD4_itemVar.pkthunder.angles[i] =
                deg_to_rad * attr->x8_PKTHUNDER_SPAWN_ANGLE;
        }
        for (i = 0; i < 6; i++) {
            ip->xDD4_itemVar.pkthunder.xDD4[i] = NULL;
        }
        ip->xDD4_itemVar.pkthunder.xEFC = 0;
        ip->xDD4_itemVar.pkthunder.xEF8 = 0;
        ip->xDD4_itemVar.pkthunder.xF00 = 0;
        ip->xDD4_itemVar.pkthunder.xF04 = owner;
        ip->xDD4_itemVar.pkthunder.xF08 = NULL;
        it_802ABA4C(ball);
        ip->xDCC_flag.b3 = false;
        if (Stage_80225194() == 0x54) {
            Item_80267454(ball);
        }
    }
    return ball;
}

void it_802AB90C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    s32 i;

    it_802725D4(gobj);

    if (ip->xDD4_itemVar.pkthunder.xF04 != NULL) {
        if (ip->xDD4_itemVar.pkthunder.xF00 == NULL &&
            ip->xDD4_itemVar.pkthunder.xF04 == ip->owner)
        {
            ftNs_SpecialHi_ItemPKThunderRemove(
                ip->xDD4_itemVar.pkthunder.xF04);
        }
        ip->xDD4_itemVar.pkthunder.xF04 = NULL;
    }

    for (i = 0; i < 6; i++) {
        if (ip->xDD4_itemVar.pkthunder.xDD4[i] != NULL) {
            it_802AC58C(ip->xDD4_itemVar.pkthunder.xDD4[i]);
            ip->xDD4_itemVar.pkthunder.xDD4[i] = NULL;
        }
    }
    ip->xDC8_word.flags.x13 = 0;
}

void it_802AB9C0(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        if (ip != NULL && ip->xDD4_itemVar.pkthunder.xF00 == NULL) {
            s32 i;
            ip->owner = NULL;
            ip->xDC8_word.flags.x13 = 0;
            for (i = 0; i < 6; i++) {
                if (ip->xDD4_itemVar.pkthunder.xDD4[i] != NULL) {
                    it_802AC5D8(ip->xDD4_itemVar.pkthunder.xDD4[i]);
                }
            }
        }
    }
}

void it_802ABA4C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itPKThunderAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    int i;

    it_8026B3A8(gobj);
    ip->xDC8_word.flags.x13 = 0;
    it_80272940(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_80275158(gobj, attr->x0_PKTHUNDER_LIFETIME);
    for (i = 0; i < 16; i++) {
        ip->xDD4_itemVar.pkthunder.angles[i] =
            deg_to_rad * attr->x8_PKTHUNDER_SPAWN_ANGLE;
    }
    {
        f32 speed = attr->x4_PKTHUNDER_SPEED;
        ip->xDD4_itemVar.pkthunder.xEEC = speed;
        ip->x40_vel.y = speed;
    }
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.x = 0.0f;
    db_80225DD8(gobj, ip->xDD4_itemVar.pkthunder.xF04);
}

bool itNesspkthunderball_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(32);

    switch (ip->xDD4_itemVar.pkthunder.xEF8) {
    case 0:
    case 2:
    case 4:
    case 6:
    case 8:
    case 10:
        if (ip->xDD4_itemVar.pkthunder.xEFC <= 5) {
            if (ip->owner == ip->xDD4_itemVar.pkthunder.xF04) {
                f32 dir = ip->facing_dir;
                ip->xDD4_itemVar.pkthunder
                    .xDD4[ip->xDD4_itemVar.pkthunder.xEFC] =
                    it_802AC43C(ip->xDD4_itemVar.pkthunder.xF04, gobj,
                                &ip->pos, ip->xDD4_itemVar.pkthunder.xEFC,
                                ip->xAC4_ignoreItemID, dir);
            } else {
                f32 dir = ip->facing_dir;
                ip->xDD4_itemVar.pkthunder
                    .xDD4[ip->xDD4_itemVar.pkthunder.xEFC] = it_802AC43C(
                    NULL, gobj, &ip->pos, ip->xDD4_itemVar.pkthunder.xEFC,
                    ip->xAC4_ignoreItemID, dir);
            }
            ip->xDD4_itemVar.pkthunder.xEFC += 1;
        }
        break;
    }

    ip->xDD4_itemVar.pkthunder.xEF8 += 1;

    if ((ip->xDD4_itemVar.pkthunder.xF00 == 0) &&
        (ip->xDD4_itemVar.pkthunder.xF04 != NULL))
    {
        if (ip->owner == ip->xDD4_itemVar.pkthunder.xF04) {
            if (ftNs_SpecialHi_CheckSpecialHiHold(
                    ip->xDD4_itemVar.pkthunder.xF04) != true)
            {
                return true;
            }
        } else {
            it_802AB90C(gobj);
            return true;
        }
    }
    return it_80273130(gobj);
}

static inline void itNesspkthunderball_ShiftAngles(Item* ip)
{
    int i;
    for (i = 14; i >= 0; i--) {
        ip->xDD4_itemVar.pkthunder.angles[i + 1] =
            ip->xDD4_itemVar.pkthunder.angles[i];
    }
}

static inline void itNesspkthunderball_ShiftPositions(Item* ip)
{
    int i;
    for (i = 14; i >= 0; i--) {
        ip->xDD4_itemVar.pkthunder.positions[i + 1] =
            ip->xDD4_itemVar.pkthunder.positions[i];
    }
}

void itNesspkthunderball_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itPKThunderAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    Vec3 stick;
    f32 angle;
    Vec3 cross;
    PAD_STACK(4);

    if (ip->xDD4_itemVar.pkthunder.xF00 == 0 &&
        ip->xDD4_itemVar.pkthunder.xF04 != NULL &&
        ip->owner == ip->xDD4_itemVar.pkthunder.xF04 &&
        ftNs_SpecialHi_CheckSpecialHiHold(ip->xDD4_itemVar.pkthunder.xF04) ==
            true)
    {
        itNesspkthunderball_ShiftAngles(ip);

        ftLib_800865D8(ip->xDD4_itemVar.pkthunder.xF04, &stick.x, &stick.y);
        stick.z = 0.0f;

        if (ABS(stick.x) > attr->xC_PKTHUNDER_STICK_THRESHOLD ||
            ABS(stick.y) > attr->xC_PKTHUNDER_STICK_THRESHOLD)
        {
            angle = lbVector_Angle(&ip->x40_vel, &stick);
            lbVector_CrossprodNormalized(&ip->x40_vel, &stick, &cross);

            if (angle >= deg_to_rad * 45.0f) {
                if (cross.z > 0.0f) {
                    ip->xDD4_itemVar.pkthunder.angles[0] +=
                        deg_to_rad * attr->x10_PKTHUNDER_TURN_RADIUS;
                } else if (cross.z < 0.0f) {
                    ip->xDD4_itemVar.pkthunder.angles[0] -=
                        deg_to_rad * attr->x10_PKTHUNDER_TURN_RADIUS;
                }
            }
            if (angle < deg_to_rad * 45.0f) {
                if (cross.z > 0.0f) {
                    ip->xDD4_itemVar.pkthunder.angles[0] +=
                        angle / (45.0f / attr->x10_PKTHUNDER_TURN_RADIUS);
                } else if (cross.z < 0.0f) {
                    ip->xDD4_itemVar.pkthunder.angles[0] -=
                        angle / (45.0f / attr->x10_PKTHUNDER_TURN_RADIUS);
                }
            }

            while (ip->xDD4_itemVar.pkthunder.angles[0] < -M_TAU) {
                ip->xDD4_itemVar.pkthunder.angles[0] += M_TAU;
            }
            while (ip->xDD4_itemVar.pkthunder.angles[0] > M_TAU) {
                ip->xDD4_itemVar.pkthunder.angles[0] -= M_TAU;
            }

            ip->x40_vel.x = ip->xDD4_itemVar.pkthunder.xEEC *
                            cosf(ip->xDD4_itemVar.pkthunder.angles[0]);
            ip->x40_vel.y = ip->xDD4_itemVar.pkthunder.xEEC *
                            sinf(ip->xDD4_itemVar.pkthunder.angles[0]);
            ip->x40_vel.z = 0.0f;
        }
    } else {
        itNesspkthunderball_ShiftAngles(ip);
    }

    itNesspkthunderball_ShiftPositions(ip);
    ip->xDD4_itemVar.pkthunder.positions[0] = ip->pos;
}

bool itNesspkthunderball_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);

    if (it_802AB4B8(gobj, &ip->x378_itemColl)) {
        it_802725D4(gobj);
        return true;
    }
    return false;
}

bool itNessPKThunderball_Logic26_DmgDealt(Item_GObj* gobj)
{
    it_802AB90C(gobj);
    return true;
}

bool it_802AC074(Item_GObj* gobj)
{
    it_802AB90C(gobj);
    return true;
}

bool it_802AC098(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    int i;
    PAD_STACK(8);

    if (ip->xDD4_itemVar.pkthunder.xF04 != NULL) {
        if (ip->owner == ip->xDD4_itemVar.pkthunder.xF04) {
            ftNs_SpecialHi_ItemPKThunderCheckOwn(
                ip->xDD4_itemVar.pkthunder.xF04, gobj);
        }
        ip->xDD4_itemVar.pkthunder.xF04 = NULL;
    }

    ip->xDD4_itemVar.pkthunder.xF00 = 1;
    ip->xDD4_itemVar.pkthunder.angles[0] += M_PI;
    normalizeAngle(&ip->xDD4_itemVar.pkthunder.angles[0]);

    for (i = 0; i < 6; i++) {
        if (ip->xDD4_itemVar.pkthunder.xDD4[i] != NULL) {
            it_802AC58C(ip->xDD4_itemVar.pkthunder.xDD4[i]);
            ip->xDD4_itemVar.pkthunder.xDD4[i] = NULL;
        }
    }

    ip->xDD4_itemVar.pkthunder.xEF8 = 0;
    ip->xDD4_itemVar.pkthunder.xEFC = 0;

    for (i = 1; i < 16; ++i) {
        ip->xDD4_itemVar.pkthunder.positions[i] =
            ip->xDD4_itemVar.pkthunder.positions[0];
        ip->xDD4_itemVar.pkthunder.angles[i] =
            ip->xDD4_itemVar.pkthunder.angles[0];
    }

    ip->x40_vel.x = ip->xDD4_itemVar.pkthunder.xEEC *
                    cosf(ip->xDD4_itemVar.pkthunder.angles[0]);
    ip->x40_vel.y = ip->xDD4_itemVar.pkthunder.xEEC *
                    sinf(ip->xDD4_itemVar.pkthunder.angles[0]);
    ip->x40_vel.z = 0.0f;
    return false;
}

bool it_802AC338(Item_GObj* gobj)
{
    it_802AB90C(gobj);
    return true;
}

bool it_802AC35C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(16);
    lbVector_Mirror(&ip->x40_vel, &ip->xC58);
    ip->x40_vel.z = 0.0f;
    ip->xDD4_itemVar.pkthunder.angles[0] =
        atan2f(ip->x40_vel.y, ip->x40_vel.x);
    normalizeAngle(&ip->xDD4_itemVar.pkthunder.angles[0]);
    return false;
}

bool it_802AC3F8(Item_GObj* gobj)
{
    it_802AB90C(gobj);
    return true;
}

void it_802AC41C(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
