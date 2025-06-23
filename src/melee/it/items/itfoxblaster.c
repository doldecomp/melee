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

#include <stdbool.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <melee/ft/chara/ftFox/ftFx_SpecialN.h>
#include <melee/ft/chara/ftKirby/ftKb_Init.h>
#include <melee/it/item.h>
#include <melee/lb/lbrefract.h>

void it_802ADF10(HSD_GObj* item_gobj);
bool it_802AEBCC(HSD_GObj* item_gobj);
void it_802AEED4(HSD_GObj* item_gobj);
bool it_802AEF08(HSD_GObj* item_gobj);
bool it_802AEF10(HSD_GObj* item_gobj);
void it_802AEFB8(HSD_GObj* item_gobj);
bool it_802AEFBC(HSD_GObj* item_gobj);
bool it_802AF064(HSD_GObj* item_gobj);
void it_802AF178(HSD_GObj* item_gobj);
bool it_802AF17C(HSD_GObj* item_gobj);

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
// Used for jobj->translate.z calc for xDD4
f32 it_803F6D58[14] = { 0.0F,    -0.51F,  -1.02F,  -1.53F,  -1.39F,
                        -1.251F, -1.112F, -0.973F, -0.834F, -0.695F,
                        -0.556F, -0.417F, -0.278F, -0.139F };
// Used in jobj->scale.y/z calcs for xDD4
f32 it_803F6D90[14] = { 0.5F, 0.5F, 1.75F, 3.0F, 2.375F, 1.75F, 1.125F,
                        0.5F, 0.5F, 0.5F,  0.5F, 0.5F,   0.5F,  0.5F };
// Used for jobj->rotate.x calc for xDD4
f32 it_803F6DC8[14] = { 0.0F, -42.0F, -20.0F, 0.0F, 0.0F, 0.0F, 0.0F,
                        0.0F, 0.0F,   0.0F,   0.0F, 0.0F, 0.0F, 0.0F };

static inline HSD_JObj* jobj_child(HSD_JObj* node)
{
    if (node == NULL) {
        return NULL;
    }
    return node->child;
}

/// @brief Sets sfx and jobj flags based on if the blaster model is visible
/// (and fox vs falco)
/// @param item_gobj
/// @param visibility always 1 except when called during SpecialN end
/// animations. Then it's set to 'fp->cmd_vars[1]', which is set in the
/// action's scripts
void it_802ADDD0(Item_GObj* item_gobj, s32 visibility)
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
    if (item->xDD4_itemVar.foxblaster.set_sfx_var2 != visibility) {
        item->xDD4_itemVar.foxblaster.set_sfx_var2 = visibility;
        if (visibility == 2) {
            switch (item->kind) {
            case It_Kind_Kirby_FoxBlaster:
            case It_Kind_Fox_Blaster:
                Item_8026AE84(item, 0x1AE14, 0x7F, 0x40);
                break;
            case It_Kind_Kirby_FalcoBlaster:
            case It_Kind_Falco_Blaster:
                Item_8026AE84(item, 0x18700, 0x7F, 0x40);
                // Item_8026AE84(item, 0x1AE05, 0x7F, 0x40);
                break;
            }
        }
    }
    switch (item->xDD4_itemVar.foxblaster.set_sfx_var2) {
    case 0:
    case 2:
        HSD_JObjSetFlagsAll(child_jobj, 0x10);
        return;
    case 1:
        HSD_JObjClearFlagsAll(child_jobj, 0x10);
        break;
    }
}

/// @brief Redirects to another function (it_802ADF10)
/// @param item_gobj
void it_802ADEF0(HSD_GObj* item_gobj)
{
    it_802ADF10(item_gobj);
}

