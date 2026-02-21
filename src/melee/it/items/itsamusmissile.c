#include "itsamusmissile.h"

#include "ef/eflib.h"
#include "ftSamus/ftSs_Init.h"
#include "ftSamus/ftSs_SpecialN.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_2725.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include <math.h>

bool itSamusmissile_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026E71C(gobj, it_802B701C);
    return false;
}

bool itSamusmissile_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E71C(gobj, it_802B70A0);
    return false;
}

bool itSamusmissile_UnkMotion3_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}


/// #it_802B64FC



inline void isSamusmissile_MotionAnim(Item_GObj* gobj)
{
    Fighter_GObj* temp_r3;
    Item* ip;

    it_802B63F8();
    ip = GET_ITEM(gobj);
    if (ip->xDB8_itcmd_var3 == 0U) {
        temp_r3 = ip->xDD4_itemVar.samusmissile.xDE0;
        if ((temp_r3 != NULL) && ((u32) (ftSs_SpecialS_8012A068(temp_r3) - ip->xDD4_itemVar.samusmissile.xDD8) >= 2U)) {
            it_2725_Logic52_DmgDealt(gobj);
        }
    }
}

s32 itSamusmissile_UnkMotion0_Anim(Item_GObj* gobj)
{
    isSamusmissile_MotionAnim(gobj);
    return 0;
}


/// #itSamusmissile_UnkMotion0_Phys


s32 itSamusmissile_UnkMotion1_Anim(Item_GObj* gobj)
{
    isSamusmissile_MotionAnim(gobj);
    return 0;
}


void itSamusmissile_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSamusMissileAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;

    f32 maxSpeed;
    f32 xvel;

    if (ip->xDB0_itcmd_var1 != 0) {
        ip->x40_vel.x = (attrs->x30 * ip->facing_dir) + ip->x40_vel.x;
        xvel = ABS(ip->x40_vel.x);
        maxSpeed = attrs->x34;
        if (xvel > maxSpeed) {
            if (ip->facing_dir == 1.0f) {
                ip->x40_vel.x = maxSpeed;
            } else {
                ip->x40_vel.x = -maxSpeed;
            }
        }
    }
}



bool it_2725_Logic52_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xDD4_itemVar.samusmissile.xDD4 == NULL) {
        if (ip->msid != 2) {
            it_802B701C(gobj);
        }
    } else if (ip->msid != 3) {
        it_802B70A0(gobj);
    }
    return 0;
}


bool it_2725_Logic52_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xDD4_itemVar.samusmissile.xDD4 == NULL) {
        if (ip->msid != 2) {
            it_802B701C(gobj);
        }
    } else if (ip->msid != 3) {
        it_802B70A0(gobj);
    }
    return 0;
}


bool it_2725_Logic52_HitShield(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xDD4_itemVar.samusmissile.xDD4 == NULL) {
        if (ip->msid != 2) {
            it_802B701C(gobj);
        }
    } else if (ip->msid != 3) {
        it_802B70A0(gobj);
    }
    return 0;
}


/// #it_2725_Logic52_ShieldBounced

/// #it_2725_Logic52_Reflected

void it_802B701C(Item_GObj* gobj)
{
    PAD_STACK(0x10);
    it_8026BB44(gobj);
    it_8026BD24(gobj);
    it_8027518C(gobj);
    it_80273454(gobj);
    efLib_DestroyAll(gobj);
    it_80272B40(gobj);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

void it_802B70A0(Item_GObj* gobj)
{
    PAD_STACK(0x10);
    it_8026BB44(gobj);
    it_8026BD24(gobj);
    it_8027518C(gobj);
    it_80273454(gobj);
    efLib_DestroyAll(gobj);
    it_80272A60(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}


void it_2725_Logic52_EvtUnk(Item_GObj* gobj, Item_GObj* arg1)
{
    Item* ip = GET_ITEM(gobj);

    it_8026B894(gobj, (HSD_GObj* ) arg1);
    if ((ip->xDD4_itemVar.samusmissile.xDE0 == arg1)) {
        ip->xDD4_itemVar.samusmissile.xDE0 = NULL;
    }
}
