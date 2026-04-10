#include "itdosei.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/ft_0C31.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"

#include <math.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

const f32 it_804DC878 = 0.0f;

static inline void itDosei_SetFacingAngle(Item_GObj* gobj, f32 m)
{
    f32 angle = (GET_ITEM(gobj)->facing_dir * M_PI_2 +
                 (GET_ITEM(gobj)->facing_dir * m));
    HSD_JObjSetRotationY(gobj->hsd_obj, angle);
}

static inline void itDosei_SetSpeed(Item_GObj* gobj, Item* ip, f32 speed)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    ip->x5D0_animFrameSpeed = speed;
    lb_8000BA0C(jobj, speed);
}

static inline void HSD_JObjSetRotationZero(Item_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_JObjSetRotationX(jobj, 0.0f);
    HSD_JObjSetRotationY(jobj, 0.0f);
    HSD_JObjSetRotationZ(jobj, 0.0f);
}

static inline void itDosei_SetRotX(HSD_JObj* jobj, f32 x)
{
    HSD_ASSERT(639, jobj);
    HSD_ASSERT(640, !(jobj->flags & JOBJ_USE_QUATERNION));
    jobj->rotate.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

static inline void itDosei_SetRotY(HSD_JObj* jobj, f32 y)
{
    HSD_ASSERT(660, jobj);
    HSD_ASSERT(661, !(jobj->flags & JOBJ_USE_QUATERNION));
    jobj->rotate.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

static inline void itDosei_SetRotZ(HSD_JObj* jobj, f32 z)
{
    HSD_ASSERT(681, jobj);
    HSD_ASSERT(682, !(jobj->flags & JOBJ_USE_QUATERNION));
    jobj->rotate.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

static inline void itDosei_SetFacingAngleFC(Item_GObj* gobj, f32 m)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    f32 angle = (GET_ITEM(gobj)->facing_dir * M_PI_2 +
                 (GET_ITEM(gobj)->facing_dir * m));
    HSD_ASSERT(660, jobj);
    HSD_ASSERT(661, !(jobj->flags & JOBJ_USE_QUATERNION));
    jobj->rotate.y = angle;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

/* 282DE4 */ static void it_80282DE4(Item_GObj* gobj);

extern s32 it_803F56B8[];

void it_3F14_Logic7_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itDoseiAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* new_var2;
    HSD_JObj* jobj;

    itResetVelocity(ip);
    {
        Item_GObj* gobj2 = gobj;
        ip->xDD4_itemVar.dosei.xDD4 = attr->unk4;
        ip->xDD4_itemVar.dosei.xDF0 = 0;
        ip->xDD4_itemVar.dosei.xDE0 = 1;
        it_8026B390(gobj2);
    }
    it_80282BFC(gobj);
    HSD_JObjSetRotationZero(gobj);
}

void fn_80281390(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
    Item_80268E5C(gobj, 0, 3);
    itDosei_SetSpeed(gobj, ip, 1.0f);
    ip->owner = NULL;
}

bool itDosei_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    HSD_JObjSetRotationZero(gobj);
    itDosei_SetFacingAngle(gobj, it_804DC878);
    ip->xDD4_itemVar.dosei.xDF0--;
    if (ip->xDD4_itemVar.dosei.xDF0 <= 0) {
        ip->xDD4_itemVar.dosei.xDF0 = 0;
        it_802817A0(gobj);
    }
    return false;
}

void itDosei_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion0_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D62C(gobj, it_80282074);
    it_80276CB8(gobj);
    return false;
}

void fn_80281734(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    if (ip->facing_dir == 1.0f) {
        if (ip->xDD4_itemVar.dosei.xDF8.x < 0.0f) {
            it_80281C6C(gobj);
            return;
        }
        it_802817A0(gobj);
        return;
    }
    if (ip->xDD4_itemVar.dosei.xDF8.x > 0.0f) {
        it_80281C6C(gobj);
        return;
    }
    it_802817A0(gobj);
}

void it_802817A0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itDoseiAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);

    ip->xD5C = 0;
    ip->xDC8_word.flags.x17 = 1;
    ip->xDC8_word.flags.x19 = 1;
    ip->owner = NULL;
    it_802762B0(ip);
    Item_80268E5C(gobj, 1, 0xB);
    itDosei_SetSpeed(gobj, ip, 1.0f);
    HSD_JObjSetRotationZero(gobj);
    itDosei_SetFacingAngle(gobj, it_804DC878);
    ip->x40_vel.x = ip->facing_dir * attr->unk8;
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
}

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
    frame_speed =
        0.5F * (ip2->x378_itemColl.floor.normal.x * ip2->facing_dir) + 1.0F;
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
    itDoseiAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.x = ip->facing_dir * ABS(attr->unk8 * ip->x5D0_animFrameSpeed);
}

