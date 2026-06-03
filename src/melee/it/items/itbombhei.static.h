#ifndef ITBOMBHEI_STATIC_H
#define ITBOMBHEI_STATIC_H

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itbombhei.h"

static inline HSD_JObj* itGetDynamicBone(Item_GObj* igp, u32 bone_id)
{
    return GET_ITEM(igp)->xBBC_dynamicBoneTable->bones[bone_id];
}

static inline void itBombhei_UpdateStatePreserveBone(Item_GObj* igp,
                                                     int anim_id, int flags)
{
    Item* ip = GET_ITEM(igp);
    HSD_JObj* jobj = ip->xBBC_dynamicBoneTable->bones[0xB];
    f32 x;
    f32 y;

    y = HSD_JObjGetTranslationY(jobj);
    x = HSD_JObjGetRotationX(jobj);
    Item_80268E5C((HSD_GObj*) igp, anim_id, flags);
    HSD_JObjSetTranslateY(jobj, y);
    HSD_JObjSetRotationX(jobj, x);
}

static inline void
itBombhei_UpdateStatePreserveBoneFake(Item_GObj* igp, int anim_id, int flags)
{
    Item* ip = GET_ITEM(igp);
    HSD_JObj* jobj = ip->xBBC_dynamicBoneTable->bones[0xB];
    f32 x;
    f32 y;

    y = HSD_JObjGetTranslationY(jobj);
    x = HSD_JObjGetRotationX(jobj);
    Item_80268E5C((HSD_GObj*) igp, anim_id, flags);
    HSD_JObjSetTranslateYWithMtxDirty(jobj, y);
    HSD_JObjSetRotationXWithMtxDirty(jobj, x);
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
            itBombhei_UpdateStatePreserveBoneFake(igp, 7, ITEM_ANIM_UPDATE);
        } else {
            ip->x5D0_animFrameSpeed = 1.0f;
            itBombhei_UpdateStatePreserveBoneFake(igp, 8, ITEM_UNK_0x1);
        }
    }
}

#endif
