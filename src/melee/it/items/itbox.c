#include "itbox.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/jobj.h"
#include "baselib/random.h"
#include "cm/camera.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbvector.h"
#include "mp/mpcoll.h"

#include <math.h>

#define ROT_VEL_SCALE 0.03490658476948738

/// Spawn a box accessory item that follows the parent item.
/// Returns the spawned gobj, or NULL if parent is invalid.
Item_GObj* it_80286088(Item_GObj* parent_gobj)
{
    Item_GObj* result = NULL;
    SpawnItem spawn;
    Vec3 pos;
    Item* spawned_ip;

    if (parent_gobj != NULL && GET_JOBJ(parent_gobj) != NULL) {
        lb_8000B1CC(GET_JOBJ(parent_gobj), NULL, &pos);

        spawn.kind = 1;
        spawn.prev_pos = pos;
        spawn.pos = spawn.prev_pos;
        spawn.facing_dir = 1.0F;
        spawn.x3C_damage = 0;
        spawn.vel.z = 0.0F;
        spawn.vel.y = 0.0F;
        spawn.vel.x = 0.0F;
        spawn.x0_parent_gobj = NULL;
        spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
        spawn.x44_flag.b0 = 0;
        spawn.x40 = 0;

        result = Item_80268B18(&spawn);
        if (result != NULL) {
            spawned_ip = GET_ITEM(result);
            spawned_ip->xDD4_itemVar.box.spawned_gobj = parent_gobj;
            {
                f32 r = HSD_Randf();
                spawned_ip->xDD4_itemVar.box.rot_vel_x =
                    (r - 0.5F) * ROT_VEL_SCALE;
            }
            {
                f32 r = HSD_Randf();
                spawned_ip->xDD4_itemVar.box.rot_vel_y =
                    (r - 0.5F) * ROT_VEL_SCALE;
            }
            spawned_ip->xDC8_word.flags.x19 = 0;
            it_8026BDB4(result);
            it_802870A4(result);
        }
    }
    return result;
}

#undef ROT_VEL_SCALE

/// Initialize box item state when spawned
void it_3F14_Logic1_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDCE_flag.b7 = 0;
    ip->xDD4_itemVar.box.opened = 0;
    ip->xDD4_itemVar.box.spawned_gobj = NULL;
    it_8028655C(gobj);
}

/// Cleanup box item when destroyed - destroys any spawned effect
void it_3F14_Logic1_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.box.spawned_gobj != NULL) {
        efLib_DestroyAll(ip->xDD4_itemVar.box.spawned_gobj);
        ip->xDD4_itemVar.box.spawned_gobj = NULL;
    }
}

/// Spawn item(s) from box based on weighted random roll.
/// arg1/arg2/arg3 are spawn weights, arg4 is additional weight for special
/// roll.
void it_80286248(Item_GObj* gobj, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    u8 pad1[24];
    s32 sum1;
    s32 rand;
    Item* ip = GET_ITEM(gobj);
    s32 special;
    Vec3 zero;
    u8 pad2[4];
    (void) pad1;
    (void) pad2;

    zero.z = 0.0F;
    zero.y = 0.0F;
    zero.x = 0.0F;

    if (it_8026F8B4(gobj, &ip->pos, &zero, false)) {
        return;
    }
    if (it_8026F6BC(gobj, &ip->pos, &zero, false) != NULL) {
        return;
    }

    special = 0;
    if (HSD_Randi(arg4) == 0) {
        special |= 1;
    }

    sum1 = arg1 + arg2;
    rand = HSD_Randi(arg3 + sum1);

    if (rand < arg1) {
        it_8026F3D4(gobj, NULL, 1, special);
    } else if (rand < sum1) {
        it_8026F3D4(gobj, NULL, 2, special);
    } else {
        it_8026F3D4(gobj, NULL, 3, special);
    }
}

#pragma push
#pragma dont_inline on
bool it_80286340(Item_GObj* gobj, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 sum1 = arg1 + arg2;
    s32 sum2 = arg3 + sum1;
    s32 rand = HSD_Randi(arg4 + sum2);
    if (rand < arg1) {
        return true;
    }
    if (rand < sum1) {
        return true;
    }
    if (rand < sum2) {
        return true;
    }
    return false;
}
#pragma pop

