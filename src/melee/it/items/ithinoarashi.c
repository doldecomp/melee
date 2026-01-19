#include "ithinoarashi.h"

#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/* 2D60C8 */ static bool itHinoarashi_UnkMotion2_Anim(Item_GObj* gobj);

void it_802D5E4C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0f);
    it_8026BDB4(gobj);
}

bool it_802D5EC8(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itHinoarashi_UnkMotion1_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itHinoarashi_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026DA08(gobj);
    return false;
}

bool itHinoarashi_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void it_802D5EEC(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

void it_802D5F0C(Item_GObj* gobj)
{
    it_8027A118(gobj, it_802D5F34);
}

void it_802D61A8(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void itHinoarashi_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}
