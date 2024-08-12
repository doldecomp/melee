#include <melee/ft/chara/ftFox/forward.h>

#include "itfoxblaster.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_0BF0.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/itCharItems.h"
#include "it/types.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <melee/ft/chara/ftFox/ftFx_SpecialN.h>
#include <melee/ft/chara/ftKirby/ftKb_Init.h>
#include <melee/it/item.h>
#include <melee/lb/lbrefract.h>

void it_802ADF10(HSD_GObj* arg0); /* static */
int it_802AEBCC(HSD_GObj* arg0);  /* static */
void it_802AEED4(HSD_GObj* arg0); /* static */
int it_802AEF08(HSD_GObj* arg0);  /* static */
int it_802AEF10(HSD_GObj* arg0);  /* static */
void it_802AEFB8(HSD_GObj* arg0); /* static */
int it_802AEFBC(HSD_GObj* arg0);  /* static */
int it_802AF064(HSD_GObj* arg0);  /* static */
void it_802AF178(HSD_GObj* arg0); /* static */
int it_802AF17C(HSD_GObj* arg0);  /* static */

ItemStateTable it_803F6CA8[11] = {
    { 0, it_802AEBCC, it_802AEED4, it_802AEF08 },
    { 1, it_802AEBCC, it_802AEED4, it_802AEF08 },
    { 2, it_802AEBCC, it_802AEED4, it_802AEF08 },
    { 3, it_802AEBCC, it_802AEED4, it_802AEF08 },
    { 4, it_802AEBCC, it_802AEED4, it_802AEF08 },
    { 5, it_802AEBCC, it_802AEED4, it_802AEF08 },
    { 6, it_802AEBCC, it_802AEED4, it_802AEF08 },
    { 7, it_802AEBCC, it_802AEED4, it_802AEF08 },
    { 8, it_802AEBCC, it_802AEED4, it_802AEF08 },
    { -1, it_802AEF10, it_802AEFB8, it_802AEFBC },
    { -1, it_802AF064, it_802AF178, it_802AF17C }
};
f32 it_803F6D58[14] = {
    0.0,    -0.51,  -1.02,  -1.53,  -1.39,  -1.251, -1.112,
    -0.973, -0.834, -0.695, -0.556, -0.417, -0.278, -0.139
}; // used for jobj->translate.z calc for xDD4
f32 it_803F6D90[14] = {
    0.5, 0.5, 1.75, 3.0, 2.375, 1.75, 1.125, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5
}; // used in jobj->scale.y/z calcs for xDD4
f32 it_803F6DC8[14] = {
    0.0, -42.0, -20.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
}; // used for jobj->rotate.x calc for xDD4
static f32 it_803F6E28[5] = {
    -0.425f, -0.595f, -0.765f, -0.935f, -0.85f
}; // used in jobj->translate.y calc for xDD8
static s32 it_803F6E3C[0xB] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xA };
static s32 it_803F6E68[0xC] = { 0, 9, 9, 3, 9, 9, 6, 7, 8, 9, 0xA, 0 };
// static s8 it_804D5428[7] = "jobj.h";
// static s8 it_804D5430[5] = "jobj";
f32 it_804DCF38 =0x00000000;

static inline HSD_JObj* jobj_child(HSD_JObj* node)
{
    if (node == NULL) {
        return NULL;
    }
    return node->child;
}

void it_802ADDD0(Item_GObj* item_gobj, s32 arg1)
{
    Item* item;
    HSD_JObj* item_jobj;
    HSD_JObj* child_jobj;

    if (item_gobj == NULL) {
        return;
    }

    item = GET_ITEM((HSD_GObj*) item_gobj);

    if (item == NULL) {
        return;
    }

    item_jobj = GET_JOBJ((HSD_GObj*) item_gobj);
    child_jobj = jobj_child(item_jobj);
    if (item->xDD4_itemVar.foxblaster.xE78 != arg1) {
        item->xDD4_itemVar.foxblaster.xE78 = arg1;
        if (arg1 == 2) {
            switch (item->kind) {
            case It_Kind_Kirby_FoxBlaster:
            case It_Kind_Fox_Blaster:
                Item_8026AE84(item, 0x1AE14, 0x7F, 0x40);
                break;
            case It_Kind_Kirby_FalcoBlaster:
            case It_Kind_Falco_Blaster:
                Item_8026AE84(item, 0x18700, 0x7F, 0x40);
                break;
            }
        }
    }
    switch (item->xDD4_itemVar.foxblaster.xE78) {
    case 0:
    case 2:
        HSD_JObjSetFlagsAll(child_jobj, 0x10);
        return;
    case 1:
        HSD_JObjClearFlagsAll(child_jobj, 0x10);
        break;
    }
}

void it_802ADEF0(HSD_GObj* item_gobj)
{
    it_802ADF10(item_gobj);
}

