#include "ithammer.h"

#include <melee/db/db_2253.h>
#include <melee/it/it_266F.h>
#include <melee/it/it_26B1.h>
#include <melee/it/item.h>
#include <melee/lb/lbrefract.h>
#include <melee/lb/lbvector.h>
#include <MSL/math.h>

void it_80293D94(Item_GObj* arg0) {
    Item* item = GET_ITEM((HSD_GObj*)arg0);
    if (!item->xDC8_word.flags.xB && item->xDC8_word.flags.xA) {
        it_8026BC14(arg0);
    }
}

s32 it_80293DCC(void* arg0) {
    Item *item = GET_ITEM(arg0);
    float *temp_r31;

    temp_r31 = &item->xC40;
    if (HSD_Randf() < (temp_r31[24] / 100.0f)) {
        //return HSD_Randi(temp_r31->unk4 - temp_r31->unk0) + temp_r31->unk0;
    }
    return 0;
}

void it_80293E34(Item_GObj* arg0) {
    Vec3 sp30;
    Vec3 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    Item* temp_r31;
    f32 var_f2;
    s32 temp_r3;
    s32 var_r0;

    temp_r31 = GET_ITEM((HSD_GObj*) arg0);
    temp_r3 = temp_r31->xD4C;
    if (temp_r3 > 0) {
        temp_r31->xD4C = temp_r3 - 1;
        lb_8000B1CC(it_80272CC0(arg0, 3), NULL, &sp30);
        lb_8000B1CC(it_80272CC0(arg0, 1), NULL, &sp24);
        sp18 = sp30.x - sp24.x;
        sp1C = sp30.y - sp24.y;
        sp20 = 0.0f;
        lbVector_Normalize((Vec3* ) &sp18);
        var_f2 = sp18;
        if (var_f2 < 0.0f) {
            var_r0 = -1;
        } else {
            var_r0 = 1;
        }
        if (var_f2 < 0.0f) {
            var_f2 = -var_f2;
        }
        sp18 = var_f2;
        it_80299C48(temp_r31->owner, &sp30, &sp18, (f32) var_r0);
    }
    if ((s32) arg0->user_data->xD4C <= 0) {
        it_80272A3C(it_80272CC0(arg0, 3));
    }
}

void it_80293F58(void* arg0) {
    HSD_GObj* temp_r4;

    GET_ITEM(arg0)->xD4C = 1;
    it_8029402C(temp_r4);
}

void it_80293F84(Item_GObj* arg0) {
    Item* temp_r4;

    temp_r4 = arg0->user_data;
    temp_r4->x40_vel.z = 0.0f;
    temp_r4->x40_vel.y = 0.0f;
    temp_r4->x40_vel.x = 0.0f;
    it_8026B390(arg0);
    Item_80268E5C((HSD_GObj* ) arg0, 0, ITEM_ANIM_UPDATE);
    if ((s32) arg0->user_data->xD4C <= 0) {
        it_80272A3C(it_80272CC0(arg0, 3));
    }
}

int it_80293FF4(void) {
    return 0;
}

void it_80293FFC(void) {

}

int it_80294000(void) {
    it_8026D62C(it_8029402C);
    return 0;
}

void it_8029402C(HSD_GObj* arg0) {
    Item_80268E5C(arg0, 1, ITEM_ANIM_UPDATE);
    if ((s32) GET_ITEM((HSD_GObj*) arg0)->xD4C <= 0) {
        it_80272A3C(it_80272CC0((Item_GObj* ) arg0, 3));
    }
}

int it_80294080(void) {
    return 0;
}

void it_80294088(void* arg0) {
    void* temp_r4;

    // temp_r4 = arg0->unk2C->unkCC;
    // it_80272860(temp_r4, temp_r4->unk10, temp_r4->unk14);
}

s32 it_802940B8(void* arg0) {
    if ((s32) GET_ITEM((HSD_GObj*) arg0)->xD4C != 0) {
        it_8026E15C(it_80293F84);
        return 0;
    }
    return it_8026DF34();
}

void it_802940FC(HSD_GObj* arg0) {

    Item *item = GET_ITEM(arg0);
    Item_80268E5C(arg0, 2, ITEM_ANIM_UPDATE);
    // item->xD28 = it_80293D94;
    if ((s32) item->xD4C <= 0) {
        it_80272A3C(it_80272CC0((Item_GObj* ) arg0, 3));
    }
    it_802725D4(arg0);
}

int it_80294170(void* arg0) {
    if ((s32) GET_ITEM((HSD_GObj*) arg0)->xD4C == 0) {
        it_802941A4((HSD_GObj*) arg0);
    }
    return 0;
}

void it_802941A4(HSD_GObj* arg0) {
    Item_80268E5C(arg0, 3, ITEM_ANIM_UPDATE);
    if ((s32) GET_ITEM(arg0)->xD4C <= 0) {
        it_80272A3C(it_80272CC0((Item_GObj* ) arg0, 3));
    }
}

void it_802941F8(HSD_GObj* arg0) {
    Item_80268E5C(arg0, 1, 6);
    if ((s32) GET_ITEM(arg0)->xD4C <= 0) {
        it_80272A3C(it_80272CC0((Item_GObj* ) arg0, 3));
    }
}

void it_8029424C(void* arg0) {
    void* temp_r4;

    // temp_r4 = GET_ITEM((HSD_GObj*) arg0)->xCC;
    // it_80272860(temp_r4, temp_r4->unk10, temp_r4->unk14);
}

int it_8029427C(void) {
    if (it_8026DA08() != 0) {
        return 1;
    }
    return 0;
}

void it_802942B0(HSD_GObj* arg0) {
    Item_80268E5C(arg0, 5, ITEM_ANIM_UPDATE);
    if ((s32) GET_ITEM(arg0)->xD4C <= 0) {
        it_80272A3C(it_80272CC0((Item_GObj* ) arg0, 3));
    }
}

int it_80294304(void) {
    return 0;
}

void it_8029430C(void) {

}

int it_80294310(void) {
    it_8026E8C4(it_80293F84, it_8029402C);
    return 0;
}

void it_80294344(Item_GObj* arg0, HSD_GObj* arg1) {
    it_8026B894(arg0, arg1);
}
/* Warning: struct HSD_Spline is not defined (only forward-declared) */
/* Warning: struct _HSD_Rvalue is not defined (only forward-declared) */
/* Warning: struct _HSD_VtxDescList is not defined (only forward-declared) */
/* Warning: struct _HSD_RObjDesc is not defined (only forward-declared) */
/* Warning: struct _HSD_ExpDesc is not defined (only forward-declared) */
/* Warning: struct _HSD_ByteCodeExpDesc is not defined (only forward-declared) */
/* Warning: struct _HSD_IKHintDesc is not defined (only forward-declared) */

