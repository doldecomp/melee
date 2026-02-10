#include "ittaru.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/jobj.h"
#include "baselib/random.h"
#include "cm/camera.h"
#include "ef/efsync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/itcoll.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbvector.h"

void it_3F14_Logic2_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    float temp;
    ip->facing_dir = -1.0f;
    ip->xD5C = 0;
    ip->xDCE_flag.b7 = 0;
    ip->xDAC_itcmd_var0 = 0;
    ip->xDB0_itcmd_var1 = 0;
    ip->xDD4_itemVar.taru.xDD4 = 0;
    /// @todo float regswap. same as in it_3F14_Logic5_Spawned
    temp = 0.34906584f * HSD_Randf();
    ip->xDD4_itemVar.taru.xDDC = 1.3089969f + temp;
    ip->xDD4_itemVar.taru.xDE0 = 0.0f;
    ip->xDD4_itemVar.taru.xDE4 = 0.0f;
    ip->xDD4_itemVar.taru.xDE8.x = 0.0f;
    ip->xDD4_itemVar.taru.xDE8.y = 1.0f;
    ip->xDD4_itemVar.taru.xDE8.z = 0.0f;
    it_80287D0C(gobj);
}

static inline f32 inline_fabsf(f32 x)
{
    if (x < 0.0F) {
        return -x;
    } else {
        return +x;
    }
}

void it_802874F0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTaruAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    f32 temp_f1;
    f32 temp_f2;
    f32 var_f0;
    int new_var2;
    f32 var_f1;
    f32 new_var;
    f32 var_f2;

    if (ip->ground_or_air != GA_Air) {
        /// @todo this surely uses some type of fabs
        /// but everything ive tried causes a reg swap
        var_f1 = ip->xDD4_itemVar.taru.xDE8.x;
        temp_f2 = var_f1;
        new_var2 = temp_f2 < 0.0f;
        if (new_var2) {
            var_f1 = -temp_f2;
        } else {
            var_f1 = temp_f2;
        }
        if (var_f1 > 0.1f) {
            var_f1 = ip->xDD4_itemVar.taru.xDE4;
            if (var_f1 < 0.0f) {
                var_f1 = -var_f1;
            }
            if (var_f1 < attr->x2C) {
                ip->xDD4_itemVar.taru.xDE4 +=
                    temp_f2 * attr->x24;
            }
        } else {
            temp_f1 = ip->xDD4_itemVar.taru.xDE4;
            if (temp_f1 < 0.0f) {
                var_f0 = -temp_f1;
            } else {
                var_f0 = temp_f1;
            }
            temp_f2 = attr->x28;
            if (var_f0 < temp_f2) {
                ip->xDD4_itemVar.taru.xDE4 = 0.0f;
            } else if (ip->xDD4_itemVar.taru.xDE4 > 0.0f) {
                ip->xDD4_itemVar.taru.xDE4 -= temp_f2;
            } else {
                ip->xDD4_itemVar.taru.xDE4 += temp_f2;
            }
        }
        temp_f2 = ip->xDD4_itemVar.taru.xDE4;
        if ((temp_f2 > 0.0f && ip->facing_dir < 0.0f) ||
            (temp_f2 < 0.0f && ip->facing_dir > 0.0f))
        {
            ip->facing_dir *= -1.0f;
        }
        var_f1 = inline_fabsf(ip->xDD4_itemVar.taru.xDE4);
        temp_f2 = attr->x20;
        if (var_f1 > temp_f2) {
            ip->xDD4_itemVar.taru.xDE4 = temp_f2 * ip->facing_dir;
        }
        ip->x40_vel.x =
            ip->xDD4_itemVar.taru.xDE4 * ip->xDD4_itemVar.taru.xDE8.y;
        var_f2 = inline_fabsf(ip->xDD4_itemVar.taru.xDE4);
        ip->xDD4_itemVar.taru.xDE0 =
            (0.12217305f * var_f2 * -ip->facing_dir) +
            ip->xDD4_itemVar.taru.xDE0;
    } else {
        ip->xDD4_itemVar.taru.xDE0 =
            (0.10471976f * -ip->facing_dir) + ip->xDD4_itemVar.taru.xDE0;
    }
}

