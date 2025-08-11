#include "itmew.h"

#include "ef/eflib.h"
#include "gr/stage.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <baselib/gobj.h>
#include <baselib/random.h>

/* 2D3B8C */ static void it_802D3B8C(Item_GObj* gobj);
/* 2D3BE0 */ static void it_802D3BE0(Item_GObj* gobj);
/* 2D3C50 */ static bool itMew_UnkMotion1_Anim(Item_GObj* gobj);
/* 2D3C90 */ static void itMew_UnkMotion1_Phys(Item_GObj* gobj);
/* 2D3C94 */ static bool itMew_UnkMotion1_Coll(Item_GObj* gobj);
/* 2D3C9C */ static void it_802D3C9C(Item_GObj* gobj);
/* 2D3D28 */ static bool itMew_UnkMotion2_Anim(Item_GObj* gobj);
/* 2D3D6C */ static void itMew_UnkMotion2_Phys(Item_GObj* gobj);
/* 2D3D8C */ static bool itMew_UnkMotion2_Coll(Item_GObj* gobj);
/* 2D3D94 */ static void it_802D3D94(Item_GObj* gobj);
/* 2D3E08 */ static bool itMew_UnkMotion0_Anim(Item_GObj* gobj);
/* 2D3E2C */ static void itMew_UnkMotion0_Phys(Item_GObj* gobj);
/* 2D3ED0 */ static bool itMew_UnkMotion0_Coll(Item_GObj* gobj);

ItemStateTable it_803F80C8[] = {
    { 0, itMew_UnkMotion0_Anim, itMew_UnkMotion0_Phys, itMew_UnkMotion0_Coll },
    { 1, itMew_UnkMotion1_Anim, itMew_UnkMotion1_Phys, itMew_UnkMotion1_Coll },
    { 2, itMew_UnkMotion2_Anim, itMew_UnkMotion2_Phys, itMew_UnkMotion2_Coll },
};

void it_2725_Logic22_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    MewVars* attr = ip->xC4_article_data->x4_specialAttributes;

    ip->facing_dir = 0.0F;
    it_802D3D94(gobj);
    it_80279CDC(gobj, attr->x0);
}

void it_802D3B6C(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802D3B8C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    it_80273454(gobj);
    it_802D3BE0(gobj);
    Item_8026AE84(ip, 0x2729, 0x7F, 0x40);
}

void it_802D3BE0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);

    it_8027ADEC(0x46B, gobj, jobj, 2.8F);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itMew_UnkMotion1_Anim(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == false) {
        it_802D3C9C(gobj);
    }
    return false;
}

void itMew_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itMew_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D3C9C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    MewVars* attr = ip->xC4_article_data->x4_specialAttributes;

    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    if (HSD_Randi(2) != 0) {
        ip->x40_vel.x = attr->x4;
    } else {
        ip->x40_vel.x = -attr->x4;
    }
    ip->x40_vel.y = attr->x8;
}

bool itMew_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->pos.y > Stage_GetBlastZoneTopOffset()) {
        return true;
    }
    return false;
}

void itMew_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    MewVars* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.y += attr->xC;
}

bool itMew_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D3D94(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0F);
}

bool itMew_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itMew_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip_arg;
    Item* ip;

    if (it_8027A09C(gobj) != false) {
        ip_arg = GET_ITEM(gobj);
        it_80273454(gobj);
        ip = GET_ITEM(gobj);
        it_8027ADEC(0x46B, gobj, HSD_GObjGetHSDObj(gobj), 2.8F);
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        ip->entered_hitlag = efLib_PauseAll;
        ip->exited_hitlag = efLib_ResumeAll;
        Item_8026AE84(ip_arg, 0x2729, 0x7F, 0x40);
    }
}

bool itMew_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, it_802D3B8C);
}
