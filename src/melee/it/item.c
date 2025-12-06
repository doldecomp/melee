#include "item.h"

#include "it_266F.h"
#include "it_26B1.h"
#include "math.h"

#include "cm/camera.h"
#include "db/db.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/ftlib.h"
#include "gm/gm_unsplit.h"
#include "gr/grlib.h"
#include "gr/stage.h"
#include "it/inlines.h"
#include "it/it_2725.h"
#include "it/itcoll.h"
#include "it/types.h"

#include "lb/forward.h"

#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/class.h>
#include <baselib/debug.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>

/* 267130 */ static void Item_80267130(HSD_GObj* gobj, SpawnItem* spawnItem);
/* 2674AC */ static void Item_802674AC(SpawnItem* spawnItem);
/* 2675A8 */ static void Item_802675A8(HSD_GObj* gobj);
/* 2676F4 */ static void Item_802676F4(HSD_GObj* gobj);
/* 26784C */ static bool Item_8026784C(enum_t dropItem, int);
/* 267AA8 */ static void Item_80267AA8(HSD_GObj* gobj, SpawnItem* spawnItem);
/* 26814C */ static void Item_8026814C(HSD_GObj* gobj);
/* 2682F0 */ static bool Item_802682F0(HSD_GObj* gobj);
/* 268560 */ static void Item_80268560(HSD_GObj* gobj);
/* 26862C */ static HSD_GObj* Item_8026862C(SpawnItem* spawnItem);
/* 268BE0 */ static void Item_80268BE0(HSD_JObj* item_jobj,
                                       HSD_AnimJoint* anim_joint,
                                       HSD_MatAnimJoint* matanim_joint,
                                       HSD_ShapeAnimJoint* shapeanim_joint,
                                       Item* item_data);
/* 269528 */ static void Item_80269528(HSD_GObj* gobj);
/* 2696CC */ static bool Item_802696CC(HSD_GObj* gobj);
/* 269A9C */ static void Item_80269A9C(HSD_GObj* gobj);
/* 269B60 */ static void Item_80269B60(HSD_GObj* gobj);
/* 269BE4 */ static void Item_80269BE4(HSD_GObj* gobj);
/* 269C5C */ static void Item_80269C5C(HSD_GObj* gobj);
/* 269CC4 */ static void Item_80269CC4(HSD_GObj* gobj);
/* 269DC8 */ static bool Item_80269DC8(HSD_GObj* gobj);
/* 269F14 */ static bool Item_80269F14(HSD_GObj* gobj);
/* 26A0A0 */ static void Item_8026A0A0(HSD_GObj* gobj);
/* 26A0FC */ static void Item_8026A0FC(HSD_GObj* gobj);
/* 26A158 */ static void Item_8026A158(HSD_GObj* gobj);
/* 26A1E8 */ static void Item_8026A1E8(HSD_GObj* gobj);
/* 26A294 */ static void Item_8026A294(HSD_GObj* gobj);
/* 26A788 */ static void Item_8026A788(HSD_GObj* gobj);
/* 26A810 */ static void Item_8026A810(HSD_GObj* gobj);
/* 26B0B4 */ static void Item_8026B0B4(HSD_GObj* gobj);

/// Check if items are enabled
bool Item_80266F3C(void)
{
    if (gm_8016AE80() != -1) {
        return true;
    }

    return false;
}

/// Check to load ItCo.dat/usd
void Item_80266F70(void)
{
    it_8027870C(Item_80266F3C());
}

/// ItCo prefunction with 0
void Item_80266FA8(void)
{
    it_8027870C(false);
}

static HSD_ObjAllocData item_alloc_data;

static HSD_ObjAllocData item_dynamic_bones_alloc_data;

HSD_ObjAllocData item_link_alloc_data;
HSD_ObjAllocUnk Item_804A0C64;
HSD_ObjAllocUnk2 Item_804A0CCC;
S32Vec3 Item_804A0E24;

/// Init item struct?
void Item_80266FCC(void)
{
    HSD_ObjAllocInit(&item_alloc_data, sizeof(Item), 4);
    HSD_ObjAllocInit(&item_dynamic_bones_alloc_data, sizeof(DynamicBoneTable),
                     4);
    HSD_ObjAllocInit(&item_link_alloc_data, sizeof(ItemLink), 4);

    Item_804A0C64.x0 = 0;
    Item_804A0C64.x8 = 0;
    Item_804A0C64.x10 = 0;
    Item_804A0C64.x18 = 0;
    Item_804A0C64.x1C = 0;
    Item_804A0C64.x24 = 0;
    Item_804A0C64.x2C = 0;
    Item_804A0C64.x34 = 0;
    Item_804A0C64.x3C = 0;
    Item_804A0C64.x40 = 0;
    Item_804A0C64.x48 = 0;
    Item_804A0C64.x50 = 0;
    Item_804A0C64.x58 = 0;
    Item_804A0C64.x60 = 0;

    Item_804A0C64.x4 = it_804D6D28->x0;
    Item_804A0C64.xC = it_804D6D28->x4;
    Item_804A0C64.x14 = it_804D6D28->x8;
    Item_804A0C64.x20 = it_804D6D28->xC;
    Item_804A0C64.x28 = it_804D6D28->x10;
    Item_804A0C64.x30 = it_804D6D28->x14;
    Item_804A0C64.x38 = it_804D6D28->x18;
    Item_804A0C64.x44 = it_804D6D28->x1C;
    Item_804A0C64.x4C = it_804D6D28->x24;
    Item_804A0C64.x54 = it_804D6D28->x20;
    Item_804A0C64.x5C = it_804D6D28->x28;
    Item_804A0C64.x64 = it_804D6D28->x148;

    Item_804A0CCC.x154.b0 = true;
    Item_804A0CCC.x150 = 1;

    Item_804A0E24.x = -1;
    Item_804A0E24.y = -1;
    Item_804A0E24.z = 0;

    it_804D6D00 = -1;
    it_804D6D14 = 1;
    it_804D6D10 = 0;
    it_804D6D0C = 0;
    it_804D6D08 = 0;

    it_804A0E60.x8 = 0;
    it_804A0E50.x8 = 0;
    it_804A0E30.x4.x8 = 0;
    it_804A0E60.x0 = 0;
    it_804A0E50.x0 = 0;
    it_804A0E30.x4.x0 = 0;
}

static void ItUnkHoldKind(HSD_GObj* gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(gobj);

    switch (it->hold_kind) {
    case 4:
    case 5:
    case 6:
    case 7: {
        int temp_r3 = gm_8017E068();
        if (temp_r3 >= 0) {
            it->xC3C = it_804D6D28->x80_float[temp_r3];
        }
    }
    }
}

static void HSD_JObjSetScaleItem(Item* it, HSD_JObj* jobj, Vec3* scl)
{
    scl->x = scl->y = scl->z = it->scl;
    HSD_JObjSetScale(jobj, scl);
}

static inline void HSD_JObjSetFacingDirItem(HSD_JObj* jobj, Item* it)
{
    if (it->xDC8_word.flags.x19 == true) {
        HSD_JObjSetRotationY(jobj, M_PI / 2 * it->facing_dir);
    }
}

static void Item_80267130(HSD_GObj* gobj, SpawnItem* spawnItem)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    HSD_JObj* model = (HSD_JObj*) HSD_GObjGetHSDObj(gobj);

    item_data->pos = spawnItem->prev_pos;
    item_data->init_facing_dir = item_data->facing_dir = spawnItem->facing_dir;
    item_data->owner = spawnItem->x0_parent_gobj;

    {
        int facing_dir;

        if (item_data->facing_dir == -1.0F) {
            facing_dir = -1;
        } else {
            facing_dir = 1;
        }

        mpCollSetFacingDir(&item_data->x378_itemColl, facing_dir);
    }

    HSD_JObjSetFacingDirItem(model, item_data);
    it_80273500(gobj, &spawnItem->vel);

    item_data->x5CC_currentAnimFrame = 0.0f;
    item_data->x5D0_animFrameSpeed = 1.0f;

    it_802753BC(gobj, spawnItem->x3C_damage);
    it_802753DC(gobj);

    item_data->xC64_reflectGObj = NULL;
    item_data->xDCC_flag.b0 = false;

    item_data->xC90_absorbGObj = NULL;
    item_data->xD0C = 0;

    it_8026B390(gobj);
    item_data->xDC8_word.flags.x13 = false;

    if (spawnItem->x48_ground_or_air == GA_Air) {
        it_802762BC(item_data);
    } else {
        it_802762B0(item_data);
    }

    it_80275E98(gobj, spawnItem);
    it_80274DAC(gobj);
    HSD_JObjSetTranslate(model, &item_data->pos);
    it_80274658(gobj, it_804D6D28->x6C_float);
    it_802725D4(gobj);
    it_80271508(gobj, 0);
    it_80272280(gobj);

    item_data->on_accessory = NULL;
    item_data->touched = NULL;
    item_data->entered_hitlag = NULL;
    item_data->exited_hitlag = NULL;
    item_data->jumped_on = NULL;

    if (item_data->owner != NULL) {
        db_80225DD8(gobj, item_data->owner);
    } else {
        db_80225D64(gobj, item_data->owner);
    }

    it_8027B0C4(gobj, spawnItem);
    it_80279B64(item_data);
    ItUnkHoldKind(gobj);
}

/// Remove Camera Box
void Item_80267454(HSD_GObj* gobj)
{
    Item* item_data = gobj->user_data;

    if (item_data->xDCD_flag.b01 != 0 &&

        (item_data->x520_cameraBox != NULL))
    {
        Camera_800290D4(item_data->x520_cameraBox);
        item_data->x520_cameraBox = NULL;
        item_data->xDCD_flag.b01 = 0;
    }
}