/// Check if box bounced off a surface nearly upright. If the bounce angle
/// relative to vertical is below threshold, clear velocity vectors and
/// set ground flag.
bool it_802863BC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    CollData* coll = &ip->x378_itemColl;
    itBoxAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    Vec3 dir;
    Vec3 unit;

    if (coll->env_flags & Collide_FloorMask) {
        it_80276408(gobj, coll, &dir);
        unit.x = 0.0F;
        unit.y = 1.0F;
        unit.z = 0.0F;
        if (lbVector_AngleXY(&dir, &unit) < attr->bounce_angle_threshold) {
            ip->x7C.z = 0.0F;
            ip->x7C.y = 0.0F;
            ip->x7C.x = 0.0F;
            ip->x88.z = 0.0F;
            ip->x88.y = 0.0F;
            ip->x88.x = 0.0F;
            ip->x94.z = 0.0F;
            ip->x94.y = 0.0F;
            ip->x94.x = 0.0F;
            ip->xA0.z = 0.0F;
            ip->xA0.y = 0.0F;
            ip->xA0.x = 0.0F;
            ip->xD5C = 1;
            return true;
        }
    }
    return false;
}

void fn_80286480(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    PAD_STACK(12);
    it_8026B390(gobj);
    it->x40_vel.x = it->x40_vel.y = it->x40_vel.z = 0.0F;
    Item_80268E5C(gobj, 0, 2);
}

/// Check animation frame and play sound if at start
bool itBox_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 1.0F) {
        it_802787B4(gobj, 0x421);
    }
    return false;
}

void itBox_UnkMotion0_Phys(Item_GObj* gobj)
{
    return;
}

bool itBox_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, (HSD_GObjEvent) it_8028655C);
    it_80276CB8(gobj);
    return false;
}

void it_8028655C(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itBox_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

#define TAU 6.2831853071795862

/// Physics for thrown box motion. Applies gravity and updates rotation
/// based on stored rotation velocities (wobble effect when thrown).
void itBox_UnkMotion1_Phys(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attr = ip->xCC_item_attr;

    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);

    if (ip->xDD4_itemVar.box.spawned_gobj != NULL) {
        Quaternion rot;
        ip->x40_vel.z *= 0.95F;

        HSD_JObjGetRotation(jobj, &rot);

        rot.x += ip->xDD4_itemVar.box.rot_vel_x;
        if (rot.x > TAU) {
            rot.x -= TAU;
        } else if (rot.x < -TAU) {
            rot.x += TAU;
        }

        rot.y += ip->xDD4_itemVar.box.rot_vel_y;
        if (rot.y > TAU) {
            rot.y -= TAU;
        } else if (rot.y < -TAU) {
            rot.y += TAU;
        }

        HSD_JObjSetRotation(jobj, &rot);
    }
}

#undef TAU

bool itBox_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, fn_80286480);
    return false;
}

void it_3F14_Logic1_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itBox_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itBox_UnkMotion2_Phys(Item_GObj* gobj)
{
    return;
}

void it_3F14_Logic1_Thrown(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

void itBox_UnkMotion4_Phys(Item_GObj* gobj)
{
    ItemAttr* attr = ((Item*) gobj->user_data)->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

/// Inline helper: spawn break effect and roll for item spawn.
/// Used by collision handlers when box breaks.
static inline void itBox_TryOpen_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itBoxAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    efSync_Spawn(0x427, gobj, &ip->pos);
    if (it_80286340(gobj, attr->spawn_weight_0, attr->spawn_weight_1,
                    attr->spawn_weight_2, attr->empty_weight))
    {
        it_80286BA0(gobj);
    } else {
        it_80286AA4(gobj);
    }
}

/// Collision handler for dropped box. Opens on ground/wall contact.
bool itBox_UnkMotion3_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(16);
    if (it_8026DA08(gobj)) {
        itBox_TryOpen_inline(gobj);
    } else if (it_802763E0(gobj)) {
        if (ip->x40_vel.y > 0.0F) {
            ip->x40_vel.y = 0.0F;
        }
    } else if (it_80276308(gobj)) {
        itBox_TryOpen_inline(gobj);
    }
    return false;
}

