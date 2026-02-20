#include "ittarucann.h"

#include "cm/camera.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_Barrel.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"
#include "MSL/math.h"

#include <baselib/jobj.h>
#include <baselib/random.h>

extern lbColl_80008D30_arg1 it_803B8610;
extern Vec3 it_803B8634;

inline void inline_itTarucann_SetRotationZ(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    Item* ip;
    jobj = GET_JOBJ(gobj);
    ip = GET_ITEM(gobj);
    HSD_JObjSetRotationZ(jobj, 0.0f);
    HSD_JObjSetRotationZ(jobj, ip->xDD4_itemVar.tarucann.xC);
}

void it_80295ED4(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = gobj->user_data;
        if (ip != NULL) {
            ip->xDD4_itemVar.tarucann.x20 = ip->grab_victim;
            ip->xDD0_flag.b5 = false;
            it_80274ECC(gobj, true);
            it_80297790(gobj);
        }
    }
}

void it_80295F38(Item_GObj* gobj)
{
    Vec3 launch_pos;
    lbColl_80008D30_arg1 params;
    Item* ip;
    itTaruCann_DatAttrs* da;
    f32 angle;

    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        da = ip->xC4_article_data->x4_specialAttributes;
        params = it_803B8610;
        params.state = 1;
        params.damage = da->x30;
        params.kb_angle = da->x34;
        params.unkC = da->x38;
        params.unk10 = da->x3C;
        params.unk14 = da->x40;
        params.element = da->x44;
        angle = M_PI_2 + ip->xDD4_itemVar.tarucann.xC;
        while (angle < 0.0f) {
            angle += 2.0 * M_PI;
        }
        while (angle > 2.0 * M_PI) {
            angle -= 2.0 * M_PI;
        }
        launch_pos = ip->pos;
        launch_pos.x += 8.0f * cosf(angle);
        launch_pos.y += 8.0f * sinf(angle);
        ftCo_800C92E4(ip->xDD4_itemVar.tarucann.x20, &launch_pos, &ip->pos,
                      &params, (f32) (180.0 / M_PI) * angle);
        it_802975F4(gobj);
    }
}

int it_802960B8(Item_GObj* gobj)
{
    itTaruCann_DatAttrs* da =
        GET_ITEM(gobj)->xC4_article_data->x4_specialAttributes;
    return da->x2C;
}

int it_802960CC(Item_GObj* gobj)
{
    itTaruCann_DatAttrs* da =
        GET_ITEM(gobj)->xC4_article_data->x4_specialAttributes;
    return da->x28;
}

void it_3F14_Logic5_Destroyed(Item_GObj* gobj)
{
    Item* ip;
    if (gobj != NULL) {
        ip = gobj->user_data;
        if (ip != NULL && ip->xDD4_itemVar.tarucann.x20 != 0) {
            it_80295F38(gobj);
        }
    }
}

void it_3F14_Logic5_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTaruCann_DatAttrs* da = ip->xC4_article_data->x4_specialAttributes;
    float temp;
    ip->facing_dir = -1.0f;
    ip->xD5C = 0;
    ip->xDCE_flag.b7 = false;
    ip->xDAC_itcmd_var0 = 0;
    ip->xDB0_itcmd_var1 = 0;
    ip->xDD4_itemVar.tarucann.x0 = 0;
    /// @todo float regswap. same as in it_3F14_Logic2_Spawned
    temp = 0.34906584f * HSD_Randf();
    ip->xDD4_itemVar.tarucann.x8 = temp + 1.3089969f;
    ip->xDD4_itemVar.tarucann.xC = 0.0f;
    ip->xDD4_itemVar.tarucann.x10 = 0.0f;
    ip->xDD4_itemVar.tarucann.x14.x = 0.0f;
    ip->xDD4_itemVar.tarucann.x14.y = 1.0f;
    ip->xDD4_itemVar.tarucann.x14.z = 0.0f;
    ip->xDD4_itemVar.tarucann.x20 = 0;
    ip->xDD4_itemVar.tarucann.x24 = 0;
    ip->xDD4_itemVar.tarucann.x28 = 1.0f;
    it_80275158(gobj, da->x24);
    it_80296694(gobj);
}