static void Item_802674AC(SpawnItem* spawnItem)
{
    ItemKind kind = spawnItem->kind;

    if (kind == It_Kind_Foods) {
        spawnItem->hold_kind = 2;
        return;
    }

    if (kind == Pokemon_Random) {
        spawnItem->hold_kind = 3;
        return;
    }

    if (kind < It_Kind_L_Gun_Ray) {
        spawnItem->hold_kind = 0;
        return;
    }

    if (kind < It_Kind_Kuriboh) {
        spawnItem->hold_kind = 1;
        return;
    }

    if (kind < It_Kind_Octarock_Stone) {
        spawnItem->hold_kind = 6;
        return;
    }

    if (kind < It_Kind_Mario_Fire) {
        spawnItem->hold_kind = 7;
        return;
    }

    if (kind < It_Kind_Unk4) {
        spawnItem->hold_kind = 8;
        return;
    }

    if (kind == It_Kind_Unk4) {
        spawnItem->hold_kind = 12;
        return;
    }

    if (kind < Pokemon_Random) {
        spawnItem->hold_kind = 11;
        return;
    }

    if (kind < Pokemon_Chicorita_Leaf) {
        spawnItem->hold_kind = 9;
        return;
    }

    if (kind < It_Kind_Old_Kuri) {
        spawnItem->hold_kind = 10;
        return;
    }

    if (kind < It_Kind_Arwing_Laser) {
        spawnItem->hold_kind = 4;
        return;
    }

    spawnItem->hold_kind = 5;
}

static void Item_802675A8(HSD_GObj* gobj)
{
    Item* item_data = gobj->user_data;

    switch (item_data->hold_kind) {
    case 0:
        Item_804A0C64.x0--;
        break;
    case 1:
        Item_804A0C64.x8--;
        break;
    case 2:
        Item_804A0C64.x10--;
        break;
    case 3:
        Item_804A0C64.x58--;
        break;
    case 4:
        Item_804A0C64.x3C--;
        break;
    case 5:
        Item_804A0C64.x40--;
        break;
    case 6:
        Item_804A0C64.x2C--;
        break;
    case 7:
        Item_804A0C64.x34--;
        break;
    case 8:
        Item_804A0C64.x18--;
        break;
    case 9:
        Item_804A0C64.x1C--;
        break;
    case 10:
        Item_804A0C64.x24--;
        break;
    case 11:
        Item_804A0C64.x48--;
        break;
    case 12:
        Item_804A0C64.x50--;
        break;
    }

    if (gm_8018841C() && item_data->x18 == 1) {
        Item_804A0C64.x60--;
    }
}

static void Item_802676F4(HSD_GObj* gobj)
{
    Item* item_data = gobj->user_data;
    switch (item_data->hold_kind) {
    case 0:
        Item_804A0C64.x0++;

        if (item_data->kind == 34) {
            Item_804A0C64.x1C++;
        }

        break;
    case 1:
        Item_804A0C64.x8++;
        break;
    case 2:
        it_80274EE8(Item_804A0C64.x10++);
        break;
    case 3:
        Item_804A0C64.x58++;
        break;
    case 4:
        Item_804A0C64.x3C++;
        break;
    case 5:
        Item_804A0C64.x40++;
        break;
    case 6:
        Item_804A0C64.x2C++;
        break;
    case 7:
        Item_804A0C64.x34++;
        break;
    case 8:
        Item_804A0C64.x18++;
        break;
    case 10:
        Item_804A0C64.x24++;
        break;
    case 11:
        Item_804A0C64.x48++;
        break;
    case 12:
        Item_804A0C64.x50++;
        break;
    }

    if (gm_8018841C() && item_data->x18 == 1) {
        Item_804A0C64.x60++;
    }
}

static /// @remarks #Item_8026862C loads two integers into this,
       ///          but the second one goes _?
    bool
    Item_8026784C(enum_t dropItem, int _)
{
    bool result = false;

    switch (dropItem) {
    case 0:
        if (Item_804A0C64.x0 >= Item_804A0C64.x4) {
            result = true;
        }

        break;

    case 1:
        if (Item_804A0C64.x8 >= Item_804A0C64.xC) {
            result = true;
        }

        break;

    case 2:
        if (Item_804A0C64.x10 >= Item_804A0C64.x14) {
            result = true;
        }

        break;

    case 3:
        if (Item_804A0C64.x58 >= Item_804A0C64.x5C) {
            result = true;
        }

        break;

    case 5:
        if (Item_804A0C64.x40 >= Item_804A0C64.x44) {
            result = true;
        }

        break;

    case 7:
        if (Item_804A0C64.x34 >= Item_804A0C64.x38) {
            result = true;
        }

        break;

    case 9:
        if (Item_804A0C64.x1C > Item_804A0C64.x20) {
            Item_804A0C64.x1C--;
            result = true;
        }

        break;

    case 10:
        if (Item_804A0C64.x24 >= Item_804A0C64.x28) {
            result = true;
        }

        break;

    case 11:
        if (Item_804A0C64.x48 >= Item_804A0C64.x4C) {
            result = true;
        }

        break;

    case 12:
        if (Item_804A0C64.x50 >= Item_804A0C64.x54) {
            result = true;
        }
    }

    return result;
}

void Item_80267978(HSD_GObj* gobj)
{
    Item* item_data = gobj->user_data;
    if (item_data->kind < It_Kind_Kuriboh) {
        // Common items
        item_data->xC4_article_data = it_804D6D24[item_data->kind];
        item_data->xB8_itemLogicTable = &it_803F14C4[item_data->kind];
    } else if (item_data->kind < Pokemon_Tosakinto) {
        // Character items
        int idx = item_data->kind - It_Kind_Kuriboh;
        item_data->xC4_article_data = it_804D6D38[idx];
        item_data->xB8_itemLogicTable = &it_803F3100[idx];
    } else if (item_data->kind < It_Kind_Old_Kuri) {
        // Pokemon
        int idx = item_data->kind - Pokemon_Tosakinto;
        item_data->xC4_article_data = it_804D6D30[idx];
        item_data->xB8_itemLogicTable = &it_803F23CC[idx];
    } else {
        // Stage items
        int idx = item_data->kind - It_Kind_Old_Kuri;
        item_data->xC4_article_data = it_804A0F60[idx];
        item_data->xB8_itemLogicTable = &it_803F4D20[idx];
        if (item_data->xC4_article_data == NULL) {
            OSReport("not found zako model data! check ground dat file!\n");
            __assert("item.c", 686, "0");
        }
    }
    item_data->xBC_itemStateContainer = item_data->xB8_itemLogicTable->states;
}

