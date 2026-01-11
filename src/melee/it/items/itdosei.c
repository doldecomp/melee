#include "itdosei.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "lb/lb_00B0.h"

extern const f32 it_804DC874;
extern const f32 it_804DC870;

// Explicit declaration for external function
extern void Item_80268E5C(Item_GObj* gobj, int arg1, int arg2);

/// #it_3F14_Logic7_Spawned

/// #fn_80281390

/// #itDosei_UnkMotion0_Anim

void itDosei_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion0_Coll(Item_GObj* gobj)
{
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
    frame_speed = it_804DC874 * (M2C_FIELD(ip2, f32*, 0x4CC) * ip2->facing_dir) + it_804DC870;
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
    // Cast strict to itDoseiAttributes* to match the header definition
    itDoseiAttributes* attr = (itDoseiAttributes*) ip->xC4_article_data->x4_specialAttributes;
    f32 var_f1;

    var_f1 = attr->unk8 * ip->x5D0_animFrameSpeed;
    if (var_f1 < 0.0f) {
        var_f1 = -var_f1;
    }
    ip->x40_vel.x = ip->facing_dir * var_f1;
}

bool itDosei_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* temp_r31;
    Item* temp_r4;
    f32 var_f1;

    temp_r31 = gobj->user_data;
    if (it_8026D8A4(gobj, (void (*)(HSD_GObj*)) it_80281C6C) != 0) {
        if (it_80276308(gobj) != 0) {
            it_80281C6C(gobj);
            return 0;
        }
        temp_r4 = gobj->user_data;
        var_f1 = temp_r4->x378_itemColl.floor.normal.x;
        if (var_f1 < 0.0f) {
            var_f1 = -var_f1;
        }

        temp_r4->xD5C = (var_f1 == 0.7853982f);
        temp_r4->xDCC_flag.b0 = temp_r4->xD5C;

        if ((u32) temp_r31->xD5C == 1U) {
            it_3F14_Logic7_EnteredAir(gobj);
        } else {
            it_80276CB8(gobj);
        }
        return 0;
    }
    it_80282074(gobj);
    return 0;
}

s32 it_80281C6C(Item_GObj* gobj)
{
    // [0x1C] r29 = gobj, r30 = user_data (ip)
    Item* ip = GET_ITEM(gobj); 
    s32 ret; 

    // [0x10 & 0x24] r31 = 0; ip->xDD8 = 0;
    ip->xDD4_itemVar.dosei.xDD8 = 0;

    // [0x2C - 0x40] Copy xDE4 (Vec3) to x4C
    ip->x4C_pos = ip->xDD4_itemVar.dosei.xDE4;

    // [0x44 - 0x4C] Initialize xDDC and vel.x with it_804DC878
    ip->xDD4_itemVar.dosei.xDDC = it_804DC878;
    ip->x40_vel.x = it_804DC878;

    // [0x50] Call helper with Item*
    it_802762B0(ip);

    // [0x54] Call Item_80268E5C
    Item_80268E5C(gobj, 2, 3);

    // [0x64] Set anim speed
    ip->x5D0_animFrameSpeed = it_804DC870;

    // [0x68 - 0x70] Call lb_8000BA0C using gobj->hsd_obj (0x28)
    // Matches assembly: lwz r3, 0x28(r29) -> bl lb_8000BA0C
    ret = lb_8000BA0C(gobj->hsd_obj, it_804DC870);

    // [0x74] Clear x518
    ip->x518 = 0;

    // [0x90] Return result (r3 is preserved)
    return ret;
}

void itDosei_UnkMotion2_Phys(Item_GObj* gobj) {}

/// #itDosei_UnkMotion2_Coll

void it_80282074(Item_GObj* gobj) {}

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
    Item* ip = GET_ITEM(gobj);
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
    Item* ip = GET_ITEM(gobj);
    // Requires header update for xDF8, xDFC, xE00
    ip->xDD4_itemVar.dosei.xDF8 = M2C_FIELD(ip, f32*, 0x4CC);
    ip->xDD4_itemVar.dosei.xDFC = M2C_FIELD(ip, f32*, 0x4D0);
    ip->xDD4_itemVar.dosei.xE00 = M2C_FIELD(ip, f32*, 0x4D4);
    it_8026E8C4(gobj, (HSD_GObjEvent) fn_80281734, (HSD_GObjEvent) it_80282074);
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
    it_8026D62C(gobj, (HSD_GObjEvent) it_80282BFC);
    it_80276CB8(gobj);
    return false;
}

/// #it_80282DE4

/// #itDosei_UnkMotion9_Anim

void itDosei_UnkMotion9_Phys(Item_GObj* gobj) {}

/// #itDosei_UnkMotion9_Coll

/// #itDosei_UnkMotion10_Anim

void itDosei_UnkMotion10_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion10_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, fn_80282CD4, it_80282BFC);
    return false;
}

bool itDosei_UnkMotion10_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    ip->x5D0_animFrameSpeed = it_804DC870;
    lb_8000BA0C(gobj->hsd_obj, it_804DC870);
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