bool it_802961E8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if (ip->xD44_lifeTimer <= 2.0f) {
        it_8026B3A8(gobj);
    }
    if (ip->xDD4_itemVar.tarucann.x20 == 0) {
        ip->xD44_lifeTimer -= 1.0f;
        if (ip->xD44_lifeTimer <= 0.0f) {
            it_802787B4(gobj, 0x421);
            return true;
        }
        if (ip->xD44_lifeTimer <= it_804D6D28->x34) {
            it_802728C8(gobj);
        } else {
            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        }
    } else {
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    }
    return false;
}

void it_802962E0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTaruCann_DatAttrs* da = ip->xC4_article_data->x4_specialAttributes;
    f32 temp_f1;
    f32 temp_f2;
    f32 var_f0;
    int new_var2;
    f32 var_f1;
    f32 new_var;
    f32 var_f2;
    if (ip->ground_or_air != GA_Air) {
        var_f1 = ip->xDD4_itemVar.tarucann.x14.x;
        temp_f2 = var_f1;
        new_var2 = temp_f2 < 0.0f;
        if (new_var2) {
            var_f1 = -temp_f2;
        } else {
            var_f1 = temp_f2;
        }
        if (var_f1 > 0.1f) {
            var_f1 = ip->xDD4_itemVar.tarucann.x10;
            if (var_f1 < 0.0f) {
                var_f1 = -var_f1;
            }
            if (var_f1 < da->x18) {
                ip->xDD4_itemVar.tarucann.x10 += temp_f2 * da->x10;
            }
        } else {
            temp_f1 = ip->xDD4_itemVar.tarucann.x10;
            if (temp_f1 < 0.0f) {
                var_f0 = -temp_f1;
            } else {
                var_f0 = temp_f1;
            }
            new_var = da->x14;
            var_f2 = new_var;
            if (var_f0 < var_f2) {
                ip->xDD4_itemVar.tarucann.x10 = 0.0f;
            } else {
                if (temp_f1 > 0.0f) {
                    var_f2 = -var_f2;
                }
                ip->xDD4_itemVar.tarucann.x10 = temp_f1 + var_f2;
            }
        }
        temp_f2 = ip->xDD4_itemVar.tarucann.x10;
        if ((temp_f2 > 0.0f && ip->facing_dir == -1.0f) ||
            (temp_f2 < 0.0f && ip->facing_dir == 1.0f))
        {
            ip->facing_dir = -ip->facing_dir;
        }
        var_f1 = ip->xDD4_itemVar.tarucann.x10;
        if (var_f1 < 0.0f) {
            var_f1 = -var_f1;
        }
        temp_f2 = da->xC;
        if (var_f1 > temp_f2) {
            ip->xDD4_itemVar.tarucann.x10 = temp_f2 * ip->facing_dir;
        }
        ip->x40_vel.x =
            ip->xDD4_itemVar.tarucann.x28 *
            (ip->xDD4_itemVar.tarucann.x10 * ip->xDD4_itemVar.tarucann.x14.y);
        var_f2 = ip->xDD4_itemVar.tarucann.x10;
        if (var_f2 < 0.0f) {
            var_f2 = -var_f2;
        }
        ip->xDD4_itemVar.tarucann.xC +=
            ip->xDD4_itemVar.tarucann.x28 *
            (0.12217305f * var_f2 * -ip->facing_dir);
    } else {
        ip->xDD4_itemVar.tarucann.xC +=
            0.10471976f * -ip->facing_dir * ip->xDD4_itemVar.tarucann.x28;
    }
    ip->xDD4_itemVar.tarucann.xC += da->x50 * -ip->facing_dir;
}

bool itTarucann_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.tarucann.x20 == 0) {
        ip->xDCC_flag.b3 = true;
    } else {
        ip->xDCC_flag.b3 = false;
    }
    return it_802961E8(gobj);
}

