#include "itlinkboomerang.h"

#include "m2c_macros.h"
#include "placeholder.h"

#include "baselib/forward.h"

#include "baselib/jobj.h"
#include "baselib/mtx.h"
#include "dolphin/mtx.h"
#include "ft/chara/ftLink/ftLk_SpecialS.h"

#include "ft/forward.h"

#include "ft/ftlib.h"
#include "ftLink/ftLk_SpecialHi.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCharItems.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"

#include <MSL/trigf.h>

#define M_TAU 6.283185307179586
#define DEG2RAD 0.017453292f

static inline float my_sqrtf(float x)
{
    static const double _half = .5;
    static const double _three = 3.0;

    u8 _[4] = { 0 };

    volatile float y;
    if (x > 0) {
        double guess = __frsqrte((double) x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        y = (float) (x * guess);
        return y;
    }
    return x;
}

#define HYPOT(x, y) my_sqrtf((x) * (x) + (y) * (y))
#define VEC_XY_LENGTH(v) HYPOT((v)->x, (v)->y)

static inline void clamp_angle_pi(f32* angle)
{
    if (*angle <= 0.0f) {
        *angle += M_PI;
    } else {
        *angle -= M_PI;
    }
}

static inline void clamp_tau(f32* angle)
{
    if (*angle > M_TAU) {
        *angle -= M_TAU;
    } else if (*angle < -M_TAU) {
        *angle += M_TAU;
    }
}

static inline void norm_xF74(Item* ip)
{
    f32 angle;
    if (ip->facing_dir != 1.0f) {
        angle = ip->xDD4_itemVar.linkboomerang.xF74;
    } else {
        angle = ip->xDD4_itemVar.linkboomerang.xF74 - M_PI;
    }
    ip->xDD4_itemVar.linkboomerang.xF78 = angle;
}

static inline void remove_boomerang(Item_GObj* gobj)
{
    Item* ip;
    HSD_GObj* owner;

    ip = GET_ITEM(gobj);
    owner = ip->owner;
    if ((owner != NULL) && (owner == ip->xDD4_itemVar.linkboomerang.xF98) &&
        (ip->xDD4_itemVar.linkboomerang.xDE8 != 1))
    {
        ftLk_SpecialS_RemoveBoomerang0(owner);
    }
}

bool it_8029FDBC(Item_GObj* gobj)
{
    return (GET_ITEM(gobj)->msid != 0) ? false : true;
}

void it_8029FDDC(HSD_GObj* gobj, int arg1)
{
    s32 i;
    Item* ip;
    HSD_JObj* jobj;

    ip = GET_ITEM(gobj);
    it_8026EECC(gobj, arg1);
    for (i = 0; i < 2; i++) {
        jobj = ip->xDD4_itemVar.linkboomerang.xF90[i];
        if (jobj != NULL) {
            HSD_JObjDispAll(jobj, NULL, HSD_GObj_80390EB8(arg1), 0);
        }
    }
}

void it_8029FE64(Item_GObj* gobj, s32 i)
{
    HSD_JObj* jobj;
    s32 temp_r30;
    Item* ip;
    Vec3* v;

    ip = gobj->user_data;
    jobj = ip->xDD4_itemVar.linkboomerang.xF90[i];
    temp_r30 = M2C_FIELD(ip, s32*, 0xDDC + (i * 4));
    if (jobj != NULL) {
        it_80272A18(jobj);
        v = M2C_FIELD(ip, Vec**, 0xDF0 + (temp_r30 * 0xC));
        HSD_JObjSetTranslate(jobj, v);
        v = M2C_FIELD(ip, Vec**, 0xEB0);
        HSD_JObjSetRotationX(jobj, v->x);
        HSD_JObjSetRotationY(jobj, v->y);
        HSD_JObjSetRotationZ(jobj, v->z);
    }
}

/// #it_802A013C

static void loop_lb_8000BA0C(Item* ip, HSD_JObj* hobj, f32 arg1)
{
    s32 i;
    lb_8000BA0C(hobj, arg1);
    for (i = 0; i < 2; i++) {
        hobj = ip->xDD4_itemVar.linkboomerang.xF90[i];
        if (hobj != NULL) {
            lb_8000BA0C(hobj, arg1);
        }
    }
}

void it_802A0534(Item_GObj* gobj, Point3d* arg1)
{
    Point3d sp20;
    HSD_JObj* hobj;
    HSD_JObj* child;
    Item* ip;
    s32 i;
    itLinkBoomerangAttributes* attrs;
    Quaternion quad;
    f32 angle;

    ip = gobj->user_data;
    hobj = gobj->hsd_obj;
    attrs = ip->xC4_article_data->x4_specialAttributes;
    child = HSD_JObjGetChild(hobj);
    if (ftLk_SpecialHi_GetFv4(ip->xDD4_itemVar.linkboomerang.xF98) != 0) {
        it_80275158(gobj, attrs->x4);
    } else {
        it_80275158(gobj, attrs->x0);
    }

    angle = 0; // TODO
    ip->xDD4_itemVar.linkboomerang.xF74 = angle;
    norm_xF74(ip);
    ip->xB8_itemLogicTable->thrown(gobj);
    HSD_MtxGetRotation(((HSD_JObj*) ftLib_80086630(
                            ip->xDD4_itemVar.linkboomerang.xF98, ip->xDC4))
                           ->mtx,
                       &sp20);
    it_8027429C(gobj, arg1);
    it_8026B3A8(gobj);

    HSD_JObjSetRotationZ(hobj, ip->xDD4_itemVar.linkboomerang.xF78);
    quad.x = sp20.x;
    quad.y = sp20.y;
    quad.z = sp20.z;
    quad.w = angle;
    HSD_JObjSetRotation(child, &quad);

    loop_lb_8000BA0C(ip, child, attrs->x30);
}

void it_802A07B4(Item_GObj* gobj)
{
    remove_boomerang(gobj);
    Item_8026A8EC(gobj);
}

void it_802A0810(Item_GObj* gobj)
{
    Item* ip;
    s32 i;

    ip = GET_ITEM(gobj);
    for (i = 0; i < 2; i++) {
        if (ip->xDD4_itemVar.linkboomerang.xF90[i] != NULL) {
            HSD_JObjRemoveAll(ip->xDD4_itemVar.linkboomerang.xF90[i]);
        }
    }
    ip->xDD4_itemVar.linkboomerang.xF90[1] = NULL;
    ip->xDD4_itemVar.linkboomerang.xF90[0] = NULL;
}

void it_2725_Logic18_Destroyed(Item_GObj* gobj)
{
    Item* ip;
    ip = GET_ITEM(gobj);
    remove_boomerang(gobj);
    it_802A0810(gobj);
    ip->owner = NULL;
    ip->xDC8_word.flags.x13 = 0;
}

void it_802A0930(Item_GObj* gobj)
{
    HSD_JObj* hobj;
    Item* ip;
    s32 i;
    Vec3* v;

    ip = gobj->user_data;
    for (i = 0; i < 2; i++) {
        hobj = ip->xDD4_itemVar.linkboomerang.xF90[i];
        if ((hobj != NULL) && (((i == 0) && (ip->xDB0_itcmd_var1 == 2)) ||
                               ((i == 1) && (ip->xDB4_itcmd_var2 == 2))))
        {
            if (hobj != NULL) {
                HSD_JObjAnimAll(hobj);

                // TODO: probably indexing into a Vec3[] field of linkboomerang
                v = M2C_FIELD(&ip->xDD4_itemVar.linkboomerang, Vec3**,
                              i * 0xC * 0xFF);
                HSD_JObjSetTranslate(hobj, v);
                v = M2C_FIELD(&ip->xDD4_itemVar.linkboomerang, Vec3**,
                              i * 0xC * 0xFF);
                HSD_JObjSetRotationX(hobj, v->x);
                HSD_JObjSetRotationY(hobj, v->y);
                HSD_JObjSetRotationZ(hobj, v->z);
                ip->xDD4_itemVar.linkboomerang.xDDC++;
                if (ip->xDD4_itemVar.linkboomerang.xDDC >= 16) {
                    ip->xDD4_itemVar.linkboomerang.xDDC = 0;
                }
            }
        }
    }
}

static inline void it_8029FE64_no_inline(Item_GObj* gobj, s32 i)
{
    it_8029FE64(gobj, i);
}

static inline void it_802A0C34_sub_1(Item_GObj* gobj)
{
    Item* ip;
    itLinkBoomerangAttributes* attrs;

    ip = gobj->user_data;
    attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xDB0_itcmd_var1 == 0) {
        ip->xDD4_itemVar.linkboomerang.xF70 =
            (ip->xDD4_itemVar.linkboomerang.xF70 - 1.0f);
        if (ip->xDD4_itemVar.linkboomerang.xF70 <= 0.0f) {
            it_8029FE64_no_inline(gobj, 0);
            ip->xDB0_itcmd_var1 = 2;
            ip->xDD4_itemVar.linkboomerang.xF70 = attrs->x40;
        }
    } else if (ip->xDB4_itcmd_var2 == 0) {
        ip->xDD4_itemVar.linkboomerang.xF70 =
            (ip->xDD4_itemVar.linkboomerang.xF70 - 1.0f);
        if (ip->xDD4_itemVar.linkboomerang.xF70 <= 0.0f) {
            it_8029FE64_no_inline(gobj, 1);
            ip->xDB4_itcmd_var2 = 2;
        }
    }
}

