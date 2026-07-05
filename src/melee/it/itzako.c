#include "itzako.h"

#include "it_266F.h"
#include "it_2725.h"
#include "it_3F14.h"
#include "ithitbox.h"
#include "itmaplib.h"
#include "itmaterial.h"

#include "baselib/jobj.h"
#include "cm/camera.h"
#include "ft/fighter.h"
#include "ft/ftlib.h"
#include "gm/gm_unsplit.h"
#include "gr/grlib.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "it/inlines.h"
#include "it/items/itheiho.h"
#include "items/itcoin.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"
#include "pl/plbonuslib.h"
#include "ty/tydisplay.h"

static void sdata2_order(void)
{
    (void) 0.0f;
    (void) 1.0f;
    (void) 0.0174532924f;
    (void) 4503601774854144.0;
    (void) 1.57079637f;
    (void) 0.100000001f;
    (void) 10.0;
    (void) 0.5;
    (void) 30.0f;
    (void) 10.0f;
    (void) 1.5707963267948966;
    (void) 0.000174532921f;
    (void) 3.0;
    (void) -1.0f;
    (void) 6.80741774e-09f;
    (void) 2.0f;
    (void) 0.5f;
}

const Vec3 it_803B85A8[6] = {
    { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
};

Item_GObj* it_8027B5B0(ItemKind kind, Vec3* pos, HSD_JObj* jobj, Vec3* vel,
                       bool use_init)
{
    SpawnItem spawn;
    Vec3 sp20;
    Item_GObj* gobj;
    Item* ip;

    spawn.kind = kind;
    if (pos != NULL) {
        spawn.prev_pos = *pos;
    } else if (jobj != NULL) {
        lb_8000B1CC(jobj, NULL, &sp20);
        spawn.prev_pos = sp20;
    } else {
        OSReport("can t init zako pos\n");
        for (;;) {
        }
    }
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = it_8026B684(&spawn.prev_pos);
    spawn.x3C_damage = 0;
    spawn.x44_flag.b0 = true;
    if (vel != NULL) {
        spawn.vel = *vel;
    } else {
        spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    }
    spawn.x0_parent_gobj = NULL;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x40 = 0;
    if (use_init == 1) {
        gobj = Item_80268B18(&spawn);
    } else {
        gobj = Item_80268B5C(&spawn);
    }
    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        ip->xDD4_itemVar.zako.jobj = jobj;
        ip->xDD4_itemVar.zako.idx = -1;
        ip->xDD4_itemVar.zako.x14.z = 0;
        ip->x378_itemColl.x34_flags.b1234 = 3;
    }
    return gobj;
}

#pragma push
#pragma dont_inline on

void it_8027B730(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDD4_itemVar.zako.jobj = 0;
    item->xDD4_itemVar.zako.idx = -1;
    item->xDD4_itemVar.zako.x8.z = 0.0f;
    item->xDD4_itemVar.zako.x8.x = 0.0f;
    item->xDD4_itemVar.zako.x8.y = 1.0f;
    item->xDD4_itemVar.zako.x14.x = 0;
    item->xDD4_itemVar.zako.x14.y = 0;
    item->xDD4_itemVar.zako.x14.z = 0;
    it_80275228(item_gobj);
    it_80275240(item_gobj);
}

#pragma pop

static inline f32 it_8027B798_CalcAngle(GroundOrAir ground_or_air, s32 angle,
                                        ftCommonData* common_data,
                                        f32 knockback)
{
    if (angle != 0x169) {
        return 0.017453292f * angle;
    } else if (ground_or_air == GA_Air) {
        return common_data->x144_radians;
    } else if (knockback < common_data->x14C) {
        return 0.0f;
    } else {
        f32 temp_angle =
            0.017453292f *
            ((common_data->x148 * ((knockback - common_data->x14C) /
                                   (common_data->x150 - common_data->x14C))) +
             1.0f);
        if (temp_angle > 0.017453292f * common_data->x148) {
            temp_angle = 0.017453292f * common_data->x148;
        }
        return temp_angle;
    }
}