void it_80287690(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 step = 1.5707964f /
               ((itTaruAttributes*) ip->xC4_article_data->x4_specialAttributes)
                   ->x18;
    HSD_JObj* child = HSD_JObjGetChild(jobj);
    f32 var_f31;
    f32 rot;

    if (ip->xDB0_itcmd_var1 != 0) {
        var_f31 = HSD_JObjGetRotationZ(child);
        if (var_f31 > (1.5882496f + step)) {
            var_f31 -= step;
        } else if (var_f31 < (1.553343f - step)) {
            var_f31 += step;
        } else {
            var_f31 = 1.5707964f;
            ip->xDB0_itcmd_var1 = 0;
        }
        HSD_JObjSetRotationZ(child, var_f31);

        var_f31 = ip->xDD4_itemVar.taru.xDDC;
        rot = HSD_JObjGetRotationX(child);
        if (rot > (0.017453292f + var_f31 + step)) {
            var_f31 = rot - step;
        } else if (rot < ((var_f31 - 0.017453292f) - step)) {
            var_f31 = rot + step;
        }
        HSD_JObjSetRotationX(child, var_f31);
    } else {
        HSD_JObjSetRotationZ(child, 1.5707964f);
        HSD_JObjSetRotationX(child, ip->xDD4_itemVar.taru.xDDC);
    }
    HSD_JObjSetRotationZ(jobj, 0.0f);
    HSD_JObjSetRotationZ(jobj, ip->xDD4_itemVar.taru.xDE0);
}

bool itTaru_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 1.0F) {
        it_802787B4(gobj, 0x421);
    }
    return false;
}

void itTaru_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itTaru_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTaruAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    CollData* coll = &ip->x378_itemColl;
    Vec3 up;
    f32 ground_rot;

    if (it_8026D564(gobj) == 0) {
        it_802762BC(ip);
        it_80287D0C(gobj);
        return false;
    }
    if (ip->ground_or_air != GA_Air && (coll->env_flags & 0x18000)) {
        it_80276408(gobj, coll, &ip->xDD4_itemVar.taru.xDE8);
        up.x = 0.0f;
        up.y = 1.0f;
        up.z = 0.0f;
        if (lbVector_AngleXY(&ip->xDD4_itemVar.taru.xDE8, &up) > attr->x14) {
            if (ip->xDD4_itemVar.taru.xDE8.x > 0.0f) {
                ip->facing_dir = 1.0f;
            } else {
                ip->facing_dir = -1.0f;
            }
            ip->xDD4_itemVar.taru.xDE4 = 0.1f * ip->facing_dir;
            it_80288194(gobj);
            return false;
        }
        ground_rot = it_8027649C(gobj);
        HSD_JObjSetRotationZ(jobj, ground_rot);
    }
    return false;
}

void it_80287D0C(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itTaru_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itTaru_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itTaru_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    itTaruAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    f32 var_f1;

    if (it_8026DA08(gobj) != 0) {
        it_802762B0(ip);
        Item_8026AE84(ip, 0x104, 0x7F, 0x40);
        var_f1 = ip->x40_vel.y;
        if (var_f1 < 0.0f) {
            var_f1 = -var_f1;
        }
        if (var_f1 < attr->x34) {
            ip = GET_ITEM(gobj);
            ip->x40_vel.z = 0.0f;
            ip->x40_vel.y = 0.0f;
            ip->x40_vel.x = 0.0f;
            it_8026B390(gobj);
            Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
        } else {
            it_802762BC(ip);
            ip->x40_vel.y *= -attrs->x58;
        }
    }
    return false;
}

void itTaru_Logic2_PickedUp(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDB0_itcmd_var1 = 1;
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itTaru_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itTaru_UnkMotion2_Phys(Item_GObj* gobj) {}

void itTaru_Logic2_Dropped(Item_GObj* gobj)
{
    it_80287F20(gobj);
}

void itTaru_Logic2_Thrown(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    lb_8000B804(gobj->hsd_obj, ip->xC4_article_data->x10_modelDesc->x0_joint);
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

void it_80287F20(Item_GObj* gobj)
{
    PAD_STACK(16);
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 3,
                  ITEM_HIT_PRESERVE | ITEM_DROP_UPDATE | ITEM_UNK_0x1);
}

bool itTaru_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xD44_lifeTimer -= 1.0f;
    if (ip->xD44_lifeTimer <= 0.0f) {
        it_802787B4(gobj, 0x421);
        return true;
    }
    if (ip->xD44_lifeTimer <= it_804D6D28->x34) {
        it_802728C8(gobj);
    }
    return false;
}

void itTaru_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_80272860(gobj, ip->xCC_item_attr->x10_fall_speed,
                ip->xCC_item_attr->x14_fall_speed_max);
    it_802874F0(gobj);
    it_80287690(gobj);
}