static inline void it_802A0C34_sub_2(Item_GObj* gobj)
{
    Item* ip;
    HSD_JObj* hobj;
    HSD_JObj* child;
    itLinkBoomerangAttributes* attrs;
    Vec3* v;
    Vec3 v2;

    hobj = gobj->hsd_obj;
    ip = gobj->user_data;
    child = HSD_JObjGetChild(hobj);
    if ((ip->xDAC_itcmd_var0 == 2) || (ip->msid == 3)) {
        v = M2C_FIELD(ip, Vec3**,
                      0xDF0 + ip->xDD4_itemVar.linkboomerang.xDD8 * 12);
        HSD_MtxGetRotation(&child->mtx[0], &v2);
        v->x = v2.x;
        v->y = v2.y;
        v->z = v2.z;
        ip->xDD4_itemVar.linkboomerang.xDDC++;
        if (ip->xDD4_itemVar.linkboomerang.xDDC >= 16) {
            ip->xDD4_itemVar.linkboomerang.xDDC = 0;
        }
    }
    it_802A0930(gobj);
}

bool it_802A0C34(Item_GObj* gobj)
{
    Item* ip;
    itLinkBoomerangAttributes* attrs;

    ip = gobj->user_data;
    attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xDD4_itemVar.linkboomerang.xF8C <= 0.0f) {
        if (ip->xDD4_itemVar.bombhei.xDEC == 6) {
            Item_8026AF0C(ip, 0x2715B, 0x7F, 0x40);
        } else {
            Item_8026AF0C(ip, 0x111CB, 0x7F, 0x40);
        }
        ip->xDD4_itemVar.linkboomerang.xF8C = attrs->x38;
    }
    ip->xDD4_itemVar.linkboomerang.xF8C -= 1.0f;
    if (ip->xDAC_itcmd_var0 == 1) {
        it_802A10E4(gobj);
        ip->xDAC_itcmd_var0 = 2;
    }
    it_802A0C34_sub_1(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return 1;
    }
    ip->xD44_lifeTimer -= 1.0f;
    it_802A0C34_sub_2(gobj);
    return false;
}