bool it_8027B798(Item_GObj* gobj, Vec3* out_vel)
{
    u8 _pad[4];
    Item* ip = gobj->user_data;
    f32 knockback;
    f32 mag;
    f32 dx;
    f32 dy;
    f32 angle_rad;
    bool result = false;
    Vec3* normal;
    f32 x;
    Vec3 v;

    knockback = ip->xCC8_knockback;
    mag = knockback * p_ftCommonData->x100;
    angle_rad = it_8027B798_CalcAngle(ip->ground_or_air, ip->xCAC_angle,
                                      p_ftCommonData, knockback);
    dx = mag * cosf(angle_rad);
    dy = mag * sinf(angle_rad);
    ip->facing_dir = ip->xCCC_incDamageDirection;
    if (ip->ground_or_air == GA_Air) {
        out_vel->x = -dx * ip->facing_dir;
        out_vel->y = dy;
        out_vel->z = 0.0f;
    } else {
        normal = &ip->x378_itemColl.floor.normal;
        v.x = -dx * ip->facing_dir;
        v.y = dy;
        v.z = 0.0f;
        if (lbVector_Angle(normal, &v) < 1.5707964f) {
            result = true;
            out_vel->x = v.x;
            out_vel->y = v.y;
            out_vel->z = 0.0f;
        } else {
            x = v.x;
            out_vel->x = normal->y * x;
            out_vel->y = -normal->x * x;
            out_vel->z = 0.0f;
        }
    }
    return result;
}

void it_8027B964(Item_GObj* item_gobj, bool chk)
{
    Vec3 sp14;
    Item* item;
    f32 scale;

    item = GET_ITEM(item_gobj);
    if (chk != 0) {
        it_8027781C(item_gobj);
    } else {
        it_8027B798(item_gobj, &item->x40_vel);
        if (!item->x40_vel.x && !item->x40_vel.y) {
            item->x40_vel.x = 0.1f * -item->xCCC_incDamageDirection;
            item->x40_vel.y = 0.1f;
        }
        if (!item->x40_vel.y) {
            item->x40_vel.y = 0.1f;
        }
    }
    sp14 = item->x40_vel;
    lbVector_Normalize(&sp14);
    scale = it_804D6D40->x4;
    sp14.x *= scale;
    sp14.y *= scale;
    sp14.z *= scale;
    item->x40_vel = sp14;
}

int it_8027BA54(HSD_GObj* item_gobj, Vec3* arg1)
{
    Vec3 sp20;
    Vec3 sp14;
    Item* item;

    item = GET_ITEM(item_gobj);
    Camera_GetTransformPosition(&sp20);
    sp20.x = ((10.0f * (HSD_Randf() - 0.5)) + sp20.x);
    sp20.y += 30.0f * HSD_Randf();
    lbVector_Diff(&sp20, &item->pos, &sp14);
    lbVector_Normalize(&sp14);
    sp14.x *= 10.0f;
    sp14.y *= 10.0f;
    sp14.z *= 10.0f;
    *arg1 = sp14;
}

void it_8027BB1C(Vec3* arg0, Vec3* arg1)
{
    f32 cos;
    f32 sin;
    f32 t1;
    f32 t2;

    {
        cos = cosf(arg1->x);
        sin = sinf(arg1->x);
        t1 = arg0->y;
        t2 = arg0->z;
        arg0->y = (t1 * cos) - (t2 * sin);
        arg0->z = (t1 * sin) + (t2 * cos);
    }

    {
        cos = cosf(arg1->y);
        sin = sinf(arg1->y);
        t1 = arg0->x;
        t2 = arg0->z;
        arg0->x = (t1 * cos) + (t2 * sin);
        arg0->z = (t2 * cos) - (t1 * sin);
    }

    {
        cos = cosf(arg1->z);
        sin = sinf(arg1->z);
        t1 = (arg0->x * cos) - (arg0->y * sin);
        t2 = (arg0->x * sin) + (arg0->y * cos);
        arg0->x = t1;
        arg0->y = t2;
    }
}

