#include "ithassam.h"

#include "math.h"

#include <placeholder.h>
#include <platform.h>

#include "cm/camera.h"
#include "ef/eflib.h"

#include "ft/forward.h"

#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "gm/gm_unsplit.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"
#include "lb/lbrefract.h"
#include "lb/lbvector.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

/* 2CDC5C */ static void it_802CDC5C(Item_GObj* gobj);
/* 2CDC80 */ static void it_802CDC80(Item_GObj* gobj);
/* 2CDCB4 */ static void it_802CDCB4(Item_GObj* gobj);
/* 2CDD24 */ static bool itHassam_UnkMotion0_Anim(Item_GObj* gobj);
/* 2CDD78 */ static void itHassam_UnkMotion0_Phys(Item_GObj* gobj);
/* 2CDDD0 */ static bool itHassam_UnkMotion0_Coll(Item_GObj* gobj);
/* 2CDE1C */ static Item_GObj* it_802CDE1C(Vec3* vec, Item_GObj* gobj);
/* 2CDF28 */ static void it_802CDF28(Item_GObj* gobj);
/* 2CE008 */ static void it_802CE008(Item_GObj* gobj);
/* 2CE0C4 */ static bool itHassam_UnkMotion1_Anim(Item_GObj* gobj);
/* 2CE308 */ static void itHassam_UnkMotion1_Phys(Item_GObj* gobj);
/* 2CE3A8 */ static bool itHassam_UnkMotion1_Coll(Item_GObj* gobj);
/* 2CE400 */ static void it_802CE400(Item_GObj* gobj);
/* 2CE588 */ static bool itHassam_UnkMotion2_Anim(Item_GObj* gobj);
/* 2CE5DC */ static void itHassam_UnkMotion2_Phys(Item_GObj* gobj);
/* 2CE638 */ static bool itHassam_UnkMotion2_Coll(Item_GObj* gobj);
/* 2CE640 */ static void it_802CE640(Item_GObj* gobj);
/* 2CE6A4 */ static bool itHassam_UnkMotion3_Anim(Item_GObj* gobj);
/* 2CE6C8 */ static void itHassam_UnkMotion3_Phys(Item_GObj* gobj);
/* 2CE6E8 */ static bool itHassam_UnkMotion3_Coll(Item_GObj* gobj);

ItemStateTable it_803F7CF8[] = {
    { 0, itHassam_UnkMotion0_Anim, itHassam_UnkMotion0_Phys,
      itHassam_UnkMotion0_Coll },
    { 1, itHassam_UnkMotion1_Anim, itHassam_UnkMotion1_Phys,
      itHassam_UnkMotion1_Coll },
    { 2, itHassam_UnkMotion2_Anim, itHassam_UnkMotion2_Phys,
      itHassam_UnkMotion2_Coll },
    { -1, itHassam_UnkMotion3_Anim, itHassam_UnkMotion3_Phys,
      itHassam_UnkMotion3_Coll },
};

void it_802CDBE0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Article* ap = ip->xC4_article_data;
    itHassam_ItemVars* attr = ap->x4_specialAttributes;

    PAD_STACK(12);

    it_80279C48(gobj, ap);
    ip->xDAC_itcmd_var0 = 0;
    ip->xDB0_itcmd_var1 = 0;
    it_80279CDC(gobj, attr->x0);
    it_802CE640(gobj);
    Item_8026AE84(ip, 0x2721, 0x7F, 0x40);
}

void it_802CDC5C(Item_GObj* gobj) {}

void it_802CDC60(Item_GObj* gobj, Item_GObj* ref)
{
    it_8026B894(gobj, ref);
}

void it_802CDC80(Item_GObj* gobj)
{
    PAD_STACK(12);

    it_80273454(gobj);
    it_802CDCB4(gobj);
}

void it_802CDCB4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_8027A13C(gobj);
    it_8027A160(ip->xBBC_dynamicBoneTable->bones[2], ip);
}

bool itHassam_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    it_8027A160(ip->xBBC_dynamicBoneTable->bones[2], ip);
    if (it_80272C6C(gobj) == false) {
        it_802CE008(gobj);
    }
    return false;
}

