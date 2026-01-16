#include "itkabigon.h"

#include <placeholder.h>
#include <platform.h>

#include "cm/camera.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "ef/eflib.h"
#include "it/item.h"

/// #it_802C9D40

void it_802C9DFC(Item_GObj* gobj) {}

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

bool itKabigon_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xDB0_itcmd_var1 == 0) {
        if (ip->ground_or_air == GA_Air) {
            it_8026E15C(gobj, it_802C9DFC);
        } else {
            it_8026D62C(gobj, it_802C9DFC);
        }
    }
    return false;
}

/// #it_802CA014

/// #it_802CA074

/// #itKabigon_UnkMotion1_Anim

void itKabigon_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itKabigon_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802CA324(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

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
