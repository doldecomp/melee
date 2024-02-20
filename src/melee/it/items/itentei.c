#include "itentei.h"

#include "cm/camera.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/types.h"

void it_802CF44C(Item_GObj* gobj)
{
    return;
}

void it_802CF450(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802CF470(Item_GObj* gobj)
{
    Item* it = GET_ITEM((HSD_GObj*) gobj);
    PAD_STACK(8);

    Camera_80030E44(4, NULL);
    Item_8026AE84(it, 0x9, 0x7F, 0x40);
    it_80273454(gobj);
    it_802CF4D4(gobj);
}

void it_802CF4D4(Item_GObj* gobj) {}

void it_802CF544(Item_GObj* gobj) {}

void it_802CF640(Item_GObj* gobj)
{
    Item* it = GET_ITEM((HSD_GObj*) gobj);
    if (it->ground_or_air == GA_Air) {
        it_80272860(gobj, it->xCC_item_attr->x10_fall_speed,
                    it->xCC_item_attr->x14_fall_speed_max);
    }
}

bool it_802CF67C(Item_GObj* gobj)
{
    Item* it = GET_ITEM((HSD_GObj*) gobj);
    if (it->ground_or_air == GA_Air) {
        it_8026E248(gobj, it_802CF44C);
    } else {
        it_8026D62C(gobj, it_802CF44C);
    }
    return false;
}

bool it_802CF7A8(Item_GObj* gobj)
{
    it_80279FF8(gobj);

    return false;
}

bool it_802CF7CC(Item_GObj* gobj)
{
    return it_8027A09C(gobj);
}

void it_802CF7EC(Item_GObj* gobj)
{
    it_8027A118(gobj, it_802CF470);
}