void itHassam_UnkMotion0_Phys(Item_GObj* gobj)
{
    ItemAttr* temp_r4;
    Item* ip = GET_ITEM(gobj);

    it_8027A344(gobj);
    if (ip->ground_or_air == GA_Air) {
        temp_r4 = ip->xCC_item_attr;
        it_80272860(gobj, temp_r4->x10_fall_speed,
                    temp_r4->x14_fall_speed_max);
    }
}

bool itHassam_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->ground_or_air == GA_Air) {
        it_8026E15C(gobj, it_802CDC5C);
    } else {
        it_8026D62C(gobj, it_802CDC5C);
    }
    return false;
}

Item_GObj* it_802CDE1C(Vec3* vec, Item_GObj* gobj)
{
    Vec3 sp20;
    Fighter* cur_fp;
    Fighter* fp;
    f32 temp_f0, x_dist, y_dist, min_dist;
    Fighter_GObj* cur_fgobj;
    Fighter_GObj* closest_fgobj;
    min_dist = F32_MAX;

    PAD_STACK(8);

    if (gobj != NULL) {
        fp = GET_FIGHTER(gobj);
    } else {
        fp = NULL;
    }

    closest_fgobj = NULL;
    for (cur_fgobj = HSD_GObj_Entities->fighters; cur_fgobj != NULL;
         cur_fgobj = cur_fgobj->next)
    {
        if (ftLib_80086FD4(gobj, cur_fgobj) == false) {
            cur_fp = GET_FIGHTER(cur_fgobj);
            if ((cur_fp->x221F_b3 == false) &&
                ((gm_8016B168() == false) || (fp == NULL) ||
                 (cur_fp->team != fp->team)))
            {
                ftLib_800866DC(cur_fgobj, &sp20);
                y_dist = vec->y - sp20.y;
                x_dist = vec->x - sp20.x;
                temp_f0 = (x_dist * x_dist) + (y_dist * y_dist);
                if ((temp_f0 < min_dist) && (sp20.y > vec->y)) {
                    min_dist = temp_f0;
                    closest_fgobj = cur_fgobj;
                }
            }
        }
    }
    if (closest_fgobj == NULL) {
        closest_fgobj = ftLib_8008627C(vec, gobj);
    }
    return closest_fgobj;
}

void it_802CDF28(Item_GObj* gobj)
{
    Vec3 sp1C;
    Vec3 sp10;
    Fighter_GObj* var_r3;

    Item* ip = GET_ITEM(gobj);
    itHassam_ItemVars* attr = ip->xC4_article_data->x4_specialAttributes;

    var_r3 = it_802CDE1C(&ip->pos, ip->owner);
    if (var_r3 == NULL) {
        var_r3 = ip->owner;
    }
    ftLib_800866DC(var_r3, &sp1C);
    sp1C.y += attr->x8;
    lbVector_Diff(&sp1C, &ip->pos, &sp10);
    ip->xDD4_itemVar.hassam.x5C.x = attr->x4;
    ip->xDD4_itemVar.hassam.x5C.y = 0.0F;
    ip->xDD4_itemVar.hassam.x5C.z = 0.0F;
    lbVector_Rotate(&ip->xDD4_itemVar.hassam.x5C, 4, atan2f(sp10.y, sp10.x));
    ip->xDD4_itemVar.hassam.x5C.y += attr->xC;
    ip->x40_vel.x = ip->xDD4_itemVar.hassam.x5C.x;
    ip->x40_vel.y = ip->xDD4_itemVar.hassam.x5C.y;
    ip->x40_vel.z = ip->xDD4_itemVar.hassam.x5C.z;
    it_80272980(gobj);
}

void it_802CE008(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHassam_ItemVars* attr = ip->xC4_article_data->x4_specialAttributes;

    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_8027A160(ip->xBBC_dynamicBoneTable->bones[2], ip);
    ip->xD44_lifeTimer = attr->x18;
    ip->x40_vel.x = attr->x4 * ip->facing_dir;
    ip->xDD4_itemVar.hassam.x5C.x = attr->x4 * ip->facing_dir;
    ip->xDD4_itemVar.hassam.x5C.z = ip->xDD4_itemVar.hassam.x5C.y = 0.0F;
}

