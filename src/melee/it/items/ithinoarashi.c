#include "ithinoarashi.h"

#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/it_266F.h"

/* 2D60C8 */ static bool itHinoarashi_UnkMotion2_Anim(Item_GObj* gobj);

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