/// @brief Sets item position relative to owner position and resets some
/// blaster vars, then shifts blaster var values up their groups and resets the
/// lowest var in each
/// @param item_gobj
void it_802ADF10(HSD_GObj* item_gobj)
{
    Vec3 ft_cur_pos;
    Vec3 ft_hold_joint_pos;
    Vec3 it_hold_joint_pos;
    Item* item = GET_ITEM(item_gobj);

    // If blaster is shooting this frame, then spawn shooting effect at
    // item/fighter position
    if (item->owner == item->xDD4_itemVar.foxblaster.owner &&
        item->xDD4_itemVar.foxblaster.gfx_spawn_var)
    {
        item->xDD4_itemVar.foxblaster.gfx_spawn_var = false;
        ftLib_80086644(item->xDD4_itemVar.foxblaster.owner, &ft_cur_pos);

        switch (item->kind) {
        case It_Kind_Fox_Blaster:
        case It_Kind_Falco_Blaster:
            ftFx_SpecialN_FtGetHoldJoint(item->xDD4_itemVar.foxblaster.owner,
                                         &ft_hold_joint_pos);
            item->xDD4_itemVar.foxblaster.xE14.x =
                ft_hold_joint_pos.x - ft_cur_pos.x;
            item->xDD4_itemVar.foxblaster.xE14.y =
                ft_hold_joint_pos.y - ft_cur_pos.y;
            item->xDD4_itemVar.foxblaster.xE14.z =
                ft_hold_joint_pos.z - ft_cur_pos.z;
            ftFx_SpecialN_ItGetHoldJoint(item->xDD4_itemVar.foxblaster.owner,
                                         &it_hold_joint_pos);

            item->xDD4_itemVar.foxblaster.angle =
                atan2f(ft_hold_joint_pos.y - it_hold_joint_pos.y,
                       ft_hold_joint_pos.x - it_hold_joint_pos.x);
            item->xDD4_itemVar.foxblaster.xDFC = 0;

            item->xDD4_itemVar.foxblaster.xDE4 =
                efSync_Spawn(1166, item_gobj, &ft_hold_joint_pos,
                             &item->xDD4_itemVar.foxblaster.angle);
            break;
        case It_Kind_Kirby_FoxBlaster:
        case It_Kind_Kirby_FalcoBlaster:
            ftKb_SpecialNFx_800FDC00(item->xDD4_itemVar.foxblaster.owner,
                                     &ft_hold_joint_pos);
            item->xDD4_itemVar.foxblaster.xE14.x =
                ft_hold_joint_pos.x - ft_cur_pos.x;
            item->xDD4_itemVar.foxblaster.xE14.y =
                ft_hold_joint_pos.y - ft_cur_pos.y;
            item->xDD4_itemVar.foxblaster.xE14.z =
                ft_hold_joint_pos.z - ft_cur_pos.z;
            ftKb_SpecialNFx_800FDC70(item->xDD4_itemVar.foxblaster.owner,
                                     &it_hold_joint_pos);

            item->xDD4_itemVar.foxblaster.angle =
                atan2f(ft_hold_joint_pos.y - it_hold_joint_pos.y,
                       ft_hold_joint_pos.x - it_hold_joint_pos.x);
            item->xDD4_itemVar.foxblaster.xDFC = 0;

            item->xDD4_itemVar.foxblaster.xDE4 =
                efSync_Spawn(1196, item_gobj, &ft_hold_joint_pos,
                             &item->xDD4_itemVar.foxblaster.angle);
            break;
        }

#if 0
        {
            int i;
            for (i = 0; i < 5; i++) {
                *(&item->xDD4_itemVar.foxblaster.xDF8 - i) =
                    *(&item->xDD4_itemVar.foxblaster.xDF4 - i);
                *(&item->xDD4_itemVar.foxblaster.xE10 - i) =
                    *(&item->xDD4_itemVar.foxblaster.xE0C - i);

                *(&item->xDD4_itemVar.foxblaster.xE50 - i) =
                    *(&item->xDD4_itemVar.foxblaster.xE44 - i);

                *(&item->xDD4_itemVar.foxblaster.xE70 - i) =
                    *(&item->xDD4_itemVar.foxblaster.xE6C - i);
            }
        }
#else
        item->xDD4_itemVar.foxblaster.xDF8 =
            item->xDD4_itemVar.foxblaster.xDF4;
        item->xDD4_itemVar.foxblaster.xE10 =
            item->xDD4_itemVar.foxblaster.xE0C;
        item->xDD4_itemVar.foxblaster.xE50 =
            item->xDD4_itemVar.foxblaster.xE44;
        item->xDD4_itemVar.foxblaster.xE70 =
            item->xDD4_itemVar.foxblaster.xE6C;

        item->xDD4_itemVar.foxblaster.xDF4 =
            item->xDD4_itemVar.foxblaster.xDF0;
        item->xDD4_itemVar.foxblaster.xE0C =
            item->xDD4_itemVar.foxblaster.xE08;
        item->xDD4_itemVar.foxblaster.xE44 =
            item->xDD4_itemVar.foxblaster.xE38;
        item->xDD4_itemVar.foxblaster.xE6C =
            item->xDD4_itemVar.foxblaster.xE68;

        item->xDD4_itemVar.foxblaster.xDF0 =
            item->xDD4_itemVar.foxblaster.xDEC;
        item->xDD4_itemVar.foxblaster.xE08 =
            item->xDD4_itemVar.foxblaster.xE04;
        item->xDD4_itemVar.foxblaster.xE38 =
            item->xDD4_itemVar.foxblaster.xE2C;
        item->xDD4_itemVar.foxblaster.xE68 =
            item->xDD4_itemVar.foxblaster.xE64;

        item->xDD4_itemVar.foxblaster.xDEC =
            item->xDD4_itemVar.foxblaster.xDE8;
        item->xDD4_itemVar.foxblaster.xE04 =
            item->xDD4_itemVar.foxblaster.xE00;
        item->xDD4_itemVar.foxblaster.xE2C =
            item->xDD4_itemVar.foxblaster.xE20;
        item->xDD4_itemVar.foxblaster.xE64 =
            item->xDD4_itemVar.foxblaster.xE60;

        item->xDD4_itemVar.foxblaster.xDE8 =
            item->xDD4_itemVar.foxblaster.xDE4;
        item->xDD4_itemVar.foxblaster.xE00 =
            item->xDD4_itemVar.foxblaster.xDFC;
        item->xDD4_itemVar.foxblaster.xE20 =
            item->xDD4_itemVar.foxblaster.xE14;
        item->xDD4_itemVar.foxblaster.xE60 =
            item->xDD4_itemVar.foxblaster.angle;
#endif

        item = GET_ITEM(item_gobj);
        item->xDD4_itemVar.foxblaster.xDE4 = 0;
        item->xDD4_itemVar.foxblaster.xDFC = 0;
        item->xDD4_itemVar.foxblaster.angle =
            item->xDD4_itemVar.foxblaster.xE14.x =
                item->xDD4_itemVar.foxblaster.xE14.y =
                    item->xDD4_itemVar.foxblaster.xE14.z = 0.0F;
    }
}