bool itHassam_UnkMotion1_Anim(Item_GObj* gobj)
{
    f32 prev_dir;
    Item* ip;
    itHassam_ItemVars* attr;
    HSD_JObj* jobj;

    ip = (Item*) gobj->user_data;
    attr = ip->xC4_article_data->x4_specialAttributes;
    if (it_80272C6C(gobj) == false) {
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        ip->entered_hitlag = efLib_PauseAll;
        ip->exited_hitlag = efLib_ResumeAll;
    }
    it_8027A160(ip->xBBC_dynamicBoneTable->bones[2], ip);
    if (ip->xDB0_itcmd_var1 != 0) {
        jobj = (HSD_JObj*) gobj->hsd_obj;

        ip->xDD4_itemVar.hassam.x68 = HSD_JObjGetRotationY(gobj->hsd_obj);
        ip->xDD4_itemVar.hassam.x68 += deg_to_rad * (180 / attr->x20);
        HSD_JObjSetRotationY(jobj, ip->xDD4_itemVar.hassam.x68);

        if (++ip->xDB0_itcmd_var1 > (u32) attr->x20) {
            ip->xDB0_itcmd_var1 = 0;
        }
    }

    if (--ip->xD44_lifeTimer < 0.0F) {
        if (ip->xDAC_itcmd_var0 != 0) {
            it_802CE400(gobj);
        } else {
            prev_dir = ip->facing_dir;
            it_802CDF28(gobj);
            if (prev_dir != ip->facing_dir) {
                ip->xDB0_itcmd_var1 = 1;
            }
            ip->xDAC_itcmd_var0 = 1;
            ip->xD44_lifeTimer = attr->x1C;
            it_802762BC(ip);
        }
    }
    return false;
}

void itHassam_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHassam_ItemVars* attr = ip->xC4_article_data->x4_specialAttributes;

    it_8027A344(gobj);
    if (ip->ground_or_air == GA_Air) {
        ip->xDD4_itemVar.hassam.x5C.y -= attr->x14;
        if (ip->xDD4_itemVar.hassam.x5C.y < -attr->x10) {
            ip->xDD4_itemVar.hassam.x5C.y = -attr->x10;
        }
    }
    ip->x40_vel.x += ip->xDD4_itemVar.hassam.x5C.x;
    ip->x40_vel.y += ip->xDD4_itemVar.hassam.x5C.y;
    ip->x40_vel.z += ip->xDD4_itemVar.hassam.x5C.z;
}

bool itHassam_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xDAC_itcmd_var0 == 0) {
        if (ip->ground_or_air == GA_Air) {
            it_8026E15C(gobj, it_802CDC5C);
        } else {
            it_8026D62C(gobj, it_802CDC5C);
        }
    }
    return false;
}

void it_802CE400(Item_GObj* gobj)
{
    Vec3 sp1C;
    Vec3 sp10;

    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = (HSD_JObj*) gobj->hsd_obj;
    itHassam_ItemVars* attr = ip->xC4_article_data->x4_specialAttributes;

    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_8027A160(ip->xBBC_dynamicBoneTable->bones[2], ip);
    Camera_80030788(&sp1C);
    lbVector_Diff(&sp1C, &ip->pos, &sp10);
    lbVector_Normalize(&sp10);
    sp10.x = sp10.x * attr->x4;
    sp10.y = sp10.y * attr->x4;
    sp10.z = sp10.z * attr->x4;

    ip->xDD4_itemVar.hassam.x5C.x = sp10.x;
    ip->xDD4_itemVar.hassam.x5C.y = sp10.y;
    ip->xDD4_itemVar.hassam.x5C.z = sp10.z;
    ip->x40_vel.x = 0.0F;
    ip->x40_vel.y = 0.0F;
    ip->x40_vel.z = 0.0F;
    ip->facing_dir = 0.0F;

    HSD_JObjSetRotationY(jobj, 0.0F);
}

bool itHassam_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    it_8027A160(ip->xBBC_dynamicBoneTable->bones[2], ip);
    if (it_80272C6C(gobj) == false) {
        return true;
    }
    return false;
}

void itHassam_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    it_8027A344(gobj);
    ip->pos.x += ip->xDD4_itemVar.hassam.x5C.x;
    ip->pos.y += ip->xDD4_itemVar.hassam.x5C.y;
    ip->pos.z += ip->xDD4_itemVar.hassam.x5C.z;
}

bool itHassam_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802CE640(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;

    it_802762BC(ip);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itHassam_UnkMotion3_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itHassam_UnkMotion3_Phys(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool itHassam_UnkMotion3_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, it_802CDC80);
}
