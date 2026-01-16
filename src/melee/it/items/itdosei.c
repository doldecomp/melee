#include "itdosei.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "lb/lb_00B0.h"

#include <math.h>

// Explicit declaration for external function
extern void Item_80268E5C(Item_GObj* gobj, int arg1, int arg2);

/// #it_3F14_Logic7_Spawned

/// #fn_80281390

/// #itDosei_UnkMotion0_Anim

void itDosei_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion0_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D62C(gobj, (HSD_GObjEvent) it_80282074);
    it_80276CB8(gobj);
    return false;
}

/// #fn_80281734

/// #it_802817A0

bool itDosei_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip2;
    Item* ip;
    f32 frame_speed;
    HSD_JObj* jobj;
    PAD_STACK(16);
    ip = gobj->user_data;
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    ip2 = gobj->user_data;
    frame_speed =
        0.5F * (M2C_FIELD(ip2, f32*, 0x4CC) * ip2->facing_dir) + 1.0F;
    jobj = gobj->hsd_obj;
    ip->x5D0_animFrameSpeed = frame_speed;
    lb_8000BA0C(jobj, frame_speed);
    if (it_80272C6C(gobj) == 0) {
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itDosei_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itDoseiAttributes* attr =
        (itDoseiAttributes*) ip->xC4_article_data->x4_specialAttributes;

    ip->x40_vel.x = ip->facing_dir * ABS(attr->unk8 * ip->x5D0_animFrameSpeed);
}

bool itDosei_UnkMotion1_Coll(Item_GObj* gobj)
{
    s32 unused[2];
    Item* temp_r31;

    temp_r31 = gobj->user_data;

    if (it_8026D8A4(gobj, it_80281C6C)) {
        if (it_80276308(gobj)) {
            it_80281C6C(gobj);
            return false;
        }

        {
            Item* temp_r4 = gobj->user_data;
            f32 var_f1 = M2C_FIELD(temp_r4, f32*, 0x4CC);

            if (var_f1 < 0.0f) {
                var_f1 = -var_f1;
            }

            if (var_f1 >= (f32) M_PI / 4) {
                temp_r4->xD5C = 1;
                temp_r4->xDC8_word.flags.x1F = true;
            } else {
                temp_r4->xD5C = 0;
                temp_r4->xDC8_word.flags.x1F = false;
            }
        }

        if (temp_r31->xD5C == 1) {
            it_3F14_Logic7_EnteredAir(gobj);
        } else {
            it_80276CB8(gobj);
        }
    } else {
        it_80282074(gobj);
    }

    return false;
}

void it_80281C6C(Item_GObj* gobj)
{
    // [0x1C] r29 = gobj, r30 = user_data (ip)
    Item* ip = GET_ITEM(gobj);

    // [0x10 & 0x24] r31 = 0;
    ip->xDD4_itemVar.dosei.xDD8 = 0;

    // [0x2C - 0x40] Copy xDE4 (Vec3) to pos
    ip->pos = ip->xDD4_itemVar.dosei.xDE4;

    ip->xDD4_itemVar.dosei.xDDC = 0.0F;
    ip->x40_vel.x = 0.0F;

    // [0x50] Call helper
    it_802762B0(ip);

    // [0x54] Call Item_80268E5C
    Item_80268E5C(gobj, 2, 3);

    {
        HSD_JObj* jobj = gobj->hsd_obj;
        ip->x5D0_animFrameSpeed = 1.0F;
        lb_8000BA0C(jobj, 1.0F);
    }

    // [0x74] Clear owner (0x518)
    ip->owner = NULL;
}

void itDosei_UnkMotion2_Phys(Item_GObj* gobj) {}

/// #itDosei_UnkMotion2_Coll

void it_80282074(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj;
    Item_80268E5C(gobj, 3, 3);
    jobj = gobj->hsd_obj;
    ip->x5D0_animFrameSpeed = 1.0F;
    lb_8000BA0C(jobj, 1.0F);
    ip->owner = NULL;
}

/// #itDosei_UnkMotion3_Anim

void itDosei_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itDosei_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802817A0);
    return false;
}

/// #it_3F14_Logic7_PickedUp

/// #itDosei_UnkMotion4_Anim

void itDosei_UnkMotion4_Phys(Item_GObj* gobj) {}

/// #it_3F14_Logic7_Dropped

/// #it_3F14_Logic7_Thrown

bool itDosei_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}
void itDosei_UnkMotion5_Phys(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

/// #it_3F14_Logic7_EnteredAir

bool itDosei_UnkMotion6_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    return false;
}

void itDosei_UnkMotion6_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion6_Coll(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ip->xDD4_itemVar.dosei.xDF8 = ip->x378_itemColl.floor.normal;
    it_8026E8C4(gobj, (HSD_GObjEvent) fn_80281734,
                (HSD_GObjEvent) it_80282074);
    return false;
}

/// #it_80282BFC

bool itDosei_UnkMotion8_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    return false;
}

void itDosei_UnkMotion8_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itDosei_UnkMotion8_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, fn_80282CD4);
    return false;
}

/// #fn_80282CD4

/// #itDosei_UnkMotion7_Anim

void itDosei_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion7_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D62C(gobj, it_80282BFC);
    it_80276CB8(gobj);
    return false;
}

/// #it_80282DE4

/// #itDosei_UnkMotion9_Anim

void itDosei_UnkMotion9_Phys(Item_GObj* gobj) {}

/// #itDosei_UnkMotion9_Coll

void itDosei_UnkMotion10_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion10_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, fn_80282CD4, it_80282BFC);
    return false;
}

bool itDosei_UnkMotion10_Anim(Item_GObj* gobj)
{
    Item* ip;
    HSD_JObj* jobj;
    ip = gobj->user_data;
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    jobj = gobj->hsd_obj;
    ip->x5D0_animFrameSpeed = 1.0F;
    lb_8000BA0C(jobj, 1.0F);
    return false;
}

/// #it_3F14_Logic7_DmgReceived

/// #itDosei_UnkMotion11_Anim

void itDosei_UnkMotion11_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itDosei_UnkMotion11_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, fn_80281390);
    return false;
}

/// #it_3F14_Logic7_DmgDealt

bool it_3F14_Logic7_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_3F14_Logic7_Clanked(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_3F14_Logic7_HitShield(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_3F14_Logic7_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_3F14_Logic7_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