void it_802A0E70(Item_GObj* gobj)
{
    HSD_JObj* hobj;
    Item* ip;
    ItemStateDesc* item_state_desc;
    PAD_STACK(8);

    ip = GET_ITEM(gobj);
    hobj = gobj->hsd_obj;
    ip->xD0_itemStateDesc =
        ip->xC4_article_data->xC_itemStates->x0_itemStateDesc;
    item_state_desc = ip->xD0_itemStateDesc;
    HSD_JObjAddAnimAll(hobj, item_state_desc->x0_anim_joint,
                       item_state_desc->x4_matanim_joint,
                       item_state_desc->x8_parameters);
    HSD_JObjReqAnimAll(hobj, 0.0f);
    HSD_JObjAnimAll(hobj);
    HSD_JObjRemoveAnimAll(hobj);
    ip->x524_cmd.u = NULL;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itLinkboomerang_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip;
    ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.linkboomerang.xF98 &&
        (ftLk_SpecialS_Is2071b0_5to13(ip->xDD4_itemVar.linkboomerang.xF98) !=
         0))
    {
        it_802A07B4(gobj);
    }
    return false;
}

void it_802A0F84(Item_GObj* gobj) {}

void it_802A0F88(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, 2);
}

bool itLinkboomerang_UnkMotion1_Anim(Item_GObj* gobj)
{
    return it_802A0C34(gobj);
}

