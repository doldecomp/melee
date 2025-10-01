#include "itfire.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/eflib.h"
#include "gr/stage.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

void it_2725_Logic6_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFireAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->facing_dir = 0.0f;
    ip->xDAC_itcmd_var0 = 0;
    it_802CC944(gobj);
    it_80279CDC(gobj, attrs->x0);
}

void it_802CC740(Item_GObj*) {}

void it_2725_Logic6_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool itFire_UnkMotion1_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        it_802CC7D8(gobj);
    }
    return false;
}

void itFire_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itFire_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E7E0(gobj, it_802CC7D4);
    return false;
}

void it_802CC7D4(Item_GObj* gobj) {}

void it_802CC7D8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFireAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);

    it_8027ADEC(0x463, gobj, gobj->hsd_obj, 1.1f);
    ip->x40_vel.y = attrs->x8;
    Item_80268E5C(gobj, 2, 2);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

void itFire_UnkMotion2_Anim_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFireAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    it_8027ADEC(0x463, gobj, gobj->hsd_obj, 1.1f);
    ip->x40_vel.y = attrs->x8;
    Item_80268E5C(gobj, 2, 2);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itFire_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (!it_80272C6C(gobj)) {
        itFire_UnkMotion2_Anim_inline(gobj);
    }

    if (ip->pos.y > Stage_GetBlastZoneTopOffset()) {
        return true;
    } else {
        return false;
    }
}

void itFire_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFireAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.y += attrs->xC;
}

bool itFire_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802CC944(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    it_802762BC(ip);
    Item_80268E5C(gobj, 0, 2);

    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0f);
}

bool itFire_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

static void itFire_UnkMotion0_Phys_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 1, 2);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

void itFire_UnkMotion0_Phys(Item_GObj* gobj)
{
    if (it_8027A09C(gobj)) {
        Item* ip = GET_ITEM(gobj);
        itFireAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
        it_8027ADEC(0x464, gobj, gobj->hsd_obj, 1.1f);
        it_80273454(gobj);
        ip->x40_vel.y = attrs->x4;
        itFire_UnkMotion0_Phys_inline(gobj);
        ip->xDD1_flag.b1 = 1;
    }
}

bool itFire_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, it_802CC740);
}
