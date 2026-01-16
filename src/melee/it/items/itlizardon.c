#include "itlizardon.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/eflib.h"
#include "ef/efsync.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "MSL/math.h"
#include "sysdolphin/baselib/random.h"

void it_802CB8AC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLizardonAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDAC_itcmd_var0 = 0;
    ip->xDB0_itcmd_var1 = 0;
    ip->xDB4_itcmd_var2 = 0;
    ip->xDD4_itemVar.lizardon.x60 = -1;
    ip->xDD4_itemVar.lizardon.x64 = 0;
    ip->xDD4_itemVar.lizardon.x68 = 0.0f;
    ip->xDD4_itemVar.lizardon.x6C = 0;
    it_802CC0EC(gobj);
    it_80279CDC(gobj, attrs->x0);
    Item_8026AE84(ip, 0x2719, 0x7FU, 0x40U);
}

void it_802CB93C(Item_GObj* gobj) {}

void it_802CB940(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802CB960(Item_GObj* gobj)
{
    it_80273454(gobj);
    it_802CB994(gobj);
}

void it_802CB994(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itLizardon_UnkMotion1_Anim(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == false) {
        it_802CBAA8(gobj);
    }
    return false;
}

void itLizardon_UnkMotion1_Phys(Item_GObj* gobj)
{
    ItemAttr* ip_attr;
    Item* ip = GET_ITEM(gobj);

    if (ip->ground_or_air == GA_Air) {
        ip_attr = ip->xCC_item_attr;
        it_80272860(gobj, ip_attr->x10_fall_speed,
                    ip_attr->x14_fall_speed_max);
    }
}

bool itLizardon_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        it_8026E15C(gobj, it_802CB93C);
    } else {
        it_8026D62C(gobj, it_802CB93C);
    }
    return false;
}

static inline void it_802CBAA8_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLizardonAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.lizardon.x70 =
        attrs->x28 + HSD_Randi(attrs->x2C - attrs->x28);
}

void it_802CBAA8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLizardonAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;

    if (ip->xDD4_itemVar.lizardon.x60 == -1) {
        ip->xDD4_itemVar.lizardon.x60 = *(s32*) (void*) (&attrs->x4);
    }
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    it_802CBAA8_inline(gobj);
    ip->xDD4_itemVar.lizardon.x74[0] = attrs->x18[0];
    ip->xDD4_itemVar.lizardon.x74[1] = attrs->x18[1];
    ip->xDD4_itemVar.lizardon.x74[2] = attrs->x18[2];
    ip->xDD4_itemVar.lizardon.x74[3] = attrs->x18[3];
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    ip->on_accessory = it_802CBD24;
}

bool itLizardon_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (!it_80272C6C(gobj)) {
        if (ip->xDD4_itemVar.lizardon.x60 <= 0) {
            ip->xDD4_itemVar.lizardon.x60 = 0;
            it_802CBFE4(gobj);
        } else {
            ip->xDD4_itemVar.lizardon.x60--;
            it_802CBAA8(gobj);
        }
    }
    return false;
}

void itLizardon_UnkMotion2_Phys(Item_GObj* gobj)
{
    itLizardon_UnkMotion1_Phys(gobj);
}

bool itLizardon_UnkMotion2_Coll(Item_GObj* gobj)
{
    return itLizardon_UnkMotion1_Coll(gobj);
}

static inline void it_802CBD24_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLizardonAttributes* attrs;
    attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.lizardon.x70 =
        attrs->x28 + HSD_Randi(attrs->x2C - attrs->x28);
}