void itLinkboomerang_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip;
    f32 angle;
    f32 var_f31;
    itLinkBoomerangAttributes* attrs;

    ip = gobj->user_data;
    attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xDD4_itemVar.linkboomerang.xDE8 != 1) {
        var_f31 = attrs->xC;
        var_f31 = VEC_XY_LENGTH(&ip->x40_vel) - var_f31;
        if (var_f31 < attrs->x18) {
            var_f31 = attrs->x18;
            it_802A1948(gobj, 0);
        }
        ip->x40_vel.x = var_f31 * cosf(ip->xDD4_itemVar.linkboomerang.xF74);
        angle = sinf(ip->xDD4_itemVar.linkboomerang.xF74);
        ip->x40_vel.y = var_f31 * angle;
    }
}

bool itLinkboomerang_UnkMotion1_Coll(Item_GObj* gobj)
{
    itLinkboomerang_UnkMotion2_Coll(gobj);
    return false;
}

void it_802A10E4(Item_GObj* gobj)
{
    HSD_JObj* hobj;
    HSD_JObj* child;
    Item* ip;
    itLinkBoomerangAttributes* attrs;
    Quaternion quat;
    PAD_STACK(8);

    hobj = gobj->hsd_obj;
    ip = gobj->user_data;
    child = HSD_JObjGetChild(hobj);
    attrs = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObjGetRotation(child, &quat);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    HSD_JObjSetRotationZ(hobj, ip->xDD4_itemVar.linkboomerang.xF78);
    HSD_JObjSetRotation(child, &quat);
    loop_lb_8000BA0C(ip, child, attrs->x30);
}

bool itLinkboomerang_UnkMotion2_Anim(Item_GObj* gobj)
{
    return it_802A0C34(gobj);
}

// NOTE: identical to itLinkboomerang_UnkMotion1_Phys
void itLinkboomerang_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip;
    f32 angle;
    f32 var_f31;
    itLinkBoomerangAttributes* attrs;

    ip = gobj->user_data;
    attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xDD4_itemVar.linkboomerang.xDE8 != 1) {
        var_f31 = attrs->xC;
        var_f31 = VEC_XY_LENGTH(&ip->x40_vel) - var_f31;
        if (var_f31 < attrs->x18) {
            var_f31 = attrs->x18;
            it_802A1948(gobj, 0);
        }
        ip->x40_vel.x = var_f31 * cosf(ip->xDD4_itemVar.linkboomerang.xF74);
        angle = sinf(ip->xDD4_itemVar.linkboomerang.xF74);
        ip->x40_vel.y = var_f31 * angle;
    }
}

static void clamp_pi_tau(f32* angle)
{
    if (*angle < -M_PI) {
        *angle += M_TAU;
    } else if (*angle > M_PI) {
        *angle -= M_TAU;
    }
}

f32 it_802A13EC(Item_GObj* gobj)
{
    Point3d sp14;
    Item* ip;
    f32 ret;
    f32 dx;
    f32 dy;
    f32 temp_f0;
    f32 angle;

    ip = gobj->user_data;
    ret = 0.0f;
    if (ip->xDD4_itemVar.linkboomerang.xF98) {
        ftLk_SpecialHi_GetPosWithAdjustedY(ip->xDD4_itemVar.linkboomerang.xF98,
                                           &sp14);
        dx = sp14.x - ip->pos.x;
        dy = sp14.y - ip->pos.y;
        ret = HYPOT(dx, dy);
        if (ip->xDD4_itemVar.linkboomerang.xF80 > 0.0f) {
            ip->xDD4_itemVar.linkboomerang.xF80 -= 1.0f;
        } else if (ip->xDD4_itemVar.linkboomerang.xF80 <= 0.0f) {
            return ret;
        }
        angle = atan2f(dx, dy);
        clamp_pi_tau(&angle);
        angle -= ip->xDD4_itemVar.linkboomerang.xF74;
        clamp_pi_tau(&angle);
        if (angle > ip->xDD4_itemVar.linkboomerang.xF84) {
            angle = ip->xDD4_itemVar.linkboomerang.xF84;
        } else if (angle < -ip->xDD4_itemVar.linkboomerang.xF84) {
            angle = -ip->xDD4_itemVar.linkboomerang.xF84;
        }
        ip->xDD4_itemVar.linkboomerang.xF74 += angle;
        clamp_tau(&ip->xDD4_itemVar.linkboomerang.xF74);
        norm_xF74(ip);
    }
    return ret;
}