static void Item_80267AA8(HSD_GObj* gobj, SpawnItem* spawnItem)
{
    ItemAttr* item_attr;
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    item_data->kind = spawnItem->kind;
    item_data->hold_kind = spawnItem->hold_kind;
    item_data->x18 = spawnItem->x10;
    item_data->x1C = it_804D6D10++;
    item_data->entity = gobj;
    Item_80267978(gobj);
    item_data->msid = -1;
    item_data->xC8_joint =
        item_data->xC4_article_data->x10_modelDesc->x0_joint;
    item_data->xCC_item_attr = item_data->xC4_article_data->x0_common_attr;
    item_data->owner = NULL;
    item_data->xDC8_word.flags.x0 = 0;
    item_data->ecb_lock = -1;
    item_data->xDC4 = 0;
    item_data->xDC8_word.flags.xF = 0;
    item_data->xCC4 = 0;
    item_data->xDCF_flag.b6 = 0;
    item_data->xDCF_flag.b7 = 0;
    item_data->xCB0_source_ply = 6;
    item_data->xCB4 = -1;
    item_data->xC38 = -1;
    item_data->xCE0.z = 0.0f;
    item_data->xCE0.y = 0.0f;
    item_data->xCE0.x = 0.0f;
    item_data->xCD4.z = 0.0f;
    item_data->xCD4.y = 0.0f;
    item_data->xCD4.x = 0.0f;
    item_data->xDD0_flag.b1 = 0;
    item_data->xDC8_word.flags.x14 = 0;
    item_data->xDC8_word.flags.xE = 0;
    item_data->xCEC_fighterGObj = NULL;
    item_data->xCF0_itemGObj = NULL;
    item_data->xCF4_fighterGObjUnk = NULL;
    item_data->toucher = NULL;
    item_data->xC64_reflectGObj = NULL;
    item_data->xCFC = 0;
    item_data->atk_victim = 0;
    item_data->grab_victim = 0;
    item_data->xCCC_incDamageDirection = 0.0f;
    item_data->xCB8_outDamageDirection = 0.0f;
    item_data->xC68 = 0.0f;
    item_data->xCD0 = 0.0f;
    it_80275158(gobj, it_804D6D28->x30);
    item_data->xDD0_flag.b3 = false;
    item_data->spin_spd = item_data->xCC_item_attr->xC_spin_speed;
    item_data->xDC8_word.flags.x19 = item_data->xCC_item_attr->x1_3;
    item_data->xDC8_word.flags.x17 = item_data->xCC_item_attr->x1_1;
    item_attr = item_data->xCC_item_attr;
    item_data->xBCC_unk = item_attr->x30_unk;
    item_data->xBD4_grabRange = item_attr->x38_grab_range;
    item_data->xDC8_word.flags.x1A = item_data->xCC_item_attr->x1_4;
    item_attr = item_data->xCC_item_attr;
    item_data->xBEC = item_attr->x20;
    item_attr = item_data->xCC_item_attr;
    item_data->xBDC = item_attr->x20;
    item_data->xDC8_word.flags.x1C = 1;
    item_data->xDC8_word.flags.x1D = 1;
    item_data->xDC8_word.flags.x1E = 1;
    item_attr = item_data->xCC_item_attr;
    item_data->xC1C = item_attr->x40;
    item_data->xC0C = item_data->xC1C;
    item_data->xBFC = item_data->xC0C;
    item_data->xDC8_word.flags.xC = item_data->xCC_item_attr->x1_5;
    item_data->xDC8_word.flags.xD = 1;
    item_data->xDCD_flag.b01 = item_data->xCC_item_attr->x1_67_cam_kind;
    item_data->xDCE_flag.b3 = 0;
    item_data->xD54_throwNum = 0;
    item_data->xD50_landNum = 0;
    item_data->xD58 = 0;
    item_data->xD5C = 2;
    item_data->xDCC_flag.b3 = 1;
    item_data->xDCC_flag.b4567 = 15;
    item_data->xAC4_ignoreItemID = spawnItem->x40;
    item_data->destroy_type = 4;
    item_data->xDCE_flag.b5 = 0;
    item_data->xDCE_flag.b4 = 0;
    item_data->xC54 = 0.0f;
    item_data->xC58.x = 0.0f;
    item_data->xC58.x = 0.0f;
    item_data->xC58.x = 0.0f;
    item_data->xDC8_word.flags.x9 = 0;
    item_data->xDC8_word.flags.x3 = 0;
    item_data->xDC8_word.flags.x4 = 0;
    item_data->xDC8_word.flags.x5 = 0;
    item_data->xDC8_word.flags.x6 = 0;
    item_data->xDC8_word.flags.x7 = 0;
    item_data->xDC8_word.flags.x8 = 0;
    item_data->xDD0_flag.b5 = 0;
    item_data->xD09 = (s8) 0;
    item_data->xDD0_flag.b4 = 0;
    item_data->xCA8 = 0;
    item_data->xCBC_hitlagFrames = 0.0f;
    item_data->xCC0 = 0.0f;
    item_data->xDC8_word.flags.xA = 0;
    item_data->xDC8_word.flags.xB = 0;
    item_data->xDCC_flag.b1 = 0;
    item_data->xC70 = 1.0f;
    item_data->xC6C = 1.0f;
    item_data->xDCC_flag.b2 = 0;
    item_data->xDD0_flag.b0 = false;
    item_data->xDCE_flag.b6 = false;
    item_data->xDCF_flag.b0 = false;
    item_data->xDCF_flag.b1 = false;
    item_data->xDCF_flag.b2 = false;
    item_data->xDD1_flag.b0 = false;
    item_data->xDCE_flag.b7 = 1;
    item_data->scl = item_data->xCC_item_attr->x60_scale;
    item_data->x3C = 0.0f;
    item_data->xDCD_flag.b3 = false;
    item_data->xDCD_flag.b4 = false;
    item_data->xDD0_flag.b7 = false;
    item_data->xBC0 = 0;
    item_data->xDD1_flag.b1 = false;
    item_data->xDCD_flag.b2 = false;
    item_data->xD6C = -1;
    item_data->sfx_unk2 = SFX_NONE;
    item_data->sfx_unk1 = SFX_NONE;
    item_data->xD70 = item_data->xCC_item_attr->x6C;
    item_data->xD74 = item_data->xCC_item_attr->x70;
    item_data->xD78 = item_data->xCC_item_attr->x74;
    item_data->destroy_sfx = item_data->xCC_item_attr->destroy_sfx;
    item_data->xD80 = item_data->xCC_item_attr->x7C;
    item_attr = item_data->xCC_item_attr;
    item_data->xD84 = item_attr->x80;

    it_80275474(gobj);
    it_80275504(gobj);
    it_80274EF8(gobj);

    if (ftLib_80086960(spawnItem->x0_parent_gobj)) {
        item_data->xDC8_word.flags.x1 = false;
    } else {
        item_data->xDC8_word.flags.x1 = true;
    }

    item_data->x5C8 = 0;
    item_data->xBC7 = 0;
    item_data->xBC6 = 0;
    item_data->xBC5 = 0;
    item_data->xBC4 = 0;
    item_data->x5C9 = 255;

    it_80279B64(item_data);

    item_data->xDCF_flag.b3 = false;
    item_data->xDCF_flag.b4 = false;
    item_data->xDCF_flag.b5 = false;

    item_data->xDAA_byte = 1;

    if (db_ShowItemPickupRange()) {
        item_data->xDAA_flag.b4 = true;
    }

    if (spawnItem->x0_parent_gobj == NULL) {
        item_data->x20_team_id = -1;
    } else if (ftLib_80086960(spawnItem->x0_parent_gobj)) {
        item_data->x20_team_id = ftLib_80086EB4(spawnItem->x0_parent_gobj);
    } else if (it_80272D1C(spawnItem->x0_parent_gobj)) {
        item_data->x20_team_id = it_8026B7B0(spawnItem->x0_parent_gobj);
    } else {
        item_data->x20_team_id = -1;
    }
}

extern void PSMTXIdentity(Mtx); /* extern */

/// Setup Item JObj
void Item_802680CC(HSD_GObj* gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);

    if (item_data->xC8_joint != NULL) {
        HSD_JObj* jobj = HSD_JObjLoadJoint(item_data->xC8_joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    } else {
        HSD_JObj* jobj = HSD_JObjAlloc();
        PSMTXIdentity(jobj->mtx);
        jobj->scl = NULL;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    }
}

extern HSD_DObj* HSD_JObjGetDObj(HSD_JObj*);
extern void* it_803F1F90[];

static void Item_8026814C(HSD_GObj* gobj)
{
    u8 _[8];
    HSD_MObj* temp_r0;
    HSD_DObj* var_r0;
    HSD_JObj* var_r0_2;
    HSD_JObj* var_r30;
    HSD_DObj* var_r29;
    HSD_JObj* var_r3;

    var_r30 = (HSD_JObj*) HSD_GObjGetHSDObj(gobj);
    while (var_r30 != NULL) {
        var_r29 = HSD_JObjGetDObj(var_r30);
    loop_2:
        if (var_r29 != NULL) {
            temp_r0 = var_r29->mobj;
            if (temp_r0 != NULL) {
                hsdChangeClass(temp_r0, &it_803F1F90);
            }
            var_r29 = var_r0 = (var_r29 != NULL) ? var_r29->next : NULL;
            goto loop_2;
        }
        if (var_r30 == NULL) {
            var_r0_2 = NULL;
        } else {
            var_r0_2 = var_r30->child;
        }
        if (var_r0_2 != NULL) {
            var_r30 = var_r0_2 = (var_r30 == NULL) ? NULL : var_r30->child;
        } else {
            var_r0_2 = (var_r30 == NULL) ? NULL : var_r30->next;
            if (var_r0_2 != NULL) {
                var_r30 = var_r0_2 = (var_r30 == NULL) ? NULL : var_r30->next;
            } else {
            loop_25:
                var_r0_2 = (var_r30 == NULL) ? NULL : var_r30->parent;
                if (var_r0_2 == NULL) {
                    var_r30 = NULL;
                } else {
                    var_r3 = (var_r30 == NULL) ? NULL : var_r30->parent;
                    var_r0_2 = (var_r3 == NULL) ? NULL : var_r3->next;
                    if (var_r0_2 != NULL) {
                        var_r3 = (var_r30 == NULL) ? NULL : var_r30->parent;
                        var_r30 = var_r0_2 =
                            (var_r3 == NULL) ? NULL : var_r3->next;
                    } else {
                        var_r30 = var_r0_2 =
                            (var_r30 == NULL) ? NULL : var_r30->parent;
                        goto loop_25;
                    }
                }
            }
        }
    }
}

static /// @todo Needs some serious cleaning.
    bool
    Item_802682F0(HSD_GObj* gobj)
{
    s32 var_r4;
    Item* item_data;
    HSD_JObj* var_r0;
    HSD_JObj* var_r3;
    HSD_JObj* var_r3_2;
    HSD_JObj* var_r5;

    item_data = (Item*) HSD_GObjGetUserData(gobj);
    if (item_data->xC4_article_data->x10_modelDesc->x4_bone_count != 0) {
        item_data->xBBC_dynamicBoneTable =
            HSD_ObjAlloc(&item_dynamic_bones_alloc_data);
        if (item_data->xBBC_dynamicBoneTable == NULL) {
            return false;
        }
        var_r5 = gobj->hsd_obj;
        var_r4 = 0;
        while (var_r5 != NULL) {
            (item_data->xBBC_dynamicBoneTable->bones[var_r4]) = var_r5;
            var_r4++;
            var_r0 = (var_r5 == NULL) ? NULL : var_r5->child;
            if (var_r0 != NULL) {
                var_r5 = var_r0 = (var_r5 == NULL) ? NULL : var_r5->child;
            } else {
                var_r0 = (var_r5 == NULL) ? NULL : var_r5->next;
                if (var_r0 != NULL) {
                    var_r5 = var_r0 = (var_r5 == NULL) ? NULL : var_r5->next;
                } else {
                loop_20:
                    var_r0 = (var_r5 == NULL) ? NULL : var_r5->parent;
                    if (var_r0 == NULL) {
                        var_r5 = NULL;
                    } else {
                        var_r3 = (var_r5 == NULL) ? NULL : var_r5->parent;
                        var_r0 = (var_r3 == NULL) ? NULL : var_r3->next;
                        if (var_r0 != NULL) {
                            var_r3_2 =
                                (var_r5 == NULL) ? NULL : var_r5->parent;
                            var_r5 = var_r0 =
                                (var_r3_2 == NULL) ? NULL : var_r3_2->next;
                        } else {
                            var_r5 = var_r0 =
                                (var_r5 == NULL) ? NULL : var_r5->parent;
                            goto loop_20;
                        }
                    }
                }
            }
        }
    } else {
        item_data->xBBC_dynamicBoneTable = NULL;
    }
    return true;
}

