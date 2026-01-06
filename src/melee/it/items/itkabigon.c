#include "itkabigon.h"

#include <placeholder.h>
#include <platform.h>

#include "cm/camera.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_802C9D40

void it_802C9DFC(void) {}

void it_2725_Logic2_Destroyed(Item_GObj* gobj)
{
    Camera_80031044(2);
}

void it_802C9E24(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_802C9E44

/// #it_802C9E8C

/// #itKabigon_UnkMotion0_Anim

/// #itKabigon_UnkMotion0_Phys

/// #itKabigon_UnkMotion0_Coll

/// #it_802CA014

/// #it_802CA074

/// #itKabigon_UnkMotion1_Anim

void itKabigon_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itKabigon_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802CA324

bool itKabigon_UnkMotion2_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itKabigon_UnkMotion2_Phys(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool itKabigon_UnkMotion2_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802C9E44);
}

/// #it_802CA3F4
