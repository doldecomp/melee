#include "it_2725.h"

#include "it_279C.h"
#include "it_3F14.h"
#include "itanimlist.h"
#include "iteffect.h"
#include "ithitbox.h"
#include "itmaplib.h"
#include "math.h"

#include "baselib/jobj.h"
#include "baselib/random.h"
#include "db/db.h"
#include "ef/efsync.h"
#include "ft/ft_0C31.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/itcoll.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcollision.h"
#include "lb/lbvector.h"
#include "mp/mpcoll.h"

#include <baselib/gobjobject.h>

extern f32 it_804DC73C;

#define it_2725_JObjSetTranslate(jobj, vec)                                   \
    {                                                                         \
        ((jobj) ? ((void) 0) : __assert("jobj.h", 916, "jobj"));              \
        ((vec) ? ((void) 0) : __assert("jobj.h", 917, "translate"));          \
        ((HSD_JObj*) (jobj))->translate = *(vec);                             \
        if (!(((HSD_JObj*) (jobj))->flags & JOBJ_MTX_INDEP_SRT)) {            \
            HSD_JObjSetMtxDirty(jobj);                                        \
        }                                                                     \
    }

#define it_2725_JObjGetTranslation(jobj, vec)                                 \
    {                                                                         \
        ((jobj) ? ((void) 0) : __assert("jobj.h", 979, "jobj"));              \
        ((vec) ? ((void) 0) : __assert("jobj.h", 980, "translate"));          \
        *(vec) = ((HSD_JObj*) (jobj))->translate;                             \
    }