void itTarucann_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itTarucann_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    itTaruCann_DatAttrs* da = ip->xC4_article_data->x4_specialAttributes;
    CollData* coll = &ip->x378_itemColl;
    Vec3 normal = it_803B8634;
    if (it_8026D564(gobj) == 0) {
        it_802762BC(ip);
        it_80296694(gobj);
    } else if (coll->env_flags & 0x18000) {
        it_80276408(gobj, coll, &ip->xDD4_itemVar.tarucann.x14);
        if (lbVector_AngleXY(&ip->xDD4_itemVar.tarucann.x14, &normal) > da->x0)
        {
            f32 var_f0;
            if (ip->xDD4_itemVar.tarucann.x14.x > 0.0f) {
                var_f0 = 1.0f;
            } else {
                var_f0 = -1.0f;
            }
            ip->facing_dir = var_f0;
            ip->xDD4_itemVar.tarucann.x10 = 0.1f * ip->facing_dir;
            it_80296E88(gobj);
        } else {
            f32 rot = it_8027649C(gobj);
            HSD_JObjSetRotationZ(jobj, rot);
        }
    }
    return false;
}

void it_80296694(Item_GObj* gobj)
{
    PAD_STACK(8);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_8026B3A8(gobj);
}

bool itTarucann_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.tarucann.x20 == 0) {
        ip->xDCC_flag.b3 = true;
    } else {
        ip->xDCC_flag.b3 = false;
    }
    return it_802961E8(gobj);
}

void itTarucann_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itTarucann_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    itTaruCann_DatAttrs* da = ip->xC4_article_data->x4_specialAttributes;
    f32 y;
    if (it_8026DA08(gobj) != 0) {
        it_802762B0(ip);
        y = ip->x40_vel.y;
        if (y < 0.0f) {
            y = -y;
        }
        if (y < da->x20) {
            Item* ip2 = GET_ITEM(gobj);
            ip2->x40_vel.x = ip2->x40_vel.y = ip2->x40_vel.z = 0.0f;
            it_8026B390(gobj);
            Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
        } else {
            it_802762BC(ip);
            ip->x40_vel.y *= -attrs->x58;
        }
        Item_8026AE84(ip, 0x104, 0x7F, 0x40);
    }
    return false;
}

void itTaruCann_Logic5_PickedUp(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTaruCann_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDB0_itcmd_var1 = 1;
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    it_80275158(gobj, attrs->x24);
}

bool itTarucann_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.tarucann.x20 == 0) {
        ip->xDCC_flag.b3 = true;
    } else {
        ip->xDCC_flag.b3 = false;
    }
    return false;
}

void itTarucann_UnkMotion2_Phys(Item_GObj* gobj) {}

void it_3F14_Logic5_Dropped(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32 facing;
    it_802969D8(gobj);
    it_80275444(gobj);
    facing = ftLib_800865C0(ip->owner);
    ip->facing_dir = facing;
    ip->x40_vel.x = 0.5f * facing;
}

void it_3F14_Logic5_Thrown(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    lb_8000B804(jobj, ip->xC4_article_data->x10_modelDesc->x0_joint);
    it_8026B3A8(gobj);
    if (ip->xDD4_itemVar.tarucann.x20 != 0) {
        Item_80268E5C(gobj, 6, 6);
    } else {
        Item_80268E5C(gobj, 3, 6);
    }
    if (ip->xDD4_itemVar.tarucann.x20 == 0) {
        it_80274F28(ip, 1, it_80295ED4, ftCo_Barrel_Enter);
    }
}

void it_802969D8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(16);
    if (ip->xDD4_itemVar.tarucann.x20 != 0) {
        Item_80268E5C(gobj, 6, 0x15);
    } else {
        Item_80268E5C(gobj, 3, 0x15);
    }
    it_8026B3A8(gobj);
    if (ip->xDD4_itemVar.tarucann.x20 == 0) {
        it_80274F28(ip, 1, it_80295ED4, ftCo_Barrel_Enter);
    }
}

bool itTarucann_UnkMotion6_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.tarucann.x20 == 0) {
        ip->xDCC_flag.b3 = true;
    } else {
        ip->xDCC_flag.b3 = false;
    }
    return it_802961E8(gobj);
}

void itTarucann_UnkMotion6_Phys(Item_GObj* gobj)
{
    ItemAttr* attrs = GET_ITEM(gobj)->xCC_item_attr;
    PAD_STACK(12);
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    it_802962E0(gobj);
    inline_itTarucann_SetRotationZ(gobj);
}