/// Set item model scale
void Item_8026849C(HSD_GObj* gobj)
{
    HSD_JObj* temp_jobj = (HSD_JObj*) HSD_GObjGetHSDObj(gobj);
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    f32 tmp = item_data->scl;
    Vec3 sp14;
    sp14.x = sp14.y = sp14.z = tmp;
    HSD_JObjSetScale(temp_jobj, &sp14);
}

static void Item_80268560(HSD_GObj* gobj)
{
    int i;
    Item* ip = GET_ITEM(gobj);
    Article* article_data = ip->xC4_article_data;
    if (article_data->x14_dynamics == NULL) {
        ip->x374_dynamicBonesNum = 0;
        ip->xB68 = 0;
        return;
    }
    ip->x374_dynamicBonesNum = article_data->x14_dynamics->count;
    for (i = 0; i < article_data->x14_dynamics->count; i++) {
        BoneDynamicsDesc* desc = &article_data->x14_dynamics->dyn_descs[i];
        HSD_JObj* jobj = ip->xBBC_dynamicBoneTable->bones[desc->bone_id];
        lb_8000FD48(jobj, &ip->xD4_dynamicBones[i].dyn_desc,
                    desc->dyn_desc.count);
        ip->xD4_dynamicBones[i].skeleton = jobj;
        ip->xD4_dynamicBones[i].flags = 0;
        lb_80011710(&article_data->x14_dynamics->dyn_descs[i].dyn_desc,
                    &ip->xD4_dynamicBones[i].dyn_desc);
    }
}

extern void ftLib_8008702C(s32);
extern struct sdata_ItemGXLink it_803F1418[];
extern struct sdata_ItemGXLink it_803F2310[];
extern struct sdata_ItemGXLink it_803F2F28[];
extern struct sdata_ItemGXLink it_803F4CA8[];

static void foobar(HSD_GObj* gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(gobj);
    switch (it->hold_kind) {
    case 0:
    case 6:
        if (it->xD0C == 2) {
            it->xDD0_flag.b7 = 1;
        }
        it->xD40 = it_804D6D28->x2C;
        it->xDD0_flag.b6 = 1;
        it_802756D0(gobj);
        it_80279B88(it, 3, 0);
        break;

    default:
        it->xD40 = 0.0f;
        it->xDD0_flag.b6 = 0;
    }
}

static void foobar2(HSD_GObj* gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(gobj);
    // Check if item is a character item with an owner
    if (it->kind >= It_Kind_Mario_Fire && it->kind < It_Kind_Unk4 &&
        ftLib_80086960(it->owner))
    {
        it->xDC8_word.flags.xE = 1;
        it->ecb_lock = ftLib_800872A4(it->owner);
        ftLib_8008702C(it->ecb_lock);
    }
}

static void foobar3(HSD_GObj* gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(gobj);
    CmSubject* cam_box;
    if (it->xDCD_flag.b01 != 0) {
        if (it->xDCD_flag.b01 == 1) {
            it->x520_cameraBox = Camera_80029044(0);
        } else {
            it->x520_cameraBox = Camera_80029044(2);
        }
        cam_box = it->x520_cameraBox;
        if (cam_box != NULL) {
            cam_box->x40.x = it_804D6D28->x14C;
            cam_box->x40.y = it_804D6D28->x150;
            cam_box->x48.x = it_804D6D28->x154;
            cam_box->x48.y = it_804D6D28->x158;
        }
    }
}

static HSD_GObj* Item_8026862C(SpawnItem* spawnItem)
{
    HSD_GObj* gobj;
    void* user_data;

    if (Item_8026784C(spawnItem->hold_kind, spawnItem->kind) != 0) {
        return NULL;
    }
    gobj = GObj_Create(HSD_GOBJ_CLASS_ITEM, 9, 0);
    if (gobj == NULL) {
        return NULL;
    }
    if (spawnItem->kind < It_Kind_Kuriboh) {
        // Common items
        GObj_SetupGXLink(gobj, it_803F1418[spawnItem->kind].x0_renderFunc, 6,
                         0);
    } else if (spawnItem->kind < Pokemon_Tosakinto) {
        // Character items
        int idx = spawnItem->kind - It_Kind_Kuriboh;
        GObj_SetupGXLink(gobj, it_803F2F28[idx].x0_renderFunc, 6, 0);
    } else if (spawnItem->kind < It_Kind_Old_Kuri) {
        // Pokemon
        int idx = spawnItem->kind - Pokemon_Tosakinto;
        GObj_SetupGXLink(gobj, it_803F2310[idx].x0_renderFunc, 6, 0);
    } else {
        // Stage items
        int idx = spawnItem->kind - It_Kind_Old_Kuri;
        GObj_SetupGXLink(gobj, it_803F4CA8[idx].x0_renderFunc, 6, 0);
    }
    user_data = HSD_ObjAlloc(&item_alloc_data);
    if (user_data == NULL) {
        HSD_GObjPLink_80390228(gobj);
        return NULL;
    }
    GObj_InitUserData(gobj, 6, Item_OnUserDataRemove, user_data);
    Item_80267AA8(gobj, spawnItem);
    Item_802680CC(gobj);
    if (Item_802682F0(gobj) != false) {
        Item_8026814C(gobj);
        Item_8026849C(gobj);
        it_8027163C(gobj);
        Item_80268560(gobj);
        HSD_GObjProc_8038FD54(gobj, Item_802693E4, 0);
        HSD_GObjProc_8038FD54(gobj, Item_80269528, 1);
        HSD_GObjProc_8038FD54(gobj, Item_802697D4, 4);
        HSD_GObjProc_8038FD54(gobj, Item_80269978, 5);
        HSD_GObjProc_8038FD54(gobj, Item_80269A9C, 9);
        HSD_GObjProc_8038FD54(gobj, Item_80269B60, 11);
        HSD_GObjProc_8038FD54(gobj, Item_80269BE4, 12);
        HSD_GObjProc_8038FD54(gobj, Item_80269C5C, 13);
        HSD_GObjProc_8038FD54(gobj, Item_8026A294, 14);
        HSD_GObjProc_8038FD54(gobj, Item_8026A788, 16);
        Item_80267130(gobj, spawnItem);
        Item_8026A810(gobj);
        foobar(gobj);
        Item_802676F4(gobj);
        foobar2(gobj);
        foobar3(gobj);
    } else {
        HSD_GObjPLink_80390228(gobj);
        return NULL;
    }
    return gobj;
}

/// Item spawn prefunction - spawn airborne
HSD_GObj* Item_80268B18(SpawnItem* spawnItem)
{
    spawnItem->x48_ground_or_air = GA_Air;
    spawnItem->x10 = 0;
    Item_802674AC(spawnItem);
    return Item_8026862C(spawnItem);
}

/// Item spawn prefunction - spawn grounded
HSD_GObj* Item_80268B5C(SpawnItem* spawnItem)
{
    spawnItem->x48_ground_or_air = GA_Ground;
    spawnItem->x10 = 0;
    Item_802674AC(spawnItem);
    return Item_8026862C(spawnItem);
}

/// Item spawn prefunction - spawn grounded and toggle unknown true
void Item_80268B9C(SpawnItem* spawnItem)
{
    spawnItem->x48_ground_or_air = GA_Ground;
    spawnItem->x10 = 1;
    Item_802674AC(spawnItem);
    Item_8026862C(spawnItem);
}

static void Item_80268BE0(HSD_JObj* item_jobj, HSD_AnimJoint* anim_joint,
                          HSD_MatAnimJoint* matanim_joint,
                          HSD_ShapeAnimJoint* shapeanim_joint, Item* item_data)
{
    void* functionArg1;
    void* functionArg2;
    void* functionArg3;

    s32 temp_r0;

    if (item_jobj != NULL) {
        if (anim_joint != NULL) {
            for (temp_r0 = 0; temp_r0 < item_data->x374_dynamicBonesNum;
                 temp_r0++)
            {
                if (item_jobj == item_data->xD4_dynamicBones[temp_r0].skeleton)
                {
                    if (anim_joint->next != NULL) {
                        functionArg1 = NULL;
                        functionArg2 = NULL;
                        functionArg3 = NULL;
                        if (anim_joint != NULL) {
                            functionArg1 = anim_joint->next;
                        }
                        if (matanim_joint != NULL) {
                            functionArg2 = matanim_joint->next;
                        }
                        if (shapeanim_joint != NULL) {
                            functionArg3 = shapeanim_joint->next;
                        }
                        Item_80268BE0(item_jobj->next, functionArg1,
                                      functionArg2, functionArg3, item_data);
                    }
                    return;
                }
            }
        }
        HSD_JObjAddAnim(item_jobj, anim_joint, matanim_joint, shapeanim_joint);
        if (item_jobj->child != NULL) {
            functionArg1 = NULL;
            functionArg2 = NULL;
            functionArg3 = NULL;
            if (anim_joint != NULL) {
                functionArg1 = anim_joint->child;
            }
            if (matanim_joint != NULL) {
                functionArg2 = matanim_joint->child;
            }
            if (shapeanim_joint != NULL) {
                functionArg3 = shapeanim_joint->child;
            }
            Item_80268BE0(item_jobj->child, functionArg1, functionArg2,
                          functionArg3, item_data);
        }
        if (item_jobj->next != NULL) {
            functionArg1 = NULL;
            functionArg2 = NULL;
            functionArg3 = NULL;
            if (anim_joint != NULL) {
                functionArg1 = anim_joint->next;
            }
            if (matanim_joint != NULL) {
                functionArg2 = matanim_joint->next;
            }
            if (shapeanim_joint != NULL) {
                functionArg3 = shapeanim_joint->next;
            }
            Item_80268BE0(item_jobj->next, functionArg1, functionArg2,
                          functionArg3, item_data);
        }
    }
}

