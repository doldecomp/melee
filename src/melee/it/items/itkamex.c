#include "itkamex.h"

#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lbaudio_ax.h"

#include <baselib/jobj.h>

ItemStateTable it_803F7B08[] = {
    { 0, it_802CA5D8, it_802CA618, it_802CA654 },
    { 1, itKamex_UnkMotion1_Anim, itKamex_UnkMotion1_Phys,
      itKamex_UnkMotion1_Coll },
    { 2, itKamex_UnkMotion2_Anim, itKamex_UnkMotion2_Phys,
      itKamex_UnkMotion2_Coll },
    { -1, itKamex_UnkMotion3_Anim, itKamex_UnkMotion3_Phys,
      itKamex_UnkMotion3_Coll },
};

ItemStateTable it_803F7B48[] = { {
    0,
    it_802CAE60,
    it_802CAE94,
    it_802CAFB4,
} };

void it_802CA49C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itPokemonAttributes* sa = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(16);

    it_80279C48(gobj);
    ip->xDD4_itemVar.pokemon.timer = -1;
    ip->xDBC_itcmd_var4.flags.x0 = false;
    ip->xDD4_itemVar.pokemon.x64 = 0;
    ip->xDD4_itemVar.pokemon.x68 = 0.0f;
    ip->xDD4_itemVar.pokemon.x6C = 0.0f;
    it_80279CDC(gobj, sa->x0);
    it_802CAA40(gobj);
    Item_8026AE84(ip, 0x271E, 127, 64);
}

void it_802CA534(Item_GObj* gobj) {}

void it_802CA538(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802CA558(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_80273454(gobj);
    it_802CA58C(gobj);
}

void it_802CA58C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool it_802CA5D8(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == 0) {
        it_802CA6A0(gobj);
    }
    return false;
}

void it_802CA618(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        it_80272860(gobj, ip->xCC_item_attr->x10_fall_speed,
                    ip->xCC_item_attr->x14_fall_speed_max);
    }
}

bool it_802CA654(Item_GObj* gobj)
{
    if (GET_ITEM(gobj)->ground_or_air == GA_Air) {
        it_8026E15C(gobj, it_802CA534);
    } else {
        it_8026D62C(gobj, it_802CA534);
    }
    return false;
}

void it_802CA6A0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itKamexAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;

    if (ip->xDD4_itemVar.pokemon.timer == -1) {
        ip->xDD4_itemVar.pokemon.timer = attrs->timer;
        ip->xDD4_itemVar.pokemon.x68 = attrs->x18;
        ip->xDD4_itemVar.pokemon.x6C = attrs->x1C;
    }
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    ip->on_accessory = it_802CA8DC;
}

bool itKamex_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    PAD_STACK(8);

    if (!it_80272C6C(gobj)) {
        if (ip->xDD4_itemVar.pokemon.timer <= 0) {
            ip->xDD4_itemVar.pokemon.timer = 0;
            ip->x40_vel.x = 0.0f;
            it_802CA938(gobj);
        } else {
            ip->xDD4_itemVar.pokemon.timer--;
            it_802CA6A0(gobj);
        }
    }
    return false;
}

void itKamex_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;

    if (ip->x40_vel.x) {
        if ((ip->x40_vel.x > 0.0f && ip->facing_dir <= 0.0f) ||
            (ip->x40_vel.x <= 0.0f && ip->facing_dir > 0.0f))
        {
            ip->x40_vel.x += ip->xDD4_itemVar.pokemon.x6C * ip->facing_dir;
        }
    }
    if (ip->ground_or_air == GA_Air) {
        it_80272860(gobj, ip->xCC_item_attr->x10_fall_speed,
                    ip->xCC_item_attr->x14_fall_speed_max);
    }
}

bool itKamex_UnkMotion1_Coll(Item_GObj* gobj)
{
    if (GET_ITEM(gobj)->ground_or_air == GA_Air) {
        it_8026E15C(gobj, it_802CA534);
    } else {
        it_8026D62C(gobj, it_802CA534);
    }
    return false;
}