// void it_802ADF10(void* arg0) {
void it_802ADF10(HSD_GObj* item_gobj)
{
    Vec3 ft_cur_pos;
    Vec3 ft_hold_joint_pos;
    Vec3 it_hold_joint_pos;
    f32 angle;
    Item* item;
    s32 i;
    // u8 i;

    item = item_gobj->user_data;
    if ((item->owner == item->xDD4_itemVar.foxblaster.xE7C) &&
        (item->xDD4_itemVar.foxblaster.xE74 != 0))
    {
        item->xDD4_itemVar.foxblaster.xE74 = 0;
        ftLib_80086644(item->xDD4_itemVar.foxblaster.xE7C, &ft_cur_pos);

        switch (item->kind) {
        case It_Kind_Fox_Blaster:
        case It_Kind_Falco_Blaster:
            ftFx_SpecialN_FtGetHoldJoint(item->xDD4_itemVar.foxblaster.xE7C,
                                         &ft_hold_joint_pos);
            item->xDD4_itemVar.foxblaster.xE14.x =
                ft_hold_joint_pos.x - ft_cur_pos.x;
            item->xDD4_itemVar.foxblaster.xE14.y =
                ft_hold_joint_pos.y - ft_cur_pos.y;
            item->xDD4_itemVar.foxblaster.xE14.z =
                ft_hold_joint_pos.z - ft_cur_pos.z;
            ftFx_SpecialN_ItGetHoldJoint(item->xDD4_itemVar.foxblaster.xE7C,
                                         &it_hold_joint_pos);
            angle = atan2f(ft_hold_joint_pos.y - it_hold_joint_pos.y,
                           ft_hold_joint_pos.x - it_hold_joint_pos.x);
            item->xDD4_itemVar.foxblaster.xE5C = angle;
            item->xDD4_itemVar.foxblaster.xDFC = 0;
            // efSync_Spawn(0x48E, item_gobj, &ft_hold_joint_pos,
            // item->xDD4_itemVar.foxblaster.xE5C, angle); efSync_Spawn(1166,
            // item_gobj, &ft_hold_joint_pos);
            efSync_Spawn(1166, item_gobj, &it_hold_joint_pos,
                         &item->xDD4_itemVar.foxblaster.xE5C);
            // item->xDD4_itemVar.foxblaster.xDE4 = (s32) M2C_ERROR(/* Read
            // from unset register $r3 */);
            item->xDD4_itemVar.foxblaster.xDE4 = 0;
            break;
        case It_Kind_Kirby_FoxBlaster:
        case It_Kind_Kirby_FalcoBlaster:
            ftKb_SpecialNFx_800FDC00(item->xDD4_itemVar.foxblaster.xE7C,
                                     &ft_hold_joint_pos);
            item->xDD4_itemVar.foxblaster.xE14.x =
                ft_hold_joint_pos.x - ft_cur_pos.x;
            item->xDD4_itemVar.foxblaster.xE14.y =
                ft_hold_joint_pos.y - ft_cur_pos.y;
            item->xDD4_itemVar.foxblaster.xE14.z =
                ft_hold_joint_pos.z - ft_cur_pos.z;
            ftKb_SpecialNFx_800FDC70(item->xDD4_itemVar.foxblaster.xE7C,
                                     &it_hold_joint_pos);
            angle = atan2f(ft_hold_joint_pos.y - it_hold_joint_pos.y,
                           ft_hold_joint_pos.x - it_hold_joint_pos.x);
            item->xDD4_itemVar.foxblaster.xE5C = angle;
            item->xDD4_itemVar.foxblaster.xDFC = 0;
            // efSync_Spawn(0x4AC, item_gobj, &ft_hold_joint_pos,
            // item->xDD4_itemVar.foxblaster.xE5C, angle); efSync_Spawn(1196,
            // item_gobj, &it_hold_joint_pos);
            efSync_Spawn(1196, item_gobj, &it_hold_joint_pos,
                         &item->xDD4_itemVar.foxblaster.xE5C);
            // item->xDD4_itemVar.foxblaster.xDE4 = (s32) M2C_ERROR(/* Read
            // from unset register $r3 */);
            item->xDD4_itemVar.foxblaster.xDE4 = 0;
            break;
        }

#if 1
        for (i = 0; i < 5; i = i + 1) {
            *(&item->xDD4_itemVar.foxblaster.xDF8 - i) =
                *(&item->xDD4_itemVar.foxblaster.xDF4 - i);
            *(&item->xDD4_itemVar.foxblaster.xE10 - i) =
                *(&item->xDD4_itemVar.foxblaster.xE0C - i);

            *(&item->xDD4_itemVar.foxblaster.xE50 - (i)) =
                *(&item->xDD4_itemVar.foxblaster.xE44 - (i));

            *(&item->xDD4_itemVar.foxblaster.xE70 - i) =
                *(&item->xDD4_itemVar.foxblaster.xE6C - i);
        }
#else
        item->xDD4_itemVar.foxblaster.xDF8 =
            item->xDD4_itemVar.foxblaster.xDF4;
        item->xDD4_itemVar.foxblaster.xE10 =
            item->xDD4_itemVar.foxblaster.xE0C;
        item->xDD4_itemVar.foxblaster.xE50.x =
            item->xDD4_itemVar.foxblaster.xE44.x;
        item->xDD4_itemVar.foxblaster.xE50.y =
            item->xDD4_itemVar.foxblaster.xE44.y;
        item->xDD4_itemVar.foxblaster.xE50.z =
            item->xDD4_itemVar.foxblaster.xE44.z;
        item->xDD4_itemVar.foxblaster.xE70 =
            item->xDD4_itemVar.foxblaster.xE6C;

        item->xDD4_itemVar.foxblaster.xDF4 =
            item->xDD4_itemVar.foxblaster.xDF0;
        item->xDD4_itemVar.foxblaster.xE0C =
            item->xDD4_itemVar.foxblaster.xE08;
        item->xDD4_itemVar.foxblaster.xE44.x =
            item->xDD4_itemVar.foxblaster.xE38.x;
        item->xDD4_itemVar.foxblaster.xE44.y =
            item->xDD4_itemVar.foxblaster.xE38.y;
        item->xDD4_itemVar.foxblaster.xE44.z =
            item->xDD4_itemVar.foxblaster.xE38.z;
        item->xDD4_itemVar.foxblaster.xE6C =
            item->xDD4_itemVar.foxblaster.xE68;

        item->xDD4_itemVar.foxblaster.xDF0 =
            item->xDD4_itemVar.foxblaster.xDEC;
        item->xDD4_itemVar.foxblaster.xE08 =
            item->xDD4_itemVar.foxblaster.xE04;
        item->xDD4_itemVar.foxblaster.xE38.x =
            item->xDD4_itemVar.foxblaster.xE2C.x;
        item->xDD4_itemVar.foxblaster.xE38.y =
            item->xDD4_itemVar.foxblaster.xE2C.y;
        item->xDD4_itemVar.foxblaster.xE38.z =
            item->xDD4_itemVar.foxblaster.xE2C.z;
        item->xDD4_itemVar.foxblaster.xE68 =
            item->xDD4_itemVar.foxblaster.xE64;

        item->xDD4_itemVar.foxblaster.xDEC =
            item->xDD4_itemVar.foxblaster.xDE8;
        item->xDD4_itemVar.foxblaster.xE04 =
            item->xDD4_itemVar.foxblaster.xE00;
        item->xDD4_itemVar.foxblaster.xE2C.x =
            item->xDD4_itemVar.foxblaster.xE20.x;
        item->xDD4_itemVar.foxblaster.xE2C.y =
            item->xDD4_itemVar.foxblaster.xE20.y;
        item->xDD4_itemVar.foxblaster.xE2C.z =
            item->xDD4_itemVar.foxblaster.xE20.z;
        item->xDD4_itemVar.foxblaster.xE64 =
            item->xDD4_itemVar.foxblaster.xE60;

        item->xDD4_itemVar.foxblaster.xDE8 =
            item->xDD4_itemVar.foxblaster.xDE4;
        item->xDD4_itemVar.foxblaster.xE00 =
            item->xDD4_itemVar.foxblaster.xDFC;
        item->xDD4_itemVar.foxblaster.xE20.x =
            item->xDD4_itemVar.foxblaster.xE14.x;
        item->xDD4_itemVar.foxblaster.xE20.y =
            item->xDD4_itemVar.foxblaster.xE14.y;
        item->xDD4_itemVar.foxblaster.xE20.z =
            item->xDD4_itemVar.foxblaster.xE14.z;
        item->xDD4_itemVar.foxblaster.xE60 =
            item->xDD4_itemVar.foxblaster.xE5C;
#endif

        item = item_gobj->user_data;
        item->xDD4_itemVar.foxblaster.xDE4 = 0;
        item->xDD4_itemVar.foxblaster.xDFC = 0;
        item->xDD4_itemVar.foxblaster.xE5C =
            item->xDD4_itemVar.foxblaster.xE14.x =
                item->xDD4_itemVar.foxblaster.xE14.y =
                    item->xDD4_itemVar.foxblaster.xE14.z = it_804DCF38;
    }
}