bool itTarucann_UnkMotion6_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    itTaruCann_DatAttrs* da = ip->xC4_article_data->x4_specialAttributes;
    CollData* coll = &ip->x378_itemColl;
    f32 var_f1;
    s32 flags;
    PAD_STACK(12);
    if (it_8026DA08(gobj) != 0) {
        it_802762B0(ip);
        var_f1 = ip->x40_vel.y;
        if (var_f1 < 0.0f) {
            var_f1 = -var_f1;
        }
        if (var_f1 < attrs->x5c) {
            f32 abs_vx = ip->x40_vel.x;
            if (abs_vx < 0.0f) {
                abs_vx = -abs_vx;
            }
            ip->xDD4_itemVar.tarucann.x10 = ip->facing_dir * abs_vx;
            it_80296EA8(gobj);
        } else {
            it_802762BC(ip);
            ip->x40_vel.y *= -attrs->x58;
        }
        Item_8026AE84(ip, 0x104, 0x7F, 0x40);
    } else {
        flags = coll->env_flags;
        if ((flags & 0x3F) || (flags & 0xFC0)) {
            ip->facing_dir = -ip->facing_dir;
            ip->x40_vel.x = -(ip->x40_vel.x * da->x1C);
        }
    }
    inline_itTarucann_SetRotationZ(gobj);
    return false;
}

void it_80296E88(Item_GObj* gobj)
{
    it_80296EF0(gobj);
}

void it_80296EA8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    lb_8000B804(jobj, ip->xC4_article_data->x10_modelDesc->x0_joint);
    it_80296EF0(gobj);
}

void it_80296EF0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(4);
    ip->x40_vel.x = ip->xDD4_itemVar.tarucann.x10;
    ip->x40_vel.y = 0.0f;
    if (ip->xDD4_itemVar.tarucann.x20 != 0) {
        Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
    } else {
        Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    }
    it_8026B3A8(gobj);
    if (ip->xDD4_itemVar.tarucann.x20 == 0) {
        it_80274F28(ip, 1, it_80295ED4, ftCo_Barrel_Enter);
    }
}

bool itTarucann_UnkMotion8_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.tarucann.x20 == 0) {
        ip->xDCC_flag.b3 = true;
    } else {
        ip->xDCC_flag.b3 = false;
    }
    return it_802961E8(gobj);
}

void itTarucann_UnkMotion8_Phys(Item_GObj* gobj)
{
    PAD_STACK(8);
    // Item* ip = GET_ITEM(gobj);
    it_802962E0(gobj);
    inline_itTarucann_SetRotationZ(gobj);
}

bool itTarucann_UnkMotion8_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTaruCann_DatAttrs* da = ip->xC4_article_data->x4_specialAttributes;
    CollData* coll = &ip->x378_itemColl;
    s32 flags;
    PAD_STACK(12);
    it_8026D62C(gobj, it_802969D8);
    if (ip->ground_or_air != GA_Air) {
        if (coll->env_flags & 0x18000) {
            it_80276408(gobj, coll, &ip->xDD4_itemVar.tarucann.x14);
        } else {
            ip->xDD4_itemVar.tarucann.x14.x = 0.0f;
        }
        flags = coll->env_flags;
        if ((flags & 0x3F) || (flags & 0xFC0)) {
            ip->facing_dir = -ip->facing_dir;
            ip->xDD4_itemVar.tarucann.x10 =
                -(ip->xDD4_itemVar.tarucann.x10 * da->x1C);
            ip->x40_vel.x = ip->xDD4_itemVar.tarucann.x10 *
                            ip->xDD4_itemVar.tarucann.x14.y;
        }
    }
    inline_itTarucann_SetRotationZ(gobj);
    return false;
}

bool itTarucann_UnkMotion7_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.tarucann.x20 == 0) {
        ip->xDCC_flag.b3 = true;
    } else {
        ip->xDCC_flag.b3 = false;
    }
    return it_802961E8(gobj);
}