/// Unk Item AObj-related function
void Item_80268D34(HSD_GObj* gobj, struct ItemStateDesc* itemStateDesc)
{
    HSD_JObj* item_jobj = (HSD_JObj*) HSD_GObjGetHSDObj(gobj);
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    HSD_JObjRemoveAnimAll(item_jobj);
    if (item_data->xC8_joint != NULL) {
        UNK_T bonestruct_arg;
        if (item_jobj == NULL) {
            bonestruct_arg = NULL;
        } else {
            bonestruct_arg = item_jobj->child;
        }
        lb_8000B804(bonestruct_arg, item_data->xC8_joint->child);
    }
    Item_80268BE0(item_jobj, itemStateDesc->x0_anim_joint,
                  itemStateDesc->x4_matanim_joint,
                  itemStateDesc->x8_parameters, item_data);
    lb_8000BA0C(item_jobj, item_data->x5D0_animFrameSpeed);
    HSD_JObjReqAnimAll(item_jobj, 0.0f);
}

/// Advance item animation?
void Item_80268DD4(HSD_GObj* gobj, f32 frame)
{
    HSD_JObj* item_jobj;
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    item_jobj = (HSD_JObj*) HSD_GObjGetHSDObj(gobj);
    lb_8000BA0C(item_jobj, item_data->x5D0_animFrameSpeed);
    HSD_JObjReqAnimAll(item_jobj, frame);
    HSD_JObjAnimAll(item_jobj);
    item_data->x5CC_currentAnimFrame = lbGetJObjCurrFrame(item_jobj);
}

/// Copy item script
void Item_80268E40(Item* item_data, struct ItemStateDesc* itemStateDesc)
{
    item_data->x524_cmd.u = itemStateDesc->xC_script;
    item_data->x524_cmd.loop_count = 0;
    item_data->x524_cmd.timer = 0.0f;
}

extern struct Fighter_804D653C_t* it_804D6D04;

// Change item state
void Item_80268E5C(HSD_GObj* gobj, enum_t msid, Item_StateChangeFlags flags)
{
    Vec3 sp4C;
    Vec3 scl;
    ItemStateTable* temp_r30;
    ItemStateDesc* temp_r29;

    u8 _[12];

    HSD_JObj* item_jobj1_2;

    UNK_T new_var;
    UNK_T new_var2;
    UNK_T new_var3;
    Item* item_data3;
    HSD_JObj* item_jobj;
    Item* item_data;
    ItemAttr* item_attr;
    ItemStateDesc* temp_r23;
    s32 temp_r0;

    item_jobj = (HSD_JObj*) HSD_GObjGetHSDObj(gobj);
    item_data = (Item*) HSD_GObjGetUserData(gobj);

    item_data->msid = msid;
    item_data->xDC8_word.flags.x14 = 0;
    HSD_JObjSetTranslate(gobj->hsd_obj, &item_data->pos);
    efAsync_80067624(gobj, &item_data->xBC0);

    if (item_data->xDC8_word.flags.x2 == 1) {
        it_8026BDCC(gobj);
        it_80274EF8(gobj);
    }

    if ((flags & ITEM_MODEL_UPDATE)) {
        it_80274740(gobj);
    }

    if (!(flags & ITEM_COLANIM_PRESERVE) &&
        it_804D6D04[item_data->x548_colorOverlay.x28_colanim.i].unk5 != 0)
    {
        it_80279BBC(item_data);
    }

    if (!(flags & ITEM_SFX_PRESERVE)) {
        Item_8026B074(item_data);
    }

    HSD_JObjSetFacingDirItem(item_jobj, item_data);

    if ((flags & ITEM_DROP_UPDATE)) {
        item_data->xC40 = item_data->xC44;
    } else {
        item_data->xC40 = 1.0F;
    }

    if (!(flags & ITEM_HIT_PRESERVE) && item_data->xDC8_word.flags.x16) {
        it_802725D4(gobj);
    }

    item_data->xCC8_knockback = 0.0F;
    temp_r30 = (new_var = &item_data->xBC_itemStateContainer[msid]);
    item_data->anim_id = temp_r30->anim_id;
    item_data->x5CC_currentAnimFrame = 0.0F;
    temp_r0 = item_data->anim_id;

    if (temp_r0 != -1) {
        item_data->xD0_itemStateDesc =
            (temp_r23 =
                 (temp_r29 =
                      (new_var2 = &item_data->xC4_article_data->xC_itemStates
                                       ->x0_itemStateDesc[temp_r0])));

        temp_r23 = (new_var3 = item_data->xD0_itemStateDesc);

        if (temp_r23 != NULL && (flags & ITEM_ANIM_UPDATE)) {
            Item_80268D34(gobj, temp_r23);

            if ((flags & ITEM_UNK_UPDATE)) {
                item_jobj1_2 = gobj->hsd_obj;
                item_data3 = GetItemData(gobj);
                item_data3->scl = item_data3->xCC_item_attr->x60_scale;
                HSD_JObjSetScaleItem(item_data3, item_jobj1_2, &sp4C);
                item_attr = item_data3->xCC_item_attr;
                item_data3->xBCC_unk = item_attr->x30_unk;
                item_data3->xBD4_grabRange = item_attr->x38_grab_range;
                item_data3->xBEC = item_data3->xCC_item_attr->x20;
                item_data3->xBDC = item_data3->xCC_item_attr->x20;
            } else {
                HSD_JObjSetScaleItem(gobj->user_data, gobj->hsd_obj, &scl);
            }

            item_data->x524_cmd.u = temp_r29->xC_script;
            item_data->x524_cmd.loop_count = 0;
            item_data->x524_cmd.timer = 0.0F;
        } else if (temp_r23 != NULL && (flags & ITEM_CMD_UPDATE)) {
            item_data->x524_cmd.u = temp_r29->xC_script;
            item_data->x524_cmd.loop_count = 0;
            item_data->x524_cmd.timer = 0.0f;
        }

        HSD_JObjAnimAll(item_jobj);
        it_80279BE0(gobj);
        it_802799E4(gobj);
    } else {
        HSD_JObjRemoveAnimAll(item_jobj);
        item_data->x524_cmd.u = NULL;
    }

    item_data->animated = temp_r30->animated;
    item_data->physics_updated = temp_r30->physics_updated;
    item_data->collided = temp_r30->collided;
    item_data->on_accessory = NULL;
    item_data->touched = NULL;
    item_data->entered_hitlag = NULL;
    item_data->exited_hitlag = NULL;
    item_data->jumped_on = NULL;

    item_data->xDD0_flag.b5 = false;
    item_data->xD09 = 0;

    it_802714C0(gobj);
}

void Item_802693E4(HSD_GObj* gobj)
{
    Item* item_data = gobj->user_data;
    if (item_data->xDC8_word.flags.x5 != 0) {
        Item_8026A0A0(gobj);
        item_data->xDC8_word.flags.x5 = 0;
    }
    if (item_data->xDC8_word.flags.x6 != 0) {
        Item_8026A0FC(gobj);
        item_data->xDC8_word.flags.x6 = 0;
    }
    if (item_data->xCBC_hitlagFrames > 0.0f) {
        item_data->xCBC_hitlagFrames -= 1.0f;
        if (item_data->xCBC_hitlagFrames <= 0.0f) {
            item_data->xCBC_hitlagFrames = 0.0f;
            item_data->xDC8_word.flags.xB = 0;
            item_data->xDC8_word.flags.xA = 0;
            if ((item_data->xDC8_word.flags.x8 == 0) &&
                (item_data->xDC8_word.flags.x7 == 0))
            {
                Item_8026A1E8(gobj);
            }
        }
    }
}

/// Advance item animation + script?
void Item_802694CC(HSD_GObj* gobj)
{
    HSD_JObj* item_jobj = (HSD_JObj*) HSD_GObjGetHSDObj(gobj);
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    HSD_JObjAnimAll(item_jobj);
    item_data->x5CC_currentAnimFrame = lbGetJObjCurrFrame(item_jobj);
    it_802799E4(gobj);
}

static void Item_80269528(HSD_GObj* gobj)
{
    u8 _[8];
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    if (item_data->xDC8_word.flags.x9 == 0) {
        Item_802694CC(gobj);
        if (item_data->animated != NULL && item_data->animated(gobj)) {
            item_data->destroy_type = 0;
            Item_8026A8EC(gobj);
            return;
        }
    }
    if (item_data->xDD0_flag.b6 != 0) {
        item_data->xD40 -= 1.0f;
        if (item_data->xD40 <= 0.0f) {
            item_data->xDD0_flag.b6 = 0;
            item_data->xD40 = 0.0f;
            it_80279BBC(item_data);
            if (item_data->xDD0_flag.b7 == 0) {
                it_802756E0(gobj);
            }
        }
    }
    if (item_data->xDC8_word.flags.x15 != 0 &&
        item_data->kind < It_Kind_L_Gun_Ray && !item_data->xDD0_flag.b3)
    {
        item_data->xD44_lifeTimer -= 1.0f;
        if (item_data->xD44_lifeTimer <= 0.0f) {
            item_data->destroy_type = 0;
            Item_8026A8EC(gobj);
            return;
        }
        if (item_data->xD44_lifeTimer <= it_804D6D28->x34) {
            it_802728C8(gobj);
        }
    }
    it_802721B8(gobj);
    it_80272298(gobj);
    it_80279BE0(gobj);
}