void it_802A15EC(Item_GObj* gobj, Point3d* arg1)
{
    Item* ip;
    f32 angle;

    ip = GET_ITEM(gobj);
    angle = lbVector_CosAngle(&ip->x40_vel, arg1);
    if (angle < 0.0f) {
        if (angle > ip->xDD4_itemVar.linkboomerang.xF7C) {
            lbVector_Mirror(&ip->x40_vel, arg1);
            ip->xDD4_itemVar.linkboomerang.xF74 =
                atan2f(ip->x40_vel.y, ip->x40_vel.x);
            clamp_tau(&ip->xDD4_itemVar.linkboomerang.xF74);
            norm_xF74(ip);
            it_802762BC(ip);
        } else {
            it_802A1948(gobj, 0);
        }
    }
}

static void it_802A15EC_no_inline(Item_GObj* gobj, Point3d* arg1)
{
    it_802A15EC(gobj, arg1);
}

bool itLinkboomerang_UnkMotion2_Coll(Item_GObj* gobj)
{
    Item* ip;
    CollData* coll;
    HSD_JObj* hobj;
    HSD_JObj* child;
    Quaternion quat;
    PAD_STACK(8);

    child = HSD_JObjGetChild(gobj->hsd_obj);
    ip = gobj->user_data;
    coll = &ip->x378_itemColl;
    hobj = gobj->hsd_obj;
    if (ip->xDD4_itemVar.linkboomerang.xDE8 != 1) {
        HSD_JObjGetRotation(child, &quat);
        it_8026E0F4(gobj);
        HSD_JObjSetRotationZ(hobj, ip->xDD4_itemVar.linkboomerang.xF78);
        HSD_JObjSetRotation(child, &quat);
        if (ip->facing_dir == -1.0f) {
            if (coll->env_flags & Collide_RightWallMask) {
                it_802A15EC_no_inline(gobj, &coll->right_facing_wall.normal);
            } else if (coll->env_flags & Collide_CeilingMask) {
                it_802A15EC_no_inline(gobj, &coll->ceiling.normal);
            } else if (coll->env_flags & Collide_FloorMask) {
                it_802A15EC_no_inline(gobj, &coll->floor.normal);
            }
        } else {
            if (coll->env_flags & Collide_LeftWallMask) {
                it_802A15EC_no_inline(gobj, &coll->left_facing_wall.normal);
            } else if (coll->env_flags & Collide_CeilingMask) {
                it_802A15EC_no_inline(gobj, &coll->ceiling.normal);
            } else if (coll->env_flags & Collide_FloorMask) {
                it_802A15EC_no_inline(gobj, &coll->floor.normal);
            }
        }
    }
    return false;
}

static void it_802A19E0_no_inline(Item_GObj* gobj)
{
    it_802A19E0(gobj);
}

void it_802A1948(Item_GObj* gobj, s32 arg1)
{
    Item* ip;
    itLinkBoomerangAttributes* attrs;

    ip = GET_ITEM(gobj);
    attrs = ip->xC4_article_data->x4_specialAttributes;
    clamp_angle_pi(&ip->xDD4_itemVar.linkboomerang.xF74);
    if (arg1 != 0) {
        ip->xDD4_itemVar.linkboomerang.xF84 = DEG2RAD * attrs->x24;
    } else {
        ip->xDD4_itemVar.linkboomerang.xF84 = DEG2RAD * attrs->x20;
    }
    ip->xDD4_itemVar.linkboomerang.xF80 = attrs->x28;
    it_802A19E0_no_inline(gobj);
}

