#include "itsamusmissile.h"

#include <math.h>

#include "db/db.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ftSamus/ftSs_Init.h"
#include "ftSamus/ftSs_SpecialN.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_2725.h"
#include "it/it_26B1.h"
#include "it/item.h"


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

void it_802B63F8(HSD_GObj* gobj)
{
    f32 temp_f1;
    Item* ip = GET_ITEM(gobj);
    itSamusMissileAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;

    if (ip->xD44_lifeTimer > (attrs->x4 - attrs->x8)) {
        ip->xDAC_itcmd_var0 = 1;
    } else {
        ip->xDAC_itcmd_var0 = 0;
    }

    if ((ip->xD44_lifeTimer == (attrs->x4 - attrs->x8)) &&
        ((s32) ip->xDD4_itemVar.samusmissile.xDD4 == 0))
    {
        efLib_DestroyAll(gobj);
    }

    /* (cror eq, lt, eq) indicates a <= style condition here */
    if (ip->xD44_lifeTimer <= (attrs->x24 - attrs->x28)) {
        ip->xDB0_itcmd_var1 = 1;
    }

    temp_f1 = ip->xD44_lifeTimer;

    /* (cror eq, lt, eq) indicates temp_f1 <= 0.0f */
    if (temp_f1 <= 0.0f) {
        if ((s32) ip->xDD4_itemVar.samusmissile.xDD4 == 0) {
            it_802B701C((Item_GObj*) gobj);
            return;
        }
        it_802B70A0((Item_GObj*) gobj);
        return;
    }

    ip->xD44_lifeTimer = (f32) (temp_f1 - 1.0f);
}

Item_GObj* it_802B62D0(Item_GObj* gobj, Vec3* pos, int arg2, f32 facing_dir)
{
    HSD_GObj* n;
    HSD_GObj* temp_owner;
    SpawnItem si;
    Item* it;
    si.kind = It_Kind_Samus_Missile;
    si.prev_pos = *pos;
    si.prev_pos.z = 0.0f;
    it_8026BB68(gobj, &si.pos);
    si.facing_dir = facing_dir;
    si.x3C_damage = 0;
    si.vel.x = si.vel.y = si.vel.z = 0.0f;
    si.x0_parent_gobj = gobj;
    si.x4_parent_gobj2 = si.x0_parent_gobj;
    si.x44_flag.b0 = true;
    si.x40 = 0;

    n = Item_80268B18(&si);

    if (n != NULL) {
        it = GET_ITEM(n);

        it->xDD4_itemVar.samusmissile.xDD4 = arg2;
        it->xDD4_itemVar.samusmissile.xDE0 =
            (Fighter_GObj*) it->owner;

        temp_owner = it->xDD4_itemVar.samusmissile.xDE0;
        if ((u32) temp_owner != 0U) {
            it->xDD4_itemVar.samusmissile.xDD8 =
                ftSs_SpecialS_8012A068(temp_owner);
        }

        if ((s32) it->xDD4_itemVar.samusmissile.xDD4 == 0) {
            it_802B66A8(n);
        } else {
            it_802B6A60(n);
        }

        db_80225DD8(n, (Fighter_GObj*) gobj);
        return n;
    } else {
        return NULL;
    }
}

/// #it_802B64FC

static HSD_JObj* itSamusmissile_Grandchild_inline(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child;

    if (!jobj) {
        child = NULL;
    } else {
        child = jobj->child;
    }
    if (!child) {
        child = NULL;
    } else {
        child = child->child;
    }
    return child;
}

void* it_802B66A8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSamusMissileAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(0x8);

    ip->x40_vel.x = attrs->xC * ip->facing_dir;
    ip->x40_vel.y = 0.0f;

    ip->xDB8_itcmd_var3 = 0.0f;
    ip->xDB4_itcmd_var2 = 0.0f;
    ip->xDAC_itcmd_var0 = 0.0f;

    it_80275158(gobj, attrs->x4);

    ip->xDD4_itemVar.samusmissile.xDDC = 0;

    it_8026B3A8(gobj);
    Item_80268E5C((HSD_GObj*) gobj, 0, ITEM_ANIM_UPDATE);

    return efSync_Spawn(0x485, (HSD_GObj*) gobj, itSamusmissile_Grandchild_inline(gobj));
}

inline void isSamusmissile_MotionAnim(Item_GObj* gobj)
{
    Fighter_GObj* temp_r3;
    Item* ip;

    it_802B63F8(temp_r3);
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

void* it_802B6A60(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSamusMissileAttributes* attrs;
    PAD_STACK(0x8);

    attrs = ip->xC4_article_data->x4_specialAttributes;

    ip->x40_vel.x = attrs->x2C * ip->facing_dir;
    ip->x40_vel.y = 0.0f;

    ip->xDB8_itcmd_var3 = 0;
    ip->xDB4_itcmd_var2 = 0;
    ip->xDB0_itcmd_var1 = 0;

    it_80275158(gobj, attrs->x24);
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);


    return efSync_Spawn(0x484, gobj, itSamusmissile_Grandchild_inline(gobj));
}


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