void it_8027BBF4(Item_GObj* item_gobj, bool arg_chk, f64 arg8, f32 arg9)
{
    f32 temp_f1;
    f32 temp_f30;
    f32 var_f29;
    f32 var_f28;
    const Vec3* vecs = it_803B85A8;
    Vec3 sp74;
    Vec3 sp68;
    Vec3 sp5C;
    Vec3 sp50;
    Vec3 sp44;
    Vec3 sp38;
    HSD_JObj* item_jobj;
    Item* item;
    CollData* coll;

    item = GET_ITEM(item_gobj);
    item_jobj = item_gobj->hsd_obj;

    coll = &item->x378_itemColl;
    sp68 = it_803B85A8[2];
    sp5C = it_803B85A8[3];

    if (!arg_chk) {
        if (coll->env_flags & Collide_FloorMask) {
            sp68 = coll->floor.normal;
            goto block_7;
        }
        return;
    } else if (coll->env_flags & Collide_CeilingMask) {
        sp68 = coll->ceiling.normal;
        goto block_7;
    }
    return;

block_7:

    sp74.x = HSD_JObjGetRotationX(item_jobj);
    sp74.y = HSD_JObjGetRotationY(item_jobj);
    sp74.z = HSD_JObjGetRotationZ(item_jobj);

    it_8027BB1C(&sp5C, &sp74);
    if (lbVector_AngleXY(&item->xDD4_itemVar.zako.x8, &sp68) > 0.00017453292f)
    {
        item->xDD4_itemVar.zako.x8 = sp68;
        item->xDD4_itemVar.zako.x14.x = (s32) arg9;
    }
    temp_f1 = lbVector_AngleXY(&sp5C, &item->xDD4_itemVar.zako.x8);
    if ((temp_f1 < 0.00017453292f) || item->xDD4_itemVar.zako.x14.x < 2) {
        var_f29 = sp68.x;
        var_f28 = sp68.y;
    } else {
        var_f29 = temp_f1 / (f32) item->xDD4_itemVar.zako.x14.x;
        item->xDD4_itemVar.zako.x14.x--;
        if (((sp5C.x * sp68.y) - (sp5C.y * sp68.x)) < 0) {
            var_f29 = -var_f29;
        }
        temp_f30 = cosf(var_f29);
        temp_f1 = sinf(var_f29);
        var_f29 = (sp5C.x * temp_f30) - (sp5C.y * temp_f1);
        var_f28 = (sp5C.x * temp_f1) + (sp5C.y * temp_f30);
    }

    sp44 = vecs[0];
    sp50 = vecs[1];
    lbVector_Rotate(&sp50, 2, M_PI_2 * arg8);
    lbVector_Rotate(&sp44, 2, M_PI_2 * arg8);

    sp38.x = var_f29;
    sp38.y = var_f28;
    sp38.z = 0.0f;
    lbVector_CrossprodNormalized(&sp38, &sp50, &sp44);
    lbVector_CrossprodNormalized(&sp44, &sp38, &sp50);
    lbVector_EulerAnglesFromONB(&sp74, &sp50, &sp44, &sp38);

    HSD_JObjSetRotationX(item_jobj, sp74.x);
    HSD_JObjSetRotationY(item_jobj, sp74.y);
    HSD_JObjSetRotationZ(item_jobj, sp74.z);
}

/// Might take in and pass more vars
void it_8027C0A8(Item_GObj* item_gobj, f32 arg4, f32 arg5)
{
    it_8027BBF4(item_gobj, false, arg4, arg5);
}