inline void inline_itTarucann_UnkMotion7_Phys(Item_GObj* gobj)
{
    Item* ip2 = GET_ITEM(gobj);
    ip2->x40_vel.x = ip2->xDD4_itemVar.tarucann.x10;
    ip2->x40_vel.y = 0.0f;
    if (ip2->xDD4_itemVar.tarucann.x20 != 0) {
        Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
    } else {
        Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    }
    it_8026B3A8(gobj);
    if (ip2->xDD4_itemVar.tarucann.x20 == 0) {
        it_80274F28(ip2, 1, it_80295ED4, ftCo_Barrel_Enter);
    }
}

float itTarucann_UnkMotion7_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTaruCann_DatAttrs* da = ip->xC4_article_data->x4_specialAttributes;
    f32 var_f1;
    PAD_STACK(16);
    it_802962E0(gobj);
    inline_itTarucann_SetRotationZ(gobj);
    var_f1 = ip->xDD4_itemVar.tarucann.x10;
    if (var_f1 < 0.0f) {
        var_f1 = -var_f1;
    }
    if (var_f1 > da->x8) {
        inline_itTarucann_UnkMotion7_Phys(gobj);
    }
    var_f1 = ip->xDD4_itemVar.tarucann.x10;
    if (var_f1 < 0.0f) {
        var_f1 = -var_f1;
    }
    return var_f1;
}

bool itTarucann_UnkMotion7_Coll(Item_GObj* gobj)
{
    return itTarucann_UnkMotion8_Coll(gobj);
}

void it_802975F4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 9, ITEM_ANIM_UPDATE);
    it_8026B3A8(gobj);
    it_802756D0(gobj);
    ip->xDAC_itcmd_var0 = 0;
    ip->xDD4_itemVar.tarucann.x20 = 0;
    ip->x40_vel.x = ip->x40_vel.y = ip->x40_vel.z = 0.0f;
    Item_8026AE84(ip, 0x12A, 0x7F, 0x40);
}

inline void itTarucann_UnkMotion9_Anim_inline(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.tarucann.x20 == 0) {
        ip->xDCC_flag.b3 = true;
    } else {
        ip->xDCC_flag.b3 = false;
    }
}

bool itTarucann_UnkMotion9_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    itTarucann_UnkMotion9_Anim_inline(gobj);
    switch (ip->xDAC_itcmd_var0) {
    case 1:
        efSync_Spawn(0x427, gobj, &ip->pos);
        Item_8026AE84(ip, 0xFB, 0x7F, 0x40);
        Camera_80030E44(2, &ip->pos);
        HSD_JObjSetFlagsAll(jobj, 0x10);
        it_8026B3A8(gobj);
        ip->xDD4_itemVar.tarucann.x4 = 0x28;
        ip->xDAC_itcmd_var0 = 2;
        break;
    case 2:
        ip->xDD4_itemVar.tarucann.x4 -= 1;
        if (ip->xDD4_itemVar.tarucann.x4 <= 0) {
            return true;
        }
        break;
    }
    return false;
}

void itTarucann_UnkMotion9_Phys(Item_GObj* gobj) {}

bool itTarucann_UnkMotion9_Coll(Item_GObj* gobj)
{
    return false;
}

bool it_80297790(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTaruCann_DatAttrs* da = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(16);
    HSD_JObjClearFlagsAll(gobj->hsd_obj, 0x10);
    switch (ip->msid) {
    case 3:
    case 4:
    case 5:
        it_802969D8(gobj);
        it_802762BC(ip);
        Item_8026AE84(ip, 0x129, 0x7F, 0x40);
        ip->xDD4_itemVar.tarucann.x24 = da->x2C;
        ip->x40_vel.y = da->x4C;
        ip->xDD4_itemVar.tarucann.x28 = da->x48;
        break;
    }
    return false;
}

bool itTaruCann_Logic5_DmgDealt(Item_GObj* arg0)
{
    return false;
}

bool itTaruCann_Logic5_Clanked(Item_GObj* arg0)
{
    return false;
}

bool itTaruCann_Logic5_HitShield(Item_GObj* arg0)
{
    return false;
}

bool itTaruCann_Logic5_Reflected(Item_GObj* arg0)
{
    return false;
}

void itTaruCann_Logic5_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