void it_802AE1D0(Item_GObj* item_gobj)
{
    Item* item;
    f32 unused;

    item = item_gobj->user_data;
    if ((item_gobj != NULL) && (item != NULL)) {
        item->xDD4_itemVar.foxblaster.xDD4 = 1;
        item->on_accessory = it_802ADEF0;
        item->xDD4_itemVar.foxblaster.xE74 = 1;
    }
}

void it_802AE200(HSD_GObj* item_gobj)
{
    HSD_JObj* jobj_1;
    HSD_JObj* jobj_2;
    HSD_JObj* jobj_3;
    Item* item;
    HSD_JObj* item_jobj;
    HSD_JObj* child_jobj_1;
    HSD_JObj* child_jobj_2;
    HSD_JObj* child_jobj_3;
    HSD_JObj* child_jobj_4;

    item_jobj = item_gobj->hsd_obj;
    item = item_gobj->user_data;
    if (item_jobj == NULL) {
        child_jobj_1 = NULL;
    } else {
        child_jobj_1 = item_jobj->child;
    }
    if (child_jobj_1 == NULL) {
        child_jobj_2 = NULL;
    } else {
        child_jobj_2 = child_jobj_1->child;
    }
    if (child_jobj_2 == NULL) {
        child_jobj_3 = NULL;
    } else {
        child_jobj_3 = child_jobj_2->child;
    }
    if (child_jobj_3 == NULL) {
        child_jobj_4 = NULL;
    } else {
        child_jobj_4 = child_jobj_3->child;
    }
    if (child_jobj_4 == NULL) {
        jobj_1 = NULL;
    } else {
        jobj_1 = child_jobj_4->next;
    }
    if ((item_gobj != NULL) && (item != NULL)) {
        if (jobj_1 != NULL) {
            HSD_JObjSetTranslateZ(
                jobj_1, it_803F6D58[item->xDD4_itemVar.foxblaster.xDD4]);

            if (jobj_1 == NULL) {
                jobj_2 = NULL;
            } else {
                jobj_2 = jobj_1->next;
            }
            HSD_JObjSetScaleY(jobj_2,
                              it_803F6D90[item->xDD4_itemVar.foxblaster.xDD4]);
            HSD_JObjSetScaleZ(jobj_2,
                              it_803F6D90[item->xDD4_itemVar.foxblaster.xDD4]);

            if (jobj_2 == NULL) {
                jobj_3 = NULL;
            } else {
                jobj_3 = jobj_2->next;
            }
            HSD_JObjSetRotationX(
                jobj_3, it_803F6DC8[item->xDD4_itemVar.foxblaster.xDD4]);

            // I think this section is iterating the 'state' (not the item
            // state, but something else), then resetting after it's done
            if ((item->xDD4_itemVar.foxblaster.xDD4 > 0) &&
                (item->xDD4_itemVar.foxblaster.xDD4 < 0xE))
            {
                item->xDD4_itemVar.foxblaster.xDD4 += 1;
                if (item->xDD4_itemVar.foxblaster.xDD4 >= 0xE) {
                    item->xDD4_itemVar.foxblaster.xDD4 = 0;
                }
            }
        }
    }
}