void it_802CBD24(Item_GObj* gobj)
{
    Vec3 bone_pos;
    f32 scale;
    f32 facing;
    Item* ip = GET_ITEM(gobj);
    itLizardonAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(4);

    if (ip->xDB0_itcmd_var1 != 0) {
        ip->xDD4_itemVar.lizardon.x64 ^= 1;
        ip->xDD4_itemVar.lizardon.x68 = attrs->x14;
        ip->xDB0_itcmd_var1 = 0;
    }
    if (ip->xDAC_itcmd_var0 != 0) {
        itLizardonAttributes* attrs2 =
            ip->xC4_article_data->x4_specialAttributes;
        scale = 1.0f;
        lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[0x32], NULL, &bone_pos);
        if (ip->xDD4_itemVar.lizardon.x64 != 0) {
            facing = -1.0f;
        } else {
            facing = 1.0f;
        }
        {
            f32 v = ip->xDD4_itemVar.lizardon.x68 - 1;
            ip->xDD4_itemVar.lizardon.x68 = v;
            if (!v) {
                ip->xDD4_itemVar.lizardon.x68 = attrs2->x14;
                it_802CC1CC(gobj, HSD_Randi(4) + 0xC3);
            }
        }
        {
            s32 v = ip->xDD4_itemVar.lizardon.x70 - 1;
            ip->xDD4_itemVar.lizardon.x70 = v;
            if (v < 0) {
                it_8027ADEC(0x452, gobj,
                            ip->xBBC_dynamicBoneTable->bones[0x31], 1.4f);
                it_802CBD24_inline(gobj);
            }
        }
        {
            s32 v = ip->xDD4_itemVar.lizardon.x74[0] - 1;
            ip->xDD4_itemVar.lizardon.x74[0] = v;
            if (v < 0) {
                scale = (scale / 1.4f) * ip->xCC_item_attr->x60_scale;
                efSync_Spawn(0x453, gobj,
                             ip->xBBC_dynamicBoneTable->bones[0x32], &facing,
                             &scale);
                ip->xDD4_itemVar.lizardon.x74[0] = attrs2->x18[0];
            }
        }
        {
            s32 v = ip->xDD4_itemVar.lizardon.x74[1] - 1;
            ip->xDD4_itemVar.lizardon.x74[1] = v;
            if (v < 0) {
                scale = (scale / 1.4f) * ip->xCC_item_attr->x60_scale;
                efSync_Spawn(0x454, gobj,
                             ip->xBBC_dynamicBoneTable->bones[0x32], &facing,
                             &scale);
                ip->xDD4_itemVar.lizardon.x74[1] = attrs2->x18[1];
            }
        }
        {
            s32 v = ip->xDD4_itemVar.lizardon.x74[2] - 1;
            ip->xDD4_itemVar.lizardon.x74[2] = v;
            if (v < 0) {
                scale = (scale / 1.4f) * ip->xCC_item_attr->x60_scale;
                efSync_Spawn(0x455, gobj,
                             ip->xBBC_dynamicBoneTable->bones[0x32], &facing,
                             &scale);
                ip->xDD4_itemVar.lizardon.x74[2] = attrs2->x18[2];
            }
        }
        {
            s32 v = ip->xDD4_itemVar.lizardon.x74[3] - 1;
            ip->xDD4_itemVar.lizardon.x74[3] = v;
            if (v < 0) {
                scale = (scale / 1.4f) * ip->xCC_item_attr->x60_scale;
                efSync_Spawn(0x456, gobj,
                             ip->xBBC_dynamicBoneTable->bones[0x32], &facing,
                             &scale);
                ip->xDD4_itemVar.lizardon.x74[3] = attrs2->x18[3];
            }
        }
    }
}

void it_802CBFE4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itLizardon_UnkMotion3_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        return true;
    }
    return false;
}

void itLizardon_UnkMotion3_Phys(Item_GObj* gobj)
{
    itLizardon_UnkMotion1_Phys(gobj);
}

bool itLizardon_UnkMotion3_Coll(Item_GObj* gobj)
{
    return itLizardon_UnkMotion1_Coll(gobj);
}

void it_802CC0EC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0f);
}

s32 it_802CC160(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return 0;
}

void it_802CC184(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool it_802CC1A4(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802CB960);
}