void it_802CA8DC(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    if (ip->xDBC_itcmd_var4.flags.x0) {
        it_802CAB10(gobj);
        ip->x40_vel.x = ip->xDD4_itemVar.pokemon.x68 * -ip->facing_dir;
        ip->xDBC_itcmd_var4.flags.x0 = false;
    }
}

void it_802CA938(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itKamex_UnkMotion2_Anim(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == 0) {
        return true;
    }
    return false;
}

void itKamex_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        it_80272860(gobj, ip->xCC_item_attr->x10_fall_speed,
                    ip->xCC_item_attr->x14_fall_speed_max);
    }
}

bool itKamex_UnkMotion2_Coll(Item_GObj* gobj)
{
    if (GET_ITEM(gobj)->ground_or_air == GA_Air) {
        it_8026E15C(gobj, it_802CA534);
    } else {
        it_8026D62C(gobj, it_802CA534);
    }
    return false;
}

void it_802CAA40(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itKamex_UnkMotion3_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itKamex_UnkMotion3_Phys(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool itKamex_UnkMotion3_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802CA558);
}

void it_802CAB10(Item_GObj* gobj)
{
    SpawnItem spawn;
    Item* ip = GET_ITEM(gobj);
    itKamexAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;

    spawn.prev_pos = ip->pos;
    spawn.prev_pos.x += attrs->x8 * ip->facing_dir;
    spawn.prev_pos.y += attrs->xC;
    if (ip->xDD4_itemVar.pokemon.x64 != 0) {
        spawn.prev_pos.z += -1.0f * (attrs->x10 * ip->facing_dir);
    } else {
        spawn.prev_pos.z += attrs->x10 * ip->facing_dir;
    }
    it_8026BB88(gobj, &spawn.pos);
    spawn.facing_dir = ip->facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = attrs->x14 * ip->facing_dir;
    spawn.vel.y = 0.0f;
    spawn.vel.z = 0.0f;
    spawn.kind = Pokemon_Kamex_HydroPump;
    ip->xDD4_itemVar.pokemon.x64 ^= 1;
    spawn.x0_parent_gobj = ip->owner;
    spawn.x4_parent_gobj2 = (HSD_GObj*) gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    if (Item_80268B18(&spawn) != NULL) {
        if (ip->facing_dir == 1.0f) {
            lbAudioAx_800263E8(3.0f, gobj, 1, 0x271D, 0x7F, 0x7F, 0, 0x7F,
                               0x3C, 0, -1);
            return;
        }
        lbAudioAx_800263E8(3.0f, gobj, 1, 0x271C, 0x7F, 0x7F, 0, 0x7F, 0x3C, 0,
                           -1);
    }
}

void it_2725_Logic31_Spawned(Item_GObj* gobj)
{
    HSD_JObj* jobj;
    Vec3 scale;
    Item* ip = gobj->user_data;
    itKamexAttributes* sa = ip->xC4_article_data->x4_specialAttributes;

    jobj = gobj->hsd_obj;
    ip->xD44_lifeTimer = sa->x0;
    it_80274740(gobj);
    it_802CADF0(gobj);
    it_8026B3A8(gobj);
    scale.x = 0.2f;
    scale.y = 0.2f;
    scale.z = 0.2f;
    HSD_JObjSetScale(jobj, &scale);
}

bool itKamex_Logic31_HitShield(Item_GObj* arg0)
{
    return true;
}

bool itKamex_Logic31_DmgDealt(Item_GObj* arg0)
{
    return false;
}

void itKamex_Logic31_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802CADF0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);

    it_8027ADEC(0x46A, gobj, jobj, 1.2f);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool it_802CAE60(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (--ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

void it_802CAE94(Item_GObj* gobj)
{
    HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);

    if (jobj->scale.x < 1.0) {
        Vec3 scale;
        HSD_JObjGetScale(jobj, &scale);
        scale.x += 0.06;
        scale.y += 0.06;
        scale.z += 0.06;
        HSD_JObjSetScale(jobj, &scale);
    }
}

bool it_802CAFB4(Item_GObj* gobj)
{
    return it_8026DFB0(gobj);
}
