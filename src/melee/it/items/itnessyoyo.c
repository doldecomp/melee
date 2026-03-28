#include "itnessyoyo.h"

#include <placeholder.h>

#include "ft/chara/ftNess/ftNs_AttackHi4.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include "it/itYoyo.h"
#include "lb/lb_00B0.h"

#include <baselib/gobjplink.h>

void it_802BE598(Item_GObj* gobj)
{
    it_8026B724(gobj);
}

void it_802BE5B8(Item_GObj* gobj)
{
    it_8026B73C(gobj);
}

void it_802BE5D8(void* arg, float frame)
{
    HSD_GObj* gobj = arg;
    Item* ip = gobj->user_data;
    itYoyoAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = ip->xDD4_itemVar.flipper.xDEC;
    HSD_JObjRemoveAnimAll(jobj);
    HSD_JObjAddAnimAll(jobj, NULL, (HSD_MatAnimJoint*) attrs->x58_UNK6, NULL);
    lb_8000BA0C(jobj, 1.0F);
    HSD_JObjReqAnimAll(jobj, frame);
    HSD_JObjAnimAll(jobj);
}

/// #it_802BE65C

void it_802BE958(void* gobj)
{
    Item* ip = ((HSD_GObj*) gobj)->user_data;
    if (ip != NULL) {
        if (gobj != NULL) {
            if (ip->owner != NULL) {
                ftNs_AttackHi4_YoyoItemSetFlag(ip->owner);
            }
            ip->owner = NULL;
            {
                ItemLink* link = (ItemLink*) ip->xDD4_itemVar.samusgrapple.x8;
                while (link != NULL) {
                    HSD_GObj* tmp = link->gobj;
                    link = link->next;
                    HSD_GObjPLink_80390228(tmp);
                }
            }
        }
        Item_8026A8EC(gobj);
    }
    PAD_STACK(8);
}

/// #it_802BE9D8

void itNessyoyo_UnkMotion0_Phys(Item_GObj* gobj)
{
    it_802BF900(GET_ITEM(gobj));
}

/// #itNessyoyo_UnkMotion1_Phys

void itNessyoyo_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    itYoyoAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ItemLink* link = (ItemLink*) ip->xDD4_itemVar.samusgrapple.x8;
    Mtx mtx;
    Vec3 pos;

    PSMTXIdentity(mtx);
    mtx[0][3] = 0.0F;
    mtx[1][3] = 0.0F;
    mtx[2][3] = 0.0F;

    HSD_JObjSetupMatrix(link->jobj);

    PSMTXConcat(link->jobj->mtx, mtx, mtx);

    pos.x = mtx[0][3];
    pos.y = mtx[1][3];
    pos.z = mtx[2][3];

    it_802BF4A0(link, &pos, attrs, ip);
    it_802BFAFC(ip, &pos);
}

/// #itNessyoyo_UnkMotion3_Phys

/// #itNessyoyo_UnkMotion3_Anim

/// #it_802BF030

/// #it_802BF180

/// #it_802BF28C

/// #it_802BF4A0

/// #it_802BF800

/// #it_802BF900

/// #it_802BFAFC

void itNessYoyo_Logic59_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

void it_802BFE5C(Item_GObj* gobj, Vec3* pos, float unused)
{
    Item* ip = GET_ITEM(gobj);
    ItemLink* link = (ItemLink*) ip->xDD4_itemVar.samusgrapple.x8;
    float vel_x;
    link->vel = *pos;
    vel_x = link->vel.x;
    if (vel_x < 0.0f) {
        vel_x = -vel_x;
    }
    link->vel.x = ip->facing_dir * vel_x;
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

/// #it_802BFEC4

/// #it_802C0010

#ifdef MWERKS_GEKKO

#pragma push
asm void it_2725_Logic59_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    // clang-format off
    nofralloc
    mflr r0
    stw r0, 0x4(r1)
    stwu r1, -0x20(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r4
    lwz r31, 0x2c(r3)
    bl it_8026B894
    lwz r0, 0xde4(r31)
    cmplw r0, r30
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    addi r1, r1, 0x20
    mtlr r0
    blr
    // clang-format on
}
#pragma pop

#else

void it_2725_Logic59_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    NOT_IMPLEMENTED;
}

#endif
