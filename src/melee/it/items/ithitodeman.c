#include "ithitodeman.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "it/item.h"

/// #it_2725_Logic24_Spawned

void it_802D43AC(void) {}

/// #it_802D43B0

/// #it_802D43EC

/// #it_802D4494

/// #it_802D4510

/// #it_802D4564

/// #it_802D472C

bool it_802D48A8(Item_GObj* gobj)
{
    return false;
}

/// #it_802D48B0

void it_802D4990(Item_GObj* gobj)
{
    Item* ip;

    ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    ip->on_accessory = it_802D4B50;
}

/// #itHitodeman_UnkMotion1_Anim

typedef struct {
    u8 _pad[0x4C];
    f32 x4C;
} itHitodemanAttributes;

void itHitodeman_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHitodemanAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xDB0_itcmd_var1 != 0) {
        ip->x40_vel.x = -((-ip->facing_dir * attrs->x4C) - ip->x40_vel.x);
    }
}

bool itHitodeman_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D4B50(Item_GObj* gobj) {}

void it_802D4B54(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itHitodeman_UnkMotion2_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

/// #itHitodeman_UnkMotion2_Phys

bool itHitodeman_UnkMotion2_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802D43AC);
}

/// #it_802D4C74

/// #it_2725_Logic43_Spawned

bool it_802D4EF4(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDB4_itcmd_var2 = 1;
    return false;
}

bool it_802D4F08(Item_GObj* gobj)
{
    return it_8027AF50(gobj);
}

bool it_802D4F28(Item_GObj* gobj)
{
    return it_8027AE34(gobj);
}

bool it_2725_Logic43_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool it_802D4F50(Item_GObj* arg0)
{
    return true;
}

void it_802D4F58(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802D4F78(Item_GObj* gobj)
{
    f32 f;
    Item* ip;
    HSD_JObj* jobj;

    ip = GET_ITEM(gobj);
    jobj = GET_JOBJ(gobj);
    f = 1.0f;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    efSync_Spawn(0x46C, gobj, jobj, &f);
}

/// #it_802D4FFC

void it_802D5044(Item_GObj* gobj) {}

bool it_802D5048(Item_GObj* gobj)
{
    return false;
}