static inline void it_2725_JObjSetTranslateInline(HSD_JObj* jobj, Vec3* vec)
{
    if (jobj == NULL) {
        __assert("jobj.h", 916, "jobj");
    }
    if (vec == NULL) {
        __assert("jobj.h", 917, "translate");
    }
    jobj->translate = *vec;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void it_8027129C_by_4(Item_GObj* item_gobj)
{
    u32 cnt;

    for (cnt = 0; cnt < 4; cnt++) {
        it_8027129C(item_gobj, cnt);
    }
}

void it_80272560(Item_GObj* item_gobj, s32 idx)
{
    Item* item;
    s32 stack[2];

    item = item_gobj->user_data;
    lbColl_80008428(&item->x5D4_hitboxes[idx].hit);
    item->xDAA_flag.b2 = false;

    it_8027129C_by_4(item_gobj);
}

void it_802725D4(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    u32 i;
    for (i = 0; i < 4; ++i) {
        lbColl_80008428(&item->x5D4_hitboxes[i].hit);
    }
    for (i = 0; i < 4; ++i) {
        it_8027129C(item_gobj, i);
    }
    item->xDC8_word.flags.x16 = 0;
    item->xDAA_flag.b2 = 0;
}

void it_80272674(Item_GObj* item_gobj, s32 idx)
{
    HitCapsuleState state;
    Item* item = item_gobj->user_data;
    HitCapsule* hitbox;

    lbColl_80008434(&item->x5D4_hitboxes[idx].hit);
    item->xDC8_word.flags.x16 = 1;

    item = GET_ITEM(item_gobj);
    hitbox = &item->x5D4_hitboxes[idx].hit;
    state = hitbox->state;

    switch (state) {
    case HitCapsule_Enabled:
        lb_8000B1CC(hitbox->jobj, &hitbox->b_offset, &hitbox->x4C);
        hitbox->x58 = hitbox->x4C;
        hitbox->state = 2;
        item->xDAA_flag.b2 = 1;
        return;
    case HitCapsule_Unk2:
        hitbox->state = 3;
        /* fallthrough */
    case HitCapsule_Unk3:
        hitbox->x58 = hitbox->x4C;
        lb_8000B1CC(hitbox->jobj, &hitbox->b_offset, &hitbox->x4C);
        /* fallthrough */
    case HitCapsule_Unk4:
    case HitCapsule_Disabled:
        return;
    }
}

static inline void it_80272784_inline(Item_GObj* item_gobj)
{
    u32 i;

    for (i = 0; i < 4; ++i) {
        it_8027129C(item_gobj, i);
    }
}

void it_80272784(Item_GObj* item_gobj)
{
    u32 i;
    Item* item = GET_ITEM(item_gobj);
    Item* hitbox_item = item;

    for (i = 0; i < 4; ++i) {
        lbColl_80008434(&hitbox_item->x5D4_hitboxes[i].hit);
    }
    item->xDC8_word.flags.x16 = 1;
    it_80272784_inline(item_gobj);
}

Fighter* it_80272818(Item* item)
{
    return ((it_2728_DatAttrs*) item->xC4_article_data->x4_specialAttributes)
        ->fighter;
}

/// Returns Item_GObj of the specified kind if part of HSD_GObj_Entities->items
Item_GObj* it_80272828(ItemKind kind)
{
    Item_GObj* item_gobj_return;
    Item* new_var2;
    Item_GObj* item_gobj_check;
    void* new_var;
    item_gobj_return = NULL;
    item_gobj_check = (Item_GObj*) HSD_GObj_Entities->items;
    while (item_gobj_check != NULL) {
        new_var2 = (Item*) (new_var = item_gobj_check->user_data);
        if (new_var2->kind == kind) {
            item_gobj_return = item_gobj_check;
        }

        item_gobj_check = item_gobj_check->next;
    }
    return item_gobj_return;
}

void it_80272860(Item_GObj* item_gobj, f32 arg1, f32 arg2)
{
    Item* item;
    f32 var_f3;
    s32 var_r0;
    s32 var_r3;

    item = item_gobj->user_data;
    // if these aren't ternaries it allocates registers differently .-.
    var_r0 = arg1 < 0.0f ? -1 : 1;

    var_f3 = item->x40_vel.y;

    var_r3 = var_f3 < 0.0f ? -1 : 1;

    if (var_r3 != var_r0) {
        if (var_f3 < 0.0f) {
            var_f3 = -var_f3;
        }
        if (var_f3 < arg2) {
        label_1:
            item->x40_vel.y -= arg1;
            return;
        }
        return;
    }
    // big dumb
    goto label_1;
}

void it_802728C8(Item_GObj* item_gobj)
{
    u32 rem;
    HSD_JObj* item_jobj2;
    HSD_JObj* item_jobj1;
    PAD_STACK(12);

    item_jobj1 = GET_JOBJ(item_gobj);
    item_jobj2 = item_jobj1 == NULL ? NULL : item_jobj1->child;
    rem = (u32) (s32) ((Item*) item_gobj->user_data)->xD44_lifeTimer %
          it_804D6D28->x44_float;
    if (rem != 0) {
        HSD_JObjClearFlagsAll(item_jobj2, 0x10U);
        return;
    }
    HSD_JObjSetFlagsAll(item_jobj2, 0x10U);
}

void it_80272940(Item_GObj* item_gobj)
{
    HSD_JObj* item_jobj2;
    HSD_JObj* item_jobj1;

    item_jobj1 = GET_JOBJ(item_gobj);
    item_jobj2 = item_jobj1 == NULL ? NULL : item_jobj1->child;
    HSD_JObjClearFlagsAll(item_jobj2, 0x10U);
}

void it_80272980(Item_GObj* item_gobj)
{
    f32 dir;
    f32 vel_x;
    s32 int_dir;
    Item* item;

    item = item_gobj->user_data;
    vel_x = item->x40_vel.x;
    if (vel_x < 0.0f) {
        vel_x = -vel_x;
    }
    if (!(vel_x < 0.00001f) || !item->facing_dir) {
        if (item->x40_vel.x >= 0.0f) {
            dir = 1.0f;
        } else {
            dir = -1.0f;
        }
        item->facing_dir = dir;
    }

    if (-1.0f == item->facing_dir) {
        int_dir = -1;
    } else {
        int_dir = 1;
    }
    mpCollSetFacingDir(&item->x378_itemColl, int_dir);
}

void it_80272A18(HSD_JObj* item_jobj)
{
    HSD_JObjClearFlagsAll(item_jobj, 0x10U);
}

void it_80272A3C(HSD_JObj* item_jobj)
{
    HSD_JObjSetFlagsAll(item_jobj, 0x10U);
}

void it_80272A60(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    efSync_Spawn(0x40E, item_gobj, &item->pos);
    Item_8026AE84(item, 0x74, 0x7F, 0x40);
    it_80274C60(item_gobj);
}

void it_80272AC4(Item_GObj* item_gobj, Vec3* arg1)
{
    Item* item = GET_ITEM(item_gobj);
    lbVector_Add(arg1, &item->pos);
    efSync_Spawn(0x40C, item_gobj, arg1);
    Item_8026AE84(item, 0x74, 0x7F, 0x40);
    it_80274C60(item_gobj);
}

void it_80272B40(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    efSync_Spawn(0x40C, item_gobj, &item->pos);
    Item_8026AE84(item, 0x74, 0x7F, 0x40);
    it_80274C60(item_gobj);
}

void it_80272BA4(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    efSync_Spawn(0x411, item_gobj, &item->pos);
    Item_8026AE84(item, 0x73, 0x7F, 0x40);
    it_80274C60(item_gobj);
}

void it_80272C08(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    efSync_Spawn(0x410, item_gobj, &item->pos);
    Item_8026AE84(item, 0x74, 0x7F, 0x40);
    it_80274C60(item_gobj);
}

bool it_80272C6C(Item_GObj* item_gobj)
{
    return lb_8000B09C(item_gobj->hsd_obj);
}

HSD_JObj* it_80272C90(Item_GObj* item_gobj)
{
    return it_80272CC0(
        item_gobj, ((Item*) item_gobj->user_data)
                       ->xC4_article_data->x10_modelDesc->x8_bone_attach_id);
}

#pragma auto_inline off

HSD_JObj* it_80272CC0(Item_GObj* item_gobj, enum_t idx)
{
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* jobj = GET_JOBJ(item_gobj);
    if (item->xC4_article_data->x10_modelDesc->x4_bone_count != 0) {
        return item->xBBC_dynamicBoneTable->bones[idx];
    }
    if (idx != 0) {
        for (; idx > 0; --idx) {
            jobj = HSD_JObjGetChild(jobj);
        }
    }

    return jobj;
}

#pragma auto_inline on

bool it_80272D1C(Item_GObj* item_gobj)
{
    if ((item_gobj != NULL) && (item_gobj->classifier == HSD_GOBJ_CLASS_ITEM))
    {
        return true;
    }
    return false;
}

#pragma push
#pragma dont_inline on

s32 it_80272D40(Item_GObj* item_gobj)
{
    bool chk;

    if (ftLib_80086960(item_gobj)) {
        return 0;
    }
    if ((item_gobj != NULL) && (item_gobj->classifier == HSD_GOBJ_CLASS_ITEM))
    { // ITEM_UNK_ENEMY?
        chk = true;
    } else {
        chk = false;
    }
    if (chk) {
        return 1;
    }
    return 2;
}

#pragma pop

void itColl_BounceOffVictim(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    item->x40_vel.x *= it_804D6D28->x58_float;
    item->x40_vel.y =
        (item->x40_vel.y * it_804D6D28->x5C_float) + it_804D6D28->x60_float;
}

void it_80272DE4(HSD_JObj* jobj, f32 scale)
{
    HSD_JObjAddScaleX(jobj, scale);
    HSD_JObjAddScaleY(jobj, scale);
    HSD_JObjAddScaleZ(jobj, scale);
}

void it_80272F7C(HSD_JObj* jobj, f32 scale)
{
    Vec3 temp;

    temp.x = temp.y = temp.z = scale;
    HSD_JObjSetScale(jobj, &temp);
}

bool it_80273030(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->x40_vel.x = -item->x40_vel.x * item->xC70;
    item->x40_vel.y = -item->x40_vel.y * item->xC70;
    item->facing_dir = -item->facing_dir;
    item->xD44_lifeTimer = item->xD48_halfLifeTimer;
    return false;
}

bool itColl_BounceOffShield(Item_GObj* item_gobj)
{
    Item* item;
    f32 dir;
    f32 vel_x;
    s32 int_dir;
    PAD_STACK(4);

    item = GET_ITEM(item_gobj);
    lbVector_Mirror(&item->x40_vel, &item->xC58);
    item = item_gobj->user_data;
    if (!(ABS(item->x40_vel.x) < 0.00001f) || !item->facing_dir) {
        if (item->x40_vel.x >= 0.0f) {
            dir = 1.0f;
        } else {
            dir = -1.0f;
        }
        item->facing_dir = dir;
    }
    if (-1.0f == item->facing_dir) {
        int_dir = -1;
    } else {
        int_dir = 1;
    }
    mpCollSetFacingDir(&item->x378_itemColl, int_dir);
    return false;
}

bool it_80273130(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xD44_lifeTimer--;
    if (item->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

void it_80273168(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    if (!(item->xDCD_flag.b2)) {
        Item_8026AE84(item, item->xD70, 0x7F, 0x40);
    }
}

void it_802731A4(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    if (!(item->xDCD_flag.b2)) {
        Item_8026AE84(item, item->xD78, 0x7F, 0x40);
    }
}

void it_802731E0(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    if (!(item->xDCD_flag.b2)) {
        Item_8026AE84(item, item->xD74, 0x7F, 0x40);
    }
}

void it_8027321C(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    if (!item->xDCD_flag.b2) {
        if (item->kind == It_Kind_Unk4) {
            lbAudioAx_80023870(item->xD84, 0x7F, 0x40, 0x9A);
            return;
        }
        Item_8026AE84(item, item->xD84, 0x7F, 0x40);
    }
}

void it_8027327C(Item_GObj* item_gobj, enum_t ID1, enum_t ID2)
{
    Item* item;

    item = item_gobj->user_data;
    if (ID1 != -1) {
        it_802787B4(item_gobj, ID1);
    }
    if (!item->xDCD_flag.b2) {
        it_802732E4(item, ID2);
        if (ID2 == 0x12F) {
            lbAudioAx_80024DC4(ID2);
        }
    }
}

void it_802732E4(Item* item, s32 arg1)
{
    if (!item->xDCD_flag.b2) {
        Item_8026AE84(item, arg1, 0x7F, 0x40);
    }
}

void it_80273318(Item_GObj* item_gobj, HSD_Joint* joint)
{
    Item* item = GET_ITEM(item_gobj);

    item->xC8_joint = joint;
    HSD_GObjObject_80390B0C(item_gobj);
    Item_802680CC(item_gobj);
    Item_8026849C(item_gobj);
    it_2725_JObjSetTranslateInline(item_gobj->hsd_obj, &item->pos);
}

void it_80273408(Item_GObj* item_gobj)
{
    it_80273454(item_gobj);
    it_8027346C(item_gobj);
    it_80273484(item_gobj);
    it_8027349C(item_gobj);
    it_802734B4(item_gobj);
}

void it_80273454(Item_GObj* item_gobj)
{
    Item* item = item_gobj->user_data;

    item->x40_vel.x = item->x40_vel.y = item->x40_vel.z = 0.0f;
}

void it_8027346C(Item_GObj* item_gobj)
{
    Item* item = item_gobj->user_data;

    item->x64_vec_unk2.x = item->x64_vec_unk2.y = item->x64_vec_unk2.z = 0.0f;
}

void it_80273484(Item_GObj* item_gobj)
{
    Item* item = item_gobj->user_data;

    item->x58_vec_unk.x = item->x58_vec_unk.y = item->x58_vec_unk.z = 0.0f;
}

void it_8027349C(Item_GObj* item_gobj)
{
    Item* item = item_gobj->user_data;

    item->x70_nudge.x = item->x70_nudge.y = item->x70_nudge.z = 0.0f;
}

void it_802734B4(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    item->x7C.x = item->x7C.y = item->x7C.z = 0.0f;
    item->x88.x = item->x88.y = item->x88.z = 0.0f;
    item->x94.x = item->x94.y = item->x94.z = 0.0f;
    item->xA0.x = item->xA0.y = item->xA0.z = 0.0f;
    item->xAC_unk.x = item->xAC_unk.z = 0.0f;
    item->xAC_unk.y = 1.0f;
}

void it_80273500(Item_GObj* item_gobj, Vec3* arg1)
{
    Item* item = GET_ITEM(item_gobj);
    item->x40_vel.x = arg1->x;
    item->x40_vel.y = arg1->y;
    item->x40_vel.z = arg1->z;
    it_8027346C(item_gobj);
    it_80273484(item_gobj);
    it_8027349C(item_gobj);
    it_802734B4(item_gobj);
}

void it_80273598(Item_GObj* item_gobj, s32 arg1, s32 arg2)
{
    Item* item = GET_ITEM(item_gobj);
    if (item->owner != NULL && ftLib_80086960(item->owner)) {
        ftLib_80086D40(item->owner, arg1, arg2);
    }
}

void it_80273600(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    if (item->owner != NULL && ftLib_80086960(item->owner)) {
        ftLib_80086E68(item->owner);
    }
}

void it_80273648(Item_GObj* item_gobj, s32 arg1, s32 arg2)
{
    ftLib_80086DC4(arg1, arg2);
}

void it_80273670(Item_GObj* item_gobj, int arg1, f32 arg8)
{
    HSD_JObj* item_jobj1;
    HSD_JObj* item_jobj2;
    Item* item;
    HSD_Joint* joint;
    ItemStateDesc* desc;

    item = GET_ITEM(item_gobj);
    item_jobj1 = GET_JOBJ(item_gobj);
    item->xD0_itemStateDesc =
        &(item->xC4_article_data->xC_itemStates->x0_itemStateDesc[arg1]);
    if (item->xD0_itemStateDesc != NULL) {
        HSD_JObjRemoveAnimAll(item_jobj1);
        joint = item->xC8_joint;
        if (joint != NULL) {
            if (item_jobj1 == NULL) {
                item_jobj2 = NULL;
            } else {
                item_jobj2 = item_jobj1->child;
            }
            lb_8000B804(item_jobj2, joint->child);
        }
        desc = item->xD0_itemStateDesc;
        HSD_JObjAddAnimAll(item_jobj1, desc->x0_anim_joint,
                           desc->x4_matanim_joint,
                           (HSD_ShapeAnimJoint*) desc->x8_parameters);
        lb_8000BA0C(item_jobj1, item->x5D0_animFrameSpeed);
        HSD_JObjReqAnimAll(item_jobj1, arg8);
    }
    HSD_JObjAnimAll(item_jobj1);
    HSD_JObjRemoveAnimAll(item_jobj1);
    item->x524_cmd.u = NULL;
}

void it_80273748(Item_GObj* item_gobj, Vec3* pos, Vec3* vel)
{
    Item* item;
    HSD_JObj* jobj2;
    f32 rotation;
    f32 dir_radians;
    f32 dir;
    f32 vel_x;
    s32 hold_kind;
    s32 int_dir;
    Vec3 sp54;
    Vec3 sp48;
    Vec3 sp3C;
    HSD_JObj* jobj_2;
    Item* item_2;
    HSD_GObj* owner;
    HSD_JObj* jobj;
    PAD_STACK(32);

    item = GET_ITEM(item_gobj);
    jobj = GET_JOBJ(item_gobj);
    owner = item->owner;
    it_80275070(item_gobj,
                item->xC4_article_data->x10_modelDesc->x8_bone_attach_id);
    if (!it_8026B6C8(item_gobj)) {
        it_8026B390(item_gobj);
    }
    it_802756E0(item_gobj);
    item_2 = item_gobj->user_data;
    jobj_2 = item_gobj->hsd_obj;
    rotation = it_80274990(item_gobj);
    lb_8000B804(jobj_2, item_2->xC8_joint);
    Item_8026849C(item_gobj);
    it_80274658(item_gobj, rotation);
    if (item->xDC8_word.flags.x0) {
        owner = item->x51C;
    }
    item->x40_vel = *vel;
    item->x40_vel.x *= item->xCC_item_attr->x4_throw_speed_mul;
    item->x40_vel.y *= item->xCC_item_attr->x4_throw_speed_mul;
    item->x40_vel.z *= item->xCC_item_attr->x4_throw_speed_mul;
    {
        Item* item = item_gobj->user_data;
        vel_x = item->x40_vel.x;
        if (vel_x < 0.0f) {
            vel_x = -vel_x;
        }
        if (!(vel_x < 0.00001f) || (!item->facing_dir)) {
            if (item->x40_vel.x >= 0.0f) {
                dir = 1.0f;
            } else {
                dir = -1.0f;
            }
            item->facing_dir = dir;
        }
        if (-1.0f == item->facing_dir) {
            int_dir = -1;
        } else {
            int_dir = 1;
        }
        mpCollSetFacingDir(&item->x378_itemColl, int_dir);
    }
    if (item->xDC8_word.flags.x19 == 1) {
        dir_radians = M_PI_2 * item->facing_dir;
        HSD_JObjSetRotationY(jobj, dir_radians);
    }
    if (((it_8026B2B4(item_gobj) == 1) &&
         (hold_kind = item->hold_kind, (hold_kind != 4)) &&
         (hold_kind != 6)) ||
        (item->hold_kind == 8))
    {
        jobj2 = it_80272C90(item_gobj);
        it_2725_JObjGetTranslation(jobj2, &sp3C);
        sp3C.x = -sp3C.x;
        sp3C.y = -sp3C.y;
        sp3C.z = -sp3C.z;
        lb_8000B1CC(ftLib_80086630((Fighter_GObj*) owner, item->xDC4), &sp3C,
                    &sp54);
        lb_8000B1CC(ftLib_80086630((Fighter_GObj*) owner, item->xDC4), NULL,
                    &sp48);
        sp3C.x = sp54.x - sp48.x;
        sp3C.y = sp54.y - sp48.y;
        sp3C.z = 0.0f;
    } else {
        sp3C.x = sp3C.y = sp3C.z = 0.0f;
    }
    item->pos.x = pos->x + sp3C.x;
    item->pos.y = pos->y + sp3C.y;
    item->pos.z = 0.0f;
    it_2725_JObjSetTranslate(jobj, &item->pos);
}

void it_80273B50(Item_GObj* item_gobj, Vec3* vel)
{
    s32 stack_top[9];
    Item* item;
    HSD_GObj* owner_gobj;
    HSD_JObj* jobj;
    f32 rotation;
    f32 dir_radians;
    f32 dir;
    f32 vel_x;
    s32 hold_kind;
    Vec3 sp40;
    Vec3 sp34;
    s32 int_dir;
    Vec3* pos;
    HSD_JObj* item_jobj3;
    HSD_JObj* item_jobj1;
    Item* item3;

    item = GET_ITEM(item_gobj);
    item_jobj1 = GET_JOBJ(item_gobj);
    owner_gobj = item->owner;
    it_80275070(item_gobj,
                item->xC4_article_data->x10_modelDesc->x8_bone_attach_id);
    if (!it_8026B6C8(item_gobj)) {
        it_8026B390(item_gobj);
    }
    it_802756E0(item_gobj);
    {
        HSD_JObj* item_jobj2;
        Item* item = GET_ITEM(item_gobj);
        item_jobj2 = GET_JOBJ(item_gobj);
        rotation = it_80274990(item_gobj);
        lb_8000B804(item_jobj2, item->xC8_joint);
        Item_8026849C(item_gobj);
    }
    it_80274658(item_gobj, rotation);
    if (item->xDC8_word.flags.x0) {
        owner_gobj = item->x51C;
    }
    item->x40_vel = *vel;
    item->x40_vel.x *= item->xCC_item_attr->x4_throw_speed_mul;
    item->x40_vel.y *= item->xCC_item_attr->x4_throw_speed_mul;
    item->x40_vel.z *= item->xCC_item_attr->x4_throw_speed_mul;
    {
        Item* item2 = GET_ITEM(item_gobj);
        vel_x = item2->x40_vel.x;
        if (vel_x < 0.0f) {
            vel_x = -vel_x;
        }
        if (!(vel_x < 0.00001f) || !item2->facing_dir) {
            if (item2->x40_vel.x >= 0.0f) {
                dir = 1.0f;
            } else {
                dir = -1.0f;
            }
            item2->facing_dir = dir;
        }
        if (-1.0f == item2->facing_dir) {
            int_dir = -1;
        } else {
            int_dir = 1;
        }
        mpCollSetFacingDir(&item2->x378_itemColl, int_dir);
    }
    if (item->xDC8_word.flags.x19 == 1) {
        dir_radians = M_PI_2 * item->facing_dir;
        HSD_JObjSetRotationY(item_jobj1, dir_radians);
    }
    if (((it_8026B2B4(item_gobj) == 1) &&
         (hold_kind = item->hold_kind, (hold_kind != 4)) &&
         (hold_kind != 6)) ||
        (item->hold_kind == 8))
    {
        jobj = it_80272C90(item_gobj);
        it_2725_JObjGetTranslation(jobj, &sp40);
        sp40.x = -sp40.x;
        sp40.y = -sp40.y;
        sp40.z = -sp40.z;
    } else {
        sp40.x = sp40.y = sp40.z = 0.0f;
    }
    {
        Item* item3 = GET_ITEM(item_gobj);
        HSD_JObj* item_jobj3 = GET_JOBJ(item_gobj);
        if (&sp40 != NULL) {
            lb_8000B1CC(
                ftLib_80086630((Fighter_GObj*) owner_gobj, item3->xDC4), &sp40,
                &sp34);
        } else {
            lb_8000B1CC(
                ftLib_80086630((Fighter_GObj*) owner_gobj, item3->xDC4), NULL,
                &sp34);
        }
        pos = &item3->pos;
        item3->pos.x = sp34.x;
        item3->pos.y = sp34.y;
        item3->pos.z = 0.0f;
        it_2725_JObjSetTranslate(item_jobj3, pos);
    }
}

void it_80273F34(Item_GObj* item_gobj, HSD_GObj* arg_gobj2)
{
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* item_jobj = GET_JOBJ(item_gobj);
    f32 rotate;
    s32 int_dir;

    item->xDC8_word.flags.x13 = 0;
    item->xDC8_word.flags.x14 = 1;
    item->xDC4 = 0;
    item->xD54_throwNum++;
    item->xD50_landNum = 0;

    it_80275BC8(item_gobj, arg_gobj2);
    it_80274DAC(item_gobj);

    if (item->xDC8_word.flags.x19 == 1) {
        rotate = M_PI_2 * item->facing_dir;
        HSD_JObjSetRotationY(item_jobj, rotate);
    }

    if (ftLib_80086960(arg_gobj2)) {
        Item_8026A848(item_gobj, arg_gobj2);
        it_8027B070(item_gobj, arg_gobj2);
    }

    if (-1.0f == item->facing_dir) {
        int_dir = -1;
    } else {
        int_dir = 1;
    }

    mpCollSetFacingDir(&item->x378_itemColl, int_dir);
    Item_8026B074(item);
    it_802762BC(item);
    it_2725_JObjSetTranslate(item_jobj, &item->pos);

    it_8027B4A4(arg_gobj2, item_gobj);
    it_8027B378(arg_gobj2, item_gobj, it_802758D4(item_gobj));
}

void it_80274198(Item_GObj* item_gobj, bool chk)
{
    Item* item;
    HSD_GObj* owner_gobj;
    HSD_GObj* x51C_gobj;

    item = item_gobj->user_data;
    owner_gobj = item->owner;
    if (item->xDC8_word.flags.x0 != 0) {
        if (chk == true) {
            x51C_gobj = item->x51C;
            item->owner = x51C_gobj;
            owner_gobj = x51C_gobj;
            item->x51C = NULL;
        } else {
            owner_gobj = item->x51C;
        }
    }
    it_80273F34(item_gobj, owner_gobj);
}

void it_802741F4(Item_GObj* item_gobj, bool chk)
{
    Item* item = GET_ITEM(item_gobj);
    HSD_GObj* owner_gobj = item->owner;
    if (item->xDC8_word.flags.x0) {
        if (chk == true) {
            HSD_GObj* x51C_gobj = item->x51C;
            item->owner = x51C_gobj;
            owner_gobj = x51C_gobj;
            item->x51C = NULL;
        } else {
            owner_gobj = item->x51C;
        }
    }
    it_80273F34(item_gobj, owner_gobj);
}

void it_80274250(Item_GObj* item_gobj, Vec3* arg1)
{
    HSD_GObj* owner_gobj;
    Item* item;
    PAD_STACK(16);

    it_80273B50(item_gobj, arg1);
    item = GET_ITEM(item_gobj);
    owner_gobj = item->owner;
    if (item->xDC8_word.flags.x0) {
        owner_gobj = item->x51C;
    }
    it_80273F34(item_gobj, owner_gobj);
}

void it_8027429C(Item_GObj* item_gobj, Vec3* arg1)
{
    HSD_GObj* owner_gobj;
    Item* item;
    PAD_STACK(16);

    it_80273B50(item_gobj, arg1);
    item = GET_ITEM(item_gobj);
    owner_gobj = item->owner;
    if (item->xDC8_word.flags.x0) {
        HSD_GObj* x51C_gobj = item->x51C;
        owner_gobj = x51C_gobj;
        item->owner = x51C_gobj;
        item->x51C = NULL;
    }
    it_80273F34(item_gobj, owner_gobj);
}

void it_802742F4(Item_GObj* item_gobj, HSD_GObj* gobj, Fighter_Part ftpart)
{
    Item* item;
    PAD_STACK(8);

    item = item_gobj->user_data;
    lb_8000B804(item_gobj->hsd_obj, item->xC8_joint);
    Item_8026849C(item_gobj);
    if (ftLib_80086960(gobj)) {
        u32 bit_idx = ftLib_80086BE0(gobj);
        item->xDC8_word.flags.xF |= 1 << bit_idx;
        if (!item->xDC8_word.flags.x0) {
            item->owner = gobj;
        } else {
            item->x51C = gobj;
        }
        item->xDC4 = ftpart;
        item->x20_team_id = ftLib_80086EB4(gobj);
        item->xD50_landNum = 0;
        item->xDC8_word.flags.x13 = 1;
        HSD_JObjClearFlagsAll(HSD_JObjGetChild(item_gobj->hsd_obj), 16U);
        it_802756D0(item_gobj);
        it_8026B3A8(item_gobj);
        db_80225DD8(item_gobj, (Fighter_GObj*) gobj);
    }
    if (item->xDD0_flag.b6) {
        item->xDD0_flag.b6 = 0;
        item->xD40 = 0.0f;
        it_80279BBC(item);
    }
    if (item->kind < It_Kind_L_Gun_Ray) { // If a common item
        it_80275158(item_gobj, it_804D6D28->x30_lifetime);
    }
    it_80274F48(item_gobj,
                item->xC4_article_data->x10_modelDesc->x8_bone_attach_id, gobj,
                ftpart);
    it_80274C88(item_gobj);
}

void it_80274484(Item_GObj* item_gobj, HSD_JObj* jobj, f32 scale)
{
    Vec3 sp1C;
    Item* item;
    f32 unused;

    item = GET_ITEM(item_gobj);
    item->scl = scale;
    sp1C.z = item->scl;
    sp1C.y = item->scl;
    sp1C.x = item->scl;
    HSD_JObjSetScale(jobj, &sp1C);
    it_80275534(item_gobj, item->x3C);
    it_80274DFC(item_gobj);
    it_80274E44(item_gobj);
}

void it_80274574(Item_GObj* item_gobj)
{
    it_80274594(item_gobj);
}

inline void HSD_JObjSetScale_2(HSD_JObj* jobj, Vec3* scale)
{
    ((jobj) ? ((void) 0) : __assert("jobj.h", 760, "jobj"));
    jobj->scale = *scale;
    if (!(jobj->flags & (1 << 25))) {
        ftCo_800C6AFC(jobj);
    }
}

void it_80274594(Item_GObj* item_gobj)
{
    Vec3 sp18;
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* item_jobj = GET_JOBJ(item_gobj);
    PAD_STACK(4);

    item->scl *= ftLib_80086A0C(item->owner);
    sp18.z = item->scl;
    sp18.y = item->scl;
    sp18.x = item->scl;
    HSD_JObjSetScale_2(item_jobj, &sp18);
    it_80275534(item_gobj, item->x3C);
    it_80274DFC(item_gobj);
    it_80274E44(item_gobj);
}

int it_80274658(Item_GObj* item_gobj, f32 arg1)
{
    Item* item;
    f32 spin_speed1;
    f32 spin_speed2;
    s32 dir1;
    s32 dir2;

    item = GET_ITEM(item_gobj);
    spin_speed2 = 0.0f;
    spin_speed1 = item->spin_spd;
    if (spin_speed1 != spin_speed2) {
        spin_speed2 = 0.01f * spin_speed1 * (0.017453292f * arg1);
    }
    item->xD3C_spinSpeed = spin_speed2;
    if (item->facing_dir < 0.0f) {
        dir1 = -1;
    } else {
        dir1 = 1;
    }
    if (item->x40_vel.x < 0.0f) {
        dir2 = -1;
    } else {
        dir2 = 1;
    }
    if (dir2 != dir1) {
        item->xD3C_spinSpeed = -item->xD3C_spinSpeed;
    }
    if (item->xDC8_word.flags.x19 != 1) {
        item->xD3C_spinSpeed *= -item->facing_dir;
    }
    return dir2;
}

HSD_JObj* it_802746F8(Item_GObj* item_gobj)
{
    u32 bit_chk;
    s32 var_ctr;
    HSD_JObj* item_jobj2;
    HSD_JObj* item_jobj1;

    item_jobj1 = item_gobj->hsd_obj;
    bit_chk = (((Item*) item_gobj->user_data)
                   ->xC4_article_data->x10_modelDesc->xC_bit_field >>
               6U) &
              3;
    if (bit_chk != 0) {
        for (var_ctr = bit_chk; var_ctr > 0; var_ctr--) {
            if (item_jobj1 == NULL) {
                item_jobj2 = NULL;
            } else {
                item_jobj2 = item_jobj1->child;
            }
            item_jobj1 = item_jobj2;
        }
    }
    return item_jobj1;
}

void it_80274740(Item_GObj* item_gobj)
{
    HSD_JObj* item_jobj;
    Item* item;
    u32 bit_chk;
    s32 var_ctr;
    PAD_STACK(24);

    item = item_gobj->user_data;
    item_jobj = item_gobj->hsd_obj;
    bit_chk = (item->xC4_article_data->x10_modelDesc->xC_bit_field >> 6U) & 3;
    if (bit_chk != 0) {
        for (var_ctr = bit_chk; var_ctr > 0; var_ctr--) {
            if (item_jobj == NULL) {
                item_jobj = NULL;
            } else {
                item_jobj = item_jobj->child;
            }
        }
    }
    item->xD3C_spinSpeed = 0.0f;
    if (item->xDC8_word.flags.x17 == 0) {
        HSD_JObjSetRotationZ(item_jobj, item->xD3C_spinSpeed);
    } else if (item->xDC8_word.flags.x17 == 1) {
        HSD_JObjSetRotationX(item_jobj, item->xD3C_spinSpeed);
    } else {
        HSD_JObjSetRotationY(item_jobj, item->xD3C_spinSpeed);
    }
}

f32 it_80274990(Item_GObj* item_gobj)
{
    u32 bit_chk;
    s32 var_ctr;
    Item* item;
    HSD_JObj* item_jobj;
    PAD_STACK(48);

    item = item_gobj->user_data;
    item_jobj = item_gobj->hsd_obj;
    bit_chk = (item->xC4_article_data->x10_modelDesc->xC_bit_field >> 6U) & 3;
    if (bit_chk != 0) {
        for (var_ctr = bit_chk; var_ctr > 0; var_ctr--) {
            if (item_jobj == NULL) {
                item_jobj = NULL;
            } else {
                item_jobj = item_jobj->child;
            }
        }
    }
    if (item->xDC8_word.flags.x17 == 0) {
        return HSD_JObjGetRotationZ(item_jobj);
    }
    if (item->xDC8_word.flags.x17 == 1) {
        return HSD_JObjGetRotationX(item_jobj);
    }
    return HSD_JObjGetRotationY(item_jobj);
}

void it_80274A64(Item_GObj* item_gobj)
{
    HSD_JObj* item_jobj;
    Item* item;
    u32 bit_chk;
    s32 var_ctr;
    PAD_STACK(24);

    item = item_gobj->user_data;
    item_jobj = item_gobj->hsd_obj;
    bit_chk = (item->xC4_article_data->x10_modelDesc->xC_bit_field >> 6U) & 3;
    if (bit_chk != 0) {
        for (var_ctr = bit_chk; var_ctr > 0; var_ctr--) {
            if (item_jobj == NULL) {
                item_jobj = NULL;
            } else {
                item_jobj = item_jobj->child;
            }
        }
    }
    if (item->xDC8_word.flags.x17 == 0) {
        HSD_JObjAddRotationZ(item_jobj, item->xD3C_spinSpeed);
    } else if (item->xDC8_word.flags.x17 == 1) {
        HSD_JObjAddRotationX(item_jobj, item->xD3C_spinSpeed);
    } else {
        HSD_JObjAddRotationY(item_jobj, item->xD3C_spinSpeed);
    }
}

void it_80274C60(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDC8_word.flags.xC = 0;
}

bool it_80274C78(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    return item->xDC8_word.flags.xC;
}

void it_80274C88(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDD0_flag.b0 = 0;
    item->xDAA_flag.b3 = 0;
}

void it_80274CAC(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDD0_flag.b0 = 1;
    if (db_ShowEnemyStompRange() != 0) {
        item->xDAA_flag.b3 = 1;
    }
}

void it_80274D04(Item_GObj* item_gobj, struct lb_80014638_arg1_t* arg1)
{
    Vec3 sp20;
    Vec3 sp14;
    PAD_STACK(4);

    it_8026BB88(item_gobj, &sp20);
    it_8026BBCC(item_gobj, &sp14);
    arg1->unk_x = sp20.x - sp14.x;
    arg1->unk_y = sp20.y - sp14.y;
}

void it_80274D6C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32 right_x = ip->x378_itemColl.ecb.right.x;
    f32 right_y = ip->x378_itemColl.ecb.right.y;
    f32 left_x = ip->x378_itemColl.ecb.left.x;
    f32 top_y = ip->x378_itemColl.ecb.top.y;

    ip->xB54.x8.y = right_x + ip->pos.x;
    ip->xB54.x8.x = left_x + ip->pos.x;
    ip->xB54.x8.z = right_y + ip->pos.y + top_y;
}

void it_80274DAC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xB54.unk_x = 0.0f;
    ip->xB54.unk_y = 0.0f;
    {
        Item* ip = GET_ITEM(gobj);
        CollData* cd = &ip->x378_itemColl;
        f32 right_x = cd->ecb.right.x;
        f32 right_y = cd->ecb.right.y;
        f32 left_x = cd->ecb.left.x;
        f32 top_y = cd->ecb.top.y;
        ip->xB54.x8.y = right_x + ip->pos.x;
        ip->xB54.x8.x = left_x + ip->pos.x;
        ip->xB54.x8.z = right_y + ip->pos.y + top_y;
    }
}

void it_80274DFC(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xBCC_unk.x *= item->scl;
    item->xBCC_unk.y *= item->scl;
    item->xBD4_grabRange.x *= item->scl;
    item->xBD4_grabRange.y *= item->scl;
}

void it_80274E44(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xBEC.top *= item->scl;
    item->xBEC.bottom *= item->scl;
    item->xBEC.right *= item->scl;
    item->xBEC.left *= item->scl;
    item->xBDC.top *= item->scl;
    item->xBDC.bottom *= item->scl;
    item->xBDC.right *= item->scl;
    item->xBDC.left *= item->scl;
}

void it_80274ECC(Item_GObj* item_gobj, bool arg1)
{
    ((Item*) item_gobj->user_data)->xD09 = arg1;
}

void it_80274ED8(void)
{
    it_804D6D0C++;
}

void it_80274EE8(void)
{
    it_804D6D08++;
}

void it_80274EF8(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDC8_word.flags.x2 = 0;
}

void it_80274F10(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDC8_word.flags.x2 = 1;
}

void it_80274F28(Item* item, s8 arg1, HSD_GObjEvent arg2,
                 HSD_GObjInteraction arg3)
{
    item->xDD0_flag.b5 = 1;
    item->xD08 = arg1;
    item->grab_dealt = arg2;
    item->grabbed_for_victim = arg3;
}

inline HSD_JObj* get_bone_by_id(Item_GObj* item_gobj, int bone_id)
{
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* jobj = GET_JOBJ(item_gobj);
    if (item->xC4_article_data->x10_modelDesc->x4_bone_count) {
        jobj = item->xBBC_dynamicBoneTable->bones[bone_id];
    } else if (bone_id != 0) {
        while (bone_id-- > 0) {
            if (jobj == NULL) {
                jobj = NULL;
            } else {
                jobj = jobj->child;
            }
        }
    }
    return jobj;
}

void it_80274F48(Item_GObj* item_gobj, s32 bone_id, HSD_GObj* arg2_gobj,
                 Fighter_Part part_idx)
{
    u8 _[8];
    HSD_JObj* jobj = get_bone_by_id(item_gobj, bone_id);
    lb_8000C2F8(jobj, ftLib_80086630(arg2_gobj, part_idx));
}

void it_80274FDC(Item_GObj* item_gobj, s32 bone_id, Fighter_GObj* arg2_gobj,
                 Fighter_Part part_idx)
{
    u8 _[8];
    HSD_JObj* jobj = get_bone_by_id(item_gobj, bone_id);
    lb_8000C1C0(jobj, ftLib_80086630(arg2_gobj, part_idx));
}

void it_80275070(Item_GObj* item_gobj, s32 bone_id)
{
    u8 _[8];
    HSD_JObj* jobj = get_bone_by_id(item_gobj, bone_id);
    lb_8000C390(jobj);
}

bool it_802750E8(Item_GObj* item_gobj, s32 mask)
{
    Item* item = GET_ITEM(item_gobj);
    return item->xDC0 & mask;
}

void it_802750F8(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCC_flag.b3 = 0;
    Item_802697D4(item_gobj);
    Item_80269978(item_gobj);
    item->xDCC_flag.b3 = 1;
}

/// Set both life timers on the item
void it_80275158(Item_GObj* item_gobj, f32 lifetime)
{
    Item* item;

    item = GET_ITEM(item_gobj);
    item->xD44_lifeTimer = lifetime;
    item->xD48_halfLifeTimer = lifetime * it_804D6D28->x4C_float;
}

void it_80275174(Item_GObj* item_gobj, f32 lifetime)
{
    ((Item*) item_gobj->user_data)->xD48_halfLifeTimer =
        lifetime * it_804D6D28->x4C_float;
}

void it_8027518C(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xD44_lifeTimer = it_804D6D28->xF8;
    item->xDCF_flag.b2 = 1;
    item->xDD1_flag.b0 = 1;
    it_8026BDB4(item_gobj);
}

bool it_802751D8(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xD44_lifeTimer--;
    if (item->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

void it_80275210(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDC8_word.flags.x1C = 1;
}

void it_80275228(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDC8_word.flags.x1C = 0;
}

void it_80275240(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDC8_word.flags.x1E = 0;
}

void it_80275258(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDD0_flag.b4 = 0;
}

void it_80275270(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDD0_flag.b4 = 1;
}

void it_80275288(Item_GObj* item_gobj, s32 arg1, s32 arg2)
{
    Item* item = GET_ITEM(item_gobj);
    int val = arg2 + HSD_Randi(arg1);
    Item_8026AE84(item, val, 127, 64);
}

void it_802752D8(Item_GObj* item_gobj, s32 arg1, s32 arg2)
{
    Item* item = GET_ITEM(item_gobj);
    int val = arg2 + HSD_Randi(arg1);
    Item_8026AFA0(item, val, 127, 64);
}

void it_80275328(HSD_GObj* gobj, ItemLink* arg1)
{
    arg1->prev = NULL;
    arg1->next = NULL;
    arg1->vel.z = 0.0f;
    arg1->vel.y = 0.0f;
    arg1->vel.x = 0.0f;
    arg1->pos.z = 0.0f;
    arg1->pos.y = 0.0f;
    arg1->pos.x = 0.0f;
    arg1->x20.z = 0.0f;
    arg1->x20.y = 0.0f;
    arg1->x20.x = 0.0f;
    arg1->x2C_b0 = 0;
    arg1->x2C_b1 = 0;
    arg1->x2C_b2 = 0;
    arg1->x1CC = 0;
    arg1->gobj = gobj;
    arg1->jobj = NULL;
}

void it_80275390(Item_GObj* item_gobj)
{
    ((Item*) item_gobj->user_data)->owner = NULL;
    it_8026B3A8(item_gobj);
}

void it_802753BC(Item_GObj* item_gobj, s16 arg1)
{
    Item* item;

    item = item_gobj->user_data;
    item->xC94 = 0;
    item->xC9C = arg1;
    item->xCA0 = 0;
    item->xCA4 = 0;
}
