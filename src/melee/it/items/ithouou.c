#include "ithouou.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/eflib.h"
#include "gr/stage.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "mp/mplib.h"

ItemStateTable it_803F7F58[] = {
    { 0, it_802D2C54, it_802D2C78, it_802D2D04 },
    { 1, itHouou_UnkMotion1_Anim, itHouou_UnkMotion1_Phys,
      itHouou_UnkMotion1_Coll },
    { 2, itHouou_UnkMotion2_Anim, itHouou_UnkMotion2_Phys,
      itHouou_UnkMotion2_Coll },
    { 3, itHouou_UnkMotion3_Anim, itHouou_UnkMotion3_Phys,
      itHouou_UnkMotion3_Coll },
    { 4, itHouou_UnkMotion4_Anim, itHouou_UnkMotion4_Phys,
      itHouou_UnkMotion4_Coll },
    { 5, itHouou_UnkMotion5_Anim, itHouou_UnkMotion5_Phys,
      itHouou_UnkMotion5_Coll },
};

ItemStateTable it_803F7FB8[] = { {
    0,
    it_802D2F3C,
    it_802D2F70,
    it_802D2FE8,
} };

void it_2725_Logic18_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHououAttr* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.houou.start_pos = ip->pos;
    ip->facing_dir = 0.0F;
    ip->xDAC_itcmd_var0 = 0;
    ip->xDB0_itcmd_var1 = 0;
    ip->xDD4_itemVar.houou.timer = attr->x14;
    ip->xDCC_flag.b3 = false;
    it_802D2BE0(gobj);
    it_80279CDC(gobj, attr->timer);
    ip->xDD4_itemVar.houou.vel_accum = 0.0F;
}

void it_802D25B8(HSD_GObj* gobj) {}

void it_802D25BC(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool itHouou_UnkMotion1_Anim(Item_GObj* gobj)
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
        it_802D2668(gobj);
    }

    return false;
}

void itHouou_UnkMotion1_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itHouou_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D2668(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.houou.vel_accum = 0.0f;
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itHouou_UnkMotion2_Anim(Item_GObj* gobj)
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

void itHouou_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHououAttr* attr = ip->xC4_article_data->x4_specialAttributes;

    it_8027A344(gobj);

    if (it_80272C6C(gobj)) {
        ip->xDD4_itemVar.houou.vel_accum += attr->x8;
    } else {
        ip->xDD4_itemVar.houou.vel_accum += attr->xC;
    }

    ip->x40_vel.y += ip->xDD4_itemVar.houou.vel_accum;

    if (ip->pos.y > Stage_GetBlastZoneTopOffset()) {
        ip->x40_vel.y = 0.0F;
        it_802D27B0(gobj);
    }
}

bool itHouou_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D27B0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itHouou_UnkMotion3_Anim(Item_GObj* gobj)
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
        Item* ip2 = GET_ITEM(gobj);
        Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
        ip2->entered_hitlag = efLib_PauseAll;
        ip2->exited_hitlag = efLib_ResumeAll;
    }

    return false;
}

void itHouou_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHououAttr* attr = ip->xC4_article_data->x4_specialAttributes;
    s32 timer;

    it_8027A344(gobj);

    timer = ip->xDD4_itemVar.houou.timer;
    ip->xDD4_itemVar.houou.timer = timer - 1;

    if (timer != 0) {
        ip->x40_vel.z = attr->x10;
        return;
    }

    ip->x40_vel.z = 0.0f;
    it_802D290C(gobj);
}

bool itHouou_UnkMotion3_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D290C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHououAttr* attr = ip->xC4_article_data->x4_specialAttributes;
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    ip->xDD4_itemVar.houou.vel_accum = attr->x18;
}

bool itHouou_UnkMotion4_Anim(Item_GObj* gobj)
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
        it_802D2A58(gobj);
    }

    return false;
}

void itHouou_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHououAttr* attr = ip->xC4_article_data->x4_specialAttributes;

    it_8027A344(gobj);

    ip->xDD4_itemVar.houou.vel_accum += attr->x1C;
    ip->x40_vel.y += ip->xDD4_itemVar.houou.vel_accum;

    if (ip->pos.y < ip->xDD4_itemVar.houou.start_pos.y - 10.0f) {
        ip->x40_vel.y = 0.0f;
    }
}