void it_802A19E0(Item_GObj* gobj)
{
    HSD_JObj* hobj;
    HSD_JObj* child;
    Item* ip;
    s32 i;
    itLinkBoomerangAttributes* attrs;
    Quaternion quat;
    PAD_STACK(8);

    hobj = gobj->hsd_obj;
    child = HSD_JObjGetChild(hobj);
    ip = gobj->user_data;
    attrs = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObjGetRotation(child, &quat);
    ip->xDD4_itemVar.linkboomerang.xF88 =
        -(2.0f * child->rotate.z) / attrs->x8;
    ip->xDD4_itemVar.linkboomerang.xDE4 = attrs->x8;
    if (ip->msid == 1) {
        Item_80268E5C(gobj, 3, 0x12);
    } else {
        Item_80268E5C(gobj, 3, 0x110);
    }
    HSD_JObjSetRotationZ(hobj, ip->xDD4_itemVar.linkboomerang.xF78);
    HSD_JObjSetRotation(child, &quat);
    loop_lb_8000BA0C(ip, child, 1.0f);
}

bool itLinkboomerang_UnkMotion3_Anim(Item_GObj* gobj)
{
    HSD_JObj* child;
    Item* ip;
    f32 rot_z;
    PAD_STACK(4);

    ip = GET_ITEM(gobj);
    child = HSD_JObjGetChild(gobj->hsd_obj);
    if (ip->xDD4_itemVar.linkboomerang.xDE4 != 0) {
        rot_z = HSD_JObjGetRotationZ(child);
        HSD_JObjSetRotationZ(child,
                             rot_z + ip->xDD4_itemVar.linkboomerang.xF88);
        ip->xDD4_itemVar.linkboomerang.xDE4 -= 1;
    }
    return it_802A0C34(gobj);
}

static inline void itLinkboomerang_UnkMotion3_Phys_sub(Item_GObj* gobj,
                                                       f32 angle)
{
    Item* ip = GET_ITEM(gobj);
    itLinkBoomerangAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    Fighter_Part part;
    if ((ip->msid == 3) && (angle < attrs->x2C)) {
        if (ip->xDD4_itemVar.linkboomerang.xF98) {
            if ((ftLk_SpecialS_Is2071b0_1to13(
                     ip->xDD4_itemVar.linkboomerang.xF98) == 0) &&
                (ftLk_SepcialS_Get2219b5(
                     ip->xDD4_itemVar.linkboomerang.xF98) == 0))
            {
                ftLk_SpecialS2_Enter(ip->xDD4_itemVar.linkboomerang.xF98);
                part = ftLk_SpecialHi_ProcessPartLThumbNb(
                    ip->xDD4_itemVar.linkboomerang.xF98);
                Item_8026AB54(gobj, ip->xDD4_itemVar.linkboomerang.xF98, part);
            } else {
                remove_boomerang(gobj);
                Item_8026A8EC(gobj);
            }
        }
        it_802A0810(gobj);
    }
}

void itLinkboomerang_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    itLinkBoomerangAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    f32 xC;
    f32 length;
    if (ip->xDD4_itemVar.linkboomerang.xDE8 != 1) {
        xC = attrs->xC;
        length = VEC_XY_LENGTH(&ip->x40_vel) + attrs->xC;
        if (length > xC) {
            length = xC;
        }
        ip->x40_vel.x = length * cosf(ip->xDD4_itemVar.linkboomerang.xF74);
        ip->x40_vel.y = length * sinf(ip->xDD4_itemVar.linkboomerang.xF74);
        itLinkboomerang_UnkMotion3_Phys_sub(gobj, it_802A13EC(gobj));
    }
}

bool it_802A1F08(Item_GObj* gobj)
{
    Item* ip;
    itLinkBoomerangAttributes* attrs;

    ip = GET_ITEM(gobj);
    if ((ip->xDD4_itemVar.linkboomerang.xDE8 != 1) &&
        ((ip->msid == 1) || (ip->msid == 2)))
    {
        attrs = ip->xC4_article_data->x4_specialAttributes;
        clamp_angle_pi(&ip->xDD4_itemVar.linkboomerang.xF74);
        ip->xDD4_itemVar.linkboomerang.xF84 = DEG2RAD * attrs->x24;
        ip->xDD4_itemVar.linkboomerang.xF80 = attrs->x28;
        it_802A19E0_no_inline(gobj);
    }
    return false;
}

// NOTE: identical to it_802A1F08
bool it_802A1FA8(Item_GObj* gobj)
{
    Item* ip;
    itLinkBoomerangAttributes* attrs;

    ip = GET_ITEM(gobj);
    if ((ip->xDD4_itemVar.linkboomerang.xDE8 != 1) &&
        ((ip->msid == 1) || (ip->msid == 2)))
    {
        attrs = ip->xC4_article_data->x4_specialAttributes;
        clamp_angle_pi(&ip->xDD4_itemVar.linkboomerang.xF74);
        ip->xDD4_itemVar.linkboomerang.xF84 = DEG2RAD * attrs->x24;
        ip->xDD4_itemVar.linkboomerang.xF80 = attrs->x28;
        it_802A19E0_no_inline(gobj);
    }
    return false;
}