bool itDosei_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (it_8026D8A4(gobj, it_80281C6C)) {
        if (it_80276308(gobj)) {
            it_80281C6C(gobj);
            return false;
        }

        {
            Item* ip2 = GET_ITEM(gobj);
            f32 angle = ABS(ip2->x378_itemColl.floor.normal.x);
            if (angle >= (f32) M_PI / 4.0f) {
                ip2->xD5C = 1;
                ip2->xDC8_word.flags.x1F = true;
            } else {
                ip2->xD5C = 0;
                ip2->xDC8_word.flags.x1F = false;
            }
        }

        if (ip->xD5C == 1) {
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
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.dosei.xDD8 = 0;
    ip->pos = ip->xDD4_itemVar.dosei.xDE4;
    ip->xDD4_itemVar.dosei.xDDC = 0.0F;
    ip->x40_vel.x = 0.0F;
    it_802762B0(ip);
    Item_80268E5C(gobj, 2, 3);
    itDosei_SetSpeed(gobj, ip, 1.0f);
    ip->owner = NULL;
}

bool itDosei_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    if (it_80272C6C(gobj) == 0) {
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        ip->facing_dir = -ip->facing_dir;
        itDosei_SetFacingAngle(gobj, it_804DC878);
    }
    return false;
}

void itDosei_UnkMotion2_Phys(Item_GObj* gobj) {}

static inline void itDosei_SetupWalk_Inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    itDoseiAttributes* attr = ip->xC4_article_data->x4_specialAttributes;

    ip->xD5C = 0;
    ip->xDC8_word.flags.x17 = 1;
    ip->xDC8_word.flags.x19 = 1;
    ip->owner = NULL;
    it_802762B0(ip);
    Item_80268E5C(gobj, 1, 0xB);
    itDosei_SetSpeed(gobj, ip, 1.0f);
    HSD_JObjSetRotationZero(gobj);
    itDosei_SetFacingAngle(gobj, it_804DC878);
    ip->x40_vel.x = ip->facing_dir * attr->unk8;
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
}

static inline void itDosei_SetupWalk_FC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    itDoseiAttributes* attr = ip->xC4_article_data->x4_specialAttributes;

    ip->xD5C = 0;
    ip->xDC8_word.flags.x17 = 1;
    ip->xDC8_word.flags.x19 = 1;
    ip->owner = NULL;
    it_802762B0(ip);
    Item_80268E5C(gobj, 1, 0xB);
    itDosei_SetSpeed(gobj, ip, 1.0f);
    {
        HSD_JObj* j = gobj->hsd_obj;
        itDosei_SetRotX(j, 0.0f);
        itDosei_SetRotY(j, 0.0f);
        itDosei_SetRotZ(j, 0.0f);
    }
    itDosei_SetFacingAngleFC(gobj, it_804DC878);
    ip->x40_vel.x = ip->facing_dir * attr->unk8;
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
}

bool itDosei_UnkMotion2_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8026D62C(gobj, it_80282074);
    if (ip->xDD4_itemVar.dosei.xDD8 == 2) {
        itDosei_SetupWalk_FC(gobj);
    }
    it_80276CB8(gobj);
    return false;
}

void it_80282074(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 3, 3);
    itDosei_SetSpeed(gobj, ip, 1.0f);
    ip->owner = NULL;
}

bool itDosei_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    if (it_80272C6C(gobj) == 0) {
        Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    }
    return false;
}

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

void it_3F14_Logic7_PickedUp(Item_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    Item* ip = GET_ITEM(gobj);
    itDoseiAttributes* attr = ip->xC4_article_data->x4_specialAttributes;

    if (ip->msid != 4) {
        Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
        HSD_JObjClearFlagsAll(HSD_JObjGetChild(jobj), JOBJ_HIDDEN);
        lb_8000BA0C(jobj, ip->x5D0_animFrameSpeed = attr->unk0);
        ip->xDC8_word.flags.x17 = 1;
        ip->xDC8_word.flags.x19 = 1;
    } else {
        Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    }
    if (ip->msid != 4) {
        HSD_JObjSetRotationZero(gobj);
        itDosei_SetFacingAngle(gobj, it_804DC878);
    }
}