void it_3F14_Logic1_Dropped(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

/// Collision handler for thrown box in air. Checks if landed hard enough
/// to break, otherwise bounces.
bool itBox_UnkMotion4_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itBoxAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(24);

    if (it_8026DA08(gobj)) {
        f32 vel_y = ip->x40_vel.y;
        if (vel_y < 0.0F) {
            vel_y = -vel_y;
        }
        if (vel_y > attr->break_vel_threshold) {
            itBox_TryOpen_inline(gobj);
        } else {
            it_802762B0(ip);
            ip = GET_ITEM(gobj);
            it_8026B390(gobj);
            ip->x40_vel.z = 0.0F;
            ip->x40_vel.y = 0.0F;
            ip->x40_vel.x = 0.0F;
            Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
        }
    }
    return false;
}

/// Box opens empty (no items spawned). Clears velocity, sets opened flag,
/// spawns smoke effect (0x78), and transitions to state 6.
void it_80286AA4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Vec3 pos;

    it_8026BB44(gobj);
    it_80272C08(gobj);
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    it_8026BD24(gobj);
    it_8027518C(gobj);

    ip->x40_vel.x = 0.0F;
    ip->x40_vel.y = 0.0F;
    ip->xDCF_flag.b2 = 1;
    ip->xDD4_itemVar.box.opened = 1;
    ip->xDD4_itemVar.box.despawn_timer = 40;

    it_80275444(gobj);

    pos = ip->pos;
    lb_800119DC(&pos, 0x78, 1.0F, 0.02F, 1.0471976F);

    Item_80268E5C(gobj, 6, 2);
}

bool itBox_UnkMotion6_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void itBox_UnkMotion6_Phys(Item_GObj* gobj)
{
    return;
}

bool itBox_UnkMotion6_Coll(Item_GObj* gobj)
{
    return false;
}

/// Box opens and spawns items. Plays sound, triggers camera, spawns items,
/// sets opened flag, and transitions to state 7.
void it_80286BA0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itBoxAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(8);

    Item_8026AE84(ip, 0xF6, 0x7F, 0x40);
    Camera_80030E44(2, &ip->pos);
    it_80286248(gobj, attr->spawn_weight_0, attr->spawn_weight_1,
                attr->spawn_weight_2, attr->special_spawn_weight);
    HSD_JObjSetFlagsAll(jobj, 0x10);
    it_802756D0(gobj);

    ip->x40_vel.x = 0.0F;
    ip->x40_vel.y = 0.0F;
    ip->xDCF_flag.b2 = 1;
    ip->xDD4_itemVar.box.opened = 1;
    ip->xDD4_itemVar.box.despawn_timer = 40;

    it_8026B3A8(gobj);

    Item_80268E5C(gobj, 7, 2);
}

bool itBox_UnkMotion7_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.box.despawn_timer -= 1;
    if (ip->xDD4_itemVar.box.despawn_timer > 0) {
        return false;
    }
    return true;
}

void itBox_UnkMotion7_Phys(Item_GObj* gobj)
{
    return;
}

bool itBox_UnkMotion7_Coll(Item_GObj* gobj)
{
    return false;
}

/// Box dealt damage to something - try to open
bool it_3F14_Logic1_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip->xDD4_itemVar.box.opened == 0) {
        itBox_TryOpen_inline(gobj);
    }
    return false;
}

/// Box clanked with another hitbox - try to open
bool it_3F14_Logic1_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip->xDD4_itemVar.box.opened == 0) {
        itBox_TryOpen_inline(gobj);
    }
    return false;
}

/// Box hit a shield - try to open
bool it_3F14_Logic1_HitShield(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip->xDD4_itemVar.box.opened == 0) {
        itBox_TryOpen_inline(gobj);
    }
    return false;
}

/// Box was reflected - try to open
bool it_3F14_Logic1_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip->xDD4_itemVar.box.opened == 0) {
        itBox_TryOpen_inline(gobj);
    }
    return false;
}

/// Handle damage received by box. When accumulated damage reaches threshold,
/// box breaks open. Weighted random roll determines if items spawn or box is
/// empty. Effect 0x427 is the box breaking visual effect.
bool it_3F14_Logic1_DmgReceived(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itBoxAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(16);
    if (ip->xDD4_itemVar.box.opened == 0) {
        if (ip->xC9C >= attr->damage_threshold) {
            efSync_Spawn(0x427, gobj, &ip->pos);
            if (it_80286340(gobj, attr->spawn_weight_0, attr->spawn_weight_1,
                            attr->spawn_weight_2, attr->empty_weight))
            {
                it_80286BA0(gobj);
            } else {
                it_80286AA4(gobj);
            }
        }
    }
    return false;
}

