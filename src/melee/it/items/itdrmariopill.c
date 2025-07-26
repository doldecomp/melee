#include "baselib/forward.h"
#include "ft/forward.h"
#include "it/forward.h"

#include "itdrmariopill.h"

#include "math_ppc.h"
#include "placeholder.h"
#include "platform.h"

#include "baselib/jobj.h"
#include "dolphin/mtx.h"
#include "ft/ft_0BF0.h"
#include "ft/ftlib.h"
#include "ftDrMario/ftDr_Init.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCharItems.h"
#include "it/item.h"

#include <math.h>

#define GET_ATTRS(ip)                                                         \
    ((itDrMarioPillAttributes*) ip->xC4_article_data->x4_specialAttributes)

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

static void it_802C0C68(Item_GObj* gobj)
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
    Vec3 sp10;
    Fighter_GObj* fobj;
    HSD_JObj* hobj;
    Item* ip;
    f32 rot_y;
    PAD_STACK(8);

    ip = gobj->user_data;
    hobj = gobj->hsd_obj;
    fobj = ip->xDD4_itemVar.drmariopill.x4;
    if (fobj) {
        ftLib_80086644(fobj, &sp10);
        ip->pos = sp10;
        HSD_JObjSetTranslate(hobj, &sp10);
        rot_y =
            (f32) (1.5707963267948966 * (f64) ip->xDD4_itemVar.drmariopill.x0);
        HSD_JObjSetRotationY(hobj, rot_y);
        HSD_JObjSetRotationY(hobj, 0);
    }
    it_8026B3A8(gobj);
}

static bool it_802C1360(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    return false;
}

static void it_802C1340(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
}

static bool it_802C1234(Item_GObj* gobj)
{
    Vec3 scale;
    f32 scale_y;
    Fighter_GObj* fobj;
    HSD_JObj* jobj;
    Item* ip;
    PAD_STACK(8);

    ip = gobj->user_data;
    it_8026B3A8(gobj);
    fobj = ip->xDD4_itemVar.drmariopill.x4;
    if (fobj && (ftCo_800BF228(fobj) == 1)) {
        scale_y = HSD_JObjGetScaleY(fobj->hsd_obj);
        scale.x = scale_y;
        scale.y = scale_y;
        scale.z = scale_y;
        HSD_JObjSetScale(gobj->hsd_obj, &scale);
    }
    return false;
}

static bool it_802C1148(Item_GObj* gobj)
{
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    return false;
}

static void it_802C1114(Item_GObj* gobj)
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
        ip = gobj->user_data;
        if (ip != NULL) {
            ip->xDD4_itemVar.drmariopill.x4 = NULL;
            Item_8026A8EC(gobj);
        }
    }
}

static bool it_802C0CC4(Item_GObj* gobj)
{
    Item* ip;
    f32 var_f4;

    it_8026D9A0(gobj);
    it_8026B3A8(gobj);
    if (it_8027781C(gobj) != 0) {
        ip = gobj->user_data;
        var_f4 = my_sqrtf((ip->x40_vel.x * ip->x40_vel.x) +
                          (ip->x40_vel.y * ip->x40_vel.y));
        if (var_f4 < GET_ATTRS(ip)->x10) {
            return true;
        }
        Item_8026AE84(ip, 0x15FAE, 0x7F, 0x40);
    }
    return false;
}

static bool it_802C0C0C(Item_GObj* gobj)
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
    Item* ip;
    f32 temp_f30;
    f32 temp_f31;
    itDrMarioPillAttributes* attrs;

    ip = gobj->user_data;
    attrs = ip->xC4_article_data->x4_specialAttributes;
    temp_f31 = attrs->x0;
    temp_f30 = attrs->x4;
    ip->x40_vel.x = ip->facing_dir * (temp_f31 * cosf(temp_f30));
    ip->x40_vel.y = temp_f31 * sinf(temp_f30);
    ip->x40_vel.z = 0.0f;
    it_80275158(gobj, attrs->x8);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_8026B3A8(gobj);
}

