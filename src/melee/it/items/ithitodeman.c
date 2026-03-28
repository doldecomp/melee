#include "ithitodeman.h"

#include <math.h>
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

#include <baselib/random.h>

typedef struct {
    f32 x0;
    float x4;
    float x8;
    float xC;
    float x10;
    float x14;
    float x18;
    char pad_0[0x3C - 0x1C];
    s32 x3C;
    s32 x40;
    s32 x44;
    u8 _pad2[0x4];
    f32 x4C;
} itHitodemanAttributes;

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

/// #it_802D4564

/// #it_802D472C

bool it_802D48A8(Item_GObj* gobj)
{
    return false;
}

void it_802D48B0(f32* value, f32 target, f32 max_val, f32 accel,
                 f32 decel)
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

/// #itHitodeman_UnkMotion1_Anim

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

/// #it_802D4C74

/// #it_2725_Logic43_Spawned

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
