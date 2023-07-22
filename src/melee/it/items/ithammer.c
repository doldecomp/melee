#include "ithammer.h"

#include <melee/db/db_2253.h>
#include <melee/it/it_266F.h>
#include <melee/it/it_26B1.h>
#include <melee/it/item.h>
#include <melee/lb/lbrefract.h>
#include <melee/lb/lbvector.h>
#include <MSL/math.h>


static inline void thing(void* arg0) {
    Item* it = GET_ITEM(arg0);
    if (it->xD4C <= 0) {
        it_80272A3C(it_80272CC0((Item_GObj* ) arg0, 3));
    }
}

void it_80293D94(Item_GObj* arg0) {
    Item* item = GET_ITEM((HSD_GObj*)arg0);
    if (!item->xDC8_word.flags.xB && item->xDC8_word.flags.xA) {
        it_8026BC14(arg0);
    }
}

s32 it_80293DCC(Item_GObj* arg0) {
    Item* item = GET_ITEM((HSD_GObj*)arg0);
    Article* article = item->xC4_article_data;
    ItemCommonData *temp_r31 = article->x4_specialAttributes;
    if (HSD_Randf() < temp_r31->x8 / 100.0f) {
        int rng = HSD_Randi(temp_r31->x4 - temp_r31->x0);
        return rng + temp_r31->x0;
    }
    return 0;
}

void it_80293E34(Item_GObj* arg0) {
    Vec3 sp30;
    Vec3 sp24;
    Vec3 result;
    Item* temp_r31;
    s32 temp_r3;
    float asd;

    temp_r31 = GET_ITEM((HSD_GObj*) arg0);
    temp_r3 = temp_r31->xD4C;
    if (temp_r3 > 0) {
        temp_r31->xD4C = temp_r3 - 1;
        lb_8000B1CC(it_80272CC0(arg0, 3), NULL, &sp30);
        lb_8000B1CC(it_80272CC0(arg0, 1), NULL, &sp24);
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
    thing(arg0);
}

void it_80293F58(void* arg0) {
    GET_ITEM(arg0)->xD4C = 1;
    it_8029402C(arg0);
}

void it_80293F84(Item_GObj* arg0) {
    Item* temp_r4 = GET_ITEM((HSD_GObj*)arg0);
    temp_r4->x40_vel.z = 0.0f;
    temp_r4->x40_vel.y = 0.0f;
    temp_r4->x40_vel.x = 0.0f;
    it_8026B390(arg0);
    Item_80268E5C((HSD_GObj* ) arg0, 0, ITEM_ANIM_UPDATE);
    thing(arg0);
}

int it_80293FF4(void) {
    return 0;
}

void it_80293FFC(void) {

}

HSD_GObj* it_80294000(void* arg0) {
    it_8026D62C(arg0, it_8029402C);
    return 0;
}

void it_8029402C(HSD_GObj* arg0) {
    Item_80268E5C(arg0, 1, ITEM_ANIM_UPDATE);
    thing(arg0);
}

int it_80294080(void) {
    return 0;
}

void it_80294088(void* arg0) {
    Item* it = GET_ITEM(arg0);
    ItemAttr* temp_r4 = it->xCC_item_attr;
    it_80272860(arg0, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
}

s32 it_802940B8(void* arg0) {
    Item* it = GET_ITEM(arg0);
    if (it->xD4C != 0) {
        it_8026E15C(arg0, it_80293F84);
        return 0;
    }
    return it_8026DF34();
}

void it_802940FC(HSD_GObj* arg0) {
    Item *item = GET_ITEM(arg0);
    Item_80268E5C(arg0, 2, ITEM_ANIM_UPDATE);
    item->entered_hitlag = (void*)(Item_GObj*) it_80293D94;
    thing(arg0);
    it_802725D4(arg0);
}

int it_80294170(HSD_GObj* arg0) {
    Item* it = GET_ITEM(arg0);
    if (it->xD4C == 0) {
        it_802941A4(arg0);
    }
    return 0;
}

void it_802941A4(HSD_GObj* arg0) {
    Item_80268E5C(arg0, 3, ITEM_ANIM_UPDATE);
    thing(arg0);
}

void it_802941F8(HSD_GObj* arg0) {
    Item_80268E5C(arg0, 1, 6);
    thing(arg0);
}

void it_8029424C(void* arg0) {
    Item* it = GET_ITEM(arg0);
    ItemAttr* temp_r4 = it->xCC_item_attr;
    it_80272860(arg0, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
}

int it_8029427C(void) {
    if (it_8026DA08() != 0) {
        return 1;
    }
    return 0;
}

void it_802942B0(HSD_GObj* arg0) {
    Item_80268E5C(arg0, 5, ITEM_ANIM_UPDATE);
    thing(arg0);
}

int it_80294304(void) {
    return 0;
}

void it_8029430C(void) {

}

int it_80294310(HSD_GObj* arg0) {
    it_8026E8C4(arg0, it_80293F84, it_8029402C);
    return 0;
}

void it_80294344(Item_GObj* arg0, HSD_GObj* arg1) {
    it_8026B894(arg0, arg1);
}