void it_802AE538(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    if ((item->xDD4_itemVar.foxblaster.xDD8 != 4) && (item_gobj != NULL) &&
        (item != NULL))
    {
        item->xDD4_itemVar.foxblaster.xDD8 = 1;
        item->xDD4_itemVar.foxblaster.xDDC = 1;
        if (item->xDD4_itemVar.foxblaster.xDE0 == 0) {
            switch (item->kind) { /* irregular */
            case It_Kind_Kirby_FoxBlaster:
            case It_Kind_Fox_Blaster:
                Item_8026AE84(item, 0x1AE05, 0x7F, 0x40);
                break;
            case It_Kind_Kirby_FalcoBlaster:
            case It_Kind_Falco_Blaster:
                Item_8026AE84(item, 0x186F1, 0x7F, 0x40);
                break;
            }
            item->xDD4_itemVar.foxblaster.xDE0 = 1;
        }
    }
}

void it_802AE608(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    if ((item->xDD4_itemVar.foxblaster.xDD8 != 0) && (item_gobj != NULL) &&
        (item != NULL))
    {
        item->xDD4_itemVar.foxblaster.xDD8 = 3;
        item->xDD4_itemVar.foxblaster.xDDC = -1;
    }
}

// void it_802AE63C(void* arg0) {
void it_802AE63C(Item_GObj* item_gobj)
{
    HSD_JObj* target_jobj;
    Item* item;
    HSD_JObj* item_jobj;
    HSD_JObj* child_jobj_1;
    HSD_JObj* child_jobj_2;
    HSD_JObj* child_jobj_3;

    item_jobj = item_gobj->hsd_obj;
    item = item_gobj->user_data;
    if (item_jobj == NULL) {
        child_jobj_1 = NULL;
    } else {
        child_jobj_1 = item_jobj->child;
    }
    if (child_jobj_1 == NULL) {
        child_jobj_2 = NULL;
    } else {
        child_jobj_2 = child_jobj_1->child;
    }
    if (child_jobj_2 == NULL) {
        child_jobj_3 = NULL;
    } else {
        child_jobj_3 = child_jobj_2->child;
    }
    if (child_jobj_3 == NULL) {
        target_jobj = NULL;
    } else {
        target_jobj = child_jobj_3->child;
    }
    // if ((item_gobj != NULL) && (item != NULL) && (is_jobj_null_check_1 =
    // target_jobj == NULL, (is_jobj_null_check_1 == 0))) {
    if ((item_gobj != NULL) && (item != NULL) && (target_jobj != NULL)) {
        HSD_JObjSetTranslateY(target_jobj,
                              it_803F6E28[item->xDD4_itemVar.foxblaster.xDD8]);

        if ((item->xDD4_itemVar.foxblaster.xDD8 > 0) &&
            (item->xDD4_itemVar.foxblaster.xDD8 < 4))
        {
            item->xDD4_itemVar.foxblaster.xDD8 +=
                item->xDD4_itemVar.foxblaster.xDDC;
            if (item->xDD4_itemVar.foxblaster.xDD8 >= 5) {
                item->xDD4_itemVar.foxblaster.xDD8 = 4;
                item->xDD4_itemVar.foxblaster.xDDC = 0;
                return;
            }
            if (item->xDD4_itemVar.foxblaster.xDD8 <= 0) {
                item->xDD4_itemVar.foxblaster.xDD8 = 0;
                item->xDD4_itemVar.foxblaster.xDDC = 0;
            }
        }
    }
}