/// Might take in and pass more vars
void it_8027C0CC(Item_GObj* item_gobj, f32 arg4, f32 arg5)
{
    it_8027BBF4(item_gobj, true, arg4, arg5);
}

void it_8027C0F0(Item_GObj* item_gobj, Vec3* arg1, f64 arg8, f32 arg9)
{
    u8 _padA[8];
    const Vec3* vecs = it_803B85A8;
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* item_jobj = item_gobj->hsd_obj;
    f32 temp_f1;
    f32 temp_f30;
    f32 var_f29;
    f32 var_f28;
    Vec3 sp74;
    Vec3 sp68;
    Vec3 sp5C;
    Vec3 sp50;
    Vec3 sp44;
    Vec3 sp3C;

    sp68 = vecs[4];
    sp5C = vecs[5];

    if (item->x378_itemColl.env_flags & Collide_FloorMask) {
        if (arg1 != NULL) {
            sp68 = *arg1;
        }
        sp74.x = HSD_JObjGetRotationX(item_jobj);
        sp74.y = HSD_JObjGetRotationY(item_jobj);
        sp74.z = HSD_JObjGetRotationZ(item_jobj);
        it_8027BB1C(&sp5C, &sp74);

        if (lbVector_AngleXY(&item->xDD4_itemVar.zako.x8, &sp68) >
            0.00017453292f)
        {
            item->xDD4_itemVar.zako.x8 = sp68;
            item->xDD4_itemVar.zako.x14.x = (s32) arg9;
        }
        temp_f1 = lbVector_AngleXY(&sp5C, &item->xDD4_itemVar.zako.x8);
        if ((temp_f1 < 0.00017453292f) || item->xDD4_itemVar.zako.x14.x < 2) {
            var_f29 = sp68.x;
            var_f28 = sp68.y;
        } else {
            var_f29 = temp_f1 / (f32) item->xDD4_itemVar.zako.x14.x;
            item->xDD4_itemVar.zako.x14.x--;
            if (((sp5C.x * sp68.y) - (sp5C.y * sp68.x)) < 0) {
                var_f29 = -var_f29;
            }
            temp_f30 = cosf(var_f29);
            temp_f1 = sinf(var_f29);
            var_f29 = (sp5C.x * temp_f30) - (sp5C.y * temp_f1);
            var_f28 = (sp5C.x * temp_f1) + (sp5C.y * temp_f30);
        }

        sp44 = vecs[0];
        sp50 = vecs[1];
        lbVector_Rotate(&sp50, 2, M_PI_2 * arg8);
        lbVector_Rotate(&sp44, 2, M_PI_2 * arg8);
        sp3C.x = var_f29;
        sp3C.y = var_f28;
        sp3C.z = 0.0f;
        lbVector_CrossprodNormalized(&sp3C, &sp50, &sp44);
        lbVector_CrossprodNormalized(&sp44, &sp3C, &sp50);
        lbVector_EulerAnglesFromONB(&sp74, &sp50, &sp44, &sp3C);

        HSD_JObjSetRotationX(item_jobj, sp74.x);
        HSD_JObjSetRotationY(item_jobj, sp74.y);
        HSD_JObjSetRotationZ(item_jobj, sp74.z);
    }
}

void it_8027C56C(Item_GObj* item_gobj, f32 y_rot)
{
    Item* item;
    HSD_JObj* item_jobj;

    item_jobj = GET_JOBJ(item_gobj);
    item = GET_ITEM(item_gobj);
    HSD_JObjSetRotationX(item_jobj, 0.0f);
    HSD_JObjSetRotationY(item_jobj, M_PI_2 * y_rot);
    HSD_JObjSetRotationZ(item_jobj, 0.0f);

    item->xDD4_itemVar.zako.x8.z = 0.0f;
    item->xDD4_itemVar.zako.x8.x = 0.0f;
    item->xDD4_itemVar.zako.x8.y = 1.0f;
    item->xDD4_itemVar.zako.x14.x = 0U;
}