/// @brief If item exists, set some blaster vars and accessory callback
/// function. Gets called from SpecialN funcs when a blaster shot should be
/// created
/// @param item_gobj
void it_802AE1D0(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    if (item_gobj != NULL && item != NULL) {
        item->xDD4_itemVar.foxblaster.xDD4 = 1;
        item->on_accessory = it_802ADEF0;
        item->xDD4_itemVar.foxblaster.gfx_spawn_var = true;
    }
}

/// @brief Gets root jobj of model and does some transformations to it
/// @param item_gobj
void it_802AE200(Item_GObj* item_gobj)
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
    f32 unused1;
    f32 unused2;
    f32 unused3;
    f32 unused4;
    f32 unused5;
    f32 unused6;

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
                (item->xDD4_itemVar.foxblaster.xDD4 < 14))
            {
                item->xDD4_itemVar.foxblaster.xDD4 += 1;
                if (item->xDD4_itemVar.foxblaster.xDD4 >= 14) {
                    item->xDD4_itemVar.foxblaster.xDD4 = 0;
                }
            }
        }
    }
}

/// @brief If item exists and some blaster vars at specific values (possibly
/// frame numbers?), then set sfx. Called from SpecialN funcs when cmd_var3 = 1
/// (when gun shooting starts)
/// @param item_gobj
void it_802AE538(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    if ((item->xDD4_itemVar.foxblaster.xDD8 != 4) && (item_gobj != NULL) &&
        (item != NULL))
    {
        item->xDD4_itemVar.foxblaster.xDD8 = 1;
        item->xDD4_itemVar.foxblaster.xDDC = 1;
        if (!item->xDD4_itemVar.foxblaster.xDE0) {
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
            item->xDD4_itemVar.foxblaster.xDE0 = true;
        }
    }
}