bool itTaru_UnkMotion3_Coll(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ItemAttr* attrs = ip->xCC_item_attr;
    itTaruAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    f32 var_f1;

    if (it_8026DA08(gobj) != 0) {
        it_802762B0(ip);
        Item_8026AE84(ip, 0x104, 0x7F, 0x40);
        var_f1 = (ip->x40_vel.y < 0.0f) ? -ip->x40_vel.y : ip->x40_vel.y;
        if (var_f1 > attr->x34) {
            return it_3F14_Logic2_DmgDealt(gobj);
        }
        var_f1 = (ip->x40_vel.y < 0.0f) ? -ip->x40_vel.y : ip->x40_vel.y;
        if (var_f1 < attrs->x5c) {
            var_f1 = (ip->x40_vel.x < 0.0f) ? -ip->x40_vel.x : ip->x40_vel.x;
            ip->xDD4_itemVar.taru.xDE4 = ip->facing_dir * var_f1;
            it_802881B4(gobj);
        } else {
            it_802762BC(ip);
            ip->x40_vel.y *= -attrs->x58;
        }
    } else if (it_802763E0(gobj) != 0) {
        if (ip->x40_vel.y > 0.0f) {
            ip->x40_vel.y = 0.0f;
        }
    } else if (it_80276308(gobj) != 0) {
        return it_3F14_Logic2_DmgDealt(gobj);
    }
    it_80287690(gobj);
    return false;
}

void it_80288194(Item_GObj* gobj)
{
    it_802881FC(gobj);
}

void it_802881B4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    lb_8000B804(gobj->hsd_obj,
                ip->xC4_article_data->x10_modelDesc->x0_joint);
    it_802881FC(gobj);
}

void it_802881FC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    ip->x40_vel.x = ip->xDD4_itemVar.taru.xDE4;
    ip->x40_vel.y = 0.0f;
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

bool itTaru_UnkMotion5_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDAC_itcmd_var0 == 1) {
        ip->xDAC_itcmd_var0 = 2;
        it_80275444(gobj);
    }
    ip = GET_ITEM(gobj);
    ip->xD44_lifeTimer -= 1.0f;
    if (ip->xD44_lifeTimer <= 0.0f) {
        it_802787B4(gobj, 0x421);
        return true;
    }
    if (ip->xD44_lifeTimer <= it_804D6D28->x34) {
        it_802728C8(gobj);
    }
    return false;
}

void itTaru_UnkMotion5_Phys(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_802874F0(gobj);
    it_80287690(gobj);
}

bool itTaru_UnkMotion5_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTaruAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    CollData* coll = &ip->x378_itemColl;
    f32 var_f1;
    s32 env_flags;

    it_8026D62C(gobj, it_80287F20);
    if (ip->ground_or_air != GA_Air) {
        if (coll->env_flags & 0x18000) {
            it_80276408(gobj, coll, &ip->xDD4_itemVar.taru.xDE8);
        } else {
            ip->xDD4_itemVar.taru.xDE8.x = 0.0f;
        }
        env_flags = coll->env_flags;
        if ((env_flags & 0x3F) || (env_flags & 0xFC0)) {
            var_f1 = ip->xDD4_itemVar.taru.xDE4;
            if (var_f1 < 0.0f) {
                var_f1 = -var_f1;
            }
            if (var_f1 > attr->x2C) {
                return it_3F14_Logic2_DmgDealt(gobj);
            }
            ip->facing_dir = -ip->facing_dir;
            ip->xDD4_itemVar.taru.xDE4 =
                -(ip->xDD4_itemVar.taru.xDE4 * attr->x30);
            ip->x40_vel.x =
                ip->xDD4_itemVar.taru.xDE4 * ip->xDD4_itemVar.taru.xDE8.y;
            it_80275444(gobj);
        }
    }
    it_80287690(gobj);
    return false;
}

bool itTaru_UnkMotion4_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xD44_lifeTimer -= 1.0f;
    if (ip->xD44_lifeTimer <= 0.0f) {
        it_802787B4(gobj, 0x421);
        return true;
    }
    if (ip->xD44_lifeTimer <= it_804D6D28->x34) {
        it_802728C8(gobj);
    }
    return false;
}

static inline void itTaru_UnkMotion4_Phys_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.x = ip->xDD4_itemVar.taru.xDE4;
    ip->x40_vel.y = 0.0f;
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    it_80275444(gobj);
}

void itTaru_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTaruAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    f32 var_f1;

    it_802874F0(gobj);
    it_80287690(gobj);
    var_f1 = ip->xDD4_itemVar.taru.xDE4;
    if (var_f1 < 0.0f) {
        var_f1 = -var_f1;
    }
    if (var_f1 > attr->x1C) {
        itTaru_UnkMotion4_Phys_inline(gobj);
    }
    var_f1 = ip->xDD4_itemVar.taru.xDE4;
    if (var_f1 < 0.0f) {
        var_f1 = -var_f1;
    }
    if (var_f1 < 0.01f) {
        it_80275444(gobj);
    }
}

bool itTaru_UnkMotion4_Coll(Item_GObj* gobj)
{
    return itTaru_UnkMotion5_Coll(gobj);
}

