#ifndef ITBOMBHEI_STATIC_H
#define ITBOMBHEI_STATIC_H

#include "it/forward.h"
#include "ft/ft_0C31.h"
#include "it/inlines.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itbombhei.h"

static inline void fake_HSD_JObjSetTranslateY(HSD_JObj* jobj, f32 y)
{
    HSD_ASSERT(947, jobj);
    jobj->translate.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

static inline void fake_HSD_JObjSetRotationX(HSD_JObj* jobj, f32 x)
{
    HSD_ASSERT(639, jobj);
    HSD_ASSERT(640, !(jobj->flags & JOBJ_USE_QUATERNION));
    jobj->rotate.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

static inline HSD_JObj* itGetDynamicBone(Item_GObj* igp, u32 bone_id)
{
    return GET_ITEM(igp)->xBBC_dynamicBoneTable->bones[bone_id];
}

static inline void itBombhei_UpdateStatePreserveBone(Item_GObj* igp, int anim_id)
{
    Item* ip = GET_ITEM(igp);
    HSD_JObj* jobj = ip->xBBC_dynamicBoneTable->bones[0xB];
    f32 x;
    f32 y;

    y = HSD_JObjGetTranslationY(jobj);
    x = HSD_JObjGetRotationX(jobj);
    Item_80268E5C((HSD_GObj*) igp, anim_id, ITEM_ANIM_UPDATE);
    HSD_JObjSetTranslateY(jobj, y);
    HSD_JObjSetRotationX(jobj, x);
}

static inline void itBombhei_UpdateStatePreserveBone2(Item_GObj* igp, int anim_id)
{
    Item* ip = GET_ITEM(igp);
    HSD_JObj* jobj = ip->xBBC_dynamicBoneTable->bones[0xB];
    f32 x;
    f32 y;

    y = HSD_JObjGetTranslationY(jobj);
    x = HSD_JObjGetRotationX(jobj);
    Item_80268E5C((HSD_GObj*) igp, anim_id, ITEM_UNK_0x1);
    HSD_JObjSetTranslateY(jobj, y);
    HSD_JObjSetRotationX(jobj, x);
}

static inline void itBombhei_UpdateStatePreserveBone3(Item_GObj* igp, int anim_id)
{
    Item* ip = GET_ITEM(igp);
    HSD_JObj* jobj = ip->xBBC_dynamicBoneTable->bones[0xB];
    f32 x;
    f32 y;

    y = HSD_JObjGetTranslationY(jobj);
    x = HSD_JObjGetRotationX(jobj);
    Item_80268E5C((HSD_GObj*) igp, anim_id, ITEM_ANIM_UPDATE);
    fake_HSD_JObjSetTranslateY(jobj, y);
    fake_HSD_JObjSetRotationX(jobj, x);
}

static inline void itBombhei_UpdateStatePreserveBone4(Item_GObj* igp, int anim_id)
{
    Item* ip = GET_ITEM(igp);
    HSD_JObj* jobj = ip->xBBC_dynamicBoneTable->bones[0xB];
    f32 x;
    f32 y;

    y = HSD_JObjGetTranslationY(jobj);
    x = HSD_JObjGetRotationX(jobj);
    Item_80268E5C((HSD_GObj*) igp, anim_id, ITEM_UNK_0x1);
    fake_HSD_JObjSetTranslateY(jobj, y);
    fake_HSD_JObjSetRotationX(jobj, x);
}

static inline void inline1_UnkMotion0_Anim(Item_GObj* igp)
{
    Item* ip;

    ip = GET_ITEM(igp);

    if (ip->xDD4_itemVar.bombhei.xDD4 <= 0) {
        it_8027E978(igp);
    } else {
        ip->xDD4_itemVar.bombhei.xDD4 = ip->xDD4_itemVar.bombhei.xDD4 - 1;
        ip->xDD4_itemVar.bombhei.xDEC -= 1.0f;
    }
}

static inline void inline2_UnkMotion0_Anim(Item_GObj* igp)
{
    Item* ip;
    HSD_JObj* jobj;

    ip = GET_ITEM(igp);
    jobj = ip->xBBC_dynamicBoneTable->bones[0xB];
    HSD_JObjAddTranslationY(jobj, ip->xDD4_itemVar.bombhei.xDF8);
    HSD_JObjAddRotationX(jobj, ip->xDD4_itemVar.bombhei.xDFC);
}

static inline void inline_UnkMotion8_Anim(Item_GObj* igp)
{
    if (it_80272C6C(igp) == 0) {
        Item* ip = GET_ITEM(igp);
        itBombHeiAttributes* ap = ip->xC4_article_data->x4_specialAttributes;

        ip->xDC8_word.flags.x19 = 1;
        ip->xDC8_word.flags.x17 = 1;

        if (ip->xDD4_itemVar.bombhei.xDE0 == 0) {
            ip->x5D0_animFrameSpeed = ap->x0;
            itBombhei_UpdateStatePreserveBone3(igp, 7);
        } else {
            ip->x5D0_animFrameSpeed = 1.0f;
            itBombhei_UpdateStatePreserveBone4(igp, 8);
        }
    }
}

#endif
