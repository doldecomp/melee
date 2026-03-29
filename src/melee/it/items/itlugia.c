#include "itlugia.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/eflib.h"
#include "gr/stage.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"

void it_2725_Logic17_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLugiaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.lugia.x64 = ip->pos;
    ip->facing_dir = it_804DD450;
    ip->xDAC_itcmd_var0 = 0;
    ip->xDD4_itemVar.lugia.x60 = attrs->x14;
    ip->xDCC_flag.b3 = 0;
    it_802D1D40(gobj);
    it_80279CDC(gobj, attrs->x0);
    ip->xDD4_itemVar.lugia.xE50.x = it_804DD450;
}

void it_802D14D0(void) {}

void itLugia_Logic17_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool itLugia_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);       // r31
    HSD_JObj* jobj = GET_JOBJ(gobj); // r3
    HSD_JObj* child;

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    it_8027A160(child, ip);

    if (!it_80272C6C(gobj)) {
        it_802D1580(gobj);
    }

    return false;
}

void itLugia_UnkMotion1_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itLugia_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D1580(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLugiaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.lugia.xE50.x = -attrs->x4;
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itLugia_UnkMotion2_Anim(Item_GObj* gobj)
{
    HSD_JObj* bone;
    Item* item = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    if (jobj == NULL) {
        bone = NULL;
    } else {
        bone = jobj->child;
    }

    it_8027A160(bone, item);
    return false;
}

void itLugia_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLugiaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    it_8027A344(gobj);
    if (it_80272C6C(gobj)) {
        ip->xDD4_itemVar.lugia.xE50.x += attrs->x8;
    } else {
        ip->xDD4_itemVar.lugia.xE50.x += attrs->xC;
    }
    ip->x40_vel.y += ip->xDD4_itemVar.lugia.xE50.x;
    if (ip->pos.y > Stage_GetBlastZoneTopOffset()) {
        ip->x40_vel.y = it_804DD450;
        it_802D16D4(gobj);
    }
}

bool itLugia_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D16D4(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
}

bool itLugia_UnkMotion3_Anim(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* child;

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    it_8027A160(child, ip);

    if (!it_80272C6C(gobj)) {
        it_802D16D4(gobj);
    }

    return false;
}

void itLugia_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLugiaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    it_8027A344(gobj);
    if (ip->xDD4_itemVar.lugia.x60-- != 0) {
        ip->x40_vel.z = attrs->x10;
    } else {
        ip->x40_vel.z = 0.0F;
        it_802D1830(gobj);
    }
}

bool itLugia_UnkMotion3_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D1830

bool itLugia_UnkMotion4_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child;

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    it_8027A160(child, ip);

    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
        ip->entered_hitlag = efLib_PauseAll;
        ip->exited_hitlag = efLib_ResumeAll;
    }

    return false;
}

void itLugia_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLugiaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    it_8027A344(gobj);
    ip->xDD4_itemVar.lugia.xE50.x += attrs->x18;
    ip->x40_vel.y = ip->xDD4_itemVar.lugia.xE50.x;
    if (ip->x40_vel.y > it_804DD450) {
        ip->x40_vel.y = it_804DD450;
        it_802D1A44(gobj);
    }
}

bool itLugia_UnkMotion4_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D1A44(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLugiaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    Vec3 pos;

    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    ip->xDD4_itemVar.lugia.xE50.y = it_804DD46C;
    ip->xDD4_itemVar.lugia.xE50.z = it_804DD470;
    ip->xDD4_itemVar.lugia.x88 = it_804DD474;
    lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[25], NULL, &pos);
    ip->xDD4_itemVar.lugia.x8C = ip->xDD4_itemVar.lugia.x64;
    ip->xDD4_itemVar.lugia.x8C.y += attrs->x40;
    ip->xDD4_itemVar.lugia.x70 = pos;
    ip->xDD4_itemVar.lugia.xA4 = 0;
    ip->on_accessory = (HSD_GObjEvent) it_802D1BBC;
    ip->xDCC_flag.b3 = 1;
}

bool itLugia_UnkMotion5_Anim(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Item* ip = GET_ITEM(gobj);

    if (jobj == NULL) {
        jobj = NULL;
    } else {
        jobj = jobj->child;
    }
    it_8027A160(jobj, ip);
    if (!it_80272C6C(gobj)) {
        return true;
    }
    return false;
}

void itLugia_UnkMotion5_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itLugia_UnkMotion5_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D1BBC

void it_802D1D40(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0f);
}

bool it_802D1DB4(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void it_802D1DD8(Item_GObj* gobj)
{
    if (it_8027A09C(gobj)) {
        Item* old_ip = GET_ITEM(gobj);
        Item* ip;
        it_80273454(gobj);
        ip = GET_ITEM(gobj);
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        ip->entered_hitlag = efLib_PauseAll;
        ip->exited_hitlag = efLib_ResumeAll;
        old_ip->xDD1_flag.b1 = 1;
    }
}

bool it_802D1E64(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802D14D0);
}

Item_GObj* it_802D1E8C(Item_GObj* gobj, ItemKind kind, f32 param)
{
    SpawnItem spawn;
    Item* ip = GET_ITEM(gobj);

    spawn.prev_pos = ip->xDD4_itemVar.lugia.x70;
    it_8026BB88(gobj, &spawn.pos);
    spawn.facing_dir = ip->facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel = it_802D1F64(gobj, param);
    spawn.kind = kind;
    spawn.x0_parent_gobj = ip->owner;
    spawn.x4_parent_gobj2 = gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;
    return Item_80268B18(&spawn);
}

/// #it_802D1F64

/// #it_802D208C

void itLugia_Logic39_Spawned(Item_GObj* gobj)
{
    it_8027ADEC(0x465, gobj, HSD_GObjGetHSDObj(gobj), it_804DD490);
    it_802D23F4(gobj);
}

void itLugia_Logic40_Spawned(Item_GObj* gobj)
{
    it_8027ADEC(0x466, gobj, HSD_GObjGetHSDObj(gobj), it_804DD490);
    it_802D23F4(gobj);
}

void itLugia_Logic41_Spawned(Item_GObj* gobj)
{
    it_8027ADEC(0x467, gobj, HSD_GObjGetHSDObj(gobj), it_804DD490);
    it_802D23F4(gobj);
}

void it_802D23D4(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802D23F4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLugiaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xD44_lifeTimer = attrs->x0;
    it_80274740(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_8026B3A8(gobj);
}

bool it_802D246C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

void it_802D24A0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32* attrs = ip->xC4_article_data->x4_specialAttributes;
    f32 multiplier = 1.0f;

    switch (ip->kind) {
    case 0xC8:
        multiplier = attrs[1];
        break;
    case 0xC9:
        multiplier = attrs[2];
        break;
    case 0xCA:
        multiplier = attrs[3];
        break;
    }

    ip->x40_vel.z *= multiplier;
}

bool it_802D24FC(Item_GObj* gobj)
{
    return it_8026DA08(gobj);
}
