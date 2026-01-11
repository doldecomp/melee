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
extern const f32 it_804DC878;

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
    s32 unused[2];  // Stack padding to achieve 0x20 frame size
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
            
            // Absolute value
            if (var_f1 < 0.0f) {
                var_f1 = -var_f1;
            }
            
            // Check if >= 0.0f (generates cror eq,gt,eq)
            if (var_f1 >= 0.0f) {
                temp_r4->xD5C = 1;
                M2C_FIELD(temp_r4, u8*, 0xDCB) |= 1;
            } else {
                temp_r4->xD5C = 0;
                M2C_FIELD(temp_r4, u8*, 0xDCB) &= ~1;
            }
        }
        
        // Use persistent r31 pointer for flag check
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

    // [0x10 & 0x24] r31 = 0; ip->xDD8 = 0;
    M2C_FIELD(ip, u32*, 0xDD8) = 0;

    // [0x2C - 0x40] Copy xDE4 (Vec3) to x4C
    M2C_FIELD(ip, Vec3*, 0x4C) = ip->xDD4_itemVar.dosei.xDE4;

    // [0x44 - 0x4C] Initialize xDDC and vel.x
    // Assign local here to force load into f0 right before use
    {
        f32 var_878 = it_804DC878;
        M2C_FIELD(ip, f32*, 0xDDC) = var_878;
        ip->x40_vel.x = var_878;
    }

    // [0x50] Call helper
    it_802762B0(ip);

    // [0x54] Call Item_80268E5C
    Item_80268E5C(gobj, 2, 3);

    // [0x64 - 0x70] Set anim speed and call function
    // Assign local here. Since it's not live across calls, compiler uses volatile f1.
    {
        f32 var_870 = it_804DC870;
        ip->x5D0_animFrameSpeed = var_870;
        // Result is implicitly left in r3 for the caller to pick up if they cast the function type
        lb_8000BA0C(gobj->hsd_obj, var_870);
    }

    // [0x74] Clear x518
    M2C_FIELD(ip, u32*, 0x518) = 0;
}

void itDosei_UnkMotion2_Phys(Item_GObj* gobj) {}

/// #itDosei_UnkMotion2_Coll

void it_80282074(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 3, 3);
    ip->x5D0_animFrameSpeed = it_804DC870;
    lb_8000BA0C(gobj->hsd_obj, it_804DC870);
    M2C_FIELD(ip, u32*, 0x518) = 0;
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
