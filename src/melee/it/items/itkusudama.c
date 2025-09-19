#include "itkusudama.h"

#include <placeholder.h>
#include <platform.h>

#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/it_266F.h"
#include "it/item.h"

extern f32 it_804DC9E4;

/// #it_802896CC

/// #it_3F14_Logic4_Spawned

/// #it_802897C8

/// #it_80289910

/// #it_80289A00

/// #it_80289B50

/// #it_80289BE8

/// #it_8028A114

/// #it_8028A190

bool itKusudama_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_802897C8(it_804DC9E4);
    return false;
}

void itKusudama_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itKusudama_UnkMotion0_Coll

/// #itKusudama_UnkMotion1_Anim

void itKusudama_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itKusudama_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026DA08(gobj);
    return false;
}

/// #it_8028A3CC

bool itKusudama_UnkMotion2_Anim(Item_GObj* gobj)
{
    it_802897C8(it_804DC9E4);
    return false;
}

/// #itKusudama_UnkMotion2_Phys

/// #itKusudama_UnkMotion2_Coll

/// #it_8028A544

/// #itKusudama_UnkMotion3_Anim

void itKusudama_UnkMotion3_Phys(Item_GObj* gobj) {}

/// #itKusudama_UnkMotion3_Coll

void it_3F14_Logic4_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 4, ITEM_ANIM_UPDATE);
}

bool itKusudama_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itKusudama_UnkMotion4_Phys(Item_GObj* gobj) {}

/// #it_3F14_Logic4_Thrown

bool itKusudama_UnkMotion6_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itKusudama_UnkMotion6_Phys

/// #itKusudama_UnkMotion5_Coll

/// #it_3F14_Logic4_Dropped

/// #itKusudama_UnkMotion6_Coll

/// #it_8028AC74

bool itKusudama_UnkMotion7_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void itKusudama_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itKusudama_UnkMotion7_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_8028AD44

/// #itKusudama_UnkMotion8_Anim

void itKusudama_UnkMotion8_Phys(Item_GObj* gobj) {}

bool itKusudama_UnkMotion8_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_3F14_Logic4_DmgDealt

/// #it_3F14_Logic4_Clanked

/// #it_3F14_Logic4_HitShield

/// #it_3F14_Logic4_Reflected

/// #it_3F14_Logic4_DmgReceived

void it_3F14_Logic4_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