static bool Item_802696CC(HSD_GObj* gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    if ((item_data->xDCC_flag.b4567 & 8) &&
        item_data->pos.x > Stage_GetBlastZoneRightOffset())
    {
        item_data->destroy_type = 3;
        Item_8026A8EC(gobj);
        return true;
    }
    if ((item_data->xDCC_flag.b4567 & 4) &&
        item_data->pos.x < Stage_GetBlastZoneLeftOffset())
    {
        item_data->destroy_type = 3;
        Item_8026A8EC(gobj);
        return true;
    }
    if ((item_data->xDCC_flag.b4567 & 1) && item_data->pos.y > 10000.0f) {
        item_data->destroy_type = 3;
        Item_8026A8EC(gobj);
        return true;
    }
    if ((item_data->xDCC_flag.b4567 & 2) &&
        item_data->pos.y < Stage_GetBlastZoneBottomOffset())
    {
        item_data->destroy_type = 3;
        Item_8026A8EC(gobj);
        return true;
    }
    return false;
}

void Item_802697D4(HSD_GObj* gobj)
{
    Vec3 sp1C;
    u8 _[12];

    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    if (item_data->xDC8_word.flags.x9 == 0 &&
        item_data->physics_updated != NULL)
    {
        item_data->physics_updated(gobj);
    }
    if (item_data->xDC8_word.flags.x13 == 0) {
        if (item_data->xDC8_word.flags.x9 == 0) {
            PSVECAdd(&item_data->x40_vel, &item_data->x70_nudge, &sp1C);
            if ((item_data->ground_or_air == 0) &&
                (item_data->xDCD_flag.b3 == 0))
            {
                it_8027737C(gobj, &sp1C);
            }
            PSVECAdd(&item_data->pos, &sp1C, &item_data->pos);
        }
        if (item_data->xDCC_flag.b3 == 1 &&
            (item_data->xDCC_flag.b4567 & 0xF) && Item_802696CC(gobj))
        {
            return;
        }
        if (item_data->xD3C_spinSpeed && item_data->ground_or_air == 1) {
            it_80274A64(gobj);
        }
    }
    if ((item_data->xDD1_flag.b1 != 0) && (item_data->ground_or_air == 1)) {
        grLib_801C9E60(&item_data->x58_vec_unk);
    }
    PSVECAdd(&item_data->pos, &item_data->x58_vec_unk, &item_data->pos);
    it_80273484(gobj);
    if (item_data->ground_or_air == 0) {
        if ((item_data->xDCE_flag.b3 != 0) && (it_8026D604(gobj) != 0)) {
            mpGetSpeed(item_data->xC30, &item_data->pos,
                       &item_data->x64_vec_unk2);
        } else {
            mpGetSpeed(item_data->x378_itemColl.floor.index, &item_data->pos,
                       &item_data->x64_vec_unk2);
        }
    }
    PSVECAdd(&item_data->pos, &item_data->x64_vec_unk2, &item_data->pos);
    it_8027346C(gobj);
    it_802714C0(gobj);
}

void Item_80269978(HSD_GObj* gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    if (item_data->collided != NULL && item_data->collided(gobj)) {
        item_data->destroy_type = 1;
        Item_8026A8EC(gobj);
    } else {
        HSD_JObjSetTranslate((HSD_JObj*) HSD_GObjGetHSDObj(gobj),
                             &item_data->pos);
        it_8027574C(gobj);
        it_8026C368(gobj);
    }
}

// this function is where the item accessory callback is called if it exists
static void Item_80269A9C(HSD_GObj* gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    efAsync_80067624(gobj, &item_data->xBC0);
    if (item_data->xDC8_word.flags.x9 == 0) {
        if (item_data->on_accessory != NULL) {
            item_data->on_accessory(gobj);
        }
    }
    item_data = (Item*) HSD_GObjGetUserData(gobj);
    if (item_data->xDCD_flag.b01 != 0) {
        CmSubject* CmSubject = item_data->x520_cameraBox;
        if (CmSubject != NULL) {
            CmSubject->x10 = item_data->pos;
            CmSubject->x1C = item_data->pos;
        }
    }
    it_80271A58(gobj);
    it_80272280(gobj);
    it_802722B0(gobj);
}

static void Item_80269B60(HSD_GObj* gobj)
{
    Item* item_data = gobj->user_data;
    if (item_data->xCFC != 0 && item_data->jumped_on != NULL &&
        item_data->jumped_on(gobj))
    {
        item_data->destroy_type = 2;
        Item_8026A8EC(gobj);
        return;
    }
    it_8027137C(gobj);
    it_8027146C(gobj);
}

static /// @remarks Somewhat arbitrary. Does not run on Hook Shot / Grapple
       /// Beam,
    ///          rather items such as the Barrel Cannon.
    void
    Item_80269BE4(HSD_GObj* gobj)
{
    Item* item_data = gobj->user_data;
    if (item_data->xDD0_flag.b5) {
        it_802701BC(gobj);

        if (item_data->grab_victim != NULL) {
            item_data->grab_dealt(gobj);
            item_data->grabbed_for_victim(item_data->grab_victim, gobj);
        }
    }
}

static void Item_80269C5C(HSD_GObj* gobj)
{
    u8 _[8];

    it_8026F9A0();
    it_802703E8(gobj);
    it_802706D0(gobj);
    it_80270E30(gobj);
}

/// Add to damage taken
void Item_80269CA0(Item* item_data, s32 damage)
{
    item_data->xC9C += damage;

    if (item_data->xC9C > 999) {
        item_data->xC9C = 999;
    }
}

static void Item_80269CC4(HSD_GObj* gobj)
{
    Item* temp_item = gobj->user_data;

    temp_item->xCA0 = 0;
    temp_item->xCA4 = 0;
    temp_item->xC94 = 0;
    temp_item->xCC8_knockback = 0.0f;
    temp_item->xC34_damageDealt = 0;
    temp_item->xC48 = 0;
    temp_item->xC4C = 0;
    temp_item->xC50 = 0;
    temp_item->xCCC_incDamageDirection = 0.0f;
    temp_item->xCB8_outDamageDirection = 0.0f;
    temp_item->xC68 = 0.0f;
    temp_item->xCD0 = 0.0f;
    temp_item->xCC0 = 0.0f;
    temp_item->xDCF_flag.b6 = false;
    temp_item->xCC4 = 0;
    temp_item->xCEC_fighterGObj = 0;
    temp_item->xCF0_itemGObj = 0;
    temp_item->xCF4_fighterGObjUnk = 0;
    temp_item->toucher = 0;
    temp_item->xC64_reflectGObj = 0;
    temp_item->xC90_absorbGObj = 0;
    temp_item->xCFC = 0;
    temp_item->xCB4 = -1;
    temp_item->xC38 = -1;
    temp_item->xCE0.z = 0.0f;
    temp_item->xCE0.y = 0.0f;
    temp_item->xCE0.x = 0.0f;
    temp_item->xCD4.z = 0.0f;
    temp_item->xCD4.y = 0.0f;
    temp_item->xCD4.x = 0.0f;
    temp_item->xDCE_flag.b5 = false;
    temp_item->xDCE_flag.b4 = false;
    temp_item->xDCC_flag.b1 = false;
    temp_item->xC70 = 1.0f;
    temp_item->xC6C = 1.0f;
    temp_item->xDCC_flag.b2 = false;
    temp_item->xDC8_word.flags.xB = false;
    temp_item->xCA8 = 0;
    temp_item->xDC8_word.flags.x3 = false;
    temp_item->xDC8_word.flags.x4 = false;
    temp_item->xDCE_flag.b6 = false;
}

static bool Item_80269DC8(HSD_GObj* gobj)
{
    HSD_GObjPredicate shield_bounced;
    HSD_GObjPredicate hit_shield;
    Item* item_data = gobj->user_data;

    if (item_data->xDCE_flag.b5 && item_data->ground_or_air == 1 &&
        (item_data->xDCE_flag.b4 ||
         item_data->xC54 < (f32) M_PI / 180 * (90 + it_804D6D28->unk_degrees)))
    {
        if (item_data->xDCE_flag.b4 == 0) {
            item_data->xC54 -= M_PI / 2;
            if (item_data->xC54 < 0.0f) {
                item_data->xC54 = 0.0f;
            }
        }

        shield_bounced = item_data->xB8_itemLogicTable->shield_bounced;

        if (shield_bounced != NULL && shield_bounced(gobj)) {
            item_data->destroy_type = 2;
            Item_8026A8EC(gobj);
            return true;
        }
    } else {
        hit_shield = item_data->xB8_itemLogicTable->hit_shield;

        if (it_80274C78(gobj)) {
            item_data->xCA8 = item_data->xC50;
        }

        if (hit_shield != NULL && hit_shield(gobj)) {
            item_data->destroy_type = 2;
            Item_8026A8EC(gobj);
            return true;
        }
    }

    return false;
}

