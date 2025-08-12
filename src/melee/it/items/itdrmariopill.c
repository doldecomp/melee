#include "itdrmariopill.h"

#include "math_ppc.h"
#include "placeholder.h"
#include "platform.h"

#include "baselib/forward.h"

#include "baselib/gobj.h"
#include "baselib/jobj.h"
#include "baselib/mtx.h"
#include "db/db.h"
#include "dolphin/mtx.h"
#include "dolphin/types.h"

#include "ft/forward.h"

#include "ft/ft_0BF0.h"
#include "ft/ftlib.h"
#include "ftDrMario/ftDr_Init.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCharItems.h"
#include "it/item.h"

#include <math.h>

#define GET_ATTRS(ip)                                                         \
    ((itDrMarioPillAttributes*) ip->xC4_article_data->x4_specialAttributes)

/* 2C0510 */ static void it_802C0510(Item_GObj* parent_gobj, Vec3* pos,
                                     s32 arg2, ItemKind kind, f32 facing_dir);
/* 2C0850 */ Item_GObj* it_802C0850(Item_GObj* parent_gobj, Vec3* pos,
                                    s32 arg2, ItemKind kind, f32 facing_dir);
/* 2C0C0C */ static bool itDrmariopill_UnkMotion0_Anim(Item_GObj*);
/* 2C0C68 */ static void itDrmariopill_UnkMotion0_Phys(Item_GObj*);
/* 2C0CC4 */ static bool itDrmariopill_UnkMotion0_Coll(Item_GObj*);
/* 2C0E48 */ static bool itDrmariopill_UnkMotion2_Anim(Item_GObj*);
/* 2C1114 */ static void itDrmariopill_UnkMotion2_Phys(Item_GObj*);
/* 2C1148 */ static bool itDrmariopill_UnkMotion2_Coll(Item_GObj*);
/* 2C1234 */ static bool itDrmariopill_UnkMotion6_Anim(Item_GObj*);
/* 2C1340 */ static void itDrmariopill_UnkMotion6_Phys(Item_GObj*);
/* 2C1360 */ static bool itDrmariopill_UnkMotion6_Coll(Item_GObj*);

ItemStateTable it_803F75D0[] = {
    { 0, itDrmariopill_UnkMotion0_Anim, itDrmariopill_UnkMotion0_Phys,
      itDrmariopill_UnkMotion0_Coll },
    { 1, itDrmariopill_UnkMotion2_Anim, itDrmariopill_UnkMotion2_Phys,
      itDrmariopill_UnkMotion2_Coll },
    { 2, itDrmariopill_UnkMotion2_Anim, itDrmariopill_UnkMotion2_Phys,
      itDrmariopill_UnkMotion2_Coll },
    { 1, itDrmariopill_UnkMotion6_Anim, itDrmariopill_UnkMotion6_Phys,
      itDrmariopill_UnkMotion6_Coll },
    { 3, itDrmariopill_UnkMotion6_Anim, itDrmariopill_UnkMotion6_Phys,
      itDrmariopill_UnkMotion6_Coll },
    { 4, itDrmariopill_UnkMotion6_Anim, itDrmariopill_UnkMotion6_Phys,
      itDrmariopill_UnkMotion6_Coll },
    { 5, itDrmariopill_UnkMotion6_Anim, itDrmariopill_UnkMotion6_Phys,
      itDrmariopill_UnkMotion6_Coll },
};

// NOTE: 4 iterations instead of the usual 3
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
        guess = _half * guess * (_three - guess * guess * x);
        y = (float) (x * guess);
        return y;
    }
    return x;
}

static void it_802C1180(Item_GObj* gobj, enum_t msid)
{
    Item* ip;
    ip = GET_ITEM(gobj);
    it_80275158(gobj, GET_ATTRS(ip)->x8);
    Item_80268E5C(gobj, msid + 4, ITEM_ANIM_UPDATE);
    it_8026B3A8(gobj);
}

