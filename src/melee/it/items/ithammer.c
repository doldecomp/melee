#include <platform.h>

#include "ithammer.h"

#include "ithammerhead.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"

#include <dolphin/mtx.h>
#include <baselib/random.h>

typedef struct itHammerData {
    u32 x0;
    u32 x4;
    f32 x8;
} itHammerData;

/* 293FF4 */ static bool itHammer_UnkMotion0_Anim(HSD_GObj* gobj);
/* 293FFC */ static void itHammer_UnkMotion0_Phys(HSD_GObj* gobj);
/* 294000 */ static bool itHammer_UnkMotion0_Coll(HSD_GObj* gobj);
/* 29402C */ static void it_8029402C(HSD_GObj* gobj);
/* 294080 */ static bool itHammer_UnkMotion4_Anim(Item_GObj* gobj);
/* 294088 */ static void itHammer_UnkMotion1_Phys(HSD_GObj* gobj);
/* 2940B8 */ static bool itHammer_UnkMotion1_Coll(Item_GObj* gobj);
/* 294170 */ static bool itHammer_UnkMotion3_Anim(Item_GObj* gobj);
/* 2941A4 */ static void it_802941A4(HSD_GObj* gobj);
/* 29424C */ static void itHammer_UnkMotion4_Phys(HSD_GObj* gobj);
/* 29427C */ static bool itHammer_UnkMotion4_Coll(HSD_GObj* gobj);
/* 294304 */ static bool itHammer_UnkMotion5_Anim(Item_GObj* gobj);
/* 29430C */ static void itHammer_UnkMotion5_Phys(HSD_GObj* gobj);
/* 294310 */ static bool itHammer_UnkMotion5_Coll(Item_GObj* gobj);

ItemStateTable it_803F6150[] = {
    { -1, itHammer_UnkMotion0_Anim, itHammer_UnkMotion0_Phys, itHammer_UnkMotion0_Coll },
    { -1, itHammer_UnkMotion4_Anim, itHammer_UnkMotion1_Phys, itHammer_UnkMotion1_Coll },
    { 0, itHammer_UnkMotion3_Anim, NULL, NULL },
    { 1, itHammer_UnkMotion3_Anim, NULL, NULL },
    { -1, itHammer_UnkMotion4_Anim, itHammer_UnkMotion4_Phys, itHammer_UnkMotion4_Coll },
    { -1, itHammer_UnkMotion5_Anim, itHammer_UnkMotion5_Phys, itHammer_UnkMotion5_Coll },
};

static inline void thing(void* gobj)
{
    Item* it = GET_ITEM(gobj);
    if (it->xD4C <= 0) {
        it_80272A3C(it_80272CC0((Item_GObj*) gobj, 3));
    }
}

void it_80293D94(Item_GObj* gobj)
{
    Item* item = GET_ITEM((HSD_GObj*) gobj);
    if (!item->xDC8_word.flags.xB && item->xDC8_word.flags.xA) {
        it_8026BC14(gobj);
    }
}

int it_80293DCC(Item_GObj* gobj)
{
    Item* item = GET_ITEM((HSD_GObj*) gobj);
    Article* article = item->xC4_article_data;
    itHammerData* temp_r31 = article->x4_specialAttributes;
    if (HSD_Randf() < temp_r31->x8 / 100.0f) {
        int rng = HSD_Randi(temp_r31->x4 - temp_r31->x0);
        return rng + temp_r31->x0;
    }
    return 0;
}

void it_80293E34(Item_GObj* gobj)
{
    Vec3 sp30;
    Vec3 sp24;
    Vec3 result;
    Item* temp_r31;
    s32 temp_r3;
    float asd;

    temp_r31 = GET_ITEM((HSD_GObj*) gobj);
    temp_r3 = temp_r31->xD4C;
    if (temp_r3 > 0) {
        temp_r31->xD4C = temp_r3 - 1;
        lb_8000B1CC(it_80272CC0(gobj, 3), NULL, &sp30);
        lb_8000B1CC(it_80272CC0(gobj, 1), NULL, &sp24);
        result.x = sp30.x - sp24.x;
        result.y = sp30.y - sp24.y;
        result.z = 0.0f;
        lbVector_Normalize(&result);
        // if (result.x < 0.0f) {
        //     var_r0 = -1;
        // } else {
        //     var_r0 = 1;
        // }
        // asd = var_r0;
        asd = result.x < 0.0f ? -1 : 1;
        // if (result.x < 0.0f) {
        //     result.x = -result.x;
        // }
        result.x = result.x < 0.0f ? -result.x : result.x;
        it_80299C48(temp_r31->owner, &sp30, &result, asd);
    }
    thing(gobj);
}

void it_3F14_Logic28_Spawned(HSD_GObj* gobj)
{
    GET_ITEM(gobj)->xD4C = 1;
    it_8029402C(gobj);
}

void it_80293F84(Item_GObj* gobj)
{
    Item* temp_r4 = GET_ITEM((HSD_GObj*) gobj);
    temp_r4->x40_vel.z = 0.0f;
    temp_r4->x40_vel.y = 0.0f;
    temp_r4->x40_vel.x = 0.0f;
    it_8026B390(gobj);
    Item_80268E5C((HSD_GObj*) gobj, 0, ITEM_ANIM_UPDATE);
    thing(gobj);
}

bool itHammer_UnkMotion0_Anim(HSD_GObj* gobj)
{
    return 0;
}

void itHammer_UnkMotion0_Phys(HSD_GObj* gobj) {}

bool itHammer_UnkMotion0_Coll(HSD_GObj* gobj)
{
    it_8026D62C(gobj, it_8029402C);
    return 0;
}

void it_8029402C(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    thing(gobj);
}

bool itHammer_UnkMotion4_Anim(Item_GObj* gobj)
{
    return 0;
}

void itHammer_UnkMotion1_Phys(HSD_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    ItemAttr* temp_r4 = it->xCC_item_attr;
    it_80272860(gobj, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
}

bool itHammer_UnkMotion1_Coll(HSD_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    if (it->xD4C != 0) {
        it_8026E15C(gobj, it_80293F84);
        return false;
    }
    return it_8026DF34(gobj);
}

void it_3F14_Logic28_PickedUp(HSD_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    item->entered_hitlag = (void*) (Item_GObj*) it_80293D94;
    thing(gobj);
    it_802725D4(gobj);
}

bool itHammer_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    if (it->xD4C == 0) {
        it_802941A4(gobj);
    }
    return 0;
}

void it_802941A4(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    thing(gobj);
}

void it_3F14_Logic28_Dropped(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 1, 6);
    thing(gobj);
}

void itHammer_UnkMotion4_Phys(HSD_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    ItemAttr* temp_r4 = it->xCC_item_attr;
    it_80272860(gobj, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
}

bool itHammer_UnkMotion4_Coll(HSD_GObj* gobj)
{
    if (it_8026DA08(gobj) != 0) {
        return 1;
    }
    return 0;
}

void it_3F14_Logic28_EnteredAir(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    thing(gobj);
}

bool itHammer_UnkMotion5_Anim(Item_GObj* gobj)
{
    return 0;
}

void itHammer_UnkMotion5_Phys(HSD_GObj* gobj) {}

bool itHammer_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_80293F84, it_8029402C);
    return 0;
}

void it_3F14_Logic28_EvtUnk(Item_GObj* igobj, HSD_GObj* gobj)
{
    it_8026B894(igobj, gobj);
}