void it_802AE7B8(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDB8_itcmd_var3 = 0;
    item->xDB4_itcmd_var2 = 0;
    item->xDB0_itcmd_var1 = 0;
    item->xDAC_itcmd_var0 = 0;
    item->xDCC_flag.b3 = 0;
    item->xDD4_itemVar.foxblaster.xDD4 = 0;
    item->xDD4_itemVar.foxblaster.xDD8 = 0;
    item->xDD4_itemVar.foxblaster.xDDC = 0.0f;
    item->xDD4_itemVar.foxblaster.xDE0 = 0.0f;
    item->xDD4_itemVar.foxblaster.xE74 = 0;
    item->xDD4_itemVar.foxblaster.xE78 = 1;

    item = item_gobj->user_data;

    item->xDD4_itemVar.foxblaster.xDE4 = 0.0f;
    item->xDD4_itemVar.foxblaster.xDFC = 0.0f;
    item->xDD4_itemVar.foxblaster.xE14.z = 0.0f;
    item->xDD4_itemVar.foxblaster.xE14.y = 0.0f;
    item->xDD4_itemVar.foxblaster.xE14.x = 0.0f;
    item->xDD4_itemVar.foxblaster.xE5C = 0.0f;

    item = item_gobj->user_data;

    item->xDD4_itemVar.foxblaster.xDE8 = 0;
    item->xDD4_itemVar.foxblaster.xE00 = 0;
    item->xDD4_itemVar.foxblaster.xE20.z = 0.0f;
    item->xDD4_itemVar.foxblaster.xE20.y = 0.0f;
    item->xDD4_itemVar.foxblaster.xE20.x = 0.0f;
    item->xDD4_itemVar.foxblaster.xE60 = 0.0f;

    item = item_gobj->user_data;

    item->xDD4_itemVar.foxblaster.xDEC = 0;
    item->xDD4_itemVar.foxblaster.xE04 = 0.0f;
    item->xDD4_itemVar.foxblaster.xE2C.z = 0.0f;
    item->xDD4_itemVar.foxblaster.xE2C.y = 0.0f;
    item->xDD4_itemVar.foxblaster.xE2C.x = 0.0f;
    item->xDD4_itemVar.foxblaster.xE64 = 0.0f;

    item = item_gobj->user_data;

    item->xDD4_itemVar.foxblaster.xDF0 = 0;
    item->xDD4_itemVar.foxblaster.xE08 = 0;
    item->xDD4_itemVar.foxblaster.xE38.z = 0.0f;
    item->xDD4_itemVar.foxblaster.xE38.y = 0.0f;
    item->xDD4_itemVar.foxblaster.xE38.x = 0.0f;
    item->xDD4_itemVar.foxblaster.xE68 = 0.0f;

    item = item_gobj->user_data;

    item->xDD4_itemVar.foxblaster.xDF4 = 0;
    item->xDD4_itemVar.foxblaster.xE0C = 0;
    item->xDD4_itemVar.foxblaster.xE44.z = 0.0f;
    item->xDD4_itemVar.foxblaster.xE44.y = 0.0f;
    item->xDD4_itemVar.foxblaster.xE44.x = 0.0f;
    item->xDD4_itemVar.foxblaster.xE6C = 0.0f;

    item = item_gobj->user_data;

    item->xDD4_itemVar.foxblaster.xDF8 = 0;
    item->xDD4_itemVar.foxblaster.xE10 = 0;
    item->xDD4_itemVar.foxblaster.xE50.z = 0.0f;
    item->xDD4_itemVar.foxblaster.xE50.y = 0.0f;
    item->xDD4_itemVar.foxblaster.xE50.x = 0.0f;
    item->xDD4_itemVar.foxblaster.xE70 = 0.0f;
}

// HSD_GObj* it_802AE8A8(f32 arg0, HSD_GObj* arg1, Vec3* arg2, enum
// Fighter_Part arg3, s32 arg4) { HSD_GObj* it_802AE8A8(f32 arg0, HSD_GObj*
// fighter_gobj, Vec3* arg2, Fighter_Part arg3, ItemKind arg4) {
HSD_GObj* it_802AE8A8(f32 facing_dir, HSD_GObj* fighter_gobj, Vec3* arg2,
                      s32 ft_part, s32 it_kind)
{
    SpawnItem spawn;
    Item_GObj* item_gobj;
    Item* item;
    s32 sp44_z;

    if (fighter_gobj != NULL) {
        spawn.kind = (ItemKind) it_kind;
        // spawn.hold_kind = (ItemKind) it_kind;

        spawn.prev_pos = *arg2;
        // spawn.prev_pos.x = arg2->x;
        // spawn.prev_pos.y = arg2->y;
        // spawn.prev_pos.z = arg2->z;

        spawn.prev_pos.z = it_804DCF38;
        // arg2->z = 0.0f;  // it_804DCF38
        // arg2->z = it_804DCF38;

        // spawn.pos = *arg2;
        spawn.pos = spawn.prev_pos;
        // spawn.pos.x = spawn.prev_pos.x;
        // spawn.pos.y = spawn.prev_pos.y;
        // spawn.pos.z = spawn.prev_pos.z;

        spawn.facing_dir = facing_dir;
        spawn.x3C_damage = 0;
        spawn.vel.x = spawn.vel.y = spawn.vel.z = it_804DCF38;
        // spawn.vel.x = spawn.vel.y = spawn.vel.z = it_804DCF38;
        spawn.x0_parent_gobj = fighter_gobj;
        spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
        spawn.x44_flag.bits.b0 = false;
        spawn.x40 = 0; // 1 = correct initial position?

        item_gobj = Item_80268B18(
            &spawn); // Item spawn prefunction - spawn airborne [sets
                     // spawn.x10, x48_ground_or_air, hold_kind]
        if (item_gobj != NULL) {
            item = item_gobj->user_data;
            item->xDD4_itemVar.foxblaster.xE7C = fighter_gobj;
            it_802AE7B8(item_gobj); // Clears all item vars and item cmd vars
            Item_8026AB54((HSD_GObj*) item_gobj, fighter_gobj, ft_part);
        }
    } else {
        item_gobj = NULL;
    }
    return (HSD_GObj*) item_gobj;
}