static void itDrmariopill_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip;
    ItemAttr* it_attr;

    ip = gobj->user_data;
    it_8026B3A8(gobj);
    it_attr = ip->xCC_item_attr;
    it_80272860(gobj, it_attr->x10_fall_speed, it_attr->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

static void it_802C061C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    // HSD_JObj* jobj = GET_JOBJ(gobj); // Using this messes up the stack
    HSD_JObj* jobj = gobj->hsd_obj;
    if (ip->xDD4_itemVar.drmariopill.x4) {
        Vec3 v;
        ftLib_80086644(ip->xDD4_itemVar.drmariopill.x4, &v);
        ip->pos = v;
        HSD_JObjSetTranslate(jobj, &v);
        HSD_JObjSetRotationY(jobj, (M_PI_2 * ip->xDD4_itemVar.drmariopill.x0));
        HSD_JObjSetRotationZ(jobj, 0);
    }
    it_8026B3A8(gobj);
}

static bool itDrmariopill_UnkMotion6_Coll(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    return false;
}

static void itDrmariopill_UnkMotion6_Phys(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
}

static inline void copy_jobj_scale(HSD_JObj* dst, HSD_JObj* src, Vec3* scale)
{
    scale->x = scale->y = scale->z = HSD_JObjGetScaleY(src);
    HSD_JObjSetScale(dst, scale);
}

static bool itDrmariopill_UnkMotion6_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_GObj* orig = gobj;
    it_8026B3A8(gobj);
    gobj = ip->xDD4_itemVar.drmariopill.x4;
    if ((gobj != NULL) && (ftCo_800BF228(gobj) == true)) {
        Vec3 scale;
        Fighter_GObj* fobj = ip->xDD4_itemVar.drmariopill.x4;
        copy_jobj_scale(GET_JOBJ(orig), GET_JOBJ(fobj), &scale);
    }
    return false;
}

static void it_802C1180_no_inline3(Item_GObj* gobj, enum_t msid)
{
    it_802C1180(gobj, msid);
}

static void it_802C1180_no_inline2(Item_GObj* gobj, enum_t msid)
{
    it_802C1180_no_inline3(gobj, msid);
}

static void it_802C1180_no_inline(Item_GObj* gobj, enum_t msid)
{
    it_802C1180_no_inline2(gobj, msid);
}

Item_GObj* it_802C09C4(Fighter_GObj* parent_gobj, Vec3* pos, s32 arg2,
                       ItemKind kind, s32 msid, Fighter_Part part,
                       f32 facing_dir)
{
    SpawnItem spawn;
    Item_GObj* gobj;

    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68(parent_gobj, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = parent_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;
    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        it_802C1180_no_inline(gobj, msid);
        it_80273670(gobj, 1, (f32) arg2);
        it_802756D0(gobj);
        it_8026B3A8(gobj);
        Item_80268E5C(gobj, msid + 4, ITEM_ANIM_UPDATE);
        ip->xDB8_itcmd_var3 = 0;
        ip->xDB4_itcmd_var2 = 0;
        ip->xDB0_itcmd_var1 = 0;
        ip->xDAC_itcmd_var0 = 0;
        ip->xDC8_word.flags.x19 = 0;
        ip->on_accessory = it_802C061C;
        ip->xDC8_word.flags.x13 = 1;
        ip->owner = parent_gobj;
        ip->xDD4_itemVar.drmariopill.x4 = parent_gobj;
        ip->xDD4_itemVar.drmariopill.x0 = facing_dir;
        it_80274740(gobj);
        it_802756D0(gobj);
        it_8026B3A8(gobj);
        it_802750F8(gobj);
        if (msid == 2) {
            Item_8026AB54(gobj, parent_gobj, part);
        }
        it_8026B3A8(gobj);
    }
    return gobj;
}

static bool itDrmariopill_UnkMotion2_Coll(Item_GObj* gobj)
{
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    return false;
}

static void itDrmariopill_UnkMotion2_Phys(Item_GObj* gobj)
{
    it_802756D0(gobj);
    it_8026B3A8(gobj);
}

static void it_802C0DF8(Item_GObj* gobj)
{
    it_80275158(gobj, 1200.0f);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_8026B3A8(gobj);
    it_8026B3A8(gobj);
}

static void it_802C0DBC(Item_GObj* gobj)
{
    Item* ip;

    if (gobj != 0) {
        ip = GET_ITEM(gobj);
        if (ip != NULL) {
            ip->xDD4_itemVar.drmariopill.x4 = NULL;
            Item_8026A8EC(gobj);
        }
    }
}