bool itDosei_UnkMotion4_Anim(Item_GObj* gobj)
{
    PAD_STACK(16);
    if (!it_80272C6C(gobj)) {
        HSD_JObj* jobj = gobj->hsd_obj;
        Item* ip = GET_ITEM(gobj);
        itDoseiAttributes* attr = ip->xC4_article_data->x4_specialAttributes;

        if (ip->msid != 4) {
            Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
            HSD_JObjClearFlagsAll(HSD_JObjGetChild(jobj), JOBJ_HIDDEN);
            lb_8000BA0C(jobj, ip->x5D0_animFrameSpeed = attr->unk0);
            ip->xDC8_word.flags.x17 = 1;
            ip->xDC8_word.flags.x19 = 1;
        } else {
            Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
        }
        if (ip->msid != 4) {
            HSD_JObj* jobj2 = gobj->hsd_obj;
            itDosei_SetRotX(jobj2, 0.0f);
            itDosei_SetRotY(jobj2, 0.0f);
            itDosei_SetRotZ(jobj2, 0.0f);
            itDosei_SetFacingAngleFC(gobj, it_804DC878);
        }
    }
    return false;
}

void itDosei_UnkMotion4_Phys(Item_GObj* gobj) {}

void it_3F14_Logic7_Dropped(Item_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    Item* ip = GET_ITEM(gobj);
    itDoseiAttributes* attr = ip->xC4_article_data->x4_specialAttributes;

    it_8026B390(gobj);
    HSD_JObjClearFlagsAll(HSD_JObjGetChild(jobj), JOBJ_HIDDEN);
    ip->xDC8_word.flags.x17 = 1;
    ip->xDC8_word.flags.x19 = 1;
    Item_80268E5C(gobj, 5, 6);
    lb_8000BA0C(jobj, ip->x5D0_animFrameSpeed = attr->unk0);
    HSD_JObjSetRotationZero(gobj);
    itDosei_SetFacingAngle(gobj, it_804DC878);
}

void it_3F14_Logic7_Thrown(Item_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    Item* ip = GET_ITEM(gobj);
    itDoseiAttributes* attr = ip->xC4_article_data->x4_specialAttributes;

    if (ip->msid != 5) {
        it_8026B390(gobj);
        HSD_JObjClearFlagsAll(HSD_JObjGetChild(jobj), JOBJ_HIDDEN);
        Item_80268E5C(gobj, 5, 6);
        lb_8000BA0C(jobj, ip->x5D0_animFrameSpeed = attr->unk0);
    } else {
        Item_80268E5C(gobj, 5, 6);
    }
    it_80274484(gobj, jobj, ip->xDD4_itemVar.dosei.xDE0);
}

bool itDosei_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}
void itDosei_UnkMotion5_Phys(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

void it_3F14_Logic7_EnteredAir(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    s32 motion_id;
    if (!ip->xDC8_word.flags.x19) {
        motion_id = 0xA;
    } else {
        motion_id = 6;
    }
    Item_80268E5C(gobj, motion_id, 3);
    {
        HSD_JObj* jobj = gobj->hsd_obj;
        ip->x5D0_animFrameSpeed = 1.0f;
        lb_8000BA0C(jobj, 1.0f);
    }
    ip->owner = NULL;
}

bool itDosei_UnkMotion6_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    return false;
}

void itDosei_UnkMotion6_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion6_Coll(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ip->xDD4_itemVar.dosei.xDF8 = ip->x378_itemColl.floor.normal;
    it_8026E8C4(gobj, fn_80281734, it_80282074);
    return false;
}

void it_80282BFC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj;
    Item_80268E5C(gobj, 8, 3);
    jobj = gobj->hsd_obj;
    ip->x5D0_animFrameSpeed = 1.0F;
    lb_8000BA0C(jobj, 1.0F);
    ip->owner = NULL;
}

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

void fn_80282CD4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    it_802762B0(ip);
    Item_80268E5C(gobj, 7, 3);
    {
        HSD_JObj* jobj = gobj->hsd_obj;
        ip->x5D0_animFrameSpeed = 1.0f;
        lb_8000BA0C(jobj, 1.0f);
    }
    ip->owner = NULL;
}

bool itDosei_UnkMotion7_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;

    if (ip->xDD4_itemVar.dosei.xDD4 > 0) {
        ip->xDD4_itemVar.dosei.xDD4--;
    } else {
        it_80282DE4(gobj);
    }

    return false;
}

void itDosei_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion7_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D62C(gobj, it_80282BFC);
    it_80276CB8(gobj);
    return false;
}