void it_802CC1CC(Item_GObj* gobj, ItemKind kind)
{
    SpawnItem spawn;
    Vec3 bone_pos;
    u8 _pad[4];
    Item* ip = GET_ITEM(gobj);
    itLizardonAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    f32 angle;
    s32 randi;

    lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[0x32], NULL, &bone_pos);
    spawn.prev_pos = bone_pos;
    it_8026BB88(gobj, &spawn.pos);
    spawn.x3C_damage = 0;
    randi = HSD_Randi(attrs->x8 - attrs->xC);
    angle = 0.017453292f * (attrs->x8 - randi);
    if (ip->xDD4_itemVar.lizardon.x64 != 0) {
        spawn.vel.x = -1.0f * (attrs->x10 * cosf(angle));
        spawn.facing_dir = -1.0f;
    } else {
        spawn.vel.x = attrs->x10 * cosf(angle);
        spawn.facing_dir = 1.0f;
    }
    spawn.vel.y = attrs->x10 * sinf(angle);
    spawn.vel.z = 0.0f;
    spawn.kind = kind;
    spawn.x0_parent_gobj = ip->owner;
    spawn.x4_parent_gobj2 = gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;
    if (Item_80268B18(&spawn) != NULL) {
        ip->xDD4_itemVar.lizardon.x6C ^= 1;
        if (ip->xDD4_itemVar.lizardon.x6C != 0) {
            switch (HSD_Randi(3)) {
            case 0:
                Item_8026AE84(ip, 0x2716, 0x7F, 0x40);
                return;
            case 1:
                Item_8026AE84(ip, 0x2717, 0x7F, 0x40);
                return;
            case 2:
                Item_8026AE84(ip, 0x2718, 0x7F, 0x40);
                break;
            }
        }
    }
}

void it_2725_Logic34_Spawned(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    void* hsd_obj = gobj->hsd_obj;
    f32 f2 = 1.0f;
    f32 f = 0.71428573f;
    PAD_STACK(16);

    f2 = f * ip->xCC_item_attr->x60_scale;
    efSync_Spawn(0x44E, gobj, hsd_obj, &ip->facing_dir, &f2);
    it_802CC5D4(gobj);
}

void it_2725_Logic35_Spawned(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    void* hsd_obj = gobj->hsd_obj;
    f32 f2 = 1.0f;
    f32 f = 0.71428573f;
    PAD_STACK(4);

    f2 = f * ip->xCC_item_attr->x60_scale;
    efSync_Spawn(0x44F, gobj, hsd_obj, &ip->facing_dir, &f2);
    it_802CC5D4(gobj);
}

void it_2725_Logic36_Spawned(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    void* hsd_obj = gobj->hsd_obj;
    f32 f2 = 1.0f;
    f32 f = 0.71428573f;
    PAD_STACK(4);

    f2 = f * ip->xCC_item_attr->x60_scale;
    efSync_Spawn(0x450, gobj, hsd_obj, &ip->facing_dir, &f2);
    it_802CC5D4(gobj);
}

void it_2725_Logic37_Spawned(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    void* hsd_obj = gobj->hsd_obj;
    f32 f2 = 1.0f;
    f32 f = 0.71428573f;
    PAD_STACK(4);

    f2 = f * ip->xCC_item_attr->x60_scale;
    efSync_Spawn(0x451, gobj, hsd_obj, &ip->facing_dir, &f2);
    it_802CC5D4(gobj);
}

void it_2725_Logic37_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool it_2725_Logic37_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_2725_Logic37_HitShield(Item_GObj* gobj)
{
    return true;
}

bool it_2725_Logic37_Absorbed(Item_GObj* gobj)
{
    return true;
}

void it_802CC5D4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLizardonAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    it_80275158(gobj, attrs->x0);
    it_80274740(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_8026B3A8(gobj);
}

bool it_802CC650(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

void it_802CC684(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLizardonAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;

    ip->x40_vel.x *= attrs->x4;
    ip->x40_vel.y *= attrs->x4;
    ip->x40_vel.z *= attrs->x4;
}

bool it_802CC6C4(Item_GObj* gobj)
{
    return it_8026DFB0(gobj);
}
