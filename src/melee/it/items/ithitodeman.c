#include "ithitodeman.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ftlib.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbvector.h"

#include <math.h>
#include <baselib/jobj.h>
#include <baselib/random.h>
#include <MSL/math_ppc.h>
#include <MSL/trigf.h>

void it_2725_Logic24_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHitodemanAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;

    ip->facing_dir = 0.0f;
    ip->xDBC_itcmd_var4.flags.x0 = false;

    it_80279CDC(gobj, attrs->x0);
    it_802D43EC(gobj);
    it_802D4494(gobj);
    it_802D4510(gobj);

    ip->xDD4_itemVar.hitodeman.x8C = (f32) attrs->x3C;

    ip->xDD4_itemVar.hitodeman.x6C = 0.0f;
    ip->xDD4_itemVar.hitodeman.x70 = 0.0f;
    ip->xDD4_itemVar.hitodeman.x74 = 0.0f;
    ip->xDD4_itemVar.hitodeman.x78 = 0.0f;
    ip->xDD4_itemVar.hitodeman.x7C = 0.0f;
    ip->xDD4_itemVar.hitodeman.x80 = 0.0f;

    ip->xDAC_itcmd_var0 = 0;
    ip->xDB0_itcmd_var1 = 0;

    it_802D4B54(gobj);
    Item_8026AE84(ip, 0x2738, 0x7F, 0x40);
}

void it_802D43AC(void) {}

void it_802D43B0(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8026B894(gobj, ref_gobj);
    ip->xDD4_itemVar.hitodeman.x90 = NULL;
    ip->xDAC_itcmd_var0 = 1;
}

void it_802D43EC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHitodemanAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    HSD_GObj* owner_gobj;
    f32 randf;
    f32 diff;

    owner_gobj = ftLib_80086198(ip->owner);
    if (owner_gobj != NULL) {
        ip->xDD4_itemVar.hitodeman.x90 = owner_gobj;
    } else {
        ip->xDD4_itemVar.hitodeman.x90 = ip->owner;
    }

    randf = HSD_Randf();
    diff = attrs->x8;
    diff = attrs->x4 - diff;
    ip->xDD4_itemVar.hitodeman.x60 = diff * randf + attrs->x8;

    randf = HSD_Randf();
    diff = attrs->xC - attrs->x10;
    ip->xDD4_itemVar.hitodeman.x64 = diff * randf + attrs->x10;

    if (HSD_Randi(2) != 0) {
        ip->xDD4_itemVar.hitodeman.x60 *= -1.0f;
    }
}

void it_802D4494(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHitodemanAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    s32 randi;
    PAD_STACK(8);
    randi = HSD_Randi((s32) (attrs->x14 - attrs->x18));
    ip->xDD4_itemVar.hitodeman.x84 = attrs->x18 + (f32) randi;
}

void it_802D4510(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHitodemanAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);
    ip->xDD4_itemVar.hitodeman.x88 =
        attrs->x44 + HSD_Randi(attrs->x40 - attrs->x44);
}

static inline void it_802D4564_anim_done(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool it_802D4564(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xDAC_itcmd_var0 != 0) {
        return true;
    }
    if (!it_80272C6C(gobj)) {
        it_802D4564_anim_done(gobj);
    }
    if (--ip->xDD4_itemVar.hitodeman.x84 < 0.0f) {
        if (ip->xDD4_itemVar.hitodeman.x90 != NULL) {
            HSD_JObj* jobj = gobj->hsd_obj;
            Vec3 target_pos;
            PAD_STACK(12);
            ftLib_80086644(ip->xDD4_itemVar.hitodeman.x90, &target_pos);
            if (target_pos.x < ip->pos.x) {
                ip->facing_dir = -1.0f;
            } else {
                ip->facing_dir = 1.0f;
            }
            HSD_JObjSetRotationY(jobj, 1.5707964f * ip->facing_dir);
        } else {
            it_80279C48(gobj);
        }
        it_802D4990(gobj);
        ip->x40_vel.x = 0.0f;
        ip->x40_vel.y = 0.0f;
        ip->x40_vel.z = 0.0f;
        Item_8026AE84(ip, 0x2738, 127, 64);
    }
    return false;
}

void it_802D472C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHitodemanAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    Vec3 target_pos;
    Vec3 dir;
    f32 speed;
    f32 dist;
    PAD_STACK(4);

    if (ip->xDD4_itemVar.hitodeman.x90 != NULL) {
        ftLib_80086644(ip->xDD4_itemVar.hitodeman.x90, &target_pos);
        target_pos.x += ip->xDD4_itemVar.hitodeman.x60;
        target_pos.y += ip->xDD4_itemVar.hitodeman.x64;
        target_pos.z = 0.0f;
        lbVector_Diff(&target_pos, &ip->pos, &dir);
        dist = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
        if (dist > attrs->x38) {
            lbVector_Normalize(&dir);
            speed = dist * attrs->x34;
            dir.x *= speed;
            dir.y *= speed;
            dir.z *= speed;
        }
        ip->x40_vel.x = it_802D48B0(&ip->xDD4_itemVar.hitodeman.x6C, dir.x,
                                    attrs->x24, attrs->x20, attrs->x1C);
        ip->x40_vel.y = it_802D48B0(&ip->xDD4_itemVar.hitodeman.x70, dir.y,
                                    attrs->x30, attrs->x2C, attrs->x28);
    }
}

bool it_802D48A8(Item_GObj* gobj)
{
    return false;
}