// Item_GObj* it_802AE994(Fighter_GObj* arg0, enum Fighter_Part arg1, ItemKind
// arg2) {
Item_GObj* it_802AE994(Fighter_GObj* fighter_gobj, Fighter_Part ft_part,
                       int it_kind)
{
    f32 sp5C;
    Vec3 sp44;
    Vec3 sp18;
    Item_GObj* item_gobj;
    Item* item;
    SpawnItem spawn;
    f32 val;

    sp44.x = 0;
    sp44.y = 0;
    sp44.z = 0;

    if (fighter_gobj != NULL) {
        spawn.kind = (ItemKind) it_kind;

        ftLib_80086644((HSD_GObj*) fighter_gobj, &sp18);
        spawn.prev_pos = sp18;
        spawn.prev_pos.z = it_804DCF38;
        spawn.pos = spawn.prev_pos;

        spawn.facing_dir = ftLib_800865C0((HSD_GObj*) fighter_gobj);
        spawn.x3C_damage = 0;
        spawn.vel.x = spawn.vel.y = spawn.vel.z = it_804DCF38;
        spawn.x0_parent_gobj = (HSD_GObj*) fighter_gobj;
        spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
        spawn.x44_flag.bits.b0 = false;
        spawn.x40 = 0; // 1 = correct initial position?

        item_gobj = Item_80268B18(
            &spawn); // Item spawn prefunction - spawn airborne [sets
                     // spawn.x10, x48_ground_or_air, hold_kind]
        if (item_gobj != NULL) {
            item = item_gobj->user_data;
            item->xDD4_itemVar.foxblaster.xE7C = (HSD_GObj*) fighter_gobj;
            it_802AE7B8(item_gobj); // Clears all item vars and item cmd vars
            item->xDB8_itcmd_var3 = 1;
            item->xDB4_itcmd_var2 = 1;
            item->xDB0_itcmd_var1 = 1;
            item->xDAC_itcmd_var0 = 1;
            Item_8026AB54((HSD_GObj*) item_gobj, (HSD_GObj*) fighter_gobj,
                          ft_part);
        }
    } else {
        item_gobj = NULL;
    }
    return item_gobj;
}

void it_802AEAB4(Item_GObj* item_gobj)
{
    Item* item;

    if (item_gobj != NULL) {
        item = item_gobj->user_data;
        item->owner = NULL;
        item->xDD4_itemVar.foxblaster.xE7C = NULL;
        efLib_DestroyAll((HSD_GObj*) item_gobj);
        Item_8026A8EC(item_gobj);
    }
}

void it_802AEB00(Item_GObj* item_gobj)
{
    Item* item;
    enum_t ft_special_state = 9;

    item = item_gobj->user_data;
    if ((item->xDB8_itcmd_var3 |
         (item->xDB4_itcmd_var2 |
          (item->xDAC_itcmd_var0 | item->xDB0_itcmd_var1))) != 0)
    {
        Item_80268E5C((HSD_GObj*) item_gobj, 0xA, ITEM_ANIM_UPDATE);
    } else {
        switch (item->kind) {
        case It_Kind_Fox_Blaster:
        case It_Kind_Falco_Blaster:
            ft_special_state = ftFx_SpecialN_GetBlasterAction(
                item->xDD4_itemVar.foxblaster.xE7C);
            break;
        case It_Kind_Kirby_FoxBlaster:
        case It_Kind_Kirby_FalcoBlaster:
            ft_special_state =
                ftKb_SpecialNFx_800FDD4C(item->xDD4_itemVar.foxblaster.xE7C);
            break;
        }
        // Item_80268E5C((HSD_GObj* ) item_gobj, it_803F6E68[M2C_ERROR(/* Read
        // from unset register $r3 */)], ITEM_ANIM_UPDATE);
        Item_80268E5C((HSD_GObj*) item_gobj, it_803F6E68[ft_special_state],
                      ITEM_ANIM_UPDATE);
    }
    Item_802694CC((HSD_GObj*) item_gobj);
}

// static inline void clear_blaster1(HSD_GObj* item_gobj) {
//     Item* item = item_gobj->user_data;