static bool Item_80269F14(HSD_GObj* gobj)
{
    f32 temp_f30;
    bool (*cb_OnReflect)(HSD_GObj*);
    s32 i;
    u32 var_r27;
    Item* temp_item = (Item*) HSD_GObjGetUserData(gobj);

    if (temp_item->xDCC_flag.b1 == 0) {
        if (temp_item->kind == 34) {
            if (temp_item->xDCC_flag.b2 == 0) {
                temp_item->owner = temp_item->xC64_reflectGObj;
                temp_item->x20_team_id = ftLib_80086EB4(temp_item->owner);
            }
        } else {
            temp_item->owner = temp_item->xC64_reflectGObj;
            temp_item->x20_team_id = ftLib_80086EB4(temp_item->owner);
        }
    }

    db_80225DD8(gobj, temp_item->owner);
    temp_item->xD90.x2070_int = temp_item->xC74;
    temp_item->xD94 = temp_item->xC78;
    temp_item->xD9C = temp_item->xC80;
    temp_item->xDA4_word = temp_item->xC88;
    temp_item->xDA8_short = temp_item->xC8C;
    cb_OnReflect = temp_item->xB8_itemLogicTable->reflected;
    if (cb_OnReflect != NULL && cb_OnReflect(gobj)) {
        temp_item->destroy_type = 2;
        Item_8026A8EC(gobj);
        return true;
    }
    if (temp_item->xDCC_flag.b0 == 0) {
        for (i = 0; i < 4; i++) // 4 here is the maximum amount of hitboxes
                                // available in the vanilla Item struct
        {
            if (temp_item->x5D4_hitboxes[i].hit.state != HitCapsule_Disabled) {
                temp_f30 =
                    temp_item->x5D4_hitboxes[i].hit.damage * temp_item->xC6C +
                    0.99f;
                var_r27 = temp_f30;
                if (var_r27 > it_804D6D28->xD8) {
                    var_r27 = it_804D6D28->xD8;
                }
                it_80272460(&temp_item->x5D4_hitboxes[i].hit, var_r27, gobj);
            }
        }
    }
    return false;
}

static void Item_8026A0A0(HSD_GObj* gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    if (item_data->xDC8_word.flags.x7 != 0) {
        if ((item_data->xDC8_word.flags.xA == 0) &&
            (item_data->xDC8_word.flags.x8 == 0))
        {
            Item_8026A1E8(gobj);
        }
        item_data->xDC8_word.flags.x7 = 0;
    }
}

static void Item_8026A0FC(HSD_GObj* gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    if (item_data->xDC8_word.flags.x8 != 0) {
        if ((item_data->xDC8_word.flags.xA == 0) &&
            (item_data->xDC8_word.flags.x7 == 0))
        {
            Item_8026A1E8(gobj);
        }
        item_data->xDC8_word.flags.x8 = 0;
    }
}

static void func_8026A158_helper(HSD_GObj* atkCollGObj)
{
    Item* temp_item = (Item*) HSD_GObjGetUserData(atkCollGObj);
    temp_item->xDC8_word.flags.x8 = 1;
    Item_8026A158(atkCollGObj);
}

static void Item_8026A158(HSD_GObj* gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    if (item_data->entered_hitlag != NULL) {
        item_data->entered_hitlag(gobj);
    }
    item_data->xDC8_word.flags.x9 = 1;
    if (item_data->atk_victim != NULL && it_80272D1C(item_data->atk_victim) &&
        item_data->xDC8_word.flags.x8 == 0)
    {
        func_8026A158_helper(item_data->atk_victim);
    }
}

static void func_8026A1E8_inline(HSD_GObj* atkCollGObj)
{
    Item* temp_item = (Item*) HSD_GObjGetUserData(atkCollGObj);
    if (temp_item->xDC8_word.flags.x8 != 0) {
        if ((temp_item->xDC8_word.flags.xA == 0) &&
            (temp_item->xDC8_word.flags.x7 == 0))
        {
            Item_8026A1E8(atkCollGObj);
        }
        temp_item->xDC8_word.flags.x8 = 0;
    }
}

static void Item_8026A1E8(HSD_GObj* gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    if (item_data->exited_hitlag != NULL) {
        item_data->exited_hitlag(gobj);
    }
    item_data->xDC8_word.flags.x9 = 0;
    if (item_data->atk_victim != NULL && it_80272D1C(item_data->atk_victim) &&
        item_data->xDC8_word.flags.x8 == 0)
    {
        func_8026A1E8_inline(item_data->atk_victim);
    }
}

static bool processCallback(HSD_GObjPredicate cb, HSD_GObj* gobj,
                            Item* item_data)
{
    if (cb && cb(gobj)) {
        item_data->destroy_type = 2;
        Item_8026A8EC(gobj);
        return true;
    }
    return false;
}

static bool OnTakeDamageThink(HSD_GObj* gobj, Item* item_data)
{
    item_data->xC9C += item_data->xCA0;
    if (item_data->xC9C > 999) {
        item_data->xC9C = 999;
    }
    item_data->xCA8 = item_data->xCA0;
    item_data->xDC8_word.flags.xB = 1;
    return processCallback(item_data->xB8_itemLogicTable->dmg_received, gobj,
                           item_data);
}

static bool OnClankThink(HSD_GObj* gobj, Item* item_data)
{
    bool (*cb_OnClank)(HSD_GObj*) = item_data->xB8_itemLogicTable->clanked;
    if (it_80274C78(gobj)) {
        item_data->xCA8 = item_data->xC48;
    }
    return processCallback(cb_OnClank, gobj, item_data);
}

static bool OnGiveDamageThink(HSD_GObj* gobj, Item* item_data)
{
    bool (*cb_OnGiveDamage)(HSD_GObj*) =
        item_data->xB8_itemLogicTable->dmg_dealt;
    if (it_80274C78(gobj)) {
        item_data->xCA8 = item_data->xC34_damageDealt;
    }
    return processCallback(cb_OnGiveDamage, gobj, item_data);
}

static void EnterHitlagThink(HSD_GObj* gobj, Item* item_data)
{
    if (!item_data->xDC8_word.flags.x9) {
        item_data = GetItemData(gobj);
        if (item_data->entered_hitlag) {
            item_data->entered_hitlag(gobj);
        }
        item_data->xDC8_word.flags.x9 = 1;

        if ((item_data->atk_victim) && it_80272D1C(item_data->atk_victim) &&
            !item_data->xDC8_word.flags.x8)
        {
            func_8026A158_helper(item_data->atk_victim);
        }
    }
}

static void checkHitLag(f32 min_value, Item* item_data)
{
    if (item_data->xCBC_hitlagFrames < min_value) {
        item_data->xCBC_hitlagFrames = min_value;
    }
    item_data->xDC8_word.flags.xA = 1;
}

static void Item_8026A294(HSD_GObj* gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);

    if ((item_data->xCC8_knockback) || (item_data->xCA0)) {
        if (OnTakeDamageThink(gobj, item_data)) {
            return;
        }
    } else if (item_data->xC50) {
        if (Item_80269DC8(gobj)) {
            return;
        }
    } else if (item_data->xC48) {
        if (OnClankThink(gobj, item_data)) {
            return;
        }
    } else if ((item_data->xC34_damageDealt) || (item_data->xC4C)) {
        if (OnGiveDamageThink(gobj, item_data)) {
            return;
        }
    } else if (item_data->xC64_reflectGObj != NULL) {
        if (Item_80269F14(gobj)) {
            return;
        }
    } else if (item_data->xC90_absorbGObj != NULL) {
        if (processCallback(item_data->xB8_itemLogicTable->absorbed, gobj,
                            item_data))
        {
            return;
        }
    } else if (item_data->xDCE_flag.b6) {
        if (processCallback(item_data->touched, gobj, item_data)) {
            return;
        }
    }

    if ((item_data->xDC8_word.flags.xD) && (item_data->xCC0 > 0.0f)) {
        checkHitLag(item_data->xCC0, item_data);

        EnterHitlagThink(gobj, item_data);
    } else if (item_data->xCA8) {
        checkHitLag(it_8026B424(item_data->xCA8), item_data);

        EnterHitlagThink(gobj, item_data);
    }
    if ((item_data->xDC8_word.flags.x4) || (item_data->xDC8_word.flags.x3)) {
        EnterHitlagThink(gobj, item_data);

        if (item_data->xDC8_word.flags.x4) {
            item_data->xDC8_word.flags.x8 = 1;
            item_data->xDC8_word.flags.x4 = 0;
        } else {
            item_data->xDC8_word.flags.x7 = 1;
            item_data->xDC8_word.flags.x3 = 0;
        }
    }
    Item_80269CC4(gobj);
}

static void Item_8026A788(HSD_GObj* gobj)
{
    Item* item_data = gobj->user_data;
    int dynamicBonesNum = item_data->x374_dynamicBonesNum;
    Item_DynamicBones* dynamicBones = item_data->xD4_dynamicBones;
    int i;

    it_80272304(gobj);
    for (i = 0; i < dynamicBonesNum; i++, dynamicBones++) {
        lb_8001044C(&dynamicBones->dyn_desc, &item_data->xB6C_vars[0].xB6C.x,
                    item_data->xB68, 0.0f, 0, dynamicBones->flags, 0, 1);
    }
}

static void Item_8026A810(HSD_GObj* gobj)
{
    Item* temp_item = (Item*) HSD_GObjGetUserData(gobj);

    if (temp_item->xB8_itemLogicTable->spawned != NULL) {
        temp_item->xB8_itemLogicTable->spawned(gobj);
    }
}

void Item_8026A848(HSD_GObj* gobj, HSD_GObj* fighter_gobj)
{
    Item* temp_item = (Item*) HSD_GObjGetUserData(gobj);

    if (temp_item->hold_kind == 8 && temp_item->kind != It_Kind_Link_Bomb &&
        temp_item->kind != It_Kind_CLink_Bomb &&
        temp_item->kind != It_Kind_Peach_Turnip &&
        temp_item->kind != It_Kind_Peach_Parasol)
    {
        if (ftLib_800867CC(fighter_gobj) == gobj) {
            ftLib_80086764(fighter_gobj);
        }
    } else if (ftLib_800867A0(fighter_gobj, gobj)) {
        ftLib_80086724(fighter_gobj, gobj);
    }
}

