#include "itmaril.h"

#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "lb/lbvector.h"

#include <math.h>

ItemStateTable it_803F82B0[] = {
    {
        -1,
        itMaril_UnkMotion0_Anim,
        itMaril_UnkMotion0_Phys,
        itMaril_UnkMotion0_Coll,
    },
    {
        0,
        itMaril_UnkMotion1_Anim,
        itMaril_UnkMotion1_Phys,
        itMaril_UnkMotion1_Coll,
    },
    {
        -1,
        itMaril_UnkMotion2_Anim,
        itMaril_UnkMotion2_Phys,
        itMaril_UnkMotion2_Coll,
    },
    {
        -1,
        itMaril_UnkMotion3_Anim,
        itMaril_UnkMotion3_Phys,
        NULL,
    },
};

static bool itMaril_UnkMotion2_Anim_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xD44_lifeTimer -= 1.0f;
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

bool it_802D66F8(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (it_80273130(gobj) == true) {
        efLib_DestroyAll(gobj);
        return true;
    }
    return false;
}

void it_802D6740(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itMarilAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.y += attr->xC;
    ip->xDD4_itemVar.maril.x6C = ip->x40_vel;
    lbVector_Normalize(&ip->xDD4_itemVar.maril.x6C);
}

bool it_802D6798(Item_GObj* gobj)
{
    s32 coll;
    PAD_STACK(24);
    coll = it_8026D9A0(gobj);
    coll |= it_80276308(gobj);
    coll |= it_802763E0(gobj);
    if (coll != 0) {
        it_802D61C8(gobj, coll);
        it_802D6310(gobj, coll);
    }
    return false;
}

bool it_802D6808(Item_GObj* arg0)
{
    return false;
}

bool it_802D6810(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_802D6830(Item_GObj* arg0)
{
    return true;
}

bool it_802D6838(Item_GObj* arg0)
{
    return false;
}

bool it_802D6840(Item_GObj* arg0)
{
    return true;
}

bool it_802D6848(Item_GObj* arg0)
{
    return true;
}

void it_802D6850(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_2725_Logic28_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itMarilAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.maril.x60.x0 = 0;
    ip->x5D0_animFrameSpeed = attr->x10;
    it_80279CDC(gobj, attr->x0);
    Item_8026AE84(ip, 0x273D, 0x7F, 0x40);
    it_80275158(gobj, attr->x4);
    it_802D68FC(gobj);
}

void it_802D68FC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0f);
    it_8026BDB4(gobj);
}

static void itMaril_UnkMotion1_Coll_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itMarilAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    if (!ip->xDD4_itemVar.maril.x60.x0) {
        ip->xDD4_itemVar.maril.x6C.y = attr->x8;
        ip->xDD4_itemVar.maril.x6C.x = (M_PI * -ip->facing_dir) / attr->x8;
        ip->xDD4_itemVar.maril.x60.x0 = 1;
        ip->facing_dir = -ip->facing_dir;
        ip->xDC8_word.flags.x19 = 0;
        ip->xDD4_itemVar.maril.x64 = -ip->xDD4_itemVar.maril.x64;
    }
}

bool itMaril_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itMaril_UnkMotion0_Phys(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool itMaril_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, it_802D69E4);
}

void it_802D69E4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    it_80273454(gobj);
    it_802762BC(ip);
    it_802D6A54(gobj);
    ip->xDAC_itcmd_var0 = 0;
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    ip->xDD4_itemVar.maril.x68 = 8.0f;
}

void it_802D6A54(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itMarilAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    ip->xDD4_itemVar.maril.x64 = attr->xC * ip->facing_dir;
    it_8026BD9C(gobj);
    it_802756E0(gobj);
    it_802754D4(gobj);
    it_802754BC(gobj);
}

bool itMaril_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    it_8027A160(ip->xBBC_dynamicBoneTable->bones[1], ip);
    if (ip->xDD4_itemVar.maril.x60.x0) {
        f32 rot = ip->xDD4_itemVar.maril.x6C.x;
        HSD_JObjAddRotationY(jobj, rot);
        ip->xDD4_itemVar.maril.x6C.y -= 1.0f;
        if (ip->xDD4_itemVar.maril.x6C.y <= 0.0f) {
            ip->xDD4_itemVar.maril.x60.x0 = 0;
            ip->xDC8_word.flags.x19 = 1;
        }
    }
    return itMaril_UnkMotion2_Anim_inline(gobj);
}

void itMaril_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8027A344(gobj);
    ip->x40_vel.x = ip->xDD4_itemVar.maril.x64;
}

bool itMaril_UnkMotion1_Coll(Item_GObj* gobj)
{
    s32 coll;
    PAD_STACK(16);
    coll = it_8026DB40(gobj);
    if (it_80272C6C(gobj) == false) {
        if (coll & 1) {
            it_802D69E4(gobj);
        } else {
            it_802D6DDC(gobj);
        }
    } else if (coll & 0xC) {
        itMaril_UnkMotion1_Coll_inline(gobj);
    }
    return false;
}

void it_802D6DDC(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_UNK_0x1);
}

bool itMaril_UnkMotion2_Anim(Item_GObj* gobj)
{
    return itMaril_UnkMotion2_Anim_inline(gobj);
}

void itMaril_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itMaril_UnkMotion2_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802D69E4);
    return false;
}

bool itMaril_UnkMotion3_Anim(Item_GObj* gobj)
{
    return itMaril_UnkMotion2_Anim(gobj);
}

void itMaril_UnkMotion3_Phys(Item_GObj* gobj)
{
    itMaril_UnkMotion2_Phys(gobj);
}

static inline void it_802D6F00_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    it_8026BDB4(gobj);
    it_802756D0(gobj);
    efLib_DestroyAll(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    it_80273670(gobj, 0, 0.0f);
}

bool it_802D6F00(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itMarilAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    if ((f32) ip->xC9C >= attr->x14) {
        it_80279D38(gobj);
        it_802D6F00_inline(gobj);
    }
    return false;
}

void it_802D6FB0(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
