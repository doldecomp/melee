#include "ittosakinto.h"

#include "it/it_26B1.h"
#include "it/it_266F.h"
#include "it/it_2725.h"

void it_802C8FC4(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool itTosakinto_UnkMotion4_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

bool itTosakinto_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802C90E8);
    return false;
}

void itTosakinto_UnkMotion4_Phys(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

void itTosakinto_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8027A118(gobj, it_802C8FE4);
}