void it_3F14_Logic1_EnteredAir(Item_GObj* gobj)
{
    Item* ip;
    PAD_STACK(16);

    if (it_802863BC(gobj) != 0) {
        ip = GET_ITEM(gobj);
        it_8026B390(gobj);
        ip->x40_vel.z = 0.0F;
        ip->x40_vel.y = 0.0F;
        ip->x40_vel.x = 0.0F;
        Item_80268E5C(gobj, 0, 2);
    } else {
        Item_80268E5C(gobj, 5, 2);
    }
}

bool itBox_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

void itBox_UnkMotion5_Phys(Item_GObj* gobj)
{
    return;
}

bool itBox_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, fn_80286480, it_8028655C);
    return false;
}

void it_3F14_Logic1_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// Transition box to state 8 and set accessory callback
void it_802870A4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762B0(ip);
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
    ip->on_accessory = (HSD_GObjEvent) it_8028733C;
}

bool itBox_UnkMotion8_Anim(Item_GObj* gobj)
{
    return false;
}

#define DEG_TO_RAD 0.01745329238474369
#define MAX_ROT_VEL 0.05235987901687622
#define TAU 6.2831853071795862

/// Physics for floating box (state 8). Randomly adjusts rotation velocities
/// each frame and applies rotation around X and Y axes.
void itBox_UnkMotion8_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Quaternion rot;
    f32 vel;

    ip->xDD4_itemVar.box.rot_vel_x += DEG_TO_RAD * (HSD_Randf() - 0.2F);
    vel = ip->xDD4_itemVar.box.rot_vel_x;
    if (vel > MAX_ROT_VEL) {
        ip->xDD4_itemVar.box.rot_vel_x = MAX_ROT_VEL;
    } else if (vel < -MAX_ROT_VEL) {
        ip->xDD4_itemVar.box.rot_vel_x = -MAX_ROT_VEL;
    }

    ip->xDD4_itemVar.box.rot_vel_y += DEG_TO_RAD * (HSD_Randf() - 0.2F);
    vel = ip->xDD4_itemVar.box.rot_vel_y;
    if (vel > MAX_ROT_VEL) {
        ip->xDD4_itemVar.box.rot_vel_y = MAX_ROT_VEL;
    } else if (vel < -MAX_ROT_VEL) {
        ip->xDD4_itemVar.box.rot_vel_y = -MAX_ROT_VEL;
    }

    HSD_JObjGetRotation(jobj, &rot);

    rot.x += ip->xDD4_itemVar.box.rot_vel_x;
    if (rot.x > TAU) {
        rot.x -= TAU;
    } else if (rot.x < -TAU) {
        rot.x += TAU;
    }

    rot.y += ip->xDD4_itemVar.box.rot_vel_y;
    if (rot.y > TAU) {
        rot.y -= TAU;
    } else if (rot.y < -TAU) {
        rot.y += TAU;
    }

    HSD_JObjSetRotation(jobj, &rot);
}

#undef DEG_TO_RAD
#undef MAX_ROT_VEL
#undef TAU

bool itBox_UnkMotion8_Coll(Item_GObj* gobj)
{
    return false;
}

/// Accessory callback - makes item follow its spawned parent item.
/// Updates position and velocity to track the parent's JObj position.
void it_8028733C(Item_GObj* gobj)
{
    HSD_JObj* spawned_jobj;
    Item* ip;
    Vec3 target_pos;
    Vec3 vel;

    ip = GET_ITEM(gobj);

    if (ip->xDD4_itemVar.box.spawned_gobj != NULL) {
        spawned_jobj = GET_JOBJ(ip->xDD4_itemVar.box.spawned_gobj);
        HSD_JObjGetTranslation(spawned_jobj, &target_pos);
        lbVector_Diff(&target_pos, &ip->pos, &vel);
        ip->pos = target_pos;
        if (target_pos.z >= 0.0F) {
            ip->x40_vel = vel;
            mpColl_80043680(&ip->x378_itemColl, &ip->pos);
            it_8026B3A8(gobj);
            Item_80268E5C(gobj, 1, 2);
        }
    } else {
        mpColl_80043680(&ip->x378_itemColl, &ip->pos);
        it_8026B3A8(gobj);
        Item_80268E5C(gobj, 1, 2);
    }
}