static void DestroyItemInline(HSD_GObj* gobj, Item* other_ip)
{
    Item* ip = gobj->user_data;
    HSD_GObj* other = other_ip->owner;

    if (ip->hold_kind == 8 && ip->kind != It_Kind_Link_Bomb &&
        ip->kind != It_Kind_CLink_Bomb && ip->kind != It_Kind_Peach_Turnip &&
        ip->kind != It_Kind_Peach_Parasol)
    {
        if (ftLib_800867CC(other) == gobj) {
            ftLib_80086764(other);
        }
    } else if (ftLib_800867A0(other, gobj)) {
        ftLib_80086724(other, gobj);
    }
}

static void ItemSwitch(HSD_GObj* gobj)
{
    Item* ip = gobj->user_data;
    enum_t destroy_type = ip->destroy_type;

    switch (destroy_type) {
    case 0:
        it_8027327C(gobj, ip->xCC_item_attr->destroy_gfx, ip->destroy_sfx);
        break;

    case 2:
    case 1:
        it_8027327C(gobj, ip->xCC_item_attr->x68, ip->xD80);
        break;

    case 3:
    case 4:
        break;
    }
}

/// @todo Could this be a higher-level inline in gobjproc.h or
/// something?
static void RunGObjCallback(HSD_GObj* gobj, HSD_GObjEvent arg1)
{
    if (arg1 != NULL) {
        arg1(gobj);
    }
}

static void func_8026A8EC_inline1(HSD_GObj* gobj)
{
    Item* ip = (Item*) HSD_GObjGetUserData(gobj);

    if (ip->xDC8_word.flags.xE) {
        ftLib_80087050(ip->ecb_lock);
        ip->xDC8_word.flags.xE = false;
        ip->ecb_lock = -1;
    }
}

static void func_8026A8EC_inline2(HSD_GObj* gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(gobj);
    RunGObjCallback(gobj, it->xB8_itemLogicTable->destroyed);
}

static void func_8026A8EC_inline3(HSD_GObj* gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(gobj);

    if (it->xDCD_flag.b01 != 0 && it->x520_cameraBox != NULL) {
        Camera_800290D4(it->x520_cameraBox);
        it->x520_cameraBox = NULL;
        it->xDCD_flag.b01 = 0;
    }
}

void Item_8026A8EC(Item_GObj* gobj)
{
    Item* ip = (Item*) HSD_GObjGetUserData(gobj);

    if (!it_80272D1C(gobj) || ip == NULL) {
        OSReport("===== Not Found Item_Struct!! =====\n");
        __assert("item.c", 2405, "0");
    }

    it_802725D4(gobj);
    Item_802675A8(gobj);
    func_8026A8EC_inline1(gobj);
    efLib_DestroyAll(gobj);

    if (!ip->xDCF_flag.b2 && (!ip->xDC8_word.flags.x13 || ip->owner == NULL)) {
        ItemSwitch(gobj);
    }

    func_8026A8EC_inline2(gobj);

    if (ip->xDC8_word.flags.x13 && ip->owner != NULL &&
        ftLib_80086960(ip->owner))
    {
        DestroyItemInline(gobj, ip);
    }

    ip->owner = NULL;
    func_8026A8EC_inline3(gobj);

    {
        int i;
        for (i = 0; i < ip->x374_dynamicBonesNum; i++) {
            lb_8000FD18(&ip->xD4_dynamicBones[i].dyn_desc);
        }
    }

    Item_8026B0B4(gobj);
    efAsync_80067688((struct ef_UnkStruct3*) &ip->xBC0);
    HSD_GObjPLink_80390228(gobj);
}

// Pick up item
void Item_8026AB54(Item_GObj* gobj, HSD_GObj* owner_gobj, Fighter_Part part)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    PAD_STACK(16);

    it_80273168(gobj); // sets pickup sfx?
    it_802742F4(gobj, owner_gobj, part);
    RunGObjCallback(gobj, item_data->xB8_itemLogicTable->picked_up);
    Item_8026B074(item_data);
}

void Item_8026ABD8(Item_GObj* gobj, Vec3* pos, f32 arg2)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    PAD_STACK(8);

    item_data->xC44 = arg2;
    it_802731A4(gobj);
    it_80273B50(gobj, pos);
    RunGObjCallback(gobj, item_data->xB8_itemLogicTable->dropped);
    it_80274198(gobj, true);
    it_802754D4(gobj);

    if (it_8026B6C8(gobj)) {
        it_80275390(gobj);
    }
}

void Item_8026AC74(HSD_GObj* gobj, Vec3* arg1, Vec3* arg2, f32 arg3)
{
    Item* item_data = GetItemData(gobj);
    item_data->xC44 = arg3;
    it_802731A4(gobj);
    it_80273748(gobj, arg1, arg2);
    RunGObjCallback(gobj, item_data->xB8_itemLogicTable->dropped);
    it_802741F4(gobj, true);
    it_802754D4(gobj);

    if (it_8026B6C8(gobj)) {
        it_80275390(gobj);
    }
}

void Item_8026AD20(HSD_GObj* gobj, Vec3* arg1, Vec3* arg2, f32 arg3)
{
    Item* item_data = GetItemData(gobj);
    it_802731E0(gobj);
    item_data->xC44 = arg3;
    it_80273748(gobj, arg1, arg2);
    RunGObjCallback(gobj, item_data->xB8_itemLogicTable->thrown);
    it_802741F4(gobj, true);
    it_802754D4(gobj);
}

void Item_8026ADC0(HSD_GObj* gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    if (item_data->xB8_itemLogicTable->entered_air != NULL) {
        item_data->xB8_itemLogicTable->entered_air(gobj);
        item_data->xDC8_word.flags.x1F = true;
    }
}

void Item_OnUserDataRemove(void* user_data)
{
    Item* item_data = (Item*) user_data;

    if (item_data->xBBC_dynamicBoneTable != NULL) {
        HSD_ObjFree(&item_dynamic_bones_alloc_data,
                    item_data->xBBC_dynamicBoneTable);
    }

    HSD_ObjFree(&item_alloc_data, item_data);
}

u32 Item_8026AE60(void)
{
    u32 result = it_804D6D14++;

    if (it_804D6D14 == 0) {
        it_804D6D14++;
    }

    return result;
}

void Item_8026AE84(Item* item_data, enum_t sfx, u8 pan, u8 volume)
{
    if (sfx != 540000) {
        if (sfx != 540001) {
            item_data->xD6C =
                lbAudioAx_800237A8(lbAudioAx_800233EC(sfx), pan, volume);
        } else {
            item_data->xD6C = lbAudioAx_800237A8(540000, pan, volume);
        }
    }
}

void Item_8026AF0C(Item* item_data, enum_t sfx, u8 pan, u8 volume)
{
    if (sfx != 540000) {
        if (sfx != 540001) {
            if (item_data->sfx_unk1 != SFX_NONE) {
                lbAudioAx_800236B8(item_data->sfx_unk1);
            }
            item_data->sfx_unk1 =
                lbAudioAx_800237A8(lbAudioAx_800233EC(sfx), pan, volume);
        } else {
            Item_8026B034(item_data);
        }
    }
}

void Item_8026AFA0(Item* item_data, enum_t sfx, u8 pan, u8 volume)
{
    if (sfx != 540000) {
        if (sfx != 540001) {
            if (item_data->sfx_unk2 != SFX_NONE) {
                lbAudioAx_800236B8(item_data->sfx_unk2);
            }
            item_data->sfx_unk2 =
                lbAudioAx_800237A8(lbAudioAx_800233EC(sfx), pan, volume);
        } else {
            Item_8026B074(item_data);
        }
    }
}

void Item_8026B034(Item* item_data)
{
    if (item_data->sfx_unk1 != SFX_NONE) {
        lbAudioAx_800236B8(item_data->sfx_unk1);
    }

    item_data->sfx_unk1 = SFX_NONE;
}

void Item_8026B074(Item* item_data)
{
    if (item_data->sfx_unk2 != SFX_NONE) {
        lbAudioAx_800236B8(item_data->sfx_unk2);
    }

    item_data->sfx_unk2 = SFX_NONE;
}

static void Item_8026B0B4(HSD_GObj* gobj)
{
    Item* item_data = (Item*) HSD_GObjGetUserData(gobj);
    lbAudioAx_80026510(gobj);

    if (item_data->xD6C != SFX_NONE) {
        lbAudioAx_800265C4(gobj, item_data->xD6C);
        item_data->xD6C = SFX_NONE;
    }

    if (item_data->sfx_unk1 != SFX_NONE &&
        lbAudioAx_800265C4(gobj, item_data->sfx_unk1) == 1)
    {
        if (item_data->sfx_unk1 != SFX_NONE) {
            lbAudioAx_800236B8(item_data->sfx_unk1);
        }
        item_data->sfx_unk1 = SFX_NONE;
    }

    if (item_data->sfx_unk2 != SFX_NONE &&
        lbAudioAx_800265C4(gobj, item_data->sfx_unk2) == 1)
    {
        if (item_data->sfx_unk2 != SFX_NONE) {
            lbAudioAx_800236B8(item_data->sfx_unk2);
        }
        item_data->sfx_unk2 = SFX_NONE;
    }

    if (item_data->sfx_unk1 != SFX_NONE) {
        lbAudioAx_800236B8(item_data->sfx_unk1);
    }

    item_data->sfx_unk1 = SFX_NONE;

    if (item_data->sfx_unk2 != SFX_NONE) {
        lbAudioAx_800236B8(item_data->sfx_unk2);
    }

    item_data->sfx_unk2 = SFX_NONE;
    item_data->xD6C = SFX_NONE;
}

/// Check if item is grabbable
bool Item_IsGrabbable(Item_GObj* gobj)
{
    Item* temp_item;

    temp_item = gobj->user_data;

    if ((temp_item->xDC8_word.flags.x15 != 0) &&
        (temp_item->xB8_itemLogicTable->picked_up != NULL))
    {
        return true;
    }

    return false;
}