static inline bool it_802C0E48_sub(Item_GObj* gobj)
{
    Item* ip;
    HSD_GObj* hobj;
    bool ret;
    if (gobj) {
        ip = gobj->user_data;
        if (gobj && ip) {
            hobj = ip->xDD4_itemVar.drmariopill.x4;
            if (hobj && (ip->owner == hobj)) {
                ftDr_Init_801498A0(hobj);
            }
            ip->xDD4_itemVar.drmariopill.x4 = 0;
            ip->on_accessory = NULL;
        }
    }
    if (gobj && ip) {
        ip->xDD4_itemVar.drmariopill.x4 = 0;
        ret = true;
        ip->on_accessory = NULL;
    } else {
        ret = false;
    }
    return ret;
}

static s32 it_802C0E48(Item_GObj* gobj)
{
    Vec scale;
    HSD_JObj* hobj;
    HSD_JObj* child;
    Item* ip;
    f32 mag;
    Fighter_GObj* fobj;
    PAD_STACK(40);

    hobj = gobj->hsd_obj;
    ip = gobj->user_data;
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    child = HSD_JObjGetChild(gobj->hsd_obj);
    it_8026B3A8(gobj);
    if (ip->xDAC_itcmd_var0 == 1) {
        HSD_JObjClearFlags(child, 0x10U);
    } else {
        HSD_JObjSetFlags(child, 0x10U);
    }
    fobj = ip->xDD4_itemVar.drmariopill.x4;
    if (fobj) {
        if (ftDr_Init_80149844(fobj) == 1) {
            if (it_802C0E48_sub(gobj)) {
                return true;
            }
            goto exit;
        }
        ip->xDAC_itcmd_var0 =
            ftDr_Init_801498EC(ip->xDD4_itemVar.drmariopill.x4);
        fobj = ip->xDD4_itemVar.drmariopill.x4;
        if (ip->owner == fobj) {
            mag = ftLib_800869D4(fobj);
            scale.x = mag;
            scale.y = mag;
            scale.z = mag;
            HSD_JObjSetScale(hobj, &scale);
            return false;
        }
        if (it_802C0E48_sub(gobj)) {
            return true;
        }
        goto exit;
    }
    if (it_802C0E48_sub(gobj)) {
        return true;
    }
exit:
    return false;
}

void it_802C11E0(Item_GObj* gobj)
{
    itDrMarioPillAttributes* attrs;
    PAD_STACK(8);
    attrs = GET_ATTRS(GET_ITEM(gobj));
    it_80275158(gobj, attrs->x8);
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
    it_8026B3A8(gobj);
}

bool it_802C1384(Item_GObj* gobj)
{
    Item* ip;
    ip = gobj->user_data;
    it_8026B3A8(gobj);
    Item_8026AE84(ip, 0x15FAE, 0x7F, 0x40);
    return true;
}

bool it_802C13CC(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    return it_80273030(gobj);
}

// NOTE: identical to it_802C1384
bool it_802C1400(Item_GObj* gobj)
{
    Item* ip;
    it_8026B3A8(gobj);
    ip = gobj->user_data;
    it_8026B3A8(gobj);
    Item_8026AE84(ip, 0x15FAE, 0x7F, 0x40);
    return true;
}

// NOTE: identical to it_802C1384
bool it_802C145C(Item_GObj* gobj)
{
    Item* ip;
    it_8026B3A8(gobj);
    ip = gobj->user_data;
    it_8026B3A8(gobj);
    Item_8026AE84(ip, 0x15FAE, 0x7F, 0x40);
    return true;
}

// NOTE: identical to it_802C1384
bool it_802C14B8(Item_GObj* gobj)
{
    Item* ip;
    it_8026B3A8(gobj);
    ip = gobj->user_data;
    it_8026B3A8(gobj);
    Item_8026AE84(ip, 0x15FAE, 0x7F, 0x40);
    return true;
}

// NOTE: identical to it_802C1384
bool it_802C1514(Item_GObj* gobj)
{
    Item* ip;
    it_8026B3A8(gobj);
    ip = gobj->user_data;
    it_8026B3A8(gobj);
    Item_8026AE84(ip, 0x15FAE, 0x7F, 0x40);
    return true;
}

void it_802C1570(Item_GObj* gobj, HSD_GObj* hobj)
{
    it_8026B894(gobj, hobj);
}