void it_802885C8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Vec3 pos;

    it_8026BB44(gobj);
    it_80272C08(gobj);
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    it_8026BD24(gobj);
    it_8027518C(gobj);

    ip->x40_vel.x = 0.0F;
    ip->x40_vel.y = 0.0F;
    ip->xDCF_flag.b2 = 1;
    ip->xDD4_itemVar.taru.xDD4 = 1;
    ip->xDD4_itemVar.taru.xDD8 = 40;

    it_80275444(gobj);

    pos = ip->pos;
    lb_800119DC(&pos, 0x78, 1.0F, 0.02F, 1.0471976F);

    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

bool itTaru_UnkMotion6_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void itTaru_UnkMotion6_Phys(Item_GObj* gobj) {}

bool itTaru_UnkMotion6_Coll(Item_GObj* gobj)
{
    return false;
}

static inline void it_802886C4_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Vec3 zero;

    /// @todo 4 byte gap for these accesses...
    zero.x = zero.y = zero.z = 0.0f;
    if (!it_8026F8B4(gobj, &ip->pos, &zero, false) &&
        it_8026F6BC(gobj, &ip->pos, &zero, false) == NULL)
    {
        it_8026F3D4(gobj, NULL, 1, false);
    }
}

void it_802886C4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Item_8026AE84(ip, 0xFB, 0x7F, 0x40);
    Camera_80030E44(2, &ip->pos);
    it_802886C4_inline(gobj);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    it_802756D0(gobj);
    ip->x40_vel.x = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->xDCF_flag.b2 = 1;
    ip->xDD4_itemVar.taru.xDD4 = 1;
    ip->xDD4_itemVar.taru.xDD8 = 0x28;
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
}

bool itTaru_UnkMotion7_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.taru.xDD8 -= 1;
    if (ip->xDD4_itemVar.taru.xDD8 > 0) {
        return false;
    }
    return true;
}

void itTaru_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itTaru_UnkMotion7_Coll(Item_GObj* gobj)
{
    return false;
}

static inline bool itTaru_RandCheck(itTaruAttributes* attr)
{
    s32 x4 = attr->x4;
    s32 x0 = attr->x0;
    if (HSD_Randi(x0 + x4) < x0) {
        return true;
    }
    return false;
}

static inline void it_3F14_Logic2_inline(Item_GObj* gobj, Item* ip, itTaruAttributes* attr)
{
    efSync_Spawn(0x427, gobj, &ip->pos);
    if (itTaru_RandCheck(attr)) {
        it_802886C4(gobj);
    } else {
        it_802885C8(gobj);
    }
}

bool it_3F14_Logic2_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(24);

    if (ip->xDD4_itemVar.taru.xDD4 == 0) {
        itTaruAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
        it_3F14_Logic2_inline(gobj, ip, attr);
    }
    return false;
}

bool it_3F14_Logic2_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(24);

    if (ip->xDD4_itemVar.taru.xDD4 == 0) {
        itTaruAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
        it_3F14_Logic2_inline(gobj, ip, attr);
    }
    return false;
}

bool it_3F14_Logic2_HitShield(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(24);

    if (ip->xDD4_itemVar.taru.xDD4 == 0) {
        itTaruAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
        it_3F14_Logic2_inline(gobj, ip, attr);
    }
    return false;
}

bool it_3F14_Logic2_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(24);

    if (ip->xDD4_itemVar.taru.xDD4 == 0) {
        itTaruAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
        it_3F14_Logic2_inline(gobj, ip, attr);
    }
    return false;
}

bool it_3F14_Logic2_DmgReceived(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTaruAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    s32 x0;
    s32 var_r0;
    PAD_STACK(24);

    if (ip->xDD4_itemVar.taru.xDD4 == 0) {
        if (ip->xC9C >= attr->xC) {
            it_3F14_Logic2_inline(gobj, ip, attr);
        } else {
            if (ip->msid == 0) {
                if (HSD_Randi(attr->x8) == 0) {
                    ip->facing_dir = -ip->xCCC_incDamageDirection;
                    ip->xDD4_itemVar.taru.xDE4 =
                        ip->facing_dir * (ip->xCA0 * attr->x10);
                    it_8027236C(gobj);
                    ip = GET_ITEM(gobj);
                    ip->x40_vel.x = ip->xDD4_itemVar.taru.xDE4;
                    ip->x40_vel.y = 0.0f;
                    it_8026B3A8(gobj);
                    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
                }
            } else if ((u32) (ip->msid - 4) <= 1u) {
                ip->xDD4_itemVar.taru.xDE4 =
                    (-ip->xCCC_incDamageDirection *
                     (ip->xCA0 * attr->x10)) +
                    ip->xDD4_itemVar.taru.xDE4;
                it_8027236C(gobj);
                it_80275444(gobj);
            }
        }
    }
    return false;
}

void itTaru_Logic2_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