/// @brief If item exists and a blaster var at a specific values (possibly
/// frame numbers?), then set other blaster vars. Called from SpecialN funcs
/// when cmd_var3 = 2 (when gun is getting put away, but not yet invisible)
/// @param item_gobj
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

// Used in jobj->translate.y calc for xDD8
static f32 it_803F6E28[5] = { -0.425F, -0.595F, -0.765F, -0.935F, -0.85F };

/// @brief Gets root jobj of model and does some transformations to it; then
/// checks blaster var values and changes them
/// @param item_gobj
void it_802AE63C(Item_GObj* item_gobj)
{
    HSD_JObj* target_jobj;
    Item* item;
    HSD_JObj* item_jobj;
    HSD_JObj* child_jobj_1;
    HSD_JObj* child_jobj_2;
    HSD_JObj* child_jobj_3;
    PAD_STACK(8);

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

/// @brief Resets all blaster and cmd vars
/// @param item_gobj
void it_802AE7B8(Item_GObj* item_gobj)
{
    Item* item;

    item = GET_ITEM(item_gobj);

    item->xDB8_itcmd_var3 = 0;
    item->xDB4_itcmd_var2 = 0;
    item->xDB0_itcmd_var1 = 0;
    item->xDAC_itcmd_var0 = 0;
    item->xDCC_flag.b3 = 0;
    item->xDD4_itemVar.foxblaster.xDD4 = 0;
    item->xDD4_itemVar.foxblaster.xDD8 = 0;
    item->xDD4_itemVar.foxblaster.xDDC = 0;
    item->xDD4_itemVar.foxblaster.xDE0 = false;
    item->xDD4_itemVar.foxblaster.gfx_spawn_var = false;
    item->xDD4_itemVar.foxblaster.set_sfx_var2 = 1;

    item = GET_ITEM(item_gobj);

    item->xDD4_itemVar.foxblaster.xDE4 = 0.0F;
    item->xDD4_itemVar.foxblaster.xDFC = 0.0F;
    item->xDD4_itemVar.foxblaster.xE14.z = 0.0F;
    item->xDD4_itemVar.foxblaster.xE14.y = 0.0F;
    item->xDD4_itemVar.foxblaster.xE14.x = 0.0F;
    item->xDD4_itemVar.foxblaster.angle = 0.0F;

    item = GET_ITEM(item_gobj);

    item->xDD4_itemVar.foxblaster.xDE8 = 0;
    item->xDD4_itemVar.foxblaster.xE00 = 0;
    item->xDD4_itemVar.foxblaster.xE20.z = 0.0F;
    item->xDD4_itemVar.foxblaster.xE20.y = 0.0F;
    item->xDD4_itemVar.foxblaster.xE20.x = 0.0F;
    item->xDD4_itemVar.foxblaster.xE60 = 0.0F;

    item = GET_ITEM(item_gobj);

    item->xDD4_itemVar.foxblaster.xDEC = 0;
    item->xDD4_itemVar.foxblaster.xE04 = 0.0F;
    item->xDD4_itemVar.foxblaster.xE2C.z = 0.0F;
    item->xDD4_itemVar.foxblaster.xE2C.y = 0.0F;
    item->xDD4_itemVar.foxblaster.xE2C.x = 0.0F;
    item->xDD4_itemVar.foxblaster.xE64 = 0.0F;

    item = GET_ITEM(item_gobj);

    item->xDD4_itemVar.foxblaster.xDF0 = 0;
    item->xDD4_itemVar.foxblaster.xE08 = 0;
    item->xDD4_itemVar.foxblaster.xE38.z = 0.0F;
    item->xDD4_itemVar.foxblaster.xE38.y = 0.0F;
    item->xDD4_itemVar.foxblaster.xE38.x = 0.0F;
    item->xDD4_itemVar.foxblaster.xE68 = 0.0F;

    item = GET_ITEM(item_gobj);

    item->xDD4_itemVar.foxblaster.xDF4 = 0;
    item->xDD4_itemVar.foxblaster.xE0C = 0;
    item->xDD4_itemVar.foxblaster.xE44.z = 0.0F;
    item->xDD4_itemVar.foxblaster.xE44.y = 0.0F;
    item->xDD4_itemVar.foxblaster.xE44.x = 0.0F;
    item->xDD4_itemVar.foxblaster.xE6C = 0.0F;

    item = GET_ITEM(item_gobj);

    item->xDD4_itemVar.foxblaster.xDF8 = 0;
    item->xDD4_itemVar.foxblaster.xE10 = 0;
    item->xDD4_itemVar.foxblaster.xE50.z = 0.0F;
    item->xDD4_itemVar.foxblaster.xE50.y = 0.0F;
    item->xDD4_itemVar.foxblaster.xE50.x = 0.0F;
    item->xDD4_itemVar.foxblaster.xE70 = 0.0F;
}

/// @brief Spawns blaster item at location arg2 and gives to fighter at
/// specified fighter part
/// @param facing_dir
/// @param fighter_gobj
/// @param arg2
/// @param ft_part
/// @param it_kind
/// @return item_gobj (HSD_GObj* for the newly spawned item)
Item_GObj* it_802AE8A8(f32 facing_dir, Fighter_GObj* fighter_gobj, Vec3* arg2,
                       Fighter_Part ft_part, ItemKind it_kind)
{
    SpawnItem spawn;
    Item_GObj* item_gobj;
    Item* item;
    s32 sp44_z;

    if (fighter_gobj != NULL) {
        spawn.kind = it_kind;
        spawn.prev_pos = *arg2;
        spawn.prev_pos.z = 0.0F;
        spawn.pos = spawn.prev_pos;
        spawn.facing_dir = facing_dir;
        spawn.x3C_damage = 0;
        spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
        spawn.x0_parent_gobj = (HSD_GObj*) fighter_gobj;
        spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
        spawn.x44_flag.b0 = false;
        spawn.x40 = 0; // 1 = correct initial position?

        item_gobj = Item_80268B18(
            &spawn); // Item spawn prefunction - spawn airborne [sets
                     // spawn.x10, x48_ground_or_air, hold_kind]
        if (item_gobj != NULL) {
            item = item_gobj->user_data;
            item->xDD4_itemVar.foxblaster.owner = (HSD_GObj*) fighter_gobj;
            it_802AE7B8(item_gobj); // Clears all item vars and item cmd vars
            Item_8026AB54((HSD_GObj*) item_gobj, (HSD_GObj*) fighter_gobj,
                          ft_part);
        }
    } else {
        item_gobj = NULL;
    }
    return item_gobj;
}

/// @brief Spawns blaster item at fighter's location and gives to them at
/// specified part, as well as initializes cmd vars at 1 (different than other
/// spawn function)
/// @param owner_gobj
/// @param ft_part
/// @param it_kind
/// @return item_gobj (HSD_GObj* for the newly spawned item)
Item_GObj* it_802AE994(Fighter_GObj* owner_gobj, Fighter_Part ft_part,
                       ItemKind it_kind)
{
    SpawnItem spawn;
    Item_GObj* item_gobj;
    Vec3 sp18;

    if (owner_gobj != NULL) {
        spawn.kind = it_kind;

        ftLib_80086644(owner_gobj, &sp18);
        spawn.prev_pos = sp18;
        spawn.prev_pos.z = 0.0F;
        spawn.pos = spawn.prev_pos;

        spawn.facing_dir = ftLib_800865C0(owner_gobj);
        spawn.x3C_damage = 0;
        spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
        spawn.x0_parent_gobj = owner_gobj;
        spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
        spawn.x44_flag.b0 = false;
        spawn.x40 = 0;

        item_gobj = Item_80268B18(
            &spawn); // Item spawn prefunction - spawn airborne [sets
                     // spawn.x10, x48_ground_or_air, hold_kind]
        if (item_gobj != NULL) {
            Item* item = GET_ITEM(item_gobj);
            item->xDD4_itemVar.foxblaster.owner = owner_gobj;
            it_802AE7B8(item_gobj); // Clears all item vars and item cmd vars
            item->xDB8_itcmd_var3 = 1;
            item->xDB4_itcmd_var2 = 1;
            item->xDB0_itcmd_var1 = 1;
            item->xDAC_itcmd_var0 = 1;
            Item_8026AB54(item_gobj, owner_gobj, ft_part);
        }
    } else {
        item_gobj = NULL;
    }
    return item_gobj;
}

/// @brief If item exists, then clear item and blaster vars and destroy item
/// @param item_gobj
void it_802AEAB4(Item_GObj* item_gobj)
{
    Item* item;

    if (item_gobj != NULL) {
        item = item_gobj->user_data;
        item->owner = NULL;
        item->xDD4_itemVar.foxblaster.owner = NULL;
        efLib_DestroyAll(item_gobj);
        Item_8026A8EC(item_gobj);
    }
}

// This is the length of the ItemStateTable
static int it_803F6E3C[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

// Fighter's state/ftFx_SpecialNIndex gets indexed into this table
// for value to set item state to
static int it_803F6E68[11] = { 0, 9, 9, 3, 9, 9, 6, 7, 8, 9, 10 };

/// @brief If any cmd var is non-zero, change the item state to 10. Otherwise
/// get the item state for the current fighter move, and set that. Then call
/// Item_802694CC to do advance animation + script
/// @param item_gobj
void it_802AEB00(Item_GObj* item_gobj)
{
    Item* item;
    enum_t ft_special_state = 9;

    item = item_gobj->user_data;
    if ((item->xDB8_itcmd_var3 |
         (item->xDB4_itcmd_var2 |
          (item->xDAC_itcmd_var0 | item->xDB0_itcmd_var1))) != 0)
    {
        Item_80268E5C(item_gobj, 0xA,
                      ITEM_ANIM_UPDATE); // Uses the last state in the Item
                                         // table (the second -1 id state)
    } else {
        switch (item->kind) {
        case It_Kind_Fox_Blaster:
        case It_Kind_Falco_Blaster:
            ft_special_state = ftFx_SpecialN_GetBlasterAction(
                item->xDD4_itemVar.foxblaster.owner);
            break;
        case It_Kind_Kirby_FoxBlaster:
        case It_Kind_Kirby_FalcoBlaster:
            ft_special_state =
                ftKb_SpecialNFx_800FDD4C(item->xDD4_itemVar.foxblaster.owner);
            break;
        }
        Item_80268E5C(item_gobj, it_803F6E68[ft_special_state],
                      ITEM_ANIM_UPDATE);
    }
    Item_802694CC(item_gobj);
}

/// @brief Clear the references from the blaster item and fighter to each other
/// and destroy the item
/// @param item_gobj
static inline void clear_blaster(HSD_GObj* item_gobj)
{
    Item* item;
    item = item_gobj->user_data;

    if ((item_gobj != NULL) && (item != NULL)) {
        if (item->owner == item->xDD4_itemVar.foxblaster.owner) {
            switch (item->kind) {
            case It_Kind_Fox_Blaster:
            case It_Kind_Falco_Blaster:
                ftFx_SpecialN_ClearBlaster(
                    item->xDD4_itemVar.foxblaster.owner);
                break;
            case It_Kind_Kirby_FoxBlaster:
            case It_Kind_Kirby_FalcoBlaster:
                ftKb_SpecialNFx_800FDEB4(item->xDD4_itemVar.foxblaster.owner);
                break;
            }
        }
        item->owner = 0U;
        item->xDD4_itemVar.foxblaster.owner = NULL;
        efLib_DestroyAll(item_gobj);
    }
    if (item_gobj != NULL) {
        item = item_gobj->user_data;
        item->owner = 0U;
        item->xDD4_itemVar.foxblaster.owner = NULL;
        efLib_DestroyAll(item_gobj);
        Item_8026A8EC((Item_GObj*) item_gobj);
    }
    return;
}

/// @brief Changes item state to match the fighter's current action
/// (ftFx_SpecialNIndex), updates subactions, and runs animation. Then clear
/// blaster item if no longer needed
/// @param item_gobj
/// @return false
bool it_802AEBCC(HSD_GObj* item_gobj)
{
    // HSD_GObj* gobj;
    int blaster_action;
    enum_t ft_special_state;
    bool blaster_removed;
    bool blaster_not_needed;
    Item* item;
    f32 unused1;
    f32 unused2;
    f32 unused3;
    f32 unused4;
    f32 unused5;
    f32 unused6;
    f32 unused7;
    f32 unused8;
    f32 unused9;

    item = GET_ITEM(item_gobj);

    // If fighter's action state is ftFx_MS_SpecialNEnd,
    // ftFx_MS_SpecialAirNEnd, or does not use a blaster (aka msid is 9): skip
    // to block_5

    switch (item->msid) {
    case 2:
    case 5:
    case 6:
    case 7:
    case 8:
        break;
    default:
        ft_special_state = 9;
        switch (item->kind) {
        case It_Kind_Fox_Blaster:
        case It_Kind_Falco_Blaster:
            ft_special_state = ftFx_SpecialN_GetBlasterAction(
                item->xDD4_itemVar.foxblaster.owner);
            break;
        case It_Kind_Kirby_FoxBlaster:
        case It_Kind_Kirby_FalcoBlaster:
            ft_special_state =
                ftKb_SpecialNFx_800FDD4C(item->xDD4_itemVar.foxblaster.owner);
            break;
        }
        // If the item's current state does not match the fighter's action state,
        // then change it to match and run animations
        if (item->msid != it_803F6E3C[ft_special_state]) {
            Item_80268E5C(item_gobj, ft_special_state, ITEM_ANIM_UPDATE);
            Item_802694CC(item_gobj);
        }
    }

    // If the blaster item is no longer needed (based on fighter state) and has
    // not already been removed, then remove/clear it
    if (item->xDD4_itemVar.foxblaster.owner != NULL) {
        blaster_action = 9;
        blaster_removed = true;
        switch (item->kind) {
        case It_Kind_Fox_Blaster:
        case It_Kind_Falco_Blaster:
            blaster_action = ftFx_SpecialN_GetBlasterAction(
                item->xDD4_itemVar.foxblaster.owner);
            blaster_removed = ftFx_SpecialN_CheckRemoveBlaster(
                item->xDD4_itemVar.foxblaster.owner);
            break;
        case It_Kind_Kirby_FoxBlaster:
        case It_Kind_Kirby_FalcoBlaster:
            blaster_action =
                ftKb_SpecialNFx_800FDD4C(item->xDD4_itemVar.foxblaster.owner);
            blaster_removed =
                ftKb_SpecialNFx_800FDD14(item->xDD4_itemVar.foxblaster.owner);
            break;
        }
        if ((blaster_action == 9) || (blaster_removed == true)) {
            // clear_blaster2(item_gobj);
            clear_blaster(item_gobj);
        } else {
            switch (item->kind) {
            case It_Kind_Fox_Blaster:
            case It_Kind_Falco_Blaster:
                blaster_not_needed = ftFx_SpecialN_CheckBlasterAction(
                    item->xDD4_itemVar.foxblaster.owner);
                break;
            case It_Kind_Kirby_FoxBlaster:
            case It_Kind_Kirby_FalcoBlaster:
                blaster_not_needed = ftKb_SpecialNFx_800FDDF4(
                    item->xDD4_itemVar.foxblaster.owner);
                break;
            default:
                blaster_not_needed = true;
                break;
            }
            if (blaster_not_needed) {
                item->xDD4_itemVar.foxblaster.owner = NULL;
                Item_8026A8EC(item_gobj);
                efLib_DestroyAll(item_gobj);
            }
        }
    } else {
        // clear_blaster2(item_gobj);
        clear_blaster(item_gobj);
    }
    return false;
}

/// @brief Calls model transformation functions
/// @param item_gobj
void it_802AEED4(HSD_GObj* item_gobj)
{
    it_802AE63C(item_gobj);
    it_802AE200(item_gobj);
}

/// @brief Does nothing
/// @param item_gobj
/// @return false
bool it_802AEF08(HSD_GObj* item_gobj)
{
    return false;
}

/// @brief If blaster item exists, clear references from it
/// @param item_gobj
/// @return true
bool it_802AEF10(HSD_GObj* item_gobj)
{
    Item* item;

    efLib_DestroyAll(item_gobj);
    item = item_gobj->user_data;
    if ((item_gobj != NULL) && (item != NULL)) {
        if (item->owner == item->xDD4_itemVar.foxblaster.owner) {
            switch (item->kind) {
            case It_Kind_Fox_Blaster:
            case It_Kind_Falco_Blaster:
                ftFx_SpecialN_ClearBlaster(
                    item->xDD4_itemVar.foxblaster.owner);
                break;
            case It_Kind_Kirby_FoxBlaster:
            case It_Kind_Kirby_FalcoBlaster:
                ftKb_SpecialNFx_800FDEB4(item->xDD4_itemVar.foxblaster.owner);
                break;
            }
        }
        item->owner = 0U;
        item->xDD4_itemVar.foxblaster.owner = NULL;
        efLib_DestroyAll(item_gobj);
    }
    return true;
}

/// @brief Does nothing
/// @param item_gobj
void it_802AEFB8(HSD_GObj* item_gobj) {}

/// @brief If blaster item exists, clear references from it (identical to
/// it_802AEF10)
/// @param item_gobj
/// @return true
bool it_802AEFBC(HSD_GObj* item_gobj)
{
    Item* item;

    efLib_DestroyAll(item_gobj);
    item = item_gobj->user_data;
    if ((item_gobj != NULL) && (item != NULL)) {
        if (item->owner == item->xDD4_itemVar.foxblaster.owner) {
            switch (item->kind) {
            case It_Kind_Fox_Blaster:
            case It_Kind_Falco_Blaster:
                ftFx_SpecialN_ClearBlaster(
                    item->xDD4_itemVar.foxblaster.owner);
                break;
            case It_Kind_Kirby_FoxBlaster:
            case It_Kind_Kirby_FalcoBlaster:
                ftKb_SpecialNFx_800FDEB4(item->xDD4_itemVar.foxblaster.owner);
                break;
            }
        }
        item->owner = NULL;
        item->xDD4_itemVar.foxblaster.owner = NULL;
        efLib_DestroyAll(item_gobj);
    }
    return true;
}

static inline void copy_jobj_scale(HSD_JObj* dst, HSD_JObj* src, Vec3* scale)
{
    scale->x = scale->y = scale->z = HSD_JObjGetScaleY(src);
    HSD_JObjSetScale(dst, scale);
}

/// @brief If blaster item exists and ? (ftCo_800BF228), set the item scale to
/// match the owner's
/// @param item_gobj
/// @return false
bool it_802AF064(HSD_GObj* item_gobj)
{
    if (item_gobj != NULL) {
        Item* it = GET_ITEM(item_gobj);
        if (it != NULL && it->xDD4_itemVar.foxblaster.owner != NULL) {
            if (ftCo_800BF228(it->xDD4_itemVar.foxblaster.owner) == 1) {
                Vec3 scale;
                HSD_GObj* owner = it->xDD4_itemVar.foxblaster.owner;
                copy_jobj_scale(GET_JOBJ(item_gobj), GET_JOBJ(owner), &scale);
            }
        }
    }
    return false;
}

/// @brief Does nothing
/// @param item_gobj
void it_802AF178(HSD_GObj* item_gobj) {}

/// @brief Does nothing
/// @param item_gobj
/// @return false
bool it_802AF17C(HSD_GObj* item_gobj)
{
    return false;
}

/// @brief Calls function it_8026B894
/// @param item_gobj
/// @param ref_gobj
void it_802AF184(Item_GObj* item_gobj, HSD_GObj* ref_gobj)
{
    // Remove all GObj interaction references from item
    // Returns whether or not the referenced_gobj was the #Item::owner.
    it_8026B894(item_gobj, ref_gobj);
}