// NOTE: identical to it_802A1F08
bool it_2725_Logic18_Absorbed(Item_GObj* gobj)
{
    Item* ip;
    itLinkBoomerangAttributes* attrs;

    ip = GET_ITEM(gobj);
    if ((ip->xDD4_itemVar.linkboomerang.xDE8 != 1) &&
        ((ip->msid == 1) || (ip->msid == 2)))
    {
        attrs = ip->xC4_article_data->x4_specialAttributes;
        clamp_angle_pi(&ip->xDD4_itemVar.linkboomerang.xF74);
        ip->xDD4_itemVar.linkboomerang.xF84 = DEG2RAD * attrs->x24;
        ip->xDD4_itemVar.linkboomerang.xF80 = attrs->x28;
        it_802A19E0_no_inline(gobj);
    }
    return false;
}

bool it_802A20E8(Item_GObj* gobj)
{
    Vec3 sp14;
    HSD_GObj* var_r3;
    Item* ip;
    f32 var_f0;
    f32 var_f31;

    ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.linkboomerang.xDE8 != 1) {
        if (!ip->xDCC_flag.b1) {
            var_r3 = ip->owner;
        } else {
            var_r3 = ip->xC64_reflectGObj;
        }
        ip->xDD4_itemVar.linkboomerang.xDE8 = 1;
        ip->xD44_lifeTimer = ip->xD48_halfLifeTimer;
        ftLib_800866DC(var_r3, &sp14);
        ip->xDD4_itemVar.linkboomerang.xF74 =
            atan2f(ip->pos.y - sp14.y, ip->pos.x - sp14.x);
        clamp_tau(&ip->xDD4_itemVar.linkboomerang.xF74);
        var_f31 = VEC_XY_LENGTH(&ip->x40_vel);
        ip->x40_vel.x =
            ip->xC70 * (var_f31 * cosf(ip->xDD4_itemVar.linkboomerang.xF74));
        ip->x40_vel.y =
            ip->xC70 * (var_f31 * sinf(ip->xDD4_itemVar.linkboomerang.xF74));
        if (ip->xDD4_itemVar.linkboomerang.xF98) {
            ftLk_SpecialS_RemoveBoomerang0(
                ip->xDD4_itemVar.linkboomerang.xF98);
        }
        norm_xF74(ip);
    }
    return false;
}

// NOTE: identical to it_802A1F08 except for the msid check
bool it_802A2288(Item_GObj* gobj)
{
    Item* ip;
    itLinkBoomerangAttributes* attrs;

    ip = GET_ITEM(gobj);
    if ((ip->xDD4_itemVar.linkboomerang.xDE8 != 1) && (ip->msid != 3)) {
        attrs = ip->xC4_article_data->x4_specialAttributes;
        clamp_angle_pi(&ip->xDD4_itemVar.linkboomerang.xF74);
        ip->xDD4_itemVar.linkboomerang.xF84 = DEG2RAD * attrs->x24;
        ip->xDD4_itemVar.linkboomerang.xF80 = attrs->x28;
        it_802A19E0_no_inline(gobj);
    }
    return false;
}

bool it_802A2320(Item_GObj* gobj)
{
    Item* ip;
    ip = GET_ITEM(gobj);
    lbVector_Mirror(&ip->x40_vel, &ip->xC58);
    ip->xDD4_itemVar.linkboomerang.xF74 = atan2f(ip->x40_vel.y, ip->x40_vel.x);
    clamp_tau(&ip->xDD4_itemVar.linkboomerang.xF74);
    norm_xF74(ip);
    return false;
}

void it_802A23CC(Item_GObj* gobj, HSD_GObj* arg1)
{
    Item* ip;

    ip = GET_ITEM(gobj);
    it_8026B894(gobj, arg1);
    if (ip->xDD4_itemVar.linkboomerang.xF98 == arg1) {
        ip->xDD4_itemVar.linkboomerang.xF98 = NULL;
    }
}