static bool itDrmariopill_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D9A0(gobj);
    it_8026B3A8(gobj);
    if (it_8027781C(gobj) != 0) {
        Item* ip = GET_ITEM(gobj);
        itDrMarioPillAttributes* attrs = GET_ATTRS(ip);
        if (my_sqrtf(VEC2_SQ_LEN(ip->x40_vel)) < attrs->x10) {
            return true;
        }
        Item_8026AE84(ip, 0x15FAE, 0x7F, 0x40);
    }
    return false;
}

static bool itDrmariopill_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip;
    PAD_STACK(8);

    ip = gobj->user_data;
    it_8026B3A8(gobj);
    ip->xD44_lifeTimer -= 1.0f;
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

static void it_802C0B5C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itDrMarioPillAttributes* attrs = GET_ATTRS(ip);
    f32 temp_f31 = attrs->x0;
    f32 temp_f30 = attrs->x4;
    ip->x40_vel.x = ip->facing_dir * (temp_f31 * cosf(temp_f30));
    ip->x40_vel.y = temp_f31 * sinf(temp_f30);
    ip->x40_vel.z = 0.0f;
    it_80275158(gobj, attrs->x8);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_8026B3A8(gobj);
}

static inline bool itDrmariopill_UnkMotion2_Anim_sub(Item_GObj* arg_gobj)
{
    Item* ip;
    HSD_GObj* gobj;
    bool ret;
    if (arg_gobj) {
        ip = arg_gobj->user_data;
        if (arg_gobj && ip) {
            gobj = ip->xDD4_itemVar.drmariopill.x4;
            if (gobj && (ip->owner == gobj)) {
                ftDr_Init_801498A0(gobj);
            }
            ip->xDD4_itemVar.drmariopill.x4 = 0;
            ip->on_accessory = NULL;
        }
    }
    if (arg_gobj && (ip = arg_gobj->user_data)) {
        ip->xDD4_itemVar.drmariopill.x4 = 0;
        ret = true;
        ip->on_accessory = NULL;
    } else {
        ret = false;
    }
    return ret;
}

static inline void itDrmariopill_UnkMotion2_Anim_flags(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    jobj = HSD_JObjGetChild(jobj);
    it_8026B3A8(gobj);
    if (ip->xDAC_itcmd_var0 == 1) {
        HSD_JObjClearFlags(jobj, 0x10U);
    } else {
        HSD_JObjSetFlags(jobj, 0x10U);
    }
}

static bool itDrmariopill_UnkMotion2_Anim(Item_GObj* gobj)
{
    Vec scale;
    Item* ip;
    HSD_JObj* child;
    Item* ixp;
    Item* ixp2;
    HSD_JObj* hobj;
    f32 mag;
    PAD_STACK(4);

    hobj = GET_JOBJ(gobj);
    ip = GET_ITEM(gobj);
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    itDrmariopill_UnkMotion2_Anim_flags(gobj);
    if (ip->xDD4_itemVar.drmariopill.x4) {
        if (ftDr_Init_80149844(ip->xDD4_itemVar.drmariopill.x4) == true) {
            if (itDrmariopill_UnkMotion2_Anim_sub(gobj)) {
                return true;
            }
        } else {
            ip->xDAC_itcmd_var0 =
                ftDr_Init_801498EC(ip->xDD4_itemVar.drmariopill.x4);
            if (ip->owner == ip->xDD4_itemVar.drmariopill.x4) {
                mag = ftLib_800869D4(ip->xDD4_itemVar.drmariopill.x4);
                scale.x = scale.y = scale.z = mag;
                HSD_JObjSetScale(hobj, &scale);
            } else if (itDrmariopill_UnkMotion2_Anim_sub(gobj)) {
                return true;
            }
        }
    } else if (itDrmariopill_UnkMotion2_Anim_sub(gobj)) {
        return true;
    }
    return false;
}

static void it_802C0B5C_no_inline(Item_GObj* gobj)
{
    it_802C0B5C(gobj);
}