//     if ((item_gobj != NULL) && (item != NULL)) {
//         if (item->owner == item->xDD4_itemVar.foxblaster.xE7C) {
//             switch (item->kind) {
//                 case It_Kind_Fox_Blaster:
//                 case It_Kind_Falco_Blaster:
//                     ftFx_SpecialN_ClearBlaster(item->xDD4_itemVar.foxblaster.xE7C);
//                     break;
//                 case It_Kind_Kirby_FoxBlaster:
//                 case It_Kind_Kirby_FalcoBlaster:
//                     ftKb_SpecialNFx_800FDEB4(item->xDD4_itemVar.foxblaster.xE7C);
//                     break;
//             }
//         }
//         item->owner = 0U;
//         item->xDD4_itemVar.foxblaster.xE7C = NULL;
//         efLib_DestroyAll(item_gobj);
//     }
//     return;
// }

// static inline void clear_blaster2(HSD_GObj* item_gobj) {
//     Item* item;
//     item = item_gobj->user_data;

//     clearblaster1(item_gobj);
//     if (item_gobj != NULL) {
//         item->owner = 0U;
//         item->xDD4_itemVar.foxblaster.xE7C = NULL;
//         efLib_DestroyAll(item_gobj);
//         Item_8026A8EC((Item_GObj* ) item_gobj);
//     }
//     return;
// }

static inline void clear_blaster(HSD_GObj* item_gobj)
{
    Item* item;
    item = item_gobj->user_data;

    if ((item_gobj != NULL) && (item != NULL)) {
        if (item->owner == item->xDD4_itemVar.foxblaster.xE7C) {
            switch (item->kind) {
            case It_Kind_Fox_Blaster:
            case It_Kind_Falco_Blaster:
                ftFx_SpecialN_ClearBlaster(item->xDD4_itemVar.foxblaster.xE7C);
                break;
            case It_Kind_Kirby_FoxBlaster:
            case It_Kind_Kirby_FalcoBlaster:
                ftKb_SpecialNFx_800FDEB4(item->xDD4_itemVar.foxblaster.xE7C);
                break;
            }
        }
        item->owner = 0U;
        item->xDD4_itemVar.foxblaster.xE7C = NULL;
        efLib_DestroyAll(item_gobj);
    }
    if (item_gobj != NULL) {
        item = item_gobj->user_data;
        item->owner = 0U;
        item->xDD4_itemVar.foxblaster.xE7C = NULL;
        efLib_DestroyAll(item_gobj);
        Item_8026A8EC((Item_GObj*) item_gobj);
    }
    return;
}

// s32 it_802AEBCC(HSD_GObj* arg0) {
int it_802AEBCC(HSD_GObj* item_gobj)
{
    // HSD_GObj* gobj;
    s32 blaster_action;
    enum_t ft_special_state;
    bool blaster_removed;
    bool need_blaster;
    Item* item;

    item = item_gobj->user_data;

    // switch (item->msid) {
    //     case 2:
    //         goto block_5;
    //         break;
    //     case 5:
    //     case 9:
    //         // goto block_5;

    //         break;
    // }
    if (item->msid < 5) {
        if (item->msid == 2) {
            goto block_5;
        }
    } else if (item->msid >= 9) {
    } else {
        goto block_5;
    }
    ft_special_state = 9;
    switch (item->kind) {
    case It_Kind_Fox_Blaster:
    case It_Kind_Falco_Blaster:
        ft_special_state =
            ftFx_SpecialN_GetBlasterAction(item->xDD4_itemVar.foxblaster.xE7C);
        break;
    case It_Kind_Kirby_FoxBlaster:
    case It_Kind_Kirby_FalcoBlaster:
        ft_special_state =
            ftKb_SpecialNFx_800FDD4C(item->xDD4_itemVar.foxblaster.xE7C);
        break;
    }
    if (item->msid != it_803F6E3C[ft_special_state]) {
        Item_80268E5C(item_gobj, ft_special_state, ITEM_ANIM_UPDATE);
        Item_802694CC(item_gobj);
    }
block_5:

    if (item->xDD4_itemVar.foxblaster.xE7C != NULL) {
        blaster_action = 9;
        blaster_removed = 1;
        switch (item->kind) {
        case It_Kind_Fox_Blaster:
        case It_Kind_Falco_Blaster:
            blaster_action = ftFx_SpecialN_GetBlasterAction(
                item->xDD4_itemVar.foxblaster.xE7C);
            blaster_removed = ftFx_SpecialN_CheckRemoveBlaster(
                item->xDD4_itemVar.foxblaster.xE7C);
            break;
        case It_Kind_Kirby_FoxBlaster:
        case It_Kind_Kirby_FalcoBlaster:
            blaster_action =
                ftKb_SpecialNFx_800FDD4C(item->xDD4_itemVar.foxblaster.xE7C);
            blaster_removed =
                ftKb_SpecialNFx_800FDD14(item->xDD4_itemVar.foxblaster.xE7C);
            break;
        }
        if ((blaster_action == 9) || (blaster_removed == 1)) {
            // clear_blaster2(item_gobj);
            clear_blaster(item_gobj);
        } else {
            switch (item->kind) {
            case It_Kind_Fox_Blaster:
            case It_Kind_Falco_Blaster:
                need_blaster = ftFx_SpecialN_CheckBlasterAction(
                    item->xDD4_itemVar.foxblaster.xE7C);
                break;
            case It_Kind_Kirby_FoxBlaster:
            case It_Kind_Kirby_FalcoBlaster:
                need_blaster = ftKb_SpecialNFx_800FDDF4(
                    item->xDD4_itemVar.foxblaster.xE7C);
                break;
            default:
                need_blaster = 1;
                break;
            }
            if (need_blaster) {
                item->xDD4_itemVar.foxblaster.xE7C = NULL;
                Item_8026A8EC((Item_GObj*) item_gobj);
                efLib_DestroyAll(item_gobj);
            }
        }
    } else {
        // clear_blaster2(item_gobj);
        clear_blaster(item_gobj);
    }
    return 0;
}