static void it_80282DE4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(16);

    ip->xDD4_itemVar.dosei.xDD8 = 1;
    ip->xDD4_itemVar.dosei.xDDC = M_PI_2;
    ip->x40_vel.x = 0.0f;
    ip->xDC8_word.flags.x17 = 1;
    ip->xDC8_word.flags.x19 = 1;
    ip->owner = NULL;
    Item_80268E5C(gobj, 9, 3);
    ip->x5D0_animFrameSpeed = 1.0f;
    lb_8000BA0C(jobj, 1.0f);
    HSD_JObjSetRotationZero(gobj);
    {
        f32 angle =
            (GET_ITEM(gobj)->facing_dir * M_PI_2 +
             (GET_ITEM(gobj)->facing_dir * -ip->xDD4_itemVar.dosei.xDDC));
        HSD_JObjSetRotationY(gobj->hsd_obj, angle);
    }
}

bool itDosei_UnkMotion9_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itDoseiAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(16);

    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    ip->xDD4_itemVar.dosei.xDDC =
        (ip->xDD4_itemVar.dosei.xDDC - (M_PI / attr->unkC));
    if (ip->xDD4_itemVar.dosei.xDD8 == 1) {
        HSD_JObj* jobj = gobj->hsd_obj;
        f32 angle =
            (GET_ITEM(gobj)->facing_dir * M_PI_2 +
             (GET_ITEM(gobj)->facing_dir * -ip->xDD4_itemVar.dosei.xDDC));
        HSD_JObjSetRotationY(jobj, angle);
        if (ip->xDD4_itemVar.dosei.xDDC <= 0.0f) {
            ip->xDD4_itemVar.dosei.xDD8 = 2;
            ip->x40_vel.x = ip->facing_dir * attr->unk8;
        }
    }
    if (it_80272C6C(gobj) == 0) {
        Item_80268E5C(gobj, 9, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itDosei_UnkMotion9_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion9_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8026D62C(gobj, it_80282074);
    if (ip->xDD4_itemVar.dosei.xDD8 == 2) {
        f32 frame = ip->x5CC_currentAnimFrame;
        itDosei_SetupWalk_FC(gobj);
        Item_80268DD4(gobj, frame);
    }
    it_80276CB8(gobj);
    return false;
}

void itDosei_UnkMotion10_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion10_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, fn_80282CD4, it_80282BFC);
    return false;
}

bool itDosei_UnkMotion10_Anim(Item_GObj* gobj)
{
    Item* ip;
    HSD_JObj* jobj;
    ip = gobj->user_data;
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    jobj = gobj->hsd_obj;
    ip->x5D0_animFrameSpeed = 1.0F;
    lb_8000BA0C(jobj, 1.0F);
    return false;
}

bool it_3F14_Logic7_DmgReceived(Item_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    Item* ip = GET_ITEM(gobj);
    itDoseiAttributes* attr = ip->xC4_article_data->x4_specialAttributes;

    Item_80268E5C(gobj, 0xB, 3);
    it_802762BC(ip);
    ip->x5D0_animFrameSpeed = 1.0f;
    lb_8000BA0C(jobj, 1.0f);
    ip->x40_vel.x = attr->unk10 * ip->facing_dir;
    ip->x40_vel.y = ABS(attr->unk14);
    ip->x40_vel.z = 0.0f;
    ip->xDC8_word.flags.x17 = 1;
    ip->xDC8_word.flags.x19 = 1;
    ip->xDD4_itemVar.dosei.xDF0 = 20;
    {
        HSD_JObj* jobj2 = gobj->hsd_obj;
        HSD_JObjSetRotationX(jobj2, 0.0f);
        HSD_JObjSetRotationY(jobj2, 0.0f);
        HSD_JObjSetRotationZ(jobj2, 0.0f);
    }
    itDosei_SetFacingAngle(gobj, it_804DC878);
    ip->owner = NULL;
    ip->xD44_lifeTimer -= 60.0f;
    return it_80273130(gobj);
}

bool itDosei_UnkMotion11_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    if (it_80272C6C(gobj) == 0) {
        Item_80268E5C(gobj, 11, ITEM_ANIM_UPDATE);
    }
    return false;
}

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

bool it_3F14_Logic7_DmgDealt(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    Item_8026AF0C(ip, it_803F56B8[HSD_Randi(3)], 127, 64);
    if (ip->msid == 5) {
        itColl_BounceOffVictim(gobj);
        it_802725D4(gobj);
    }
    return false;
}

bool itDosei_Logic7_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool itDosei_Logic7_Clanked(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool itDosei_Logic7_HitShield(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool itDosei_Logic7_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void itDosei_Logic7_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
