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

void it_2725_Logic18_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHououAttr* attr = ip->xC4_article_data->x4_specialAttributes;
    *(Vec3*) &ip->xDD4_itemVar.pokemon.x64 = ip->pos;
    ip->facing_dir = 0.0F;
    ip->xDAC_itcmd_var0 = 0;
    ip->xDB0_itcmd_var1 = 0;
    ip->xDD4_itemVar.pokemon.timer = attr->x14;
    ip->xDCC_flag.b3 = false;
    it_802D2BE0(gobj);
    it_80279CDC(gobj, attr->timer);
    ip->xDD4_itemVar.pokemon.xE44 = 0.0F;
}

void it_802D25B8(void) {}

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
    ip->xDD4_itemVar.pokemon.xE44 = 0.0f;
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
        ip->xDD4_itemVar.pokemon.xE44 += attr->x8;
    } else {
        ip->xDD4_itemVar.pokemon.xE44 += attr->xC;
    }

    ip->x40_vel.y += ip->xDD4_itemVar.pokemon.xE44;

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

    timer = ip->xDD4_itemVar.pokemon.timer;
    ip->xDD4_itemVar.pokemon.timer = timer - 1;

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
    ip->xDD4_itemVar.pokemon.xE44 = attr->x18;
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

    ip->xDD4_itemVar.pokemon.xE44 += attr->x1C;
    ip->x40_vel.y += ip->xDD4_itemVar.pokemon.xE44;

    if (ip->pos.y < (*(f32*) ((u8*) ip + 0xE3C)) - 1.0f) {
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
        it_8027ADEC(0x46F, gobj, ip->xBBC_dynamicBoneTable->bones[16],
                    1.3F);
        it_8027ADEC(0x46F, gobj, ip->xBBC_dynamicBoneTable->bones[17],
                    1.3F);
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
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802D25B8);
}

/// #it_802D2D2C

void it_2725_Logic42_Spawned(Item_GObj* item_gobj)
{
    Item* item;
    itHououAttr* attr;
    PAD_STACK(8);

    item = GET_ITEM((HSD_GObj*) item_gobj);
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

    if (mpLib_80054ED8(ip->xDD4_itemVar.pokemon.timer)) {
        mpGetSpeed(ip->xDD4_itemVar.pokemon.timer, &ip->pos, &sp10);
        ip->pos.x += sp10.x;
        ip->pos.y += sp10.y;
        ip->pos.z += sp10.z;
    }
}

bool it_802D2FE8(Item_GObj* gobj)
{
    return it_8026DA08(gobj);
}