bool itHouou_UnkMotion4_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D2A58(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    ip->on_accessory = (HSD_GObjEvent) it_802D2B4C;
    ip->xDCC_flag.b3 = true;
}

bool itHouou_UnkMotion5_Anim(Item_GObj* gobj)
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

void itHouou_UnkMotion5_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itHouou_UnkMotion5_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D2B4C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xDAC_itcmd_var0 != 0) {
        ip->xDAC_itcmd_var0 = 0;
        it_8027ADEC(0x46F, gobj, ip->xBBC_dynamicBoneTable->bones[16], 1.3F);
        it_8027ADEC(0x46F, gobj, ip->xBBC_dynamicBoneTable->bones[17], 1.3F);
    }

    if (ip->xDB0_itcmd_var1 != 0) {
        ip->xDB0_itcmd_var1 = 0;
        it_802D2D2C(gobj);
    }
}

void it_802D2BE0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0f);
}

bool it_802D2C54(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void it_802D2C78(Item_GObj* gobj)
{
    if (it_8027A09C(gobj)) {
        Item* ip = GET_ITEM(gobj);
        Item* ip2;
        it_80273454(gobj);
        ip2 = GET_ITEM(gobj);
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        ip2->entered_hitlag = efLib_PauseAll;
        ip2->exited_hitlag = efLib_ResumeAll;
        ip->xDD1_flag.b1 = true;
    }
}

bool it_802D2D04(Item_GObj* gobj)
{
    return it_8027A118(gobj, it_802D25B8);
}

void it_802D2D2C(Item_GObj* gobj)
{
    u8 _pad[8];
    SpawnItem spawn;
    Vec3 hit_pos;
    Vec3 tmp;
    Item_GObj* new_gobj;
    int line_id;
    Item* ip = GET_ITEM(gobj);

    tmp = ip->xDD4_itemVar.houou.start_pos;
    if (mpCheckAllRemap(&hit_pos, &line_id, NULL, NULL, -1, -1, tmp.x, tmp.y,
                        tmp.x, Stage_GetBlastZoneBottomOffset()) ||
        mpCheckAllRemap(&hit_pos, &line_id, NULL, NULL, -1, -1, tmp.x,
                        Stage_GetBlastZoneTopOffset(), tmp.x, tmp.y))
    {
        spawn.prev_pos = hit_pos;
        spawn.pos = ip->xDD4_itemVar.houou.start_pos;
        spawn.facing_dir = ip->facing_dir;
        spawn.x3C_damage = 0;
        spawn.vel.y = spawn.vel.x = 0.0f;
        spawn.vel.z = 0.0f;
        spawn.kind = Pokemon_Houou_SacredFire;
        spawn.x0_parent_gobj = ip->owner;
        spawn.x4_parent_gobj2 = gobj;
        spawn.x44_flag.b0 = true;
        spawn.x40 = 0;
        new_gobj = Item_80268B18(&spawn);
        GET_ITEM(new_gobj)->xDD4_itemVar.houou.timer = line_id;
    }
}

void it_2725_Logic42_Spawned(Item_GObj* item_gobj)
{
    Item* item;
    itHououAttr* attr;
    PAD_STACK(8);

    item = GET_ITEM(item_gobj);
    attr = item->xC4_article_data->x4_specialAttributes;
    if ((item_gobj && item_gobj) && item_gobj) {
    }
    item->xD44_lifeTimer = attr->timer;
    it_80274740(item_gobj);
    it_802D2EF0(item_gobj);
    it_8026B3A8(item_gobj);
}

void it_802D2ED0(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802D2EF0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool it_802D2F3C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

void it_802D2F70(Item_GObj* gobj)
{
    Vec3 sp10;
    Item* ip = GET_ITEM(gobj);

    if (mpLib_80054ED8(ip->xDD4_itemVar.houou.timer)) {
        mpGetSpeed(ip->xDD4_itemVar.houou.timer, &ip->pos, &sp10);
        ip->pos.x += sp10.x;
        ip->pos.y += sp10.y;
        ip->pos.z += sp10.z;
    }
}

bool it_802D2FE8(Item_GObj* gobj)
{
    return it_8026DA08(gobj);
}