void it_802AEED4(HSD_GObj* item_gobj)
{
    // it_802AE63C();
    it_802AE63C((Item_GObj*) item_gobj);
    it_802AE200(item_gobj);
}

// s32 it_802AEF08(HSD_GObj* arg0) {
int it_802AEF08(HSD_GObj* arg0)
{
    return 0;
}

// s32 it_802AEF10(HSD_GObj* arg0) {
// int it_802AEF10(HSD_GObj* item_gobj) {
//     efLib_DestroyAll(item_gobj);
//     clearblaster1(item_gobj);
//     return 1;
// }
int it_802AEF10(HSD_GObj* item_gobj)
{
    // void* temp_r31;
    Item* item;

    efLib_DestroyAll(item_gobj);
    item = item_gobj->user_data;
    if ((item_gobj != NULL) && (item != NULL)) {
        if (item->owner == item->xDD4_itemVar.foxblaster.xE7C) {
            switch (item->kind) {
            case It_Kind_Fox_Blaster:
            case It_Kind_Falco_Blaster:
                ftFx_SpecialN_ClearBlaster(item->xDD4_itemVar.foxblaster.xE7C);
                break;
            case It_Kind_Kirby_FoxBlaster:
            case It_Kind_Kirby_FalcoBlaster:
                ftKb_SpecialNFx_800FDEB4(item->xDD4_itemVar.foxblaster.xE7C);
                break;
            }
        }
        item->owner = 0U;
        item->xDD4_itemVar.foxblaster.xE7C = NULL;
        efLib_DestroyAll(item_gobj);
    }
    return 1;
}

void it_802AEFB8(HSD_GObj* arg0) {}

// s32 it_802AEFBC(HSD_GObj* arg0) {
// int it_802AEFBC(HSD_GObj* item_gobj) {
//     return it_802AEF10(item_gobj);
// }
int it_802AEFBC(HSD_GObj* item_gobj)
{
    Item* item;

    efLib_DestroyAll(item_gobj);
    item = item_gobj->user_data;
    if ((item_gobj != NULL) && (item != NULL)) {
        if (item->owner == item->xDD4_itemVar.foxblaster.xE7C) {
            switch (item->kind) {
            case It_Kind_Fox_Blaster:
            case It_Kind_Falco_Blaster:
                ftFx_SpecialN_ClearBlaster(item->xDD4_itemVar.foxblaster.xE7C);
                break;
            case It_Kind_Kirby_FoxBlaster:
            case It_Kind_Kirby_FalcoBlaster:
                ftKb_SpecialNFx_800FDEB4(item->xDD4_itemVar.foxblaster.xE7C);
                break;
            }
        }
        item->owner = 0U;
        item->xDD4_itemVar.foxblaster.xE7C = NULL;
        efLib_DestroyAll(item_gobj);
    }
    return 1;
}

// s32 it_802AF064(HSD_GObj* arg0) {
int it_802AF064(HSD_GObj* item_gobj)
{
    Vec3 ft_scale;
    // Item* item;

    if (item_gobj != NULL) {
        // item = item_gobj->user_data;
        // if (item != NULL) {
        if (item_gobj->user_data != NULL) {
            // if ((item->xDD4_itemVar.foxblaster.xE7C != NULL) &&
            // (ftCo_800BF228((Fighter_GObj*)
            // item->xDD4_itemVar.foxblaster.xE7C) == 1)) {
            if ((((Item*) item_gobj->user_data)
                     ->xDD4_itemVar.foxblaster.xE7C != NULL) &&
                (ftCo_800BF228((Fighter_GObj*) ((Item*) item_gobj->user_data)
                                   ->xDD4_itemVar.foxblaster.xE7C) == 1))
            {
                // ft_scale.x = ft_scale.y = ft_scale.z =
                // HSD_JObjGetScaleY(item->xDD4_itemVar.foxblaster.xE7C->hsd_obj);
                ft_scale.x = ft_scale.y = ft_scale.z = HSD_JObjGetScaleY(
                    ((Item*) item_gobj->user_data)
                        ->xDD4_itemVar.foxblaster.xE7C->hsd_obj);
                HSD_JObjSetScale(item_gobj->hsd_obj, &ft_scale);
            }
        }
    }
    return 0;
}

void it_802AF178(HSD_GObj* arg0) {}

// s32 it_802AF17C(HSD_GObj* arg0) {
int it_802AF17C(HSD_GObj* arg0)
{
    return 0;
}

void it_802AF184(Item_GObj* item_gobj_1, Item_GObj* item_gobj_2)
{
    it_8026B894(item_gobj_1, (HSD_GObj*) item_gobj_2);
}