void it_802C0510(Item_GObj* parent_gobj, Vec3* pos, s32 arg2, ItemKind kind,
                 f32 facing_dir)
{
    SpawnItem spawn;
    Item_GObj* gobj;

    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68(parent_gobj, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = parent_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;
    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        it_802C0B5C_no_inline(gobj);
        it_80273670(gobj, 0, (f32) arg2);
        db_80225DD8(gobj, parent_gobj);
        it_802750F8(gobj);
        it_8026B3A8(gobj);
    }
}

static void it_802C0DF8_no_inline(Item_GObj* gobj)
{
    it_802C0DF8(gobj);
}

static void it_802C0DF8_no_inline2(Item_GObj* gobj)
{
    it_802C0DF8_no_inline(gobj);
}

static void it_802C0DF8_no_inline3(Item_GObj* gobj)
{
    it_802C0DF8_no_inline2(gobj);
}

Item_GObj* it_802C0850(Item_GObj* parent_gobj, Vec3* pos, s32 arg2,
                       ItemKind kind, f32 facing_dir)
{
    SpawnItem spawn;
    Item_GObj* gobj;

    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68(parent_gobj, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = parent_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;
    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        it_802C0DF8_no_inline3(gobj);
        it_80273670(gobj, 1, (f32) arg2);
        it_8026B3A8(gobj);
        Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
        ip->xDB8_itcmd_var3 = 0;
        ip->xDB4_itcmd_var2 = 0;
        ip->xDB0_itcmd_var1 = 0;
        ip->xDAC_itcmd_var0 = 0;
        ip->xDC8_word.flags.x19 = 0;
        ip->on_accessory = it_802C061C;
        ip->xDC8_word.flags.x13 = 1;
        ip->owner = parent_gobj;
        ip->xDD4_itemVar.drmariopill.x4 = parent_gobj;
        ip->xDD4_itemVar.drmariopill.x0 = facing_dir;
        it_80274740(gobj);
        it_802756D0(gobj);
        it_8026B3A8(gobj);
        db_80225DD8(gobj, parent_gobj);
        it_802750F8(gobj);
        it_8026B3A8(gobj);
    }
    return gobj;
}

void it_2725_Logic6_PickedUp(Item_GObj* gobj)
{
    itDrMarioPillAttributes* attrs;
    PAD_STACK(8);
    attrs = GET_ATTRS(GET_ITEM(gobj));
    it_80275158(gobj, attrs->x8);
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
    it_8026B3A8(gobj);
}

bool it_2725_Logic88_DmgDealt(Item_GObj* gobj)
{
    Item* ip;
    ip = gobj->user_data;
    it_8026B3A8(gobj);
    Item_8026AE84(ip, 0x15FAE, 0x7F, 0x40);
    return true;
}

bool it_2725_Logic88_Reflected(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    return it_80273030(gobj);
}

// NOTE: identical to it_2725_Logic88_DmgDealt
bool it_2725_Logic88_Clanked(Item_GObj* gobj)
{
    Item* ip;
    it_8026B3A8(gobj);
    ip = gobj->user_data;
    it_8026B3A8(gobj);
    Item_8026AE84(ip, 0x15FAE, 0x7F, 0x40);
    return true;
}

// NOTE: identical to it_2725_Logic88_DmgDealt
bool it_2725_Logic88_HitShield(Item_GObj* gobj)
{
    Item* ip;
    it_8026B3A8(gobj);
    ip = gobj->user_data;
    it_8026B3A8(gobj);
    Item_8026AE84(ip, 0x15FAE, 0x7F, 0x40);
    return true;
}

// NOTE: identical to it_2725_Logic88_DmgDealt
bool it_2725_Logic88_Absorbed(Item_GObj* gobj)
{
    Item* ip;
    it_8026B3A8(gobj);
    ip = gobj->user_data;
    it_8026B3A8(gobj);
    Item_8026AE84(ip, 0x15FAE, 0x7F, 0x40);
    return true;
}

// NOTE: identical to it_2725_Logic88_DmgDealt
bool it_2725_Logic88_ShieldBounced(Item_GObj* gobj)
{
    Item* ip;
    it_8026B3A8(gobj);
    ip = gobj->user_data;
    it_8026B3A8(gobj);
    Item_8026AE84(ip, 0x15FAE, 0x7F, 0x40);
    return true;
}

void it_2725_Logic88_EvtUnk(Item_GObj* gobj, HSD_GObj* hobj)
{
    it_8026B894(gobj, hobj);
}