f32 it_802D48B0(f32* value, f32 target, f32 max_val, f32 accel, f32 decel)
{
    f32 current = *value;
    f32 diff = target - current;

    if (ABS(diff) > ABS(accel)) {
        if (diff > 0.0F) {
            target = current + accel;
        } else {
            target = current - accel;
        }
    } else if (ABS(diff) < ABS(decel)) {
        if (diff > 0.0F) {
            target = current + decel;
        } else {
            target = current - decel;
        }
    }

    if (target > 0.0F) {
        if (target > max_val) {
            target = max_val;
        }
    } else {
        if (target < -max_val) {
            target = -max_val;
        }
    }

    *value = target;
    return target;
}

void it_802D4990(Item_GObj* gobj)
{
    Item* ip;

    ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    ip->on_accessory = it_802D4B50;
}

bool itHitodeman_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32 timer;

    if (ip->xDAC_itcmd_var0 != 0) {
        return true;
    }

    timer = ip->xDD4_itemVar.hitodeman.x8C - 1.0F;
    ip->xDD4_itemVar.hitodeman.x8C = timer;

    if (timer < 0.0F) {
        if (--ip->xDD4_itemVar.hitodeman.x88 < 0) {
            return true;
        }

        ip->xDD4_itemVar.hitodeman.x8C =
            ((itHitodemanAttributes*)
                 ip->xC4_article_data->x4_specialAttributes)
                ->x3C;

        if (ip->xDD4_itemVar.hitodeman.x90 != NULL) {
            itHitodemanAttributes* attrs =
                ip->xC4_article_data->x4_specialAttributes;
            ip->x40_vel.x = -ip->facing_dir * attrs->x48;
            it_802D4C74(gobj);
            ip->xDB0_itcmd_var1 = 1;
        }
    }

    if (!it_80272C6C(gobj)) {
        ip = GET_ITEM(gobj);
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        ip->entered_hitlag = efLib_PauseAll;
        ip->exited_hitlag = efLib_ResumeAll;
        ip->on_accessory = it_802D4B50;
    }

    PAD_STACK(8);

    return false;
}

void itHitodeman_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHitodemanAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xDB0_itcmd_var1 != 0) {
        ip->x40_vel.x = -((-ip->facing_dir * attrs->x4C) - ip->x40_vel.x);
    }
}

bool itHitodeman_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D4B50(Item_GObj* gobj) {}

void it_802D4B54(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itHitodeman_UnkMotion2_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itHitodeman_UnkMotion2_Phys(Item_GObj* gobj)
{
    if (it_8027A09C(gobj)) {
        Item* ip;
        it_80273454(gobj);
        ip = GET_ITEM(gobj);
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
        ip->entered_hitlag = efLib_PauseAll;
        ip->exited_hitlag = efLib_ResumeAll;
    }
}

bool itHitodeman_UnkMotion2_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802D43AC);
}

void it_802D4C74(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHitodemanAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    SpawnItem spawn;
    Item_GObj* item_gobj;

    spawn.prev_pos = ip->pos;
    spawn.prev_pos.x += ip->facing_dir * attrs->x54;
    spawn.prev_pos.y += attrs->x58;
    it_8026BB88(gobj, &spawn.pos);
    spawn.facing_dir = ip->facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.facing_dir * attrs->x50;
    spawn.vel.y = 0.0f;
    spawn.vel.z = 0.0f;
    spawn.kind = 0xCC;
    spawn.x0_parent_gobj = ip->owner;
    spawn.x4_parent_gobj2 = gobj;
    spawn.x44_flag.b0 = false;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        if (ip->facing_dir == 1.0f) {
            lbAudioAx_800263E8(3.0f, gobj, 1, 0x2739, 127, 127, 0, 127, 60, 0,
                               -1);
        } else {
            lbAudioAx_800263E8(3.0f, gobj, 1, 0x273A, 127, 127, 0, 127, 60, 0,
                               -1);
        }
    }
}

void it_2725_Logic43_Spawned(Item_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    Item* ip = GET_ITEM(gobj);
    itHitodemanAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(16);

    it_80275158(gobj, attrs->x0);
    ip->xDB4_itcmd_var2 = 0;
    it_80274740(gobj);
    it_802D4F78(gobj);
    it_8026B3A8(gobj);
    HSD_JObjSetRotationY(jobj, (f32) M_PI_2 * ip->facing_dir);
}

bool it_802D4EF4(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDB4_itcmd_var2 = 1;
    return false;
}

bool it_802D4F08(Item_GObj* gobj)
{
    return it_8027AF50(gobj);
}

bool it_802D4F28(Item_GObj* gobj)
{
    return it_8027AE34(gobj);
}

bool itHitodeman_Logic43_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool it_802D4F50(Item_GObj* arg0)
{
    return true;
}

void it_802D4F58(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802D4F78(Item_GObj* gobj)
{
    f32 f;
    Item* ip;
    HSD_JObj* jobj;

    ip = GET_ITEM(gobj);
    jobj = GET_JOBJ(gobj);
    f = 1.0f;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    efSync_Spawn(0x46C, gobj, jobj, &f);
}

bool it_802D4FFC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32 timer;

    timer = ip->xD44_lifeTimer - 1.0F;
    ip->xD44_lifeTimer = timer;
    if (timer <= 0.0F) {
        return true;
    }
    if (ip->xDB4_itcmd_var2 != 0) {
        return true;
    }
    return false;
}

void it_802D5044(Item_GObj* gobj) {}

bool it_802D5048(Item_GObj* gobj)
{
    return false;
}
