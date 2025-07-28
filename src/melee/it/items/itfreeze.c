#include "itfreeze.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

/// #it_8028EB88

/// #it_8028EC98

void it_8028ECE0(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.freeze.unk_1C = 0;
}

/// #it_8028ECF0

/// #it_8028ED10

/// #it_8028ED50

/// #it_8028EDBC

/// #it_8028EF34

bool it_8028EF88(void)
{
    return false;
}

/// #it_8028EF90

/// #it_8028EFB0

/// #it_8028F1D8

bool it_8028F200(void)
{
    return false;
}

/// #it_8028F208

/// #it_8028F238

void it_8028F2B4(Item_GObj* gobj) 
{
    Item* item = gobj->user_data;
    Item_GObj* linked;
    
    if ((linked = (Item_GObj*)item->xDD4_itemVar.foxblaster.xDF0) != NULL) {
        it_802E37A4(linked);
        item->xDD4_itemVar.foxblaster.xDF0 = NULL;
    }
    
    Item_80268E5C((HSD_GObj*) gobj, 2, ITEM_ANIM_UPDATE);
}

bool it_8028F310(void)
{
    return false;
}

void it_8028F318(Item_GObj* gobj) 
{
    Item_80268E5C((HSD_GObj*) gobj, 1, 6);
}

void it_8028F340(Item_GObj* gobj) 
{
    Item_80268E5C((HSD_GObj*) gobj, 3, 6);
}

s32 it_8028F368(Item_GObj* gobj) 
{
    Item* ip;
    ItemAttr* it_attr;

    ip = gobj->user_data;
    it_attr = ip->xCC_item_attr;
    it_80272860(gobj, it_attr->x10_fall_speed, it_attr->x14_fall_speed_max);
}

s32 it_8028F398(Item_GObj* gobj) 
{
    if (it_8026DAA8(gobj) != 0) 
    {
        return 1;
    }
    return 0;
}

bool it_8028F3CC(Item_GObj* arg0)
{
    return true;
}

bool it_8028F3D4(Item_GObj* arg0)
{
    return true;
}

bool it_8028F3DC(Item_GObj* arg0)
{
    return true;
}

bool it_8028F3E4(Item_GObj* arg0)
{
    return true;
}

bool it_8028F3EC(Item_GObj* gobj) 
{
    return it_80273030(gobj);
}

bool it_8028F40C(Item_GObj* gobj) 
{
    return itColl_BounceOffShield(gobj);
}

bool it_8028F42C(Item_GObj* arg0)
{
    return true;
}

/// #it_8028F434

bool it_8028F4AC(void)
{
    return false;
}

/// #it_8028F4B4

/// #it_8028F560

/// #it_8028F7C8

bool it_8028F828(void)
{
    return false;
}

void it_8028F830(void) {}

/// #it_8028F834

void it_8028F8C4(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_8028F8E4

/// #it_8028F968

void it_8028F9B8(Item_GObj* gobj) 
{
    Item_8026A8EC(gobj);
}