bool it_8027C794(Item_GObj* gobj)
{
    return false;
}

bool it_8027C79C(Item_GObj* item_gobj)
{
    Item* item;
    PAD_STACK(4);

    if (it_8026DAA8(item_gobj) & 0xF) {
        item = GET_ITEM(item_gobj);
        it_8027C9D8(item);
        it_8027B964(item_gobj, 1);
        item->xDD4_itemVar.zako.x14.y++;
        if (item->xDD4_itemVar.zako.x14.y > it_804D6D40->x0) {
            it_8027CC88(item_gobj);
            return true;
        }
    }
    return false;
}

bool it_8027C824(Item_GObj* item_gobj, s32 (*arg_func)(Item_GObj*))
{
    s32 arg_func_ret_val;

    if (it_8026DAA8(item_gobj) & 0xF) {
        it_8027CC88(item_gobj);
        if (arg_func != NULL) {
            arg_func_ret_val = arg_func(item_gobj);
            if (arg_func_ret_val != 0) {
                it_8027CE44(item_gobj);
            }
            return arg_func_ret_val;
        }
        it_8027CE44(item_gobj);
        return true;
    }
    return false;
}

void it_2725_Logic9_Destroyed(Item_GObj* item_gobj)
{
    grZakoGenerator_801CAC14(item_gobj);
}

static inline float product_xyz(Vec3* a, Vec3* b)
{
    return (a->x * b->x + a->y * b->y + a->z * b->z);
}

static inline float itzako_sqrtf(float x)
{
    volatile float y;

    if (x > 0.0f) {
        double guess = __frsqrte((double) x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        y = (float) (x * guess);
        return y;
    }
    return x;
}

static inline float return_sqrt_value3(Vec3* v)
{
    return itzako_sqrtf(product_xyz(v, v));
}

void it_8027C8D0(Vec3* arg0, Vec3* arg1, f32 arg8)
{
    f32 dir;
    f32 vec_mag;
    f32 var_f6;
    Vec3 sp1C;

    vec_mag = return_sqrt_value3(arg0);
    sp1C = *arg1;
    if (arg8 > 0.0f) {
        dir = -1.0f;
        var_f6 = 6.8074177e-9f;
    } else if (arg8 < 0.0f) {
        dir = 1.0f;
        var_f6 = 6.8074177e-9f;
    } else {
        arg0->z = 0.0f;
        arg0->y = 0.0f;
        arg0->x = 0.0f;
        return;
    }

    arg0->x = vec_mag * ((sp1C.x * var_f6) - (sp1C.y * dir));
    arg0->y = vec_mag * ((sp1C.x * dir) + (sp1C.y * var_f6));
    arg0->z = 0.0f;
}

void it_8027C9D8(Item* item)
{
    s32 spC[4] = {
        0x131,
        0x132,
        0x133,
        0x134,
    };
    s32 var_r3;

    var_r3 = spC[HSD_Randi(4)];
    while (var_r3 == item->xDD4_itemVar.zako.x14.z) {
        var_r3 = spC[HSD_Randi(4)];
    }
    item->xDD4_itemVar.zako.x14.z = var_r3;
    Item_8026AE84(item, item->xDD4_itemVar.zako.x14.z, 127, 64);
}

bool it_8027CA7C(HSD_GObj* gobj)
{
    bool chk;

    chk = false;
    if (ftLib_80086C0C(gobj) == 0x14E) {
        chk = true;
    }
    if (ftLib_80086C0C(gobj) == 0x14D) {
        chk = true;
    }
    return chk;
}

#pragma push
#pragma dont_inline on

void it_8027CAD8(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->x40_vel.y = 0.0f;
    item->x40_vel.x = 0.0f;
    it_8027542C(item_gobj);
    it_80275444(item_gobj);
    it_80274740(item_gobj);
    item->owner = NULL;
    it_80275270(item_gobj);
}

void it_8027CB3C(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    it_8026C220(item_gobj, item->owner);
    item->facing_dir = ftLib_800865C0(item->owner);
    it_80275414(item_gobj);
    it_80275474(item_gobj);
    it_802762BC(item);
    it_8026B3A8(item_gobj);
}

void it_8027CBA4(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->facing_dir = ftLib_800865C0(item->owner);
    it_802762BC(item);
    it_802754D4(item_gobj);
    it_8026B3A8(item_gobj);
}

#pragma pop

f32 it_8027CBFC(Item_GObj* item_gobj)
{
    s32 ret_val;
    PAD_STACK(4);

    ret_val = 0U;
    switch (GET_ITEM(item_gobj)->xCC4) {
    case 6:
    case 7:
        ret_val = it_804D6D40->xC;
        break;
    case 9:
        ret_val = it_804D6D40->x10;
        break;
    case 4:
    case 5:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
        break;
    }
    return (f32) ret_val;
}

Item_GObj* it_8027CC88(Item_GObj* item_gobj_arg)
{
    s32 temp_r3;
    s32 temp_r3_2;
    s32 var_r30;
    Item_GObj* item_gobj_var;
    Item* var_item;
    u32 pad[20];
    Vec3 sp44;
    s32 sp1C[10];
    u32 pad2[4];

    item_gobj_var = NULL;
    if ((gm_8016B498() != 0) && (HSD_Randi(it_804D6D40->x14) == 0)) {
        if (grLib_801C9E40() == 0) {
            var_r30 = Ground_801C5840();
            if (var_r30 != -1) {
                temp_r3 = tyDisplay_8031C354(var_r30, sp1C, 0xA, 0x63);
                temp_r3_2 = temp_r3 + tyDisplay_8031C354(
                                          var_r30, &sp1C[temp_r3], 0xA, 2);
                if (temp_r3_2 != 0) {
                    var_r30 = (&sp1C[0])[HSD_Randi(temp_r3_2)];
                }
                it_8026BB88(item_gobj_arg, &sp44);
                item_gobj_var = it_802F2094(NULL, &sp44, var_r30, 0);
                if (item_gobj_var != 0) {
                    var_item = item_gobj_var->user_data;
                    var_item->x40_vel.x = ((2.0f * (HSD_Randf() - 0.5f)) *
                                           (it_804D6D28->x54_float));
                    var_item->x40_vel.y = var_item->xCC_item_attr->x18;
                    var_item->x40_vel.z = 0.0f;
                    grLib_801C9E50(1);
                }
            }
        } else if (grLib_801C9E40() >= it_804D6D40->x18) {
            grLib_801C9E50(0);
        } else {
            grLib_801C9E50(grLib_801C9E40() + 1);
        }
    }
    return item_gobj_var;
}

void it_8027CE18(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    pl_8004049C(item->xCB0_source_ply, item->kind);
}

void it_8027CE44(Item_GObj* item_gobj)
{
    grZakoGenerator_801CACB8(item_gobj);
}

#pragma push
#pragma dont_inline on

/// Appears to be a function for Game&Watch items
void it_8027CE64(Item_GObj* item_gobj, HSD_GObj* fighter_gobj,
                 void* arg_attr_address)
{
    Item* item;
    GXColor sp18;
    u32 pad[1];

    item = item_gobj->user_data;
    item->xDCF_flag.b3 = true;
    ftLib_8008770C(fighter_gobj, (void*) &sp18);
    it_80278574(item_gobj, &sp18);
    ftLib_80087744(fighter_gobj, &item->xBC8);
    item->x5C8 = ftLib_800870BC(item->owner, (int*) &item->xBC4);
    it_80274594(item_gobj);
    item->xDD4_itemVar.gamewatch.attr = arg_attr_address;
}

#pragma pop
